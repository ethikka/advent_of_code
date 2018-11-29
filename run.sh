#!/bin/sh
#
# AoC runner

file="./buildoutput/d$1$2.out"
inputfile="./$1/input.day$2"
cppfile="./$1/day$2.cpp"
key="$1 $2"
optsfile="ExtraOpts.txt"

extraoptions=`egrep "$key" $optsfile | sed 's/[^ ]* *[^ ]* *//'`

if [ ! -f $file ]
then
  echo "No binary: making '$1' '$2' "
  make $2 YEAR=$1 $extraoptions
fi

if [ $cppfile -nt $file ]
then
  echo "Old binary: making '$1' '$2' "
  make $2 YEAR=$1 $extraoptions
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

