# specify compiler
GXX=clang++-18 
YEAR=2020
CFLAGS = -O3 -Wfatal-errors -std=c++2a
ADDITIONAL_FILES=$(addprefix ./$(YEAR)/,$(subst :, ,$(ADD)))
ADDITIONAL_FLAGS=$(subst :, ,$(FLAGS))

all: 
	$(info Make <{daynumber}> [YEAR={yearnumber default:2019}] [ADD={additionalfile1.cpp:additionalfile2.cpp}] [FLAGS={-Wunused-value:-Wother-flag}])

%: ./$(YEAR)/day%.cpp
	$(GXX) $(CFLAGS) $(ADDITIONAL_FLAGS) -o buildoutput/d$(YEAR)$@.out ./$(YEAR)/day$@.cpp $(ADDITIONAL_FILES) 

clean: 
	rm ./buildoutput/*
