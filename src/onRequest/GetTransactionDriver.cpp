#include "action/GetTransactionDriver.h"
#include "action/OnNewOrder.h"
#include "action/OnReplaceOrder.h"
#include "action/OnCancelOrder.h"
#include "action/OnQuery.h"

bool OrderList::instanceFlag = false;
std::string OrderList::tp = "Rushi";
OrderListPointer OrderList::instance = nullptr;


GetTransactionDriver *GetTransactionDriver::getTransactionType(MessageType &messageType) {
    switch (static_cast<MessageType>(messageType)) {
        case MessageType::order:
            return new OnNewOrder();
        case MessageType::amend :
            return new OnReplaceOrder();
        case MessageType::cancel :
            return new OnCancelOrder();
        case MessageType::query :
            return new OnQuery();
        default:
            return nullptr;
    }

}