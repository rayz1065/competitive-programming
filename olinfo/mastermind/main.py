from math import log
from random import choice

all_combs = []
def find_combs (curr, sz, options='BRG'):
    global all_combs
    if len(curr) == sz:
        all_combs.append(''.join(curr))
        return
    for x in options:
        curr.append(x)
        find_combs(curr, sz, options)
        curr.pop()

def find_eq (a, b):
    s = 0
    for ai, bi in zip(a, b):
        s += ai == bi or ai == 'G' or bi == 'G'
    return s

def score (spl):
    s = 0
    tot_am = 0
    for val in spl[1].values():
        if isinstance(val, list):
            n = len(val)
            tot_am += n
            s += n * log(n)
        else:
            sub_s, sub_tot = score(val)
            tot_am += sub_tot
            s += sub_s * sub_tot
    return s / tot_am + 1, tot_am

def split (combs, guess):
    res = {}
    for comb in combs:
        eq = find_eq(comb, guess)
        res.setdefault(eq, [])
        res[eq].append(comb)
    return (guess, res)

def find_guess (combs, depth=0):
    if depth == 20 or len(combs) == 1:
        return combs
    all_guesses = []
    for guess in valid_guesses:
        spl = split(combs, guess)
        all_guesses.append(spl)
    all_guesses.sort(key=lambda x: score(x)) # sort by score
    all_guesses = all_guesses[:1] # pick the best ones
    # split further for all the best ones
    all_guesses = [(guess, {
        k: find_guess(v, depth + 1)
        for k, v in spl.items()
    }) for guess, spl in all_guesses]
    all_guesses.sort(key=lambda x: score(x))
    return all_guesses[0] # return the best

def flatten_dts (spl, all_dts):
    if isinstance(spl, list):
        all_dts.append((spl[0], [-1]))
        return len(all_dts) - 1
    guess, values = spl
    sub_dts = { res: flatten_dts(x, all_dts) for res, x in values.items() }
    rem_subdts = [0] * (len(guess) + 1)
    for x, v in sub_dts.items():
        rem_subdts[x] = v
    while rem_subdts[-1] == 0:
        rem_subdts.pop()
    all_dts.append((spl[0], rem_subdts))
    return len(all_dts) - 1

def flat_dt_to_c (dts):
    print('{')
    i = 0
    for guess, sub_dts in dts:
        sub_dts = '{' + ','.join(str(x) for x in sub_dts) + '}'
        print('{', f'"{guess}",{sub_dts}', '},', end='', sep='')
        i += 1
        if i % 30 == 0:
            print()
    print('}')

find_combs([], 10, options='BRG')
valid_guesses = [guess for guess in all_combs if 'G' not in guess]
x = find_guess(all_combs)
print(x)
all_dts = [('ZZZZZ', [-1])]
print(flatten_dts(x, all_dts))
print(all_dts)
flat_dt_to_c(all_dts)
print(score(x))
