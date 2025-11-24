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

    int end() const {
        if (empty()) throw "Underflow!";
        return tail_Node->retrieve();
    }

    //  DISPLAY FORWARD
    void display() const {
        Node* temp = head_Node;
        while (temp != nullptr) {
            cout << " " << temp->retrieve();
            temp = temp->next();
        }
        cout << endl;
    }

    //  DISPLAY BACKWARD
    void reverse_display() const {
        Node* temp = tail_Node;
        while (temp != nullptr) {
            cout << " " << temp->retrieve();
            temp = temp->prev();
        }
        cout << endl;
    }

    //  SIZE
    int size() const {
        int count = 0;
        Node* temp = head_Node;
        while (temp != nullptr) {
            count++;
            temp = temp->next();
        }
        return count;
    }

    //  COUNT ELEMENTS
    int count(int n) const {
        int c = 0;
        Node* temp = head_Node;
        while (temp != nullptr) {
            if (temp->retrieve() == n) c++;
            temp = temp->next();
        }
        return c;
    }

    //  PUSH FRONT
    void push_front(int n) {
        Node* newNode = new Node(n, head_Node, nullptr);

        if (empty()) {
            head_Node = tail_Node = newNode;
        } else {
            head_Node->setprev(newNode);
            head_Node = newNode;
        }
    }

    //  PUSH END
    void push_end(int n) {
        Node* newNode = new Node(n, nullptr, tail_Node);

        if (empty()) {
            head_Node = tail_Node = newNode;
        } else {
            tail_Node->setnext(newNode);
            tail_Node = newNode;
        }
    }

    //  POP FRONT
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

    //  POP END
    void pop_end() {
        if (empty()) throw "Underflow!";

        Node* temp = tail_Node;

        if (head_Node == tail_Node) {
            head_Node = tail_Node = nullptr;
        } else {
            tail_Node = tail_Node->prev();
            tail_Node->setnext(nullptr);
        }

        delete temp;
    }

    //  ERASE ALL OCCURRENCES
    int erase(int n) {
        if (empty()) throw "Underflow!";

        int removed = 0;
        Node* curr = head_Node;

        while (curr != nullptr) {
            if (curr->retrieve() == n) {
                Node* nextNode = curr->next();
                Node* prevNode = curr->prev();

                // Removing head
                if (curr == head_Node)
                    head_Node = nextNode;

                // Removing tail
                if (curr == tail_Node)
                    tail_Node = prevNode;

                if (prevNode) prevNode->setnext(nextNode);
                if (nextNode) nextNode->setprev(prevNode);

                delete curr;
                removed++;

                curr = nextNode;
            }
            else {
                curr = curr->next();
            }
        }
        return removed;
    }

    //  Destructor
    ~D_list() {
        while (!empty())
            pop_front();
    }
};


//  MAIN
int main() {
    D_list l;

    l.push_end(1);
    l.push_front(1);
    l.push_front(2);
    l.push_end(3);
    l.push_end(1);

    l.display();
    l.reverse_display();

    cout << "Size: " << l.size() << endl;
    cout << "Count of 1: " << l.count(1) << endl;
    cout << "Front: " << l.front() << endl;
    cout << "End: " << l.end() << endl;

    cout << "Deleting all 1s..." << endl;
    l.erase(1);

    l.display();
    l.reverse_display();

    return 0;
}
