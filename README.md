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
Best (µs)       | 1620  | 448   | 701   | 912   | 466   | 1021  | 2075  | 3354  | 494   | 42    | 63595 | 100   | 22    | 15076 | 871562  | 6803  | 22178 | 1448  | 60471 | 598   |       |       |       |       |       | 1052986
Avg (µs)        | 1897  | 564   | 839   | 1108  | 547   | 1136  | 2427  | 3814  | 566   | 61    | 66744 | 124   | 32    | 16480 | 945775  | 8618  | 25582 | 1665  | 68693 | 775   |       |       |       |       |       | 1147447
Worst (µs)      | 2242  | 804   | 1180  | 1724  | 661   | 1281  | 3025  | 4438  | 803   | 91    | 76087 | 204   | 59    | 18772 | 1002880 | 11641 | 32146 | 2109  | 75954 | 959   |       |       |       |       |       | 1237060
----------------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+---------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+--------------
```