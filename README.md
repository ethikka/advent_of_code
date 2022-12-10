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
1           | 207       | 276       | 485
2           | 206       | 248       | 347
3           | 670       | 864       | 1252
4           | 462       | 573       | 696
5           | 326       | 403       | 624
6           | 433       | 579       | 1107
7           | 238       | 284       | 385
8           | 586       | 670       | 911
9           | 2608      | 2852      | 3412
10          | 82        | 120       | 283
------------+-----------+-----------+--------------
Totals      | 5818      | 6869      | 9502

Total time taken 68 ms
```

