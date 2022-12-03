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
1           | 209       | 323       | 702
2           | 207       | 292       | 612
3           | 1377      | 1703      | 2268
------------+-----------+-----------+--------------
Totals      | 1793      | 2318      | 3582

Total time taken 23 ms
```

