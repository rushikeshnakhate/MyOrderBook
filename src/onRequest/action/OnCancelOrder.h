#ifndef MYORDERBOOK_ONCANCELORDER_H
#define MYORDERBOOK_ONCANCELORDER_H

#include "GetTransactionDriver.h"

class OnCancelOrder : public GetTransactionDriver {
    bool processTransaction(MesgTokens &tokens) override;

    bool validateRequest(MesgTokens &tokens, OrderListPointer pList) override;

};

#endif //MYORDERBOOK_ONCANCELORDER_H
