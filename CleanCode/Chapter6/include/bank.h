#ifndef __BANK_H__
#define __BANK_H__

#include "bankServer.h"
#include "bankDatabase.h"

class Bank
{
private:
    BankServer server;
    BankDatabase &database;

    Response validateCard(const ValidationData &validationData);

    Response withdrawCash(const WithdrawData &withdrawData);

public:
    Bank(BankDatabase &database);

    bool serveRequest();
};

#endif