def convertIntoArmstrongNumber(originalNumber):
    sum = 0
    noOfDigits = 0

    copyOfOriginalNum = originalNumber
    while copyOfOriginalNum > 0:
        noOfDigits = noOfDigits + 1
        copyOfOriginalNum = copyOfOriginalNum // 10

    copyOfOriginalNum = originalNumber
    for n in range(1, copyOfOriginalNum + 1):
        remainder = copyOfOriginalNum % 10
        sum = sum + (remainder ** noOfDigits)
        copyOfOriginalNum //= 10
    return sum


originalNumber = int(
    input("\nPlease Enter the Number to Check for Armstrong: "))

if (originalNumber == convertIntoArmstrongNumber(originalNumber)):
    print("\n%d is Armstrong Number.\n" % originalNumber)
else:
    print("\n%d is Not a Armstrong Number.\n" % originalNumber)
