import random
f = open('qq.in', 'w')
s = list()
for i in xrange(100):
    s.append(random.randint(1, 400))
s.sort()
f.write(' '.join(map(str, s)))
f.close()
