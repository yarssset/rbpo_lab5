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
            delete[] elements;
            front = 0;
            rear = 0;
            size = 0;
        }

        bool Push(const T& element) override {
            if (size == capacity) {
                resize();
            }
            elements[rear] = element;
            rear = (rear + 1) % capacity;
            size++;
            return true;
        }

        bool Pop(T& element) override {
            if (size == 0) {
                return false;
            }
            element = elements[front];
            front = (front + 1) % capacity;
            size--;
            return true;
        }

        bool Peek(T& element) const override {
            if (size == 0) {
                return false;
            }
            element = elements[front];
            return true;
        }

        DequeBasedOnArray() : elements(nullptr), front(0), rear(0), size(0) {
            elements = new T[capacity];
        }

        DequeBasedOnArray(const DequeBasedOnArray<T>& other) : elements(nullptr), front(0), rear(0), size(0) {
            *this = other;
        }

        DequeBasedOnArray(DequeBasedOnArray<T>&& other) : elements(nullptr), front(0), rear(0), size(0) {
            *this = std::move(other);
        }

        DequeBasedOnArray(std::initializer_list<T> ilist) : elements(nullptr), front(0), rear(0), size(0) {
            *this = ilist;
        }

        ~DequeBasedOnArray() override {
            clear();
        }

        DequeBasedOnArray<T>& operator=(const DequeBasedOnArray<T>& other) {
            if (this != &other) {
                clear();
                front = other.front;
                rear = other.rear;
                size = other.size;
                elements = new T[capacity];
                for (int i = 0; i < capacity; i++) {
                    elements[i] = other.elements[i];
                }
            }
            return *this;
        }

        DequeBasedOnArray<T>& operator=(DequeBasedOnArray<T>&& other) {
            if (this != &other) {
                clear();
                front = other.front;
                rear = other.rear;
                size = other.size;
                elements = other.elements;
                other.elements = nullptr;
                other.front = 0;
                other.rear = 0;
                other.size = 0;
            }
            return *this;
        }

        DequeBasedOnArray<T>& operator=(std::initializer_list<T> ilist) {
            clear();
            for (const T& element : ilist) {
                Push(element);
            }
            return *this;
        }

        friend std::ostream& operator<<(std::ostream& os, const DequeBasedOnArray<T>& deque) {
            for (int i = deque.front; i != deque.rear; i = (i + 1) % capacity) {
                os << deque.elements[i] << " ";
            }
            return os;
        }
    };

}