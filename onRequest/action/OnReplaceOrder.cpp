
#include <thread>
#include "OnReplaceOrder.h"
#include "../../order/Order.h"

bool OnReplaceOrder::processTransaction(MesgTokens &tokens) {

    OrderListPointer listInstance = OrderList::getInstance();
    if (!validateRequest(tokens, listInstance)) return false;

    OrderID orderId = atol(tokens[static_cast<int>(amendOrderFieldIndex::OrderID)].c_str());
    OrderPointer pOrder = listInstance->getOrder(orderId);
    Quantity newQuantity = atol(tokens[static_cast<int>(amendOrderFieldIndex::Quantity)].c_str());

    pOrder->updateQuantity(newQuantity);
    std::cout << std::this_thread::get_id() << "  Amend->" << orderId << std::endl;

//    getAllocations(pOrder);

    return true;
}


bool OnReplaceOrder::validateRequest(MesgTokens &tokens, OrderListPointer pList) {
    if (tokens.empty()) return false;
    OrderID orderId = atol(tokens[static_cast<int>(amendOrderFieldIndex::OrderID)].c_str());
    if (pList->getOrder(orderId) == nullptr) {
        std::cout << std::this_thread::get_id() << "  OrderID " << orderId
                  << " does not exists in cache ,Reject->Amend->" << orderId << std::endl;
        return false;
    }

    OrderPointer pOrder = pList->getOrder(orderId);
    if (pOrder->state != State::LIVE && pOrder->state != State::PARTIAL_ALLOCATED) {
        std::cout << std::this_thread::get_id() << "  Order not in LIVE state ,Reject->Amend->" << orderId << std::endl;
        return false;
    }

    return true;
}
