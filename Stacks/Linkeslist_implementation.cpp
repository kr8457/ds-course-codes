#include<iostream> // stack using doubly

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

    // Insert at front (stack push)
    void push_front(int n) {
        Node* newNode = new Node(n, head_Node, nullptr);

        if (empty()) {
            head_Node = tail_Node = newNode;
        } else {
            head_Node->setprev(newNode);
            head_Node = newNode;
        }
    }

    // Remove from front (stack pop)
    int pop_front() {
        if (empty()) throw "Underflow!";
        int val = head_Node->retrieve();

        Node* temp = head_Node;

        if (head_Node == tail_Node) {
            head_Node = tail_Node = nullptr;
        }
        else {
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

// ✅ STACK using D_list
class Stack_List {
private:
    D_list list;

public:
    void push(int x) {
        list.push_front(x);
    }

    int pop() {
        return list.pop_front();
    }

    int top() const {
        return list.front();
    }

    bool isEmpty() const {
        return list.empty();
    }

    int size() const {
        return list.size();
    }
};


// ✅ MAIN
int main() {
    Stack_List s;

    s.push(10);
    s.push(20);
    s.push(30);

    std::cout << "Top: " << s.top() << std::endl; // 30
    std::cout << "Pop: " << s.pop() << std::endl; // 30
    std::cout << "Top After Pop: " << s.top() << std::endl; // 20

    std::cout << "Size: " << s.size() << std::endl; 

    return 0;
}
