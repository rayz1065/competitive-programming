import json
import sys

res = json.load(sys.stdin)
if 'tasks' in res:
    res = res['tasks']
for problem in res:
    print(f"- [ ] {problem['title']} ({problem['name']}) [url]({problem['link']})")
