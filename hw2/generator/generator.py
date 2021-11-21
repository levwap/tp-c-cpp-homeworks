import random

for i in range(500):
    f = open('../data/' + str(i) + '.txt', 'w')
    for j in range(2000):
        count = random.randint(1, 5)
        for k in range(count):
            f.write(str(random.randint(0, 9)))
        f.write(' ')
        if not (j % 20) :
            f.write('\n')
    f.close()
