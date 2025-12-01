#include<iostream>
using namespace std;

template <typename T>
class Node {
private:
    T element;
    Node<T>* next_Node;

public:
    Node(T e, Node<T>* n) : element(e), next_Node(n) {}

    void setelement(T e) { element = e; }
    void setnext(Node<T>* n) { next_Node = n; }

    T retrieve() const { return element; }
    Node<T>* next() const { return next_Node; }
};

template <typename T>
class S_list {
private:
    Node<T>* list_Head;

public:
    S_list() : list_Head(nullptr) {}

    bool empty() const { return list_Head == nullptr; }
    Node<T>* head() const { return list_Head; }

    T front() const {
        if (empty()) throw "Underflow!";
        return list_Head->retrieve();
    }

    void display() const {
        if (empty()) {
            cout << "List is empty\n";
            return;
        }
        Node<T>* temp = list_Head;
        do {
            cout << " " << temp->retrieve();
            temp = temp->next();
        } while (temp != list_Head);
        cout << endl;
    }

    int size() const {
        if (empty()) return 0;
        int count = 0;
        Node<T>* temp = list_Head;
        do {
            count++;
            temp = temp->next();
        } while (temp != list_Head);
        return count;
    }

    int count(T n) const {
        if (empty()) return 0;
        int c = 0;
        Node<T>* temp = list_Head;
        do {
            if (temp->retrieve() == n)
                c++;
            temp = temp->next();
        } while (temp != list_Head);
        return c;
    }

    T end() const {
        if (empty()) throw "Underflow!";
        Node<T>* temp = list_Head;
        while (temp->next() != list_Head)
            temp = temp->next();
        return temp->retrieve();
    }

    void push_front(T n) {
        if (empty()) {
            list_Head = new Node<T>(n, nullptr);
            list_Head->setnext(list_Head);
        }
        else {
            Node<T>* last = list_Head;
            while (last->next() != list_Head)
                last = last->next();

            Node<T>* newNode = new Node<T>(n, list_Head);
            last->setnext(newNode);
            list_Head = newNode;
        }
    }

    void push_end(T n) {
        if (empty()) {
            list_Head = new Node<T>(n, nullptr);
            list_Head->setnext(list_Head);
        }
        else {
            Node<T>* last = list_Head;
            while (last->next() != list_Head)
                last = last->next();

            last->setnext(new Node<T>(n, list_Head));
        }
    }

    T pop_front() {
        if (empty()) throw "Underflow!";

        T val = list_Head->retrieve();

        if (list_Head->next() == list_Head) {
            delete list_Head;
            list_Head = nullptr;
        }
        else {
            Node<T>* last = list_Head;
            while (last->next() != list_Head)
                last = last->next();

            Node<T>* temp = list_Head;
            list_Head = list_Head->next();
            last->setnext(list_Head);
            delete temp;
        }
        return val;
    }

    void pop_end() {
        if (empty()) throw "Underflow!";

        if (list_Head->next() == list_Head) {
            delete list_Head;
            list_Head = nullptr;
            return;
        }

        Node<T>* prev = nullptr;
        Node<T>* curr = list_Head;

        while (curr->next() != list_Head) {
            prev = curr;
            curr = curr->next();
        }

        prev->setnext(list_Head);
        delete curr;
    }

    int erase(T n) {
        if (empty()) throw "Underflow!";

        int removed = 0;

        while (!empty() && list_Head->retrieve() == n) {
            pop_front();
            removed++;
            if (empty()) return removed;
        }

        Node<T>* curr = list_Head->next();
        Node<T>* prev = list_Head;

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

    ~S_list() {
        while (!empty())
            pop_front();
    }
};

int main() {
    S_list<int> l;
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

    l.erase(1);

    l.display();

    return 0;
}
