# specify compiler
GXX=clang++ 
YEAR=2018
CFLAGS = -g -O3 -Wfatal-errors -std=c++11
ADDITIONAL_FILES=$(addprefix ./$(YEAR)/,$(subst :, ,$(ADD)))

all: 
	$(info Make <{daynumber}> [YEAR={yearnumber default:2018}] [ADD={additionalfile1.cpp:additionalfile2.cpp}])

%: ./$(YEAR)/day%.cpp
	$(GXX) $(CFLAGS) -o buildoutput/d$(YEAR)$@.out ./$(YEAR)/day$@.cpp $(ADDITIONAL_FILES)

clean: 
	rm ./buildoutput/*
