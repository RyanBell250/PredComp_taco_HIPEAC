# Overview

To get the program to run properly, some things had to be changed. Below is a list of every fix made and why.

## Fixes
- Use Python 3.10 as networkx3.4.2 needs python 3.10+ and IR2Vec2.1.1 only has builds up to 3.11
- Repo folder must be named "PredComp" due to how the scripts import the modules
- Some packages were not listed in requirements and some at the wrong versions, the requirements.txt file has been updated to reflect this
- programl package was importing DGLHeterograph incorrectly, code had to be changed
- clang2graph-10 needs libtinfo5, newer versions of Ubuntu do not have this, so had to be installed from Ubuntu 22.04 archive.
- changed permissions on all cBench files so they could be executable (chmod +x)
- bin_path was hardcoded in the main.py and had to be changed
- the inline dump name being used in heads.py is GCC specific, was changed to allow different versions of GCC


## How to run
This is how I got it to run on my linux machine with Ubuntu 24.04. No need to worry about python packages and chmod as those changes have been uploaded to the git.

```bash
# 1. System packages
sudo apt install build-essential linux-tools-common linux-tools-$(uname -r)
sudo sysctl kernel.perf_event_paranoid=1

# Ubuntu 24.04+ only
wget http://archive.ubuntu.com/ubuntu/pool/universe/n/ncurses/libtinfo5_6.3-2ubuntu0.3_amd64.deb
sudo apt install ./libtinfo5_6.3-2ubuntu0.3_amd64.deb

```
2 - Make sure to rename the repo folder to "PredComp"

```bash
# 3. Python env
conda create -n predcomp python=3.10 -y
conda activate predcomp
python -m pip install -r requirements.txt

# 4. Patch programl (old DGL API)
sed -i 's/from dgl.heterograph import DGLHeteroGraph/from dgl import DGLGraph as DGLHeteroGraph/' \
  $(grep -rl "DGLHeteroGraph" "$(python -c 'import programl,os;print(os.path.dirname(programl.__file__))')")

# 5. Run, from inside PredComp/
export PYTHONPATH="$(dirname "$PWD"):$PYTHONPATH"
python3 main.py --bin_path=/usr/bin
```