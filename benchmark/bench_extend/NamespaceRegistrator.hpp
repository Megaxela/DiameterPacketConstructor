#pragma once

#include <benchmark/benchmark.h>

// Helpers for generating unique variable names
#define BENCHMARK_PRIVATE_NAME_NS(n) \
  BENCHMARK_PRIVATE_CONCAT(_benchmark_, BENCHMARK_PRIVATE_UNIQUE_ID, cut)

#define BENCHMARK_PRIVATE_DECLARE_NS(n)                                 \
  static ::benchmark::internal::Benchmark* BENCHMARK_PRIVATE_NAME_NS(n) \
      BENCHMARK_UNUSED

#define BENCHMARK_NS(n)                                  \
BENCHMARK_PRIVATE_DECLARE_NS(n) =                           \
      (::benchmark::internal::RegisterBenchmarkInternal( \
          new ::benchmark::internal::FunctionBenchmark(#n, n)))