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

        Day     | 1    | 2   | 3     | 4    | 5   | 6    | 7    | 8    | 9   | 10 | 11    | 12  | 13 | 14    | 15     | 16    | 17    | 18   | 19    | 20  | 21   | 22     | 23      | 24 | 25 | Totals (µs)
----------------+------+-----+-------+------+-----+------+------+------+-----+----+-------+-----+----+-------+--------+-------+-------+------+-------+-----+------+--------+---------+----+----+--------------
Best (µs)       | 1627 | 490 | 662   | 925  | 480 | 1091 | 2113 | 3326 | 459 | 40 | 64299 | 105 | 22 | 16133 | 899378 | 7220  | 23694 | 1460 | 60911 | 594 | 974  | 264942 | 1601293 |    |    | 2952238
Avg (µs)        | 1798 | 586 | 768   | 1277 | 613 | 1338 | 3196 | 3767 | 565 | 50 | 68894 | 156 | 29 | 18421 | 922323 | 8673  | 26320 | 1806 | 66881 | 688 | 1291 | 278167 | 1646000 |    |    | 3053607
Worst (µs)      | 2099 | 911 | 1052  | 2205 | 733 | 2016 | 5906 | 4334 | 702 | 89 | 74606 | 270 | 58 | 20773 | 965436 | 11686 | 33972 | 2296 | 91832 | 891 | 1850 | 301180 | 1688026 |    |    | 3212923
----------------+------+-----+-------+------+-----+------+------+------+-----+----+-------+-----+----+-------+--------+-------+-------+------+-------+-----+------+--------+---------+----+----+--------------

Total time taken 30536 ms
```