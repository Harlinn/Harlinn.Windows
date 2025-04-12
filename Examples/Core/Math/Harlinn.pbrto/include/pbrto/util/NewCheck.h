#pragma once
#ifndef PBRTO_UTIL_NEWCHECK_H_
#define PBRTO_UTIL_NEWCHECK_H_


#include <pbrto/NewPbrt.h>

#include <pbrto/util/NewLog.h>
#include <pbrto/util/NewStats.h>

#include <functional>
#include <string>
#include <vector>

namespace pbrto
{

    void PrintStackTrace( );

#ifdef PBRT_IS_GPU_CODE

#define NCHECK(x) assert(x)
#define NCHECK_IMPL(a, b, op) assert((a)op(b))

#define NCHECK_EQ(a, b) NCHECK_IMPL(a, b, ==)
#define NCHECK_NE(a, b) NCHECK_IMPL(a, b, !=)
#define NCHECK_GT(a, b) NCHECK_IMPL(a, b, >)
#define NCHECK_GE(a, b) NCHECK_IMPL(a, b, >=)
#define NCHECK_LT(a, b) NCHECK_IMPL(a, b, <)
#define NCHECK_LE(a, b) NCHECK_IMPL(a, b, <=)

#else

    // CHECK Macro Definitions
#define NCHECK(x) (!(!(x) && (NLOG_FATAL("Check failed: %s", #x), true)))

#define NCHECK_EQ(a, b) NCHECK_IMPL(a, b, ==)
#define NCHECK_NE(a, b) NCHECK_IMPL(a, b, !=)
#define NCHECK_GT(a, b) NCHECK_IMPL(a, b, >)
#define NCHECK_GE(a, b) NCHECK_IMPL(a, b, >=)
#define NCHECK_LT(a, b) NCHECK_IMPL(a, b, <)
#define NCHECK_LE(a, b) NCHECK_IMPL(a, b, <=)

// CHECK\_IMPL Macro Definition
#define NCHECK_IMPL(a, b, op)                                                           \
    do {                                                                               \
        auto va = a;                                                                   \
        auto vb = b;                                                                   \
        if (!(va op vb))                                                               \
            NLOG_FATAL("Check failed: %s " #op " %s with %s = %s, %s = %s", #a, #b, #a, \
                      va, #b, vb);                                                     \
    } while (false) /* swallow semicolon */

#endif  // PBRT_IS_GPU_CODE

#ifdef PBRT_DEBUG_BUILD

#define NDCHECK(x) (NCHECK(x))
#define NDCHECK_EQ(a, b) NCHECK_EQ(a, b)
#define NDCHECK_NE(a, b) NCHECK_NE(a, b)
#define NDCHECK_GT(a, b) NCHECK_GT(a, b)
#define NDCHECK_GE(a, b) NCHECK_GE(a, b)
#define NDCHECK_LT(a, b) NCHECK_LT(a, b)
#define NDCHECK_LE(a, b) NCHECK_LE(a, b)

#else

#define NEMPTY_CHECK \
    do {            \
    } while (false) /* swallow semicolon */

// Use an empty check (rather than expanding the macros to nothing) to swallow the
// semicolon at the end, and avoid empty if-statements.
#define NDCHECK(x) NEMPTY_CHECK

#define NDCHECK_EQ(a, b) NEMPTY_CHECK
#define NDCHECK_NE(a, b) NEMPTY_CHECK
#define NDCHECK_GT(a, b) NEMPTY_CHECK
#define NDCHECK_GE(a, b) NEMPTY_CHECK
#define NDCHECK_LT(a, b) NEMPTY_CHECK
#define NDCHECK_LE(a, b) NEMPTY_CHECK

#endif

#define NCHECK_RARE_TO_STRING(x) #x
#define NCHECK_RARE_EXPAND_AND_TO_STRING(x) NCHECK_RARE_TO_STRING(x)

#ifdef PBRT_IS_GPU_CODE

#define NCHECK_RARE(freq, condition)
#define NDCHECK_RARE(freq, condition)

#else

#define NCHECK_RARE(freq, condition)                                                     \
    static_assert(std::is_floating_point<decltype(freq)>::value,                        \
                  "Expected floating-point frequency as first argument to CHECK_RARE"); \
    static_assert(std::is_integral<decltype(condition)>::value,                         \
                  "Expected Boolean condition as second argument to CHECK_RARE");       \
    do {                                                                                \
        static thread_local int64_t numTrue, total;                                     \
        static StatRegisterer reg([](StatsAccumulator &accum) {                         \
            accum.ReportRareCheck(__FILE__ " " NCHECK_RARE_EXPAND_AND_TO_STRING(         \
                                      __LINE__) ": NCHECK_RARE failed: " #condition,     \
                                  freq, numTrue, total);                                \
            numTrue = total = 0;                                                        \
        });                                                                             \
        ++total;                                                                        \
        if (condition)                                                                  \
            ++numTrue;                                                                  \
    } while (0)

#ifdef PBRT_DEBUG_BUILD
#define NDCHECK_RARE(freq, condition) CHECK_RARE(freq, condition)
#else
#define NDCHECK_RARE(freq, condition)
#endif  // NDEBUG

#endif  // PBRT_IS_GPU_CODE

// CheckCallbackScope Definition
    class CheckCallbackScope
    {
    public:
        // CheckCallbackScope Public Methods
        CheckCallbackScope( std::function<std::string( void )> callback );

        ~CheckCallbackScope( );

        CheckCallbackScope( const CheckCallbackScope& ) = delete;
        CheckCallbackScope& operator=( const CheckCallbackScope& ) = delete;

        static void Fail( );

    private:
        // CheckCallbackScope Private Members
        static std::vector<std::function<std::string( void )>> callbacks;
    };

}

#endif
