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
Running each day 10 times

Day         | Best (µs) | Avg (µs)  | Worst (µs)
------------+-----------+-----------+--------------
1           | 546       | 742       | 1050
2           | 767       | 995       | 1582
------------+-----------+-----------+--------------
Totals      | 1313      | 1737      | 2632

Total time taken 17 ms
```