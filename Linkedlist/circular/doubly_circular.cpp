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

public:
    D_list() : head_Node(nullptr) {}

    bool empty() const { return head_Node == nullptr; }
    Node* head() const { return head_Node; }

    int front() const {
        if (empty()) throw "Underflow!";
        return head_Node->retrieve();
    }

    int end() const {
        if (empty()) throw "Underflow!";
        return head_Node->prev()->retrieve();
    }

    // ✅ DISPLAY FORWARD
    void display() const {
        if (empty()) {
            cout << "List is empty\n";
            return;
        }
        Node* temp = head_Node;
        do {
            cout << " " << temp->retrieve();
            temp = temp->next();
        } while (temp != head_Node);
        cout << endl;
    }

    // ✅ DISPLAY BACKWARD
    void reverse_display() const {
        if (empty()) {
            cout << "List is empty\n";
            return;
        }
        Node* temp = head_Node->prev();
        Node* tail = temp;
        do {
            cout << " " << temp->retrieve();
            temp = temp->prev();
        } while (temp != tail);
        cout << endl;
    }

    // ✅ SIZE
    int size() const {
        if (empty()) return 0;
        int count = 0;
        Node* temp = head_Node;
        do {
            count++;
            temp = temp->next();
        } while (temp != head_Node);
        return count;
    }

    // ✅ COUNT OCCURRENCES
    int count(int n) const {
        if (empty()) return 0;
        int c = 0;
        Node* temp = head_Node;
        do {
            if (temp->retrieve() == n)
                c++;
            temp = temp->next();
        } while (temp != head_Node);
        return c;
    }

    // ✅ PUSH FRONT
    void push_front(int n) {
        Node* newNode = new Node(n);

        if (empty()) {
            newNode->setnext(newNode);
            newNode->setprev(newNode);
            head_Node = newNode;
        }
        else {
            Node* tail = head_Node->prev();

            newNode->setnext(head_Node);
            newNode->setprev(tail);

            tail->setnext(newNode);
            head_Node->setprev(newNode);

            head_Node = newNode;
        }
    }

    // ✅ PUSH END
    void push_end(int n) {
        if (empty()) {
            push_front(n);
            return;
        }

        Node* newNode = new Node(n);
        Node* tail = head_Node->prev();

        newNode->setnext(head_Node);
        newNode->setprev(tail);

        tail->setnext(newNode);
        head_Node->setprev(newNode);
    }

    // ✅ POP FRONT
    int pop_front() {
        if (empty()) throw "Underflow!";

        int val = head_Node->retrieve();

        // One node only
        if (head_Node->next() == head_Node) {
            delete head_Node;
            head_Node = nullptr;
        }
        else {
            Node* tail = head_Node->prev();
            Node* temp = head_Node;

            head_Node = head_Node->next();
            head_Node->setprev(tail);
            tail->setnext(head_Node);

            delete temp;
        }

        return val;
    }

    // ✅ POP END
    void pop_end() {
        if (empty()) throw "Underflow!";

        // One node only
        if (head_Node->next() == head_Node) {
            delete head_Node;
            head_Node = nullptr;
            return;
        }

        Node* tail = head_Node->prev();
        Node* newTail = tail->prev();

        newTail->setnext(head_Node);
        head_Node->setprev(newTail);

        delete tail;
    }

    // ✅ ERASE ALL OCCURRENCES
    int erase(int n) {
        if (empty()) throw "Underflow!";

        int removed = 0;

        Node* curr = head_Node;
        Node* nextNode;

        do {
            nextNode = curr->next();

            if (curr->retrieve() == n) {
                // Only 1 node left
                if (curr->next() == curr) {
                    delete curr;
                    head_Node = nullptr;
                    return 1;
                }

                Node* prev = curr->prev();
                Node* next = curr->next();

                prev->setnext(next);
                next->setprev(prev);

                // Update head if needed
                if (curr == head_Node)
                    head_Node = next;

                delete curr;
                removed++;
            }

            curr = nextNode;

        } while (curr != head_Node);

        return removed;
    }

    // ✅ Destructor
    ~D_list() {
        while (!empty())
            pop_front();
    }
};


// ✅ MAIN (SAME TESTS)
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
