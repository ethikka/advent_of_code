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
1           | 280       | 313       | 394
2           | 221       | 254       | 396
3           | 414       | 535       | 849
4           | 311       | 477       | 619
5           | 143600    | 152247    | 159158
6           | 43        | 60        | 104
------------+-----------+-----------+--------------
Totals      | 144869    | 153886    | 161520

Total time taken 1538 ms
```