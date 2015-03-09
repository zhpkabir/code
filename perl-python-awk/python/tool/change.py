#!/usr/bin/env python3.4
import sys
import getopt

local_arr = 'data_array'
local_fun = 'dsi_set_cmdq'

def usage():
        print('''Usage:
        -h, --help:        help information
        -i, --inputfile:   input file  
        inputfile:         input file
        -o, --outputfile:  output file ''')

def fun(obj):
    return obj.strip().replace('{','').replace('}','').replace('\n','').split(',')

def getarray(obj):
    array = []  
    try:
        f = open(obj)
    except FileNotFoundError as msg:
        print('%s' % msg,file=sys.stderr)
        sys.exit()
    except PermissionError as msg:
        print('%s' % msg,file=sys.stderr)
        sys.exit()
    for i in f:
        j = fun(i)
        a = []
        for num in range(len(j)):
            if num == 1:
                continue
            if j[num]:
                a.append(int(j[num].strip(),16))
        if a:   
            array.append(a)
    f.close()
    return array

def genarray(obj,fd):
    for i in getarray(obj):
        if len(i) == 2:
           print('%s[0]=%#010X;' % (local_arr,0x00000500|i[0]<<16),file=fd)
           print('%s(%s, 1, 1);\n' % (local_fun,local_arr),file=fd)
        else:
            print('%s[0]=%#010X;' % (local_arr,0x00003902|len(i)<<16),file=fd)
            tmp = 0;
            value = 0;
            while True:
                value += i[tmp]<<(tmp%4)*8
                if tmp%4 == 3 or tmp+1 >= len(i):
                    print('%s[%d]=%#010X;' % (local_arr,tmp//4+1,value),file=fd)
                    value = 0;

                if tmp+1 >= len(i):
                    break;
                else:
                    tmp += 1

            print('%s(%s, %d, 1);\n' % (local_fun,local_arr,tmp//4+2),file=fd)
        
def main(argv):
    inputpath = None
    outputpath= None
    try:
        opts, args = getopt.getopt(argv,'-hi:o:',['help','inputfile=','outputfile='])
    except getopt.GetoptError as msg:
        print('%s' % msg,file=sys.stderr)
        sys.exit()
    for opt, arg in opts:
        if opt in ('-h', '--help'):
            usage()
            sys.exit()
        if opt in ('-i', '--inputfile'):
            inputpath = arg
        if opt in ('-o', '--outputfile'):
            outputpath = arg

    if inputpath == None:
        if args[0] :
            inputpath = args[0]
        else:
            usage()
            sys.exit()

    if outputpath:
        try:
            fd = open(outputpath,'w')
        except PermissionError as msg:
            print('%s\n,Using stdout' % msg,file=sys.stderr)
            fd = sys.stdout
    else:
        fd = sys.stdout
    
    genarray(inputpath,fd) 
    fd.close()

if __name__ == '__main__':
    main(sys.argv[1:])

