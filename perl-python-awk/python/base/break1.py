#!/usr/bin/python
prime = 1;
a = []
for n in range(3,100):
    prime = 1
    for x in range(2,n):
        if n % x == 0:
            prime = 0
            break
    if prime == 1:
        a.append(n)
print a
