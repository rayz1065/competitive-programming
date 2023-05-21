def normalize (word):
    return ''.join(sorted(word.lower()))


words = []
while True:
    line = input().strip()
    if line == '#':
        break
    words.extend(x for x in line.split() if len(x) > 0)

anagram_freqs = {}
for word in words:
    key = normalize(word)
    anagram_freqs.setdefault(key, 0)
    anagram_freqs[key] += 1

words.sort()
for word in words:
    key = normalize(word)
    if anagram_freqs[key] == 1:
        print(word)
