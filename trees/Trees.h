#pragma once
#include <iostream>
#include <queue>

template<class T>
struct Node{
    T element;
    Node<T> *left, *right;
};

template<class T>
Node<T>* createNode(T *&data){
    Node<T>* newNode = new Node<T>{data, nullptr, nullptr};
    return newNode;
}

template<class T>
void insertElement(Node<T> *& root, T data, std::string path){
    if (root == nullptr){
        if (path.empty()){
            root = new Node<T>{data, nullptr, nullptr};
        }
        return;
    }
    if (path[0] == 'L')
        insertElement(root->left, data, path.substr(1));
    else
        insertElement(root->right, data, path.substr(1));
}

template<class T>
void insert(Node<T>*& root, int element) {
    if (root == nullptr) {
        // the tree is empty, so the new node becomes the root
        root = new Node<T>{element, nullptr, nullptr};
        return;
    }

    if (element < root->element) {
        // the new value goes in the left subtree
        insert(root->left, element);
    } else {
        // the new value goes in the right subtree
        insert(root->right, element);
    }
}

template<class T>
void printByLevels(Node<T>* root) {
    if (root == nullptr) {
        return;
    }

    // create a queue to store the nodes at each level
    std::queue<Node<T>*> q;
    q.push(root); // start with the root node

    int level = 0; // current level of the tree
    while (!q.empty()) {
        // print the level number
        std::cout << "Level " << level << ": ";

        // calculate the number of nodes at the current level
        int levelSize = q.size();

        // print the values of the nodes at the current level
        for (int i = 0; i < levelSize; i++) {
            Node<T>* curr = q.front();
            q.pop();
            std::cout << curr->element << " ";

            // add the children of the current node to the queue
            if (curr->left != nullptr) {
                q.push(curr->left);
            }
            if (curr->right != nullptr) {
                q.push(curr->right);
            }
        }

        std::cout << std::endl; // move to the next line
        level++; // go to the next level
    }
}


template<class T>
void DFS_preOrder(Node<T>* root) {
    if (root == nullptr) {
        return;
    }

    std::cout << root->element << " "; // visit the current node
    DFS(root->left); // recurse on the left subtree
    DFS(root->right); // recurse on the right subtree
}

template<class T>
void DFS_inOrder(Node<T>* root) {
    if (root == nullptr) {
        return;
    }

    DFS(root->left); // recurse on the left subtree
    std::cout << root->element << " "; // visit the current node
    DFS(root->right); // recurse on the right subtree
}

template<class T>
void DFS_postOrder(Node<T>* root) {
    if (root == nullptr) {
        return;
    }

    DFS(root->left); // recurse on the left subtree
    DFS(root->right); // recurse on the right subtree
    std::cout << root->element << " "; // visit the current node
}

template<class T>
bool findSum(Node<T>* root, int a, int b) {
    if (root == nullptr) {
        return false;
    }

    if (root->element == a || root->element == b) {
        // we found one of the elements we're looking for
        return true;
    }

    // search the left and right subtrees for the other element
    bool foundInLeft = findSum(root->left, a, b);
    bool foundInRight = findSum(root->right, a, b);

    if (foundInLeft && foundInRight) {
        // both elements were found in different subtrees
        std::cout << "The sum of " << a << " and " << b << " is " << a+b << std::endl;
        return true;
    }

    return foundInLeft || foundInRight; // return true if either element was found
}

template<class T>
void findLevel(Node<T>* root, int level) {
    if (root == nullptr) {
        return;
    }

    // create a queue to store the nodes at each level
    std::queue<Node<T>*> q;
    q.push(root); // start with the root node
    int currLevel = 0; // current level of the tree

    while (!q.empty()) {
        // calculate the number of nodes at the current level
        int levelSize = q.size();

        if (currLevel == level) {
            // we found the level we're looking for, so print the values of the nodes
            for (int i = 0; i < levelSize; i++) {
                Node<T>* curr = q.front();
                q.pop();
                std::cout << curr->element << " ";
            }
            std::cout << std::endl; // move to the next line
            return; // we're done, so return
        }

        // process the nodes at the current level
        for (int i = 0; i < levelSize; i++) {
            Node<T>* curr = q.front();
            q.pop();

            // add the children of the current node to the queue
            if (curr->left != nullptr) {
                q.push(curr->left);
            }
            if (curr->right != nullptr) {
                q.push(curr->right);
            }
        }

        currLevel++; // go to the next level
    }
}

template<class T>
int findBiggestLevel(Node<T>* root) {
    if (root == nullptr) {
        return -1; // the tree is empty, so return -1
    }

    // create a queue to store the nodes at each level
    std::queue<Node<T>*> q;
    q.push(root); // start with the root node
    int currLevel = 0; // current level of the tree
    int biggestLevel = 0; // level of the biggest element
    int biggestVal = root->element; // biggest element so far

    while (!q.empty()) {
        // calculate the number of nodes at the current level
        int levelSize = q.size();

        // process the nodes at the current level
        for (int i = 0; i < levelSize; i++) {
            Node<T>* curr = q.front();
            q.pop();

            if (curr->element > biggestVal) {
                // we found a bigger element, so update the biggest level and value
                biggestLevel = currLevel;
                biggestVal = curr->element;
            }

            // add the children of the current node to the queue
            if (curr->left != nullptr) {
                q.push(curr->left);
            }
            if (curr->right != nullptr) {
                q.push(curr->right);
            }
        }

        currLevel++; // go to the next level
    }

    return biggestLevel; // return the level of the biggest element
}

