TOO_LOW = 'too low'
TOO_HIGH = 'too high'
RIGHT_ON = 'right on'
DISHONEST = 'Stan is dishonest'
HONEST = 'Stan may be honest'

def tc ():
    min_v, max_v = 1, 10
    is_cheating = False
    while True:
        guess = int(input().strip())
        if guess == 0:
            return None

        expected_response = None
        if guess < min_v:
            expected_response = TOO_LOW
        elif guess > max_v:
            expected_response = TOO_HIGH
        elif min_v == max_v:
            expected_response = RIGHT_ON

        response = input().strip()

        if expected_response is not None and response != expected_response:
            is_cheating = True

        if response == TOO_LOW:
            min_v = max(guess + 1, min_v)
        elif response == TOO_HIGH:
            max_v = min(guess - 1, max_v)
        else:
            break

    return is_cheating

while (is_cheating := tc()) is not None:
    print(DISHONEST if is_cheating else HONEST)
