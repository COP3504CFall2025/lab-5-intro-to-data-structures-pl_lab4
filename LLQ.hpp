#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLQ : public QueueInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLQ() = default;
    LLQ(const LLQ& other) = default;
    LLQ(LLQ&& other) noexcept = default;
    LLQ& operator=(const LLQ& other) = default;
    LLQ& operator=(LLQ&& other) noexcept = default;
    ~LLQ() = default;

    // Insertion
    void enqueue(const T& item) override{
        list.addTail(item);
    }

    // Deletion
    T dequeue() override{
        if (list.getCount() == 0) {
            throw std::runtime_error("Empty queue");
        }

        T temp = list.getHead() -> getData();
        list.removeHead();
        return temp;
    }

    // Access
    T peek() const override{
        if (list.getCount() == 0) {
            throw std::runtime_error("Queue is empty");
        }
        
        return list.getHead() -> getData();
    }

    // Getter
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