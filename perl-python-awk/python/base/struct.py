#!/usr/bin/python
a = [1,2,3,4]
b = [5,6,7,8]
print a
a.append(13)
print a
a.extend(b)
print a
a.insert(0,100)
print a
a.remove(100)
print a
print a.pop()
print a
print a.index(7)
print a.count(7)
print a
a.reverse()
print a
del(a[0])
print a

