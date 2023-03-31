from random import randint, shuffle
n = 1000
m = 50000

print(n, m)
numbers = list(range(m))
shuffle(numbers)
numbers = numbers[:n]
print(' '.join(str(x) for x in sorted(numbers)))
