
#ifndef MYORDERBOOK_ORDERLIST_H
#define MYORDERBOOK_ORDERLIST_H


#include <shared_mutex>
#include "../const.h"
#include "Order.h"
#include <iostream>

class order;

class OrderList;

using OrderListPointer = OrderList *;
using OrderPointer = order *;

class OrderList {
    std::unordered_map<OrderID, OrderPointer> unorderedMap;
    static bool instanceFlag;
    static OrderListPointer instance;
    static std::string tp;
    mutable std::shared_mutex mutex_;
public:
    static OrderListPointer getInstance() {
        if (!instanceFlag) {
            instance = new OrderList;
            instanceFlag = true;
            return instance;
        } else {
            return instance;
        }
    }


    OrderPointer getOrder(OrderID &orderId) const {
        std::shared_lock lock(mutex_);
        if (unorderedMap.find(orderId) == unorderedMap.end())
            return nullptr;
        return unorderedMap.at(orderId);
    }

    bool updateOrderInList(OrderPointer order, OrderID &orderId) {
        std::shared_lock lock(mutex_);
        unorderedMap[orderId] = order;
        return true;
    }


};


#endif //MYORDERBOOK_ORDERLIST_H
