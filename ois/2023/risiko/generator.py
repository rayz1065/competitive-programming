from random import randint, sample

k = randint(50, 100)
n = randint(100, 500)
n -= n % k - 1

strengths = [randint(1, 10**9) for _ in range(n)]

adj_mat = [[0] * n for _ in range(n)]
adj_count = [0] * n

for _ in range(n * k):
    i = randint(0, n - 1)
    j = randint(0, n - 2)
    if j >= i:
        j += 1
    if adj_count[i] < k - 1 and adj_count[j] < k - 1 and not adj_mat[i][j]:
        adj_mat[i][j] = True
        adj_mat[j][i] = True
        adj_count[i] += 1
        adj_count[j] += 1

print(n, k)
print(' '.join(str(x) for x in strengths))
for i in range(n):
    print(adj_count[i], ' '.join(str(j) for j, is_adj in enumerate(adj_mat[i]) if is_adj))
