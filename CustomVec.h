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

    void sort(T* arr, int left, int right);
public:

    // default constructor
    CustomVec() : size(0), capacity(0), begin(0), end(0) {}

    CustomVec(size_t s);

    CustomVec(size_t s, T elem);

    CustomVec(const CustomVec<T> &other); // copy constructor

    CustomVec(CustomVec&& source) noexcept;

    ~CustomVec() { delete [] begin; }

    inline size_t GetSize() const { return size; }

    inline size_t GetCapacity() const { return capacity; }

    bool empty() const { return !begin; }

    void push_back(T elem);

    T pop_back();

    void reserve(size_t new_cap);

    void sort();

    CustomVec<T>& operator=(const CustomVec<T> &other);

    CustomVec<T>& operator=(CustomVec&& source) noexcept;

    T& operator[](size_t index);

    const T& operator[](size_t index) const;

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
    for (T* p = begin; p != end; ++p) {
        *p = elem;
    }
}

template <class T>
CustomVec<T>::CustomVec(CustomVec&& source) noexcept
    : size(std::move(source.size))
    , capacity(std::move(source.capacity)) {
        begin = source.begin;
        source.begin = nullptr;
        end = source.end;
        source.end = nullptr;
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
void CustomVec<T>::resize(size_t new_cap) {
    capacity = new_cap ? new_cap : 2; // if new_cap == 0 then reserve 2
    T* new_array = new T[capacity];

    //we should remember that new_cap might be < current_cap
    //so in the copy loop is additional border checker
    if (begin) {
        // copy loop
        for (size_t i = 0; i < size && i < capacity; i++) {
            new_array[i] = begin[i];
        }
        delete[] begin;
    }
    size = size > capacity ? capacity : size; // cut off excess if necessary
    begin = new_array;
    end = begin + size;
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
void CustomVec<T>::sort() {
    sort(begin, 0, size - 1);
}

template <class T>
void CustomVec<T>::sort(T* arr, int left, int right) {
    int l = left;
    int r = right;
    T pivot = arr[ (left + right) / 2];

    do {
        while (arr[l] < pivot) {
            l++;
        }
        while (arr[r] > pivot) {
            r--;
        }
        if (l <= r) {
            T tmp = arr[l];
            arr[l] = arr[r];
            arr[r] = tmp;
            l++;
            r--;
        }
    } while( l <= r);

    if (left < r)
        sort(arr, left, r);
    if (l < right)
        sort(arr, l, right);
}

template <class T>
CustomVec<T>& CustomVec<T>::operator=(const CustomVec<T> &other) {
    if (this == &other) {
        return *this;
    }
    if (begin) {
        delete[] begin;
    }
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
CustomVec<T>& CustomVec<T>::operator=(CustomVec&& source) noexcept {
    if (begin) {
        delete[] begin;
    }
    size = std::move(source.size);
    capacity = std::move(source.capacity);
    begin = source.begin;
    source.begin = nullptr;
    end = source.end;
    source.end = nullptr;
}

template <class T>
T& CustomVec<T>::operator[](size_t index) {
    try {
        if (index >= size) {
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
const T& CustomVec<T>::operator[](size_t index) const {
    try {
        if (index >= size) {
            throw std::out_of_range("index is out of range");
        }
        return begin[index];
    }
    catch (const std::exception &ex) {
        std::cerr << ex.what() << std::endl;
    }
    return *(end - 1);
}


#endif //CUSTOMVEC_H_SENTRY
