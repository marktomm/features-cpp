#include "lib.h"

#include <memory>
#include <utility>

int main() {
    using namespace trivial_type;

    int* pp = new int{0x64};
    fn(pp);

    std::unique_ptr<int> up = std::make_unique<int>(int{0x65});
    fn(std::move(up));

    return 0;
}
