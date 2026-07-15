#pragma once
#include <iostream>
#include <algorithm>
using namespace std;

template<typename T>
class Inventory {
private:
    T* pItems_;
    int capacity_;
    int size_;

public:
    Inventory(int capacity)
        : capacity_(capacity), size_(0) {
        pItems_ = new T[capacity_]();
    }

    Inventory(const Inventory<T>& other)
        : capacity_(other.capacity_), size_(other.size_) {
        pItems_ = new T[capacity_]();
        for (int i = 0; i < size_; i++) {
            pItems_[i] = other.pItems_[i];
        }
    }

    Inventory<T>& operator=(const Inventory<T>& other) {
        if (this == &other) {
            return *this;
        }

        delete[] pItems_;

        capacity_ = other.capacity_;
        size_ = other.size_;
        pItems_ = new T[capacity_]();
        for (int i = 0; i < size_; i++) {
            pItems_[i] = other.pItems_[i];
        }

        return *this;
    }

    ~Inventory() {
        delete[] pItems_;
    }

    void Resize(int newCapacity) {
        T* newItems = new T[newCapacity]();
        for (int i = 0; i < size_; i++) {
            newItems[i] = pItems_[i];
        }
        delete[] pItems_;
        pItems_ = newItems;
        capacity_ = newCapacity;
    }

    bool AddItem(const T& item) {
        if (size_ >= capacity_) {
            int oldCapacity = capacity_;
            int newCapacity = (capacity_ == 0) ? 1 : capacity_ * 2;
            Resize(newCapacity);
            cout << "-> 인벤토리 자동 확장! (" << oldCapacity << " -> " << newCapacity << ")" << endl;
        }
        pItems_[size_] = item;
        size_++;
        return true;
    }

    bool RemoveLastItem() {
        if (size_ <= 0) {
            return false;
        }
        size_--;
        return true;
    }

    void PrintAllItems() const {
        cout << "[ 인벤토리 (" << size_ << "/" << capacity_ << ") ]" << endl;
        for (int i = 0; i < size_; i++) {
            cout << (i + 1) << ". ";
            pItems_[i].PrintInfo();
            cout << endl;
        }
    }

    int GetSize() const { return size_; }
    int GetCapacity() const { return capacity_; }

    T& operator[](int index) { return pItems_[index]; }
    const T& operator[](int index) const { return pItems_[index]; }

    T* begin() { return pItems_; }
    T* end() { return pItems_ + size_; }
    const T* begin() const { return pItems_; }
    const T* end() const { return pItems_ + size_; }

    bool RemoveItemAt(int index) {
        if (index < 0 || index >= size_) {
            return false;
        }
        for (int i = index; i < size_ - 1; i++) {
            pItems_[i] = pItems_[i + 1];
        }
        size_--;
        return true;
    }

    template<typename Compare>
    void SortItems(Compare compareFunc) {
        std::sort(pItems_, pItems_ + size_, compareFunc);
    }
};
