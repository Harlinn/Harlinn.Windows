#pragma once
#ifndef PBRTO_UTIL_NEWSTATS_H_
#define PBRTO_UTIL_NEWSTATS_H_

/*
   Copyright 2024-2026 Espen Harlinn

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/


// pbrt is Copyright(c) 1998-2020 Matt Pharr, Wenzel Jakob, and Greg Humphreys.
// The pbrt source code is licensed under the Apache License, Version 2.0.
// SPDX: Apache-2.0

#include <pbrto/NewPbrt.h>

#include <cstdio>
#include <limits>
#include <string>

namespace pbrto
{

    class StatsAccumulator;
    class PixelStatsAccumulator;
    // StatRegisterer Definition
    class StatRegisterer
    {
    public:
        // StatRegisterer Public Methods
        using AccumFunc = void ( * )( StatsAccumulator& );
        using PixelAccumFunc = void ( * )( Point2i p, int counterIndex, PixelStatsAccumulator& );

        PBRTO_EXPORT
            StatRegisterer( AccumFunc func, PixelAccumFunc = {} );

        PBRTO_EXPORT
            static void CallCallbacks( StatsAccumulator& accum );

        PBRTO_EXPORT
            static void CallPixelCallbacks( Point2i p, PixelStatsAccumulator& accum );
    };

    PBRTO_EXPORT
        void StatsEnablePixelStats( const Bounds2i& b, const std::string& baseName );
    PBRTO_EXPORT
        void StatsReportPixelStart( Point2i p );
    PBRTO_EXPORT
        void StatsReportPixelEnd( Point2i p );

    void PrintStats( FILE* dest );
    void StatsWritePixelImages( );
    bool PrintCheckRare( FILE* dest );
    void ClearStats( );
    PBRTO_EXPORT
        void ReportThreadStats( );

    // StatsAccumulator Definition
    class StatsAccumulator
    {
    public:
        // StatsAccumulator Public Methods
        PBRTO_EXPORT
            StatsAccumulator( );

        PBRTO_EXPORT
            void ReportCounter( const char* name, int64_t val );
        PBRTO_EXPORT
            void ReportMemoryCounter( const char* name, int64_t val );
        PBRTO_EXPORT
            void ReportPercentage( const char* name, int64_t num, int64_t denom );
        PBRTO_EXPORT
            void ReportRatio( const char* name, int64_t num, int64_t denom );
        PBRTO_EXPORT
            void ReportRareCheck( const char* condition, Float maxFrequency, int64_t numTrue,
                int64_t total );

        PBRTO_EXPORT
            void ReportIntDistribution( const char* name, int64_t sum, int64_t count, int64_t min,
                int64_t max );
        PBRTO_EXPORT
            void ReportFloatDistribution( const char* name, double sum, int64_t count, double min,
                double max );

        PBRTO_EXPORT
            void AccumulatePixelStats( const PixelStatsAccumulator& accum );
        PBRTO_EXPORT
            void WritePixelImages( ) const;

        PBRTO_EXPORT
            void Print( FILE* file );
        PBRTO_EXPORT
            bool PrintCheckRare( FILE* dest );
        PBRTO_EXPORT
            void Clear( );

    private:
        // StatsAccumulator Private Data
        struct Stats;
        Stats* stats = nullptr;
    };

    // PixelStatsAccumulator Definition
    class PixelStatsAccumulator
    {
    public:
        PBRTO_EXPORT
            PixelStatsAccumulator( );

        PBRTO_EXPORT
            void ReportPixelMS( Point2i p, float ms );
        PBRTO_EXPORT
            void ReportCounter( Point2i p, int counterIndex, const char* name, int64_t val );
        PBRTO_EXPORT
            void ReportRatio( Point2i p, int counterIndex, const char* name, int64_t num,
                int64_t denom );

    private:
        friend class StatsAccumulator;
        struct PixelStats;
        PixelStats* stats = nullptr;
    };

    // Statistics Macros
#define NSTAT_COUNTER(title, var)                                       \
    static thread_local int64_t var;                                   \
    static StatRegisterer STATS_REG##var([](StatsAccumulator &accum) { \
        accum.ReportCounter(title, var);                               \
        var = 0;                                                       \
    });

#define NSTAT_PIXEL_COUNTER(title, var)                                        \
    static thread_local int64_t var, var##Sum;                                \
    static StatRegisterer STATS_REG##var(                                     \
        [](StatsAccumulator &accum) {                                         \
            /* report sum, since if disabled, it all just goes into var... */ \
            accum.ReportCounter(title, var + var##Sum);                       \
            var##Sum = 0;                                                     \
            var = 0;                                                          \
        },                                                                    \
        [](Point2i p, int counterIndex, PixelStatsAccumulator &accum) {       \
            accum.ReportCounter(p, counterIndex, title, var);                 \
            var##Sum += var;                                                  \
            var = 0;                                                          \
        });

