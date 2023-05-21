numbers = []
while True:
    n = int(input().strip())
    if n == 0:
        break
    numbers.append(n)

for number in numbers:
    res = number % 9
    if res == 0:
        res = 9
    print(res)
