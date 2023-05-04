n, p = (int(x) for x in input().strip().split())
first_score = sum(int(x) for x in input().strip().split())

max_other_score = 0
for _ in range(n - 1):
    score = sum(int(x) for x in input().strip().split())
    max_other_score = max(max_other_score, score)

max_other_score += p * 100
s = max(0, max_other_score + 1 - first_score)
print(s)
