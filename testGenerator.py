import random
lim = 20
ops = 10
f = open('input1.txt', 'w')
for i in range(ops):
    j = random.randint(1, lim)
    f.write('INSERT '+str(j) + '\n')

for i in range(ops):
    j = random.randint(1, lim)
    f.write('FIND '+str(j) + '\n')

for i in range(ops):
    j = random.randint(1, lim)
    f.write('COUNT '+str(j) + '\n')

for i in range(ops):
    r = random.randint(1, lim)
    l = random.randint(1, r)
    f.write('RANGE '+str(l)+' '+str(r)+'\n')
