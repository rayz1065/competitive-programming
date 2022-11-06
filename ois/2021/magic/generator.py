from random import randint, shuffle

n, l = 5, 18
possible_positions = list(range(1, l))
shuffle(possible_positions)
x = [0] + possible_positions[: n - 1]
x.sort()
m = [randint(1, 9) for _ in range(n)]

print(n, l)
print(' '.join(str(k) for k in x))
print(' '.join(str(k) for k in m))
