import csv
import os
from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker
from PredComp.Dataset.process.database import OptionsMd5, Md5TestTime, CompileError, RunError, WrongOutput, Base,ProgramFeature
import subprocess
import psutil
import signal
import statistics
import uuid
import hashlib
from concurrent.futures import ThreadPoolExecutor
from PredComp.Dataset.process.feature import gen_call_graph,gen_flow_graph,gen_vec
import uuid
import time

# class Dataset --- a dataset of some projects, e.g. cBench
# class Project --- a project, e.g. cBench/automotive_bitcount
# class Test --- a test, e.g. a test in cBench/automotive_bitcount/_my_info_datasets
# format of project_info_file: project_name, project_path, exec_file, output_file, std_output_file
# format of std_output_file: test_name, test_std(md5), test_data
def preexec():
    os.setpgrp()

module_path = os.path.abspath(__file__)

MODULE_DIR = os.path.dirname(module_path)


def get_md5(stdout):
    return stdout.decode('ascii').split(' ')[0]

def reverse_op(op):
    if op.startswith('-fno-'):
        return f'-f{op[5:]}'
    return f'-fno-{op[2:]}'
def nor_op(op):
    if op.startswith('-fno-'):
        return f'-f{op[5:]}'
    return op

def convert2str(setting):
    seq='-O3'
    for op in setting:
        if setting[op]:
            seq+=f' {op}'
        else:
            seq+=f' -fno-{op[2:]}'
    return seq

class Dataset():
    def __init__(self,name):
        self.name=name

    def pre_process(self):
        pass

    def compile(self):
        pass


