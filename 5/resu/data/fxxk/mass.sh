#!/bin/bash
NM=fxxk
./gen.exec >${NM}1.in 100 20
time ./std.exec <${NM}1.in >${NM}1.ans

for i in 2 3 4 5
do
    ./gen.exec >${NM}${i}.in 8 500
    time ./std.exec <${NM}${i}.in >${NM}${i}.ans
done

for i in 6 7 8 9 10
do
    ./gen.exec >${NM}${i}.in 1 1000
    time ./std.exec <${NM}${i}.in >${NM}${i}.ans
done
