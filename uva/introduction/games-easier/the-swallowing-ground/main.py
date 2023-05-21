t_testcases = int(input().strip())
outputs = []
for _ in range(t_testcases):
    assert input() == ''
    w = int(input().strip())
    columns = [tuple(int(x) for x in input().strip().split())
               for _ in range(w)]

    target = columns[0][1] - columns[0][0]
    for y0, y1 in columns:
        if y1 - y0 != target:
            outputs.append('no')
            break
    else:
        outputs.append('yes')

print('\n\n'.join(outputs))
