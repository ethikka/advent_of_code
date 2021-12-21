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
1           | 279       | 319       | 491
2           | 223       | 236       | 274
3           | 406       | 506       | 876
4           | 314       | 463       | 641
5           | 44856     | 46635     | 49984
6           | 36        | 59        | 109
7           | 3845      | 6659      | 21067
8           | 948       | 1094      | 1547
9           | 62977     | 68464     | 78361
10          | 196       | 281       | 360
11          | 5136      | 5753      | 7144
12          | 105139    | 116245    | 131436
13          | 957       | 1084      | 1646
14          | 727       | 925       | 1520
15          | 1838876   | 1997329   | 2325395
16          | 156       | 232       | 328
17          | 268       | 321       | 450
18          | 269       | 300       | 432       * only part a
21          | 246369    | 273081    | 310059
------------+-----------+-----------+--------------
Totals      | 2311977   | 2519986   | 2932122

Total time taken 25199 ms
```

