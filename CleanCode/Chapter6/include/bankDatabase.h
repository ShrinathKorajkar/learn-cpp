#ifndef __BANK_DATABASE_H__
#define __BANK_DATABASE_H__

#include "bankAccount.h"
#include "networkMsgs.h"

#include <fstream>

class BankDatabase
{
private:
    std::fstream file;
    std::string filepath = "./database/database.bin";
    std::streampos fileEndPos = 0;

    Account getNextAccountData();

public:
    BankDatabase() = default;
    ~BankDatabase();

    void connect();

    std::tuple<ResponseStatus, int> validateCard(const Card &card, const int &pin);
    ResponseStatus withdrawAmount(const int &accountNo, const int &amount);

    void addAccount(const Account &newAccount);
    void printAccountDetails(const Account &account);
};

#endif