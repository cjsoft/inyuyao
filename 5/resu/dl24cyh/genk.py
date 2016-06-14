#coding=utf-8
import random
n = 20
Q = 10
f = open('kth.in', 'w')
f.write('%d\n'%n)
l = list()
for i in xrange(n):
    l.append(random.randint(-100, 100))
l = map(str, l)
f.write('%s\n'%' '.join(l))
f.write('%d\n'%Q)
for i in xrange(Q):
    a = random.randint(1, 2)
    b, c = random.randint(1, n), random.randint(1, n)
    if (b > c): b, c = c, b
    if (a == 1):
        f.write('1 %d %d %d\n'%(b, c, random.randint(-100, 100)))
    else:
        f.write('2 %d %d %d\n'%(b, c, random.randint(1, max(c - b - 1, 1))))
f.close()
