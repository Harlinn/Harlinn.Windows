#pragma once
#ifndef HARLINN_COMMON_CORE_HCCRTWORKQ_H_
#define HARLINN_COMMON_CORE_HCCRTWORKQ_H_
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

#include "HCCCom.h"

namespace Harlinn::Common::Core
{
    class RtwqAsyncResult : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(RtwqAsyncResult, Unknown, IRtwqAsyncResult, IUnknown)
    public:
        void GetState(_Out_ IUnknown** ppunkState) const
        {
            auto pInterface = GetInterface();
            auto hr = pInterface->GetState(ppunkState);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        void GetStatus() const
        {
            auto pInterface = GetInterface();
            auto hr = pInterface->GetStatus();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        void SetStatus(HRESULT hrStatus) const
        {
            auto pInterface = GetInterface();
            auto hr = pInterface->SetStatus(hrStatus);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        void GetObject(_Out_ IUnknown** ppObject) const
        {
            auto pInterface = GetInterface();
            auto hr = pInterface->GetObject(ppObject);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        IUnknown* GetStateNoAddRef() const
        {
            auto pInterface = GetInterface();
            auto result = pInterface->GetStateNoAddRef();
            return result;
        }
    };

    class RtwqAsyncCallback : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(RtwqAsyncCallback, Unknown, IRtwqAsyncCallback, IUnknown)
    public:
        void GetParameters(_Out_ DWORD* pdwFlags, _Out_ DWORD* pdwQueue) const
        {
            auto pInterface = GetInterface();
            auto hr = pInterface->GetParameters(pdwFlags, pdwQueue);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        void Invoke(_In_ IRtwqAsyncResult* pAsyncResult) const
        {
            auto pInterface = GetInterface();
            auto hr = pInterface->Invoke(pAsyncResult);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class RtwqPlatformEvents : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(RtwqPlatformEvents, Unknown, IRtwqPlatformEvents, IUnknown)
    public:
        void InitializationComplete() const
        {
            auto pInterface = GetInterface();
            auto hr = pInterface->InitializationComplete();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        void ShutdownStart() const
        {
            auto pInterface = GetInterface();
            auto hr = pInterface->ShutdownStart();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        void ShutdownComplete() const
        {
            auto pInterface = GetInterface();
            auto hr = pInterface->ShutdownComplete();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    namespace RtWorkQ
    {
        class Platform
        {
        public:
            Platform()
            {
                auto hr = RtwqStartup();
                HCC_COM_CHECK_HRESULT(hr);
            }
            ~Platform()
            {
                auto hr = RtwqShutdown();
                HCC_COM_CHECK_HRESULT(hr);
            }

        };

        enum class WorkQueueType
        {
            // Create a work queue without a message loop.
            Standard = RTWQ_STANDARD_WORKQUEUE,
            // Create a work queue with a message loop that calls PeekMessage() / DispatchMessage()..
            Window = RTWQ_WINDOW_WORKQUEUE,
            // Create a multithreaded work queue. This type of work queue uses a 
            // thread pool to dispatch work items. The caller is responsible for 
            // serializing the work items.
            MultiThreaded = RTWQ_MULTITHREADED_WORKQUEUE,
        };


        class WorkQueue
        {
        private:
            DWORD id_ = 0;
        public:
            WorkQueue()
            { }

            explicit WorkQueue(WorkQueueType type)
            {
                DWORD id;
                auto hr = RtwqAllocateWorkQueue(static_cast<RTWQ_WORKQUEUE_TYPE>(type),&id);
                HCC_COM_CHECK_HRESULT(hr);
                id_ = id;
            }

            WorkQueue(const WorkQueue& other) = delete;
            WorkQueue& operator = (const WorkQueue& other) = delete;

            WorkQueue(WorkQueue&& other) noexcept
                : id_(other.id_)
            { 
                other.id_ = 0;
            }
            WorkQueue& operator = (WorkQueue&& other) noexcept
            {
                std::swap(id_, other.id_);
            }

            void Lock() const
            {
                auto hr = RtwqLockWorkQueue(id_);
                HCC_COM_CHECK_HRESULT(hr);
            }
            void Unlock() const
            {
                auto hr = RtwqUnlockWorkQueue(id_);
                HCC_COM_CHECK_HRESULT(hr);
            }


            static WorkQueue LockShared()
            {

            }


        };

    }


}

#endif
