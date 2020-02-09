#include <thread>
#include "OnCancelOrder.h"
#include "../../order/Order.h"

bool OnCancelOrder::processTransaction(MesgTokens &tokens) {

    OrderListPointer listInstance = OrderList::getInstance();

    if (!validateRequest(tokens, listInstance)) return false;

    OrderID orderId = atol(tokens[static_cast<int>(NewOrderFieldIndex::OrderID)].c_str());

    OrderPointer pOrder = listInstance->getOrder(orderId);
    if (pOrder->state != State::LIVE && pOrder->state != State::PARTIAL_ALLOCATED) {
        std::cout << std::this_thread::get_id() << "  Order not in LIVE state,Current Order State "
                  << getStateToString(pOrder->state)
                  << " Reject->Cancel->" << orderId
                  << std::endl;
        return false;
    }

    pOrder->updateState(State::CXL);
    std::cout << std::this_thread::get_id() << "  Canceled->" << orderId << std::endl;


    return true;
}


bool OnCancelOrder::validateRequest(MesgTokens &tokens, OrderListPointer pList) {
    if (tokens.empty()) return false;
    OrderID orderId = atol(tokens[static_cast<int>(cancelOrderFieldIndex::OrderID)].c_str());
    if (pList->getOrder(orderId) == nullptr) {
        std::cout << std::this_thread::get_id() << "  OrderID " << orderId
                  << " does not exists in cache ,Reject->Cancel->" << orderId << std::endl;
        return false;
    }
    return true;
}