template<class T>
int findSmallestLevel(Node<T>* root) {
    if (root == nullptr) {
        return -1; // the tree is empty, so return -1
    }

    // create a queue to store the nodes at each level
    std::queue<Node<T>*> q;
    q.push(root); // start with the root node
    int currLevel = 0; // current level of the tree
    int smallestLevel = 0; // level of the smallest element
    int smallestVal = root->element; // smallest element so far

    while (!q.empty()) {
        // calculate the number of nodes at the current level
        int levelSize = q.size();

        // process the nodes at the current level
        for (int i = 0; i < levelSize; i++) {
            Node<T>* curr = q.front();
            q.pop();

            if (curr->element < smallestVal) {
                // we found a smaller element, so update the smallest level and value
                smallestLevel = currLevel;
                smallestVal = curr->element;
            }

            // add the children of the current node to the queue
            if (curr->left != nullptr) {
                q.push(curr->left);
            }
            if (curr->right != nullptr) {
                q.push(curr->right);
            }
        }

        currLevel++; // go to the next level
    }

    return smallestLevel; // return the level of the smallest element
}

template<class T>
bool areMirrored(Node<T>* tree1, Node<T>* tree2) {
    if (tree1 == nullptr && tree2 == nullptr) {
        return true; // both trees are empty, so they are mirrored
    }
    if (tree1 == nullptr || tree2 == nullptr) {
        return false; // one tree is empty, the other is not, so they are not mirrored
    }
    if (tree1->element != tree2->element) {
        return false; // the root nodes have different values, so the trees are not mirrored
    }
    // recurse on the left and right subtrees
    return areMirrored(tree1->left, tree2->right) && areMirrored(tree1->right, tree2->left);
}

template<class T>
bool haveSameStructure(Node<T>* tree1, Node<T>* tree2) {
    if (tree1 == nullptr && tree2 == nullptr) {
        return true; // both trees are empty, so they have the same structure
    }
    if (tree1 == nullptr || tree2 == nullptr) {
        return false; // one tree is empty, the other is not, so they don't have the same structure
    }
    // recurse on the left and right subtrees
    return haveSameStructure(tree1->left, tree2->left) && haveSameStructure(tree1->right, tree2->right);
}

template<class T>
void reverseTree(Node<T>* root) {
    if (root == nullptr) {
        return; // the tree is empty, so nothing to do
    }

    // swap the left and right children
    Node<T>* temp = root->left;
    root->left = root->right;
    root->right = temp;

    // recurse on the left and right subtrees
    reverseTree(root->left);
    reverseTree(root->right);
}

template<class T>
bool isSubTree(Node<T>* tree1, Node<T>* tree2) {
    if (tree1 == nullptr || tree2 == nullptr) {
        return false; // at least one of the trees is empty, so tree2 cannot be a sub tree of tree1
    }
    if (haveSameStructure(tree1, tree2)) {
        return true; // tree2 has the same structure as tree1, so it is a sub tree
    }
    // recurse on the left and right subtrees of tree1
    return isSubTree(tree1->left, tree2) || isSubTree(tree1->right, tree2);
}

template<class T>
bool areEqual(Node<T>* tree1, Node<T>* tree2) {
    if (tree1 == nullptr && tree2 == nullptr) {
        return true; // both trees are empty, so they are equal
    }
    if (tree1 == nullptr || tree2 == nullptr) {
        return false; // one tree is empty, the other is not, so they are not equal
    }
    if (tree1->element != tree2->element) {
        return false; // the root nodes have different values, so the trees are not equal
    }
    // recurse on the left and right subtrees
    return areEqual(tree1->left, tree2->left) && areEqual(tree1->right, tree2->right);
}

template<class T>
int sumTree(Node<T>* root) {
    if (root == nullptr) {
        return 0; // the tree is empty, so the sum is 0
    }

    // add the value of the root node to the sum of the left and right subtrees
    return root->element + sumTree(root->left) + sumTree(root->right);
}

template<class T>
int countSubTrees(Node<T>* root) {
    if (root == nullptr) {
        return 0; // the tree is empty, so there are no sub trees
    }

    int count = 0;
    // check if the root node is the root of a sub tree
    if (isSubTree(root, root)) {
        count++;
    }
    // count the sub trees in the left and right subtrees
    count += countSubTrees(root->left);
    count += countSubTrees(root->right);

    return count;
}

template<class T>
void insertIntoBST(Node<T>*& root, int elem) {
    if (root == nullptr) {
        // the tree is empty, so create a new node
        root = new Node<T>{elem, nullptr, nullptr};
        return;
    }

    if (elem < root->element) {
        // insert the new node into the left subtree
        insertIntoBST(root->left, elem);
    } else {
        // insert the new node into the right subtree
        insertIntoBST(root->right, elem);
    }
}


template<class T>
void deleteFromBST(Node<T>*& root, int element) {
    if (root == nullptr) {
        // the tree is empty, so there is nothing to delete
        return;
    }

    if (element < root->element) {
        // the node to be deleted is in the left subtree
        deleteFromBST(root->left, element);
    } else if (element > root->element) {
        // the node to be deleted is in the right subtree
        deleteFromBST(root->right, element);
    } else {
        // the node to be deleted is the root node
        if (root->left == nullptr) {
            // the root node has no left child, so replace it with its right child
            Node<T>* temp = root->right;
            delete root;
            root = temp;
        } else if (root->right == nullptr) {
            // the root node has no right child, so replace it with its left child
            Node<T>* temp = root->left;
            delete root;
            root = temp;
        } else {
            // the root node has both left and right children, so find the inorder successor and replace it with the root node
            Node<T>* successor = root->right;
            while (successor->left != nullptr) {
                successor = successor->left;
            }
            root->element = successor->element;
            deleteFromBST(root->right, successor->element);
        }
    }
}