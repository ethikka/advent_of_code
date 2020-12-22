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

        Day     | 1     | 2     | 3     | 4     | 5     | 6     | 7     | 8     | 9     | 10    | 11    | 12    | 13    | 14    | 15      | 16    | 17    | 18    | 19    | 20    | 21    | 22      | 23    | 24    | 25    | Totals (µs)
----------------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+---------+-------+-------+-------+-------+-------+-------+---------+-------+-------+-------+--------------
Best (µs)       | 1596  | 447   | 706   | 925   | 463   | 1047  | 2077  | 3095  | 479   | 44    | 64135 | 102   | 26    | 15789 | 887910  | 7045  | 22079 | 1448  | 59600 | 619   | 902   | 1805928 |       |       |       | 2876462
Avg (µs)        | 1825  | 539   | 766   | 1118  | 569   | 1164  | 2455  | 3677  | 569   | 67    | 67444 | 140   | 35    | 18449 | 1000782 | 8106  | 27366 | 1747  | 62793 | 739   | 1025  | 1942974 |       |       |       | 3144349
Worst (µs)      | 2118  | 654   | 869   | 1372  | 691   | 1356  | 2764  | 5404  | 741   | 119   | 74540 | 274   | 55    | 22776 | 1111777 | 9430  | 34553 | 2029  | 67954 | 964   | 1164  | 2075277 |       |       |       | 3416881
----------------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+---------+-------+-------+-------+-------+-------+-------+---------+-------+-------+-------+--------------

Total time taken 31443 ms
```