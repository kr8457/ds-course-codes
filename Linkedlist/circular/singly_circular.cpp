#include<iostream>
using namespace std;

class Node {
private:
    int element;
    Node* next_Node;

public:
    Node(int e, Node* n): element(e), next_Node(n) {}

    void setelement(int e) { element = e; }
    void setnext(Node* n) { next_Node = n; }

    int retrieve() const { return element; }
    Node* next() const { return next_Node; }
};

class S_list {
private:
    Node* list_Head;

public:
    S_list(): list_Head(nullptr) {}

    bool empty() const { return list_Head == nullptr; }
    Node* head() const { return list_Head; }

    int front() const {
        if (empty()) throw "Underflow!";
        return list_Head->retrieve();
    }

    //  DISPLAY (Circular safe)
    void display() const {
        if (empty()) {
            cout << "List is empty\n";
            return;
        }
        Node* temp = list_Head;
        do {
            cout << " " << temp->retrieve();
            temp = temp->next();
        } while (temp != list_Head);
        cout << endl;
    }

    //  SIZE
    int size() const {
        if (empty()) return 0;
        int count = 0;
        Node* temp = list_Head;
        do {
            count++;
            temp = temp->next();
        } while (temp != list_Head);
        return count;
    }

    //  COUNT occurrences
    int count(int n) const {
        if (empty()) return 0;
        int c = 0;
        Node* temp = list_Head;
        do {
            if (temp->retrieve() == n)
                c++;
            temp = temp->next();
        } while (temp != list_Head);
        return c;
    }

    //  END element
    int end() const {
        if (empty()) throw "Underflow!";
        Node* temp = list_Head;
        while (temp->next() != list_Head)
            temp = temp->next();
        return temp->retrieve();
    }

    //  PUSH_FRONT (Circular version)
    void push_front(int n) {
        if (empty()) {
            list_Head = new Node(n, nullptr);
            list_Head->setnext(list_Head);   // circular link
        }
        else {
            Node* last = list_Head;
            while (last->next() != list_Head)
                last = last->next();

            Node* newNode = new Node(n, list_Head);
            last->setnext(newNode);
            list_Head = newNode;//
        }
    }

    //  PUSH_END (Circular version)
    void push_end(int n) {
        if (empty()) {
            list_Head = new Node(n, nullptr);
            list_Head->setnext(list_Head);
        }
        else {
            Node* last = list_Head;
            while (last->next() != list_Head)
                last = last->next();
            last->setnext(new Node(n, list_Head));
        }
    }

    //  POP_FRONT
    int pop_front() {
        if (empty()) throw "Underflow!";

        int val = list_Head->retrieve();

        // Only one node
        if (list_Head->next() == list_Head) {
            delete list_Head;
            list_Head = nullptr;
        }
        else {
            Node* last = list_Head;
            while (last->next() != list_Head)
                last = last->next();

            Node* temp = list_Head;
            list_Head = list_Head->next();
            last->setnext(list_Head);
            delete temp;
        }
        return val;
    }

    //  POP_END
    void pop_end() {
        if (empty()) throw "Underflow!";

        // Only one node
        if (list_Head->next() == list_Head) {
            delete list_Head;
            list_Head = nullptr;
            return;
        }

        Node* prev = nullptr;
        Node* curr = list_Head;

        while (curr->next() != list_Head) {
            prev = curr;
            curr = curr->next();
        }

        prev->setnext(list_Head);
        delete curr;
    }

    //  ERASE ALL OCCURRENCES of a value
    int erase(int n) {
        if (empty()) throw "Underflow!";

        int removed = 0;

        // Case 1: delete from front repeatedly
        while (!empty() && list_Head->retrieve() == n) {
            pop_front();
            removed++;
            if (empty()) return removed;
        }

        // Now delete any remaining nodes
        Node* curr = list_Head->next();
        Node* prev = list_Head;

        while (curr != list_Head) {
            if (curr->retrieve() == n) {
                prev->setnext(curr->next());
                delete curr;
                curr = prev->next();
                removed++;
            }
            else {
                prev = curr;
                curr = curr->next();
            }
        }

        return removed;
    }

    //  Destructor
    ~S_list() {
        while (!empty())
            pop_front();
    }
};


//  MAIN
int main() {
    S_list l;
    l.push_end(1);
    l.push_front(1);
    l.push_front(2);
    l.push_end(3);
    l.push_end(1);

    l.display();

    cout << "Size: " << l.size() << endl;
    cout << "Count of 1: " << l.count(1) << endl;
    cout << "Front: " << l.front() << endl;
    cout << "End: " << l.end() << endl;

    cout << "Deleting all 1s..." << endl;
    l.erase(1);

    l.display();

    return 0;
}
