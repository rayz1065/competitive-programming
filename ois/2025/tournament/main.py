def main():
    input()
    skills = [(int(x), i) for i, x in enumerate(input().strip().split())]
    while len(skills) > 2:
        skills = [
            max(skills[2 * i], skills[2 * i + 1]) for i in range(len(skills) // 2)
        ]

    winner, runner_up = max(skills), min(skills)
    print(winner[1], runner_up[1])


if __name__ == "__main__":
    main()
