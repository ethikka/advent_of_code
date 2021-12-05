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
1           | 278       | 327       | 475
2           | 224       | 273       | 362
3           | 427       | 593       | 1213
4           | 312       | 468       | 698
5           | 141341    | 144286    | 150137
------------+-----------+-----------+--------------
Totals      | 142582    | 145947    | 152885

Total time taken 1459 ms
```