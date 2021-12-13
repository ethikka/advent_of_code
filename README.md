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
1           | 277       | 337       | 421
2           | 223       | 258       | 333
3           | 420       | 518       | 724
4           | 317       | 424       | 676
5           | 149250    | 163147    | 185638
6           | 36        | 46        | 102
7           | 3988      | 5374      | 9082
8           | 988       | 1293      | 2164
9           | 61948     | 69459     | 78990
10          | 191       | 249       | 396
11          | 5104      | 5876      | 6978
12          | 1400250   | 1463243   | 1704353
13          | 968       | 1166      | 1853
------------+-----------+-----------+--------------
Totals      | 1623960   | 1711390   | 1991710

Total time taken 17113 ms
```