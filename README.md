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
1           | 277       | 309       | 423
2           | 222       | 254       | 348
3           | 413       | 461       | 564
4           | 314       | 486       | 672
5           | 140785    | 147605    | 166369
6           | 38        | 56        | 99
------------+-----------+-----------+--------------
Totals      | 142049    | 149171    | 168475

Total time taken 1491 ms
```