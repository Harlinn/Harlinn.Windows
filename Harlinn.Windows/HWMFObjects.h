#pragma once
#ifndef HARLINN_WINDOWS_HWMFOBJECTS_H_
#define HARLINN_WINDOWS_HWMFOBJECTS_H_

#include "HWMediaObj.h"
#include <HCCVariant.h>
#include <HCCPropSys.h>
#include "HWMFObjectsTypes.h"

namespace Harlinn::Windows
{
#pragma comment(lib,"mfuuid.lib")
#pragma comment(lib,"Mfplat.lib")

    class MFAttributes;
    class MFMediaBuffer;
    class MFSample;
    class MF2DBuffer;
    class MF2DBuffer2;
    class MFDXGIBuffer;
    class MFMediaType;
    class MFAudioMediaType;
    class MFVideoMediaType;
    class MFAsyncCallback;
    class MFAsyncResult;
    class MFAsyncCallbackLogging;
    class MFMediaEvent;
    class MFMediaEventGenerator;
    class MFRemoteAsyncCallback;
    class MFByteStream;
    class MFByteStreamProxyClassFactory;
    class MFSampleOutputStream;
    class MFCollection;
    template<typename T>
    class MFCollectionT;
    class MFMediaEventQueue;
    class MFActivate;
    class MFPluginControl;
    class MFPluginControl2;
    class MFDXGIDeviceManager;
    class MFMuxStreamAttributesManager;
    class MFMuxStreamMediaTypeManager;
    class MFMuxStreamSampleManager;
    class MFSecureBuffer;


    namespace MF
    {
        


    }


