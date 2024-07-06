# DNA Sequence Alignment.

This repository contains the implementation of the DNA sequence alignment problem using dynamic programming. The objective is to obtain a deeper understanding of dynamic programming by solving the DNA sequence alignment problem with specific constraints.

### Objective

- The solution focuses on sequences with the alphabet [A, C, G, T].
- During traceback, ties are broken using the following priority order: match/mismatch, insertion, deletion.

### Specification

- Two sequences are given as input.
- The sequences consist of characters from the alphabet [A, C, G, T].
- The solution must handle traceback with specific tie-breaking priorities.


### Instances

- Ten instances are provided for testing the implementation.
- Each instance includes:
  - `input_[1-10].txt`: Input files containing the sequences.
  - `output_[1-10].txt`: Correct output files with the expected results.

### Compilation and Testing

```bash
g++ -std=c++11 MainTest.cpp -o sequence-alignment

/usr/bin/time -v -o ${Log*File} ./sequence-alignment ${input*[1-10].txt} > ${result\_[1-10].txt}

for i in {1..10}; do /usr/bin/time -v -o "Log*${i}.txt" ./sequence-alignment "./Inputs/input*${i}.txt" > "./result_${i}.txt";done
```
