def read_in():
    problem = []
    try:
        while True:
            line = input()
            problem.append(line)
    except EOFError:
        pass
    return problem

def count_one_freq(problem, bit_idx):
    one_freq = 0
    for line in problem:
        one_freq+= line[bit_idx] == '1'
    return one_freq

def count_one_freqs(problem):
    n = len(problem[0])
    return [count_one_freq(problem, i) for i in range(n)]

def bin_to_dec(bin_num):
    dec = 0
    for i in bin_num:
        dec = dec * 2 + int(i)
    return dec

def part_1(problem):
    one_freqs = count_one_freqs(problem)
    gamma_rate = []
    epsilon_rate = []
    for one_freq in one_freqs:
        zero_freq = len(problem) - one_freq

        most_freq = int(one_freq > zero_freq)
        least_freq = int(not most_freq)

        gamma_rate.append(most_freq)
        epsilon_rate.append(least_freq)
    return bin_to_dec(gamma_rate) * bin_to_dec(epsilon_rate)

def bit_criteria_ox(zero_freq, one_freq):
    return str(int(one_freq >= zero_freq))

def bit_criteria_co2(zero_freq, one_freq):
    return str(int(one_freq < zero_freq))

def apply_bit_criteria(problem, bit_criteria):
    bit_pos = 0
    while len(problem) > 1:
        one_freq = count_one_freq(problem, bit_pos)
        zero_freq = len(problem) - one_freq
        stored_bit = bit_criteria(zero_freq, one_freq)
        problem = [line for line in problem if line[bit_pos] == stored_bit]
        bit_pos+= 1
    return bin_to_dec(problem[0])

def part_2(problem):
    ox_rating = apply_bit_criteria(problem, bit_criteria_ox)
    co2_rating = apply_bit_criteria(problem, bit_criteria_co2)
    return ox_rating * co2_rating

def main():
    problem = read_in()
    print('part_1:', part_1(problem))
    print('part_2:', part_2(problem))

if __name__ == '__main__':
    main()
