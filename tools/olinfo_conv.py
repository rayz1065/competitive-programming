import json
import sys

res = json.load(sys.stdin)
if 'tasks' in res:
    res = res['tasks']
for problem in res:
    url = f"https://training.olinfo.it/#/task/{problem['name']}/statement"
    score = 'x' if 'score' in problem and problem['score'] == 100 else ' '
    print(f"- [{score}] {problem['title']} ({problem['name']}) [url]({url})")
