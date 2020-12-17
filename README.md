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

        Day     | 1     | 2     | 3     | 4     | 5     | 6     | 7     | 8     | 9     | 10    | 11    | 12    | 13    | 14    | 15      | 16    | 17    | 18    | 19    | 20    | 21    | 22    | 23    | 24    | 25    | Totals (µs)
----------------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+---------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+--------------
Best (µs)       | 1591  | 445   | 727   | 926   | 467   | 1073  | 2201  | 3088  | 459   | 43    | 63660 | 100   | 25    | 15561 | 864465  | 7458  | 22705 |       |       |       |       |       |       |       |       | 984994
Avg (µs)        | 1830  | 505   | 985   | 1111  | 547   | 1216  | 2411  | 3831  | 532   | 60    | 68549 | 125   | 28    | 18793 | 935450  | 8117  | 27788 |       |       |       |       |       |       |       |       | 1071878
Worst (µs)      | 2420  | 683   | 1456  | 1338  | 736   | 1686  | 2720  | 5118  | 647   | 79    | 72939 | 170   | 35    | 24201 | 1003780 | 9987  | 37308 |       |       |       |       |       |       |       |       | 1165303
----------------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+---------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+--------------

Total time taken 10718 ms
```