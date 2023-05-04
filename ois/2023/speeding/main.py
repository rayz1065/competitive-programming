MOD = 1000000007

input()
limits = sorted(int(x) for x in input().strip().split())
speeds = sorted(int(x) for x in input().strip().split())

def solve ():
    for limit, speed in zip(limits, speeds):
        if limit < speed:
            return 0
    s = 1
    speed_i, speed_j = 0, 0
    for limit in limits:
        while speed_j + 1 < len(speeds) and speeds[speed_j + 1] <= limit:
            speed_j += 1
        s = (s * (speed_j - speed_i + 1)) % MOD
        speed_i += 1
    return s

print(solve())
