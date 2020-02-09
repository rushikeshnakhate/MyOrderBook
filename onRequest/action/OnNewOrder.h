#ifndef MYORDERBOOK_ONNEWORDER_H
#define MYORDERBOOK_ONNEWORDER_H

#include "GetTransactionDriver.h"
#include "../../order/Order.h"

class OnNewOrder : public GetTransactionDriver {
//    static Matching matching;
public:
    bool processTransaction(MesgTokens &tokens) override;

    virtual bool validateRequest(MesgTokens &tokens, OrderListPointer pList) override;

    OrderPointer createNewOrder(OrderID &orderId, MesgTokens &tokens);
};

#endif //MYORDERBOOK_ONNEWORDER_H
