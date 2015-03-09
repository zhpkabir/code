#!/usr/bin/python
s = 'Hello, world'
print str(s)
print repr(s)
print str(0.1)
print repr(0.1)
x = 10 * 3.25
y = 200 * 200
s = 'The value of x is ' + repr(x) + ', and y is ' + repr(y) + '...'
print s
hello = 'hello, world\n'
hellos = repr(hello)
print hellos
print repr((x, y, ('spam', 'eggs')))
print `x, y, ('spam', 'eggs')`

