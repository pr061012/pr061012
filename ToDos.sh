#!/bin/sh

# ToDos.sh
# Prints out all TODOS and FIXMES found in source files.

list=`find ./ -iname '*.cpp'; find ./ -iname '*.h'`

for f in "$list"
do
    grep -H -n -A 3 "TODO" $f
    grep -H -n -A 3 "FIXME" $f
done
