#ifndef MYORDERBOOK_MESGPARSER_H
#define MYORDERBOOK_MESGPARSER_H


#include "../const.h"

using message = std::string;
const char MessageDelimeter = ' ';

class MesgParser {
public:
    MesgTokens getMessageToken(message &notification);

    std::vector<std::string> Tokenizer(message &notification, const char delimiter);
};


#endif //MYORDERBOOK_MESGPARSER_H
