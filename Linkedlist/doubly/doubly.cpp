#include<iostream>

// ================= TEMPLATE NODE =================
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

// ================= TEMPLATE DOUBLY LINKED LIST =================
template <typename T>
class D_list {
private:
    Node<T>* head_Node;
    Node<T>* tail_Node;

public:
    D_list() : head_Node(nullptr), tail_Node(nullptr) {}

    bool empty() const { return head_Node == nullptr; }

    T front() const {
        if (empty()) throw "Underflow!";
        return head_Node->retrieve();
    }

    T end() const {
        if (empty()) throw "Underflow!";
        return tail_Node->retrieve();
    }

    // Display forward
    void display() const {
        Node<T>* temp = head_Node;
        while (temp != nullptr) {
            std::cout << " " << temp->retrieve();
            temp = temp->next();
        }
        std::cout << std::endl;
    }

    // Display backward
    void reverse_display() const {
        Node<T>* temp = tail_Node;
        while (temp != nullptr) {
            std::cout << " " << temp->retrieve();
            temp = temp->prev();
        }
        std::cout << std::endl;
    }

    // Size
    int size() const {
        int count = 0;
        Node<T>* temp = head_Node;
        while (temp != nullptr) {
            count++;
            temp = temp->next();
        }
        return count;
    }

    // Count occurrences
    int count(T n) const {
        int c = 0;
        Node<T>* temp = head_Node;
        while (temp != nullptr) {
            if (temp->retrieve() == n)
                c++;
            temp = temp->next();
        }
        return c;
    }

    // Push front
    void push_front(T n) {
        Node<T>* newNode = new Node<T>(n, head_Node, nullptr);

        if (empty()) {
            head_Node = tail_Node = newNode;
        }
        else {
            head_Node->setprev(newNode);
            head_Node = newNode;
        }
    }

    // Push end
    void push_end(T n) {
        Node<T>* newNode = new Node<T>(n, nullptr, tail_Node);

        if (empty()) {
            head_Node = tail_Node = newNode;
        }
        else {
            tail_Node->setnext(newNode);
            tail_Node = newNode;
        }
    }

    // Pop front
    T pop_front() {
        if (empty()) throw "Underflow!";

        T val = head_Node->retrieve();
        Node<T>* temp = head_Node;

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

    // Pop end
    void pop_end() {
        if (empty()) throw "Underflow!";

        Node<T>* temp = tail_Node;

        if (head_Node == tail_Node) {
            head_Node = tail_Node = nullptr;
        }
        else {
            tail_Node = tail_Node->prev();
            tail_Node->setnext(nullptr);
        }

        delete temp;
    }

    // Erase all occurrences of value
    int erase(T n) {
        if (empty()) throw "Underflow!";

        int removed = 0;
        Node<T>* curr = head_Node;

        while (curr != nullptr) {
            if (curr->retrieve() == n) {
                Node<T>* nextNode = curr->next();
                Node<T>* prevNode = curr->prev();

                if (curr == head_Node)
                    head_Node = nextNode;

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

    // Destructor
    ~D_list() {
        while (!empty())
            pop_front();
    }
};


// ================= MAIN (TESTING) =================
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

    std::cout << "Deleting all 1s..." << std::endl;
    l.erase(1);

    l.display();
    l.reverse_display();

    return 0;
}
