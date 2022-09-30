input()
values = (int(x) for x in input().split())
s, last_v = 0, None
for v in values:
    if v == -1:
        v = last_v
    s += v
    last_v = v
print(s)
