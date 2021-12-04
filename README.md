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
1           | 278       | 306       | 348
2           | 223       | 254       | 352
3           | 413       | 516       | 1016
4           | 312       | 437       | 633
------------+-----------+-----------+--------------
Totals      | 1226      | 1513      | 2349

Total time taken 15 ms
```