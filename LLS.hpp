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
        if (list.getCount() == 0) {
            throw std::runtime_error("Empty stack");
        }

        T temp = list.getHead() -> getData();
        list.removeHead();
        return temp;
    }

    // Access
    T peek() const override{
        if (list.getCount() == 0) {
            throw std::runtime_error("Empty stack");
        }
        
        return list.getHead() -> getData();
    }

    //Getters
    std::size_t getSize() const noexcept override{
        return list.getCount();
    }

    void PrintForward() const{
        list.printForward();
    }

    void PrintReverse() const{
        list.printReverse();
    }
};