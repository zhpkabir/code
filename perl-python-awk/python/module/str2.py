#!/usr/bin/python
import string
for x in range(1, 11):
    print string.rjust(repr(x), 2), string.rjust(repr(x*x), 3),
    print string.rjust(repr(x*x*x), 4)


for x in range(1, 11):
    print string.ljust(repr(x), 2), string.ljust(repr(x*x), 3),
    print string.ljust(repr(x*x*x), 4)


for x in range(1, 11):
    print string.center(repr(x), 2), string.center(repr(x*x), 3),
    print string.center(repr(x*x*x), 4)

for x in range(1,11):
    print '%2d %3d %4d' % (x, x*x, x*x*x)

