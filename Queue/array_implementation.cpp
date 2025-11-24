#include<iostream>
using namespace std;

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

    cout << "Front: " << q.front() << endl;
    cout << "Dequeue: " << q.dequeue() << endl;
    cout << "New Front: " << q.front() << endl;
    cout << "Size: " << q.size() << endl;

    return 0;
}
