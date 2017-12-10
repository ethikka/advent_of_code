# specify compiler
GXX=clang++ 
CFLAGS = -g -Wfatal-errors -std=c++11

all: 
	$(info Make <{year}_{daynumber}> ) 
     
2015_1: ./2015/day1.cpp
	$(GXX) $(CFLAGS) -o buildoutput/d20151.out ./2015/day1.cpp
        
2015_2: ./2015/day2.cpp
	$(GXX) $(CFLAGS) -o buildoutput/d20152.out ./2015/day2.cpp

2015_3: ./2015/day3.cpp
	$(GXX) $(CFLAGS) -o buildoutput/d20153.out ./2015/day3.cpp

2015_4: ./2015/day4.cpp
	$(GXX) $(CFLAGS) -o buildoutput/d20154.out ./2015/day4.cpp ./2015/md5.cpp

2015_5: ./2015/day5.cpp
	$(GXX) $(CFLAGS) -o buildoutput/d20155.out ./2015/day5.cpp

clean: 
	rm ./buildoutput/*



