n, d = (int(input().strip()) for _ in range(2))
a = d
while len(str(a)) < n:
    a = a * 10
b = a + d
if len(str(b)) != n:
    b -= 2 * d
if len(str(b)) != n or b <= 0:
    a, b = 0, 0
print(a, b)
