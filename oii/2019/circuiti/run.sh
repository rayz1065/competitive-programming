#! /usr/bin/env bash

for filename in ./input_???.txt;
do
  out_filename=./output_${filename#./input_}
  python main.py < "$filename" > "$out_filename"
done

zip output.zip output*.txt
