from random import randint, shuffle

n = 250
m = randint(n + 2, n + 20)

def get_numbers ():
    numbers = list(range(2, m + 1))
    shuffle(numbers)
    return numbers[:n]

print(n, m)
print(' '.join(str(x) for x in get_numbers()))
