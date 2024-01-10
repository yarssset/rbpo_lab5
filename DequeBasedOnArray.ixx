module;
#include <iostream>
using namespace std;

export module dynamic_structure: DequeBasedOnArray;

import :AbstractClass;
export namespace dynamic_structure
{
    template <typename T>
    class DequeBasedOnArray : public AbstractClass<T> {
        T* elements;
        const int capacity = 150;
        int front;
        int rear;
        int size;

        void resize() {
            T* newElements = new T[capacity * 2];
            int j = 0;
            for (int i = front; i != rear; i = (i + 1) % capacity) {
                newElements[j] = elements[i];
                j++;
            }
            delete[] elements;
            elements = newElements;
            front = 0;
            rear = j;
        }

    public:
        int GetSize() const override {
            return size;
        }

        void clear() {
            front = 0;
            rear = 0;
            size = 0;
        }

        bool PushFront(const T& element) {
            if (size == capacity) {
                resize();
            }
            front = (front - 1 + capacity) % capacity;
            elements[front] = element;
            size++;
            return true;
        }

        bool PushBack(const T& element) {
            if (size == capacity) {
                resize();
            }
            elements[rear] = element;
            rear = (rear + 1) % capacity;
            size++;
            return true;
        }

        bool PopFront(T& element) {
            if (size == 0) {
                return false;
            }
            element = elements[front];
            front = (front + 1) % capacity;
            size--;
            return true;
        }

        bool PopBack(T& element) {
            if (size == 0) {
                return false;
            }
            rear = (rear - 1 + capacity) % capacity;
            element = elements[rear];
            size--;
            return true;
        }

        bool PeekFront(T& element) const {
            if (size == 0) {
                return false;
            }
            element = elements[front];
            return true;
        }

        bool PeekBack(T& element) const {
            if (size == 0) {
                return false;
            }
            element = elements[(rear - 1 + capacity) % capacity];
            return true;
        }

        DequeBasedOnArray() : elements(new T[capacity]), front(0), rear(0), size(0) {}
        DequeBasedOnArray(const DequeBasedOnArray<T>& other) : DequeBasedOnArray() {
            *this = other;
        }
        DequeBasedOnArray(DequeBasedOnArray<T>&& other) noexcept : elements(nullptr), front(0), rear(0), size(0) {
            *this = std::move(other);
        }
        DequeBasedOnArray(std::initializer_list<T> ilist) : DequeBasedOnArray() {
            *this = ilist;
        }
        ~DequeBasedOnArray() override {
            delete[] elements;
        }
        DequeBasedOnArray<T>& operator=(const DequeBasedOnArray<T>& other) {
            if (this != &other) {
                delete[] elements;
                elements = new T[other.capacity];
                front = other.front;
                rear = other.rear;
                size = other.size;
                for (int i = 0; i < size; i++) {
                    elements[i] = other.elements[i];
                }
            }
            return *this;
        }
        DequeBasedOnArray<T>& operator=(DequeBasedOnArray<T>&& other) noexcept {
            if (this != &other) {
                delete[] elements;
                elements = other.elements;
                front = other.front;
                rear = other.rear;
                size = other.size;
                other.elements = nullptr;
                other.front = 0;
                other.rear = 0;
                other.size = 0;
            }
            return *this;
        }
        DequeBasedOnArray<T>& operator=(std::initializer_list<T> ilist) {
            delete[] elements;
            elements = new T[ilist.size()];
            front = 0;
            rear = 0;
            size = 0;
            for (const T& element : ilist) {
                PushBack(element);
            }
            return *this;
        }

        friend std::ostream& operator<<(std::ostream& os, const DequeBasedOnArray<T>& deque) {
            for (int i = deque.front; i != deque.rear; i = (i + 1) % deque.capacity) {
                os << deque.elements[i] << " ";
            }
            return os;
        }
    };
}