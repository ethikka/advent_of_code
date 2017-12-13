#!/bin/sh
#
# AoC runner

file="./buildoutput/d$1$2.out"
inputfile="./$1/input.day$2"

echo $file;

if [ ! -f $file ]
then
  echo "No binary: making '$1' '$2' "
  make $1_$2
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

