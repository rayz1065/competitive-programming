t = int(input().strip())
results = []
for _ in range(t):
    numbers = [int(x) for x in input().strip().split()]
    ascending_numbers = sorted(numbers)
    descending_numbers = sorted(numbers, key=lambda x: -x)
    if all(x == y for x, y in zip(numbers, ascending_numbers)) or \
       all(x == y for x, y in zip(numbers, descending_numbers)):
        results.append('Ordered')
    else:
        results.append('Unordered')

print("Lumberjacks:")
print('\n'.join(results))
