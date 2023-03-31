from random import randint

n = 200
b = 2
for f_id in range(1000):
    with open('inputs/' + str(f_id) + '.txt', 'w') as fout:
        print(n, file=fout)
        for i in range(n):
            print(randint(-b, b), end=' ', file=fout)
