#!/bin/bash
for i in 1 2 3 4 5
do
    time ./baoli.exec <kth${i}.in | diff - kth${i}.ans
    if [ $? -ne 0 ]
    then
        exit 1
    fi
    echo DATA $i OK
done
