n, k = (int(x) for x in input().strip().split())
lines = [[ord(x) - ord('a') for x in input().strip()] for _ in range(n)]

line_distances = [0] * n
for j in range(k):
    char_freqs = [0] * 26
    for line in lines:
        char_freqs[line[j]] += 1

    for i, line in enumerate(lines):
        line_distances[i] += n - char_freqs[line[j]]

min_dist = min(line_distances)
best_line = next(i for i, dist in enumerate(line_distances) if dist == min_dist)
print(best_line)
