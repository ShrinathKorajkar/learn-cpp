import random


def rollDice(totalSidesOfDice):
    return random.randint(1, totalSidesOfDice)


def startDiceGame():
    totalSidesOfDice = 6
    readyToRoll = True
    while readyToRoll:
        userInput = input("Ready to roll? Enter Q to Quit : ")
        if userInput.lower() != "q":
            diceResult = rollDice(totalSidesOfDice)
            print("You have rolled a", diceResult)
        else:
            readyToRoll = False


startDiceGame()
