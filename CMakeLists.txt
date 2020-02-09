cmake_minimum_required(VERSION 3.15)
project(MyOrderBook)

set(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_FLAGS -pthread)

add_executable(MyOrderBook main.cpp src/order/Order.cpp src/order/Order.h src/onRequest/GetTransactionDriver.cpp src/onRequest/action/GetTransactionDriver.h src/onRequest/action/OnNewOrder.cpp src/onRequest/action/OnNewOrder.h src/onRequest/action/OnReplaceOrder.h src/onRequest/action/OnCancelOrder.h src/onRequest/action/OnReplaceOrder.cpp src/onRequest/action/OnCancelOrder.cpp src/message/MessageType.h src/mqEngine/MesgQEngine.cpp src/mqEngine/MesgQEngine.h src/parsor/MesgParser.h src/parsor/MesgParser.cpp src/const.h src/message/MessageType.cpp src/order/OrderList.h src/onRequest/action/OnQuery.cpp src/onRequest/action/OnQuery.h src/utils.cpp src/onRequest/maching/node.cpp src/onRequest/maching/node.h src/onRequest/maching/maching.cpp src/onRequest/maching/maching.h Tests/unitTests/TestNew.cpp)