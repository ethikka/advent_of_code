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
1           | 1254      | 1332      | 1421
2           | 264       | 272       | 298
3           | 2254      | 2373      | 2518
4           | 696       | 725       | 784
------------+-----------+-----------+--------------
Totals      | 4468      | 4702      | 5021

Total time taken 47 ms
```