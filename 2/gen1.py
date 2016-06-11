#coding=utf-8

import os, sys, random

f = open('a.in', 'w')
n = 131072
m = 65536
f.write('%d %d %d\n'%(n, m, 0))
s = list()
for i in xrange(n):
    s.append(str(random.randint(1, m)))
f.write('%s\n'%' '.join(s))
for i in xrange(1, n):
    f.write('%d %d\n'%(i, i + 1))

