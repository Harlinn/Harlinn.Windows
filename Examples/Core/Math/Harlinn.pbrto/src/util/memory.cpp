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
#include "pch.h"
// pbrt is Copyright(c) 1998-2020 Matt Pharr, Wenzel Jakob, and Greg Humphreys.
// The pbrt source code is licensed under the Apache License, Version 2.0.
// SPDX: Apache-2.0

#include <pbrto/util/memory.h>

#include <pbrto/util/check.h>
#include <pbrto/util/print.h>

#include <cstdlib>
#ifdef PBRT_HAVE_MALLOC_H
#include <malloc.h>  // for both memalign and _aligned_malloc
#endif
#ifdef PBRT_IS_WINDOWS
// clang-format off
#include <windows.h>
#include <psapi.h>
#pragma comment(lib, "psapi.lib")
// clang-format on
#endif  // PBRT_IS_WINDOWS
#ifdef PBRT_IS_LINUX
#include <unistd.h>
#include <cstdio>
#endif  // PBRT_IS_LINUX
#ifdef PBRT_IS_OSX
#include <mach/mach.h>
#endif  // PBRT_IS_OSX

namespace pbrt {

/*
 * Author:  David Robert Nadeau
 * Site:    http://NadeauSoftware.com/
 * License: Creative Commons Attribution 3.0 Unported License
 *          http://creativecommons.org/licenses/by/3.0/deed.en_US
 *
 * Returns the current resident set size (physical memory use) measured
 * in bytes, or zero if the value cannot be determined on this OS.
 */
PBRTO_EXPORT
size_t GetCurrentRSS() {
#ifdef PBRT_IS_WINDOWS
    PROCESS_MEMORY_COUNTERS info;
    GetProcessMemoryInfo(GetCurrentProcess(), &info, sizeof(info));
    return (size_t)info.WorkingSetSize;
#elif defined(PBRT_IS_OSX)
    struct mach_task_basic_info info;
    mach_msg_type_number_t infoCount = MACH_TASK_BASIC_INFO_COUNT;
    if (task_info(mach_task_self(), MACH_TASK_BASIC_INFO, (task_info_t)&info,
                  &infoCount) != KERN_SUCCESS)
        return (size_t)0L; /* Can't access? */
    return (size_t)info.resident_size;

#elif defined(PBRT_IS_LINUX)
    FILE *fp;
    if ((fp = fopen("/proc/self/statm", "r")) == nullptr) {
        LOG_ERROR("Unable to open /proc/self/statm");
        return 0;
    }

    long rss = 0L;
    if (fscanf(fp, "%*s%ld", &rss) != 1) {
        LOG_ERROR("Unable to read /proc/self/statm");
        fclose(fp);
        return 0;
    }
    fclose(fp);
    return (size_t)rss * (size_t)sysconf(_SC_PAGESIZE);
#else
#error "TODO: implement GetCurrentRSS() for this target"
    return 0;
    /*    struct rusage rusage;
    CHECK(getrusage(RUSAGE_SELF, &rusage) == 0);
    return rusage.ru_idrss;
    */
#endif
}

}  // namespace pbrt
