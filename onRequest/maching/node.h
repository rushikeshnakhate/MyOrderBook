#ifndef MYORDERBOOK_NODE_H
#define MYORDERBOOK_NODE_H

#include "../../const.h"

struct Node {
    Price price;
    std::vector<OrderID> orderIdList;
    Node *left;
    Node *right;
    int height;
    int count;
};

int max(int a, int b);

Node *newNode(Price &price, OrderID &orderId);

Node *rightRotate(Node *y);

Node *leftRotate(Node *x);

int getBalance(Node *N);

Node *insert(Node *node, Price &price, OrderID &orderId);

Node *minValueNode(Node *node);

//Node *maxValueNode(Node *node);

Node *deleteNode(Node *root, Price &price);

Node* getBestBidOfferUsingPostOrder(Node *root);

#endif //MYORDERBOOK_NODE_H

