#!/bin/bash
#
# AoC time all the things of year {x}
tabs 12
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

printf "\n\nRunning each day %d times\n\n" $runs

echo "Day         | Best (µs) | Avg (µs)  | Worst (µs)"
echo "------------+-----------+-----------+--------------"

for day in {1..25}
do
  best=0
  worst=0
  subt=0
  total=0
  file="./buildoutput/d$year$day.out"
  inputfile="./inputs/$year/input.day$day"
  if [ -f $file ]
  then
    for cnt in $( eval echo {1..$runs} )
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

    printf "%s\t| %d\t| %d\t| %d\n" $day ${daybest[$day]} ${dayavg[$day]} ${dayworst[$day]}

    totalbest=$(($totalbest+$best));
    totalworst=$(($totalworst+$worst));
    totalavg=$(($totalavg+$subt));
  fi
done

echo "------------+-----------+-----------+--------------"
printf "Totals\t| %d\t| %d\t| %d\n\n" $totalbest $totalavg $totalworst

totalruntime=$(($totalruntime / 1000))
printf "Total time taken %d ms\n\n" $totalruntime
tabs -8