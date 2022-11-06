from random import randint

n = 100000
d = 0
print(n, d)
for i in range(n):
    l_receiver = randint(-(10 ** 1), 10 ** 1)
    p_power = randint(-(10 ** 1), 10 ** 1)
    s_start = randint(0, 10)
    t_interval = randint(1, 10)
    print(l_receiver, p_power, s_start, t_interval)
