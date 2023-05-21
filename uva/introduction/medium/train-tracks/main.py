import re

t_testcases = int(input().strip())

for _ in range(t_testcases):
    connectors = re.sub(r'\s+', ' ', input()).strip().split()
    starting_m = sum(x.startswith('M') for x in connectors)
    ending_m = sum(x.endswith('M') for x in connectors)
    starting_f = sum(x.startswith('F') for x in connectors)
    ending_f = sum(x.endswith('F') for x in connectors)

    if starting_m == ending_f and starting_f == ending_m and len(connectors) > 1:
        print('LOOP')
    else:
        print('NO LOOP')
