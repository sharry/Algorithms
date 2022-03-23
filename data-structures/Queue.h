#pragma once

#include <vector>
#include <assert.h>

template <typename T = int>
class Queue
{
private:
    struct Node
    {
        T data;
        Node *next;
        Node(T val) : data(val), next(nullptr) {}
    };

    Node *head, *tail;
    std::vector<T> _values_;
    size_t _length_ = 0;

    // enqueue() method helpers
    void _enqueue_(T element)
    {
        Node *node = new Node(element);
        if (!tail)
        {
            tail = head = node;
            return;
        }
        tail->next = node;
        tail = tail->next;
    }
    void enqueue() {}

public:
    // Constructors
    Queue() : head(nullptr), tail(nullptr), _values_(*new std::vector<T>()) {}
    template <typename First, typename... Rest>
    Queue(const First &first, const Rest &...rest)
        : head(nullptr), tail(nullptr), _values_(*new std::vector<T>())
    {
        this->enqueue(first, rest...);
    }

    // Methods

    // add a value to the back of the queue
    template <typename First, typename... Rest>
    void enqueue(const First &first, const Rest &...rest)
    {
        _enqueue_(first);
        _values_.push_back(first);
        _length_++;
        enqueue(rest...);
    }

    // get the value in the front of the queue
    T front() const
    {
        assert(head);
        return head->data;
    }

    // get the value in the back of the queue
    T back() const
    {
        assert(head);
        return tail->data;
    }

    // get the value in the front of the queue & remove it
    T dequeue()
    {
        assert(head);
        _values_.erase(_values_.begin());
        _length_--;
        T val = head->data;
        if (head->next)
            head = head->next;
        else
            tail = head = nullptr;
        return val;
    }

    // check if the queue is empty or not
    bool is_empty() const
    {
        return !head;
    }

    // get a vector of the values in the stack
    std::vector<T> values() const
    {
        return _values_;
    }

    // get the length of the queue
    size_t length() const
    {
        return _length_;
    }
};
