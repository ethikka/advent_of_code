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
1           | 286       | 324       | 448
2           | 221       | 334       | 821
3           | 415       | 634       | 1413
4           | 318       | 459       | 613
5           | 48967     | 51972     | 57380
6           | 37        | 50        | 84
7           | 4437      | 5745      | 8993
8           | 997       | 1235      | 1772
9           | 63274     | 69686     | 81482
10          | 193       | 242       | 414
11          | 5269      | 5771      | 6782
12          | 108842    | 118850    | 151936
13          | 970       | 1137      | 1361
14          | 804       | 996       | 1369
15          | 2082403   | 2118181   | 2189153
------------+-----------+-----------+--------------
Totals      | 2317433   | 2375616   | 2504021

Total time taken 23756 ms
```

