#include<iostream>

class Stack_Array {
private:
    int arr[100];     // fixed size stack
    int topIndex;     // index of top element

public:
    Stack_Array() : topIndex(-1) {}

    bool isEmpty() const {
        return topIndex == -1;
    }

    bool isFull() const {
        return topIndex == 99;
    }

    void push(int x) {
        if (isFull()) throw "Overflow!";
        arr[++topIndex] = x;
    }

    int pop() {
        if (isEmpty()) throw "Underflow!";
        return arr[topIndex--];
    }

    int top() const {
        if (isEmpty()) throw "Underflow!";
        return arr[topIndex];
    }

    int size() const {
        return topIndex + 1;
    }
};


// ✅ MAIN to test array stack
int main() {
    Stack_Array s;

    s.push(5);
    s.push(10);
    s.push(15);

    std::cout << "Top: " << s.top() << std::endl;
    std::cout << "Pop: " << s.pop() << std::endl;
    std::cout << "New Top: " << s.top() << std::endl;
    std::cout << "Size: " << s.size() << std::endl;

    return 0;
}
