from random import randint

def rand_string():
    l = randint(10, 20)
    s = ''.join(chr(ord('a') + randint(0, 25)) for _ in range(l))
    return s

n = 100000
print(n)
for i in range(n):
    print(rand_string())
