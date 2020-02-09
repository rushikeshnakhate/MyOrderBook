#include <iostream>
#include "node.h"


int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(struct Node *N) {
    if (N == nullptr)
        return 0;
    return N->height;
}

Node *newNode(Price &price, OrderID &orderId) {
    Node *newNode = new Node;
    newNode->price = price;
    newNode->orderIdList.push_back(orderId);
    newNode->left = nullptr;
    newNode->right = nullptr;
    newNode->height = 1;
    newNode->count = 1;
    return newNode;
}

Node *rightRotate(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;

    //rotation
    x->right = y;
    y->left = T2;

    //Height
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}


Node *leftRotate(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Return new root
    return y;
}

// Get Balance factor of node N
int getBalance(Node *N) {
    if (N == nullptr)
        return 0;
    return height(N->left) - height(N->right);
}


Node *insert(Node *node, Price &price, OrderID &orderId) {
    /* 1.  Perform the normal BST rotation */
    if (node == nullptr)
        return (newNode(price, orderId));

    // If price already exists in BST, increment count and return
    if (price == node->price) {
        (node->orderIdList.push_back(orderId));
        (node->count)++;
        return node;
    }

    /* Otherwise, recur down the tree */
    if (price < node->price)
        node->left = insert(node->left, price, orderId);
    else
        node->right = insert(node->right, price, orderId);

    /* 2. Update height of this ancestor node */
    node->height = max(height(node->left), height(node->right)) + 1;

    /* 3. Get the balance factor of this ancestor node to check whether
       this node became unbalanced */
    int balance = getBalance(node);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && price < node->left->price)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && price > node->right->price)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && price > node->left->price) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && price < node->right->price) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    /* return the (unchanged) node pointer */
    return node;
}

/* Given a non-empty binary search tree, return the node with minimum
price value found in that tree. Note that the entire tree does not
need to be searched. */
Node *minValueNode(Node *node) {
    Node *current = node;

    /* loop down to find the leftmost leaf */
    while (current->left != nullptr)
        current = current->left;

    return current;
}


Node *deleteNode(Node *root, Price &price) {
    // STEP 1: PERFORM STANDARD BST DELETE

    if (root == nullptr)
        return root;

    // If the price to be deleted is smaller than the root's price,
    // then it lies in left subtree
    if (price < root->price)
        root->left = deleteNode(root->left, price);

        // If the price to be deleted is greater than the root's price,
        // then it lies in right subtree
    else if (price > root->price)
        root->right = deleteNode(root->right, price);

        // if price is same as root's price, then This is the node
        // to be deleted
    else {
        // If price is present more than once, simply decrement
        // count and return
        if (root->count > 1) {
            (root->count)--;
            return nullptr;
        }
        // Else, delete the node

        // node with only one child or no child
        if ((root->left == nullptr) || (root->right == nullptr)) {
            Node *temp = root->left ? root->left : root->right;

            // No child case
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else // One child case
                *root = *temp; // Copy the contents of the non-empty child

            free(temp);
        } else {
            // node with two children: Get the inorder successor (smallest
            // in the right subtree)
            Node *temp = minValueNode(root->right);

            // Copy the inorder successor's data to this node and update the count
            root->price = temp->price;
            root->count = temp->count;
            temp->count = 1;

            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->price);
        }
    }

    // If the tree had only one node then return
    if (root == nullptr)
        return root;

    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    root->height = max(height(root->left), height(root->right)) + 1;

    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to check whether
    // this node became unbalanced)
    int balance = getBalance(root);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// A utility function to print getBestBidOfferUsingPostOrder traversal of the tree.
// The function also prints height of every node
Node *getBestBidOfferUsingPostOrder(Node *root) {
    if (root == nullptr) return nullptr;
    getBestBidOfferUsingPostOrder(root->left);
    getBestBidOfferUsingPostOrder(root->right);
    return root;
}



