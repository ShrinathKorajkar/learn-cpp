import random
RANDOM_UPPER_LIMIT = 100
RANDOM_LOWER_LIMIT = 1


def validNumber(userInput):
    if userInput.isdigit() and RANDOM_LOWER_LIMIT <= int(userInput) <= RANDOM_UPPER_LIMIT:
        return True
    else:
        return False


def main():
    randomNumber = random.randint(RANDOM_LOWER_LIMIT, RANDOM_UPPER_LIMIT)
    gameOver = False
    guessedNumber = input("Guess a number between 1 and 100 : ")
    totalGuesses = 0
    while not gameOver:
        if not validNumber(guessedNumber):
            guessedNumber = input(
                "I wont count this one Please enter a number between 1 to 100 : ")
            continue
        else:
            totalGuesses += 1
            guessedNumber = int(guessedNumber)

        if guessedNumber < randomNumber:
            guessedNumber = input("Too low. Guess again : ")
        elif guessedNumber > randomNumber:
            guessedNumber = input("Too High. Guess again : ")
        else:
            print("You guessed it in", totalGuesses, "guesses!")
            gameOver = True


main()
