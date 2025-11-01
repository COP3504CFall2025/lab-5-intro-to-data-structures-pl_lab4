#pragma once

#include <cstddef>
#include <stdexcept>
#include <iostream>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABQ : public QueueInterface<T>{

    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;

public:
    // Constructors + Big 5
    ABQ(){
        capacity_ = 1;
        curr_size_ = 0;
        array_ = new T[capacity_];
    }
    explicit ABQ(const size_t capacity){
        capacity_ = capacity;
        curr_size_ = 0;
        array_ = new T[capacity_];
    }

    ABQ(const ABQ& other): capacity_(other.capacity_), curr_size_(other.curr_size_), array_(new T[other.capacity_]){
        for(std::size_t i = 0; i < curr_size_; ++i){
            array_[i] = other.array_[i];
        }
    }

    ABQ& operator=(const ABQ& rhs){
        if (this == &rhs){
            return *this;
        }

        delete[] array_;

        capacity_ = rhs.capacity_;
        curr_size_ = rhs.curr_size_;
        array_ = new T[capacity_];

        for(std::size_t i = 0; i < curr_size_; ++i){
            array_[i] = rhs.array_[i];
        }

        return *this;
    }

    ABQ(ABQ&& other) noexcept: capacity_(other.capacity_), curr_size_(other.curr_size_), array_(other.array_) {
        other.array_ = nullptr;
        other.curr_size_ = 0;
        other.capacity_ = 0;
    }

    ABQ& operator=(ABQ&& rhs) noexcept{
        if (this == &rhs){
            return *this;
        } 

        delete[] array_;

        array_ = rhs.array_;
        curr_size_ = rhs.curr_size_;
        capacity_ = rhs.capacity_;

        rhs.array_ = nullptr;
        rhs.curr_size_ = 0;
        rhs.capacity_ = 0;
        return *this;
    }

    ~ABQ() noexcept{
        capacity_ = 0;
        curr_size_ = 0;
        delete[] array_;
    }

    // Getters
    [[nodiscard]] size_t getSize() const noexcept override{
        return curr_size_;
    }
    [[nodiscard]] size_t getMaxCapacity() const noexcept{
        return capacity_;
    }
    [[nodiscard]] T* getData() const noexcept{
        return array_;
    }

    // Insertion
    void enqueue(const T& data) override{
        if(curr_size_ >= capacity_){
            T* new_array = new T[capacity_ * scale_factor_];
            for(std::size_t i = 0; i < curr_size_; ++i){
                new_array[i] = array_[i];
            }
            delete[] array_;
            array_ = new_array;
            capacity_ *= scale_factor_;
        }
        array_[curr_size_++] = data;
    }

    // Access
    T peek() const override{
        if (curr_size_ == 0){
            throw std::runtime_error("Queue is empty");
        }
        return array_[0];
    }

    // Deletion
    T dequeue() override{
        if (curr_size_ == 0)
            throw std::runtime_error("Queue is empty");
        T temp = array_[0];
        for(size_t i = 0; i < curr_size_ - 1; ++i){
            array_[i] = array_[i + 1];
        }
        --curr_size_;

        if (curr_size_ > 0 && curr_size_ * 4 < capacity_) {
            size_t new_capacity = capacity_ / 2;
            if (new_capacity < 1)
                new_capacity = 1;
            T* new_array = new T[new_capacity];
            for (size_t i = 0; i < curr_size_ && i < new_capacity; ++i)
                new_array[i] = array_[i];
            delete[] array_;
            array_ = new_array;
            capacity_ = new_capacity;
        }
        return temp;
    }

    void PrintForward() const{
        for (size_t i = 0; i < curr_size_; ++i)
            std::cout << array_[i] << std::endl;
    }

    void PrintReverse() const{
        for (size_t i = curr_size_ - 1; i > 0; --i)
            std::cout << array_[i] << std::endl;
    }

};