
#include "bank.h"

Response Bank::validateCard(const ValidationData &validationData)
{
    Response response;
    std::tuple<ResponseStatus, int> validationStatus;

    validationStatus = database.validateCard(validationData.card, validationData.pin);

    response.status = std::get<0>(validationStatus);
    response.data = std::get<1>(validationStatus);
    return response;
}

Response Bank::withdrawCash(const WithdrawData &withdrawData)
{
    Response response;
    response.data = withdrawData.accountNo;
    response.status = database.withdrawAmount(withdrawData.accountNo, withdrawData.amount);
    return response;
}

Bank::Bank(BankDatabase &database) : database(database)
{
    database.connect();
    server.start();
}

bool Bank::serveRequest()
{
    while (1)
    {
        try
        {
            Request request = server.getNextRequest();
            Response response;

            switch (request.type)
            {
            case CARD_VALIDATION:
                response = validateCard(request.data.validationData);
                break;
            case WITHDRAW:
                response = withdrawCash(request.data.withdrawData);
                break;
            }
            server.sendResponseToClient(response);
        }
        catch (std::runtime_error &e)
        {
            break;
        }
    }
    return true;
}
