#coding=utf-8

def fac(n):
    rtn = 1
    for i in xrange(1, n + 1, 1):
        rtn = rtn * i
    return rtn

