import re
from itertools import tee

def pairwise(iterator):
    a, b = tee(iterator)
    next(b)
    return zip(a, b)

class PolymerizationRule:
    def __init__(self, lft, rgt, generated):
        self.lft = lft
        self.rgt = rgt
        self.ingredients = (lft, rgt)
        self.generated = generated

    def __str__(self):
        return f"{self.lft}{self.rgt} -> {self.generated}"

class PolymerGenerator:
    def __init__(self, template, rules):
        self.template = template
        self.rules = rules
        self.state = list(template)
        self.rules_map = { x.ingredients: x for x in rules }

    def __str__(self):
        return ''.join(self.state)

    def __next__(self):
        new_state = []
        for lft, rgt in pairwise(self.state):
            new_state.append(lft)
            if (lft, rgt) in self.rules_map:
                new_state.append(self.rules_map[lft, rgt].generated)
        new_state.append(self.state[len(self.state) - 1])
        self.state = new_state
        return new_state

    def calculate_freqs(self):
        freqs = {}
        for c in self.state:
            freqs.setdefault(c, 0)
            freqs[c]+= 1
        return freqs

    def score(self):
        freqs = self.calculate_freqs()
        return max(freqs.values()) - min(freqs.values())

    def copy(self):
        return PolymerGenerator(self.template, self.rules.copy())

    def internal_states(self):
        return self.state[1:len(self.state) - 1]

def read_in():
    template = input()
    rules = []
    assert input() == ''
    try:
        rule_re = re.compile('^([A-Z])([A-Z]) -> ([A-Z])$')
        while True:
            line = input()
            matches = rule_re.match(line)
            assert matches is not None
            lft, rgt, generated = matches.groups()
            rules.append(PolymerizationRule(lft, rgt, generated))
    except EOFError:
        pass
    return template, rules

def sum_dicts(res: dict, other: dict):
    for k, v in other.items():
        res.setdefault(k, 0)
        res[k]+= v

def freqs_rec(lft, rgt, steps, rules_map, memo):
    if (lft, rgt, steps) in memo:
        return memo[lft, rgt, steps]
    freqs = {}

    if steps != 0:
        mid = rules_map[lft, rgt].generated
        freqs[mid] = 1
        sum_dicts(freqs, freqs_rec(lft, mid, steps - 1, rules_map, memo))
        sum_dicts(freqs, freqs_rec(mid, rgt, steps - 1, rules_map, memo))

    memo[lft, rgt, steps] = freqs
    return freqs

def part_1(problem):
    for _ in range(10):
        next(problem)
        # print(i, problem)
    return problem.score()

def freqs_after(template, rules_map, steps):
    res = {}
    for x in template:
        res.setdefault(x, 0)
        res[x]+= 1
    memo = {}
    for lft, rgt in pairwise(template):
        sum_dicts(res, freqs_rec(lft, rgt, steps, rules_map, memo))
    return max(res.values()) - min(res.values())

def main():
    template, rules = read_in()
    rules_map = { x.ingredients: x for x in rules }
    print("part_1:", freqs_after(template, rules_map, 10))
    print("part_2:", freqs_after(template, rules_map, 40))

if __name__ == '__main__':
    main()
