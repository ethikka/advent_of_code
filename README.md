- install itertools (https://github.com/ryanhaining/cppitertools)
- create buildoutput directory

Run year day once
- ./run_once.sh <year> <day>

Build and run <year> <day> if the binary is older then the sourcefile, and wait for changes
- ./run.sh <year> <day>


---
```
wartoy@MU-TH-R-182:~/src/advent_of_code$ ./time_all.sh 

Running each day 1000 times

Day         | Best (µs) | Avg (µs)  | Worst (µs)
------------+-----------+-----------+--------------
1           | 203       | 229       | 500
2           | 204       | 230       | 1028
3           | 652       | 740       | 5169
4           | 441       | 500       | 1908
5           | 323       | 366       | 765
6           | 427       | 475       | 981
7           | 231       | 265       | 636
8           | 562       | 616       | 981
9           | 2490      | 2777      | 9138
10          | 81        | 96        | 307
------------+-----------+-----------+--------------
Totals      | 5614      | 6294      | 21413

Total time taken 6298 ms
```

