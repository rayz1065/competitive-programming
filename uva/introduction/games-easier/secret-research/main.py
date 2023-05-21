n = int(input().strip())

for _ in range(n):
    s = input().strip()
    if s in ['1', '4', '78']:
        print('+')
    elif s.endswith('35'):
        print('-')
    elif s.startswith('9') and s.endswith('4'):
        print('*')
    else:
        print('?')
