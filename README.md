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
1           | 207       | 331       | 507
2           | 207       | 243       | 318
3           | 656       | 849       | 1243
4           | 445       | 599       | 1046
5           | 329       | 402       | 672
6           | 431       | 505       | 751
7           | 234       | 303       | 438
8           | 571       | 652       | 795
9           | 2556      | 2895      | 3430
10          | 82        | 99        | 120
11          | 6723      | 7475      | 8920
12          | 243       | 316       | 408
13          | 2566      | 2905      | 3862
------------+-----------+-----------+--------------
Totals      | 15250     | 17574     | 22510

Total time taken 175 ms
```

