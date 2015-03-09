#!/usr/bin/python
tel = {'jack': 4098, 'sape': 4139}
tel['guido'] = 4127
print tel
print tel['jack']
del tel['sape']
tel['irv'] = 4127
print tel
print tel.keys()
print tel.has_key('guido')

knights = {'gallahad': 'the pure', 'robin': 'the brave'}
for k, v in knights.items():
    print k, v

for i, v in enumerate(['tic', 'tac', 'toe']):
    print i, v

questions = ['name', 'quest', 'favorite color']
answers = ['lancelot', 'the holy grail', 'blue']
for q, a in zip(questions, answers):
    print 'What is your %s?  It is %s.' % (q, a)

