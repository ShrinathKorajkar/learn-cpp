#include "bankDatabase.h"

Account BankDatabase::getNextAccountData()
{
    Account account;
    file.read(reinterpret_cast<char *>(&account.accountID), sizeof(Account::accountID));

    int nameLength = 0;
    file.read(reinterpret_cast<char *>(&nameLength), sizeof(nameLength));

    char *nameBuffer = new char[nameLength + 1]; // +1 for null terminator
    file.read(nameBuffer, nameLength);
    nameBuffer[nameLength] = '\0'; // Null-terminate the string
    account.name = std::string(nameBuffer);
    delete[] nameBuffer;

    file.read(reinterpret_cast<char *>(&account.balance), sizeof(Account::balance));
    file.read(reinterpret_cast<char *>(&account.debitCard), sizeof(Card));
    file.read(reinterpret_cast<char *>(&account.debitCardPin), sizeof(Account::debitCardPin));

    return account;
}

void BankDatabase::connect()
{
    file.open(filepath.c_str(), std::ios::binary | std::ios::in | std::ios::out);
    if (!file)
    {
        throw std::runtime_error("Error connecting to database");
    }

    file.seekg(0, std::ios::end);
    fileEndPos = file.tellg();
}

std::tuple<ResponseStatus, int> BankDatabase::validateCard(const Card &card, const int &pin)
{
    bool status = false;
    Account account;

    file.seekg(0);

    while (file.tellg() < fileEndPos && !file.eof())
    {
        account = getNextAccountData();
        if (account.debitCard.cardNumber == card.cardNumber)
        {
            status = account.debitCardPin == pin;
            break;
        }
    }

    if (file.tellg() >= fileEndPos)
    {
        return {INVALID_CARD, -1};
    }

    if (account.debitCard.isBlocked)
    {
        return {BLOCKED, -1};
    }

    if (status == false)
    {
        account.debitCard.noOfPinAttempts++;
        if (account.debitCard.noOfPinAttempts > 3)
        {
            account.debitCard.isBlocked = true;
            return {BLOCKED, -1};
        }

        return {INVALID_PIN, -1};
    }

    account.debitCard.noOfPinAttempts = 0;

    return {SUCCESS, account.accountID};
}

ResponseStatus BankDatabase::withdrawAmount(const int &accountNo, const int &amount)
{
    Account account;

    file.seekg(0);
    std::streampos previousAccountPos = file.tellg();

    while (file.tellg() < fileEndPos && !file.eof())
    {
        previousAccountPos = file.tellg();
        account = getNextAccountData();
        if (account.accountID == accountNo)
        {
            break;
        }
    }

    if (account.balance < amount)
    {
        return INSUFFICIENT_BALANCE;
    }
    account.balance -= amount;

    file.seekg(previousAccountPos);
    addAccount(account);

    return SUCCESS;
}

void BankDatabase::addAccount(const Account &newAccount)
{
    file.write(reinterpret_cast<const char *>(&newAccount.accountID), sizeof(Account::accountID));
    int nameLength = newAccount.name.length();
    file.write(reinterpret_cast<const char *>(&nameLength), sizeof(nameLength));
    file.write(newAccount.name.c_str(), nameLength);
    file.write(reinterpret_cast<const char *>(&newAccount.balance), sizeof(Account::balance));
    file.write(reinterpret_cast<const char *>(&newAccount.debitCard), sizeof(Card));
    file.write(reinterpret_cast<const char *>(&newAccount.debitCardPin), sizeof(Account::debitCardPin));
}

void BankDatabase::printAccountDetails(const Account &account)
{
    std::cout << "ID : " << account.accountID << std::endl
              << "Name : " << account.name << std::endl
              << "Balance : " << account.balance << std::endl
              << "card no : " << account.debitCard.cardNumber << std::endl
              << "Card expiry day : " << account.debitCard.expiryDate.day << std::endl
              << "month : " << account.debitCard.expiryDate.month << std::endl
              << "year : " << account.debitCard.expiryDate.year << std::endl
              << "Pin : " << account.debitCardPin << std::endl;
}

BankDatabase::~BankDatabase()
{
    if (file)
    {
        file.close();
    }
}
