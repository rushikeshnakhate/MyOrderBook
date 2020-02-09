#include <thread>
#include "maching.h"

static Node *buyTree = nullptr;
static Node *SellTree = nullptr;
Node *BuyRoot = nullptr;
Node *sellRoot = nullptr;
const int FOUND_ONE_ORDER = 1;

bool createTrade(OrderPointer oppositeOrder, OrderPointer order) {
    if (oppositeOrder->quantity == order->quantity) {
        oppositeOrder->allocateOrder();
        order->allocateOrder();

    } else if (oppositeOrder->quantity > order->quantity) {
        oppositeOrder->partialAllocate(order->quantity);
        order->allocateOrder();
    } else {
        oppositeOrder->allocateOrder();
        order->partialAllocate(oppositeOrder->quantity);
    }

    std::cout << std::this_thread::get_id() << "  Allocated OrderId:" << order->orderId << " Quantity:"
              << order->quantity << " LeavesQuantity:"
              << order->leavesQuantity << " Price:" << order->price << " State:" << getStateToString(order->state)
              << std::endl;
    std::cout << std::this_thread::get_id() << "  Opposite  OrderId << " << oppositeOrder->orderId << " Quantity:"
              << oppositeOrder->quantity
              << " LeavesQuantity:"
              << oppositeOrder->leavesQuantity << " Price:" << oppositeOrder->price << " State:"
              << getStateToString(oppositeOrder->state) << std::endl;

    return true;
}


bool matchTrade(Node *oppositeOrder, OrderPointer order) {
    OrderListPointer listInstance = OrderList::getInstance();

    if (oppositeOrder->count == FOUND_ONE_ORDER) {
        OrderID oppositeOrderId = oppositeOrder->orderIdList[0];
        OrderPointer opOrder = listInstance->getOrder(oppositeOrderId);
        if (opOrder != nullptr) {
            return createTrade(opOrder, order);
        } else {
            std::cout << "Error:opposite order " << oppositeOrderId << "does not exists in cache" << std::endl;
        }
    }
}

bool processBuy(OrderPointer order) {
    BuyRoot = insert(BuyRoot, order->price, order->orderId);
    if (sellRoot == nullptr)
        return true;
    Node *bestOffer = minValueNode(sellRoot);
    if (bestOffer != nullptr) {
        if (order->price >= bestOffer->price) {
            matchTrade(bestOffer, order);
        }
    }
}

bool processSell(OrderPointer order) {
    sellRoot = insert(sellRoot, order->price, order->orderId);
    Node *bestBid = maxValueNode(BuyRoot);
    if (bestBid != nullptr) {
        if (order->price >= bestBid->price) {
            matchTrade(bestBid, order);
        }
    }
}

bool getAllocation(OrderPointer order) {
    if (order->side == BookType::sell)
        processSell(order);
    else
        processBuy(order);
}

