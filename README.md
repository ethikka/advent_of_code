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
1           | 278       | 343       | 833
2           | 220       | 294       | 722
3           | 426       | 697       | 1126
4           | 308       | 456       | 1186
5           | 45527     | 47742     | 51433
6           | 35        | 148       | 1001
7           | 4204      | 5124      | 6421
8           | 993       | 1205      | 1897
9           | 62522     | 65953     | 69290
10          | 191       | 274       | 786
11          | 5121      | 5626      | 6678
12          | 97149     | 101835    | 115967
13          | 962       | 1119      | 1417
14          | 736       | 955       | 1745
15          | 1819522   | 2099453   | 2262784
16          | 248       | 373       | 590
17          | 284       | 430       | 825
18          | 34753     | 39685     | 46963
19          | 0         | 1         | 2
20          | 7094479   | 7865665   | 8507703
21          | 237470    | 262919    | 296920
22          | 4044      | 4908      | 6350
23          | no code   |           |
24          | 72        | 160       | 521
25          | 861942    | 972236    | 1109211
------------+-----------+-----------+--------------
Totals      | 10271486  | 11477601  | 12492373

Total time taken 114776 ms
```

