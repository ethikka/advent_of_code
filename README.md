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
1           | 285       | 396       | 534
2           | 221       | 300       | 461
3           | 416       | 521       | 786
4           | 317       | 424       | 521
5           | 153594    | 161815    | 182725
6           | 38        | 56        | 92
7           | 4908      | 5455      | 6603
8           | 1152      | 1642      | 2359
9           | 64751     | 70197     | 79290
10          | 193       | 268       | 386
------------+-----------+-----------+--------------
Totals      | 225875    | 241074    | 273757

Total time taken 2410 ms
```