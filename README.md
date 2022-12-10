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
1           | 215       | 269       | 370
2           | 210       | 275       | 340
3           | 661       | 768       | 1001
4           | 447       | 528       | 631
5           | 325       | 399       | 632
6           | 431       | 508       | 743
7           | 235       | 272       | 351
8           | 568       | 667       | 820
9           | 4207      | 4813      | 5528
10          | 61        | 74        | 176
------------+-----------+-----------+--------------
Totals      | 7360      | 8573      | 10592

Total time taken 85 ms
```

