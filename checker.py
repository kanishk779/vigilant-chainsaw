f1 = open('output.txt', 'r')
f2 = open('output1.txt', 'r')

for l1 in f1.readlines():
    l2 = f2.readline()
    if l1 != l2:
        print('error')
        raise NotImplemented('error')

print('Ok')
