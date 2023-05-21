while True:
    months, down_payment, amount, m_records = input().strip().split()
    months = int(months)
    if months < 0:
        break
    down_payment = float(down_payment)
    amount = float(amount)
    m_records = int(m_records)

    records = []

    for _ in range(m_records):
        month_idx, depreciation = input().strip().split()
        month_idx = int(month_idx)
        depreciation = float(depreciation)
        records.append(( month_idx, depreciation ))

    def apply_depreciation (depreciation):
        return car_value * (1 - depreciation)

    def remaining_loan (month_idx):
        return (months - month_idx) * (amount / months)

    car_value = amount + down_payment
    record_idx = 0

    for month_idx in range(months + 1):
        if record_idx + 1 < len(records) and records[record_idx + 1][0] == month_idx:
            record_idx += 1
        car_value = apply_depreciation(records[record_idx][1])

        if remaining_loan(month_idx) < car_value:
            break

    print(month_idx, 'month' if month_idx == 1 else 'months')
