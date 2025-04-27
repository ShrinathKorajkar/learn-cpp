#ifndef __NETWORK_MESSAGE_DEFINITIONS__
#define __NETWORK_MESSAGE_DEFINITIONS__

#include "bankAccount.h"

enum RequestType
{
    CARD_VALIDATION = 0,
    WITHDRAW
};

struct ValidationData
{
    Card card;
    int pin;
};

struct WithdrawData
{
    int accountNo;
    int amount;
};

union RequestData
{
    ValidationData validationData;
    WithdrawData withdrawData;
};

struct Request
{
    RequestType type;
    RequestData data;
};

enum ResponseStatus
{
    SUCCESS = 0,
    FAILURE,
    INVALID_CARD,
    INVALID_PIN,
    INSUFFICIENT_BALANCE,
    BLOCKED
};

struct Response
{
    ResponseStatus status;
    int data;
};

#endif