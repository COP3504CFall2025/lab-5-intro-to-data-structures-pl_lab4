#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLS : public StackInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLS() = default;
    LLS(const LLS& other) = default;
    LLS(LLS&& other) noexcept = default;
    LLS& operator=(const LLS& other) = default;
    LLS& operator=(LLS&& other) noexcept = default;
    ~LLS() = default;

    // Insertion
    void push(const T& item) override{
        list.addHead(item);
    }

    // Deletion
    T pop() override{
        T temp = list -> head;
        list.removeHead();
        return temp;
    }

    // Access
    T peek() const override{
        return list -> head;
    }

    //Getters
    std::size_t getSize() const noexcept override{
        return list -> count;
    }

    void PrintForward() const{
        list.PrintForward();
    }

    void PrintReverse() const{
        list.PrintReverse();
    }
};