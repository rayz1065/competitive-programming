from random import choice
n = 10000
dice = [0] + [1] * 90

print(''.join(str(choice(dice)) for _ in range(n)))
