#include "lib.h"

#include <benchmark/benchmark.h>

#include <chrono>
#include <iostream>
#include <vector>

using namespace basics;
using namespace std;

extern "C" {
void asmfna() { asm("movl $324, %eax"); }

void asmfnt() {
    ostream& out = cout;
    vector<TimeDur> vtd;
    clock_t c = clock();
    if (clock_t(-1) == c) {
        cerr << "clock fail" << endl;
        exit(1);
    }

    for (int i = 0; i < 10; ++i) {
        c = clock();
        asm("movl $324, %eax");
        vtd.push_back(TimeDur{"movl 1 to eax", clock() - c});
    }

    for (auto& it : vtd) {
        out << it.GetDesc() << ": " << it.GetDur() << endl;
    }
}

void xeqfna() { [[maybe_unused]] uint32_t x = 234; }

void xeqfne() {
    [[maybe_unused]] uint32_t x = 234;
    doNotOptimize(&x);
}

void xeqfnb() {
    [[maybe_unused]] uint32_t x = 234;
    benchmark::DoNotOptimize(&x);
}

void xeqfnt() {
    ostream& out = cout;
    vector<TimeDur> vtd;
    clock_t c = clock();
    if (clock_t(-1) == c) {
        cerr << "clock fail" << endl;
        exit(1);
    }

    for (int i = 0; i < 10; ++i) {
        c = clock();
        [[maybe_unused]] uint32_t x = 234;
        doNotOptimize(&x);
        vtd.push_back(
            TimeDur{"muint32_t x = 234;doNotOptimize(&x);", clock() - c});
    }

    for (auto& it : vtd) {
        out << it.GetDesc() << ": " << it.GetDur() << endl;
    }
}
}

int main() {
    asmfna();
    asmfnt();
    xeqfna();
    xeqfnb();
    xeqfne();
    xeqfnt();

    {
        const int num_iterations = 1000000000;
        auto start = chrono::high_resolution_clock::now();

        asm volatile(".intel_syntax noprefix;"
                     "mov ecx, %[num_iterations];"
                     "1:;"
                     "sub ecx, 1;"
                     "jnz 1b;"
                     ".att_syntax prefix"
                     : /* no output */
                     : [num_iterations] "r"(num_iterations)
                     : "ecx");

        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> diff = end - start;
        cout << "Time per empty loop: " << diff.count() / num_iterations
             << " s\n";
    }

    {
        const int num_iterations = 1000000000;
        auto start = chrono::high_resolution_clock::now();

        asm volatile(".intel_syntax noprefix;"
                     "mov ecx, %[num_iterations];"
                     "1:;"
                     "mov eax, 342;"
                     "sub ecx, 1;"
                     "jnz 1b;"
                     ".att_syntax prefix"
                     : /* no output */
                     : [num_iterations] "r"(num_iterations)
                     : "ecx", "eax");

        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> diff = end - start;
        cout << "Time per movl: " << diff.count() / num_iterations << " s\n";
    }

    [[maybe_unused]] A4 a;
    benchmark::DoNotOptimize(a);

    return 0;
}
