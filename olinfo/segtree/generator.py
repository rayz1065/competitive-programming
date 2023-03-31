from random import randint

n = 1000
q = 1000
num_range = 1000

print(n)
print(' '.join(str(randint(-num_range, num_range)) for _ in range(n)))

for i in range(q):
    action = randint(1, 5)
    l = randint(0, n - 1)
    r = randint(0, n - 1)
    if l > r:
        l, r = r, l
    r += 1
    if action in (1, 4):
        # get sum
        print(action, l, r)
    else:
        # add
        print(action, l, r, randint(-num_range, num_range))
