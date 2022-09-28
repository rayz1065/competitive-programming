def read_input ():
    return tuple(int(x) for x in input().split())

a, b, t = read_input()

def brute_force(a, b, t, start_time):
    s = 0
    curr_time = start_time
    while t > 0:
        if a <= curr_time < b:
            s += 1
        curr_time = (curr_time + 1) % 24
        t -= 1
    return s

s = 0

# add the time required for the full days
full_days = t // 24
daily_uptime = b - a
s += daily_uptime * full_days
t -= full_days * 24

s += min(brute_force(a, b, t, start_time) for start_time in range(24))

# assert s == true_sol, [a, b, t, true_sol, s]
print(s)
