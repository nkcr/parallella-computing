#!/bin/bash

for ((i=0;i<=100;i++));
do
  for ((j=0;j<=100;j++));
  do
    echo "i = $(($i*$i)) j = $(($j*$j))"
    ./main.elf $(($i*$i)) $(($j*$j)) >> stats.csv
  done
done
