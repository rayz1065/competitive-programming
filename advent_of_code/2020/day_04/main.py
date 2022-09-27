import re

fields = ['byr', 'iyr', 'eyr', 'hgt', 'hcl', 'ecl', 'pid', 'cid']
requiredFields = ['byr', 'iyr', 'eyr', 'hgt', 'hcl', 'ecl', 'pid']

def inputData():
    data = []

    currPass = dict()
    try:
        while True:
            line = input()
            if len(line) == 0:
                data.append(currPass)
                currPass = dict()
            else:
                flds = line.split(' ')
                for field in flds:
                    name, value = field.split(':')
                    currPass[name] = value
    except EOFError:
        pass

    data.append(currPass)
    return data

def part1(data):
    s = 0
    for d in data:
        for key in requiredFields:
            if not key in d:
                break
        else:
            s+= 1
    return s

def isPassValid(passport):
    for key in requiredFields:
        if not key in passport:
            return False
    
    byr = int(passport['byr'])
    iyr = int(passport['iyr'])
    eyr = int(passport['eyr'])
    hgtGroups = re.fullmatch(r'(\d+)([a-z]+)', passport['hgt'])
    if hgtGroups == None:
        return False
    hgt, hgtUnit = hgtGroups.groups()
    hgt = int(hgt)
    hcl = passport['hcl']
    ecl = passport['ecl']
    pid = passport['pid']

    if byr < 1920 or byr > 2002:
        return False
    if iyr < 2010 or iyr > 2020:
        return False
    if eyr < 2020 or eyr > 2030:
        return False
    if hgtUnit == 'cm' and (hgt < 150 or hgt > 193):
        return False
    if hgtUnit == 'in' and (hgt < 59 or hgt > 76):
        return False
    if re.fullmatch(r'#[a-z0-9]{6}', hcl) == None:
        return False
    if ecl not in ['amb', 'blu', 'brn', 'gry', 'grn', 'hzl', 'oth']:
        return False
    if re.fullmatch(r'[\d]{9}', pid) == None:
        return False
    return True

def part2(data):
    s = 0
    for d in data:
        if isPassValid(d):
            s+= 1
    return s

def main():
    data = inputData()
    print("1)", part1(data))
    print("2)", part2(data))

if __name__ == "__main__":
    main()