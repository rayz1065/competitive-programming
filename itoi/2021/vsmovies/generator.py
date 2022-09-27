from itertools import tee
from random import randint, shuffle

def pairwise(it):
    a, b = tee(it)
    next(b)
    return zip(a, b)

n_movies = 200
s_heros = randint(2, n_movies)
min_t, max_t = 5, 500

print(n_movies, s_heros)
heros = list(range(s_heros))
shuffle(heros)

for hero, other_hero in pairwise(heros):
    print(hero, other_hero, randint(min_t, max_t))

for i in range(n_movies - s_heros + 1):
    shuffle(heros)
    print(heros[0], heros[1], randint(min_t, max_t))
