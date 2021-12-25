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
1           | 278       | 326       | 454
2           | 223       | 256       | 334
3           | 421       | 617       | 1102
4           | 321       | 451       | 549
5           | 46520     | 47886     | 52006
6           | 39        | 49        | 73
7           | 4420      | 5287      | 7179
8           | 1054      | 1352      | 2036
9           | 60992     | 64695     | 67889
10          | 193       | 236       | 309
11          | 5164      | 5410      | 6251
12          | 100984    | 103713    | 107267
13          | 944       | 1106      | 1628
14          | 753       | 977       | 2045
15          | 1824632   | 1931978   | 2134529
16          | 160       | 243       | 449
17          | 275       | 314       | 382
18          | 33784     | 36033     | 39928
21          | 238421    | 255962    | 272793
22          | 3943      | 4709      | 5849
23          | no code   |           |
24          | 75        | 109       | 159
25          | 876003    | 908824    | 940705
------------+-----------+-----------+--------------
Totals      | 3199600   | 3370533   | 3643921

Total time taken 33705 ms
```

