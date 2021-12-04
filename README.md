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
1           | 278       | 312       | 408
2           | 223       | 291       | 574
3           | 417       | 522       | 1058
4           | 316       | 468       | 667
------------+-----------+-----------+--------------
Totals      | 1234      | 1593      | 2707

Total time taken 15 ms
```