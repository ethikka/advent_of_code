- install itertools (https://github.com/ryanhaining/cppitertools)
- create buildoutput directory

Run year day once
- ./run_once.sh <year> <day>

Build and run <year> <day> if the binary is older then the sourcefile, and wait for changes
- ./run.sh <year> <day>


---
```
wartoy@MU-TH-R-182:~/src/advent_of_code$ ./time_all.sh 

Running each day 10 times

Day         | Best (µs) | Avg (µs)  | Worst (µs)
------------+-----------+-----------+--------------
1           | 207       | 267       | 431
2           | 208       | 239       | 286
3           | 667       | 830       | 1114
4           | 456       | 537       | 781
------------+-----------+-----------+--------------
Totals      | 1538      | 1873      | 2612

Total time taken 18 ms
```

