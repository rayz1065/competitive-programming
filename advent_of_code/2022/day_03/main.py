def read_input ():
  sacks = []
  try:
    while True:
      line = input()
      sacks.append(line)
  except EOFError:
    pass
  return sacks

def prio (item):
  if ord('a') <= ord(item) <= ord('z'):
    return 1 + ord(item) - ord('a')
  return 27 + ord(item) - ord('A')

def part_1 (sacks):
  partitioned = [(x[:len(x)//2], x[len(x)//2:]) for x in sacks]
  items = [set(a).intersection(b).pop() for a, b in partitioned]
  return sum(prio(x) for x in items)

def part_2 (sacks):
  items = []
  for i in range(0, len(sacks), 3):
    items.append(set(sacks[i]).intersection(sacks[i + 1]).intersection(sacks[i + 2]).pop())
  return sum(prio(x) for x in items)

def main ():
  sacks = read_input()
  print('part_1:', part_1(sacks))
  print('part_2:', part_2(sacks))

if __name__ == '__main__':
  main()
