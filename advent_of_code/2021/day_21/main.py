import re
from itertools import count, islice, product

MIN_SCORE_1 = 1000
MIN_SCORE_2 = 21

class ProblemState:
    def __init__(self, positions, scores, turn):
        self.positions = positions
        self.scores = scores
        self.turn = turn

    def __hash__(self):
        return hash((tuple(self.positions), tuple(self.scores), self.turn))

    def __eq__(self, other):
        return self.positions == other.positions and \
               self.scores == other.scores and \
               self.turn == other.turn

    def get_winning_player(self, min_score):
        return next((i for i, x in enumerate(self.scores) if x >= min_score), None)

    def simulate(self, rolls):
        move_by = sum(rolls)
        positions = self.positions.copy()
        scores = self.scores.copy()
        positions[self.turn] = (positions[self.turn] - 1 + move_by)%10 + 1
        scores[self.turn]+= positions[self.turn]
        return ProblemState(positions, scores, (self.turn + 1)%2)

def read_in():
    problem = []
    pl_re = re.compile(r'^Player \d starting position: (\d+)')
    for _ in range(2):
        line = input()
        match = pl_re.match(line)
        assert match is not None
        problem.append(int(match.groups()[0]))
    return problem

def part_1(positions):
    state = ProblemState(positions, [0, 0], 0)
    dice = count(1)
    rolls_count = 0
    while state.get_winning_player(MIN_SCORE_1) is None:
        rolls = islice(dice, 3)
        state = state.simulate(rolls)
        rolls_count+= 3
    return rolls_count * min(state.scores)

def possible_rolls():
    return product(range(1, 4), repeat=3)

def _part_2(state: ProblemState, memo):
    if state in memo:
        return memo[state]

    winning_player = state.get_winning_player(MIN_SCORE_2)
    if winning_player is not None:
        results = [winning_player == i for i in range(2)]
    else:
        results = [0, 0]
        for rolls in possible_rolls():
            next_state = state.simulate(rolls)
            new_results = _part_2(next_state, memo)
            for i, x in enumerate(new_results):
                results[i]+= x
    memo[state] = results
    return results

def part_2(positions):
    memo = {}
    return max(_part_2(ProblemState(positions, [0, 0], 0), memo))

def main():
    problem = read_in()
    print("part_1:", part_1(problem.copy()))
    print("part_2:", part_2(problem.copy()))

if __name__ == '__main__':
    main()
