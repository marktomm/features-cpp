#ifndef MACRO_common_LIB_H
#define MACRO_common_LIB_H

#include <cstdint>
#include <vector>

namespace common {

using vb = std::vector<bool>;
using vu32 = std::vector<uint32_t>;

// GEN_PROTO_BEGIN
int getRandom12();
int getRandom13();
std::size_t GetNextGlobalIndex();
vb GetGlobalRandBoolVec();
void emptyFn();
void emptyFnInt();
vu32 GetGlobalRandIntVec();
// GEN_PROTO_END

template<class T>
void rreorder(std::vector<T>& v, vu32 const& order) {
    for (uint32_t s = 1, d; s < order.size(); ++s) {
        for (d = order[s]; d < s; d = order[d])
            ;
        if (d == s)
            while (d = order[d], d != s)
                swap(v[s], v[d]);
    }
}

}; // namespace common

#endif
