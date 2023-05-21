import re
from collections import OrderedDict

ACCOUNT_NAME_LENGTH = len('xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx')
AMOUNT_LENGTH = len('vvvvvvv.vv')


def read_input ():
    while True:
        line = input().strip()
        if line.startswith('000'):
            break
        yield line


def read_accounts ():
    accounts = {}
    for line in read_input():
        match = re.match(r'^(\d{3})(.+)$', line)
        number, name = match.groups()
        accounts[number] = name
    return accounts


def read_transactions ():
    # note: python3.5
    transactions = OrderedDict()
    for line in read_input():
        match = re.match(r'^(\d{3})(\d{3})\s+(-?\d+)$', line)
        seq_number, account_number, amount = match.groups()
        amount = int(amount)
        transactions.setdefault(seq_number, [])
        transactions[seq_number].append((account_number, amount))
    return transactions



def main ():
    accounts = read_accounts()
    transactions = read_transactions()
    accounts['999'] = 'Out of Balance'

    for seq_number, sub_transactions in transactions.items():
        total = sum(amount for _, amount in sub_transactions)
        if total == 0:
            continue

        sub_transactions.append(('999', -total))
        print(f'*** Transaction {seq_number} is out of balance ***')
        for account_id, amount in sub_transactions:
            account = accounts[account_id].ljust(ACCOUNT_NAME_LENGTH)
            sign = '-' if amount < 0 else ''
            cents = str(abs(amount) % 100).rjust(2, '0')
            amount = f'{sign}{abs(amount) // 100}.{cents}'.rjust(AMOUNT_LENGTH)
            print(f'{account_id} {account} {amount}')
        print()


if __name__ == '__main__':
    main()
