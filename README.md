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

        Day     | 1     | 2     | 3     | 4     | 5     | 6     | 7     | 8     | 9     | 10    | 11    | 12    | 13    | 14    | 15      | 16    | 17    | 18    | 19    | 20    | 21    | 22     | 23    | 24    | 25    | Totals (µs)
----------------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+---------+-------+-------+-------+-------+-------+-------+--------+-------+-------+-------+--------------
Best (µs)       | 1547  | 446   | 730   | 931   | 466   | 1117  | 2121  | 3282  | 494   | 39    | 66178 | 104   | 21    | 16397 | 929967  | 7788  | 22752 | 1529  | 60230 | 601   | 955   | 271958 |       |       |       | 1389653
Avg (µs)        | 1709  | 606   | 854   | 1173  | 666   | 1213  | 2821  | 3810  | 586   | 58    | 70375 | 141   | 26    | 19514 | 967475  | 9308  | 25900 | 1905  | 63665 | 809   | 1151  | 279310 |       |       |       | 1453075
Worst (µs)      | 2011  | 785   | 985   | 1948  | 1135  | 1418  | 3610  | 4724  | 641   | 117   | 77766 | 175   | 45    | 21925 | 1036722 | 10934 | 33071 | 3315  | 70480 | 1027  | 1641  | 287635 |       |       |       | 1562110
----------------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+---------+-------+-------+-------+-------+-------+-------+--------+-------+-------+-------+--------------

Total time taken 14530 ms
```