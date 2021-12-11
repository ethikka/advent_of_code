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
1           | 281       | 348       | 613
2           | 226       | 295       | 565
3           | 413       | 653       | 1062
4           | 312       | 428       | 680
5           | 145792    | 159887    | 187151
6           | 41        | 76        | 134
7           | 4156      | 5502      | 7902
8           | 1060      | 1326      | 1892
9           | 65584     | 71200     | 76719
10          | 193       | 221       | 327
11          | 5156      | 5604      | 6123
------------+-----------+-----------+--------------
Totals      | 223214    | 245540    | 283168

Total time taken 2455 ms
```