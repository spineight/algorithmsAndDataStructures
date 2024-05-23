#!/bin/bash

#================================
#title      :test_perfomance.sh
#author     :covariancemomentum
#date       :04.04.2020 15:53
#version    :1.1
#================================

type=$1
echo "<====== Testing ""$type"" solution ======>"
declare -i cnt=$2
declare -i step=$3
declare -i repeat=$4
declare -i length=0

while [ $length -le "$cnt" ]
do
  chrt -f 98 perf stat -r "$repeat" sudo java -jar ./PerformanceTestCompiled.jar $length "$type" 2>"$type"_performance.log
  echo "$(grep task-clock "$type"_performance.log | cut -f1 -d, | sed -e 's/^[[:space:]]*//') ms" >> "$type"_performance.txt
  length+=$step
  echo "$length"
done

rm ./"$type"_performance.log