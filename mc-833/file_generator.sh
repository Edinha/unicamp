#!/usr/bin/env bash


touch $1

for i in {1..20100}
do
  printf "Computer Networks are awesome, or maybe i'm wrong ...\n" >> "$1"
done