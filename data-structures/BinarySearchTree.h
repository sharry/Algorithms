// Accessing: O(h)
// Inserting: Beggining: O(h) Middle & End: O(h)
// Deleting : Beggining: O(h) Middle & End: O(h)

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <math.h>
#include <cstdarg>

template <typename T>
class BST
{
private:
    // The actual data stored in the node
    T data;
    // Occurrence tracker for a datum
    size_t occ;
    // Pointer the the left tree
    BST *left;
    // Pointer the the right tree
    BST *right;

    // insert method helpers
    void _insert(T val)
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
            this->right->_insert(val);
        }
        else if (this->data > val)
        {
            if (!this->left)
                this->left = new BST<T>();
            this->left->_insert(val);
        }
        else
            this->occ++;
    }
    void insert() {}

public:
    // Constructors
    BST() : data(0), occ(0), left(nullptr), right(nullptr) {}
    BST(T val) : data(val), occ(1), left(nullptr), right(nullptr) {}

    // Insert values to the tree
    template <typename First, typename... Rest>
    void insert(const First &first, const Rest &...rest)
    {
        _insert(first);
        insert(rest...);
    }

    // Remove a value from the tree
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
                auto right = this->right->right;
                auto left = this->right->left;
                delete this->right;
                this->right = right;
                this->left = left;
            }
            else if (!this->right)
            {
                this->data = this->left->data;
                auto right = this->left->right;
                auto left = this->left->left;
                delete this->left;
                this->right = right;
                this->left = left;
            }
            else
            {
                auto min = this->right->min();
                this->data = min;
                this->right->remove(min);
            }
        }
    }

    // Returns a string from the elements of the tree
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

    // Get the elements count
    size_t count()
    {
        size_t count = this->occ;
        if (this->left)
            count += this->left->count();
        if (this->right)
            count += this->right->count();
        return count;
    }

    // Search for a value in the tree
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

    // Returns a vector from the elements of the tree
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

    // Get how many an element occur in the tree
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

    // Sum (addition) of all the element of the tree
    T sum()
    {
        T sum = 0;
        if (!this)
            return 0;
        sum += this->data * this->occ;
        sum += this->left->sum();
        sum += this->right->sum();
        return sum;
    }

    // Product (multiplication) of all the element of the tree
    T prod()
    {
        T prod = 1;
        if (!this)
            return 1;
        prod *= std::pow(this->data, this->occ);
        prod *= this->left->prod();
        prod *= this->right->prod();
        return prod;
    }

    // Minimum value in the tree
    T min()
    {
        auto curr = this;
        while (curr && curr->left)
            curr = curr->left;
        return curr->data;
    }

    // Maximum value in the tree
    T max()
    {
        auto curr = this;
        while (curr && curr->right)
            curr = curr->right;
        return curr->data;
    }

    // Height of the tree
    size_t height()
    {
        if (!this || !this->occ)
            return 0;
        else
            return 1 + std::max(this->left->height(), this->right->height());
    }
};