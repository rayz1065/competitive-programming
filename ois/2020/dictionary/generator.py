from random import choice, randint, shuffle

def rand_string (n):
    return ''.join(choice('abcdefghijklmnopqrstuvwxyz') for _ in range(n))

n = 1000
words = [rand_string(20) for _ in range(n)]
d = randint(n // 2, n)
print(n)
print(d)
for i in range(d):
    dependencies = randint(1, n // 2)
    new_words = list(set(words) - set([words[i]]))
    shuffle(new_words)
    print(words[i], dependencies, ' '.join(x for x, _ in zip(new_words, range(dependencies))))
