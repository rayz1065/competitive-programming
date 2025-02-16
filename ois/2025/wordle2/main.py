import sys
import re
from string import ascii_lowercase


def solve():
    initial_guesses = re.findall(r"\w{5}", ascii_lowercase)
    correct_letters = []

    for guess in initial_guesses:
        print("?", guess)
        sys.stdout.flush()
        feedback = input().strip()
        for letter, letter_feed in zip(guess, feedback):
            if letter_feed in "GY":
                correct_letters.append(letter)

    if len(correct_letters) == 5:
        solution = [correct_letters.pop()] * 5
    else:
        solution = ["z"] * 5

    for letter in correct_letters:
        print("?", letter * 5)
        sys.stdout.flush()
        feedback = input().strip()

        for i, letter_feed in enumerate(feedback):
            if letter_feed == "G":
                solution[i] = letter

    print("!", "".join(solution))
    sys.stdout.flush()


def main():
    testcases = int(input().strip())
    for _ in range(testcases):
        solve()

    sys.stdout.close()


if __name__ == "__main__":
    main()
