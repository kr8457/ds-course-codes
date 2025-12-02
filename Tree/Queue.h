#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>

template <typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& d, Node* n = nullptr) : data(d), next(n) {}
    };

    Node* head;
    Node* tail;

public:
    Queue() : head(nullptr), tail(nullptr) {}

    ~Queue() {
        while (!empty()) dequeue();
    }

    bool empty() const { return head == nullptr; }

    void enqueue(const T& x) {
        Node* n = new Node(x);
        if (tail) tail->next = n;
        tail = n;
        if (!head) head = n;
    }

    T dequeue() {
        if (empty()) throw "Underflow!";
        Node* temp = head;
        T val = temp->data;
        head = head->next;
        if (!head) tail = nullptr;
        delete temp;
        return val;
    }

    T front() const {
        if (empty()) throw "Underflow!";
        return head->data;
    }

    int size() const {
        int c = 0;
        for (Node* p = head; p != nullptr; p = p->next) ++c;
        return c;
    }
};

#endif
