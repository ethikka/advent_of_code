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
1           | 282       | 305       | 356
2           | 243       | 289       | 374
3           | 423       | 529       | 724
4           | 348       | 502       | 795
5           | 50450     | 53259     | 56527
6           | 38        | 50        | 124
7           | 4300      | 5613      | 9709
8           | 993       | 1259      | 2040
9           | 68470     | 78511     | 85895
10          | 217       | 298       | 495
11          | 6365      | 9846      | 24564
12          | 112306    | 118795    | 137284
13          | 1005      | 1224      | 1529
14          | 728       | 821       | 961
15          | 2071900   | 2262657   | 2572843
16          | 182       | 296       | 408
------------+-----------+-----------+--------------
Totals      | 2318250   | 2534254   | 2894628

Total time taken 25342 ms
```

