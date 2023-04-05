#pragma once
/*
 * Copyright 2017 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkExecutor_DEFINED
#define SkExecutor_DEFINED

#include <functional>
#include <memory>
#include <skia/core/SkTypes.h>

class SkExecutor {
public:
    SK_API virtual ~SkExecutor();

    // Create a thread pool SkExecutor with a fixed thread count, by default the number of cores.
    SK_API static std::unique_ptr<SkExecutor> MakeFIFOThreadPool(int threads = 0,
                                                          bool allowBorrowing = true);
    SK_API static std::unique_ptr<SkExecutor> MakeLIFOThreadPool(int threads = 0,
                                                          bool allowBorrowing = true);

    // There is always a default SkExecutor available by calling SkExecutor::GetDefault().
    SK_API static SkExecutor& GetDefault();
    SK_API static void SetDefault(SkExecutor*);  // Does not take ownership.  Not thread safe.

    // Add work to execute.
    virtual void add(std::function<void(void)>) = 0;

    // If it makes sense for this executor, use this thread to execute work for a little while.
    virtual void borrow() {}

protected:
    SkExecutor() = default;
    SkExecutor(const SkExecutor&) = delete;
    SkExecutor& operator=(const SkExecutor&) = delete;
};

#endif//SkExecutor_DEFINED
