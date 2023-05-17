#include "lib.h"

#include <benchmark/benchmark.h>

#include <asm/unistd.h>
#include <linux/perf_event.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include <iostream>

#include <cstdint>
#include <cstring>

using namespace virtual_base_class;
using namespace std;

namespace pperf {

class A {
public:
    std::uintptr_t a{};
};

} // namespace pperf

int main() {
    pperf::A a;

    // Perf event attributes
    struct perf_event_attr pe;
    memset(&pe, 0, sizeof(struct perf_event_attr));
    pe.type = PERF_TYPE_HARDWARE;
    // pe.config = PERF_COUNT_HW_CACHE_MISSES;
    pe.config = PERF_COUNT_HW_CACHE_REFERENCES;
    pe.size = sizeof(struct perf_event_attr);
    pe.disabled = 1;
    pe.exclude_kernel = 1;
    pe.exclude_hv = 1;
    // Configure L1 data cache loads
    pe.config1 = PERF_COUNT_HW_CACHE_L1D | (PERF_COUNT_HW_CACHE_OP_READ << 8) |
                 (PERF_COUNT_HW_CACHE_RESULT_ACCESS << 16);
    // clang-format off
    // Configure L1 data cache load misses
    // pe.config1 = PERF_COUNT_HW_CACHE_L1D | (PERF_COUNT_HW_CACHE_OP_READ << 8) |
    //             (PERF_COUNT_HW_CACHE_RESULT_MISS << 16);
    // clang-format on

    // Open perf event
    long int lfd = syscall(__NR_perf_event_open, &pe, 0, -1, -1, 0);
    if (lfd == -1) {
        cout << "perf_event_open" << endl;
        return 1;
    }
    int fd = static_cast<int>(lfd);

    // Enable perf event
    ioctl(fd, PERF_EVENT_IOC_RESET, 0);
    ioctl(fd, PERF_EVENT_IOC_ENABLE, 0);

    // Code section to profile
    // Access the A local variable
    benchmark::DoNotOptimize(a);

    // Disable perf event and read the result
    ioctl(fd, PERF_EVENT_IOC_DISABLE, 0);
    uint64_t cache_loads;
    read(fd, &cache_loads, sizeof(uint64_t));

    // Print the cache X count
    cout << "L1 Cache Loads: " << cache_loads << endl;

    // Close perf event
    close(fd);

    return 0;
}
