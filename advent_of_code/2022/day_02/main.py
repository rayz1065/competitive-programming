def read_input():
  strategy = []
  try:
    while True:
      line = input()
      strategy.append(tuple(line.split()))
  except EOFError:
    pass
  return strategy

rps_scores = {
  'A': 1,
  'B': 2,
  'C': 3,
}
OUTCOME_WIN = 'Z'
OUTCOME_EVEN = 'Y'
OUTCOME_LOSS = 'X'
rps_outcome_scores = {
  OUTCOME_WIN: 6,
  OUTCOME_EVEN: 3,
  OUTCOME_LOSS: 0,
}

def rps_simulate (move_a, move_b):
  move_a = ord(move_a) - ord('A')
  move_b = ord(move_b) - ord('A')
  if move_b == (move_a + 1) % 3:
    return OUTCOME_WIN
  elif move_a == (move_b + 1) % 3:
    return OUTCOME_LOSS
  return OUTCOME_EVEN

def rps_find_move (move_a, outcome):
  move_a = ord(move_a) - ord('A')
  if outcome == OUTCOME_WIN:
    move_b = (move_a + 1) % 3
  elif outcome == OUTCOME_LOSS:
    move_b = (move_a + 2) % 3
  else:
    move_b = move_a
  return chr(move_b + ord('A'))

def apply_strategy (strategy, moves_map):
  score = 0
  for move_a, move_b in strategy:
    move_b = moves_map[move_b]
    outcome = rps_simulate(move_a, move_b)
    score += rps_outcome_scores[outcome] + rps_scores[move_b]
  return score

def apply_outcomes_strategy (strategy):
  score = 0
  for move_a, outcome in strategy:
    move_b = rps_find_move(move_a, outcome)
    score += rps_outcome_scores[outcome] + rps_scores[move_b]
  return score

def main():
  strategy = read_input()
  # print(strategy)
  print('part 1:', apply_strategy(strategy, { 'Y': 'B', 'X': 'A', 'Z': 'C' }))
  print('part 2:', apply_outcomes_strategy(strategy))
  # all_sums = [sum(x) for x in all_calories]
  # print('part 1:', max(all_sums))
  # all_sums.sort()
  # print('part 2:', all_sums[-1] + all_sums[-2] + all_sums[-3])


if __name__ == '__main__':
  main()
