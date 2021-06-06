/* 
 * File:   Node<T>.h
 * Modified:  from http://www.sanfoundry.com/cpp-program-implement-AVL-trees/
 * Created on May 23, 2021, 9:14 PM
 * Purpose:  An Binary Tree using an AVL balancing technique
 */

#ifndef TREE_H
#define	TREE_H

#include <iostream>
#include <queue>
#include <vector>
#include <functional>
using namespace std;

template <class T>
struct Node{
    T data;
    struct Node<T> *left;
    struct Node<T> *right;
};

template <class T>
class Tree{
 public:
 Node<T> *root;                   //Root node
 Tree(){root = NULL;}          //Constructor

//******************************************************************************
//                            Height of AVL Sub Trees
//******************************************************************************
int height(Node<T> *temp){
    int h = 0;
    if (temp != NULL){
        int l_height = height (temp->left);
        int r_height = height (temp->right);
        int max_height = max (l_height, r_height);
        h = max_height + 1;
    }
    return h;
}
 
//******************************************************************************
//                      Height Difference of AVL Sub Trees
//******************************************************************************
int diff(Node<T> *temp){
    int l_height = height (temp->left);
    int r_height = height (temp->right);
    int b_factor= l_height - r_height;
    return b_factor;
}
 
//******************************************************************************
//                      Right-Right Rotations of Sub Trees
//******************************************************************************
Node<T> *rr_rotation(Node<T> *parent){
    Node<T> *temp;
    temp = parent->right;
    parent->right = temp->left;
    temp->left = parent;
    return temp;
}

//******************************************************************************
//                      Left-Left Rotations of Sub Trees
//******************************************************************************
Node<T> *ll_rotation(Node<T> *parent){
    Node<T> *temp;
    temp = parent->left;
    parent->left = temp->right;
    temp->right = parent;
    return temp;
}
 
//******************************************************************************
//                      Left-Right Rotations of Sub Trees
//******************************************************************************
Node<T> *lr_rotation(Node<T> *parent){
    Node<T> *temp;
    temp = parent->left;
    parent->left = rr_rotation (temp);
    return ll_rotation (parent);
}
 
//******************************************************************************
//                      Right-Left Rotations of Sub Trees
//******************************************************************************
Node<T> *rl_rotation(Node<T> *parent){
    Node<T> *temp;
    temp = parent->right;
    parent->right = ll_rotation (temp);
    return rr_rotation (parent);
}
 
//******************************************************************************
//                         Balancing of Sub Trees
//******************************************************************************
Node<T> *balance(Node<T> *temp){
    int bal_factor = diff (temp);
    if (bal_factor > 1){
        if (diff (temp->left) > 0)
            temp = ll_rotation (temp);
        else
            temp = lr_rotation (temp);
    }else if (bal_factor < -1){
        if (diff (temp->right) > 0)
            temp = rl_rotation (temp);
        else
            temp = rr_rotation (temp);
    }
    return temp;
}
 
//******************************************************************************
//                    Insert the Data into the Sub Trees
//******************************************************************************
Node<T> *insert(Node<T> *root, T value){
    if (root == NULL){
        root = new Node<T>;
        root->data = value;
        root->left = NULL;
        root->right = NULL;
        return root;
    }else if (value < root->data){
        root->left = insert(root->left, value);
        root = balance (root);
    }else if (value >= root->data){
        root->right = insert(root->right, value);
        root = balance (root);
    }
    return root;
}
//******************************************************************************
//                      Level-order Output of Tree
//******************************************************************************
void levelorder(Node<T> *tree){
    queue<Node<T>*> q;
    q.push(tree);
    while (!q.empty())
    {
        if (q.front()->left)      q.push(q.front()->left);
        if (q.front()->right)    q.push(q.front()->right);
        cout << q.front()->data << " ";
        q.pop();
    }
}

std::vector<T*> getIndexes(Node<T> *tree){
    queue<Node<T>*> q;
    q.push(tree);
    std::vector<T*> res;
    while (!q.empty())
    {
        if (q.front()->left)      q.push(q.front()->left);
        if (q.front()->right)    q.push(q.front()->right);
         res.push_back(&(q.front()->data));
        q.pop();
    }
    return res;
}

Node<T> *deleteNode(Node<T> *tree, T val)
{
    vector <T> elements;
    std::function<void(Node<T>*)> inordertraverse = [&](Node<T> *t)
    {
      if (t == nullptr)
        return;
     inordertraverse (t->left);
     if (t->data != val)
         elements.push_back(t->data);
     inordertraverse (t->right);
    };
    inordertraverse(tree);
    Node<T> *temp = nullptr;
    for (T x: elements)
        temp = insert(temp, x);
    return temp;
}
};

#endif	/* TREE_H */