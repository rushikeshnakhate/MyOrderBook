#ifndef MYORDERBOOK_MESGQENGINE_H
#define MYORDERBOOK_MESGQENGINE_H

#include <mutex>
#include <condition_variable>
#include <queue>
#include <thread>
#include "../parsor/MesgParser.h"

using message = std::string;

class MesgQEngine {
    static std::queue<message> mq;
    static std::mutex mutex;
    static std::condition_variable cond_var;
    static bool notified;


public:


    MesgQEngine();

    ~MesgQEngine();

    static void onMessage(message &o);

    void worker();


};

#endif //MYORDERBOOK_MESGQENGINE_H
