import re
import csv
import programl as pg
import networkx as nx
import os
import ir2vec

module_path = os.path.abspath(__file__)

MODULE_DIR = os.path.dirname(module_path)

voca={}
with open(f'{MODULE_DIR}/vocabulary.csv','r') as f:
    f_csv=csv.reader(f)
    for row in f_csv:
        voca[row[0]]=int(row[1])

def extract_numbers(s):
    numbers = re.findall(r'[0-9]+(?:\.[0-9]+)?', s)
    converted_numbers = [float(num) if '.' in num else int(num) for num in numbers]
    while len(converted_numbers)<6:
        converted_numbers.append(0)

    return converted_numbers[:6]

def extract_function_name(log_content):
    # 匹配第一个空格后的部分，直到第一个括号之前
    pattern = r'\b(\w+)\s*\('
    match = re.search(pattern, log_content)
    if match:
        return match.group(1)
    else:
        return None


def extract_function_summary(log_content):
    pattern = r'IPA function summary for (.+?/\d+)'  # 非贪婪匹配
    match = re.search(pattern, log_content)
    if match:
        func_summary=match.group(1)
        return [func_summary,extract_function_name(func_summary)]
    else:
        return None


def extract_two_line_entries(log_content):
    # 匹配两行内容
    pattern = re.compile(r' {4}.*\n {6}.*')
    
    matches = pattern.findall(log_content)
    return matches

def gen_call_graph(filename):

    funcinfo={}
    edge=[]

    with open(f'{filename}','r') as f:
       cgraph=f.read().split('Flattening functions:')[0].split('\n')
       cgraph=[c for c in cgraph if not c.startswith('       op')]
       cgraph=('\n'.join(cgraph)).split('\n\n')[:-1]
    for c in cgraph:
        c=c.split('\n')
        func_name=extract_function_summary(c[0])
        if func_name == None:
            continue
        func_name=func_name[0]
        funcinfo[func_name]={
                            'global time': float(c[1].strip().split()[-1]),
                            'self size': float(c[2].strip().split()[-1]),
                            'global size':float(c[3].strip().split()[-1]),
                            'min size':float(c[4].strip().split()[-1]),
                            'self stack':float(c[5].strip().split()[-1]), 
                            'global stack':float(c[6].strip().split()[-1]),
                            'calls':extract_two_line_entries('\n'.join(('\n'.join(c)).split(' calls:')[1].split('\n')[1:]))}
    for func in funcinfo:
        # print(func)
        for c in funcinfo[func]['calls']:
            # print(c)
            pattern = re.compile(r'(.+?/\d+)', re.MULTILINE)
            callee_func = pattern.findall(c)[0].strip()
            n=extract_numbers(c.split('\n')[1])
            edge.append([func,callee_func]+n[:6])
        del funcinfo[func]['calls']
    for e in edge:
        for func in [e[0],e[1]]:
            if func not in funcinfo:
                funcinfo[func]={
                    'global time': -1,
                    'self size': -1,
                    'global size': -1,
                    'min size':-1,
                    'self stack':-1,
                    'global stack':-1
                }
    graph={'node':funcinfo,'edge':edge}
    return graph

def gen_flow_graph(file_path,para):
    G=pg.from_clang([file_path, para])
    graph=pg.to_networkx(G)
    for node, attrs in graph.nodes(data=True):
        if 'features' in graph.nodes[node]:
            del graph.nodes[node]['features']
        if 'text' not in graph.nodes[node] or graph.nodes[node]['text'] not in voca:
            graph.nodes[node]['text']=102
        else:
            graph.nodes[node]['text']=voca[graph.nodes[node]['text']]
    for node1, node2, edge_data in graph.edges(data=True):
        start_block = graph.nodes[node1]['block']
        end_block = graph.nodes[node2]['block']

        if start_block == end_block:
            graph.edges[node1, node2,0]['block'] = 0  # 使用 graph.edges 修改边的属性
        elif start_block > end_block:
            graph.edges[node1, node2,0]['block'] = -1
        else:
            graph.edges[node1, node2,0]['block'] = 1
    data={'node':{},'edge':[]}
    for node, attr in graph.nodes(data=True):
        data['node'][node]=[attr['block'],attr['function'],attr['text'],attr['type']]
    for u, v, attr in graph.edges(data=True):
        data['edge'].append([u,v,attr['flow'],attr['position'],attr['block']])
    return data

def gen_vec(path):
    initObj=ir2vec.initEmbedding(path,'fa','p')
    progVec = initObj.getProgramVector()
    return progVec