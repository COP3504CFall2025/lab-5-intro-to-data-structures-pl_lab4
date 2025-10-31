#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <utility>



template <typename T>
class LLDQ : public DequeInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLDQ() = default;
    LLDQ(const LLDQ& other) = default;
    LLDQ(LLDQ&& other) noexcept = default;
    LLDQ& operator=(const LLDQ& other) = default;
    LLDQ& operator=(LLDQ&& other) noexcept = default;
    ~LLDQ() = default;

    // Core Insertion Operations
    void pushFront(const T& item) override{
        list.AddHead(item);
    }
    void pushBack(const T& item) override{
        list.AddTail(item);
    }

    // Core Removal Operations
    T popFront() override{
        if (list.getCount() == 0){
            throw std::runtime_error("Empty deque");
        }

        T* temp = list.getHead();
        T value = temp.getData();
        list.RemoveHead();
        return value;
    }
    T popBack() override{
        if (list.getCount() == 0){
            throw std::runtime_error("Empty deque");
        }

        T* temp = list.getTail();
        T value = temp.getData();
        list.RemoveTail();
        return value;
    }

    // Element Accessors
    const T& front() const override{
        if (list.getCount() == 0){
            throw std::runtime_error("Empty deque");
        }
        T* temp = list.getHead();
        T value = temp.getData();
        return value;
    }
    const T& back() const override{
        if (list.getCount() == 0){
            throw std::runtime_error("Empty deque");
        }
        T* temp = list.getTail();
        T value = temp.getData();
        return value;
    }

    // Getter
    std::size_t getSize() const noexcept override{
        return list.getCount();
    }

    void PrintForward() const{
        list.PrintForward();
    }

    void PrintReverse() const{
        list.PrintReverse();
    }
};






