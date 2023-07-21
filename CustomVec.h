#ifndef CUSTOMVEC_H_SENTRY
#define CUSTOMVEC_H_SENTRY

#include <cstddef>
#include <exception>

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
    bool empty() const { return !begin; }
    void push_back(T elem);
    T pop_back();
    void reserve(size_t new_cap);
    CustomVec<T> &operator=(const CustomVec<T> &other);
    T &operator[](size_t index);
    const T &operator[](size_t index) const { return begin[index]; }
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
    if (empty()) {
        std::cerr << "Array is empty\n";
        return T(); //not the best solution, but still acceptable
    }
    T out = *(end - 1);
    end--;
    size--;
    return out;
}

template <class T>
void CustomVec<T>::reserve(size_t new_cap) {
    if (new_cap == capacity)
        return;
    resize(new_cap);
}

template <class T>
CustomVec<T>& CustomVec<T>::operator=(const CustomVec<T> &other) {
    if (this == &other) {
        return *this;
    }
    delete [] begin; // deleting nullptr has no effect
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
    try {
        if (index > size - 1) {
            throw std::out_of_range("index is out of range");
        }
        return begin[index];
    }
    catch (const std::exception &ex) {
        std::cerr << ex.what() << std::endl;
    }
    return *(end - 1);
}

template <class T>
void CustomVec<T>::resize(size_t new_cap) {
    capacity = new_cap ? new_cap : 2; // if new_cap == 0 then reserve 2
    T* new_array = new T[capacity];
    //we should remember that new_cap might be < current_cap
    //so in the copy loop is additional border checker
    if (begin) {
        // copy loop
        for (int i = 0; i < size && i < capacity; i++) {
            new_array[i] = begin[i];
        }
        delete[] begin;
    }
    size = size > capacity ? capacity : size; // cut off excess if necessary
    begin = new_array;
    end = begin + size;
}

#endif //CUSTOMVEC_H_SENTRY
