#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>

template <typename T>
class ABDQ : public DequeInterface<T> {
private:
    T* data_;                 // underlying dynamic array
    std::size_t capacity_;    // total allocated capacity
    std::size_t size_;        // number of stored elements
    std::size_t front_;       // index of front element
    std::size_t back_;        // index after the last element (circular)

    static constexpr std::size_t SCALE_FACTOR = 2;

public:
    // Big 5
    ABDQ(){
        capacity_ = 4;
        size_ = 0;
        front_ = 0;
        back_ = 0;
        data_ = new T[4];
    }

    explicit ABDQ(std::size_t capacity){
        capacity_ = capacity;
        size_ = 0;
        front_ = 0;
        back_ = 0;
        data_ = new T[capacity];
    }

    ABDQ(const ABDQ& other): data_(new T[other.capacity_]), capacity_(other.capacity_), size_(other.size_), front_(0), back_(other.back_) 
    {
        for (std::size_t i = 0; i < other.size_; ++i) {
            data_[i] = other.data_[(other.front_ + i) % other.capacity_];
        }
    }

    ABDQ(ABDQ&& other) noexcept : data_(other.data_), capacity_(other.capacity_), size_(other.size_), front_(other.front_), back_(other.back_){
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
        other.front_ = 0;
        other.back_ = 0;
    }

    ABDQ& operator=(const ABDQ& other){
        if(this == &other){
            return *this;
        }

        T* newData = new T[other.capacity_];

        delete[] data_;

        for (std::size_t i = 0; i < other.size_; ++i) {
            newData[i] = other.data_[(other.front_ + i) % other.capacity_];
        }

        data_ = newData;

        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = 0;
        back_ = other.size_;

        return *this;
    }

    ABDQ& operator=(ABDQ&& other) noexcept{
        if(this == &other){
            return *this;
        }

        delete[] data_;
        data_ = other.data_;
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;

        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
        other.front_ = 0;
        other.back_ = 0;
        return *this;
    }

    ~ABDQ(){
        delete[] data_;
    }

    // Insertion
    void pushFront(const T& item) override{
        if(size_ >= capacity_){
            T* new_array = new T[capacity_ * SCALE_FACTOR];
            for(std::size_t i = 0; i < size_; ++i){
                new_array[i] = data_[(front_ + i) % capacity_];
            }
            delete[] data_;
            data_ = new_array;
            capacity_ *= 2;
            front_ = 0;
            back_ = size_;
        }
        front_ = (front_ + capacity_ - 1) % capacity_;
        data_[front_] = item;
        ++size_;
    }

    void pushBack(const T& item) override{
        if(size_ >= capacity_){
            T* new_array = new T[capacity_ * 2];
            for(std::size_t i = 0; i < size_; ++i){
                new_array[i] = data_[(front_ + i) % capacity_];
            }
            delete[] data_;
            data_ = new_array;
            capacity_ *= 2;
            front_ = 0;
            back_ = size_;
        }
        data_[back_] = item;
        back_ = (back_ + 1) % capacity_;
        ++size_;
    }

    // Deletion
    T popFront() override{
        if (size_ == 0) {
            throw std::runtime_error("Empty deque");
        }
        T temp = data_[front_];
        front_ = (front_ + 1) % capacity_;
        --size_;
        return temp;
    }

    T popBack() override{
        if (size_ == 0) {
            throw std::runtime_error("Empty deque");
        }
        back_ = (back_ + capacity_ - 1) % capacity_;
        T temp = data_[back_];
        --size_;
        return temp;
    }

    // Access
    const T& front() const override{
        if (size_ == 0) {
            throw std::runtime_error("Empty deque");
        }
        return data_[front_];
    }
    const T& back() const override{
        if (size_ == 0) {
            throw std::runtime_error("Empty deque");
        }
        return data_[(back_ + capacity_ - 1) % capacity_];
    }

    // Getters
    std::size_t getSize() const noexcept override{
        return size_;
    }

};
