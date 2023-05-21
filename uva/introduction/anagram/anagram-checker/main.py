def find_freqs (letters):
    freqs = {}
    for letter in letters:
        freqs[letter] = freqs.get(letter, 0) + 1
    return freqs


def find_anagrams (letter_freqs, dictionary):
    if len(letter_freqs) == 0:
        return [[]]

    anagrams = []
    for i, word in enumerate(dictionary):
        word_freqs = find_freqs(word)
        if any(freq > letter_freqs.get(letter, 0) for letter, freq in word_freqs.items()):
            continue

        new_letter_freqs = letter_freqs.copy()
        for letter, freq in word_freqs.items():
            new_letter_freqs[letter] -= freq
            if new_letter_freqs[letter] == 0:
                new_letter_freqs.pop(letter)
        sub_anagrams = find_anagrams(new_letter_freqs, dictionary[i + 1:])

        anagrams.extend([[word, *sub] for sub in sub_anagrams])

    return anagrams


def main ():
    dictionary = []
    while True:
        line = input().strip()
        if line == '#':
            break
        dictionary.append(line)

    while True:
        sentence = input().strip()
        if sentence == '#':
            break
        sentence_words = sentence.split()
        filtered_dictionary = set(dictionary) - set(sentence_words)
        anagrams = find_anagrams(find_freqs(''.join(sentence_words)), sorted(filtered_dictionary))

        for anagram in anagrams:
            print(sentence, '=', ' '.join(anagram))


if __name__ == '__main__':
    main()
