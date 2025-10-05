import torch
import torch.nn.functional as F
import torch.nn as nn
from torch_geometric.nn import GATConv, global_mean_pool
from torch.nn import MultiheadAttention

class FeatureEncoder(nn.Module):
    def __init__(self, input_dim):
        super(FeatureEncoder, self).__init__()
        self.encoder = nn.Sequential(
            nn.Linear(input_dim, input_dim//2),
            nn.ReLU(),
            nn.Linear(input_dim// 2, input_dim//2),
            nn.LayerNorm(input_dim//2)
        )

    def forward(self, x):
        return self.encoder(x)

class SubLoopModel(torch.nn.Module):
    def __init__(self,loop_arg):
        super(SubLoopModel, self).__init__()
        input_dim,hidden_dim=loop_arg[0],loop_arg[1]
        self.conv1 = GATConv(input_dim, hidden_dim, heads=2)
        self.conv2 = GATConv(hidden_dim*2, hidden_dim * 2, heads=2)
        self.program_linear=FeatureEncoder(hidden_dim*4)

    def forward(self,loop_x, loop_edge_index, loop_batch, loop_edge_attr):
        loop_x = F.relu(self.conv1(loop_x, loop_edge_index,edge_attr=loop_edge_attr))
        loop_x = F.relu(self.conv2(loop_x, loop_edge_index,edge_attr=loop_edge_attr))
        
        program_feature = global_mean_pool(loop_x, loop_batch)
        program_feature=self.program_linear(program_feature)
    
        return program_feature

class SubInlineModel(torch.nn.Module):
    def __init__(self, inline_arg):
        super(SubInlineModel, self).__init__()
        input_dim,hidden_dim=inline_arg[0],inline_arg[1]
        self.conv1 = GATConv(input_dim, hidden_dim, heads=2)
        self.conv2 = GATConv(hidden_dim*2, hidden_dim * 2, heads=2)
        self.program_linear=FeatureEncoder(hidden_dim*4)

    def forward(self, inline_x, inline_edge_index, inline_batch, inline_edge_attr):
        inline_x = F.relu(self.conv1(inline_x, inline_edge_index,edge_attr=inline_edge_attr))
        inline_x = F.relu(self.conv2(inline_x, inline_edge_index,edge_attr=inline_edge_attr))
        program_feature = global_mean_pool(inline_x, inline_batch)
        program_feature=self.program_linear(program_feature)
        return program_feature

class SubSchedModel(torch.nn.Module):
    def __init__(self, sched_arg):
        super(SubSchedModel, self).__init__()
        input_dim,hidden_dim=sched_arg[0],sched_arg[1]
        self.net = nn.Sequential(
            nn.Linear(input_dim, hidden_dim),
            nn.ReLU(),
            nn.Linear(hidden_dim, hidden_dim),
            nn.ReLU(),
            nn.LayerNorm(hidden_dim)
        )
    
    def forward(self, x):
        program_feature=self.net(x)
        return program_feature

class SubSeqModel(torch.nn.Module):
    def __init__(self,seq_arg):
        super(SubSeqModel, self).__init__()
        input_dim,hidden_dim=seq_arg[0],seq_arg[1]
        self.seq_linear = nn.Sequential(
            nn.Linear(input_dim, hidden_dim),
            nn.ReLU(),
            nn.Linear(hidden_dim, hidden_dim),
            nn.ReLU(),
            nn.LayerNorm(hidden_dim)
        )
    def forward(self,seq):
        seq=self.seq_linear(seq)
        return seq


class RankModel(torch.nn.Module):
    def __init__(self, inline_arg,loop_arg,sched_arg,seq_arg, num_heads=2):
        super(RankModel, self).__init__()
        self.inline=SubInlineModel(inline_arg)
        self.loop=SubLoopModel(loop_arg)
        self.sched=SubSchedModel(sched_arg)
        self.seq=SubSeqModel(seq_arg)

        self.gate_fc = nn.Sequential(
            nn.Linear(768, 384),
            nn.ReLU(),
            nn.Linear(384, 128),
            nn.ReLU(),
            nn.Linear(128, 3)  # 输出3个通道的打分
        )
        self.layer_norm=nn.LayerNorm(256)
        self.self_attention=MultiheadAttention(embed_dim=256,num_heads=num_heads,batch_first=True)
        self.output_layer = nn.Sequential(
            nn.Linear(256 , 128),
            nn.ReLU(),
            nn.Linear(128 , 1)
        )

    def forward(self,data):
        inline_x, inline_edge_index, inline_batch, inline_edge_attr = data[0].x, data[0].edge_index, data[0].batch, data[0].edge_attr
        loop_x, loop_edge_index, loop_batch, loop_edge_attr = data[1].x, data[1].edge_index, data[1].batch, data[1].edge_attr
        batch_size = inline_batch.max().item() + 1
        vec=data[1].vec
        seq=data[1].seq
        vec=vec.view(batch_size,-1,300)
        seq=seq.view(batch_size,-1,seq.shape[1])
        inline_feature=self.inline(inline_x, inline_edge_index, inline_batch, inline_edge_attr)
        loop_feature=self.loop(loop_x, loop_edge_index, loop_batch, loop_edge_attr)
        sched_feature=self.sched(vec).squeeze(1)
        seq_feature=self.seq(seq)
        concat_features = torch.cat([inline_feature, loop_feature, sched_feature], dim=1)
        gating_logits = self.gate_fc(concat_features)
        gating_weights = F.softmax(gating_logits, dim=1) 
        w_inline = gating_weights[:, 0].unsqueeze(-1)  # (batch_size, 1)
        w_loop   = gating_weights[:, 1].unsqueeze(-1)
        w_sched  = gating_weights[:, 2].unsqueeze(-1)

        fused_feature = w_inline * inline_feature + \
                        w_loop   * loop_feature   + \
                        w_sched  * sched_feature  # shape: (batch_size, D)
        fused_feature=self.layer_norm(fused_feature)
        fused_feature=fused_feature.unsqueeze(1).expand(-1,seq_feature.shape[1],-1)
        combined_feature=seq_feature*fused_feature
        attn_output, _= self.self_attention(combined_feature,combined_feature,combined_feature)
        output=self.output_layer(attn_output)
        arg=(w_inline,w_loop,w_sched)
        return output,arg