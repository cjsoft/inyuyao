#coding=utf-8
f = open('an', 'r')
s = f.read().split('\n')
if (s[-1] == ''):
    s.pop()
s = map(int, s)
s.sort()
s = map(str, s)
s.insert(0, "1")
s.insert(0, "0")
def wrapper(s):
    s = '"' + s + '"'
    return s
s = map(wrapper, s)
f = open('parseds', 'w')
# f.write('\n'.join(s[:1461]))
f.write('std::string table[] = {%s};'%', '.join(s[:1461]))
f.close()
