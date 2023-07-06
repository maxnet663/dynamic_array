#include <iostream>
#include <string>
#include "CustomVec.h"

template<class T>
void print_vec_inf(const CustomVec<T> &v) {
    std::cout << "Size: " << v.GetSize() << "; Capacity: "
        << v.GetCapacity() << std::endl;
    for (int i = 0; i < v.GetSize(); i++) {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::cout <<  "Using CustomVec(size_t s, T elem): " << std::endl;
    CustomVec<int> v(5, 3);
    print_vec_inf(v);
    std::cout << std::endl << "Using CustomVec(size_t s): " << std::endl;
    CustomVec<int> vec(10);
    for (int i = 0; i < 10; i++) {
        vec[i] = i + 1;
    }
    print_vec_inf(vec);
    std::cout << std::endl
        << "Let's try to add 11 in the end of vector using push_back(elem)"
        << std::endl;
    vec.push_back(11);
    print_vec_inf(vec);

    std::cout << std::endl<< "CustomVec<string>: " << std::endl;
    CustomVec<std::string> vec2;
    for (int i = 0; i < 4; i++) {
        std::string s(3, char('0' + i));
        vec2.push_back(s);
    }
    print_vec_inf(vec2);
    std::cout << "Let's try to pop last string:" << std::endl;
    std::cout << vec2.pop_back() << std::endl;
    print_vec_inf(vec2);

    std::cout << std::endl << "vec3 = vec" << std::endl << "Vec3: ";
    CustomVec vec3 = vec;
    print_vec_inf(vec3);

    std::cout << std::endl << "Well, let's try to make new vec" << std::endl <<
        "vec4(CustomVec<double>(s, elem) using copy constructor:" << std::endl;
    CustomVec<double> vec4(CustomVec<double>(4, 3.14 / 2.7));
    print_vec_inf(vec4);
    return 0;
}
