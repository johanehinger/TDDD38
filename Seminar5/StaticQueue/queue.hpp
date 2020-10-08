#include <iostream>

template <typename T, size_t N>
class Queue
{
    T *queue;
    size_t size;
    size_t end;

public:
    Queue();
    void enqueue(T value);
    T dequeue();
    bool empty();
    bool full();
    void clear();
    T &front();
};

// Constructor
template<typename T, size_t N>
Queue<T, N>::Queue() : size(N), end(0) {
    queue = new T [size];
}

template<typename T, size_t N>
void Queue<T, N>::enqueue(T value) {
    if (full) {
        exit(EXIT_FAILURE);
    }
    end += 1;
    queue[end] = value;   
}

template<typename T, size_t N>
T Queue<T, N>::dequeue() {
    if (empty) {
        exit(EXIT_FAILURE);
    }
    end -= 1;
    return queue[end];
}