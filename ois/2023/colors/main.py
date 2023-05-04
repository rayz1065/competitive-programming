MOD = 1000000007

n, k = (int(x) for x in input().strip().split())
same_color = [int(x) for x in input().strip().split()]

s = 1
available_endings = [0] * (n + 1)

for freq_ahead in same_color:
    ways = 1
    if freq_ahead > 0:
        ways = available_endings[freq_ahead - 1]
        available_endings[freq_ahead - 1] -= 1
    available_endings[freq_ahead] += 1
    s = (s * ways) % MOD

total_endings = sum(available_endings)

# choose factorial_endings colors, rearrange
for i in range(k - total_endings + 1, k + 1):
    s = (s * i) % MOD

print(s)
