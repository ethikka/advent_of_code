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

2015_19: ./2015/day19.cpp
	$(GXX) $(CFLAGS) -o buildoutput/d201519.out ./2015/day19.cpp

2017_1: ./2017/day1.cpp
	$(GXX) $(CFLAGS) -o buildoutput/d20171.out ./2017/day1.cpp

2017_2: ./2017/day2.cpp
	$(GXX) $(CFLAGS) -o buildoutput/d20172.out ./2017/day2.cpp

2017_3: ./2017/day3.cpp
	$(GXX) $(CFLAGS) -o buildoutput/d20173.out ./2017/day3.cpp

2017_4: ./2017/day4.cpp
	$(GXX) $(CFLAGS) -o buildoutput/d20174.out ./2017/day4.cpp

2017_5: ./2017/day5.cpp
	$(GXX) $(CFLAGS) -o buildoutput/d20175.out ./2017/day5.cpp

#2017_6: ./2017/day6.cpp
#	$(GXX) $(CFLAGS) -o buildoutput/d20176.out ./2017/day6.cpp

2017_7: ./2017/day7.cpp
	$(GXX) $(CFLAGS) -o buildoutput/d20177.out ./2017/day7.cpp

2017_8: ./2017/day8.cpp
	$(GXX) $(CFLAGS) -o buildoutput/d20178.out ./2017/day8.cpp


2017_13: ./2017/day13.cpp
	$(GXX) $(CFLAGS) -o buildoutput/d201713.out ./2017/day13.cpp


clean: 
	rm ./buildoutput/*



