f2 = open('output1.txt', 'r')
f1 = open('out3.txt', 'r')
err = 0
tot = 0
for l1 in f1.readlines():
    l2 = f2.readline()
    tot += 1
    if l1 != l2:
        err += 1
        
print('number of lines : {a}'.format(a=tot))
print('number of errors : {a}'.format(a=err))
