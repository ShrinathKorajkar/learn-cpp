/*
    Chain of Responsibility Pattern: ->  Passes the request along a chain of handlers. Upon receiving a request,
    each handler decides either to process the request or to pass it to the next handler in the chain.
*/

#include <iostream>

// Handler interface
class TransactionHandler
{
public:
    virtual void handleRequest(int amount) = 0;
    virtual ~TransactionHandler() {}
    void setNextHandler(TransactionHandler *next)
    {
        nextHandler_ = next;
    }

protected:
    TransactionHandler *nextHandler_;

public:
    TransactionHandler() : nextHandler_(nullptr) {}
};

// Concrete Handlers
class WithdrawalHandler : public TransactionHandler
{
public:
    void handleRequest(int amount) override
    {
        if (amount <= 200)
        {
            std::cout << "Processing withdrawal of $" << amount << std::endl;
        }
        else if (nextHandler_)
        {
            nextHandler_->handleRequest(amount);
        }
        else
        {
            std::cout << "Transaction failed: Insufficient funds!" << std::endl;
        }
    }
};

class DepositHandler : public TransactionHandler
{
public:
    void handleRequest(int amount) override
    {
        if (amount > 0)
        {
            std::cout << "Processing deposit of $" << amount << std::endl;
        }
        else if (nextHandler_)
        {
            nextHandler_->handleRequest(amount);
        }
        else
        {
            std::cout << "Transaction failed: Invalid deposit amount!" << std::endl;
        }
    }
};

class BalanceInquiryHandler : public TransactionHandler
{
public:
    void handleRequest(int amount) override
    {
        if (amount == 0)
        {
            std::cout << "Checking account balance: $1000" << std::endl;
        }
        else if (nextHandler_)
        {
            nextHandler_->handleRequest(amount);
        }
        else
        {
            std::cout << "Transaction failed: Invalid request!" << std::endl;
        }
    }
};

int main()
{
    TransactionHandler *withdrawalHandler = new WithdrawalHandler();
    TransactionHandler *depositHandler = new DepositHandler();
    TransactionHandler *balanceInquiryHandler = new BalanceInquiryHandler();

    withdrawalHandler->setNextHandler(depositHandler);
    depositHandler->setNextHandler(balanceInquiryHandler);

    withdrawalHandler->handleRequest(150);
    withdrawalHandler->handleRequest(250);
    depositHandler->handleRequest(-100);
    balanceInquiryHandler->handleRequest(0);

    delete withdrawalHandler;
    delete depositHandler;
    delete balanceInquiryHandler;

    return 0;
}
