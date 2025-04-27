#ifndef __BANK_ACCOUNT_H__
#define __BANK_ACCOUNT_H__

#include <iostream>

struct Date
{
    int day;
    int month;
    int year;
};

struct Card
{
    int cardNumber;
    Date expiryDate;
    bool isBlocked;
    int noOfPinAttempts;
    Card() = default;
    Card(int cardNumber, Date expiryDate) : cardNumber(cardNumber), expiryDate(expiryDate), isBlocked(false), noOfPinAttempts(0) {}
};

struct Account
{
    int accountID;
    std::string name;
    double balance;
    int debitCardPin;
    Card debitCard;

    Account() = default;

    Account(int id, std::string name, double balance, int cardNo, int expDay, int expMonth, int expYear, int pin)
        : accountID(id), name(name), balance(balance), debitCardPin(pin), debitCard(cardNo, {expDay, expMonth, expYear})
    {
    }
};

#endif