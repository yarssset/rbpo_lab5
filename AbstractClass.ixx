module;
#include <iostream>
export module dynamic_structure: AbstractClass;

export namespace dynamic_structure
{
    template <typename T>
    class AbstractClass {
    public:
        virtual int GetSize() const = 0;
        virtual bool PushFront(const T& element);
        virtual bool PopFront(T& element);
        virtual bool PushBack(const T& element);
        virtual bool PopBack(T& element);
        virtual bool PeekFront(T& element) const;
        virtual bool PeekBack(T& element) const;

        virtual bool Push(const T& element) = 0;
        virtual bool Pop(T& element) = 0;
        virtual bool Peek(T& element) const = 0;
        virtual ~AbstractClass() {};
    };
}
