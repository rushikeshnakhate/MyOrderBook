#ifndef MYORDERBOOK_ONREPLACEORDER_H
#define MYORDERBOOK_ONREPLACEORDER_H

#include "GetTransactionDriver.h"

class OnReplaceOrder : public GetTransactionDriver {
    virtual bool validateRequest(MesgTokens &tokens, OrderListPointer pList) override;

    bool processTransaction(MesgTokens &tokens) override;

};

#endif //MYORDERBOOK_ONREPLACEORDER_H
