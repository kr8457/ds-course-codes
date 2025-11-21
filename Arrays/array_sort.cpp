#include <iostream>
using namespace std;

int main() {
    const int size = 5;
    int arr[size] = {40, 10, 50, 20, 30};

    // Array of pointers
    int* ptr[size];

    // Make each pointer point to an element of arr
    for(int i = 0; i < size; i++)
        ptr[i] = &arr[i];

          cout << "Array in sorted order:\n";
    for(int i = 0; i < size; i++)
        cout << *ptr[i] << " ";

    // Sort the pointers based on the values they point to
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (*ptr[j] < *ptr[i]) {
                int* temp = ptr[i];
                ptr[i] = ptr[j];
                ptr[j] = temp;
            }
        }
    }

    // Display the array values in sorted order (without sorting the array itself)
    cout << "Array in sorted order:\n";
    for(int i = 0; i < size; i++)
        cout << *ptr[i] << " ";

    cout << "\n\nOriginal array remains unchanged:\n";
    for(int i = 0; i < size; i++)
        cout << arr[i] << " ";

    return 0;
}
