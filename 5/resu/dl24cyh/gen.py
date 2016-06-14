import random
f = open('sub.in', 'w')
a = 1000000
for i in xrange(a):
    f.write(chr(random.randint(1, 26) + ord('a') - 1))
f.close()
