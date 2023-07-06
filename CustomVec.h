#ifndef CUSTOM_VEC_CUSTOMVEC_H
#define CUSTOM_VEC_CUSTOMVEC_H

#include <cstddef>

//simple vector implementation

template <class T>
class CustomVec {
    size_t size; // real vector size
    size_t capacity; // used memory
    T *begin; // pointer to the beginning of array
    T *end; // pointer to the last + 1 element of array
public:
    // default constructor
    CustomVec() : size(0), capacity(0), begin(0), end(0) {}
    CustomVec(size_t s);
    CustomVec(size_t s, T elem);
    CustomVec(const CustomVec<T> &other); // copy constructor
    ~CustomVec() { delete [] begin; }
    size_t GetSize() const { return size; }
    size_t GetCapacity() const { return capacity; }
    void push_back(T elem);
    T pop_back();
    void reserve(size_t new_cap);
    CustomVec<T> &operator=(const CustomVec<T> &other);
    T &operator[](size_t index);
    const T &operator[](size_t index) const { return begin[index]; }
private:
    void resize(size_t new_cap);

};

template <class T>
CustomVec<T>::CustomVec(size_t s) : size(s), capacity(s) {
    begin = new T[size];
    end = begin + size;
}

template <class T>
CustomVec<T>::CustomVec(size_t s, T elem) : size(s), capacity(s) {
    begin = new T[size];
    end = begin + size;
    for (T* p = begin; p != end; p++) {
        *p = elem;
    }
}

template <class T>
CustomVec<T>::CustomVec(const CustomVec<T> &other) {
    size = other.size;
    capacity = other.capacity;
    begin = new T[capacity];
    end = begin + size;
    for (size_t i = 0; i < size; i++) {
        begin[i] = other.begin[i];
    }
}

template <class T>
void CustomVec<T>::push_back(T elem) {
    if (size + 1 > capacity) {
        resize(size * 2);
    }
    size++;
    *end = elem;
    end++;
}

template <class T>
T CustomVec<T>::pop_back() {
    //exception
    T out = *(end - 1);
    end--;
    size--;
    return out;
}

template <class T>
void CustomVec<T>::reserve(size_t new_cap) {
    if (new_cap <= capacity) {
        return;
    }
    capacity = new_cap;
}

template <class T>
CustomVec<T>& CustomVec<T>::operator=(const CustomVec<T> &other) {
    delete [] begin;
    size = other.size;
    capacity = other.capacity;
    begin = new T[capacity];
    end = begin + size;
    for (size_t i = 0; i < size; i++) {
        begin[i] = other.begin[i];
    }
    return *this;
}

template <class T>
T& CustomVec<T>::operator[](size_t index) {
    //exception
    return begin[index];
}

template <class T>
void CustomVec<T>::resize(size_t new_cap) {
    capacity = new_cap ? new_cap : 2;
    T* new_array = new T[capacity];
    if (begin) {
        for (int i = 0; i < size; i++) {
            new_array[i] = begin[i];
        }
        delete[] begin;
    }
    begin = new_array;
    end = begin + size;
}

#endif //CUSTOM_VEC_CUSTOMVEC_H