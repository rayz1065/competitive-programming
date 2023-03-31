from random import randint

n = 50000000
m = 67108864
print(n)
for i in range(n):
    print(randint(-m, m), end=' ')
print()
