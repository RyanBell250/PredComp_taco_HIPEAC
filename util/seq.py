
import itertools
from itertools import chain
import os

module_path = os.path.abspath(__file__)
MODULE_DIR = os.path.dirname(module_path)


with open(f'{MODULE_DIR}/../Space/opts_group_5.txt','r') as f:
    options=f.read().split('---------------------------')
for i in range(len(options)):
    options[i]=[x for x in options[i].split('\n') if x] 

op={}
for i in range(1,6):
    op[str(i)]=options[i-1]

op['comb']=op['1']+op['2']+op['3']+op['4']+op['5']

def gen_seq(op_type,index):
    seq='-O3 '
    if len(index)!=len(op[op_type]):
        raise ValueError(f'Invalid input length. {op_type} expected length: {len(op[op_type])}, received {len(index)}.')
    for i in range(len(index)):
        if index[i]==1:
            seq+=f'{op[op_type][i]} '
        else:
            seq+=f'-fno-{op[op_type][i][2:]} '
    
    return seq[:-1]

def gen_global_seq(seq):
    result={}
    for p in seq:
        result[p]=[]
        for s in seq[p]:
            result[p].append(gen_seq('comb',s))
    return result

def gen_comb_seq(pred_result):
    result={}
    for p in pred_result['1']:
        x=itertools.product(pred_result['1'][p], pred_result['2'][p], pred_result['3'][p],pred_result['4'][p],pred_result['5'][p])
        result[p]=[list(chain.from_iterable(lst)) for lst in x]
    return result

    