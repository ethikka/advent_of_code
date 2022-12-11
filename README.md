- install itertools (https://github.com/ryanhaining/cppitertools)
- create buildoutput directory

Run year day once
- ./run_once.sh <year> <day>

Build and run <year> <day> if the binary is older then the sourcefile, and wait for changes
- ./run.sh <year> <day>


---
```
wartoy@MU-TH-R-182:~/src/advent_of_code$ ./time_all.sh 

Running each day 1000 times

Day         | Best (µs) | Avg (µs)  | Worst (µs)
------------+-----------+-----------+--------------
1           | 203       | 233       | 560
2           | 204       | 251       | 1004
3           | 654       | 727       | 1611
4           | 441       | 484       | 819
5           | 323       | 354       | 553
6           | 426       | 480       | 1216
7           | 232       | 264       | 780
8           | 563       | 616       | 1241
9           | 2494      | 2774      | 7290
10          | 82        | 94        | 443
11          | 6893      | 7523      | 20611
------------+-----------+-----------+--------------
Totals      | 12515     | 13800     | 36128

Total time taken 13804 ms
```

