#ifndef MYORDERBOOK_GETTRANSACTIONDRIVER_H
#define MYORDERBOOK_GETTRANSACTIONDRIVER_H

#include <string>
#include "../../const.h"
#include "../../message/MessageType.h"
#include "../../order/OrderList.h"
#include "../maching/maching.h"


class GetTransactionDriver {

public:
    static GetTransactionDriver *getTransactionType(MessageType &messageType);

    virtual bool processTransaction(MesgTokens &tokens) = 0;

    virtual bool validateRequest(MesgTokens &tokens, OrderListPointer pList) = 0;

    virtual  ~GetTransactionDriver() = default;;

};


#endif //MYORDERBOOK_GETTRANSACTIONDRIVER_H
