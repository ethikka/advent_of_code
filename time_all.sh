#!/bin/bash
#
# AoC time all the things of year {x}

year=$1
runs=10

if [ ! $1 ]
then
  year=`date +"%Y"`
fi

declare -A daytotal
declare -A daybest
declare -A dayavg
declare -A dayworst


for day in {1..25}
do
  best=0
  worst=0
  subt=0
  total=0
  file="./buildoutput/d$year$day.out"
  inputfile="./$year/input.day$day"
  if [ -f $file ]
  then
    for cnt in {1..10}
    do
      if [ ! -f $inputfile ]
      then
        retVal=`$file t`
      else
        retVal=`$file t < $inputfile`
      fi
      total=$(($total + retVal))
      subt=$(($subt + retVal))
      best=$((best > retVal || best == 0 ? retVal: best))
      worst=$((retVal > worst || worst == 0 ? retVal: worst))
      totalruntime=$(($totalruntime + retVal))
    done

    subt=$(($subt/$runs))
    daytotal[$day]=$total
    daybest[$day]=$best
    dayavg[$day]=$subt
    dayworst[$day]=$worst

    totalbest=$(($totalbest+$best));
    totalworst=$(($totalworst+$worst));
    totalavg=$(($totalavg+$subt));
  fi
done

printf "Running each day %d times\n\n" $runs

printf "\tDay\t"
for day in {1..25}
do
  printf "| %d\t" $day
done
printf "| Totals (µs)"
printf "\n"
echo "----------------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+--------------"

printf "Best (µs)\t"
for day in {1..25}
do
  printf "| %s\t" ${daybest[$day]}
done
printf "| %d" $totalbest

printf "\nAvg (µs)\t"
for day in {1..25}
do
  printf "| %s\t" ${dayavg[$day]}
done
printf "| %d" $totalavg

printf "\nWorst (µs)\t"
for day in {1..25}
do
  printf "| %s\t" ${dayworst[$day]}
done
printf "| %d" $totalworst

printf "\n"
echo "----------------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+--------------"
echo ""
totalruntime=$(($totalruntime / 1000))
printf "Total time taken %d ms\n\n" $totalruntime