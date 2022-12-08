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
1           | 209       | 275       | 383
2           | 207       | 236       | 331
3           | 1558      | 1992      | 2904
4           | 444       | 496       | 563
5           | 367       | 534       | 988
6           | 1392      | 1571      | 2180
8           | 666       | 791       | 1094
------------+-----------+-----------+--------------
Totals      | 4843      | 5895      | 8443

Total time taken 58 ms
```

