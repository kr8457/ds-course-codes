#include<iostream>
using namespace std;

class Node {
private:
    int element;
    Node* next_Node;
    Node* prev_Node;

public:
    Node(int e, Node* n = nullptr, Node* p = nullptr)
        : element(e), next_Node(n), prev_Node(p) {}

    void setelement(int e) { element = e; }
    void setnext(Node* n) { next_Node = n; }
    void setprev(Node* p) { prev_Node = p; }

    int retrieve() const { return element; }
    Node* next() const { return next_Node; }
    Node* prev() const { return prev_Node; }
};

class D_list {
private:
    Node* head_Node;
    Node* tail_Node;

public:
    D_list() : head_Node(nullptr), tail_Node(nullptr) {}

    bool empty() const { return head_Node == nullptr; }

    int front() const {
        if (empty()) throw "Underflow!";
        return head_Node->retrieve();
    }

    int size() const {
        int count = 0;
        Node* temp = head_Node;
        while (temp != nullptr) {
            count++;
            temp = temp->next();
        }
        return count;
    }

    void push_back(int n) {
        Node* newNode = new Node(n, nullptr, tail_Node);

        if (empty()) {
            head_Node = tail_Node = newNode;
        } else {
            tail_Node->setnext(newNode);
            tail_Node = newNode;
        }
    }

    int pop_front() {
        if (empty()) throw "Underflow!";
        int val = head_Node->retrieve();
        Node* temp = head_Node;

        if (head_Node == tail_Node) {
            head_Node = tail_Node = nullptr;
        } else {
            head_Node = head_Node->next();
            head_Node->setprev(nullptr);
        }

        delete temp;
        return val;
    }

    ~D_list() {
        while (!empty())
            pop_front();
    }
};

class Queue_List {
private:
    D_list list;

public:
    void enqueue(int x) {
        list.push_back(x);
    }

    int dequeue() {
        return list.pop_front();
    }

    int front() const {
        return list.front();
    }

    bool isEmpty() const {
        return list.empty();
    }

    int size() const {
        return list.size();
    }
};

int main() {
    Queue_List q;

    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);

    cout << "Front: " << q.front() << endl;
    cout << "Dequeue: " << q.dequeue() << endl;
    cout << "Front After Dequeue: " << q.front() << endl;
    cout << "Size: " << q.size() << endl;

    return 0;
}