    /// <summary>
    /// <p>
    /// Provides a generic way to store key/value pairs on an object. The keys are GUIDs, 
    /// and the values can be any of the following data types: UINT32, UINT64, double, GUID, 
    /// wide-character string, byte array, or IUnknown pointer. The standard implementation 
    /// of this interface holds a thread lock while values are added, deleted, or retrieved.
    /// </p>
    /// <p>
    /// For a list of predefined attribute GUIDs, see Media Foundation Attributes. Each 
    /// attribute GUID has an expected data type. The various "set" methods in MFAttributes 
    /// do not validate the type against the attribute GUID. It is the application's 
    /// responsibility to set the correct type for the attribute.
    /// </p>
    /// <p>
    /// To create an empty attribute store, call MFAttributes::Create.
    /// </p>
    /// </summary>
    class MFAttributes : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFAttributes, Unknown, IMFAttributes, IUnknown)
    public:
        static MFAttributes Create(UInt32 initialSize)
        {
            IMFAttributes* itf = nullptr;
            auto hr = MFCreateAttributes(&itf, initialSize);
            HCC_COM_CHECK_HRESULT(hr);
            return MFAttributes(itf);
        }

        static MFAttributes Create(const MF::Attributes& attributes)
        { 
            auto result = Create(static_cast<UInt32>(attributes.size()));
            attributes.AssignTo(result);
            return result;
        }

        template<typename ReaderT>
        void Read(ReaderT& reader) const
        {
            MF::Attributes attributes;
            attributes.Read(reader);
            attributes.AssignTo(*this);
        }
        template<typename WriterT>
        void Write(WriterT& writer)
        {
            MF::Attributes attributes(*this);
            attributes.Write(writer);
        }



        bool GetItem( const Guid& key, PROPVARIANT* value) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetItem(key, value);
            if (hr != MF_E_ATTRIBUTENOTFOUND)
            {
                HCC_COM_CHECK_HRESULT2(hr, pInterface);
            }
            return hr == S_OK;
        }

        bool GetItemType( const Guid& key, MF_ATTRIBUTE_TYPE* type) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetItemType(key, type);
            if (hr != MF_E_ATTRIBUTENOTFOUND)
            {
                HCC_COM_CHECK_HRESULT2(hr, pInterface);
            }
            return hr == S_OK;
        }

        MF_ATTRIBUTE_TYPE GetItemType(const Guid& key) const
        {
            MF_ATTRIBUTE_TYPE result{};
            GetItemType(key, &result);
            return result;
        }


        void CompareItem( const Guid& key, REFPROPVARIANT value, BOOL* result) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CompareItem(key, value, result);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        bool CompareItem(const Guid& key, REFPROPVARIANT value ) const
        {
            BOOL result = FALSE;
            CompareItem(key, value, &result);
            return result != FALSE;
        }


        void Compare( IMFAttributes* other, MF_ATTRIBUTES_MATCH_TYPE matchType, BOOL* result) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Compare(other, matchType, result);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        void Compare(const MFAttributes& other, MF_ATTRIBUTES_MATCH_TYPE matchType, BOOL* result) const
        {
            Compare(other.GetInterfacePointer<IMFAttributes>(), matchType, result);
        }
        bool Compare(IMFAttributes* other, MF_ATTRIBUTES_MATCH_TYPE matchType) const
        {
            BOOL result = FALSE;
            Compare(other, matchType, &result);
            return result != FALSE;
        }
        bool Compare(const MFAttributes& other, MF_ATTRIBUTES_MATCH_TYPE matchType) const
        {
            BOOL result = FALSE;
            Compare(other, matchType, &result);
            return result != FALSE;
        }

        bool GetUINT32(const Guid& key, UINT32* value) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetUINT32(key, value);
            if (hr != MF_E_ATTRIBUTENOTFOUND)
            {
                HCC_COM_CHECK_HRESULT2(hr, pInterface);
            }
            return hr == S_OK;
        }
        UINT32 GetUINT32( const Guid& key ) const
        {
            UINT32 value = 0;
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetUINT32(key, &value);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
            return value;
        }
        UINT32 GetUINT32OrDefault(const Guid& key, UINT32 defaultValue = 0) const
        {
            UINT32 value = 0;
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetUINT32(key, &value);
            if (hr == MF_E_ATTRIBUTENOTFOUND)
            {
                return defaultValue;
            }
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
            return value;
        }


        bool GetUINT64( const Guid& key, UINT64* value) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetUINT64(key, value);
            if (hr != MF_E_ATTRIBUTENOTFOUND)
            {
                HCC_COM_CHECK_HRESULT2(hr, pInterface);
            }
            return hr == S_OK;
        }
        UINT64 GetUINT64(const Guid& key) const
        {
            UINT64 value = 0;
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetUINT64(key, &value);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
            return value;
        }
        UINT64 GetUINT64OrDefault(const Guid& key, UINT64 defaultValue = 0) const
        {
            UINT64 value = 0;
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetUINT64(key, &value);
            if (hr == MF_E_ATTRIBUTENOTFOUND)
            {
                return defaultValue;
            }
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
            return value;
        }


        bool GetDouble( const Guid& key, double* value) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetDouble(key, value);
            if (hr != MF_E_ATTRIBUTENOTFOUND)
            {
                HCC_COM_CHECK_HRESULT2(hr, pInterface);
            }
            return hr == S_OK;
        }
        double GetDouble(const Guid& key) const
        {
            double value = 0.0;
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetDouble(key, &value);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
            return value;
        }
        double GetDoubleOrDefault(const Guid& key, double defaultValue = 0.0) const
        {
            double value = 0.0;
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetDouble(key, &value);
            if (hr == MF_E_ATTRIBUTENOTFOUND)
            {
                return defaultValue;
            }
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
            return value;
        }

        bool GetGUID( const Guid& key, Guid* value) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetGUID(key, (GUID*)value);
            if (hr != MF_E_ATTRIBUTENOTFOUND)
            {
                HCC_COM_CHECK_HRESULT2(hr, pInterface);
            }
            return hr == S_OK;
        }
        Guid GetGUID(const Guid& key) const
        {
            Guid value;
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetGUID(key, (GUID*)&value);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
            return value;
        }
        Guid GetGUIDOrDefault(const Guid& key, const Guid& defaultValue = Guid()) const
        {
            Guid value;
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetGUID(key, (GUID*)&value);
            if (hr == MF_E_ATTRIBUTENOTFOUND)
            {
                return defaultValue;
            }
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
            return value;
        }


        bool GetStringLength(const Guid& key, UINT32* length) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetStringLength(key, length);
            if (hr != MF_E_ATTRIBUTENOTFOUND)
            {
                HCC_COM_CHECK_HRESULT2(hr, pInterface);
            }
            return hr == S_OK;
        }
        UINT32 GetStringLength(const Guid& key) const
        {
            UINT32 value = 0;
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetStringLength(key, &value);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
            return value;
        }


        bool GetString(const Guid& key, LPWSTR buffer, UINT32 bufferSize, UINT32* length = nullptr) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetString(key, buffer, bufferSize, length);
            if (hr != MF_E_ATTRIBUTENOTFOUND)
            {
                HCC_COM_CHECK_HRESULT2(hr, pInterface);
            }
            return hr == S_OK;
        }

        std::wstring GetString(const Guid& key) const
        {
            UINT32 length = 0;
            if (GetStringLength(key, &length))
            {
                if (length)
                {
                    std::wstring result(static_cast<size_t>(length), static_cast<wchar_t>(0));
                    GetString(key, result.data(),length+1);
                    return result;
                }
            }
            return std::wstring();
        }


        bool GetAllocatedString( const Guid& key, LPWSTR* buffer, UINT32* length) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetAllocatedString(key, buffer, length);
            if (hr != MF_E_ATTRIBUTENOTFOUND)
            {
                HCC_COM_CHECK_HRESULT2(hr, pInterface);
            }
            return hr == S_OK;
        }

        bool GetBlobSize(const Guid& key, UINT32* blobSize) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetBlobSize(key, blobSize);
            if (hr != MF_E_ATTRIBUTENOTFOUND)
            {
                HCC_COM_CHECK_HRESULT2(hr, pInterface);
            }
            return hr == S_OK;
        }
        UINT32 GetBlobSize(const Guid& key) const
        {
            UINT32 value = 0;
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetBlobSize(key, &value);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
            return value;
        }

        bool GetBlob( const Guid& key, UINT8* buffer, UINT32 bufferSize, UINT32* blobSize = nullptr) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetBlob(key, buffer, bufferSize, blobSize);
            if (hr != MF_E_ATTRIBUTENOTFOUND)
            {
                HCC_COM_CHECK_HRESULT2(hr, pInterface);
            }
            return hr == S_OK;
        }

        template<typename T>
        MF::BlobValue<T> GetBlob(const Guid& key) const
        {
            UINT32 blobSize = 0;
            if (GetBlobSize(key, &blobSize))
            {
                MF::BlobValue<T> result(static_cast<size_t>(blobSize));
                GetBlob(key, reinterpret_cast<UINT8*>( result.data() ), blobSize);
                return result;
            }
            else
            {
                return MF::BlobValue<T>();
            }
        }


        bool GetAllocatedBlob( const Guid& key, UINT8** buffer, UINT32* blobSize) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetAllocatedBlob(key, buffer, blobSize);
            if (hr != MF_E_ATTRIBUTENOTFOUND)
            {
                HCC_COM_CHECK_HRESULT2(hr, pInterface);
            }
            return hr == S_OK;
        }

        bool GetUnknown( const Guid& key, const Guid& riid, LPVOID* result) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetUnknown(key, riid, result);
            if (hr != MF_E_ATTRIBUTENOTFOUND)
            {
                HCC_COM_CHECK_HRESULT2(hr, pInterface);
            }
            return hr == S_OK;
        }

        template<typename T>
            requires std::is_base_of_v<Unknown,T>
        T GetUnknown(const Guid& key) const
        {
            using ItfT = T::InterfaceType;
            const Guid riid = __uuidof(ItfT);
            ItfT* itf = nullptr;
            if (GetUnknown(key, riid, (void**)&itf))
            {
                return T(itf);
            }
            return T();
        }


        void SetItem( const Guid& key, REFPROPVARIANT Value) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetItem(key, Value);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        bool DeleteItem(const Guid& key) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->DeleteItem(key);
            if (hr != MF_E_ATTRIBUTENOTFOUND)
            {
                HCC_COM_CHECK_HRESULT2(hr, pInterface);
            }
            return hr == S_OK;
        }

        void DeleteAllItems( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->DeleteAllItems( );
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetUINT32( const Guid& key, UINT32 value) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetUINT32(key, value);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetUINT64( const Guid& key, UINT64 value) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetUINT64(key, value);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetDouble( const Guid& key, double value) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetDouble(key, value);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetGUID( const Guid& key, const Guid& value) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetGUID(key, value);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetString( const Guid& key, LPCWSTR value) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetString(key, value);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        void SetString(const Guid& key, const std::wstring& value) const
        {
            SetString(key, value.c_str());
        }

        void SetBlob( const Guid& key, const UINT8* buffer, UINT32 bufferSize) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetBlob(key, buffer, bufferSize);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        void SetBlob(const Guid& key, const std::span<byte>& buffer) const
        {
            SetBlob(key, buffer.data(), static_cast<UINT32>(buffer.size()));
        }
        void SetBlob(const Guid& key, const std::vector<byte>& buffer) const
        {
            SetBlob(key, buffer.data(), static_cast<UINT32>(buffer.size()));
        }

        template<typename T>
        void SetBlob(const Guid& key, const MF::BlobValue<T>& blob) const
        {
            SetBlob(key,  reinterpret_cast<const UINT8*>( blob.data() ), static_cast<UINT32>(blob.DataSize()));
        }

        void SetUnknown(const Guid& key, IUnknown* unknown) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetUnknown(key, unknown);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void LockStore( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->LockStore( );
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void lock() const
        {
            LockStore();
        }

        void UnlockStore( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->UnlockStore();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        void unlock() const
        {
            UnlockStore();
        }


        void GetCount( UINT32* result ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetCount(result);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        UInt32 GetCount() const
        {
            UInt32 result = 0;
            GetCount(&result);
            return result;
        }


        void GetItemByIndex( UINT32 index, Guid* key, PROPVARIANT* value = nullptr) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetItemByIndex(index, (GUID*)key, value);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        Guid GetItemKeyByIndex(UINT32 index) const
        {
            Guid result;
            GetItemByIndex(index, &result);
            return result;
        }



        void CopyAllItems(IMFAttributes* destination) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CopyAllItems(destination);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        void CopyAllItems(const MFAttributes& destination) const
        {
            CopyAllItems(destination.GetInterfacePointer<IMFAttributes>());
        }
    };

    enum class MFMediaBufferAlignment : DWORD
    {
        AlignOn1ByteBoundary = MF_1_BYTE_ALIGNMENT,
        AlignOn2ByteBoundary = MF_2_BYTE_ALIGNMENT,
        AlignOn4ByteBoundary = MF_4_BYTE_ALIGNMENT,
        AlignOn8ByteBoundary = MF_8_BYTE_ALIGNMENT,
        AlignOn16ByteBoundary = MF_16_BYTE_ALIGNMENT,
        AlignOn32ByteBoundary = MF_32_BYTE_ALIGNMENT,
        AlignOn64ByteBoundary = MF_64_BYTE_ALIGNMENT,
        AlignOn128ByteBoundary = MF_128_BYTE_ALIGNMENT,
        AlignOn256ByteBoundary = MF_256_BYTE_ALIGNMENT,
        AlignOn512ByteBoundary = MF_512_BYTE_ALIGNMENT,
        AlignOn1024ByteBoundary = MF_1024_BYTE_ALIGNMENT,
        AlignOn2048ByteBoundary = MF_2048_BYTE_ALIGNMENT,
        AlignOn4096ByteBoundary = MF_4096_BYTE_ALIGNMENT,
        AlignOn9192ByteBoundary = MF_8192_BYTE_ALIGNMENT,

    };

    class MFMediaBuffer : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFMediaBuffer, Unknown, IMFMediaBuffer, IUnknown)
    public:
        /// <summary>
        /// Creates a system-memory buffer object to hold 2D image data.
        /// </summary>
        /// <param name="width">
        /// Width of the image, in pixels.
        /// </param>
        /// <param name="height">
        /// Height of the image, in pixels.
        /// </param>
        /// <param name="fourCC">
        /// A FOURCC code or D3DFORMAT value that specifies the video format. If you have 
        /// a video subtype GUID, you can use the first DWORD of the subtype.
        /// </param>
        /// <param name="bottomUp">
        /// f true, the buffer's MF2DBuffer::ContiguousCopyTo method copies the buffer into 
        /// a bottom-up format. The bottom-up format is compatible with GDI for uncompressed 
        /// RGB images. If this parameter is false, the ContiguousCopyTo method copies the buffer 
        /// into a top-down format, which is compatible with DirectX.
        /// </param>
        /// <returns>The new MFMediaBuffer object</returns>
        static MFMediaBuffer Create2DMediaBuffer(DWORD width, DWORD height, DWORD fourCC, bool bottomUp = false )
        {
            IMFMediaBuffer* itf = nullptr;
            auto hr = MFCreate2DMediaBuffer(width, height, fourCC, bottomUp, &itf);
            HCC_COM_CHECK_HRESULT(hr);
            return MFMediaBuffer(itf);
        }

        using Alignment = MFMediaBufferAlignment;
        static MFMediaBuffer CreateAlignedMemoryBuffer(DWORD maxLength, Alignment aligment)
        {
            IMFMediaBuffer* itf = nullptr;
            auto hr = MFCreateAlignedMemoryBuffer(maxLength, static_cast<DWORD>(aligment), &itf);
            HCC_COM_CHECK_HRESULT(hr);
            return MFMediaBuffer(itf);
        }


        /// <summary>
        /// Creates a media buffer that wraps an existing media buffer. The new media buffer 
        /// points to the same memory as the original media buffer, or to an offset from the 
        /// start of the memory.
        /// </summary>
        /// <param name="buffer">
        /// A pointer to the IMFMediaBuffer interface of the original media buffer.
        /// </param>
        /// <param name="offset">
        /// The start of the new buffer, as an offset in bytes from the start of the original buffer.
        /// </param>
        /// <param name="length">
        /// The size of the new buffer. The value of offset + length must be less than or 
        /// equal to the size of valid data the original buffer. (The size of the valid 
        /// data is returned by the MFMediaBuffer::GetCurrentLength method.)
        /// </param>
        /// <returns>The new MFMediaBuffer object</returns>
        static MFMediaBuffer CreateMediaBufferWrapper(IMFMediaBuffer* buffer, DWORD offset, DWORD length)
        {
            IMFMediaBuffer* itf = nullptr;
            auto hr = MFCreateMediaBufferWrapper(buffer, offset, length, &itf);
            HCC_COM_CHECK_HRESULT(hr);
            return MFMediaBuffer(itf);
        }
        static MFMediaBuffer CreateMediaBufferWrapper(const MFMediaBuffer& buffer, DWORD offset, DWORD length)
        {
            return CreateMediaBufferWrapper(buffer.GetInterfacePointer<IMFMediaBuffer>(), offset, length);
        }
        /// <summary>
        /// Allocates system memory and creates a media buffer to manage it.
        /// </summary>
        /// <param name="maxLength">
        /// Size of the buffer, in bytes.
        /// </param>
        /// <returns>The new MFMediaBuffer object</returns>
        static MFMediaBuffer CreateMemoryBuffer(DWORD maxLength)
        {
            IMFMediaBuffer* itf = nullptr;
            auto hr = MFCreateMemoryBuffer(maxLength, &itf);
            HCC_COM_CHECK_HRESULT(hr);
            return MFMediaBuffer(itf);
        }

        void Lock(BYTE** buffer, DWORD* maxLength, DWORD* currentLength) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Lock(buffer, maxLength, currentLength);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Unlock() const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Unlock();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetCurrentLength( DWORD* currentLength) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetCurrentLength(currentLength);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        DWORD GetCurrentLength() const
        {
            DWORD result = 0;
            GetCurrentLength(&result);
            return result;
        }

        void SetCurrentLength( DWORD currentLength) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetCurrentLength(currentLength);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetMaxLength( DWORD* maxLength) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetMaxLength(maxLength);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        DWORD GetMaxLength() const
        {
            DWORD result = 0;
            GetMaxLength(&result);
            return result;
        }
    };


    class MFSample : public MFAttributes
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFSample, MFAttributes, IMFSample, IMFAttributes)
    public:
        /// <summary>
        /// Creates an empty media sample.
        /// </summary>
        static MFSample Create()
        {
            IMFSample* itf = nullptr;
            auto hr = MFCreateSample(&itf);
            HCC_COM_CHECK_HRESULT(hr);
            return MFSample(itf);
        }

        /// <summary>
        /// Creates a media sample with a single buffer.
        /// </summary>
        static MFSample Create(DWORD maxLength)
        {
            auto memoryBuffer = MFMediaBuffer::CreateMemoryBuffer(maxLength);
            auto result = Create();
            result.AddBuffer(memoryBuffer);
            return result;
        }

        void GetSampleFlags(DWORD* sampleFlags) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetSampleFlags(sampleFlags);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        DWORD GetSampleFlags() const
        {
            DWORD result = 0;
            GetSampleFlags(&result);
            return result;
        }

        void SetSampleFlags( DWORD sampleFlags) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetSampleFlags(sampleFlags);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetSampleTime( LONGLONG* sampleTime) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetSampleTime(sampleTime);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        TimeSpan GetSampleTime() const
        {
            LONGLONG result = 0;
            GetSampleTime(&result);
            return TimeSpan(result);
        }

        void SetSampleTime( LONGLONG sampleTime) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetSampleTime(sampleTime);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetSampleTime(const TimeSpan& sampleTime) const
        {
            SetSampleTime(sampleTime.Ticks());
        }


        void GetSampleDuration( LONGLONG* sampleDuration) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetSampleDuration(sampleDuration);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        TimeSpan GetSampleDuration() const
        {
            LONGLONG result = 0;
            GetSampleDuration(&result);
            return TimeSpan(result);
        }


        void SetSampleDuration( LONGLONG sampleDuration) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetSampleDuration(sampleDuration);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        void SetSampleDuration(const TimeSpan& sampleDuration) const
        {
            SetSampleDuration(sampleDuration.Ticks());
        }


        void GetBufferCount( DWORD* bufferCount) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetBufferCount(bufferCount);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        DWORD GetBufferCount() const
        {
            DWORD result = 0;
            GetBufferCount(&result);
            return result;
        }


        void GetBufferByIndex( DWORD index, IMFMediaBuffer** buffer) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetBufferByIndex(index, buffer);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        MFMediaBuffer GetBufferByIndex(DWORD index) const
        {
            IMFMediaBuffer* itf = nullptr;
            GetBufferByIndex(index, &itf);
            return MFMediaBuffer(itf);
        }


        void ConvertToContiguousBuffer( IMFMediaBuffer** buffer) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->ConvertToContiguousBuffer(buffer);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        MFMediaBuffer ConvertToContiguousBuffer() const
        {
            IMFMediaBuffer* itf = nullptr;
            ConvertToContiguousBuffer(&itf);
            return MFMediaBuffer(itf);
        }

        void AddBuffer( IMFMediaBuffer* buffer) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->AddBuffer(buffer);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        void AddBuffer(const MFMediaBuffer& buffer) const
        {
            AddBuffer(buffer.GetInterfacePointer<IMFMediaBuffer>());
        }

        void RemoveBufferByIndex( DWORD index) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->RemoveBufferByIndex(index);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void RemoveAllBuffers( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->RemoveAllBuffers( );
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        /// <summary>
        /// Retrieves the total length of the valid data in all of 
        /// the buffers in the sample. The length is calculated as 
        /// the sum of the values retrieved by the 
        /// IMFMediaBuffer::GetCurrentLength method.
        /// </summary>
        /// <param name="totalLength">
        /// Receives the total length of the valid data, in bytes.
        /// </param>
        void GetTotalLength( DWORD* totalLength) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetTotalLength(totalLength);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        /// <summary>
        /// Retrieves the total length of the valid data in all of 
        /// the buffers in the sample. The length is calculated as 
        /// the sum of the values retrieved by the 
        /// IMFMediaBuffer::GetCurrentLength method.
        /// </summary>
        /// <returns>
        /// The total length of the valid data, in bytes.
        /// </returns>
        DWORD GetTotalLength() const
        {
            DWORD result = 0;
            GetTotalLength(&result);
            return result;
        }

        void CopyToBuffer( IMFMediaBuffer* buffer) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CopyToBuffer(buffer);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        void CopyToBuffer(const MFMediaBuffer& buffer) const
        {
            CopyToBuffer(buffer.GetInterfacePointer<IMFMediaBuffer>());
        }


        // Attributes

        /// <summary>
        /// Specifies whether a media sample contains a 3D video frame.
        /// </summary>
        /// <returns>
        /// true if this is a video frame that has two or more stereoscopic views.
        /// </returns>
        bool Get3DVideo() const
        {
            return GetUINT32OrDefault(MFSampleExtension_3DVideo) != FALSE;
        }
        /// <summary>
        /// Specifies whether a media sample contains a 3D video frame.
        /// </summary>
        /// <param name="value">
        /// Set to true to indicate that this is a video frame that has two or more stereoscopic views.
        /// </param>
        void Set3DVideo(bool value) const
        {
            SetUINT32(MFSampleExtension_3DVideo, value ? TRUE : FALSE);
        }

        /// <summary>
        /// Specifies how a 3D video frame is stored in a media sample.
        /// </summary>
        /// <returns>A value from the MFVideo3DSampleFormat enumeration.</returns>
        MFVideo3DSampleFormat Get3DVideoSampleFormat() const
        {
            return static_cast<MFVideo3DSampleFormat>( GetUINT32OrDefault(MFSampleExtension_3DVideo_SampleFormat) );
        }
        void Set3DVideoSampleFormat(MFVideo3DSampleFormat video3DSampleFormat) const
        {
            SetUINT32(MFSampleExtension_3DVideo_SampleFormat, static_cast<UINT32>( video3DSampleFormat ) );
        }

        /// <summary>
        /// Specifies the field dominance for an interlaced video frame. This attribute applies to media samples.
        /// </summary>
        /// <returns>
        /// A bool value.
        /// </returns>
        /// <remarks>
        /// <p>
        /// If the video frame is interlaced and the sample contains two interleaved fields, 
        /// this attribute indicates which field is displayed first. If true, the bottom field 
        /// is first in time. If false, the top field is first.
        /// </p>
        /// <p>
        /// If the frame is interlaced and the sample contains a single field, this attribute 
        /// indicates which field the sample contains. If true, the sample contains the bottom 
        /// field. If false, the sample contains the top field.
        /// </p>
        /// <p>
        /// If the frame is progressive, this attribute describes how the fields should be ordered 
        /// when the output is interlaced. If true, the bottom field should be output first. If 
        /// false, the top field should be output first.
        /// </p>
        /// <p>
        /// If this attribute not set, the media type describes the field dominance.
        /// </p>
        /// </remarks>
        bool GetBottomFieldFirst() const
        {
            return GetUINT32OrDefault(MFSampleExtension_BottomFieldFirst) != FALSE;
        }
        void SetBottomFieldFirst(bool value) const
        {
            SetUINT32(MFSampleExtension_BottomFieldFirst, value ? TRUE : FALSE);
        }

        /// <summary>
        /// Retrieves the camera extrinsics for the sample.
        /// </summary>
        MF::CameraExtrinsics GetCameraExtrinsics() const
        {
            UINT32 blobSize = 0;
            if (GetBlobSize(MFSampleExtension_CameraExtrinsics, &blobSize))
            {
                MFCameraExtrinsics* cameraExtrinsics = reinterpret_cast<MFCameraExtrinsics*>( new Byte[blobSize] );
                MF::CameraExtrinsics result(cameraExtrinsics);
                cameraExtrinsics->TransformCount = 0;
                GetBlob(MFSampleExtension_CameraExtrinsics, reinterpret_cast<UINT8*>(cameraExtrinsics), blobSize);
                return result;
            }
            return MF::CameraExtrinsics();
        }
        void SetCameraExtrinsics(const MF::CameraExtrinsics& cameraExtrinsics)
        {
            SetBlob(MFSampleExtension_CameraExtrinsics, reinterpret_cast<const UINT8*>( cameraExtrinsics.data()), static_cast<UINT32>(cameraExtrinsics.DataSize()));
        }


        /// <summary>
        /// Retrives the MFAttributes store for all the metadata related to the capture pipeline.
        /// </summary>
        /// <returns></returns>
        MFAttributes CaptureMetadata() const
        {
            return GetUnknown<MFAttributes>(MFSampleExtension_CaptureMetadata);
        }


        /// <summary>
        /// Indicates whether a sample is a random access point.
        /// </summary>
        /// <remarks>
        /// <p>
        /// This attribute applies to samples. If the attribute is true, the sample is 
        /// a random access point and decoding can begin from this sample. Otherwise, 
        /// the sample is not a random access point.
        /// </p>
        /// <p>
        /// If this attribute is not set, the default value is FALSE.
        /// </p>
        /// </remarks>
        bool GetCleanPoint() const
        {
            return GetUINT32OrDefault(MFSampleExtension_CleanPoint) != FALSE;
        }
        void SetCleanPoint(bool value) const
        {
            SetUINT32(MFSampleExtension_CleanPoint, value ? TRUE : FALSE);
        }
        /// <summary>
        /// Indicates whether a video sample is a key frame.
        /// </summary>
        /// <returns>
        /// true if the sample is a key frame.
        /// </returns>
        bool IsKeyFrame() const
        {
            return GetCleanPoint();
        }

        /// <summary>
        /// Retrieves the Key ID for the sample.
        /// </summary>
        /// <returns></returns>
        Guid GetContentKeyId() const
        {
            return GetGUIDOrDefault(MFSampleExtension_Content_KeyID);
        }

        /// <summary>
        /// Sets the Key ID for the sample.
        /// </summary>
        /// <param name="keyId">
        /// the Key ID for the sample
        /// </param>
        void SetContentKeyId(const Guid& keyId) const
        {
            SetGUID(MFSampleExtension_Content_KeyID, keyId);
        }

        /// <summary>
        /// Specifies whether a deinterlaced video frame was derived from 
        /// the upper field or the lower field.
        /// </summary>
        /// <remarks>
        /// <p>
        /// This attribute is valid for deinterlaced samples only. Set this 
        /// attribute if the frame was deinterlaced by interpolating one of 
        /// the fields.
        /// </p>
        /// <p>
        /// If the value is TRUE, the lower field was interpolated from the 
        /// upper field. If the value is FALSE, the upper field was interpolated 
        /// from the lower field.
        /// </p>
        /// <p>
        /// If the attribute is not set, the frame has not been deinterlaced. The 
        /// frame is either a true progressive frame, or it is an interlaced frame.
        /// </p>
        /// <p>
        /// This attribute is informational. A software deinterlacer could set this 
        /// attribute. If this attribute is set, it provides a hint that you can 
        /// recover the original field by dropping the interpolated scan lines. 
        /// For example, if the attribute is TRUE, you can recover the original 
        /// upper field by dropping the interpolated lower field.
        /// </p>
        /// </remarks>
        bool GetDerivedFromTopField() const
        {
            return GetUINT32OrDefault(MFSampleExtension_DerivedFromTopField) != FALSE;
        }
        /// <summary>
        /// Specifies whether a deinterlaced video frame was derived from 
        /// the upper field or the lower field.
        /// </summary>
        /// <remarks>
        /// <p>
        /// This attribute is valid for deinterlaced samples only. Set this 
        /// attribute if the frame was deinterlaced by interpolating one of 
        /// the fields.
        /// </p>
        /// <p>
        /// If the value is TRUE, the lower field was interpolated from the 
        /// upper field. If the value is FALSE, the upper field was interpolated 
        /// from the lower field.
        /// </p>
        /// <p>
        /// If the attribute is not set, the frame has not been deinterlaced. The 
        /// frame is either a true progressive frame, or it is an interlaced frame.
        /// </p>
        /// <p>
        /// This attribute is informational. A software deinterlacer could set this 
        /// attribute. If this attribute is set, it provides a hint that you can 
        /// recover the original field by dropping the interpolated scan lines. 
        /// For example, if the attribute is TRUE, you can recover the original 
        /// upper field by dropping the interpolated lower field.
        /// </p>
        /// </remarks>
        void SetDerivedFromTopField(bool value) const
        {
            SetUINT32(MFSampleExtension_DerivedFromTopField, value ? TRUE : FALSE);
        }

        /// <summary>
        /// Retrieves the time stamp provided by the device driver.
        /// </summary>
        /// <remarks>
        /// <p>
        /// This attribute is set on media samples created by a media 
        /// source for a capture device. This attribute's value is in 
        /// the MFTIME domain, sharing an epoch with query performance 
        /// counter (QPC) time and always expressed in 100ns units. 
        /// This attribute is available for MFTs inserted into the 
        /// capture pipeline.
        /// </p>
        /// </remarks>
        TimeSpan GetDeviceTimestamp() const
        {
            return TimeSpan( static_cast<Int64>(GetUINT64OrDefault(MFSampleExtension_DeviceTimestamp)) );
        }
        void SetDeviceTimestamp(UInt64 value)
        {
            SetUINT64(MFSampleExtension_DeviceTimestamp, value);
        }
        void SetDeviceTimestamp(const TimeSpan& value)
        {
            SetUINT64(MFSampleExtension_DeviceTimestamp, static_cast<UInt64>(value.Ticks()));
        }

        /// <summary>
        /// Specifies whether a media sample is the first sample after a gap in the stream.
        /// </summary>
        /// <remarks>
        /// This attribute applies to media samples. If this attribute is true, it means 
        /// there was a discontinuity in the stream and this sample is the first to 
        /// appear after the gap.
        /// </remarks>
        bool GetDiscontinuity() const
        {
            return GetUINT32OrDefault(MFSampleExtension_Discontinuity) != FALSE;
        }
        void SetDiscontinuity(bool value) const
        {
            SetUINT32(MFSampleExtension_Discontinuity, value ? TRUE : FALSE);
        }

        /// <summary>
        /// Specifies the encrypted byte block size for sample-based pattern encryption.
        /// </summary>
        /// <remarks>
        /// <p>
        /// The number of clear (non-encrypted) bytes in the subsample mapping block are 
        /// specified in the MFSampleExtension_Encryption_SkipByteBlock attribute. If either 
        /// of these attributes are not present or have a value of 0, it means that the 
        /// sample data is not encrypted. Either both of these values must be non-zero, 
        /// positive values, or both must have a value of zero.
        /// </p>
        /// <p>
        /// In cases where the Source is MP4-based, the value is set based off the values 
        /// of default_crypt_byte_block within the track encryption box (‘tenc’) in the MP4 header.
        /// </p>
        /// </remarks>
        UInt32 GetEncryptionCryptByteBlock() const
        {
            return GetUINT32OrDefault(MFSampleExtension_Encryption_CryptByteBlock);
        }
        /// <summary>
        /// Specifies the encrypted byte block size for sample-based pattern encryption.
        /// </summary>
        /// <remarks>
        /// <p>
        /// The number of clear (non-encrypted) bytes in the subsample mapping block are 
        /// specified in the MFSampleExtension_Encryption_SkipByteBlock attribute. If either 
        /// of these attributes are not present or have a value of 0, it means that the 
        /// sample data is not encrypted. Either both of these values must be non-zero, 
        /// positive values, or both must have a value of zero.
        /// </p>
        /// <p>
        /// In cases where the Source is MP4-based, the value is set based off the values 
        /// of default_crypt_byte_block within the track encryption box (‘tenc’) in the MP4 header.
        /// </p>
        /// </remarks>
        void SetEncryptionCryptByteBlock(UInt32 value) const
        {
            SetUINT32(MFSampleExtension_Encryption_CryptByteBlock, value);
        }

        /// <summary>
        /// Specifies the protection scheme for encrypted samples.
        /// </summary>
        /// <remarks>
        /// <p>
        /// The value of this attribute is a member of the MFSampleEncryptionProtectionScheme 
        /// enumeration. In cases where the media source is MP4-based, the value is set based 
        /// off the value of the scheme_type field within the scheme type box (‘schm’) in the 
        /// MP4 header (‘moov’ or ‘moof’).
        /// </p>
        /// <p>
        /// If the scheme_type field in an MP4-based file, or stream, is set to ‘cenc’ or ‘cbc1’, 
        /// then the MFSampleExtension_Encryption_ProtectionScheme attribute should be set to 
        /// PROTECTION_SCHEME_AES_CTR or PROTECTION_SCHEME_CBC, respectively, and no values 
        /// should be set for MFSampleExtension_Encryption_CryptByteBlock and 
        /// MFSampleExtension_Encryption_SkipByteBlock.
        /// </p>
        /// <p>
        /// If the scheme_type field in an MP4-based file, or stream, is set to ‘cens’ or ‘cbcs’, 
        /// then the MFSampleExtension_Encryption_ProtectionScheme attribute should be set to 
        /// PROTECTION_SCHEME_AES_CTR or PROTECTION_SCHEME_CBC, respectively, and 
        /// MFSampleExtension_Encryption_CryptByteBlock and MFSampleExtension_Encryption_SkipByteBlock 
        /// must be set using the values in the ‘tenc’ box.
        /// </p>
        /// </remarks>
        MFSampleEncryptionProtectionScheme GetEncryptionProtectionScheme() const
        {
            return static_cast<MFSampleEncryptionProtectionScheme>( GetUINT32OrDefault(MFSampleExtension_Encryption_ProtectionScheme) );
        }
        /// <summary>
        /// Specifies the protection scheme for encrypted samples.
        /// </summary>
        /// <remarks>
        /// <p>
        /// The value of this attribute is a member of the MFSampleEncryptionProtectionScheme 
        /// enumeration. In cases where the media source is MP4-based, the value is set based 
        /// off the value of the scheme_type field within the scheme type box (‘schm’) in the 
        /// MP4 header (‘moov’ or ‘moof’).
        /// </p>
        /// <p>
        /// If the scheme_type field in an MP4-based file, or stream, is set to ‘cenc’ or ‘cbc1’, 
        /// then the MFSampleExtension_Encryption_ProtectionScheme attribute should be set to 
        /// PROTECTION_SCHEME_AES_CTR or PROTECTION_SCHEME_CBC, respectively, and no values 
        /// should be set for MFSampleExtension_Encryption_CryptByteBlock and 
        /// MFSampleExtension_Encryption_SkipByteBlock.
        /// </p>
        /// <p>
        /// If the scheme_type field in an MP4-based file, or stream, is set to ‘cens’ or ‘cbcs’, 
        /// then the MFSampleExtension_Encryption_ProtectionScheme attribute should be set to 
        /// PROTECTION_SCHEME_AES_CTR or PROTECTION_SCHEME_CBC, respectively, and 
        /// MFSampleExtension_Encryption_CryptByteBlock and MFSampleExtension_Encryption_SkipByteBlock 
        /// must be set using the values in the ‘tenc’ box.
        /// </p>
        /// </remarks>
        void SetEncryptionProtectionScheme(MFSampleEncryptionProtectionScheme value) const
        {
            SetUINT32(MFSampleExtension_Encryption_ProtectionScheme, value);
        }

        /// <summary>
        /// Specifies the ID of an encrypted sample.
        /// </summary>
        MF::BlobValue<Byte> GetEncryptionSampleID() const
        {
            return GetBlob<Byte>(MFSampleExtension_Encryption_SampleID);
        }
        /// <summary>
        /// Specifies the ID of an encrypted sample.
        /// </summary>
        void SetEncryptionSampleID(const MF::BlobValue<Byte>& value) const
        {
            SetBlob(MFSampleExtension_Encryption_SampleID, value);
        }

        /// <summary>
        /// Specifies the clear (non-encrypted) byte block size for sample-based pattern encryption.
        /// </summary>
        /// <remarks>
        /// <p>
        /// The number of encrypted bytes in the subsample mapping block are specified in the 
        /// MFSampleExtension_Encryption_CryptByteBlock attribute. If either of these attributes 
        /// are not present or have a value of 0, it means that the sample data is not encrypted. 
        /// Either both of these values must be non-zero, positive values, or both must have a 
        /// value of zero.
        /// </p>
        /// <p>
        /// In cases where the Source is MP4-based, the value is set based off the values of 
        /// default_skip_byte_block within the track encryption box (‘tenc’) in the MP4 header.
        /// </p>
        /// </remarks>
        UInt32 GetEncryptionSkipByteBlock() const
        {
            return GetUINT32OrDefault(MFSampleExtension_Encryption_SkipByteBlock);
        }
        /// <summary>
        /// Specifies the clear (non-encrypted) byte block size for sample-based pattern encryption.
        /// </summary>
        /// <remarks>
        /// <p>
        /// The number of encrypted bytes in the subsample mapping block are specified in the 
        /// MFSampleExtension_Encryption_CryptByteBlock attribute. If either of these attributes 
        /// are not present or have a value of 0, it means that the sample data is not encrypted. 
        /// Either both of these values must be non-zero, positive values, or both must have a 
        /// value of zero.
        /// </p>
        /// <p>
        /// In cases where the Source is MP4-based, the value is set based off the values of 
        /// default_skip_byte_block within the track encryption box (‘tenc’) in the MP4 header.
        /// </p>
        /// </remarks>
        void SetEncryptionSkipByteBlock(UInt32 value) const
        {
            SetUINT32(MFSampleExtension_Encryption_SkipByteBlock, value);
        }

        /// <summary>
        /// Retrieves the sub-sample mapping for the sample indicating the clear and encrypted 
        /// bytes in the sample data.
        /// </summary>
        /// <remarks>
        /// <p>
        /// The BLOB should contain an array of byte ranges as DWORDs where every two DWORDs 
        /// makes a set. The first DWORD in each set is the number of clear bytes and the 
        /// second DWORD of the set is the number of encrypted bytes. Note that a pair of 0s 
        /// is not a valid set (either value can be 0, but not both). The array of byte ranges 
        /// indicate which ranges to decrypt, including the possibility that the entire sample 
        /// should not be decrypted. It is recommended that this should not be set on clear 
        /// samples, though it is possible to achieve the same result by setting it with the 
        /// appropriate values.
        /// </p>
        /// </remarks>
        MF::EncryptionSubSampleMappingSplit GetEncryptionSubSampleMappingSplit() const
        {
            UINT32 blobSize = 0;
            if (GetBlobSize(MFSampleExtension_Encryption_SubSampleMappingSplit, &blobSize))
            {
                MF::EncryptionSubSampleMappingSplit result(static_cast<size_t>(blobSize));
                GetBlob(MFSampleExtension_Encryption_SubSampleMappingSplit, reinterpret_cast<UINT8*>(result.data()), blobSize);
                return result;
            }
            else
            {
                return MF::EncryptionSubSampleMappingSplit();
            }
        }
        /// <summary>
        /// Retrieves the sub-sample mapping for the sample indicating the clear and encrypted 
        /// bytes in the sample data.
        /// </summary>
        /// <remarks>
        /// <p>
        /// The BLOB should contain an array of byte ranges as DWORDs where every two DWORDs 
        /// makes a set. The first DWORD in each set is the number of clear bytes and the 
        /// second DWORD of the set is the number of encrypted bytes. Note that a pair of 0s 
        /// is not a valid set (either value can be 0, but not both). The array of byte ranges 
        /// indicate which ranges to decrypt, including the possibility that the entire sample 
        /// should not be decrypted. It is recommended that this should not be set on clear 
        /// samples, though it is possible to achieve the same result by setting it with the 
        /// appropriate values.
        /// </p>
        /// </remarks>
        void SetEncryptionSubSampleMappingSplit(const MF::EncryptionSubSampleMappingSplit& value)
        {
            SetBlob(MFSampleExtension_Encryption_SubSampleMappingSplit, reinterpret_cast<const UINT8*>(value.data()), static_cast<UINT32>(value.DataSize()));
        }
        void SetEncryptionSubSampleMappingSplit(const DWORD* values, size_t numberOfValues)
        {
            SetBlob(MFSampleExtension_Encryption_SubSampleMappingSplit, reinterpret_cast<const UINT8*>(values), static_cast<UINT32>(numberOfValues));
        }

        /// <summary>
        /// Specifies whether a video frame is corrupted.
        /// </summary>
        /// <remarks>
        /// A video decoder can set this attribute on its output samples. If the value 
        /// is 1, the decoder detected data corruption in the frame. If the value is 0, 
        /// there is no data corruption, or none was detected.
        /// </remarks>
        bool GetFrameCorruption() const
        {
            return GetUINT32OrDefault(MFSampleExtension_FrameCorruption) != 0;
        }
        /// <summary>
        /// Specifies whether a video frame is corrupted.
        /// </summary>
        /// <remarks>
        /// A video decoder can set this attribute on its output samples. If the value 
        /// is 1, the decoder detected data corruption in the frame. If the value is 0, 
        /// there is no data corruption, or none was detected.
        /// </remarks>
        void SetFrameCorruption(bool value) const
        {
            SetUINT32(MFSampleExtension_FrameCorruption,value?TRUE:FALSE);
        }

        /// <summary>
        /// Gets an object of type MFCollectionT<MFSample> containing MFSample objects 
        /// which contain network abstraction layer units (NALUs) and Supplemental 
        /// Enhancement Information (SEI) units forwarded by a decoder.
        /// </summary>
        MFCollectionT<MFSample> GetForwardedDecodeUnits() const;

        /// <summary>
        /// Retrieves the type, NALU or SEI, of a unit attached to an MFSample in 
        /// a MFSampleExtension_ForwardedDecodeUnits collection.
        /// </summary>
        MF_CUSTOM_DECODE_UNIT_TYPE GetForwardedDecodeUnitType() const
        {
            return static_cast<MF_CUSTOM_DECODE_UNIT_TYPE>(GetUINT32OrDefault(MFSampleExtension_ForwardedDecodeUnitType));
        }

        /// <summary>
        /// Indicates whether a video frame is interlaced or progressive. If true, the frame 
        /// is interlaced. If false, the frame is progressive. If not set, the media type 
        /// describes the interlacing. This attribute applies to media samples.
        /// </summary>
        std::optional<bool> GetInterlaced() const
        {
            UINT32 value = 0;
            if (GetUINT32(MFSampleExtension_Interlaced, &value))
            {
                return { value != FALSE };
            }
            return {};
        }


        /// <summary>
        /// Specifies Long Term Reference (LTR) frame info and is returned on the output sample.
        /// </summary>
        /// <remarks>
        /// <b>H.264/AVC encoders:</b>
        /// <p>
        /// Encoders shall return this attribute on the output sample when the application controls 
        /// LTR frames, which is specified by CODECAPI_AVEncVideoLTRBufferControl.
        /// </p>
        /// <p>
        /// MFSampleExtension_LongTermReferenceFrameInfo returns up to two fields.
        /// </p>
        /// <p>
        /// The first field, bits[0..15], is LongTermFrameIdx associated with the 
        /// output frame if it is marked as a LTR frame. The first value is 0xffff, 
        /// if this output frame is a short term reference frame or a non-reference frame.
        /// </p>
        /// <p>
        /// The second field, bits[16..31], is a bitmap consisting of MaxNumLTRFrames 
        /// many bits that indicate which LTR frame(s) were used for encoding this output 
        /// frame, starting from bit 16. The rest of bits shall be set to 0. The second 
        /// value is 0 if this output frame is not encoded using any LTR frames. 
        /// MaxNumLTRFrames is the maximum number of LTR frames set through 
        /// CODECAPI_AVEncVideoLTRBufferControl.
        /// </p>
        /// </remarks>
        UInt32 GetLongTermReferenceFrameInfo() const
        {
            return GetUINT32OrDefault(MFSampleExtension_LongTermReferenceFrameInfo);
        }


        /// <summary>
        /// This attribute returns the mean absolute difference (MAD) across all 
        /// macro-blocks in the Y plane.
        /// </summary>
        /// <remarks>
        /// Application can request encoder to set this attribute on output samples 
        /// by using CODECAPI_AVEncVideoMeanAbsoluteDifference.
        /// </remarks>
        UInt32 GetMeanAbsoluteDifference() const
        {
            return GetUINT32OrDefault(MFSampleExtension_MeanAbsoluteDifference);
        }
        /// <summary>
        /// Retrieves the offsets to the payload boundaries in a frame for protected samples.
        /// </summary>
        /// <remarks>
        /// This attribute applies to media samples protected by Windows Media Digital Rights 
        /// Management (DRM). The value of the attribute is an array of DWORDs. Each entry in 
        /// the array is the offset of a payload boundary, relative to the start of the frame. 
        /// An application can use these values when decrypting and reconstructing the frames.
        /// </remarks>
        MF::PacketCrossOffsets GetPacketCrossOffsets() const
        {
            UINT32 blobSize = 0;
            if (GetBlobSize(MFSampleExtension_PacketCrossOffsets, &blobSize))
            {
                MF::PacketCrossOffsets result(static_cast<size_t>(blobSize));
                GetBlob(MFSampleExtension_PacketCrossOffsets, reinterpret_cast<UINT8*>(result.data()), blobSize);
                return result;
            }
            else
            {
                return MF::PacketCrossOffsets();
            }
        }
        /// <summary>
        /// Sets the offsets to the payload boundaries in a frame for protected samples.
        /// </summary>
        /// <remarks>
        /// This attribute applies to media samples protected by Windows Media Digital Rights 
        /// Management (DRM). The value of the attribute is an array of DWORDs. Each entry in 
        /// the array is the offset of a payload boundary, relative to the start of the frame. 
        /// An application can use these values when decrypting and reconstructing the frames.
        /// </remarks>
        void SetPacketCrossOffsets(const MF::PacketCrossOffsets& value)
        {
            SetBlob(MFSampleExtension_PacketCrossOffsets, reinterpret_cast<const UINT8*>(value.data()), static_cast<UINT32>(value.DataSize()));
        }
        void SetPacketCrossOffsets(const DWORD* values, size_t numberOfValues)
        {
            SetBlob(MFSampleExtension_PacketCrossOffsets, reinterpret_cast<const UINT8*>(values), static_cast<UINT32>(numberOfValues));
        }

    };


    class MF2DBuffer : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MF2DBuffer, Unknown, IMF2DBuffer, IUnknown)
    public:
        void Lock2D(BYTE** scanline0, LONG* pitch) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Lock2D(scanline0, pitch);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Unlock2D( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Unlock2D( );
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        struct Scanline0AndPitch
        {
            BYTE* Scanline0; 
            LONG Pitch;
        };

        void GetScanline0AndPitch( BYTE** scanline0, LONG* pitch) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetScanline0AndPitch(scanline0, pitch);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        Scanline0AndPitch GetScanline0AndPitch() const
        {
            Scanline0AndPitch result{};
            GetScanline0AndPitch(&result.Scanline0, &result.Pitch);
            return result;
        }


        void IsContiguousFormat( BOOL* isContiguous) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->IsContiguousFormat(isContiguous);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        bool IsContiguousFormat( ) const
        {
            BOOL result = FALSE;
            IsContiguousFormat(&result);
            return result != FALSE;
        }

        void GetContiguousLength( DWORD* length) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetContiguousLength(length);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        DWORD GetContiguousLength() const
        {
            DWORD result = 0;
            GetContiguousLength(&result);
            return result;
        }

        void ContiguousCopyTo( BYTE* destinationBuffer, DWORD destinationBufferSize) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->ContiguousCopyTo(destinationBuffer, destinationBufferSize);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void ContiguousCopyFrom( const BYTE* sourceBufferBuffer, DWORD sourceBufferBufferSize) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->ContiguousCopyFrom(sourceBufferBuffer, sourceBufferBufferSize);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

    };

    class MF2DBuffer2 : public MF2DBuffer
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MF2DBuffer2, MF2DBuffer, IMF2DBuffer2, IMF2DBuffer)
    public:
        void Lock2DSize( MF2DBuffer_LockFlags lockFlags, BYTE** scanline0, LONG* pitch, BYTE** bufferStart, DWORD* bufferLength) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Lock2DSize(lockFlags, scanline0, pitch, bufferStart, bufferLength);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Copy2DTo(IMF2DBuffer2* destinationBuffer) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Copy2DTo(destinationBuffer);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        void Copy2DTo(const MF2DBuffer2& destinationBuffer) const
        {
            Copy2DTo(destinationBuffer.GetInterfacePointer<IMF2DBuffer2>());
        }

    };


    class MFDXGIBuffer : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFDXGIBuffer, Unknown, IMFDXGIBuffer, IUnknown)
    public:
        void GetResource(const Guid& riid, LPVOID* ppvObject) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetResource(riid, ppvObject);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        template<typename T>
            requires std::is_base_of_v<Unknown,T>
        T GetResource() const
        {
            using ItfT = typename T::InterfaceType;
            ItfT* itf = nullptr;
            const Guid riid = __uuidof(ItfT);
            GetResource(riid, (void**)&itf);
            return T(itf);
        }

        template<typename T>
            requires std::is_base_of_v<IUnknown, T>
        void GetResource(T** result) const
        {
            const Guid riid = __uuidof(T);
            GetResource(riid, (void**)&result);
        }



        void GetSubresourceIndex(UINT* subresource) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetSubresourceIndex(subresource);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        UINT GetSubresourceIndex() const
        {
            UINT result = 0;
            GetSubresourceIndex(&result);
            return result;
        }


        void GetUnknown( const Guid& guid, const Guid& riid, LPVOID* result) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetUnknown(guid, riid, result);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetUnknown(const Guid& guid, IUnknown* unknown) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetUnknown(guid, unknown);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class MFMediaType : public MFAttributes
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFMediaType, MFAttributes, IMFMediaType, IMFAttributes)
    public:
        static MFMediaType Create()
        {
            IMFMediaType* itf = nullptr;
            auto hr = MFCreateMediaType(&itf);
            HCC_COM_CHECK_HRESULT(hr);
            return MFMediaType(itf);
        }
        static MFMediaType Clone(const MFMediaType& source)
        {
            auto result = Create();
            source.CopyAllItems(result);
            return result;
        }


        void GetMajorType(Guid* majorType) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetMajorType((GUID*)majorType);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        Guid GetMajorType() const
        {
            Guid result;
            GetMajorType(&result);
            return result;
        }


        //Guid GetMajorType() const
        //{
        //    return GetGUID(MF_MT_MAJOR_TYPE);
        //}

        void SetMajorType(const Guid& value) const
        {
            SetGUID(MF_MT_MAJOR_TYPE, value);
        }

        Guid GetSubType() const
        {
            return GetGUID(MF_MT_SUBTYPE);
        }

        void SetSubType(const Guid& value) const
        {
            SetGUID(MF_MT_SUBTYPE, value);
        }

        void SetFrameRate(UINT32 numerator, UINT32 denominator = 1) const
        {
            InterfaceType* pInterface = GetInterface();
            auto hr = MFSetAttributeRatio(pInterface, MF_MT_FRAME_RATE, numerator, denominator);
            HCC_COM_CHECK_HRESULT(hr);
        }
        void GetFrameRate(UINT32* numerator, UINT32* denominator) const
        {
            InterfaceType* pInterface = GetInterface();
            auto hr = MFGetAttributeRatio(pInterface, MF_MT_FRAME_RATE, numerator, denominator);
            HCC_COM_CHECK_HRESULT(hr);
        }


        void SetFrameSize(UINT32 width, UINT32 height) const
        {
            InterfaceType* pInterface = GetInterface();
            auto hr = MFSetAttributeSize(pInterface, MF_MT_FRAME_SIZE, width, height);
            HCC_COM_CHECK_HRESULT(hr);
        }
        void GetFrameSize(UINT32* width, UINT32* height) const
        {
            InterfaceType* pInterface = GetInterface();
            auto hr = MFGetAttributeSize(pInterface, MF_MT_FRAME_SIZE, width, height);
            HCC_COM_CHECK_HRESULT(hr);
        }

        void SetAverageBitRate(UINT32 bitsPerSecond) const
        {
            SetUINT32(MF_MT_AVG_BITRATE, bitsPerSecond);
        }
        UINT32 GetAverageBitRate() const
        {
            return GetUINT32(MF_MT_AVG_BITRATE);
        }

        void SetInterlaceMode(MFVideoInterlaceMode videoInterlaceMode) const
        {
            SetUINT32(MF_MT_INTERLACE_MODE, static_cast<UINT32>(videoInterlaceMode));
        }
        MFVideoInterlaceMode GetInterlaceMode() const
        {
            return static_cast<MFVideoInterlaceMode>( GetUINT32(MF_MT_INTERLACE_MODE) );
        }

        void SetMPEG2Profile(eAVEncH264VProfile profile) const
        {
            SetUINT32(MF_MT_MPEG2_PROFILE, static_cast<UINT32>(profile));
        }
        void SetMPEG2Profile(AM_MPEG2Profile profile) const
        {
            SetUINT32(MF_MT_MPEG2_PROFILE, static_cast<UINT32>(profile));
        }

        template<typename T>
            requires (std::is_same_v<T, eAVEncH264VProfile> || std::is_same_v<T, AM_MPEG2Profile>)
        T GetMPEG2Profile() const
        {
            return static_cast<T>(GetUINT32(MF_MT_MPEG2_PROFILE));
        }



        void IsCompressedFormat(BOOL* compressed) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->IsCompressedFormat(compressed);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        bool IsCompressedFormat() const
        {
            BOOL result = FALSE;
            IsCompressedFormat(&result);
            return result != FALSE;
        }

        bool IsEqual( IMFMediaType* mediaType, DWORD* flags) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->IsEqual(mediaType, flags);
            if (hr != S_OK && hr != S_FALSE)
            {
                HCC_COM_CHECK_HRESULT2(hr, pInterface);
            }
            return hr == S_OK;
        }
        bool IsEqual(const MFMediaType& mediaType, DWORD* flags) const
        {
            return IsEqual(mediaType.GetInterfacePointer<IMFMediaType>(), flags);
        }

        void GetRepresentation(GUID guidRepresentation, LPVOID* representation) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetRepresentation(guidRepresentation, representation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void FreeRepresentation(GUID guidRepresentation, LPVOID representation) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->FreeRepresentation(guidRepresentation, representation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }


        

    };


    class MFAudioMediaType : public MFMediaType
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFAudioMediaType, MFMediaType, IMFAudioMediaType, IMFMediaType)
    public:
        const WAVEFORMATEX* GetAudioFormat() const
        {
            InterfaceType* pInterface = GetInterface();
            return pInterface->GetAudioFormat();
        }
    };

    class MFVideoMediaType : public MFMediaType
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFVideoMediaType, MFMediaType, IMFVideoMediaType, IMFMediaType)
    public:
        const MFVIDEOFORMAT* GetVideoFormat() const
        {
            InterfaceType* pInterface = GetInterface();
            return pInterface->GetVideoFormat();
        }

        void GetVideoRepresentation(const Guid& guidRepresentation, LPVOID* representation, LONG stride) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetVideoRepresentation(guidRepresentation, representation, stride);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFAsyncResult;
    class MFAsyncCallback : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFAsyncCallback, Unknown, IMFAsyncCallback, IUnknown)
    public:
        void GetParameters(DWORD* flags, DWORD* queue) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetParameters(flags, queue);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Invoke(IMFAsyncResult* asyncResult) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Invoke(asyncResult);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        void Invoke(const MFAsyncResult& asyncResult) const;
    };
    

    class MFAsyncResult : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFAsyncResult, Unknown, IMFAsyncResult, IUnknown)
    public:
        static MFAsyncResult Create(IUnknown* punkObject, IMFAsyncCallback* pCallback, IUnknown* punkState)
        {
            IMFAsyncResult* itf = nullptr;
            HRESULT hr = MFCreateAsyncResult(punkObject, pCallback, punkState,&itf);
            HCC_COM_CHECK_HRESULT(hr);
            return MFAsyncResult(itf);
        }
        void GetState(IUnknown** ppunkState) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetState(ppunkState);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        HRESULT GetStatus( ) const
        {
            InterfaceType* pInterface = GetInterface();
            return pInterface->GetStatus( );
        }

        void SetStatus(HRESULT hrStatus) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetStatus(hrStatus);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetObject(IUnknown** ppObject) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetObject(ppObject);
            if (hr != E_POINTER)
            {
                HCC_COM_CHECK_HRESULT2(hr, pInterface);
            }
        }
        Unknown GetObject() const
        {
            IUnknown* itf = nullptr;
            GetObject(&itf);
            return Unknown(itf);
        }

        IUnknown* GetStateNoAddRef( ) const
        {
            InterfaceType* pInterface = GetInterface();
            return pInterface->GetStateNoAddRef();
        }
    };
    inline void MFAsyncCallback::Invoke(const MFAsyncResult& asyncResult) const
    {
        Invoke(asyncResult.GetInterfacePointer<IMFAsyncResult>());
    }


    class MFAsyncCallbackLogging : public MFAsyncCallback
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFAsyncCallbackLogging, MFAsyncCallback, IMFAsyncCallbackLogging, IMFAsyncCallback)
    public:
        void* GetObjectPointer() const
        {
            InterfaceType* pInterface = GetInterface();
            return pInterface->GetObjectPointer();
        }

        DWORD GetObjectTag( ) const
        {
            InterfaceType* pInterface = GetInterface();
            return pInterface->GetObjectTag();
        }
    };

    class MFMediaEvent : public MFAttributes
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFMediaEvent, MFAttributes, IMFMediaEvent, IMFAttributes)
    public:
        void GetType(MediaEventType* mediaEventType) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetType(mediaEventType);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        [[nodiscard]]
        MediaEventType GetType() const
        {
            MediaEventType result{};
            GetType(&result);
            return result;
        }


        void GetExtendedType(Guid* guidExtendedType) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetExtendedType((GUID*)guidExtendedType);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        Guid GetExtendedType() const
        {
            Guid result;
            GetExtendedType(&result);
            return result;
        }

        void GetStatus( HRESULT* status) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetStatus(status);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        HRESULT GetStatus() const
        {
            HRESULT result = 0;
            GetStatus(&result);
            return result;
        }

        void GetValue(PROPVARIANT* value) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetValue(value);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        PropertyVariant GetValue() const
        {
            PropertyVariant result;
            GetValue(&result);
            return result;
        }
    };

    class MFMediaEventGenerator : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFMediaEventGenerator, Unknown, IMFMediaEventGenerator, IUnknown)
    public:
        void GetEvent(DWORD flags, IMFMediaEvent** event) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetEvent(flags, event);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        MFMediaEvent GetEvent(DWORD flags) const
        {
            IMFMediaEvent* itf = nullptr;
            GetEvent(flags, &itf);
            return MFMediaEvent(itf);
        }

        void BeginGetEvent(IMFAsyncCallback* callback, IUnknown* unkState = nullptr) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->BeginGetEvent(callback, unkState);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        void BeginGetEvent(const MFAsyncCallback& callback, const Unknown& unkState) const
        {
            BeginGetEvent(callback.GetInterfacePointer<IMFAsyncCallback>(), unkState.GetInterfacePointer<IUnknown>());
        }

        void EndGetEvent(IMFAsyncResult* result, IMFMediaEvent** event) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->EndGetEvent(result, event);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        MFMediaEvent EndGetEvent(IMFAsyncResult* result) const
        {
            IMFMediaEvent* itf = nullptr;
            EndGetEvent(result, &itf);
            return MFMediaEvent(itf);
        }
        MFMediaEvent EndGetEvent(const MFAsyncResult& result) const
        {
            return EndGetEvent(result.GetInterfacePointer<IMFAsyncResult>());
        }

        void QueueEvent(MediaEventType mediaEventType, const Guid& guidExtendedType, HRESULT status, const PROPVARIANT* value) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->QueueEvent(mediaEventType, guidExtendedType, status, value);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class MFRemoteAsyncCallback : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFRemoteAsyncCallback, Unknown, IMFRemoteAsyncCallback, IUnknown)
    public:
        void Invoke(HRESULT hResult, IUnknown* remoteResult) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Invoke(hResult, remoteResult);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class MFByteStream : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFByteStream, Unknown, IMFByteStream, IUnknown)
    public:
        static MFByteStream Create(IStream* stream)
        {
            IMFByteStream* itf = nullptr;
            auto hr = MFCreateMFByteStreamOnStream(stream, &itf);
            HCC_COM_CHECK_HRESULT(hr);
            return MFByteStream(itf);
        }



        void GetCapabilities( DWORD* capabilities) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetCapabilities(capabilities);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        DWORD GetCapabilities() const
        {
            DWORD result = 0;
            GetCapabilities(&result);
            return result;
        }

        void GetLength( QWORD* length) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetLength(length);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        QWORD GetLength() const
        {
            QWORD result = 0;
            GetLength(&result);
            return result;
        }

        void SetLength( QWORD length) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetLength(length);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetCurrentPosition( QWORD* position) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetCurrentPosition(position);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        QWORD GetCurrentPosition() const
        {
            QWORD result = 0;
            GetCurrentPosition(&result);
            return result;
        }

        void SetCurrentPosition( QWORD position) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetCurrentPosition(position);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void IsEndOfStream( BOOL* endOfStream) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->IsEndOfStream(endOfStream);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        bool IsEndOfStream() const
        {
            BOOL result = FALSE;
            IsEndOfStream(&result);
            return result != FALSE;
        }

        void Read( BYTE* buffer, ULONG bufferSize, ULONG* numberOfBytesRead) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Read(buffer, bufferSize, numberOfBytesRead);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void BeginRead( BYTE* buffer, ULONG bufferSize, IMFAsyncCallback* callback, IUnknown* unkState = nullptr) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->BeginRead(buffer, bufferSize, callback, unkState);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        void BeginRead(BYTE* buffer, ULONG bufferSize, const MFAsyncCallback& callback, IUnknown* unkState = nullptr) const
        {
            BeginRead(buffer, bufferSize, callback.GetInterfacePointer<IMFAsyncCallback>(), unkState);
        }

        void EndRead( IMFAsyncResult* result, ULONG* numberOfBytesRead) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->EndRead(result, numberOfBytesRead);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        void EndRead(const MFAsyncResult& result, ULONG* numberOfBytesRead) const
        {
            EndRead(result.GetInterfacePointer<IMFAsyncResult>(), numberOfBytesRead);
        }

        void Write( const BYTE* buffer, ULONG bufferSize, ULONG* numberOfBytesWritten) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Write(buffer, bufferSize, numberOfBytesWritten);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void BeginWrite( const BYTE* buffer, ULONG bufferSize, IMFAsyncCallback* callback, IUnknown* unkState = nullptr) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->BeginWrite(buffer, bufferSize, callback, unkState);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        void BeginWrite(const BYTE* buffer, ULONG bufferSize, const MFAsyncCallback& callback, IUnknown* unkState = nullptr) const
        {
            BeginWrite(buffer, bufferSize, callback.GetInterfacePointer<IMFAsyncCallback>(), unkState);
        }

        void EndWrite( IMFAsyncResult* result, ULONG* numberOfBytesWritten) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->EndWrite(result, numberOfBytesWritten);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        void EndWrite(const MFAsyncResult& result, ULONG* numberOfBytesWritten) const
        {
            EndWrite(result.GetInterfacePointer<IMFAsyncResult>(), numberOfBytesWritten);
        }

        void Seek(MFBYTESTREAM_SEEK_ORIGIN seekOrigin, LONGLONG seekOffset, DWORD seekFlags, QWORD* currentPosition) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Seek(seekOrigin, seekOffset, seekFlags, currentPosition);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        QWORD Seek(MFBYTESTREAM_SEEK_ORIGIN seekOrigin, LONGLONG seekOffset, DWORD seekFlags) const
        {
            QWORD result = 0;
            Seek(seekOrigin, seekOffset, seekFlags, &result);
            return result;
        }

        void Flush( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Flush();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Close( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Close();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class MFByteStreamProxyClassFactory : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFByteStreamProxyClassFactory, Unknown, IMFByteStreamProxyClassFactory, IUnknown)
    public:
        void CreateByteStreamProxy( IMFByteStream* byteStream, IMFAttributes* attributes, REFIID riid, LPVOID* result) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateByteStreamProxy(byteStream, attributes, riid, result);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFSampleOutputStream : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFSampleOutputStream, Unknown, IMFSampleOutputStream, IUnknown)
    public:
        void BeginWriteSample(IMFSample* sample, IMFAsyncCallback* callback, IUnknown* unkState = nullptr) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->BeginWriteSample(sample, callback, unkState);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        void BeginWriteSample(const MFSample& sample, const MFAsyncCallback& callback, IUnknown* unkState = nullptr) const
        {
            BeginWriteSample(sample.GetInterfacePointer<IMFSample>(), callback.GetInterfacePointer<IMFAsyncCallback>(), unkState);
        }


        void EndWriteSample(IMFAsyncResult* result) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->EndWriteSample(result);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        void EndWriteSample(const MFAsyncResult& result) const
        {
            EndWriteSample(result.GetInterfacePointer<IMFAsyncResult>());
        }

        void Close() const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Close();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFCollection : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFCollection, Unknown, IMFCollection, IUnknown)
    public:
        void GetElementCount( DWORD* count) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetElementCount(count);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        DWORD GetElementCount() const
        {
            DWORD result = 0;
            GetElementCount(&result);
            return result;
        }

        void GetElement( DWORD index, IUnknown** element) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetElement(index, element);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        Unknown GetElement(DWORD index) const
        {
            IUnknown* itf = nullptr;
            GetElement(index, &itf);
            return Unknown(itf);
        }

        void AddElement( IUnknown* element) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->AddElement(element);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        void AddElement(const Unknown& element) const
        {
            AddElement(element.GetInterfacePointer<IUnknown>());
        }

        void RemoveElement( DWORD index, IUnknown** element) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->RemoveElement(index, element);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        Unknown RemoveElement(DWORD index) const
        {
            IUnknown* itf = nullptr;
            RemoveElement(index, &itf);
            return Unknown(itf);
        }


        void InsertElementAt( DWORD index, IUnknown* element) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->InsertElementAt(index, element);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        void InsertElementAt(DWORD index, const Unknown& element) const
        {
            InsertElementAt(index, element.GetInterfacePointer<IUnknown>());
        }

        void RemoveAllElements( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->RemoveAllElements();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    template<typename T>
    class MFCollectionT : public MFCollection
    {
    public:
        using Base = MFCollection;
        using Base::Base;

        size_t size() const
        {
            return static_cast<size_t>( GetElementCount() );
        }

        T operator[](size_t index) const
        {
            auto element = GetElement(static_cast<DWORD>(index));
            if (element != nullptr)
            {
                return element.As<T>();
            }
            return T();
        }
    };

    inline MFCollectionT<MFSample> MFSample::GetForwardedDecodeUnits() const
    {
        auto unk = GetUnknown<MFCollectionT<MFSample>>(MFSampleExtension_ForwardedDecodeUnits);
    }



    class MFMediaEventQueue : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFMediaEventQueue, Unknown, IMFMediaEventQueue, IUnknown)
    public:

        void GetEvent( DWORD flags, IMFMediaEvent** event) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetEvent(flags, event);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void BeginGetEvent( IMFAsyncCallback* callback, IUnknown* unkState) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->BeginGetEvent(callback, unkState);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void EndGetEvent( IMFAsyncResult* result, IMFMediaEvent** event) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->EndGetEvent(result, event);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void QueueEvent( IMFMediaEvent* event) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->QueueEvent(event);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void QueueEventParamVar( MediaEventType mediaEventType, const Guid& guidExtendedType, HRESULT status, const PROPVARIANT* value) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->QueueEventParamVar(mediaEventType, guidExtendedType, status, value);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void QueueEventParamUnk( MediaEventType mediaEventType, const Guid& guidExtendedType, HRESULT status, IUnknown* unknown) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->QueueEventParamUnk(mediaEventType, guidExtendedType, status, unknown);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Shutdown( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Shutdown( );
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

    };

    class MFActivate : public MFAttributes
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFActivate, MFAttributes, IMFActivate, IMFAttributes)
    public:
        static MFActivate CreateAudioRendererActivate()
        {
            IMFActivate* itf = nullptr;
            auto hr = MFCreateAudioRendererActivate(&itf);
            HCC_COM_CHECK_HRESULT( hr );
            return MFActivate(itf);
        }

        static MFActivate CreateVideoRendererActivate(HWND videoDisplayWindowHandle)
        {
            IMFActivate* itf = nullptr;
            auto hr = MFCreateVideoRendererActivate(videoDisplayWindowHandle,&itf);
            HCC_COM_CHECK_HRESULT(hr);
            return MFActivate(itf);
        }

        static MFActivate CreateAudioRendererActivate(IMFAttributes* attributes)
        {
            IMFActivate* itf = nullptr;
            auto hr = MFCreateDeviceSourceActivate(attributes, &itf);
            HCC_COM_CHECK_HRESULT(hr);
            return MFActivate(itf);
        }
        static MFActivate CreateTransformActivate()
        {
            IMFActivate* itf = nullptr;
            auto hr = MFCreateTransformActivate(&itf);
            HCC_COM_CHECK_HRESULT(hr);
            return MFActivate(itf);
        }



        void ActivateObject( const Guid& riid, void** result) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->ActivateObject(riid, result);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }


        template<typename T>
            requires std::is_base_of_v<Unknown, T>
        T ActivateObject( ) const
        {
            using ItfT = typename T::InterfaceType;
            ItfT* itf = nullptr;
            InterfaceType* pInterface = GetInterface();
            ActivateObject(__uuidof(ItfT), (void**)&itf);
            return T(itf);
        }


        void ShutdownObject( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->ShutdownObject( );
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void DetachObject( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->DetachObject();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }



    };

    class MFPluginControl : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFPluginControl, Unknown, IMFPluginControl, IUnknown)
    public:
        void GetPreferredClsid( DWORD pluginType, LPCWSTR selector, Guid* clsid) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetPreferredClsid(pluginType, selector, (GUID*)clsid);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetPreferredClsidByIndex( DWORD pluginType, DWORD index, LPWSTR* selector, Guid* clsid) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetPreferredClsidByIndex(pluginType, index, selector, (GUID*)clsid);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetPreferredClsid( DWORD pluginType, LPCWSTR selector, const Guid* clsid) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetPreferredClsid(pluginType, selector, (const GUID*) clsid);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void IsDisabled( DWORD pluginType, const Guid& clsid) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->IsDisabled(pluginType, clsid);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetDisabledByIndex( DWORD pluginType, DWORD index, Guid* clsid) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetDisabledByIndex(pluginType, index, (GUID*)clsid);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetDisabled( DWORD pluginType, const Guid& clsid, bool disabled) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetDisabled(pluginType, clsid, disabled);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFPluginControl2 : public MFPluginControl
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFPluginControl2, MFPluginControl, IMFPluginControl2, IMFPluginControl)
    public:
        void SetPolicy(MF_PLUGIN_CONTROL_POLICY policy) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetPolicy(policy);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFDXGIDeviceManager : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFDXGIDeviceManager, Unknown, IMFDXGIDeviceManager, IUnknown)
    public:
        void CloseDeviceHandle(HANDLE hDevice) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CloseDeviceHandle(hDevice);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetVideoService( HANDLE hDevice, const Guid& riid, void** ppService) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetVideoService(hDevice, riid, ppService);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void LockDevice( HANDLE hDevice, const Guid& riid, void** unkDevice, BOOL fBlock) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->LockDevice(hDevice, riid, unkDevice, fBlock);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void OpenDeviceHandle( HANDLE* phDevice) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->OpenDeviceHandle(phDevice);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void ResetDevice( IUnknown* unkDevice, UINT resetToken) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->ResetDevice(unkDevice, resetToken);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void TestDevice( HANDLE hDevice) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->TestDevice(hDevice);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void UnlockDevice( HANDLE hDevice, BOOL fSaveState) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->UnlockDevice(hDevice, fSaveState);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

    };


    class MFMuxStreamAttributesManager : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFMuxStreamAttributesManager, Unknown, IMFMuxStreamAttributesManager, IUnknown)
    public:
        void GetStreamCount(DWORD* muxStreamCount) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetStreamCount(muxStreamCount);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        DWORD GetStreamCount( ) const
        {
            DWORD result = 0;
            GetStreamCount(&result);
            return result;
        }

        void GetAttributes(DWORD muxStreamIndex, IMFAttributes** streamAttributes) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetAttributes(muxStreamIndex, streamAttributes);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        MFAttributes GetAttributes(DWORD muxStreamIndex) const
        {
            IMFAttributes* itf = nullptr;
            GetAttributes(muxStreamIndex,&itf);
            return MFAttributes(itf);
        }

    };

    class MFMuxStreamMediaTypeManager : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFMuxStreamMediaTypeManager, Unknown, IMFMuxStreamMediaTypeManager, IUnknown)
    public:
        void GetStreamCount( DWORD* muxStreamCount) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetStreamCount(muxStreamCount);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        DWORD GetStreamCount( ) const
        {
            DWORD result = 0;
            GetStreamCount(&result);
            return result;
        }

        void GetMediaType( DWORD muxStreamIndex, IMFMediaType** mediaType) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetMediaType(muxStreamIndex, mediaType);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        MFMediaType GetMediaType(DWORD muxStreamIndex) const
        {
            IMFMediaType* itf = nullptr;
            GetMediaType(muxStreamIndex, &itf);
            return MFMediaType(itf);
        }

        void GetStreamConfigurationCount( DWORD* count) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetStreamConfigurationCount(count);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        DWORD GetStreamConfigurationCount() const
        {
            DWORD result = 0;
            GetStreamConfigurationCount(&result);
            return result;
        }

        void AddStreamConfiguration( ULONGLONG streamMask) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->AddStreamConfiguration(streamMask);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void RemoveStreamConfiguration( ULONGLONG streamMask) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->RemoveStreamConfiguration(streamMask);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetStreamConfiguration( DWORD index, ULONGLONG* streamMask) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetStreamConfiguration(index, streamMask);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        ULONGLONG GetStreamConfiguration(DWORD index) const
        {
            ULONGLONG result = 0;
            GetStreamConfiguration(index, &result);
            return result;
        }

    };

    class MFMuxStreamSampleManager : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFMuxStreamSampleManager, Unknown, IMFMuxStreamSampleManager, IUnknown)
    public:
        void GetStreamCount(DWORD* muxStreamCount) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetStreamCount(muxStreamCount);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        DWORD GetStreamCount() const
        {
            DWORD result = 0;
            GetStreamCount(&result);
            return result;
        }

        void GetSample( DWORD muxStreamIndex, IMFSample** ppSample) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetSample(muxStreamIndex, ppSample);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        MFSample GetSample(DWORD muxStreamIndex) const
        {
            IMFSample* itf = nullptr;
            GetSample(muxStreamIndex, &itf);
            return MFSample(itf);
        }

        ULONGLONG GetStreamConfiguration( ) const
        {
            InterfaceType* pInterface = GetInterface();
            return pInterface->GetStreamConfiguration( );
        }
    };


    class MFSecureBuffer : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFSecureBuffer, Unknown, IMFSecureBuffer, IUnknown)
    public:
        void GetIdentifier(Guid* identifier) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetIdentifier((GUID *) identifier);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        Guid GetIdentifier( ) const
        {
            Guid result;
            GetIdentifier(&result);
            return result;
        }

    };


}

#endif
