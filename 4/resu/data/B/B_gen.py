from random import *
from sys import *
n = int(argv[1])
A = [[randint(0, 1) for j in xrange(n)] for i in xrange(n)]
B = [[A[j][i] for j in xrange(n)] for i in xrange(n)]
cnt0, cnt1 = 0, 0
print n
for i in xrange(n << 1):
	if cnt0 == n: pick = 1
	elif cnt1 == n: pick = 0
	else: pick = randint(0, 1)
	if pick == 0:
		print ' '.join(str(e) for e in A[cnt0])
		cnt0 += 1
	elif pick == 1:
		print ' '.join(str(e) for e in B[cnt1])
		cnt1 += 1
