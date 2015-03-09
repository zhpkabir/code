#!/usr/bin/env python3.4
import struct
import os
import sys
def fun(obj):
    return obj.strip().replace('{','').replace(';','').replace('}','').replace('\n','').split(',')

def bin2arr(argv):
    filesize=os.path.getsize(argv)
    f = open(argv,'rb')
    print("{")
    for i in range(filesize):
        data=struct.unpack('B',f.read(1))
        if i%16 == 16-1:
            print(" %#04x"%(int(data[0])),end='\n')
        elif i == filesize-1:
            print(" %#04x"%(int(data[0])),end='')
        else:
            print(" %#04x"%(int(data[0])),end=',')
    f.close()
    print("};")

def arr2bin(argv):
    try:
        f=open(argv[0])
    except FileNotFoundError as msg:
        print('%s' % msg,file=sys.stderr)
        sys.exit()
    fw=open(argv[1],'wb')
    for i in f:
        j = fun(i)
        for num in range(len(j)):
            if j[num] !='':
                fw.write(struct.pack("B",int(j[num].strip(),16)))
    f.close()
    fw.close()

def main(argv):
    if len(argv) == 1:
        bin2arr(argv[0])
    elif len(argv) == 2:
        arr2bin(argv)

if __name__ == "__main__":
    main(sys.argv[1:])

