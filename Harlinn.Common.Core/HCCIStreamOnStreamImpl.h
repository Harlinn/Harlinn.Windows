#pragma once
#ifndef HARLINN_COMMON_CORE_HCCISTREAMONSTREAMIMPL_H_
#define HARLINN_COMMON_CORE_HCCISTREAMONSTREAMIMPL_H_
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

#include "HCCComImpl.h"
#include "HCCIO.h"

namespace Harlinn::Common::Core::Com
{
    namespace Internal
    {
        template<typename StreamT, typename DerivedT, typename InterfaceT = ISequentialStream>
        class ISequentialStreamOnStreamImpl : public ObjectBase<DerivedT, InterfaceT>
        {
        public:
            using Base = ObjectBase<DerivedT, InterfaceT>;
            using StreamType = StreamT;
            using InterfaceType = InterfaceT;
        protected:
            StreamT stream_;
            CriticalSection criticalSection_;
        public:
            using Base::QueryInterface;
            using Base::AddRef;
            using Base::Release;

            ISequentialStreamOnStreamImpl(StreamType&& stream)
                : stream_(std::move(stream))
            {
            }

            const StreamType& StreamBase()
            {
                return stream_;
            }


            virtual HRESULT STDMETHODCALLTYPE Read(void* buffer, ULONG numberOfBytesToRead, ULONG* numberOfBytesRead) override
            {
                if constexpr (IO::StreamReader<StreamT>)
                {
                    try
                    {
                        if (numberOfBytesToRead)
                        {
                            if (buffer)
                            {
                                std::unique_lock lock(criticalSection_);
                                auto count = stream_.Read(buffer, static_cast<size_t>(numberOfBytesToRead));
                                if (numberOfBytesRead)
                                {
                                    *numberOfBytesRead = static_cast<ULONG>(count);
                                }
                                if (static_cast<size_t>(count) == static_cast<size_t>(numberOfBytesToRead))
                                {
                                    return S_OK;
                                }
                                return S_FALSE;
                            }
                            return STG_E_INVALIDPOINTER;
                        }
                        return S_OK;
                    }
                    HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT();
                }
                else
                {
                    return E_NOTIMPL;
                }
            }

            virtual HRESULT STDMETHODCALLTYPE Write(const void* buffer, ULONG numberOfBytesToWrite, ULONG* numberOfBytesWritten) override
            {
                if constexpr (IO::StreamWriter<StreamT>)
                {
                    try
                    {
                        if (numberOfBytesToWrite)
                        {
                            if (buffer)
                            {
                                std::unique_lock lock(criticalSection_);
                                auto count = stream_.Write(buffer, static_cast<size_t>(numberOfBytesToWrite));
                                if (numberOfBytesWritten)
                                {
                                    *numberOfBytesWritten = static_cast<ULONG>(count);
                                }
                                if (static_cast<size_t>(count) == static_cast<size_t>(numberOfBytesToWrite))
                                {
                                    return S_OK;
                                }
                                return S_FALSE;
                            }
                            return STG_E_INVALIDPOINTER;
                        }
                        return S_OK;
                    }
                    HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT();
                }
                else
                {
                    return E_NOTIMPL;
                }
            }
        };
    }

    namespace Internal
    {
        template<typename StreamT, typename DerivedT, typename InterfaceT = IStream>
        class IStreamOnStreamImpl : public ISequentialStreamOnStreamImpl<StreamT, DerivedT, InterfaceT>
        {
        public:
            using Base = ISequentialStreamOnStreamImpl<StreamT, DerivedT, InterfaceT>;
            using StreamType = Base::StreamType;
            using InterfaceType = Base::InterfaceType;
        private:
            WideString name_;
        public:
            IStreamOnStreamImpl(StreamType&& stream, const WideString& name = WideString())
                : Base(std::move(stream)), name_(name)
            {
            }
            virtual HRESULT STDMETHODCALLTYPE Seek(
                LARGE_INTEGER distanceToMove,
                DWORD seekOrigin,
                _Out_opt_  ULARGE_INTEGER* newPosition) override
            {
                if constexpr (IO::StreamSeek<StreamT>)
                {
                    try
                    {
                        
                        if (distanceToMove.QuadPart)
                        {
                            auto tmpSeekOrigin = static_cast<IO::SeekOrigin>(seekOrigin);
                            std::unique_lock lock(Base::criticalSection_);
                            auto newPos = Base::stream_.Seek(distanceToMove.QuadPart, tmpSeekOrigin);
                            if (newPosition)
                            {
                                (*newPosition).QuadPart = newPos;
                            }
                        }
                        return S_OK;
                    }
                    HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT();
                }
                else
                {
                    return E_NOTIMPL;
                }
            }

            virtual HRESULT STDMETHODCALLTYPE SetSize(
                ULARGE_INTEGER newSize) override
            {
                if constexpr (IO::StreamSize<StreamT>)
                {
                    try
                    {
                        std::unique_lock lock(Base::criticalSection_);
                        Base::stream_.SetSize(static_cast<Int64>(newSize.QuadPart));
                        return S_OK;
                    }
                    HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT();
                }
                else
                {
                    return E_NOTIMPL;
                }
            }

