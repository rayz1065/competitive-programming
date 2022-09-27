from functools import reduce

PAR_MAP = {
    '(': ')',
    '<': '>',
    '[': ']',
    '{': '}',
}

PAR_SCORES_SYNTAX = {
    ')': 3,
    ']': 57,
    '}': 1197,
    '>': 25137,
}

PAR_SCORES_UNMATCHED = {
    ')': 1,
    ']': 2,
    '}': 3,
    '>': 4,
}

def closing_par(par):
    # returns the closing par for an opening par
    # if none is found returns the input itself,
    # in that case it is expected for the input to be a closing par
    return PAR_MAP.get(par, par)

def read_in():
    problem = []
    try:
        while True:
            line = input()
            problem.append(line)
    except EOFError:
        pass
    return problem

class ParSyntaxError(SyntaxError):
    def __init__(self, par):
        super().__init__()
        self.par = par

    def score(self):
        return PAR_SCORES_SYNTAX[closing_par(self.par)]

class UnmatchedParError(Exception):
    def __init__(self, state):
        super().__init__()
        self.state = state

    def score(self):
        rev_par_scores = (PAR_SCORES_UNMATCHED[closing_par(par)] for par in reversed(self.state))
        return reduce(lambda tot, s: tot*5 + s, rev_par_scores)

def parse(line):
    state = []
    for par in line:
        if par in PAR_MAP:
            state.append(par)
        else:
            if len(state) == 0:
                # close before open
                raise ParSyntaxError(par)
            last_p = state.pop()
            if PAR_MAP[last_p] != par:
                # wrong closer
                raise ParSyntaxError(par)
    if len(state) > 0:
        # the rest of the state is unmatched
        raise UnmatchedParError(state)

def get_errors(problem):
    syntax_errors = []
    unmatched_errors = []
    for line in problem:
        try:
            parse(line)
        except ParSyntaxError as err:
            syntax_errors.append(err)
        except UnmatchedParError as err:
            unmatched_errors.append(err)
    return syntax_errors, unmatched_errors

def calc_1(scores):
    # the solution is the sum of the scores
    return sum(scores)

def calc_2(scores):
    # take the middle score in the sorted list
    return sorted(scores)[len(scores)//2]

def part_1(problem):
    errors, _ = get_errors(problem)
    return calc_1([err.score() for err in errors])

def part_2(problem):
    _, errors = get_errors(problem)
    return calc_2([err.score() for err in errors])

def parts_combined(problem):
    syntax_errors, unmatched_errors = get_errors(problem)
    scores_1 = [err.score() for err in syntax_errors]
    scores_2 = [err.score() for err in unmatched_errors]
    return calc_1(scores_1), calc_2(scores_2)

def main():
    problem = read_in()
    # sol_1, sol_2 = part_1(problem), part_2(problem)
    sol_1, sol_2 = parts_combined(problem)
    print("part_1:", sol_1)
    print("part_2:", sol_2)

if __name__ == '__main__':
    main()
