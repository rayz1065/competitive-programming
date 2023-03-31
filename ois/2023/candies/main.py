n = int(input())
scores = sorted(int(x) for x in input().strip().split())
candies = 1
curr = 1

for i in range(1, n):
    if scores[i] > scores[i - 1]:
        curr += 1 # must give one more
    candies += curr
print(candies)
