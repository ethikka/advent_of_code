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
1           | 281       | 317       | 375
2           | 222       | 251       | 363
3           | 412       | 543       | 1079
4           | 393       | 510       | 816
5           | 49709     | 51153     | 54055
6           | 41        | 59        | 117
7           | 3996      | 5071      | 7549
8           | 975       | 1258      | 1996
9           | 62755     | 71539     | 90909
10          | 220       | 316       | 441
11          | 5175      | 5809      | 7249
12          | 107119    | 119549    | 129742
13          | 967       | 1146      | 1622
14          | 761       | 1003      | 1534
------------+-----------+-----------+--------------
Totals      | 233026    | 258524    | 297847

Total time taken 2585 ms
```

