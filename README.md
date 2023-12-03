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
1           | 1152      | 1272      | 1583
2           | 244       | 250       | 258
3           | 2207      | 2287      | 2501
------------+-----------+-----------+--------------
Totals      | 3603      | 3809      | 4342

Total time taken 38 ms
```