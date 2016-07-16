#coding=utf-8
import random
n = 1000
f = open('a.in', 'w')
f.write('%d\n'%n)
for i in xrange(n):
    f.write('1 %d\n'%random.randint(-10000, 10000))
m = 20
f.write('%d\n'%m)
for i in xrange(m):
    f.write('%d %d\n'%(random.randint(1, n), random.randint(1, n)))
f.close()
