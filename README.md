- create buildoutput directory

Year and day in the following commands default to today, omit them if you need to run them today

Build (if needed) and run once
- ./run_once.sh <year> <day>

Build (if needed) and run <year> <day> if the binary is older then the sourcefile, and wait for changes
- ./run.sh <year> <day>

Run each (built) day 10 times and generate a table of best, worst and average runtimes
- ./time_all.sh <year>

---
```
~/src/advent_of_code> ./time_all.sh

Running each day 10 times

Day         | Best (µs) | Avg (µs)  | Worst (µs)
------------+-----------+-----------+--------------
1           | 1206      | 1263      | 1322
2           | 246       | 254       | 264
3           | 2192      | 2295      | 2552
4           | 674       | 725       | 856
5           | 11512     | 11967     | 12445
6           | 12025     | 12171     | 12318
7           | 1025      | 1116      | 1702
8           | 11065     | 11400     | 12641
9           | 599       | 622       | 748
10          | 9919      | 10173     | 10710
11          | 75352     | 76869     | 78528
------------+-----------+-----------+--------------
Totals      | 125815    | 128855    | 134086

Total time taken 1288 ms
```