// Accessing: O(h)
// Inserting: Beggining: O(h) Middle & End: O(h)
// Deleting : Beggining: O(h) Middle & End: O(h)

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

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
    BST(T val) : data(val), occ(1), left(nullptr), right(nullptr) {}
    void insert(T val)
    {
        if (this->occ == 0)
        {
            this->data = val;
            this->occ = 1;
            return;
        }
        if (this->data < val)
        {
            if (!this->right)
                this->right = new BST<T>();
            this->right->insert(val);
        }
        else if (this->data > val)
        {
            if (!this->left)
                this->left = new BST<T>();
            this->left->insert(val);
        }
        else
            this->occ++;
    }
    void remove(T val)
    {
        if (this->occ == 0)
            return;
        if (this->data < val && this->right)
            this->right->remove(val);
        else if (this->data > val && this->left)
            this->left->remove(val);
        else
        {
            if (this->occ > 1)
            {
                this->occ--;
                return;
            }

            if (!this->left && !this->right)
            {
                // I need to do better (but it works)
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
    std::string to_string(std::string seperator = "\n")
    {
        std::ostringstream strm;
        if (this)
        {
            strm << this->left->to_string(seperator);
            auto occ = this->occ;
            while (occ--)
                strm << this->data << seperator;
            strm << this->right->to_string(seperator);
        }
        return strm.str();
    }
    size_t count()
    {
        size_t count = this->occ;
        if (this->left)
            count += this->left->count();
        if (this->right)
            count += this->right->count();
        return count;
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
    std::vector<T> to_vector()
    {
        std::vector<T> vect;
        if (this)
        {
            auto occ = this->occ;
            auto left = this->left->to_vector();
            vect.insert(vect.end(), left.begin(), left.end());
            while (occ--)
                vect.push_back(this->data);
            auto right = this->right->to_vector();
            vect.insert(vect.end(), right.begin(), right.end());
        }
        return vect;
    }
    size_t occurrencesOf(T val)
    {
        if (this->data > val && this->left)
            return this->left->occurrencesOf(val);
        if (this->data < val && this->right)
            return this->right->occurrencesOf(val);
        if (this->data == val)
            return this->occ;
        return 0;
    }
    int sum()
    {
        int sum = 0;
        if (!this)
            return 0;
        sum += this->data * this->occ;
        sum += this->left->sum();
        sum += this->right->sum();
        return sum;
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
};