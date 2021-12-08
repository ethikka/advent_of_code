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
1           | 287       | 412       | 571
2           | 261       | 448       | 705
3           | 463       | 731       | 1327
4           | 349       | 479       | 620
5           | 157330    | 171414    | 190035
6           | 38        | 49        | 67
7           | 4448      | 6315      | 10829
8           | 980       | 1177      | 1642
------------+-----------+-----------+--------------
Totals      | 164156    | 181025    | 205796

Total time taken 1810 ms
```