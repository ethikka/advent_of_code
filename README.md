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

Running each day 10 times

Day         | Best (µs) | Avg (µs)  | Worst (µs)
------------+-----------+-----------+--------------
1           | 208       | 263       | 490
2           | 246       | 329       | 364
3           | 689       | 1036      | 1357
4           | 455       | 584       | 755
5           | 329       | 385       | 552
6           | 1324      | 1534      | 1967
7           | 240       | 308       | 429
------------+-----------+-----------+--------------
Totals      | 3491      | 4439      | 5914

Total time taken 44 ms
```

