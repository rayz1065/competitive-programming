input()
ids = (int(x) for x in input().split())
freqs = {}
found_multiple = []
for x in ids:
    freqs.setdefault(x, 0)
    freqs[x] += 1
    if freqs[x] == 2:
        found_multiple.append(x)
print('YES' if len(found_multiple) > 1 else 'NO')
