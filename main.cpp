#include <iostream>
#include "mqEngine/MesgQEngine.h"


int main() {
//    std::string message = "order 1001 buy 100 10";
//    std::string message1 = "order 1002 buy 100 20";
//    std::string message2 = "order 1003 buy 100 12.30";
//    std::string message3 = "order 1004 sell 100 10";
//    std::string message4 = "order 1005 sell 100 12.30";
//    std::string message5 = "order 1006 sell 100 12.30";
//    std::string query = "q order 1001 600";

    try {
        MesgQEngine init;
        std::string message;
        std::thread consumer(&MesgQEngine::worker, MesgQEngine());
        std::this_thread::sleep_for(std::chrono::seconds(2));
        while (1) {
            std::cout << "Please pride your query" << std::endl;
            std::cin >> message;
            MesgQEngine::onMessage(message);
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

    }
    catch (...) {
        std::cout << "Error:un-handled exception " << __FILE__ << ":" << __LINE__ << std::endl;
    }
    return 0;
}
