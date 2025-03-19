#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class MaxHeap {
private:
    int heap_size = 0;
    void buildMaxHeap(vector<T>& array);
    void maxHeapify(int i, vector<T>& array);
    void swap(T* value1, T* value2);

public:
    MaxHeap() {}

    vector<T> heapSort(vector<T>& array);
};

template <typename T>
vector<T> MaxHeap<T>::heapSort(vector<T>& array) {
    this->heap_size = array.size();
    this->buildMaxHeap(array);

    for (int i = array.size() - 1; i > 0; i--) {
        swap(&array[i], &array[0]);
        this->heap_size--;
        maxHeapify(0, array);
    }

    return array;
}

template <typename T>
void MaxHeap<T>::buildMaxHeap(vector<T>& array) {
    for (int i = array.size() / 2 - 1; i >= 0; i--) {
        maxHeapify(i, array);
    }
}

template <typename T>
void MaxHeap<T>::maxHeapify(int i, vector<T>& array) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int max = i;

    if (left < this->heap_size && array[left] > array[max])
        max = left;

    if (right < this->heap_size && array[right] > array[max])
        max = right;

    if (max != i) {
        swap(&array[max], &array[i]);
        maxHeapify(max, array);
    }
}

template <typename T>
void MaxHeap<T>::swap(T* value1, T* value2) {
    T temp = *value1;
    *value1 = *value2;
    *value2 = temp;
}