#define NSTAT_MEMORY_COUNTER(title, var)                                \
    static thread_local int64_t var;                                   \
    static StatRegisterer STATS_REG##var([](StatsAccumulator &accum) { \
        accum.ReportMemoryCounter(title, var);                         \
        var = 0;                                                       \
    });

    struct StatIntDistribution
    {
        int64_t sum = 0, count = 0;
        int64_t min = std::numeric_limits<int64_t>::max( );
        int64_t max = std::numeric_limits<int64_t>::lowest( );
        void operator<<( int64_t value )
        {
            sum += value;
            count += 1;
            min = ( value < min ) ? value : min;
            max = ( value > max ) ? value : max;
        }
    };

#define NSTAT_INT_DISTRIBUTION(title, var)                                         \
    static thread_local StatIntDistribution var;                                  \
    static StatRegisterer STATS_REG##var([](StatsAccumulator &accum) {            \
        accum.ReportIntDistribution(title, var.sum, var.count, var.min, var.max); \
        var.sum = 0;                                                              \
        var.count = 0;                                                            \
        var.min = int64_t(std::numeric_limits<int64_t>::max());                   \
        var.max = int64_t(std::numeric_limits<int64_t>::lowest());                \
    });

#define NSTAT_FLOAT_DISTRIBUTION(title, var)                                             \
    static thread_local StatCounter<double> var##sum;                                   \
    static thread_local int64_t var##count;                                             \
    static thread_local StatCounter<double> var##min(                                   \
        std::numeric_limits<double>::max());                                            \
    static thread_local StatCounter<double> var##max(                                   \
        std::numeric_limits<double>::lowest());                                         \
    static StatRegisterer STATS_REG##var([](StatsAccumulator &accum) {                  \
        accum.ReportFloatDistribution(title, var##sum, var##count, var##min, var##max); \
        var##sum = 0;                                                                   \
        var##count = 0;                                                                 \
        var##min = StatCounter<double>(std::numeric_limits<double>::max());             \
        var##max = StatCounter<double>(std::numeric_limits<double>::lowest());          \
    });

#define NSTAT_PERCENT(title, numVar, denomVar)                             \
    static thread_local int64_t numVar, denomVar;                         \
    static StatRegisterer STATS_REG##numVar([](StatsAccumulator &accum) { \
        accum.ReportPercentage(title, numVar, denomVar);                  \
        numVar = 0;                                                       \
        denomVar = 0;                                                     \
    });

#define NSTAT_RATIO(title, numVar, denomVar)                               \
    static thread_local int64_t numVar, denomVar;                         \
    static StatRegisterer STATS_REG##numVar([](StatsAccumulator &accum) { \
        accum.ReportRatio(title, numVar, denomVar);                       \
        numVar = 0;                                                       \
        denomVar = 0;                                                     \
    });

#define NSTAT_PIXEL_RATIO(title, numVar, denomVar)                                     \
    static thread_local int64_t numVar, numVar##Sum, denomVar, denomVar##Sum;         \
    static StatRegisterer STATS_REG##numVar##denomVar(                                \
        [](StatsAccumulator &accum) {                                                 \
            /* report sum, since if disabled, it all just goes into var... */         \
            accum.ReportRatio(title, numVar + numVar##Sum, denomVar + denomVar##Sum); \
            numVar = 0;                                                               \
            numVar##Sum = 0;                                                          \
            denomVar = 0;                                                             \
            denomVar##Sum = 0;                                                        \
        },                                                                            \
        [](Point2i p, int counterIndex, PixelStatsAccumulator &accum) {               \
            accum.ReportRatio(p, counterIndex, title, numVar, denomVar);              \
            numVar##Sum += numVar;                                                    \
            denomVar##Sum += denomVar;                                                \
            numVar = 0;                                                               \
            denomVar = 0;                                                             \
        });

}

#endif
