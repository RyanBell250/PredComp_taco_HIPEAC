
import itertools
from itertools import chain


inline_op=['-finline', '-fearly-inlining', '-finline-small-functions', 
    '-fpartial-inlining', '-finline-functions', 
    '-finline-functions-called-once','-findirect-inlining']


loop_op=['-funswitch-loops', '-fsplit-loops', '-ftree-loop-vectorize',
 '-floop-unroll-and-jam', '-fpeel-loops', '-ftree-loop-if-convert', 
 '-ftree-slp-vectorize', '-funroll-loops', '-ftree-loop-distribution', 
 '-ftree-loop-ivcanon', '-ftree-loop-im', '-fprefetch-loop-arrays']

sched_op=['-fschedule-insns', '-fschedule-insns2', 
    '-fsel-sched-pipelining-outer-loops', '-fsched-stalled-insns', 
    '-fsel-sched-pipelining', '-fsched-spec-load', 
    '-fsched-rank-heuristic', '-fsched-pressure', 
    '-fsched-dep-count-heuristic', '-fsched-critical-path-heuristic', 
    '-fsched-last-insn-heuristic', '-fsched-group-heuristic', 
    '-fsched-interblock', '-fselective-scheduling', 
    '-fselective-scheduling2', '-fsched2-use-superblocks', 
    '-fsched-spec', '-flive-range-shrinkage']

op={'inline':inline_op,'loop':loop_op,'sched':sched_op,
    'comb':inline_op+loop_op+sched_op
    }

O3={'inline':[1,1,1,1,1,1,1],'loop':[1,1,1,1,1,1,1,0,1,1,1,1],'sched':[0,1,0,0,0,0,1,0,1,1,1,1,1,0,0,0,1,0]}

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
    for p in pred_result['inline']:
        for op in ['inline','loop','sched']:
            pred_result[op][p].append(O3[op])
        x=itertools.product(pred_result['inline'][p], pred_result['loop'][p], pred_result['sched'][p])
        result[p]=[list(chain.from_iterable(lst)) for lst in x]
    return result

    