# inp w\nmul x 0\nadd x z\nmod x 26\ndiv z \d+\nadd x -?\d+\neql x w\neql x 0\nmul y 0\nadd y 25\nmul y x\nadd y 1\nmul z y\nmul y 0\nadd y w\nadd y \d+\nmul y x\nadd z y

# inp w
# mul x 0
# add x z
# mod x 26
# div z \d+
# add x -?\d+
# eql x w
# eql x 0
# mul y 0
# add y 25
# mul y x
# add y 1
# mul z y
# mul y 0
# add y w
# add y \d+
# mul y x
# add z y


values = [
    [  1,  10,  0 ],
    [  1,  12,  6 ],
    [  1,  13,  4 ],
    [  1,  13,  2 ],
    [  1,  14,  9 ],
    [ 26,  -2,  1 ],
    [  1,  11, 10 ],
    [ 26, -15,  6 ],
    [ 26, -10,  4 ],
    [  1,  10,  6 ],
    [ 26, -10,  3 ],
    [ 26,  -4,  9 ],
    [ 26,  -1, 15 ],
    [ 26,  -1,  5 ],
]

def test_number(number):
    number = [int(x) for x in str(number)]

    z_stack = []

    def curr_z():
        if len(z_stack) > 0:
            return z_stack[len(z_stack) - 1]
        return 0

    for digit, val in zip(number, values):
        found_dig = (curr_z() + val[1]) == digit
        if val[0] == 26:
            z_stack.pop()
        if not found_dig:
            z_stack.append(digit + val[2])

    if found_dig:
        return True
    return curr_z() == 0

def test_found_dig(i, curr_z, w):
    val = values[i]
    found_dig = (curr_z - val[1]) == w
    return found_dig

def main():
    bases = [0]
    i = 0
    while i < 14:
        attempts = 0
        while True:
            assert i < 14
            attempts+= 1
            print('digit', i, 'attempt', attempts)
            new_bases = []
            for base in bases:
                for last_dig in range(10**(attempts - 1), 10**attempts):
                    if '0' in str(last_dig):
                        continue
                    number = base * (10**attempts) + last_dig
                    if test_number(number):
                        new_bases.append(number)
            i+= 1
            if len(new_bases) > 0:
                # print()
                print('found', len(new_bases), 'new bases')
                bases = new_bases
                break
    print(max(bases))
    print(min(bases))

if __name__ == '__main__':
    main()
