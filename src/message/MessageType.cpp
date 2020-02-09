#include "MessageType.h"

MessageType MessageTypeFromReq::get(RequestType &req) {

    if (req == "order")
        return MessageType::order;
    else if (req == "cancel")
        return MessageType::cancel;
    else if (req == "amend")
        return MessageType::amend;
    else if (req == "q")
        return MessageType::query;
    else
        return MessageType::invalid;

}
