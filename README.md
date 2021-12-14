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
1           | 282       | 379       | 739
2           | 225       | 330       | 683
3           | 419       | 624       | 1573
4           | 311       | 442       | 663
5           | 151215    | 171383    | 203882
6           | 39        | 84        | 401
7           | 4272      | 5106      | 6201
8           | 1032      | 1603      | 2403
9           | 70113     | 79809     | 105532
10          | 207       | 308       | 727
11          | 5242      | 5906      | 6669
12          | 1397622   | 1480692   | 1605728
13          | 991       | 1304      | 1718
14          | 835       | 1358      | 2297
------------+-----------+-----------+--------------
Totals      | 1632805   | 1749328   | 1939216

Total time taken 17493 ms
```