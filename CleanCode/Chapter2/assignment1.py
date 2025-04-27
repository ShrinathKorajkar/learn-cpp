import random


class GuessNumberGame:
    def __init__(self):
        self.MIN_RANDOM_NUMBER = 1
        self.MAX_RANDOM_NUMBER = 100
        self.gameOver = False
        self.totalGuesses = 0

    def start(self):
        self.generateRandomNumber()
        self.guessedNumber = input("Guess a number between 1 and 100 : ")
        self.playUntillGameOver()

    def generateRandomNumber(self):
        self.randomNumber = random.randint(
            self.MIN_RANDOM_NUMBER, self.MAX_RANDOM_NUMBER)

    def playUntillGameOver(self):
        while not self.gameOver:
            self.validateInput()
            self.totalGuesses += 1
            self.guessedNumber = int(self.guessedNumber)
            self.printGuessedResult()

    def validateInput(self):
        while not self.validNumber():
            self.guessedNumber = input(
                "I wont count this one Please enter a number between 1 to 100 : ")

    def validNumber(self):
        return self.guessedNumber.isdigit() and self.inValidRange()

    def inValidRange(self):
        return self.MIN_RANDOM_NUMBER <= int(self.guessedNumber) <= self.MAX_RANDOM_NUMBER

    def printGuessedResult(self):
        if self.guessedNumber < self.randomNumber:
            self.guessedNumber = input("Too low. Guess again : ")
        elif self.guessedNumber > self.randomNumber:
            self.guessedNumber = input("Too High. Guess again : ")
        else:
            print("You guessed it in", self.totalGuesses, "guesses!")
            self.gameOver = True


def startGuessNumberGame():
    guessNumberGame = GuessNumberGame()
    guessNumberGame.start()


def main():
    startGuessNumberGame()


main()
