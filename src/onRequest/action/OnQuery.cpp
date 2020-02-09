#include <thread>
#include "OnQuery.h"
#include "../../order/Order.h"

bool OnQuery::processTransaction(MesgTokens &tokens) {
    OrderListPointer listInstance = OrderList::getInstance();
    OrderID orderId = atol(tokens[static_cast<int>(queryOrderFieldIndex::OrderID)].c_str());
    if (!validateRequest(tokens, listInstance)) return false;

    OrderPointer pOrder = listInstance->getOrder(orderId);

    std::cout << std::this_thread::get_id() << "  Below is result for your query on OrderID:" << orderId << " Side:"
              << getBookTypeToString(pOrder->side)
              << " Price:"
              << pOrder->price << " Quantity:" << pOrder->quantity
              << " State:" << getStateToString(pOrder->state) << " LeavesQuantity:" << pOrder->leavesQuantity
              << std::endl;

    return true;
}

bool OnQuery::validateRequest(MesgTokens &tokens, OrderListPointer pList) {
    if (tokens.empty()) return false;

    OrderID orderId = atol(tokens[static_cast<int>(queryOrderFieldIndex::OrderID)].c_str());

    if (pList->getOrder(orderId) == nullptr) {
        std::cout << std::this_thread::get_id() << "  OrderID " << orderId
                  << " does not exists in cache"
                  << "  Ignore->Query->OrderId " << orderId << std::endl;
        return false;
    }
    return true;
}
