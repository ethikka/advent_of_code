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
1           | 280       | 341       | 404
2           | 223       | 268       | 465
3           | 423       | 658       | 1239
4           | 315       | 498       | 655
5           | 46916     | 49451     | 53365
6           | 36        | 42        | 77
7           | 4015      | 4576      | 5542
8           | 1027      | 1286      | 1905
9           | 61497     | 67631     | 81842
10          | 204       | 235       | 288
11          | 5217      | 5833      | 7012
12          | 100532    | 110777    | 124465
13          | 1019      | 1226      | 1608
14          | 765       | 1159      | 2104
15          | 1973747   | 2005467   | 2093081
16          | 161       | 205       | 343
17          | 269       | 328       | 383
18          | 272       | 342       | 433        * part 1 only
21          | 242336    | 250982    | 263175
22          | 3816      | 4456      | 5672
------------+-----------+-----------+--------------
Totals      | 2443070   | 2505761   | 2644062

Total time taken 25057 ms


Total time taken 25199 ms
```

