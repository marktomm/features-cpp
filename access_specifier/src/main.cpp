#include "lib.h"
#include <iostream>

int main() {
    using namespace access_specifier;
    using namespace std;
    A a;
    cout << a.a;
    A2 a2;
    cout << a2.a;

    [[maybe_unused]] A aa = a;
    [[maybe_unused]] A2 aa2 = a2;

    return 0;
}