#include <algorithm>
#include <thread>
#include "OnNewOrder.h"
#include "../../order/Order.h"
#include "../maching/maching.h"

namespace orderToken {
    std::string buy = "buy";
    std::string sell = "sell";
}


bool OnNewOrder::processTransaction(MesgTokens &tokens) {
    OrderListPointer listInstance = OrderList::getInstance();
    if (!validateRequest(tokens, listInstance)) return false;
    OrderID orderId = atol(tokens[static_cast<int>(NewOrderFieldIndex::OrderID)].c_str());
    OrderPointer newOrder = createNewOrder(orderId, tokens);
    listInstance->updateOrderInList(newOrder, newOrder->orderId);

    getAllocation(newOrder);

}

OrderPointer OnNewOrder::createNewOrder(OrderID &orderId, MesgTokens &tokens) {
    try {

        auto *newOrder = new order;
        Side side = tokens[static_cast<int>(NewOrderFieldIndex::Side)];
        newOrder->orderId = orderId;
        newOrder->side = ((side == orderToken::buy) ? BookType::buy : BookType::sell);
        newOrder->price = atof(tokens[static_cast<int>(NewOrderFieldIndex::Price)].c_str());
        newOrder->quantity = atol(tokens[static_cast<int>(NewOrderFieldIndex::Quantity)].c_str());
        newOrder->leavesQuantity = atol(tokens[static_cast<int>(NewOrderFieldIndex::Quantity)].c_str());
        newOrder->state = State::LIVE;

        std::cout << std::this_thread::get_id() << "  create cache OrderID:" << orderId << " Side:"
                  << getBookTypeToString(newOrder->side)
                  << " Price:" << newOrder->price
                  << " Quantity:" << newOrder->quantity
                  << " LeavesQuantity:" << newOrder->leavesQuantity
                  << " State:" << getStateToString(newOrder->state) << std::endl;
        return newOrder;
    }
    catch (std::exception &e) {
        std::cout << "Error:found exception " << e.what() << ":" << __FILE__ << ":" << __LINE__ << std::endl;
        return nullptr;
    }
    catch (...) {
        std::cout << "Error:un-handled exception " << __FILE__ << ":" << __LINE__ << std::endl;
        return nullptr;
    }

}


bool OnNewOrder::validateRequest(MesgTokens &tokens, OrderListPointer pList) {
    if (tokens.empty()) return false;

    OrderID orderId = atol(tokens[static_cast<int>(NewOrderFieldIndex::OrderID)].c_str());

    if (pList->getOrder(orderId) != nullptr) {
        std::cout << std::this_thread::get_id() << "  OrderID " << orderId
                  << " already exists in cache ,ignore this request now " << std::endl;
        return false;
    }
    return true;
}