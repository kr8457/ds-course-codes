#include<iostream>

class Queue_Array {
private:
    int arr[100];
    int frontIndex;
    int rearIndex;

public:
    Queue_Array() : frontIndex(0), rearIndex(-1) {}

    bool isEmpty() const {
        return rearIndex < frontIndex;
    }

    bool isFull() const {
        return rearIndex == 99;
    }

    void enqueue(int x) {
        if (isFull()) throw "Overflow!";
        arr[++rearIndex] = x;
    }

    int dequeue() {
        if (isEmpty()) throw "Underflow!";
        return arr[frontIndex++];
    }

    int front() const {
        if (isEmpty()) throw "Underflow!";
        return arr[frontIndex];
    }

    int size() const {
        return (isEmpty() ? 0 : rearIndex - frontIndex + 1);
    }
};


int main() {
    Queue_Array q;

    q.enqueue(5);
    q.enqueue(10);
    q.enqueue(15);

    std::cout << "Front: " << q.front() << std::endl;
    std::cout << "Dequeue: " << q.dequeue() << std::endl;
    std::cout << "New Front: " << q.front() << std::endl;
    std::cout << "Size: " << q.size() << std::endl;

    return 0;
}
