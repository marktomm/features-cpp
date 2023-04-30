#include "lib.h"
#include <benchmark/benchmark.h>
#include <functional>

namespace lambda_fns {
void small_obj() { [[maybe_unused]] SmallObject obj; }
void small_obj_opt() {
    [[maybe_unused]] SmallObject obj;
    benchmark::DoNotOptimize(obj);
}

void small_obj_lambda() {
    SmallObject obj;
    [[maybe_unused]] auto lambda = [obj]() {
        [[maybe_unused]] auto ptr = &obj;
    };
}

std::function<void()> small_obj_lambda_ret() {
    SmallObject obj;
    auto lambda = [obj]() { [[maybe_unused]] auto ptr = &obj; };
    return lambda;
}

void small_obj_lambda_ref(SmallObject& obj) {
    [[maybe_unused]] auto lambda = [obj]() {
        [[maybe_unused]] auto ptr = &obj;
    };
}

void small_obj_lambda_opt_ref(SmallObject& obj) {
    [[maybe_unused]] auto lambda = [obj]() {
        [[maybe_unused]] auto ptr = &obj;
    };
    benchmark::DoNotOptimize(obj);
}

void small_obj_lambda_call() {
    SmallObject obj;
    auto lambda = [obj]() { [[maybe_unused]] auto ptr = &obj; };
    lambda();
}

void small_obj_lambda_call_ref(SmallObject& obj) {
    auto lambda = [obj]() { [[maybe_unused]] auto ptr = &obj; };
    lambda();
}

void small_obj_lambda_opt() {
    SmallObject obj;
    [[maybe_unused]] auto lambda = [obj]() mutable {
        [[maybe_unused]] auto ptr = &obj;
    };
    benchmark::DoNotOptimize(obj);
    benchmark::DoNotOptimize(lambda);
}

void large_obj_lambda_ref(LargeObject& obj) {
    [[maybe_unused]] auto lambda = [obj]() mutable {
        [[maybe_unused]] auto ptr = &obj;
    };
}

void large_obj_lambda_opt_ref(LargeObject& obj) {
    [[maybe_unused]] auto lambda = [obj]() mutable {
        [[maybe_unused]] auto ptr = &obj;
    };
    benchmark::DoNotOptimize(obj);
}

void large_obj_lambda_call_ref(LargeObject& obj) {
    auto lambda = [obj]() mutable { [[maybe_unused]] auto ptr = &obj; };
    lambda();
}

void large_obj_lambda_call() {
    LargeObject obj;
    auto lambda = [obj]() mutable { [[maybe_unused]] auto ptr = &obj; };
    lambda();
}

void large_obj_lambda() {
    LargeObject obj;
    [[maybe_unused]] auto lambda = [obj]() mutable {
        [[maybe_unused]] auto ptr = &obj;
    };
}

std::function<void()> large_obj_lambda_ret() {
    LargeObject obj;
    auto lambda = [obj]() mutable { [[maybe_unused]] auto ptr = &obj; };
    return lambda;
}

void large_obj_lambda_opt() {
    LargeObject obj;
    [[maybe_unused]] auto lambda = [obj]() mutable {
        [[maybe_unused]] auto ptr = &obj;
    };
    benchmark::DoNotOptimize(obj);
    benchmark::DoNotOptimize(lambda);
}

void large_obj() { [[maybe_unused]] LargeObject obj; }

void large_obj_opt() {
    LargeObject obj;
    benchmark::DoNotOptimize(obj);
}

std::function<void()> create_lambda_min() {
    [[maybe_unused]] LargeObject lo;
    auto lambda = [lo]() { [[maybe_unused]] auto dummy = lo; };
    return lambda;
}

} // namespace lambda_fns
