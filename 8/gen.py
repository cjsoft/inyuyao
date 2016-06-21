import random
f = open('DIVLJAK.in', 'w')
n = 200
f.write('%d\n'%n)
for i in xrange(n / 2):
    l = random.randint(2, 4)
    o = ''
    for j in xrange(l):
        o = o + chr(ord('a') + random.randint(0, 25))
    f.write('%s\n%s\n'%(o, o))
q = 1000
f.write('%d\n'%q)
for i in xrange(q):
    if random.randint(1, 5) == 1:
        f.write('1 ')
        l = random.randint(10, 1000)
        for j in xrange(l):
            f.write(chr(ord('a') + random.randint(0, 25)))
        f.write('\n')
    else:
        f.write('2 %d\n'%random.randint(1, n))
f.close()
