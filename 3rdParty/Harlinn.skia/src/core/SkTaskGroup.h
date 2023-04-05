/*
 * Copyright 2014 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkTaskGroup_DEFINED
#define SkTaskGroup_DEFINED

#include <skia/core/SkExecutor.h>
#include <skia/core/SkTypes.h>
#include <skia/private/SkNoncopyable.h>
#include <atomic>
#include <functional>

class SkTaskGroup : SkNoncopyable {
public:
    // Tasks added to this SkTaskGroup will run on its executor.
    SK_API explicit SkTaskGroup(SkExecutor& executor = SkExecutor::GetDefault());
    ~SkTaskGroup() { this->wait(); }

    // Add a task to this SkTaskGroup.
    SK_API void add(std::function<void(void)> fn);

    // Add a batch of N tasks, all calling fn with different arguments.
    SK_API void batch(int N, std::function<void(int)> fn);

    // Returns true if all Tasks previously add()ed to this SkTaskGroup have run.
    // It is safe to reuse this SkTaskGroup once done().
    SK_API bool done() const;

    // Block until done().
    SK_API void wait();

    // A convenience for testing tools.
    // Creates and owns a thread pool, and passes it to SkExecutor::SetDefault().
    struct Enabler {
        SK_API explicit Enabler(int threads = -1);  // -1 -> num_cores, 0 -> noop
        std::unique_ptr<SkExecutor> fThreadPool;
    };

private:
    std::atomic<int32_t> fPending;
    SkExecutor&          fExecutor;
};

#endif//SkTaskGroup_DEFINED
