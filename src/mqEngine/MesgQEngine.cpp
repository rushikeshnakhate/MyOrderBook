#include <iostream>
#include "MesgQEngine.h"
#include "../onRequest/action/GetTransactionDriver.h"
#include "../order/Order.h"

bool MesgQEngine::notified = false;
std::queue<message> MesgQEngine::mq;
std::mutex MesgQEngine::mutex;
std::condition_variable MesgQEngine::cond_var;
const int PROCESS_RUNNING = 1;

MesgQEngine::MesgQEngine() = default;

MesgQEngine::~MesgQEngine() = default;


void MesgQEngine::onMessage(message &notification) {
    try {
//        std::cout << std::this_thread::get_id() << "  received message in Q=>" << notification << std::endl;
        std::lock_guard<std::mutex> lock(MesgQEngine::mutex);
        mq.push(notification);
        MesgQEngine::notified = true;
        MesgQEngine::cond_var.notify_one();
    }
    catch (...) {
        std::cout << "Error:un-handled exception " << __FILE__ << ":" << __LINE__ << std::endl;
    }
}


void MesgQEngine::worker() {

    while (PROCESS_RUNNING) {
        try {
            std::string consumer;
            std::unique_lock<std::mutex> lock(MesgQEngine::mutex);
            {
                while (!MesgQEngine::notified) {
//                    std::cout << std::this_thread::get_id() << "  waiting for next  message..." << std::endl;
                    MesgQEngine::cond_var.wait(lock);
                }

                if (!mq.empty()) {
                    consumer = mq.front();
                    mq.pop();
                    MesgQEngine::notified = false;
                }
            }
            std::unique_ptr<MesgParser> pMesgParser = std::make_unique<MesgParser>();
            MesgTokens tokens = pMesgParser->getMessageToken(consumer);
            std::unique_ptr<Order> pOrder = std::make_unique<Order>();
            pOrder->processOrder(tokens);
//            std::cout << std::this_thread::get_id() << "  processing completed for message " << consumer << std::endl;
        }
        catch ( std::exception & e ) {
            std::cout << "Error:found exception " <<e.what() << ":"<<  __FILE__ << ":" << __LINE__ << std::endl;
        }
        catch (...) {
            std::cout << "Error:un-handled exception " << __FILE__ << ":" << __LINE__ << std::endl;

        }

    }
}



