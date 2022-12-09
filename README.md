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
1           | 210       | 340       | 568
2           | 206       | 262       | 341
3           | 700       | 915       | 1136
4           | 445       | 567       | 883
5           | 345       | 435       | 612
6           | 433       | 719       | 1606
7           | 235       | 337       | 585
8           | 591       | 795       | 1484
9           | 4476      | 5301      | 6162
------------+-----------+-----------+--------------
Totals      | 7641      | 9671      | 13377

Total time taken 96 ms
```

