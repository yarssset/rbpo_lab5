#include <iostream>
#include "dynamic_structure.ixx"
using namespace dynamic_structure;
using namespace std;

template <typename T>
void view(AbstractClass<T>& structure, const std::initializer_list<T>& elements) {
    cout << "Add elements: ";
    for (const auto& element : elements) {
        structure.Push(element);
        cout << element << "  ";
    }
    cout << endl;

    cout << "Size: " << structure.GetSize() << endl;

    T topElement;
    if (structure.Peek(topElement)) {
        cout << "Top: " << topElement << endl;
    }

    T popElement;
    if (structure.Pop(popElement)) {
        cout << "Pop: " << popElement << endl;
    }

    cout << "All elements: ";
    while (structure.GetSize() > 0) {
        structure.Peek(topElement);
        cout << topElement << "  ";
        structure.Pop(topElement);
    }
    cout << endl;
}

int main() {
    cout << "Demonstration of the work:" << endl << endl;

    cout << "StackBasedOnUnidirectionalCyclicLinkedList" << endl;
    StackBasedOnUnidirectionalCyclicLinkedList<int> stack;
    view(stack, { 1, 2, 3, 4, 5 });

    cout << "------------------------------" << endl;

    cout << "DequeBasedOnArray" << endl;
    DequeBasedOnArray<int> deque;
    view(deque, { 6, 7, 8, 9, 10 });

    return 0;
}