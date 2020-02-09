cmake_minimum_required(VERSION 3.15)
project(MyOrderBook)

set(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_FLAGS -pthread)
add_executable(MyOrderBook main.cpp order/Order.cpp order/Order.h onRequest/GetTransactionDriver.cpp onRequest/action/GetTransactionDriver.h onRequest/action/OnNewOrder.cpp onRequest/action/OnNewOrder.h onRequest/action/OnReplaceOrder.h onRequest/action/OnCancelOrder.h onRequest/action/OnReplaceOrder.cpp onRequest/action/OnCancelOrder.cpp message/MessageType.h mqEngine/MesgQEngine.cpp mqEngine/MesgQEngine.h parsor/MesgParser.h parsor/MesgParser.cpp const.h message/MessageType.cpp order/OrderList.h onRequest/action/OnQuery.cpp onRequest/action/OnQuery.h utils.cpp onRequest/maching/node.cpp onRequest/maching/node.h onRequest/maching/maching.cpp onRequest/maching/maching.h)