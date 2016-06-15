#!/bin/bash
NM=sub
./gen.exec >${NM}1.in 1000 2
time ./std.exec <${NM}1.in >${NM}1.ans

for i in 2 3 4 5
do
    ./gen.exec >${NM}${i}.in 1000000 2
    time ./std.exec <${NM}${i}.in >${NM}${i}.ans
done

for i in 6 7 8 9 10
do
    ./gen.exec >${NM}${i}.in 1000000 26
    time ./std.exec <${NM}${i}.in >${NM}${i}.ans
done
