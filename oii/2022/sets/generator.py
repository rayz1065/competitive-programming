from random import shuffle
n = 20
print(n)
numbers = list(range(n))
shuffle(numbers)
print(' '.join(str(x) for x in numbers))
