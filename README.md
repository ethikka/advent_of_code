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
1           | 1231      | 1264      | 1312
2           | 243       | 251       | 258
3           | 2223      | 2278      | 2360
5           | 11169     | 11567     | 12592
6           | 11526     | 11728     | 12121
------------+-----------+-----------+--------------
Totals      | 26392     | 27088     | 28643

Total time taken 270 ms
```