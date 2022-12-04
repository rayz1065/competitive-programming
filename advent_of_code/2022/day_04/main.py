import re

def read_input ():
  groups = []
  try:
    while True:
      line = input()
      res = re.match(r'^(\d+)-(\d+),(\d+)-(\d+)$', line)
      assert res is not None
      a, b, a2, b2 = (int(x) for x in res.groups())
      groups.append(((a, b), (a2, b2)))
  except EOFError:
    pass
  return groups

def part_1 (groups):
  s = 0
  for group in groups:
    x, y = group
    if x[0] <= y[0] <= y[1] <= x[1]:
      s += 1
    elif y[0] <= x[0] <= x[1] <= y[1]:
      s += 1
  return s

def part_2 (groups):
  s = 0
  for group in groups:
    x, y = group
    if not (x[1] < y[0] or y[1] < x[0]):
      s += 1
  return s

def main ():
  groups = read_input()
  print('part_1:', part_1(groups))
  print('part_2:', part_2(groups))

if __name__ == '__main__':
  main()
