# PredComp

PredComp is a static prediction framework to directly predict desired option sequence for programs to improve their execution time.

# Structure

```
|- Dataset/                         # Dataset and their implement
    |- cBench_V1.1                  # cBench Dataset
    |- PolybenchC-4.2.1             # Polybench Dataset
    |- train_dataset                # Source code, program feature and label of training dataset
    |- process                      # Scripts to evaluate the performance of option sequences
    |- output                       # Store evaluation results
|- Inference/                       # Inference scripts to implement prediction
|- saved_model/                     # Stored the trained models obtained from the training phase
|- util/                            # Utilities functions to generate option sequence and construct dataset
|- main.py                          # Predict desired option sequences of cbench
 
```

# Prerequisites
```
conda create -n predcomp python=3.9.21
conda activate predcomp
cd predcomp
pip install -r requirements.txt
export PYTHONPATH=$(dirname "$PWD"):$PYTHONPATH
```

# Running predcomp

main.py shows an example of predicting the desired option sequence for cBench programs and execute the corresponding sequence to validate the performance improvement.

```
python3 main.py --bin_path=/path/to/gcc
```

