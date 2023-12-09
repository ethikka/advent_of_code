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
1           | 1129      | 1257      | 1402
2           | 246       | 276       | 420
3           | 2230      | 2318      | 2504
5           | 11219     | 11677     | 12231
6           | 11691     | 12337     | 13757
7           | 980       | 1052      | 1341
8           | 10705     | 10929     | 11316
9           | 540       | 571       | 681
------------+-----------+-----------+--------------
Totals      | 38740     | 40417     | 43652

Total time taken 404 ms
```