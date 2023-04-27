#include "lib.h"

using namespace non_standard_member_vars;

int main() {
    NonStandard ns;
    fn(ns);
    StandardClass sc;
    fn(sc);

    [[maybe_unused]] int nsa = ns.a;
    [[maybe_unused]] int sca = sc.a;
    return 0;
}
