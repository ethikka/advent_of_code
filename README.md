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
1           | 281       | 350       | 677
2           | 226       | 294       | 417
3           | 417       | 597       | 1724
4           | 311       | 442       | 701
5           | 50463     | 52809     | 58133
6           | 39        | 53        | 90
7           | 3952      | 5764      | 10518
8           | 955       | 1281      | 2081
9           | 64155     | 70148     | 79686
10          | 220       | 314       | 392
11          | 5466      | 7249      | 10214
12          | 114752    | 131408    | 183474
13          | 976       | 1244      | 2122
14          | 754       | 1057      | 1790
15          | 6578592   | 6895000   | 7387778
------------+-----------+-----------+--------------
Totals      | 6821559   | 7168010   | 7739797

Total time taken 71680 ms
```

