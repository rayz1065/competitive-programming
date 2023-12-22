def normalize_records (records):
    result = []
    from_name = ''

    for record in records:
        record_info = record.strip().split()
        if len(record_info) < 3:
            record_info = from_name, *record_info

        from_name, preference, to_name = record_info
        preference = int(preference)
        result.append((from_name, preference, to_name))

    return result


def is_match (name, matched_name):
    name = list(reversed(name.split('.')))
    matched_name = list(reversed(matched_name.split('.')))

    if matched_name[-1] == '*':
        matched_name.pop()
        if len(name) <= len(matched_name):
            return False

        while len(name) > len(matched_name):
            name.pop()

    return tuple(name) == tuple(matched_name)


def read_operations ():
    while True:
        line = input().strip()
        if line == 'X':
            break
        # lines may contain more than 2 sections, ignore after first 2
        op, name, *_ = line.split()
        yield op, name


def main ():
    n = int(input().strip())
    mx_records = normalize_records([input() for _ in range(n)])
    is_online = { x[2]: True for x in mx_records }

    for op, name in read_operations():
        if op == 'D':
            is_online[name] = False
            continue
        if op == 'U':
            is_online[name] = True
            continue

        valid = [x for x in mx_records
                 if is_online[x[2]] and is_match(name, x[0])]

        res = ''
        if len(valid) > 0:
            best_preference = min(x[1] for x in valid)
            best = next(x for x in valid if x[1] == best_preference)
            res = f' {best[2]}'

        print(f'{name} =>{res}')


if __name__ == '__main__':
    main()
