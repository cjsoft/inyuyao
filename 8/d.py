#coding
import sys, os
n = int(raw_input())
a = list()
a.append('')
for i in xrange(1, n + 1):
    a.append(raw_input())
q = int(raw_input())
lll = list()
for i in xrange(q):
    l = raw_input().split(' ')
    if (l[0] == '1'):
        lll.append(l[1])
    else:
        cnt = 0
        p = int(l[1])
        for j in lll:
            if j.find(a[p]) != -1:
                cnt = cnt + 1
        print cnt
