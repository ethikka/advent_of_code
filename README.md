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
1           | 277       | 319       | 404
2           | 223       | 270       | 425
3           | 424       | 676       | 1800
4           | 311       | 413       | 555
5           | 140284    | 144397    | 152814
6           | 38        | 47        | 76
7           | 3930      | 5134      | 6385
8           | 964       | 1076      | 1422
9           | 63257     | 66323     | 69039
10          | 192       | 231       | 268
11          | 5066      | 5633      | 6487
12          | 1336929   | 1410924   | 1523076
------------+-----------+-----------+--------------
Totals      | 1551895   | 1635443   | 1762751

Total time taken 16354 ms
```