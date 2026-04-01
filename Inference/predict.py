

from torch.utils.data import DataLoader
from util.dataset import collate,load_subspace_data,load_comb_data
from util.seq import gen_seq
from Model.model import RankModel
import torch
import os
import json
import csv
import time
import statistics
from concurrent.futures import ThreadPoolExecutor

module_path = os.path.abspath(__file__)
MODULE_DIR = os.path.dirname(module_path)

device = torch.device("cpu")


def pred_result_seq(feature,op_type,topk,comb_seq=''):
    if op_type=='comb':
        test_data=load_comb_data(feature,comb_seq)
    else:
        test_data=load_subspace_data(feature,op_type)
    test_loader = DataLoader(test_data, batch_size=1,collate_fn=collate)
    model=torch.load(f'{MODULE_DIR}/../saved_model/{op_type}.pth',weights_only=False)
    model.eval()
    model.to(device)
    result={}
    with torch.no_grad():
        for data in test_loader:
            data[0].to(device)
            data[1].to(device)
            all_seq=data[1].seq
            output=model(data)
            output=output.squeeze(0).squeeze(-1)
            probs = torch.sigmoid(output)
            name=data[1].name[0]
            topk_values, topk_indices = torch.topk(probs, k=topk, dim=0)
            seq=[]
            for i in topk_indices:
                seq.append([int(x) for x in all_seq[i].tolist()])
            result[name]=seq
    return result
