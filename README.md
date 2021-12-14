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
1           | 280       | 345       | 441
2           | 224       | 309       | 569
3           | 420       | 708       | 1554
4           | 335       | 453       | 569
5           | 152399    | 165333    | 216511
6           | 44        | 63        | 81
7           | 4126      | 6710      | 12344
8           | 986       | 1304      | 2064
9           | 65361     | 71315     | 81616
10          | 192       | 279       | 623
11          | 5263      | 6249      | 9457
12          | 109643    | 121400    | 129983
13          | 1003      | 1376      | 2084
14          | 729       | 1040      | 1595
------------+-----------+-----------+--------------
Totals      | 341005    | 376884    | 459491

Total time taken 3768 ms
```