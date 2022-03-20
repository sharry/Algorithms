// Accessing: O(h)
// Inserting: Beggining: O(h) Middle & End: O(h)
// Deleting : Beggining: O(h) Middle & End: O(h)

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
    void remove(T e)
    {
        if (this->occ == 0)
            return;
        if (this->data < e && this->right)
            this->right->remove(e);
        else if (this->data > e && this->left)
            this->left->remove(e);
        else
        {
            if (this->occ > 1)
            {
                this->occ--;
                return;
            }

            if (!this->left && !this->right)
            {
                // Should do better
                this->occ = 0;
                this->data = 0;
            }
            else if (!this->left)
            {
                this->data = this->right->data;
                delete this->right;
                this->right = nullptr;
            }
            else if (!this->right)
            {
                this->data = this->left->data;
                delete this->left;
                this->left = nullptr;
            }
            else
            {
                auto min = this->right->min();
                this->data = min;
                this->right->remove(min);
            }
        }
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
    T min()
    {
        auto curr = this;
        while (curr && curr->left)
            curr = curr->left;
        return curr->data;
    }
    T max()
    {
        auto curr = this;
        while (curr && curr->right)
            curr = curr->right;
        return curr->data;
    }
    bool has(T val)
    {
        if (this->data > val && this->left)
            return this->left->has(val);
        else if (this->data < val && this->right)
            return this->right->has(val);
        else if (this->data == val)
            return true;
        return false;
    }
};