#!/usr/bin/env python3
from math import comb, factorial

# input data
n_letters = int(input().strip())
curr_guess = input().strip().split()


# insert your code here

left_to_guess = sum(x == '_' for x in curr_guess)
already_guessed = n_letters - left_to_guess
possible_letters = 26 - already_guessed

print(comb(possible_letters, left_to_guess) * factorial(left_to_guess))
