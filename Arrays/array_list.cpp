#include <iostream>

template<typename T, size_t size>
class list {
    T arr[size];     
    size_t N;        

public:

    
    template<size_t N2>
    list(T (&a)[N2]) {
        static_assert(N2 <= size, "Array too big!");
        for (size_t i = 0; i < N2; i++)
            arr[i] = a[i];
        N = N2;
    }

    void insert_front(T value) {
        for (int i = N; i > 0; i--)
            arr[i] = arr[i - 1];
        arr[0] = value;
        N++;
    }

    void insert_end(T value) {
        arr[N++] = value;
    }

    void insert_btw(T value, size_t pos) {
        for (size_t i = N; i > pos; i--)
            arr[i] = arr[i - 1];
        arr[pos] = value;
        N++;
    }

    void delete_front() {
        for (size_t i = 0; i < N - 1; i++)
            arr[i] = arr[i + 1];
        N--;
    }

    void delete_end() {
        N--;
    }

    void delete_btw(size_t pos) {
        for (size_t i = pos; i < N - 1; i++)
            arr[i] = arr[i + 1];
        N--;
    }

    void search(T value) {
        int idx = -1;
        for (size_t i = 0; i < N; i++)
            if (arr[i] == value) idx = i;

        std::cout << "location is: " << idx << std::endl;
    }

    void display() {
        for (size_t i = 0; i < N; i++)
            std::cout << arr[i] << " ";
        std::cout << "\n-------------------------\n";
    }
};

int main() {
    int arrt[] = {1,2,3,4,5};
    list<int, 10> l(arrt);

    l.display();
    l.insert_front(120);
    l.display();
    l.insert_end(12);
    l.display();
    l.insert_btw(44, 4);
    l.display();
    l.search(44);
    l.display();
    l.delete_front();
    l.display();
    l.delete_end();
    l.display();
    l.delete_btw(3);
    l.display();
}
