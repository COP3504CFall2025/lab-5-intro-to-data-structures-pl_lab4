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
            data_[i] = other.data_[i];
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
            this -> data_[i] = other.data_[i];
        }

        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = 0;
        back_ = other.back_;
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
            T* new_array = new T[capacity_ * 2];
            for(std::size_t i = 0; i < size_; ++i){
                new_array[i + 1] = data_[i];
            }
            delete[] data_;
            data_ = new_array;
            capacity_ *= 2;
        }
        data_[0] = item;
    }

    void pushBack(const T& item) override{
        if(size_ >= capacity_){
            T* new_array = new T[capacity_ * 2];
            for(std::size_t i = 0; i < size_; ++i){
                new_array[i] = data_[i];
            }
            delete[] data_;
            data_ = new_array;
            capacity_ *= 2;
        }
        data_[size_++] = item;
    }

    // Deletion
    T popFront() override{
        if (size_ == 0) {
            throw std::runtime_error("Empty deque");
        }
        T temp = data_[0];
        for(size_t i = 0; i < size_ - 1; ++i){
            data_[i] = data_[i + 1];
        }
        --size_;
        return data_[0];
    }

    T popBack() override{
        if (size_ == 0) {
            throw std::runtime_error("Empty deque");
        }
        if(size_ != 0){
            T temp = data_[size_ - 1];
            data_[size_] = 0;
            size_--;
            return data_[size_];
        }
        else{
            return 0;
        }
    }

    // Access
    const T& front() const override{
        if (size_ == 0) {
            throw std::runtime_error("Empty deque");
        }
        return data_[0];
    }
    const T& back() const override{
        if (size_ == 0) {
            throw std::runtime_error("Empty deque");
        }
        return data_[size_ - 1];
    }

    // Getters
    std::size_t getSize() const noexcept override{
        return size_;
    }

};
