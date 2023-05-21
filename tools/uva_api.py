import requests

UHUNT_API_URL = 'https://uhunt.onlinejudge.org/api'
JUDGE_URL = 'https://onlinejudge.org'
MY_USER_ID = 928021
BOOK_EDITION = 3

PROBLEM_TYPE = list[
    int, # problem ID
    int, # problem number
    str, # problem title
    # many others...
]

BOOK_PROBLEMS_TYPE = list[dict[
    # chapter
    'title': str,
    'arr': list[dict[
        # sub-chapter
        'title': str,
        'arr': list[
            # categories, first element is category name, then problem numbers
            list
        ]
    ]]
]]

SOLVED_PROBLEMS_TYPE = list[dict[
    'uid': int,
    'solved': list[int]
]]

problems_list: list[PROBLEM_TYPE] = requests.get(f'{UHUNT_API_URL}/p', timeout=60).json()
solved_problems: SOLVED_PROBLEMS_TYPE = requests.get(f'{UHUNT_API_URL}/solved-bits/{MY_USER_ID}', timeout=60).json()
book_problems: BOOK_PROBLEMS_TYPE = requests.get(f'{UHUNT_API_URL}/cpbook/{BOOK_EDITION}', timeout=60).json()

problems_by_number = {}
problems_by_id = {}
for problem in problems_list:
    assert problem[1] not in problems_by_number
    problems_by_number[problem[1]] = problem
    problems_by_id[problem[0]] = problem

solved_problems_set = set()
for i, encoded_bits in enumerate(solved_problems[0]['solved']):
    for j in range(32):
        problem_id = i * 32 + j
        solved = encoded_bits & (1 << j)
        if solved:
            solved_problems_set.add(problem_id)

print(f'# UVa Problems by [OnlineJudge]({JUDGE_URL})')

for chapter in book_problems:
    print()
    print('##', chapter['title'])
    for sub_chapter in chapter['arr']:
        print()
        print('###', sub_chapter['title'])
        for category in sub_chapter['arr']:
            print()
            print(category[0])
            for problem_number in category[1:]:
                starred = '*' if problem_number < 0 else ''
                problem_number = abs(problem_number)
                problem = problems_by_number[problem_number]
                problem_id = problem[0]
                solved = 'x' if problem_id in solved_problems_set else ' '
                url = f'{JUDGE_URL}/index.php?option=com_onlinejudge&Itemid={8}&page=show_problem&problem={problem_id}'
                print(f'- [{solved}] {problem[2]}{starred} [url]({url})')
