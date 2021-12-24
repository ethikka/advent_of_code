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
1           | 283       | 381       | 871
2           | 226       | 318       | 528
3           | 414       | 661       | 1845
4           | 346       | 474       | 590
5           | 49892     | 54780     | 68278
6           | 39        | 60        | 147
7           | 4027      | 4906      | 5749
8           | 982       | 1128      | 1313
9           | 62496     | 65460     | 71392
10          | 192       | 230       | 325
11          | 5164      | 5618      | 6543
12          | 107189    | 118059    | 135085
13          | 998       | 1296      | 1826
14          | 767       | 955       | 1222
15          | 2070168   | 2283080   | 2683845
16          | 170       | 273       | 493
17          | 288       | 367       | 684
18          | 34135     | 37105     | 45708
21          | 239531    | 251051    | 265088
22          | 3876      | 4284      | 4570
23          | no code   | no code   | no code
24          | 74        | 94        | 146
------------+-----------+-----------+--------------
Totals      | 2581258   | 2830580   | 3296253

Total time taken 28305 ms
```

