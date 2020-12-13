#!/bin/bash
#
# AoC time all the things of year {x}

year=$1
runs=100

if [ ! $1 ]
then
  year=`date +"%Y"`
fi

daystats=();
echo "Best and worst completion times out of $runs for year $year"
echo ""
echo "Day     | Best (µs)     | Worst (µs)    | Average (µs)"
echo "--------+---------------+---------------+----------------"
for day in {1..25}
do
  best=0
  worst=0
  subt=0
  file="./buildoutput/d$year$day.out"
  inputfile="./$year/input.day$day"
  if [ -f $file ]
  then
    for cnt in {1..100}
    do
      if [ ! -f $inputfile ]
      then
        retVal=`$file t`
      else
        retVal=`$file t < $inputfile`
      fi
      subt=$(($subt + retVal))
      best=$((best > retVal || best == 0 ? retVal: best))
      worst=$((retVal > worst || worst == 0 ? retVal: worst))
    done
    subt=$(($subt/$runs))
    printf "%d\t| %d\t\t| %d\t\t| %d\n" $day $best $worst $subt
    totalbest=$(($totalbest+$best));
    totalworst=$(($totalworst+$worst));
    totalavg=$(($totalavg+$subt));
  fi
done

echo "--------+---------------+---------------+----------------"
printf "Totals\t| %d\t\t| %d\t| %d\n" $totalbest  $totalworst $totalavg
