#!/bin/bash
#
# AoC runner
catch_errors() {
  exit 1;
}
trap catch_errors ERR

year=$1
day=$2

if [ ! $1 ]
then
  year=`date +"%Y"`
  day=`date +"%d" | sed 's/^0*//'`
fi

file="./buildoutput/d$year$day.out"
inputfile="./inputs/$year/input.day$day"
cppfile="./$year/day$day.cpp"
key="$year $day"
optsfile="ExtraOpts.txt"

extraoptions=`egrep "$key" $optsfile | sed 's/[^ ]* *[^ ]* *//'`
if [ ! -f $file ]
then
  echo "No binary: making '$year' '$day' "
  make $day YEAR=$year $extraoptions
fi

if [ $cppfile -nt $file ]
then
  echo "Old binary: making '$year' '$day' "
  make $day YEAR=$year $extraoptions
fi

if [ ! -f $file ]
then
  echo "Make failed!"
else
  if [ ! -f $inputfile ]
  then
    $file 
  else
    $file < $inputfile
  fi
fi
