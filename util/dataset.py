from torch.utils.data import DataLoader, TensorDataset,Dataset
from torch_geometric.data import Data, DataLoader,Batch
import os
import json
import torch
import copy

module_path = os.path.abspath(__file__)
MODULE_DIR = os.path.dirname(module_path)

class PairDataset(Dataset):
    def __init__(self, datasetA, datasetB):
        self.inline_dataset = datasetA
        self.loop_dataset = datasetB

    def __len__(self):
        return min(len(self.inline_dataset), len(self.loop_dataset))  

    def __getitem__(self, idx):
        return self.inline_dataset[idx], self.loop_dataset[idx]

def collate(data_list):
    batchA = Batch.from_data_list([data[0] for data in data_list])
    batchB = Batch.from_data_list([data[1] for data in data_list])
    return batchA, batchB

def convert_inline_graph_to_geo(graph):
    node_features = []
    node_names = list(graph["node"].keys())
    node_indices = {name: idx for idx, name in enumerate(node_names)}
    for name in node_names:
        feature = list(graph["node"][name].values())
        node_features.append(feature)
    
    edge_index = []
    edge_attr = []
    for edge in graph["edge"]:
        src, dst = edge[0], edge[1]
        src_idx = node_indices[src]
        dst_idx = node_indices[dst]
        edge_index.append([src_idx, dst_idx])
        edge_attr.append(edge[2:]) 
    
    x = torch.tensor(node_features, dtype=torch.float)
    if edge_index:
        edge_index = torch.tensor(edge_index, dtype=torch.long).t().contiguous()
    else:
        edge_index = torch.empty((2, 0), dtype=torch.long)
    if edge_attr:
        edge_attr = torch.tensor(edge_attr, dtype=torch.float)
    else:
        edge_attr = torch.empty((0, 6), dtype=torch.float)  
    return [x,edge_index,edge_attr]

def convert_loop_graph_to_geo(graph):
    node_features = []
    node_names = list(graph["node"].keys())
    node_indices = {name: idx for idx, name in enumerate(node_names)}
    for name in node_names:
        feature = graph["node"][name]
        node_features.append(feature)
    # print(node_indices)
    edge_index = []
    edge_attr = []
    for edge in graph["edge"]:
        src, dst = edge[0], edge[1]
        src_idx = node_indices[src]
        dst_idx = node_indices[dst]
        edge_index.append([src_idx, dst_idx])
        edge_attr.append(edge[2:])  
    
    x = torch.tensor(node_features, dtype=torch.float)
    if edge_index:
        edge_index = torch.tensor(edge_index, dtype=torch.long).t().contiguous()
    else:
        edge_index = torch.empty((2, 0), dtype=torch.long)
    if edge_attr:
        edge_attr = torch.tensor(edge_attr, dtype=torch.float)
    else:
        edge_attr = torch.empty((0, 3), dtype=torch.float)  
    return [x,edge_index,edge_attr]

def convert_to_Pairdataset(dataset):
    datasetA=[]
    datasetB=[]
    for d in dataset:
        datasetA.append(Data(x=d['inline_feature'][0],edge_index=d['inline_feature'][1],edge_attr=d['inline_feature'][2]))
        datasetB.append(Data(x=d['loop_feature'][0],edge_index=d['loop_feature'][1],edge_attr=d['loop_feature'][2],
                        vec=d['vec'],seq=d['seq'],name=d['name']))
    data=PairDataset(datasetA,datasetB)
    return data


def load_subspace_data(feature,op_type):
    with open(f'{MODULE_DIR}/../Dataset/process/label_v1.json','r') as f:
        label=json.load(f)
    dataset=[]
    for p in feature:
        prog={}
        prog['inline_feature']=convert_inline_graph_to_geo(feature[p]['inline_feature'])
        prog['loop_feature']=convert_loop_graph_to_geo(feature[p]['loop_feature'])
        prog['vec']=torch.FloatTensor(feature[p]['vec'])
        prog['seq']=torch.tensor(label[op_type],dtype=torch.float)
        prog['label']=torch.tensor([0 for i in range(len(label[op_type]))],dtype=torch.float)
        prog['perf']=torch.tensor([0 for i in range(len(label[op_type]))],dtype=torch.float)
        prog['name']=feature[p]['name']

        dataset.append(prog)
    return convert_to_Pairdataset(dataset)

def load_comb_data(feature,comb_seq):
    dataset=[]
    for p in feature:
        prog={}
        prog['inline_feature']=convert_inline_graph_to_geo(feature[p]['inline_feature'])
        prog['loop_feature']=convert_loop_graph_to_geo(feature[p]['loop_feature'])
        prog['vec']=torch.FloatTensor(feature[p]['vec'])
        prog['seq']=torch.tensor(comb_seq[p],dtype=torch.float)
        prog['label']=torch.tensor([0 for i in range(len(comb_seq[p]))],dtype=torch.float)
        prog['perf']=torch.tensor([0 for i in range(len(comb_seq[p]))],dtype=torch.float)
        prog['name']=feature[p]['name']

        dataset.append(prog)
    return convert_to_Pairdataset(dataset)

    