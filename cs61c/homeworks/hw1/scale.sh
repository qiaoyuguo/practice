#!/bin/bash

# for use with Life1D for CS61C
# example usage:
# $ ./Life1D 17 3141592653 | ./scale.sh 10 | ppmtogif > Life1D_17_3141592653.gif

first=1
while read line
do
  array=(${line// / })
  if [ "$first" -eq 0 ]
  then
    # insert black horizontal line
    for (( k=0; k<$width; k++ ))
    do
      echo -n "1 "
    done
    echo ""
    # loop by scaling factor in height
    for (( n=0; n<$1; n++ ))
    do
      # loop by element in line
      for i in "${!array[@]}"
      do
        echo -n "1 "
        # loop by scaling factor in width
        for (( j=0; j<$1; j++ ))
        do
          echo -n "${array[i]} "
        done
      done
      echo "1 "
    done
  else
    # modify first line for new dimensions
    first=0
    width=$((${array[1]}*($1+1)+1))
    height=$((${array[2]}*($1+1)+1))
    for i in "${!array[@]}"
    do
      if [ "$i" -eq 1 ]
      then
        echo -n "$width "
      elif [ "$i" -eq 2 ]
      then
        echo -n "$height "
      else
        echo -n "${array[i]} "
      fi
    done
    echo ""
  fi
done

# insert black horizontal line
for (( n=0; n<$width; n++ ))
do
  echo -n "1 "
done
echo ""
