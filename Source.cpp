#include <iostream>
#include <stdexcept> 

template <typename T>
class MyVector {
private:
    T* data;
    int capacity_;
    int size_;

public:

    MyVector() : data(nullptr), capacity_(0), size_(0) {}

    ~MyVector() {
        delete[] data;
    }

    MyVector(const MyVector& other) :
        capacity_(other.capacity_),
        size_(other.size_)
    {
        data = new T[capacity_];
        for (int i = 0; i < size_; ++i) {
            data[i] = other.data[i];
        }
    }

    MyVector& operator=(const MyVector& other) {
        if (this != &other) {
            delete[] data;
            capacity_ = other.capacity_;
            size_ = other.size_;
            data = new T[capacity_];
            for (int i = 0; i < size_; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    T& at(int index) {
        if (index < 0 || index >= size_) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[index];
    }

    void push_back(const T& value) {
        if (size_ == capacity_) {
            capacity_ = (capacity_ == 0) ? 1 : capacity_ * 2;
            T* newData = new T[capacity_];
            for (int i = 0; i < size_; ++i) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
        }
        data[size_++] = value;
    }

    int size() const {
        return size_;
    }

    int capacity() const {
        return capacity_;
    }
};

int main() {
    MyVector<int> myVec;

    myVec.push_back(1);
    myVec.push_back(2);
    myVec.push_back(3);
    myVec.push_back(4);

    try {
        std::cout << "Ёлемент с индексом 1: " << myVec.at(1) << std::endl;
        std::cout << "Ёлемент с индексом 1: " << myVec.at(5) << std::endl;
    }
    catch (const std::out_of_range& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::cout << "Size: " << myVec.size() << std::endl;
    std::cout << "Capacity: " << myVec.capacity() << std::endl;

    return 0;
}
