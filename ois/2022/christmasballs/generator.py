from random import randint

n = 100000
print(n)
for i in range(n):
    # some random color
    print(randint(0, n - 1), end=' ')

print()
for i in range(1, n):
    # parent node
    print(randint(0, n - 1), end=' ')
