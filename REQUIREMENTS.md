# Requirements
## Hardware
### Raspberry Pi
- Do we need some sort of power supply
- SSD or SD card?
- How to keep cool
- How long can we keep the Pi for?

### RISC-V Board
- Will try ARM stuff first to get an idea before asking for RISC-V boards
- What boards are they (for specs)

### x86 Machine
- We all have x86 machines
- But for standardisation is there a server we can use  for testing?

## Benchmarks

I would say our main focus would be on PolyBench and cBench. Already come with the repo (kinda) and are small enough to stay in scope.

### PolyBench
- We can use this, small set of 30 programs, used in the paper
- These are single file
- Not in repo
### cBench
- We can also use this and main.py runs some of these by default
- Programs can be multiple files, only the "hot" files get predicted flags, all other files are run with -O3.
- In repo
### SPEC CPU2017
- We need a license for this, university may have one?
### Redis
- Also used by the paper, more of a focus on database accesses etc.

## Software
### Compilers
- GCC 9.2\*\*\*, and appropiate cross compilers for ARM and RISC-V
- clang16 for IR2Vec 2.1.1
- clang10 for ProGraML
- clang is needed to convert code into LLVM for prediction

### Measurements
- perf averaged over 5 runs on actual paper
- also a check of output against -03 output
- \*\*\*they also test on newer GCCs in section 7.1, GCC 11.5 and GCC 13.1. Improvement decreases as GCC version increases. 

## Concerns
- The paper has a LLM step (using QWEN) to narrow down some flags. This step isn't in the repo.
- They only kept program in their benchmark where the theoretical improvement was atleast 2%. It could be the case that there is no improvement to be made for an ARM device anyway on some benchmarks - should check this if any results seem particularly poor. 