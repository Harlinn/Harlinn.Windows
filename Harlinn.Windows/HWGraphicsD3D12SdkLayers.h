#pragma once
#ifndef HARLINN_WINDOWS_HWGRAPHICSD3D12SDKLAYERS_H_
#define HARLINN_WINDOWS_HWGRAPHICSD3D12SDKLAYERS_H_

#include "HWGraphicsD3D12.h"

namespace Harlinn::Windows::Graphics
{
    class D3D12Debug : public Unknown
    {
    public:
        using Base = Unknown;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12Debug, Unknown, ID3D12Debug, IUnknown )

    public:
        void EnableDebugLayer( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->EnableDebugLayer( );
        }
    };


    class D3D12Debug1 : public Unknown
    {
    public:
        using Base = Unknown;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12Debug1, Unknown, ID3D12Debug1, IUnknown )

    public:
        void EnableDebugLayer( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->EnableDebugLayer( );
        }

        void SetEnableGPUBasedValidation( bool enable  ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetEnableGPUBasedValidation( enable );
        }

        void SetEnableSynchronizedCommandQueueValidation( bool enable ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetEnableSynchronizedCommandQueueValidation( enable );
        }
    };

    class D3D12Debug2 : public Unknown
    {
    public:
        using Base = Unknown;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12Debug2, Unknown, ID3D12Debug2, IUnknown )

    public:
        void SetGPUBasedValidationFlags( D3D12_GPU_BASED_VALIDATION_FLAGS flags ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetGPUBasedValidationFlags( flags );
        }
    };

    class D3D12Debug3 : public D3D12Debug
    {
    public:
        using Base = D3D12Debug;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12Debug3, D3D12Debug, ID3D12Debug3, ID3D12Debug )

    public:
        void SetEnableGPUBasedValidation( bool enable )  const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetEnableGPUBasedValidation( enable );
        }

        void SetEnableSynchronizedCommandQueueValidation( bool enable ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetEnableSynchronizedCommandQueueValidation( enable );
        }

        void SetGPUBasedValidationFlags( D3D12_GPU_BASED_VALIDATION_FLAGS flags ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetGPUBasedValidationFlags( flags );
        }

    };

    class D3D12Debug4 : public D3D12Debug3
    {
    public:
        using Base = D3D12Debug3;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12Debug4, D3D12Debug3, ID3D12Debug4, ID3D12Debug3 )

    public:
        void DisableDebugLayer( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->DisableDebugLayer( );
        }
    };


    class D3D12Debug5 : public D3D12Debug4
    {
    public:
        using Base = D3D12Debug4;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12Debug5, D3D12Debug4, ID3D12Debug5, ID3D12Debug4 )

    public:
        void SetEnableAutoName( bool enable ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetEnableAutoName( enable );
        }
    };


    class D3D12Debug6 : public D3D12Debug5
    {
    public:
        using Base = D3D12Debug5;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12Debug6, D3D12Debug5, ID3D12Debug6, ID3D12Debug5 )

    public:
        void SetForceLegacyBarrierValidation( bool enable ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetForceLegacyBarrierValidation( enable );
        }
    };


    class D3D12DebugDevice1 : public Unknown
    {
    public:
        using Base = Unknown;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12DebugDevice1, Unknown, ID3D12DebugDevice1, IUnknown )

    public:
        void SetDebugParameter( D3D12_DEBUG_DEVICE_PARAMETER_TYPE type, _In_reads_bytes_( dataSize ) const void* data, UINT dataSize ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->SetDebugParameter( type, data, dataSize );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetDebugParameter( D3D12_DEBUG_DEVICE_PARAMETER_TYPE type, _Out_writes_bytes_( dataSize )  void* data, UINT dataSize ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetDebugParameter( type, data, dataSize );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void ReportLiveDeviceObjects( D3D12_RLDO_FLAGS flags ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->ReportLiveDeviceObjects( flags );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    class D3D12DebugDevice : public Unknown
    {
    public:
        using Base = Unknown;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12DebugDevice, Unknown, ID3D12DebugDevice, IUnknown )

    public:

        void SetFeatureMask( D3D12_DEBUG_FEATURE mask ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->SetFeatureMask( mask );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        D3D12_DEBUG_FEATURE GetFeatureMask( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetFeatureMask( );
        }

        void ReportLiveDeviceObjects( D3D12_RLDO_FLAGS flags ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->ReportLiveDeviceObjects( flags );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    class D3D12DebugDevice1 : public Unknown
    {
    public:
        using Base = Unknown;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12DebugDevice1, Unknown, ID3D12DebugDevice1, IUnknown )
    public:

        void SetDebugParameter( D3D12_DEBUG_DEVICE_PARAMETER_TYPE type, _In_reads_bytes_( dataSize )  const void* data, UINT dataSize ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->SetDebugParameter( type, data, dataSize );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetDebugParameter( D3D12_DEBUG_DEVICE_PARAMETER_TYPE type, _Out_writes_bytes_( dataSize )  void* data, UINT dataSize ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetDebugParameter( type, data, dataSize );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void ReportLiveDeviceObjects( D3D12_RLDO_FLAGS flags ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->ReportLiveDeviceObjects( flags );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

    };

    class D3D12DebugDevice2 : public D3D12DebugDevice
    {
    public:
        using Base = D3D12DebugDevice;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12DebugDevice2, D3D12DebugDevice, ID3D12DebugDevice2, ID3D12DebugDevice )
    public:

        void SetDebugParameter( D3D12_DEBUG_DEVICE_PARAMETER_TYPE type, _In_reads_bytes_( dataSize )  const void* data, UINT dataSize ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->SetDebugParameter( type, data, dataSize );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetDebugParameter( D3D12_DEBUG_DEVICE_PARAMETER_TYPE type, _Out_writes_bytes_( dataSize )  void* data, UINT dataSize ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetDebugParameter( type, data, dataSize );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };


    class D3D12DebugCommandQueue : public Unknown
    {
    public:
        using Base = Unknown;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12DebugCommandQueue, Unknown, ID3D12DebugCommandQueue, IUnknown )
    public:
        bool AssertResourceState( ID3D12Resource* resource, UINT subresource, UINT state ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->AssertResourceState( resource, subresource, state ) != FALSE;
        }

        bool AssertResourceState( const D3D12Resource& resource, UINT subresource, UINT state ) const
        {
            return AssertResourceState( resource.GetInterfacePointer<ID3D12Resource>( ), subresource, state );
        }
    };

    class D3D12DebugCommandList1 : public Unknown
    {
    public:
        using Base = Unknown;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12DebugCommandList1, Unknown, ID3D12DebugCommandList1, IUnknown )
    public:
        bool AssertResourceState( ID3D12Resource* resource, UINT subresource, UINT state ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->AssertResourceState( resource, subresource, state ) != FALSE;
        }

        bool AssertResourceState( const D3D12Resource& resource, UINT subresource, UINT state ) const
        {
            return AssertResourceState( resource.GetInterfacePointer<ID3D12Resource>( ), subresource, state );
        }

        void SetDebugParameter( D3D12_DEBUG_COMMAND_LIST_PARAMETER_TYPE type, _In_reads_bytes_( dataSize )  const void* data, UINT dataSize ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->SetDebugParameter( type, data, dataSize );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetDebugParameter( D3D12_DEBUG_COMMAND_LIST_PARAMETER_TYPE type, _Out_writes_bytes_( dataSize )  void* data, UINT dataSize ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetDebugParameter( type, data, dataSize );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };


    class D3D12DebugCommandList : public Unknown
    {
    public:
        using Base = Unknown;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12DebugCommandList, Unknown, ID3D12DebugCommandList, IUnknown )
    public:
        bool AssertResourceState( ID3D12Resource* resource, UINT subresource, UINT state ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->AssertResourceState( resource, subresource, state ) != FALSE;
        }

        bool AssertResourceState( const D3D12Resource& resource, UINT subresource, UINT state ) const
        {
            return AssertResourceState( resource.GetInterfacePointer<ID3D12Resource>( ), subresource, state );
        }

        void SetFeatureMask( D3D12_DEBUG_FEATURE mask ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->SetFeatureMask( mask );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        D3D12_DEBUG_FEATURE GetFeatureMask( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetFeatureMask( );
        }
    };


    class D3D12DebugCommandList2 : public D3D12DebugCommandList
    {
    public:
        using Base = D3D12DebugCommandList;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12DebugCommandList2, D3D12DebugCommandList, ID3D12DebugCommandList2, ID3D12DebugCommandList )
    public:
        void SetDebugParameter( D3D12_DEBUG_COMMAND_LIST_PARAMETER_TYPE type, _In_reads_bytes_( dataSize )  const void* data, UINT dataSize ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->SetDebugParameter( type, data, dataSize );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetDebugParameter( D3D12_DEBUG_COMMAND_LIST_PARAMETER_TYPE type, _Out_writes_bytes_( dataSize )  void* data, UINT dataSize ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetDebugParameter( type, data, dataSize );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };


    class D3D12SharingContract : public Unknown
    {
    public:
        using Base = Unknown;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12SharingContract, Unknown, ID3D12SharingContract, IUnknown )
    public:
        void Present( _In_ ID3D12Resource* resource, UINT subresource, _In_  HWND window ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->Present( resource, subresource, window );
        }

        void SharedFenceSignal( _In_ ID3D12Fence* fence, UINT64 fenceValue ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SharedFenceSignal( fence, fenceValue );
        }

        void BeginCapturableWork( _In_ REFGUID guid ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->BeginCapturableWork( guid );
        }

        void EndCapturableWork( _In_ REFGUID guid ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->EndCapturableWork( guid );
        }
        
    };

    class D3D12InfoQueue : public Unknown
    {
    public:
        using Base = Unknown;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12InfoQueue, Unknown, ID3D12InfoQueue, IUnknown )
    public:
        void SetMessageCountLimit( _In_  UINT64 messageCountLimit ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->SetMessageCountLimit( messageCountLimit );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void ClearStoredMessages( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->ClearStoredMessages( );
        }

        void GetMessage( _In_  UINT64 messageIndex, _Out_writes_bytes_opt_( *messageByteLength )  D3D12_MESSAGE* message, _Inout_  SIZE_T* messageByteLength ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetMessage( messageIndex, message, messageByteLength );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        UINT64 GetNumMessagesAllowedByStorageFilter( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetNumMessagesAllowedByStorageFilter( );
        }

        UINT64 GetNumMessagesDeniedByStorageFilter( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetNumMessagesDeniedByStorageFilter( );
        }

        UINT64 GetNumStoredMessages( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetNumStoredMessages( );
        }

        UINT64 GetNumStoredMessagesAllowedByRetrievalFilter( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetNumStoredMessagesAllowedByRetrievalFilter( );
        }

        UINT64 GetNumMessagesDiscardedByMessageCountLimit( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetNumMessagesDiscardedByMessageCountLimit( );
        }

        UINT64 GetMessageCountLimit( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetMessageCountLimit( );
        }

        void AddStorageFilterEntries( _In_  D3D12_INFO_QUEUE_FILTER* filter ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->AddStorageFilterEntries( filter );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetStorageFilter( _Out_writes_bytes_opt_( *filterByteLength )  D3D12_INFO_QUEUE_FILTER* filter, _Inout_  SIZE_T* filterByteLength ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetStorageFilter( filter, filterByteLength );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void ClearStorageFilter( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->ClearStorageFilter( );
        }

        void PushEmptyStorageFilter( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->PushEmptyStorageFilter( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void PushCopyOfStorageFilter( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->PushCopyOfStorageFilter( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void PushStorageFilter( _In_  D3D12_INFO_QUEUE_FILTER* filter ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->PushStorageFilter( filter );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void PopStorageFilter( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->PopStorageFilter( );
        }

        UINT GetStorageFilterStackSize( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetStorageFilterStackSize( );
        }

        void AddRetrievalFilterEntries( _In_  D3D12_INFO_QUEUE_FILTER* filter ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->AddRetrievalFilterEntries( filter );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetRetrievalFilter( _Out_writes_bytes_opt_( *filterByteLength )  D3D12_INFO_QUEUE_FILTER* filter, _Inout_  SIZE_T* filterByteLength ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetRetrievalFilter( filter, filterByteLength );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void ClearRetrievalFilter( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->ClearRetrievalFilter( );
        }

        void PushEmptyRetrievalFilter( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->PushEmptyRetrievalFilter( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void PushCopyOfRetrievalFilter( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->PushCopyOfRetrievalFilter( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void PushRetrievalFilter( _In_  D3D12_INFO_QUEUE_FILTER* filter ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->PushRetrievalFilter( filter );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void PopRetrievalFilter( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->PopRetrievalFilter( );
        }

        UINT GetRetrievalFilterStackSize( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetRetrievalFilterStackSize( );
        }

        void AddMessage( _In_  D3D12_MESSAGE_CATEGORY category, _In_  D3D12_MESSAGE_SEVERITY severity, _In_  D3D12_MESSAGE_ID id, _In_  LPCSTR description ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->AddMessage( category, severity, id, description );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void AddApplicationMessage( _In_  D3D12_MESSAGE_SEVERITY severity, _In_  LPCSTR description ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->AddApplicationMessage( severity, description );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetBreakOnCategory( _In_  D3D12_MESSAGE_CATEGORY category, _In_  bool enable = true ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->SetBreakOnCategory( category, enable );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetBreakOnSeverity( _In_  D3D12_MESSAGE_SEVERITY severity, _In_  bool enable = true ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->SetBreakOnSeverity( severity, enable );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetBreakOnID( _In_  D3D12_MESSAGE_ID id, _In_  bool enable = true ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->SetBreakOnID( id, enable );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        bool GetBreakOnCategory( _In_  D3D12_MESSAGE_CATEGORY category ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetBreakOnCategory( category ) != false; 
        }

        bool GetBreakOnSeverity( _In_  D3D12_MESSAGE_SEVERITY severity ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetBreakOnSeverity( severity ) != false;
        }

        bool GetBreakOnID( _In_  D3D12_MESSAGE_ID id ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetBreakOnID( id );
        }

        void SetMuteDebugOutput( _In_  bool mute = true ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetMuteDebugOutput( mute );
        }

        bool GetMuteDebugOutput( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetMuteDebugOutput( );
        }
    };


    class D3D12InfoQueue1 : public D3D12InfoQueue
    {
    public:
        using Base = D3D12InfoQueue;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12InfoQueue1, D3D12InfoQueue, ID3D12InfoQueue1, ID3D12InfoQueue )
    public:
        void RegisterMessageCallback( _In_  D3D12MessageFunc callbackFunc, _In_  D3D12_MESSAGE_CALLBACK_FLAGS callbackFilterFlags, _In_  void* context, _Inout_  DWORD* callbackCookie ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->RegisterMessageCallback( callbackFunc, callbackFilterFlags, context, callbackCookie );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void UnregisterMessageCallback( _In_  DWORD callbackCookie ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->UnregisterMessageCallback( callbackCookie );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

    };

}

#endif
