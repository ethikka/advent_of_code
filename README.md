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
1           | 206       | 305       | 520
2           | 206       | 264       | 367
3           | 718       | 880       | 1396
4           | 447       | 575       | 727
5           | 331       | 419       | 540
6           | 1364      | 1693      | 2396
7           | 240       | 306       | 507
8           | 585       | 723       | 1115
9           | 4366      | 4922      | 5645
------------+-----------+-----------+--------------
Totals      | 8463      | 10087     | 13213

Total time taken 100 ms
```

