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

        Day     | 1     | 2     | 3     | 4     | 5     | 6     | 7     | 8     | 9     | 10    | 11    | 12    | 13    | 14    | 15     | 16    | 17    | 18    | 19    | 20    | 21    | 22    | 23    | 24    | 25    | Totals (µs)
----------------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+--------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+--------------
Best (µs)       | 1671  | 478   | 674   | 885   | 489   | 1027  | 2062  | 3252  | 462   | 41    | 62415 | 101   | 26    | 14455 | 797522 | 6638  | 21790 | 1489  | 47250 |       |       |       |       |       |       | 962727
Avg (µs)        | 1821  | 579   | 865   | 1032  | 539   | 1235  | 2376  | 3481  | 627   | 48    | 66814 | 139   | 37    | 16377 | 870979 | 7291  | 25176 | 1872  | 50300 |       |       |       |       |       |       | 1051588
Worst (µs)      | 2094  | 749   | 1255  | 1483  | 607   | 1503  | 2764  | 3703  | 842   | 79    | 73430 | 229   | 52    | 20357 | 942594 | 7981  | 30027 | 2520  | 56504 |       |       |       |       |       |       | 1148773
----------------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+--------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+--------------

Total time taken 10515 ms
```