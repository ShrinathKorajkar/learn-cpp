#ifndef __ATM_H__
#define __ATM_H__

#include "atmServer.h"

class ATM
{
private:
    ATMServer server;
    Card *card;
    int currentAccountId = 0;
    double cashAvailable = 100000;

    void init();

public:
    void start();

    bool authenticateCard(Card *card, int pin);

    bool withdrawCash(int amount);
};

#endif