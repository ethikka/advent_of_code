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
1           | 279       | 357       | 476
2           | 222       | 280       | 460
3           | 420       | 646       | 1261
4           | 389       | 491       | 684
5           | 49110     | 52091     | 60052
6           | 42        | 66        | 107
7           | 4386      | 6308      | 12119
8           | 999       | 1375      | 2272
9           | 66210     | 70122     | 73632
10          | 192       | 247       | 424
11          | 5216      | 6061      | 8359
12          | 107504    | 114489    | 123827
13          | 984       | 1156      | 1638
14          | 826       | 958       | 1311
15          | 2006056   | 2178541   | 2525285
16          | 154       | 180       | 256
17          | 268       | 331       | 435
18          | 36502     | 41509     | 45344
19          |           |           |  
20          |           |           |  
21          | 258567    | 275227    | 298102
22          | 3939      | 4619      | 6427
------------+-----------+-----------+--------------
Totals      | 2542265   | 2755055   | 3162475

Total time taken 27550 ms
```

