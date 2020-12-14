- install itertools (https://github.com/ryanhaining/cppitertools)
- create buildoutput directory

Run year day once
- ./run_once.sh <year> <day>

Build and run <year> <day> if the binary is older then the sourcefile, and wait for changes
- ./run.sh <year> <day>


---
```
Running each day 100 times

        Day     | 1     | 2     | 3     | 4     | 5     | 6     | 7     | 8     | 9     | 10    | 11     | 12    | 13    | 14    | 15    | 16    | 17    | 18    | 19    | 20    | 21    | 22    | 23    | 24    | 25    | Totals (µs)
----------------|-------|-------+-------+-------+-------+-------+-------+-------+-------+-------+--------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+--------------
Best (µs)       | 1561  | 440   | 658   | 874   | 462   | 1017  | 1984  | 2964  | 457   | 38    | 60073  | 99    | 21    | 14147 |       |       |       |       |       |       |       |       |       |       |       | 84795
Avg (µs)        | 1775  | 523   | 744   | 1037  | 554   | 1178  | 2303  | 3571  | 550   | 50    | 67470  | 121   | 28    | 17028 |       |       |       |       |       |       |       |       |       |       |       | 96932
Worst (µs)      | 2384  | 810   | 1052  | 1667  | 876   | 2203  | 3774  | 4287  | 1111  | 161   | 110916 | 220   | 76    | 25867 |       |       |       |       |       |       |       |       |       |       |       | 155404
----------------|-------|-------+-------+-------+-------+-------+-------+-------+-------+-------+--------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+--------------

Total time taken 9693 ms
```