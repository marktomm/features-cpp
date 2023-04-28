#include "lib.h"
#include <iostream>

int main() {
    using namespace multi_inherit;
    using namespace std;

    CC c;
    A* a = (A*)&c;
    B* b = (B*)a;
    B* b2 = (B*)&c;
    cout << b->b << endl;  // output: 5. NB! B::b is 255
    cout << b2->b << endl; // output: 255

    return 0;
}
