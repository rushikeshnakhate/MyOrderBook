#include <string>
#include "order/Order.h"

namespace OrderSide {
    std::string buy = "buy";
    std::string sell = "sell";
}

namespace OrderState {
    std::string live = "LIVE";
    std::string allocated = "ALLOCATED";
    std::string partial_allocated = "PARTIAL_ALLOCATED";
    std::string cancelled = "CXL";
    std::string rejected = "REJ";

}

std::string getStateToString(State &state) {
    if (state == State::LIVE)
        return OrderState::live;
    else if (state == State::ALLOCATED)
        return OrderState::allocated;
    else if (state == State::PARTIAL_ALLOCATED)
        return OrderState::partial_allocated;
    else if (state == State::CXL)
        return OrderState::cancelled;
    else if (state == State::REJ)
        return OrderState::rejected;
    else return " ";
}

std::string getBookTypeToString(BookType &bookType) {
    if (bookType == BookType::buy)
        return OrderSide::buy;
    if (bookType == BookType::sell)
        return OrderSide::sell;
}