class cBench(Dataset):

    def __init__(self,name,file,cmp_para,ld_para,bin_path):
        self.name=name
        self.db_path=f'{MODULE_DIR}/../output/cbench/{self.name}.db'
        self.path=f'{MODULE_DIR}/../cBench_V1.1/{self.name}/src'
        self.bin_path=bin_path
        self.cmp_para=cmp_para
        self.ld_para=ld_para
        self.file=file
        directory=os.path.dirname(self.db_path)
        if not os.path.exists(directory):
            os.makedirs(directory)
        self.engine = create_engine(f'sqlite:///{self.db_path}', echo=False)
        Base.metadata.create_all(self.engine)
        self.session = sessionmaker(bind=self.engine)()
        self.O3_perf=None

    def prepare(self):
        command=f"""
                cd {self.path};
                make clean;
                ./_ccc_check_output.clean;
                {self.bin_path}/gcc -O3 {self.cmp_para} *.c;
                {self.bin_path}/gcc {self.ld_para} *.o -o a.out;
        """
        cp = subprocess.run(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        eclapse_time=[]

        if cp.returncode==0:
            md5_command = f"md5sum {self.path}/a.out"
            p=subprocess.run(md5_command,shell=True,stdout=subprocess.PIPE)
            md5=get_md5(p.stdout)
            OptionsMd5.add(self.session,'-O3',md5)
            command=f"""
                cd {self.path};
                taskset -c 0 perf stat -- ./__run 1;
            """
            for i in range(3):
                try:
                    p = subprocess.Popen(command, shell=True, stderr=subprocess.PIPE, stdout=subprocess.DEVNULL,preexec_fn=preexec)
                    out, err = p.communicate(timeout=60)
                    stderr=err.decode('utf-8',errors='ignore')
                except subprocess.TimeoutExpired:
                    if psutil.pid_exists(p.pid):
                        os.killpg(os.getpgid(p.pid), signal.SIGKILL)
                    RunError.add(self.session,md5,i,'timeout')
                    print('error: time out')
                    return -1
                if i==0:
                    md5_command = f"md5sum {self.path}/a.out"
                    p2 = subprocess.run(md5_command, shell=True, stdout=subprocess.PIPE)
                    md5 = get_md5(p2.stdout)
                    if p2.returncode != 0 or p.returncode!=0:
                                
                        RunError.add(self.session,md5,i,stderr)
                        print('error: run_command failed')
                        return -1
                    cmd=f"""
                        cd {self.path};
                        ./_ccc_check_output.copy;
                    """
                    subprocess.run(cmd,shell=True)
                index=stderr.find('seconds time elapsed')
                eclapse_time.append(float(stderr[:index].split(' ')[-2]))
            derta=statistics.stdev(eclapse_time)
            eclapse_time=sum(eclapse_time)/len(eclapse_time)

            Md5TestTime.add(self.session,md5,eclapse_time,derta)
            self.O3_perf=eclapse_time

        else:
            CompileError.add(self.session,'',cp.stderr.decode('utf-8'))
            return -1
        return eclapse_time,md5

    def compile(self,options):
        command = f"""cd {self.path};
                make clean;
                {self.bin_path}/gcc -O3 {self.cmp_para} *.c;
                {self.bin_path}/gcc -O3 {options} {self.cmp_para} {self.file};
                {self.bin_path}/gcc {self.ld_para} *.o -o a.out;
                """
        cp = subprocess.run(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        if cp.returncode==0:
            md5_command = f"md5sum {self.path}/a.out"
            p=subprocess.run(md5_command,shell=True,stdout=subprocess.PIPE)
            md5=get_md5(p.stdout)
            if not OptionsMd5.add(self.session,options,md5):
                return md5

            return md5
        else:
            CompileError.add(self.session,options,cp.stderr.decode('utf-8'))
            return -1

    def run(self,md5_bin):
        eclapse_time=[]
        for i in range(3):
            run_commands = f"""cd {self.path};
                taskset -c 0 perf stat -- ./__run 1;
                """
            # numactl --physcpubind=1 --localalloc 
            try:
                p = subprocess.Popen(run_commands, shell=True, stderr=subprocess.PIPE, stdout=subprocess.DEVNULL,preexec_fn=preexec)
                out, err = p.communicate(timeout=60)
                stderr=err.decode('utf-8',errors='ignore')
            except subprocess.TimeoutExpired:
                if psutil.pid_exists(p.pid):
                    os.killpg(os.getpgid(p.pid), signal.SIGKILL)
                RunError.add(self.session,md5_bin,i,'timeout')
                print('error: time out')
                return -1

            if i==0:
                md5_command = f"md5sum {self.path}/a.out"
                p2 = subprocess.run(md5_command, shell=True, stdout=subprocess.PIPE)
                md5 = get_md5(p2.stdout)
                if p2.returncode != 0 or p.returncode!=0:
                    RunError.add(self.session,md5_bin,i,stderr)
                    print('error: run_command failed')
                    return -1
                cmd=f"""
                    cd {self.path};
                    ./_ccc_check_output.diff;
                    cat tmp-ccc-diff;
                """
                p=subprocess.run(cmd,shell=True,stdout=subprocess.PIPE,stderr=subprocess.PIPE)
                if p.stdout.decode('ascii')!='' and self.name!='security_sha' and self.name!='office_rsynth':
                    print('error:output different')
                    WrongOutput.add(self.session,md5_bin,i,md5)
                    return -1
            index=stderr.find('seconds time elapsed')
            eclapse_time.append(float(stderr[:index].split(' ')[-2]))
        derta=statistics.stdev(eclapse_time)
        eclapse_time=sum(eclapse_time)/len(eclapse_time)

        Md5TestTime.add(self.session,md5_bin,eclapse_time,derta)
        return eclapse_time
    

    def evaluate(self,options):
        bin_md5=self.compile(options)
        if bin_md5==-1:
            return -1,-1
        exec_time=Md5TestTime.get_time(self.session,bin_md5)
        if not exec_time:
            status=self.run(bin_md5)
            return status,self.O3_perf/status
        return exec_time,self.O3_perf/exec_time


    def extract_call_graph(self):
        command=f"""
        cd {self.path};
        {self.bin_path}/gcc -O1 -fdump-ipa-inline -S {self.cmp_para} {self.file};
        """
        p=subprocess.run(command,shell=True,stdout=subprocess.DEVNULL,stderr=subprocess.DEVNULL)
        call_graph=gen_call_graph(f'{self.path}/{self.file}.076i.inline')
        clean_command=f"rm -rf {self.path}/{self.file}.076i.inline"
        subprocess.run(clean_command,shell=True,stdout=subprocess.DEVNULL,stderr=subprocess.DEVNULL)
        return call_graph

    def extract_instr_feature(self):
        command=f"""
        cd {self.path};
        clang -O0 -S -emit-llvm {self.cmp_para} {self.file}"""
        p=subprocess.run(command,shell=True,stdout=subprocess.DEVNULL,stderr=subprocess.DEVNULL)
        progVec=gen_vec(f'{self.path}/{self.file[:-2]}.ll')
        clean_command=f"rm -rf {self.path}/{self.file[:-2]}.ll"
        subprocess.run(clean_command,shell=True,stdout=subprocess.DEVNULL,stderr=subprocess.DEVNULL)
        return progVec

    def extract_flow_feature(self):
        graph=gen_flow_graph(f'{self.path}/{self.file}',self.cmp_para)
        return graph

    def gen_feature(self):
        call_graph=self.extract_call_graph()
        instr_feature=self.extract_instr_feature()
        flow_feature=self.extract_flow_feature()
        return {'inline_feature':call_graph,'vec':instr_feature,'loop_feature':flow_feature,'name':self.name}

    def gen_potential_sequence(self):
        with open(f'{MODULE_DIR}/../label/label.json','r') as f:
            label=json.load(f)
        return label

class PolyBench(Dataset):
    def __init__(self,name,path,size,bin_path):
        self.bin_path=bin_path
        self.name=name.split('/')[-1]
        self.db_path=f'{MODULE_DIR}/../output/polybench/{self.name}.db'
        self.pre=path
        self.path=f'{MODULE_DIR}/../PolyBenchC-4.2.1/{path}'
        self.size=size
        directory=os.path.dirname(self.db_path)
        if not os.path.exists(directory):
            os.makedirs(directory)
        self.engine = create_engine(f'sqlite:///{self.db_path}', echo=False)
        Base.metadata.create_all(self.engine)
        self.session = sessionmaker(bind=self.engine)()
        # self.O3_perf,_=self.evaluate('-O3')

        
    def validate(self,options):
        if '-O' not in options:
            options='-O3 '+options
        command = f"""cd {MODULE_DIR}/../PolyBenchC-4.2.1;
                rm -rf a.out;
                rm -rf output.txt;
                {self.bin_path}/gcc {options} -I utilities -I ./{self.pre} utilities/polybench.c ./{self.pre}/{self.name}.c -lm -DPOLYBENCH_DUMP_ARRAYS -D{self.size} -o a.out;
                """
        # print(command)
        cp = subprocess.run(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        if cp.returncode!=0:
            print(cp.stderr)
            print(command)
            return False
        run_commands = f"""cd {MODULE_DIR}/../PolyBenchC-4.2.1;
                ./a.out 2>output.txt;
                """
        # print(run_commands)
        try:
            p = subprocess.Popen(run_commands, shell=True, stderr=subprocess.PIPE, preexec_fn=preexec)
            out, err = p.communicate(timeout=60)
            stderr=err.decode('utf-8',errors='ignore')

        except subprocess.TimeoutExpired:
            if psutil.pid_exists(p.pid):
                os.killpg(os.getpgid(p.pid), signal.SIGKILL)
            return False
        md5_command = f"md5sum {MODULE_DIR}/../PolyBenchC-4.2.1/output.txt"
        # print(md5_command)
        # print(p.return) .
        p2 = subprocess.run(md5_command, shell=True, stdout=subprocess.PIPE)
        md5 = get_md5(p2.stdout)
        if p.returncode!=0:
            print(p.stderr)
        if options=='-O3':
            self.stdout=md5
            return True
        elif md5==self.stdout:
            return True
        return False
        
    def compile(self,options,record):
        if '-O' not in options:
            options='-O3 '+options
        command = f"""cd {MODULE_DIR}/../PolyBenchC-4.2.1;
                rm -rf a.out;
                rm -rf output.txt;
                {self.bin_path}/gcc {options} -I utilities -I ./{self.pre} utilities/polybench.c ./{self.pre}/{self.name}.c -lm -D{self.size} -o a.out;
                """
                # -DPOLYBENCH_DUMP_ARRAYS
        # print(command)
        t=time.time()
        cp = subprocess.run(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        t1=time.time()-t
        if cp.returncode==0:
            md5_command = f"md5sum {MODULE_DIR}/../PolyBenchC-4.2.1/a.out"
            p=subprocess.run(md5_command,shell=True,stdout=subprocess.PIPE)
            md5=get_md5(p.stdout)
            if record:
                if not OptionsMd5.add(self.session,options,md5):
                    print(f'{md5} have existed')
                    return md5,t1

            return md5,t1
        else:
            CompileError.add(self.session,options,cp.stderr.decode('utf-8'))
            return -1,t1

    def clean(self):
        cmd=f"""cd {MODULE_DIR}/../PolyBenchC-4.2.1;
            rm -rf output.txt;
            rm -rf a.out;
        """
        subprocess.run(cmd,shell=True,stderr=subprocess.DEVNULL,stdout=subprocess.DEVNULL)

    def run(self,md5_bin):
        eclapse_time=[]
        derta=[]
        for i in range(1):
            run_commands = f"""cd {MODULE_DIR}/../PolyBenchC-4.2.1;
                perf stat -r 3 -- bash -c './a.out 2>output.txt';
                """
            # print(run_commands)
            try:
                p = subprocess.Popen(run_commands, shell=True, stderr=subprocess.PIPE, preexec_fn=preexec)
                out, err = p.communicate(timeout=20)
                stderr=err.decode('utf-8',errors='ignore')

            except subprocess.TimeoutExpired:
                if psutil.pid_exists(p.pid):
                    os.killpg(os.getpgid(p.pid), signal.SIGKILL)
                RunError.add(self.session,md5_bin,i,'timeout')
                print('error: time out')
                return -1
            # md5_command = f"md5sum {MODULE_DIR}/../dataset/PolyBenchC-4.2.1/output.txt"
            # p2 = subprocess.run(md5_command, shell=True, stdout=subprocess.PIPE)
            # md5 = get_md5(p2.stdout)
            # print(md5)
            if p.returncode!=0:
                        
                RunError.add(self.session,md5_bin,i,stderr)
                print('error: run_command failed')
                return -1
            index=stderr.find('seconds time elapsed')
            derta.append(float(stderr[:index].split(' ')[-2]))
            eclapse_time.append(float(stderr[:index].split(' ')[-4]))
        Md5TestTime.add(self.session,md5_bin,sum(eclapse_time)/len(eclapse_time),derta[0])
        self.clean()
        return sum(eclapse_time)/len(eclapse_time)
    

    def evaluate(self,options):
        if not self.validate(options):
            return -1,-1
        bin_md5,_=self.compile(options,True)
        if bin_md5==-1 or bin_md5==-2:
            return -1,-1
        
        exec_time=Md5TestTime.get_time(self.session,bin_md5)
        if not exec_time:
            status=self.run(bin_md5)
            return status,self.O3_perf/status
        return exec_time,self.O3_perf/exec_time

    def extract_call_graph(self):
        command=f"""
        cd {MODULE_DIR}/../PolyBenchC-4.2.1;
        {self.bin_path}/gcc -O1 -fdump-ipa-inline -S -I utilities -I ./{self.pre} ./{self.pre}/{self.name}.c;
        """
        p=subprocess.run(command,shell=True,stdout=subprocess.DEVNULL,stderr=subprocess.DEVNULL)
        call_graph=gen_call_graph(f'{MODULE_DIR}/../PolyBenchC-4.2.1/{self.name}.c.076i.inline')
        clean_command=f"rm -rf {MODULE_DIR}/../PolyBenchC-4.2.1/{self.name}.c.076i.inline"
        subprocess.run(clean_command,shell=True,stdout=subprocess.DEVNULL,stderr=subprocess.DEVNULL)
        return call_graph

    def extract_instr_feature(self):
        command=f"""
        cd {MODULE_DIR}/../PolyBenchC-4.2.1;
        clang -O0 -S -emit-llvm  -I utilities -I ./{self.pre} ./{self.pre}/{self.name}.c"""
        p=subprocess.run(command,shell=True,stdout=subprocess.DEVNULL,stderr=subprocess.DEVNULL)
        progVec=gen_vec(f'{MODULE_DIR}/../PolyBenchC-4.2.1/{self.name}.ll')
        clean_command=f"rm -rf {MODULE_DIR}/../PolyBenchC-4.2.1/{self.name}.ll"
        subprocess.run(clean_command,shell=True,stdout=subprocess.DEVNULL,stderr=subprocess.DEVNULL)
        return progVec

    def extract_flow_feature(self):
        cmp_para=f'-I {MODULE_DIR}/../PolyBenchC-4.2.1/utilities -I {MODULE_DIR}/../PolyBenchC-4.2.1/{self.pre}'
        graph=gen_flow_graph(f'{MODULE_DIR}/../PolyBenchC-4.2.1/{self.pre}/{self.name}.c',cmp_para)
        return graph