#coding=utf-8
resu = list()
def validate(n):
    q = n
    while (q > 0):
        if (q % 10 != n & 1):
            return False
        q = q / 10
        n = n >> 1
    return True
num = 0
def qpow(x, y):
    if (y == 0): return 1
    temp = qpow(x, y >> 1)
    if (y & 1):
        return temp * temp * x
    else:
        return temp * temp
s = 1
def dfs(depth):
    global num, s
    if (depth == 0): return
    s = s * 10
    dfs(depth - 1)
    num = num + s
    if (validate(num)):
        print num
        dfs(depth - 1)
    num = num - s
    s = s / 10

dfs(135)
num = 1
dfs(135)
