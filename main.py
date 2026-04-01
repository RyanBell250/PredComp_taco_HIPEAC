
import os
from PredComp.Dataset.process.heads import cBench
import json
import itertools
import random
from util.seq import gen_seq,gen_comb_seq,gen_global_seq
from Inference.predict import pred_result_seq
import argparse
parser = argparse.ArgumentParser()
parser.add_argument('--bin_path', type=str, required=False, default='', help='Path to GCC bin directory')
args = parser.parse_args()
bin_path = args.bin_path

if __name__=='__main__':

    bin_path='/home/gby/gcc_install/build/bin'
    with open('Dataset/process/cbench.json','r') as f:
        prog=json.load(f)
    cbench={}
    all_features={}
    for p in prog:
        evaluator=cBench(p,prog[p][0],prog[p][1],prog[p][2],bin_path)
        cbench[p]=evaluator
        all_features[p]=evaluator.gen_feature()
        

    pred_result={}
    for op in range(1,6):
        pred_result[str(op)]=pred_result_seq(all_features,str(op),topk=3)

    global_candidate=gen_comb_seq(pred_result)
    result=pred_result_seq(all_features,'comb',topk=3,comb_seq=global_candidate)
    seq=gen_global_seq(result)

    for p in seq:
        cbench[p].prepare()
        best_perf=cbench[p].O3_perf
        best_seq='-O3'
        print(f'{p} O3 exec time:{cbench[p].O3_perf:.3f}')
        for i in range(len(seq[p])):
            print(seq[p][i])
            perf,improv=cbench[p].evaluate(seq[p][i])
            print(f'{p} Top-{i+1} sequence: {seq[p][i]}, exec time:{perf:.3f}, perf improv: {improv:.3f}')
            if perf<best_perf:
                best_perf=perf
                best_seq=seq[p][i]
        print(f'{p} best sequence: {best_seq}, best exec time: {best_perf:.3f}, best improv: {cbench[p].O3_perf/best_perf:.3f}')