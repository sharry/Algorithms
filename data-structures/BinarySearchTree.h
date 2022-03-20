// Accessing: O(?)
// Inserting: Beggining: O(?) Middle & End: O(?)
// Deleting : Beggining: O(?) Middle & End: O(?)

#pragma once
#include <iostream>
#include <string>

template <typename T>
class BST
{
private:
    T data;
    size_t occ;
    BST *left;
    BST *right;

public:
    // Constructors
    BST() : data(0), occ(0), left(nullptr), right(nullptr) {}
    BST(T e) : data(e), occ(1), left(nullptr), right(nullptr) {}
    void insert(T e)
    {
        if (this->occ == 0)
        {
            this->data = e;
            this->occ = 1;
            return;
        }
        if (this->data < e)
        {
            if (!this->right)
                this->right = new BST<T>();
            this->right->insert(e);
        }
        else if (this->data > e)
        {
            if (!this->left)
                this->left = new BST<T>();
            this->left->insert(e);
        }
        else
            this->occ++;
    }
    void inorder()
    {
        if (!this)
            return;
        this->left->inorder();
        size_t occ = this->occ;
        while (occ--)
            std::cout << this->data << std::endl;

        this->right->inorder();
    }
};