# My Competitive Programming Solutions

👋 Hello!
This is a personal collection of solutions to competitive programming problems, it's mainly here for **archival** and **educational** purposes.

I have been coding these solutions since I originally started programming in **2016**, as a result you can expect a lot of code in this repository to be _rather bad_ and (hopefully) not a good representation of my current programming ability and style!

Most sub-directory contains a README cataloguing the list of problems and whether they were solved:

- [abc](./abc/README.md)
- [Advent of Code](./advent_of_code/README.md)
- [cses.fi](./cses/README.md)
- [dmoj.ca](./dmoj/README.md)
- [itoi](./itoi/README.md)
- [LuissMatics](./luissmatics/README.md)
- [oii](./oii/README.md)
- [ois](./ois/README.md)
- [olinfo](./olinfo/README.md)
- [usaco](./usaco/README.md)
- [uva](./uva/README.md)

## Generating the READMEs

Some of these lists were generated automatically, check out `tools/` to see what's available!

```bash
cd ./tools
# Create a virtualenv and install the dependencies
python -m venv .venv
source .venv/bin/activate
python -m pip install -r requirements.txt
# Run the tool, check out the source for details
python cses_parser.py < input.html
```
