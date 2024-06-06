from itertools import permutations

line = input()
res = sorted(set(permutations(line)))

print(len(res))
print("\n".join("".join(x) for x in res))
