#include<iostream>

template <typename T>
class Node {
private:
    T element;
    Node<T>* next_Node;

public:
    Node(T e, Node<T>* n) : element(e), next_Node(n) {}

    void setelement(T e) {
        element = e;
    }

    void setnext(Node<T>* n) {
        next_Node = n;
    }

    T retrieve() const {
        return element;
    }

    Node<T>* next() const {
        return next_Node;
    }
};

template <typename T>
class S_list {
private:
    Node<T>* list_Head;

public:
    S_list() : list_Head(nullptr) {}

    bool empty() const;
    Node<T>* head() const;
    T front() const;
    void display() const;
    int size() const;
    int count(T) const;
    
    T end() const;
    void push_front(T);
    T pop_front();
    void push_end(T);
    void pop_end();
    int erase(T);

    ~S_list() {
        while (!empty())
            pop_front();
    }
};

template <typename T>
bool S_list<T>::empty() const {
    return list_Head == nullptr;
}

template <typename T>
Node<T>* S_list<T>::head() const {
    return list_Head;
}

template <typename T>
T S_list<T>::front() const {
    if (empty()) throw "Underflow";
    return list_Head->retrieve();
}

template <typename T>
void S_list<T>::push_front(T n) {
    list_Head = new Node<T>(n, head());
}

template <typename T>
void S_list<T>::push_end(T n) {
    if (empty()) {
        push_front(n);
    } else {
        Node<T>* temp = list_Head;
        while (temp->next() != nullptr)
            temp = temp->next();

        temp->setnext(new Node<T>(n, nullptr));
    }
}

template <typename T>
T S_list<T>::pop_front() {
    if (empty()) throw "Underflow";

    Node<T>* temp = list_Head;
    T val = temp->retrieve();
    list_Head = temp->next();
    delete temp;
    return val;
}

template <typename T>
void S_list<T>::pop_end() {
    if (empty()) throw "Underflow";

    if (list_Head->next() == nullptr) {
        delete list_Head;
        list_Head = nullptr;
        return;
    }

    Node<T>* temp = list_Head;
    while (temp->next()->next() != nullptr)
        temp = temp->next();

    delete temp->next();
    temp->setnext(nullptr);
}

template <typename T>
T S_list<T>::end() const {
    if (empty()) throw "Underflow";

    Node<T>* temp = list_Head;
    while (temp->next() != nullptr)
        temp = temp->next();

    return temp->retrieve();
}

template <typename T>
int S_list<T>::size() const {
    int count = 0;
    Node<T>* temp = list_Head;

    while (temp != nullptr) {
        count++;
        temp = temp->next();
    }
    return count;
}

template <typename T>
int S_list<T>::count(T n) const {
    int cnt = 0;
    Node<T>* temp = list_Head;

    while (temp != nullptr) {
        if (temp->retrieve() == n)
            cnt++;

        temp = temp->next();
    }
    return cnt;
}

template <typename T>
int S_list<T>::erase(T n) {
    if (empty())
        throw "Underflow";

    Node<T>* ptr = list_Head;
    Node<T>* prev = nullptr;
    int count = 0;

    while (ptr != nullptr) {
        if (ptr->retrieve() == n) {
            if (prev == nullptr) {
                list_Head = ptr->next();
                delete ptr;
                ptr = list_Head;
            } else {
                prev->setnext(ptr->next());
                delete ptr;
                ptr = prev->next();
            }
            count++;
        } else {
            prev = ptr;
            ptr = ptr->next();
        }
    }
    return count;
}

template <typename T>
void S_list<T>::display() const {
    Node<T>* temp = list_Head;
    while (temp != nullptr) {
        std::cout << temp->retrieve() << " ";
        temp = temp->next();
    }
    std::cout << std::endl;
}

int main() {
    S_list<int> l;

    l.push_end(12);
    l.push_front(1);
    l.push_front(12);
    l.push_front(12);

    l.display();
    std::cout << "Size: " << l.size() << std::endl;
    std::cout << "Count: " << l.count(12) << std::endl;
    std::cout << "Front: " << l.front() << std::endl;
    std::cout << "End: " << l.end() << std::endl;

    std::cout << "Erased: " << l.erase(12) << std::endl;

    std::cout << "After erase: ";
    l.display();

    return 0;
}
