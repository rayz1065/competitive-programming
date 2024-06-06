n = int(input())
res = 0

while n > 0:
    n //= 5
    res += n

print(res)
