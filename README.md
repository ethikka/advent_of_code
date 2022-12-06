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
1           | 208       | 297       | 586
2           | 208       | 280       | 605
3           | 671       | 863       | 1314
4           | 447       | 564       | 1132
5           | 328       | 401       | 616
6           | 1297      | 1533      | 2101
------------+-----------+-----------+--------------
Totals      | 3159      | 3938      | 6354

Total time taken 39 ms
```

