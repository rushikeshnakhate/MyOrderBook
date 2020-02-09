#include <iostream>
#include <thread>
#include <vector>
#include <sstream>
#include "MesgParser.h"

MesgTokens MesgParser::getMessageToken(message &notification) {
//    std::cout << std::this_thread::get_id() << "  parsing message  " << notification << std::endl;
    return (Tokenizer(notification, MessageDelimeter));
}

std::vector<std::string> MesgParser::Tokenizer(message &notification, const char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream notif(notification);
    std::string token;
    while (std::getline(notif, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}