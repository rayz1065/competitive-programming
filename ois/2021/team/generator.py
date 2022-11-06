from random import randint
n = 500
max_days = 10
max_dist = randint(1, max_days)
print(n)
print(' '.join(str(randint(0, max_days)) for _ in range(n)))

def valid_dist (i, j):
    return 0 if i == j else randint(1, max_dist)

for i in range(n):
    print(' '.join(str(valid_dist(i, j)) for j in range(n)))
