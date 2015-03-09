#!/usr/bin/python
#def aa(s):
#    print s
#aa('hello,world')
#aa(40)
def fib2(n):
    result = []
    a, b = 0, 1
    while b < n:
        result.append(b)
        a, b = b, a+b
    return result
f100 = fib2(100)
print f100
