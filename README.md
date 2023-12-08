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
wartoy@holly:~/src/advent_of_code$ ./time_all.sh

Running each day 10 times

Day         | Best (µs) | Avg (µs)  | Worst (µs)
------------+-----------+-----------+--------------
1           | 1215      | 1244      | 1296
2           | 241       | 246       | 252
3           | 2129      | 2282      | 2398
5           | 10903     | 11433     | 11982
6           | 11499     | 11815     | 12327
7           | 966       | 993       | 1047
8           | 10514     | 10735     | 11285
------------+-----------+-----------+--------------
Totals      | 37467     | 38748     | 40587

Total time taken 387 ms
```