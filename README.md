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
1           | 1156      | 1228      | 1249
2           | 244       | 249       | 259
3           | 2219      | 2274      | 2382
5           | 11388     | 11765     | 12356
------------+-----------+-----------+--------------
Totals      | 15007     | 15516     | 16246

Total time taken 155 ms
```