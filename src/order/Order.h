#ifndef MYORDERBOOK_ORDER_H
#define MYORDERBOOK_ORDER_H

#include <cstdint>
#include <cstddef>
#include <map>
#include <unordered_map>
#include <vector>
#include "../const.h"

#include "../message/MessageType.h"
#include "OrderList.h"


enum class BookType {
    buy, sell
};

enum class State {
    LIVE, ALLOCATED, PARTIAL_ALLOCATED, CXL, REJ
};

std::string getStateToString(State &state);

std::string getBookTypeToString(BookType &bookType);

struct order {
    OrderID orderId;
    Price price;
    Quantity quantity;
    Quantity leavesQuantity;
    BookType side;
    State state;
    SecurityID securityId;

    inline void updateQuantity(Quantity &newQuantity) {
        this->quantity = quantity + newQuantity;
        this->leavesQuantity = leavesQuantity + newQuantity;
    }


    inline bool cancelOrder() {
        if (state == State::CXL || state == State::ALLOCATED || state == State::REJ)
            return false;
        leavesQuantity = 0;
        return true;
    }


    inline void allocateOrder() {
        this->leavesQuantity = 0;
        this->state = State::ALLOCATED;
    }

    inline void partialAllocate(Quantity &allocQuantity) {
        this->leavesQuantity = this->leavesQuantity - allocQuantity;
        this->state = State::PARTIAL_ALLOCATED;
    }
};


using OrderPointer = order *;

class Order {
public:
    static bool processOrder(MesgTokens &tokens);

};


#endif //MYORDERBOOK_ORDER_H
