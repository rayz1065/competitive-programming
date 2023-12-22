def message_match (message_route, table_entry):
    for x, y in zip(message_route, table_entry):
        if y != '*' and x != y:
            return False
    return True


def find_route (mta, country, admd, prmd, org_name, mtas):
    visited = {}
    while mta not in visited:
        visited[mta] = True
        found_mta = None
        for table_entry in mtas[mta]:
            if message_match((country, admd, prmd, org_name), table_entry[1:]):
                found_mta = table_entry[0]
                break

        if found_mta is None:
            return f'unable to route at {mta}'
        if found_mta == mta:
            return f'delivered to {mta}'
        mta = found_mta

    return f'circular routing detected by {mta}'


def ugly_input(amount):
    res = []
    while len(res) < amount:
        line = input().strip()
        res.extend(line.split())
    return res


def main ():
    tc = 0
    while True:
        try:
            n_mtas = int(ugly_input(1)[0])
        except EOFError:
            break
        except:
            break

        mtas = {}

        for _ in range(n_mtas):
            name, table_entries = ugly_input(2)
            table_entries = int(table_entries)
            mtas[name] = []

            for _ in range(table_entries):
                adj_mta, country, admd, prmd, org_name = ugly_input(5)
                mtas[name].append((adj_mta, country, admd, prmd, org_name))

        n_messages = int(input().strip())

        tc += 1
        print(f'Scenario # {tc}')

        for i in range(n_messages):
            mta, country, admd, prmd, org_name = ugly_input(5)

            try:
                res = find_route(mta, country, admd, prmd, org_name, mtas)
                print(f'{i + 1} -- {res}')
            except:
                pass
        print()


if __name__ == '__main__':
    main()
