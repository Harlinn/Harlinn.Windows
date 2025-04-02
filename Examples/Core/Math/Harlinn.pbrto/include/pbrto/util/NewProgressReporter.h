#pragma once
#ifndef PBRTO_UTIL_NEWPROGRESSREPORTER_H_
#define PBRTO_UTIL_NEWPROGRESSREPORTER_H_

/*
   Copyright 2024-2025 Espen Harlinn

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

#include <atomic>
#include <chrono>
#include <cstdint>
#include <string>
#include <thread>

#ifdef PBRT_BUILD_GPU_RENDERER
#include <cuda_runtime.h>
#include <vector>
#endif

namespace pbrto
{

    // Timer Definition
    class Timer
    {
        using clock = std::chrono::steady_clock;
        clock::time_point start;
    public:
        Timer( ) 
            : start( clock::now( ) )
        { }

        double ElapsedSeconds( ) const
        {
            clock::time_point now = clock::now( );
            int64_t elapseduS = std::chrono::duration_cast< std::chrono::microseconds >( now - start ).count( );
            return elapseduS / 1000000.;
        }

        std::string ToString( ) const;
    };

    // ProgressReporter Definition
    class ProgressReporter
    {
        // ProgressReporter Private Members
        int64_t totalWork;
        std::string title;
        bool quiet;
        Timer timer;
        std::atomic<int64_t> workDone;
        std::atomic<bool> exitThread;
        std::thread updateThread;
        std::optional<float> finishTime;

#ifdef PBRT_BUILD_GPU_RENDERER
        std::vector<cudaEvent_t> gpuEvents;
        std::atomic<size_t> gpuEventsLaunchedOffset;
        int gpuEventsFinishedOffset;
#endif
    public:
        // ProgressReporter Public Methods
        ProgressReporter( ) 
            : quiet( true ) 
        { }

        ProgressReporter( int64_t totalWork, std::string title, bool quiet, bool gpu = false );

        ~ProgressReporter( );

        void Update( int64_t num = 1 );
        void Done( );
        double ElapsedSeconds( ) const;

        std::string ToString( ) const;

    private:
        // ProgressReporter Private Methods
        void printBar( );

        
    };
    // ProgressReporter Inline Method Definitions
    inline double ProgressReporter::ElapsedSeconds( ) const
    {
        return finishTime ? *finishTime : timer.ElapsedSeconds( );
    }

    inline void ProgressReporter::Update( int64_t num )
    {
#ifdef PBRT_BUILD_GPU_RENDERER
        if ( gpuEvents.size( ) > 0 )
        {
            if ( gpuEventsLaunchedOffset + num <= gpuEvents.size( ) )
            {
                while ( num-- > 0 )
                {
                    NCHECK_EQ( cudaEventRecord( gpuEvents[ gpuEventsLaunchedOffset ] ),
                        cudaSuccess );
                    ++gpuEventsLaunchedOffset;
                }
            }
            return;
        }
#endif
        if ( num == 0 || quiet )
            return;
        workDone += num;
    }

}


#endif
