#!/bin/bash
NM=kth

for i in 1
do
    ./gen.exec >${NM}${i}.in 1000 2
    time ./std.exec <${NM}${i}.in >${NM}${i}.ans
done

for i in 2
do
    ./gen.exec >${NM}${i}.in 80000 1
    time ./std.exec <${NM}${i}.in >${NM}${i}.ans
done

for i in 3 4 5
do
    ./gen.exec >${NM}${i}.in 80000 2
    time ./std.exec <${NM}${i}.in >${NM}${i}.ans
done
