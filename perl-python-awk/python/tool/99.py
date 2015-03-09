#!/usr/bin/env python
for x in range(1,10):
    for y in range(1,10):
        if y <= x:
            print "%dx%d=%d\t"%(y,x,x*y),
    print ""

print ""

for x in range(1,10):
    for y in range(1,x+1):
        print "%dx%d=%d\t"%(y,x,x*y),
    print ""

print ""

a,b=1,1
while a < 10:
    while b < 10:
        if b <= a:
            print "%dx%d=%d\t"%(b,a,a*b),
        b+=1
    a+=1
    b=1
    print ""

print ""
a,b=1,1
while a < 10:
    while b <= a:
        print "%dx%d=%d\t"%(b,a,a*b),
        b+=1
    a+=1
    b=1
    print ""

