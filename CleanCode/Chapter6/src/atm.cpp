#include "atm.h"

void ATM::init()
{
    server.connectToServer();
}

void ATM::start()
{
    init();
}

bool ATM::authenticateCard(Card *card, int pin)
{
    this->card = card;
    currentAccountId = server.validateAccount(card, pin);
    return true;
}

bool ATM::withdrawCash(int amount)
{
    if (amount > cashAvailable)
    {
        throw std::runtime_error("Insufficient cash in ATM.");
    }

    server.withdrawCash(currentAccountId, amount);
    cashAvailable -= amount;
    return true;
}
