#!/usr/bin/python
f = open('./temp.txt','a+')
f.write('aaaaaaaaaaaaa\n')
f.close()
f = open('./temp.txt','r')
print f.read(1)
print f.readline()
print f.read()
f.close()
