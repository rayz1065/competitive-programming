BLOOD_TYPES = [f'{bt}{rh}' for bt in ('O', 'AB', 'B', 'A') for rh in '-+']


def get_alleles (blood_type):
    if blood_type == '?':
        return None
    alleles = {
        x: (x in blood_type)
        for x in 'AB+'
    }
    return alleles


def read_tests ():
    while True:
        line = input().strip()
        if line.replace(' ', '') == 'END':
            break
        yield [get_alleles(x) for x in line.split(' ') if len(x) > 0]


def to_blood_type (alleles):
    res = [allele for allele in 'AB' if alleles[allele]]
    if len(res) == 0:
        res.append('O')
    res.append('+' if alleles['+'] else '-')
    return ''.join(res)


def is_o (alleles):
    return all(not alleles[x] for x in 'AB')


def is_ab (alleles):
    return all(alleles[x] for x in 'AB')


def is_valid (parent_1, parent_2, child):
    for allele, is_present in child.items():
        if is_present and not (parent_1[allele] or parent_2[allele]):
            return False

    if is_o(child) and any(is_ab(x) for x in (parent_1, parent_2)):
        return False
    if is_ab(child) and any(is_o(x) for x in (parent_1, parent_2)):
        return False

    return True


def possible_alleles ():
    for blood_type in BLOOD_TYPES:
        yield get_alleles(blood_type)


def normalize_output (person):
    if isinstance(person, list):
        if len(person) == 0:
            return "IMPOSSIBLE"
        if len(person) == 1:
            return to_blood_type(person[0])
        return '{' + ', '.join(to_blood_type(x) for x in person) + '}'

    return to_blood_type(person)


def main ():
    tc = 0

    for parent_1, parent_2, child in read_tests():
        if child is None:
            child = [x for x in possible_alleles() if is_valid(parent_1, parent_2, x)]
        if parent_2 is None:
            parent_2 = [x for x in possible_alleles() if is_valid(parent_1, x, child)]
        if parent_1 is None:
            parent_1 = [x for x in possible_alleles() if is_valid(x, parent_2, child)]

        tc += 1
        print(f'Case {tc}:', ' '.join(normalize_output(x) for x in (parent_1, parent_2, child)))


if __name__ == '__main__':
    main()
