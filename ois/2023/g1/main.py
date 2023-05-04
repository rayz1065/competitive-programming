_, q = (int(x) for x in input().strip().split())
positions = [int(x) for x in input().strip().split()]
positions_map = [0] * (len(positions) + 1)
for i, x in enumerate(positions):
    positions_map[x] = i
overtaken_count = [0] * (len(positions) + 1)
max_overtaken = 0

for _ in range(q):
    a = int(input().strip())
    position = positions_map[a]
    b = positions[position - 1]

    positions[position], positions[position - 1] = b, a
    positions_map[b] = position
    positions_map[a] = position - 1
    overtaken_count[b] += 1
    if overtaken_count[b] > overtaken_count[max_overtaken] or \
        (overtaken_count[b] == overtaken_count[max_overtaken] and b < max_overtaken):
        max_overtaken = b
    print(max_overtaken)
