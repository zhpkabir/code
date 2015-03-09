#!/usr/bin/env python3.3
for a in range(1,10):
	for b in range(1,10) :
		if a>=b :
			print(repr(b).ljust(1)+"x"+repr(a).ljust(1)+"="+repr(b*a).ljust(2),end=' ')
	print('')
