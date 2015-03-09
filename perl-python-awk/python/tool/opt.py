import getopt
import sys
print(getopt.getopt(sys.argv[1:],"-hi:o:",["help","inputfile=","outputfile="]))
try:
    open("ss")
except IOError, msg:
    print("aaaaaaaaaaaaaaaa")
