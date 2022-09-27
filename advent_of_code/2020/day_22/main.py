import itertools

class Player:
    cards: list

    def __init__(self, cards):
        self.cards = cards.copy()

    def getScore(self):
        return sum((i + 1)*card for i, card in enumerate(reversed(self.cards)))

    def drawTopCard(self):
        card = self.cards[0]
        self.cards.pop(0)
        return card

    def topCard(self):
        return self.cards[0]

    def undoDraw(self, card):
        self.cards.insert(0, card)
    
    def addCards(self, cardsToAdd: list):
        self.cards.extend(cardsToAdd)
    
    def undoAddCards(self):
        self.cards.pop()
        self.cards.pop()

    def copy(self):
        return Player(self.cards.copy())

    def withCards(self, am):
        return Player(self.cards[0:am])

def inputData():
    player1Cards = []
    player2Cards = []

    assert(input() == "Player 1:")
    while (line := input()) != '':
        player1Cards.append(int(line))
    assert(input() == "Player 2:")

    try:
        while True:
            player2Cards.append(int(input()))
    except EOFError:
        pass
    return (player1Cards, player2Cards)

def simulateRound1(player1, player2):
    card1 = player1.drawTopCard()
    card2 = player2.drawTopCard()
    assert(card1 != card2)
    if card1 > card2:
        player1.addCards([card1, card2])
    else:
        player2.addCards([card2, card1])
    return min(len(player1.cards), len(player2.cards)) > 0

def part1(player1, player2):
    while simulateRound1(player1, player2):
        pass
    if len(player1.cards) == 0:
        return player2.getScore()
    else:
        return player1.getScore()


def simulateRound2(player1, player2):
    card1, card2 = player1.drawTopCard(), player2.drawTopCard()
    if card1 > len(player1.cards) or card2 > len(player2.cards):
        assert(card1 != card2)
        if card1 > card2:
            winner = '1'
        else:
            winner = '2'
    else:
        winner = recursiveBattle(player1.withCards(card1), player2.withCards(card2))

    if winner == '1':
        player1.addCards([card1, card2])
    else:
        player2.addCards([card2, card1])
    return winner

def recursiveBattle(player1, player2, f = False):
    foundGames = {}
    # print('recursive battle...', (player1.cards, player2.cards))
    while min(len(player1.cards), len(player2.cards)) > 0:
        gameState = (tuple(player1.cards), tuple(player2.cards))
        # if f:
        #     print('game state', gameState)
        if foundGames.get(gameState, None) != None:
            return '1'
        foundGames[gameState] = True
        simulateRound2(player1, player2)
    # print(len(player1.cards), len(player2.cards), player1.cards, player2.cards, foundGames)
    
    # print('return winner...', (player1.cards, player2.cards))
    if f:
        if len(player1.cards) > 0:
            return player1.cards
        return player2.cards
    if len(player1.cards) == 0:
        return '2'
    if len(player2.cards) == 0:
        return '1'
    assert(False)

def part2(player1, player2):
    winnerCards = recursiveBattle(player1, player2, True)
    # print('winning cards:', winnerCards)
    return Player(winnerCards).getScore()

def main():
    player1Cards, player2Cards = inputData()
    player1 = Player(player1Cards)
    player2 = Player(player2Cards)
    print("1)", part1(player1.copy(), player2.copy()))
    print("2)", part2(player1.copy(), player2.copy()))

if __name__ == "__main__":
    main()