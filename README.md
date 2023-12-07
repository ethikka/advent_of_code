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
1           | 1228      | 1371      | 1857
2           | 247       | 265       | 298
3           | 2151      | 2371      | 2864
4           | 671       | 698       | 740
6           | 12226     | 12501     | 12861
7           | 1146      | 1197      | 1315
------------+-----------+-----------+--------------
Totals      | 17669     | 18403     | 19935

Total time taken 184 ms
```