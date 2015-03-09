#!/usr/bin/python
prime = 1;
a = []
for n in range(3,100):
    prime = 1
    for x in range(2,n):
        if n % x == 0:
            prime = 0
            #print n,'equals', x, '*', n/x
            break
    if prime == 1:
        a.insert(len(a),n)
        #print n, 'is a prime number'
print a
