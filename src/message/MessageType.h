#ifndef MYORDERBOOK_MESSAGETYPE_H
#define MYORDERBOOK_MESSAGETYPE_H


#include "../const.h"

enum class MessageType {
    order, cancel, amend, query, invalid
};

enum class NewOrderFieldIndex {
    OrderTpe, OrderID, Side, Quantity, Price
};

enum class cancelOrderFieldIndex {
    OrderTpe, OrderID
};

enum class amendOrderFieldIndex {
    OrderTpe, OrderID, Quantity
};

enum class queryOrderFieldIndex {
    query, OrderType, OrderID
};

struct MessageTypeFromReq {
    static MessageType get(RequestType &req);

};

#endif //MYORDERBOOK_MESSAGETYPE_H
