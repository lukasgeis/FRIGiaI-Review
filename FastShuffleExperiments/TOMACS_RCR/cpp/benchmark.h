#include <chrono>
#include <stdint.h>
#include <assert.h>
typedef std::chrono::high_resolution_clock Clock;

#define AVG_TIME_NS(test, pre, repeat, size, verbose)                         \
  do {                                                                         \
    if (verbose)                                                               \
      printf("%-60s: ", #test);                                                \
    assert(repeat >= 5);                                     \
    fflush(NULL);                                                              \
    int64_t min_diff = INT64_MAX;                                              \
    int64_t sum_diff = 0;                                              \
    for (int i = 0; i < repeat; i++) {                                         \
      pre;                                                                     \
      __asm volatile("" ::: /* pretend to clobber */ "memory");                \
      auto t0 = Clock::now();                                                  \
      test;                                                                    \
      auto t1 = Clock::now();                                                  \
      auto cycles_diff =                                                       \
          std::chrono::duration_cast<std::chrono::nanoseconds>(t1 - t0)        \
              .count();                                                        \
      sum_diff += cycles_diff;                \
      if (cycles_diff < min_diff)                                              \
        min_diff = cycles_diff;                                                \
    }                                                                          \
    uint64_t S = size;                                                         \
    if (verbose)                                                               \
      printf(" %d ns total, ", (int)min_diff);                                 \
    float cycle_per_op = (min_diff) / (double)S;                               \
    float avg_cycle_per_op = (sum_diff) / ((double)S * repeat);                \
    if (verbose)                                                               \
      printf(" %.2f ns per input key ", cycle_per_op);                         \
    if (verbose)                                                               \
      printf("\n");                                                            \
    bool err = abs(avg_cycle_per_op - cycle_per_op) > 0.01 * avg_cycle_per_op; \
    double percent = abs(avg_cycle_per_op - cycle_per_op) / avg_cycle_per_op * 100.0; \
    if(err) {                                                                  \
      fprintf( stderr, "warning: average %f vs min %f (%f percent) for arrays of size %zu \n", avg_cycle_per_op, cycle_per_op, percent, size); \
    }                                                                          \
    if (!verbose)                                                              \
      printf("  %.2f ", avg_cycle_per_op);                                     \
    fflush(NULL);                                                              \
  } while (0)
