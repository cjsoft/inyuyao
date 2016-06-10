#coding=utf-8
import os, sys, random
f = open('in', 'w')
n = 10
m = 5
f.write('%d %d\n'%(n, m))
for i in xrange(n):
    f.write('%d\n'%random.randint(-1000, 1000))
for i in xrange(m):
    op = random.randint(0, 2)
    l, r = random.randint(0, n - 1), random.randint(0, n - 1)
    if (l > r): l, r = r, l
    if (op == 0):
        f.write('%d %d %d %d\n'%(op, l, r, random.randint(-1000, 1000)))
    else:
        f.write('%d %d %d\n'%(op, l, r))
f.close()
