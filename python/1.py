#!/usr/bin/python
max = 1
def printMax(a,b):
	global max
	if a>b:
		print a
		max = a
	else:
		print b
		max = b
i = 1
j = 2
printMax(i,j)
print max
print 'hello'*5
