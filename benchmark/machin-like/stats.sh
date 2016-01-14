#!/bin/bash

for ((i=0;i<=22;i++));
do
  for ((j=0;j<=22;j++));
  do
    echo "i = $(($i*$i*$i)) j = $(($j*$j*$j))"
    ./main.elf $(($i*$i*$i)) $(($j*$j*$j)) >> stats.csv
  done
done
