_, x = (int(x) for x in input().strip().split())
ls = sorted(int(x) for x in input().strip().split())
s = 0
i = 0
while i < len(ls):
    if i + 1 < len(ls) and ls[i] + ls[i + 1] <= x:
        i += 1
    i += 1
    s += 1
print(s)
