from random import randint
n = 10 ** 4

print(n)
lst = 10000
for i in range(n):
    # nxt = randint(lst - 10, lst)
    nxt = randint(-1000, 1000)
    # nxt = -1 if i >= 839 else +1
    print(nxt, end=' ')
    lst = nxt
print()
