//
// Created by ayush on 2/9/2020.
//

#ifndef MYORDERBOOK_ONQUERY_H
#define MYORDERBOOK_ONQUERY_H

#include "GetTransactionDriver.h"

class OnQuery : public GetTransactionDriver {
    bool processTransaction(MesgTokens &tokens) override;
    virtual bool validateRequest(MesgTokens &tokens, OrderListPointer pList) override  ;

};


#endif //MYORDERBOOK_ONQUERY_H
