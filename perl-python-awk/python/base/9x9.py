#!/usr/bin/env python
a,b=1,1
while a < 10:
    while b < 10:
        if(a>=b):
            print "%dx%d=%d\t"%(b,a,a*b),
        b=b+1
    b=1
    a=a+1
    print ""
