#include "lib.h"

using namespace rvo;
using namespace std;

// struct LargeObject {
//     LargeObject() { std::cout << "Constructing LargeObject\n"; }

//     LargeObject(const LargeObject&) { std::cout << "Copying LargeObject\n"; }

//     LargeObject(LargeObject&&) { std::cout << "Moving LargeObject\n"; }

//     ~LargeObject() { std::cout << "Destroying LargeObject\n"; }

//     LargeObject& operator=(const LargeObject&) {
//         std::cout << "Copying LargeObject\n";
//         return *this;
//     }

//     LargeObject& operator=(LargeObject&&) {
//         std::cout << "Moving LargeObject\n";
//         return *this;
//     }

//     std::array<uint32_t, 10000> data;
// };

// Function that returns by value
LargeObject return_by_value_no_rvo(const LargeObject& obj) { return obj; }

// Function that returns by value with RVO in C++17
LargeObject return_by_value_rvo() {
    LargeObject obj;
    // Perform some computation with obj
    return obj; // RVO will occur in C++17
}

int main() {
    auto a = return_by_value_rvo();
    auto b = return_by_value_no_rvo(a);
    return 0;
}
