// Stack - LIFO data structure (Last in first out)
// Push : O(1)
// Pop : O(1)
// Peek : O(1)

#pragma once

#include <vector>
#include <assert.h>

template <typename T = int>
class Stack
{
private:
    struct Node
    {
        T data;
        Node *next;
        Node(T val) : data(val), next(nullptr) {}
    };
    Node *head;
    std::vector<T> _values_;
    size_t _length_ = 0;

    // push() method helpers
    void _push_(T element)
    {
        Node *node = new Node(element);
        node->next = head;
        head = node;
    }
    void push() {}

public:
    // Constructors

    Stack() : head(nullptr), _values_(*new std::vector<T>()) {}
    template <typename First, typename... Rest>
    Stack(const First &first, const Rest &...rest) : head(nullptr), _values_(*new std::vector<T>())
    {
        this->push(first);
        this->push(rest...);
    }

    // Methods

    // insert a value to the stack
    template <typename First, typename... Rest>
    void push(const First &first, const Rest &...rest)
    {
        _push_(first);
        _values_.push_back(first);
        _length_++;
        push(rest...);
    }

    // get the top value
    T peek() const
    {
        assert(head);
        return head->data;
    }

    // get the top value & remove it from the stack
    T pop()
    {
        assert(head);
        _values_.pop_back();
        _length_--;
        T val = head->data;
        if (head->next)
        {
            auto new_head = head->next;
            delete head;
            head = new_head;
            return val;
        }
        head = nullptr;
        return val;
    }

    // checks if the stack is empty or not
    bool is_empty() const
    {
        return !head;
    }

    // get a vector of the values in the stack
    std::vector<T> values() const
    {
        return _values_;
    }

    // get the length of the stack
    size_t length() const
    {
        return _length_;
    }
};
