#include<iostream>

template <typename T>
class Node {
private:
    T element;
    Node<T>* next_Node;
    Node<T>* prev_Node;

public:
    Node(T e, Node<T>* n = nullptr, Node<T>* p = nullptr)
        : element(e), next_Node(n), prev_Node(p) {}

    void setelement(T e) { element = e; }
    void setnext(Node<T>* n) { next_Node = n; }
    void setprev(Node<T>* p) { prev_Node = p; }

    T retrieve() const { return element; }
    Node<T>* next() const { return next_Node; }
    Node<T>* prev() const { return prev_Node; }
};

template <typename T>
class D_list {
private:
    Node<T>* head_Node;

public:
    D_list() : head_Node(nullptr) {}

    bool empty() const { return head_Node == nullptr; }
    Node<T>* head() const { return head_Node; }

    T front() const {
        if (empty()) throw "Underflow!";
        return head_Node->retrieve();
    }

    T end() const {
        if (empty()) throw "Underflow!";
        return head_Node->prev()->retrieve();
    }

    void display() const {
        if (empty()) return;
        Node<T>* temp = head_Node;
        do {
            std::cout << " " << temp->retrieve();
            temp = temp->next();
        } while (temp != head_Node);
        std::cout << std::endl;
    }

    void reverse_display() const {
        if (empty()) return;
        Node<T>* temp = head_Node->prev();
        Node<T>* tail = temp;
        do {
            std::cout << " " << temp->retrieve();
            temp = temp->prev();
        } while (temp != tail);
        std::cout << std::endl;
    }

    int size() const {
        if (empty()) return 0;
        int count = 0;
        Node<T>* temp = head_Node;
        do {
            count++;
            temp = temp->next();
        } while (temp != head_Node);
        return count;
    }

    int count(T n) const {
        if (empty()) return 0;
        int c = 0;
        Node<T>* temp = head_Node;
        do {
            if (temp->retrieve() == n) c++;
            temp = temp->next();
        } while (temp != head_Node);
        return c;
    }

    void push_front(T n) {
        Node<T>* newNode = new Node<T>(n);

        if (empty()) {
            newNode->setnext(newNode);
            newNode->setprev(newNode);
            head_Node = newNode;
        }
        else {
            Node<T>* tail = head_Node->prev();
            newNode->setnext(head_Node);
            newNode->setprev(tail);
            tail->setnext(newNode);
            head_Node->setprev(newNode);
            head_Node = newNode;
        }
    }

    void push_end(T n) {
        if (empty()) {
            push_front(n);
            return;
        }

        Node<T>* newNode = new Node<T>(n);
        Node<T>* tail = head_Node->prev();

        newNode->setnext(head_Node);
        newNode->setprev(tail);
        tail->setnext(newNode);
        head_Node->setprev(newNode);
    }

    T pop_front() {
        if (empty()) throw "Underflow!";

        T val = head_Node->retrieve();

        if (head_Node->next() == head_Node) {
            delete head_Node;
            head_Node = nullptr;
        }
        else {
            Node<T>* tail = head_Node->prev();
            Node<T>* temp = head_Node;

            head_Node = head_Node->next();
            head_Node->setprev(tail);
            tail->setnext(head_Node);

            delete temp;
        }

        return val;
    }

    void pop_end() {
        if (empty()) throw "Underflow!";

        if (head_Node->next() == head_Node) {
            delete head_Node;
            head_Node = nullptr;
            return;
        }

        Node<T>* tail = head_Node->prev();
        Node<T>* newTail = tail->prev();

        newTail->setnext(head_Node);
        head_Node->setprev(newTail);

        delete tail;
    }

    int erase(T n) {
        if (empty()) throw "Underflow!";

        int removed = 0;
        Node<T>* curr = head_Node;
        Node<T>* nextNode;

        do {
            nextNode = curr->next();

            if (curr->retrieve() == n) {
                if (curr->next() == curr) {
                    delete curr;
                    head_Node = nullptr;
                    return 1;
                }

                Node<T>* prev = curr->prev();
                Node<T>* next = curr->next();

                prev->setnext(next);
                next->setprev(prev);

                if (curr == head_Node)
                    head_Node = next;

                delete curr;
                removed++;
            }

            curr = nextNode;

        } while (curr != head_Node);

        return removed;
    }

    ~D_list() {
        while (!empty())
            pop_front();
    }
};

int main() {
    D_list<int> l;
    l.push_end(1);
    l.push_front(1);
    l.push_front(2);
    l.push_end(3);
    l.push_end(1);

    l.display();
    l.reverse_display();

    std::cout << "Size: " << l.size() << std::endl;
    std::cout << "Count of 1: " << l.count(1) << std::endl;
    std::cout << "Front: " << l.front() << std::endl;
    std::cout << "End: " << l.end() << std::endl;

    l.erase(1);

    l.display();
    l.reverse_display();

    return 0;
}
