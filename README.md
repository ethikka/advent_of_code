- install itertools (https://github.com/ryanhaining/cppitertools)
- create buildoutput directory

Run year day once
- ./run_once.sh <year> <day>

Build and run <year> <day> if the binary is older then the sourcefile, and wait for changes
- ./run.sh <year> <day>


---
```
wartoy@MU-TH-R-182:~/src/advent_of_code$ ./time_all.sh 

Day         | Best (µs) | Avg (µs)  | Worst (µs)
------------+-----------+-----------+--------------
1           | 281       | 378       | 828
2           | 226       | 264       | 384
3           | 440       | 609       | 942
4           | 327       | 542       | 823
5           | 48605     | 54915     | 74920
6           | 40        | 76        | 253
7           | 4934      | 7516      | 11526
8           | 1109      | 1684      | 2301
9           | 69459     | 82554     | 122066
10          | 202       | 280       | 520
11          | 5227      | 7063      | 8916
12          | 145139    | 173871    | 229533
13          | 1040      | 1417      | 2328
14          | 762       | 1343      | 2770
15          | 2017044   | 2321750   | 2561235
16          | 161       | 223       | 326
17          | 288       | 365       | 542
------------+-----------+-----------+--------------
Totals      | 2295284   | 2654850   | 3020213

Total time taken 26548 ms
```