            virtual HRESULT STDMETHODCALLTYPE CopyTo(
                IStream* destinationStream,
                ULARGE_INTEGER numberOfBytesToCopy,
                _Out_opt_  ULARGE_INTEGER* numberOfBytesRead,
                _Out_opt_  ULARGE_INTEGER* numberOfBytesWritten) override
            {
                if constexpr (IO::StreamReader<StreamT>)
                {
                    try
                    {
                        if (destinationStream)
                        {
                            size_t numBytesRead = 0;
                            size_t numBytesWritten = 0;
                            size_t numBytesToCopy = numberOfBytesToCopy.QuadPart;
                            constexpr size_t bufferSize = 32 * 1024;
                            Byte buffer[bufferSize];
                            size_t fullBufferCount = numBytesToCopy / bufferSize;
                            size_t remainingBytesToCopy = numBytesToCopy % bufferSize;

                            std::unique_lock lock(Base::criticalSection_);
                            for (size_t i = 0; i < fullBufferCount; i++)
                            {
                                auto nr = Base::stream_.Read((void*)buffer, bufferSize);
                                numBytesRead += nr;
                                ULONG written = 0;
                                auto hr = destinationStream->Write(buffer, static_cast<ULONG>(bufferSize), &written);
                                HCC_COM_CHECK_HRESULT(hr);
                                numBytesWritten += written;
                            }
                            if (remainingBytesToCopy)
                            {
                                auto nr = Base::stream_.Read(buffer, remainingBytesToCopy);
                                numBytesRead += nr;
                                ULONG written = 0;
                                auto hr = destinationStream->Write(buffer, static_cast<ULONG>(remainingBytesToCopy), &written);
                                HCC_COM_CHECK_HRESULT(hr);
                                numBytesWritten += written;
                            }

                            if (numberOfBytesRead)
                            {
                                (*numberOfBytesRead).QuadPart = numBytesRead;
                            }
                            if (numberOfBytesWritten)
                            {
                                (*numberOfBytesWritten).QuadPart = numBytesWritten;
                            }
                            return S_OK;
                        }
                        return STG_E_INVALIDPOINTER;
                    }
                    HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT();
                }
                else
                {
                    return E_NOTIMPL;
                }
            }

            virtual HRESULT STDMETHODCALLTYPE Commit( DWORD grfCommitFlags) override
            {
                return E_NOTIMPL;
            }

            virtual HRESULT STDMETHODCALLTYPE Revert() override
            {
                return E_NOTIMPL;
            }

            virtual HRESULT STDMETHODCALLTYPE LockRegion(
                ULARGE_INTEGER libOffset,
                ULARGE_INTEGER cb,
                DWORD dwLockType) override
            {
                return E_NOTIMPL;
            }

            virtual HRESULT STDMETHODCALLTYPE UnlockRegion(
                ULARGE_INTEGER libOffset,
                ULARGE_INTEGER cb,
                DWORD dwLockType) override
            {
                return E_NOTIMPL;
            }

            virtual HRESULT STDMETHODCALLTYPE Stat(
                __RPC__out STATSTG* statstg,
                DWORD statFlag) override
            {
                try
                {
                    if(statstg)
                    { 
                        memset(statstg, 0, sizeof(STATSTG));
                        statstg->type = STGTY_STREAM;
                        std::unique_lock lock(Base::criticalSection_);
                        if constexpr (IO::StreamSize<StreamT>)
                        {
                            statstg->cbSize.QuadPart = static_cast<UInt64>( Base::stream_.Size() );
                        }

                        if ((statFlag & STATFLAG_NONAME) == 0)
                        {
                            size_t nameSize = name_.size();
                            auto ptr = reinterpret_cast<wchar_t*>(CoTaskMemAlloc((nameSize +1)*sizeof(wchar_t)));
                            if (!ptr)
                            {
                                return E_OUTOFMEMORY;
                            }
                            wmemcpy(ptr, name_.c_str(), nameSize);
                            ptr[nameSize] = L'\x0';
                            statstg->pwcsName = ptr;
                        }
                        return S_OK;
                    }
                    else
                    {
                        return E_POINTER;
                    }
                }
                HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT();
            }

            virtual HRESULT STDMETHODCALLTYPE Clone(
                __RPC__deref_out_opt IStream** ppstm) override
            {
                if constexpr (IO::StreamClone<StreamT>)
                {
                    try
                    {
                        if (ppstm)
                        {
                            std::unique_lock lock(Base::criticalSection_);
                            auto clone = Base::stream_.Clone();
                            auto ptr = new IStreamOnStreamImpl(std::move(clone), name_);
                            *ppstm = static_cast<InterfaceType*>(ptr);
                        }
                        else
                        {
                            return E_POINTER;
                        }
                    }
                    HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT();
                }
                else
                {
                    return E_NOTIMPL;
                }
            }
        };
    }

    template<typename StreamT, typename InterfaceT = IStream>
    class IStreamOnStreamImpl : public Internal::IStreamOnStreamImpl<StreamT, IStreamOnStreamImpl<StreamT, InterfaceT>, InterfaceT>
    {
    public:
        using Base = Internal::IStreamOnStreamImpl<StreamT, IStreamOnStreamImpl<StreamT, InterfaceT>, InterfaceT>;
        using StreamType = Base::StreamType;
        IStreamOnStreamImpl(StreamType&& stream)
            : Base(std::move(stream))
        {
        }
    };

}

#endif
