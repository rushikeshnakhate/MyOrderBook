#include <iostream>
#include <algorithm>
#include <thread>
#include "Order.h"
#include "../onRequest/action/GetTransactionDriver.h"


bool Order::processOrder(MesgTokens &tokens) {
    if (tokens.empty()) {
        std::cout << "Message is Empty " << std::endl;
        return false;
    }

    MessageType type = MessageTypeFromReq::get(tokens[0]);


    GetTransactionDriver *pTransacation = GetTransactionDriver::getTransactionType(type);
    if (pTransacation != nullptr)
        pTransacation->processTransaction(tokens);
    else {
        std::cout << "Error: Invalid request type, received " << tokens[0] << std::endl;
        return false;
    }
    return true;
}
