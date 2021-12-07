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
1           | 280       | 306       | 377
2           | 221       | 239       | 271
3           | 413       | 603       | 1045
4           | 314       | 422       | 562
5           | 137593    | 139605    | 146859
6           | 37        | 46        | 70
7           | 4879      | 5392      | 5889
------------+-----------+-----------+--------------
Totals      | 143737    | 146613    | 155073

Total time taken 1466 ms
```