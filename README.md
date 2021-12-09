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
1           | 283       | 303       | 371
2           | 226       | 274       | 494
3           | 419       | 656       | 1009
4           | 352       | 474       | 674
5           | 156169    | 165991    | 175737
6           | 39        | 55        | 74
7           | 4238      | 5032      | 6723
8           | 977       | 1345      | 2426
9           | 63745     | 68614     | 74808
------------+-----------+-----------+--------------
Totals      | 226448    | 242744    | 262316

Total time taken 2427 ms
```