#pragma once
#ifndef __HWDXGI_H__
#define __HWDXGI_H__
/*
   Copyright 2024 Espen Harlinn

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

#include <HWDef.h>
#include <HCCCOM.h>
#include <HCCException.h>
#include <HWCommon.h>

#pragma comment(lib,"DXGI.lib")

#pragma pack(push,8)

namespace Harlinn::Windows::Graphics
{
    class DeviceContext;
}

namespace Harlinn::Windows::Graphics::D3D12
{
    class Resource;
    class CommandQueue;
}

namespace Harlinn::Windows::Graphics::DXGI
{
    class Object;
    class DeviceSubObject;
    class Resource;
    class KeyedMutex;
    class Surface;
    class Surface1;
    class Adapter;
    class Output;
    class SwapChain;
    class Factory;
    class Device;
    class Adapter1;
    class Factory1;
    class Device1;
    class DisplayControl;
    class OutputDuplication;
    class Surface2;
    class Resource1;
    class Device2;
    class SwapChain1;
    class Factory2;
    class Adapter2;
    class Output1;
    class Device3;
    class SwapChain2;
    class Output2;
    class Factory3;
    class DecodeSwapChain;
    class FactoryMedia;
    class SwapChainMedia;
    class Output3;
    class SwapChain3;
    class Output4;
    class Factory4;
    class Adapter3;
    class Output5;
    class SwapChain4;
    class Device4;
    class Factory5;
    class Adapter4;
    class Output6;
    class Factory6;
    class Factory7;


    /// <summary>
    /// Describes multi-sampling parameters for a resource.
    /// </summary>
    struct SampleDesc
    {
        /// <summary>
        /// The number of multisamples per pixel.
        /// </summary>
        UINT Count = 0;
        /// <summary>
        /// <para>
        /// The image quality level. The higher the quality, the lower the performance. The valid range is between 
        /// zero and one less than the level returned by ID3D10Device::CheckMultisampleQualityLevels for Direct3D 10 or 
        /// ID3D11Device::CheckMultisampleQualityLevels for Direct3D 11.
        /// </para>
        /// </summary>
        UINT Quality = 0;
    };


    /// <summary>
    /// This is the base class for all DXGI objects; DXGI::Object supports 
    /// associating caller-defined (private data) with an object and 
    /// retrieval of an interface to the parent object.
    /// </summary>
    class Object : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( Object, Unknown, IDXGIObject, IUnknown )
    public:
        void SetPrivateData( REFGUID name, UINT dataSize, const void* data ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->SetPrivateData( name, dataSize, data );
            CheckHRESULT( hr );
        }

        void SetPrivateDataInterface( REFGUID name, const IUnknown* pUnknown ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->SetPrivateDataInterface( name, pUnknown );
            CheckHRESULT( hr );
        }

        void GetPrivateData( REFGUID name, UINT* dataSize, void* data ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetPrivateData( name, dataSize, data );
            CheckHRESULT( hr );
        }

        bool GetParent( REFIID riid, void** ppParent ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetParent( riid, ppParent );
            if ( FAILED( hr ) && hr != E_NOINTERFACE )
            {
                CheckHRESULT( hr );
            }
            return hr != E_NOINTERFACE;
        }

        template <typename T>
            requires std::is_base_of_v<IUnknown,T>
        [[nodiscard]] UnknownPtr<T> GetParent() const
        { 
            T* parent = nullptr;
            if ( GetParent( __uuidof( T ), (void**)&parent ) )
            {
                return parent;
            }
            else
            {
                return nullptr;
            }
        }
        template <typename T>
            requires std::is_base_of_v<Object,T>
        [[nodiscard]] T GetParent() const
        { 
            using InterfaceType = typename T::InterfaceType;
            InterfaceType* parent = nullptr;
            if ( GetParent( __uuidof( InterfaceType ), (void**)&parent ) )
            {
                T result( parent );
                return result;
            }
            else
            {
                return T();
            }
        }


    };

    /// <summary>
    /// Base class for objects that are tied to the device 
    /// so that they can retrieve a pointer to it.
    /// </summary>
    class DeviceSubObject : public Object
    {
    public:
        typedef Object Base;

        HCC_COM_STANDARD_METHODS_IMPL( DeviceSubObject, Object, IDXGIDeviceSubObject, IDXGIObject )
    public:
        bool GetDevice( REFIID riid, void** ppDevice ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetDevice( riid, ppDevice );
            if ( FAILED( hr ) && hr != E_NOINTERFACE )
            {
                CheckHRESULT( hr );
            }
            return hr != E_NOINTERFACE;
        }
        template <typename T>
            requires std::is_base_of_v<IUnknown, T>
        [[nodiscard]] UnknownPtr<T> GetDevice( ) const
        {
            T* device = nullptr;
            if ( GetDevice( __uuidof( T ), (void**)&device ) )
            {
                return device;
            }
            else
            {
                return nullptr;
            }
        }
    };

    /// <summary>
    /// Allows resource sharing and identifies the memory that a resource resides in.
    /// </summary>
    class Resource : public DeviceSubObject
    {
    public:
        typedef DeviceSubObject Base;

        HCC_COM_STANDARD_METHODS_IMPL( Resource, DeviceSubObject, IDXGIResource, IDXGIDeviceSubObject )
    public:
        void GetSharedHandle( HANDLE* sharedHandle ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetSharedHandle( sharedHandle );
            CheckHRESULT( hr );
        }

        void GetUsage( DXGI_USAGE* usage ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetUsage( usage );
            CheckHRESULT( hr );
        }

        void SetEvictionPriority( UINT evictionPriority ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->SetEvictionPriority( evictionPriority );
            CheckHRESULT( hr );
        }

        void GetEvictionPriority( UINT* evictionPriority ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetEvictionPriority( evictionPriority );
            CheckHRESULT( hr );
        }
    };

    /// <summary>
    /// Represents a keyed mutex, which allows exclusive access to a shared resource that is used by multiple devices.
    /// </summary>
    class KeyedMutex : public DeviceSubObject
    {
    public:
        typedef DeviceSubObject Base;

        HCC_COM_STANDARD_METHODS_IMPL( KeyedMutex, DeviceSubObject, IDXGIKeyedMutex, IDXGIDeviceSubObject )

    public:
        bool AcquireSync( UINT64 Key, DWORD dwMilliseconds ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->AcquireSync( Key, dwMilliseconds );
            if ( hr != WAIT_TIMEOUT )
            {
                CheckHRESULT( hr );
            }
            return hr != WAIT_TIMEOUT;
        }

        void ReleaseSync(UINT64 Key ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->ReleaseSync( Key );
            CheckHRESULT( hr );
        }
    };

    /// <summary>
    /// Implements methods for image-data objects.
    /// </summary>
    class Surface : public DeviceSubObject
    {
    public:
        typedef DeviceSubObject Base;

        HCC_COM_STANDARD_METHODS_IMPL( Surface, Base, IDXGISurface, IDXGIDeviceSubObject )

    public:
        void GetDesc( DXGI_SURFACE_DESC* pDesc ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetDesc( pDesc );
            CheckHRESULT( hr );
        }

        void Map( DXGI_MAPPED_RECT* pLockedRect, UINT MapFlags ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->Map( pLockedRect, MapFlags );
            CheckHRESULT( hr );
        }

        void Unmap( void ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->Unmap( );
            CheckHRESULT( hr );
        }
    };

    /// <summary>
    /// The Surface1 class extends the Surface class by adding support for 
    /// using Windows Graphics Device Interface (GDI) to render to a 
    /// Microsoft DirectX Graphics Infrastructure (DXGI) surface.
    /// </summary>
    class Surface1 : public Surface
    {
    public:
        typedef Surface Base;

        HCC_COM_STANDARD_METHODS_IMPL( Surface1, Base, IDXGISurface1, IDXGISurface )

    public:
        void GetDC( BOOL Discard, HDC* phdc ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetDC( Discard, phdc );
            CheckHRESULT( hr );
        }

        void ReleaseDC(RECT* pDirtyRect ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->ReleaseDC( pDirtyRect );
            CheckHRESULT( hr );
        }
    };

    /// <summary>
    /// The Adapter class represents a display subsystem (including one or more GPUs, DACs and video memory).
    /// </summary>
    class Adapter : public Object
    {
    public:
        typedef Object Base;

        HCC_COM_STANDARD_METHODS_IMPL( Adapter, Base, IDXGIAdapter, IDXGIObject )

    public:
        void EnumOutputs( UINT Output, IDXGIOutput** ppOutput ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->EnumOutputs( Output, ppOutput );
            CheckHRESULT( hr );
        }

        void GetDesc( DXGI_ADAPTER_DESC* pDesc ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetDesc( pDesc );
            CheckHRESULT( hr );
        }

        void CheckInterfaceSupport( REFGUID InterfaceName, LARGE_INTEGER* pUMDVersion ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CheckInterfaceSupport( InterfaceName, pUMDVersion );
            CheckHRESULT( hr );
        }
    };

    /// <summary>
    /// An Output object represents an adapter output (such as a monitor).
    /// </summary>
    class Output : public Object
    {
    public:
        typedef Object Base;

        HCC_COM_STANDARD_METHODS_IMPL( Output, Base, IDXGIOutput, IDXGIObject )
    public:
        void GetDesc( DXGI_OUTPUT_DESC* pDesc ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetDesc( pDesc );
            CheckHRESULT( hr );
        }

        void GetDisplayModeList(DXGI_FORMAT EnumFormat, UINT Flags, UINT* pNumModes, DXGI_MODE_DESC* pDesc ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetDisplayModeList( EnumFormat, Flags, pNumModes, pDesc );
            CheckHRESULT( hr );
        }

        void FindClosestMatchingMode( const DXGI_MODE_DESC* pModeToMatch, DXGI_MODE_DESC* pClosestMatch, IUnknown* pConcernedDevice ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->FindClosestMatchingMode( pModeToMatch, pClosestMatch, pConcernedDevice );
            CheckHRESULT( hr );
        }

        void WaitForVBlank( void ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->WaitForVBlank( );
            CheckHRESULT( hr );
        }

        void TakeOwnership( IUnknown* pDevice, BOOL Exclusive ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->TakeOwnership( pDevice, Exclusive );
            CheckHRESULT( hr );
        }

        void ReleaseOwnership( void ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->ReleaseOwnership( );
        }

        void GetGammaControlCapabilities( DXGI_GAMMA_CONTROL_CAPABILITIES* pGammaCaps ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetGammaControlCapabilities( pGammaCaps );
            CheckHRESULT( hr );
        }

        void SetGammaControl( const DXGI_GAMMA_CONTROL* pArray ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->SetGammaControl( pArray );
            CheckHRESULT( hr );
        }

        void GetGammaControl( DXGI_GAMMA_CONTROL* pArray ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetGammaControl( pArray );
            CheckHRESULT( hr );
        }

        void SetDisplaySurface( IDXGISurface* pScanoutSurface ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->SetDisplaySurface( pScanoutSurface );
            CheckHRESULT( hr );
        }

        void GetDisplaySurfaceData( IDXGISurface* pDestination ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetDisplaySurfaceData( pDestination );
            CheckHRESULT( hr );
        }

        void GetFrameStatistics( DXGI_FRAME_STATISTICS* pStats ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetFrameStatistics( pStats );
            CheckHRESULT( hr );
        }
    };

    /// <summary>
    /// A SwapChain object implements one or more surfaces for storing 
    /// rendered data before presenting it to an output.
    /// </summary>
    class SwapChain : public DeviceSubObject
    {
    public:
        typedef DeviceSubObject Base;

        HCC_COM_STANDARD_METHODS_IMPL( SwapChain, Base, IDXGISwapChain, IDXGIDeviceSubObject )
    public:
        /// <summary>
        /// Presents a rendered image to the user.
        /// </summary>
        /// <param name="SyncInterval">
        /// <para>
        /// An integer that specifies how to synchronize presentation of a frame with the vertical blank.
        /// </para>
        /// <para>
        /// For the bit-block transfer (bitblt) model 
        /// (<see href="https://learn.microsoft.com/en-us/windows/win32/api/dxgi/ne-dxgi-dxgi_swap_effect">DXGI_SWAP_EFFECT_DISCARD</see> or 
        /// <see href="https://learn.microsoft.com/en-us/windows/win32/api/dxgi/ne-dxgi-dxgi_swap_effect">DXGI_SWAP_EFFECT_SEQUENTIAL</see>), values are:
        /// </para>
        /// <list type="bullet">
        /// <item>
        /// 0 - The presentation occurs immediately, there is no synchronization.
        /// </item>
        /// <item>
        /// 1 through 4 - Synchronize presentation after the nth vertical blank.
        /// </item>
        /// </list>
        /// <para>
        /// For the flip model (DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL), values are:
        /// </para>
        /// <list type="bullet">
        /// <item>
        /// 0 - Cancel the remaining time on the previously presented frame and discard this frame if a newer frame is queued.
        /// </item>
        /// <item>
        /// 1 through 4 - Synchronize presentation for at least n vertical blanks.
        /// </item>
        /// </list>
        /// <para>
        /// If the update region straddles more than one output (each represented by <see cref="Output">Output</see>), 
        /// Present performs the synchronization to the output that contains the largest 
        /// sub-rectangle of the target window's client area.
        /// </para>
        /// </param>
        /// <param name="Flags">
        /// An integer value that contains swap-chain presentation options. These options are defined by the 
        /// <see href="https://learn.microsoft.com/en-us/windows/desktop/direct3ddxgi/dxgi-present">DXGI_PRESENT</see> constants.
        /// </param>
        /// <remarks>
        /// <para>
        /// Starting with Direct3D 11.1, consider using <see cref="SwapChain1::Present1">SwapChain1::Present1</see> 
        /// because you can then use dirty rectangles and the scroll rectangle in the swap chain presentation 
        /// and as such use less memory bandwidth and as a result less system power. For more info about using 
        /// dirty rectangles and the scroll rectangle in swap chain presentation, see 
        /// <see href="https://learn.microsoft.com/en-us/windows/win32/direct3ddxgi/dxgi-1-2-presentation-improvements">Using dirty rectangles and the scroll rectangle in swap chain presentation</see>.
        /// </para>
        /// <para>
        /// For the best performance when flipping swap-chain buffers in a full-screen application, see 
        /// <see href="https://learn.microsoft.com/en-us/windows/win32/direct3ddxgi/d3d10-graphics-programming-guide-dxgi">Full-Screen Application Performance Hints</see>.
        /// </para>
        /// <para>
        /// Because calling Present might cause the render thread to wait on the message-pump 
        /// thread, be careful when calling this method in an application that uses multiple 
        /// threads. For more details, see 
        /// <see href="https://learn.microsoft.com/en-us/windows/win32/direct3ddxgi/d3d10-graphics-programming-guide-dxgi">Multithreading Considerations</see>.
        /// </para>
        /// <para>
        /// For flip presentation model swap chains that you create with the 
        /// <see href="https://learn.microsoft.com/en-us/windows/win32/api/dxgi/ne-dxgi-dxgi_swap_effect">DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL</see> 
        /// value set, a successful presentation unbinds back buffer 0 from the graphics pipeline, except for when you pass the 
        /// <see href="https://learn.microsoft.com/en-us/windows/win32/direct3ddxgi/dxgi-present">DXGI_PRESENT_DO_NOT_SEQUENCE</see> flag in the Flags parameter.
        /// </para>
        /// </remarks>
        void Present( UINT SyncInterval, UINT Flags ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->Present( SyncInterval, Flags );
            CheckHRESULT( hr );
        }

        void GetBuffer( UINT Buffer, REFIID riid, void** ppSurface ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetBuffer( Buffer, riid, ppSurface );
            CheckHRESULT( hr );
        }
        template<typename T>
            requires std::is_base_of_v<IUnknown,T>
        UnknownPtr<T> GetBuffer( UINT Buffer ) const
        {
            T* surface = nullptr;
            GetBuffer( Buffer, __uuidof( T ), (void**)&surface );
            UnknownPtr<T> result( surface );
            return result;
        }

        template<typename T>
            requires std::is_base_of_v<Windows::Graphics::D3D12::Resource,T>
        T GetBuffer( UINT bufferIndex ) const
        {
            using IntfT = T::InterfaceType;
            IID IntfTId = __uuidof( IntfT );

            IntfT* intf = nullptr;

            GetBuffer( bufferIndex, IntfTId, (void**)&intf );
            T result( intf );
            return result;
        }



        void SetFullscreenState( BOOL Fullscreen, IDXGIOutput* pTarget ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->SetFullscreenState( Fullscreen, pTarget );
            CheckHRESULT( hr );
        }

        void GetFullscreenState( BOOL* pFullscreen, IDXGIOutput** ppTarget ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetFullscreenState( pFullscreen, ppTarget );
            CheckHRESULT( hr );
        }

        void GetDesc( DXGI_SWAP_CHAIN_DESC* pDesc ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetDesc( pDesc );
            CheckHRESULT( hr );
        }

        void ResizeBuffers( UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->ResizeBuffers( BufferCount, Width, Height, NewFormat, SwapChainFlags );
            CheckHRESULT( hr );
        }

        void ResizeTarget( const DXGI_MODE_DESC* pNewTargetParameters ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->ResizeTarget( pNewTargetParameters );
            CheckHRESULT( hr );
        }

        void GetContainingOutput( _COM_Outptr_  IDXGIOutput** ppOutput ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetContainingOutput( ppOutput );
            CheckHRESULT( hr );
        }

        Output GetContainingOutput( ) const
        {
            IDXGIOutput* itf = nullptr;
            GetContainingOutput( &itf );
            Output result( itf );
            return result;
        }


        void GetFrameStatistics( DXGI_FRAME_STATISTICS* pStats ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetFrameStatistics( pStats );
            CheckHRESULT( hr );
        }

        void GetLastPresentCount( UINT* pLastPresentCount ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetLastPresentCount( pLastPresentCount );
            CheckHRESULT( hr );
        }
    };


    /// <summary>
    /// The Factory class implements methods for generating DXGI 
    /// objects (which handle full screen transitions).
    /// </summary>
    class Factory : public Object
    {
    public:
        typedef Object Base;

        HCC_COM_STANDARD_METHODS_IMPL( Factory, Object, IDXGIFactory, IDXGIObject )
        static Factory Create( )
        {
            InterfaceType* factory = nullptr;
            auto hr = CreateDXGIFactory( __uuidof( InterfaceType ), (void**)&factory );
            CheckHRESULT( hr );
            Factory result( factory );
            return result;
        }
    public:
        void EnumAdapters( UINT adapterIndex, IDXGIAdapter** adapter ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->EnumAdapters( adapterIndex, adapter );
            if ( hr == DXGI_ERROR_NOT_FOUND )
            {
                if ( adapter )
                {
                    *adapter = nullptr;
                }
            }
            else
            {
                CheckHRESULT( hr );
            }
        }

        void MakeWindowAssociation( HWND windowHandle, UINT flags ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->MakeWindowAssociation( windowHandle, flags );
            CheckHRESULT( hr );
        }

        void GetWindowAssociation( HWND* windowHandle ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetWindowAssociation( windowHandle );
            CheckHRESULT( hr );
        }

        void CreateSwapChain( IUnknown* pDevice, DXGI_SWAP_CHAIN_DESC* pDesc, IDXGISwapChain** ppSwapChain ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateSwapChain( pDevice, pDesc, ppSwapChain );
            CheckHRESULT( hr );
        }

        void CreateSoftwareAdapter( HMODULE Module, IDXGIAdapter** ppAdapter ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateSoftwareAdapter( Module, ppAdapter );
            CheckHRESULT( hr );
        }
    };

    /// <summary>
    /// An Device class implements a derived class for DXGI objects that produce image data.
    /// </summary>
    class Device : public Object
    {
    public:
        typedef Object Base;

        HCC_COM_STANDARD_METHODS_IMPL( Device, Object, IDXGIDevice, IDXGIObject )
    public:
        void GetAdapter( IDXGIAdapter** pAdapter ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetAdapter( pAdapter );
            CheckHRESULT( hr );
        }
        Adapter GetAdapter( )
        {
            IDXGIAdapter* adapter = nullptr;
            GetAdapter( &adapter );
            Adapter result( adapter );
            return result;
        }


        void CreateSurface(const DXGI_SURFACE_DESC* pDesc, UINT NumSurfaces, DXGI_USAGE Usage, const DXGI_SHARED_RESOURCE* pSharedResource, IDXGISurface** ppSurface ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateSurface( pDesc, NumSurfaces, Usage, pSharedResource, ppSurface );
            CheckHRESULT( hr );
        }

        void QueryResourceResidency(IUnknown* const* ppResources, DXGI_RESIDENCY* pResidencyStatus, UINT NumResources ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->QueryResourceResidency( ppResources, pResidencyStatus, NumResources );
            CheckHRESULT( hr );
        }

        void SetGPUThreadPriority( INT Priority ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->SetGPUThreadPriority( Priority );
            CheckHRESULT( hr );
        }

        void GetGPUThreadPriority( INT* pPriority ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetGPUThreadPriority( pPriority );
            CheckHRESULT( hr );
        }
    };

    /// <summary>
    /// The Adapter1 class represents a display sub-system (including one or more GPU's, DACs and video memory).
    /// </summary>
    class Adapter1 : public Adapter
    {
    public:
        typedef Adapter Base;

        HCC_COM_STANDARD_METHODS_IMPL( Adapter1, Adapter, IDXGIAdapter1, IDXGIAdapter )
    public:
        void GetDesc1( DXGI_ADAPTER_DESC1* pDesc ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetDesc1( pDesc );
            CheckHRESULT( hr );
        }

        DXGI_ADAPTER_DESC1 GetDesc1( ) const
        {
            DXGI_ADAPTER_DESC1 result{};
            GetDesc1( &result );
            return result;
        }


        bool CanCreateD3D12Device( D3D_FEATURE_LEVEL minimumFeatureLevel = D3D_FEATURE_LEVEL_11_1 ) const
        {
            auto* pInterface = GetInterface( );
            if ( SUCCEEDED( D3D12CreateDevice( pInterface, minimumFeatureLevel, __uuidof( ID3D12Device ), nullptr ) ) )
            {
                return true;
            }
            else
            {
                return false;
            }
        }

    };

    /// <summary>
    /// The Factory1 class implements methods for generating DXGI objects.
    /// </summary>
    class Factory1 : public Factory
    {
    public:
        typedef Factory Base;

        HCC_COM_STANDARD_METHODS_IMPL( Factory1, Factory, IDXGIFactory1, IDXGIFactory )
        static Factory1 Create( )
        {
            InterfaceType* factory = nullptr;
            auto hr = CreateDXGIFactory1( __uuidof( InterfaceType ), (void**)&factory );
            CheckHRESULT( hr );
            Factory1 result( factory );
            return result;
        }
    public:
        using Base::EnumAdapters;

        void EnumAdapters1( UINT adapterIndex, IDXGIAdapter1** ppAdapter ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->EnumAdapters1( adapterIndex, ppAdapter );
            if ( hr == DXGI_ERROR_NOT_FOUND )
            {
                if ( ppAdapter )
                {
                    *ppAdapter = nullptr;
                }
            }
            else
            {
                CheckHRESULT( hr );
            }
        }

        Adapter1 EnumAdapters( UINT adapterNumber ) const
        {
            IDXGIAdapter1* adapter = nullptr;
            EnumAdapters1( adapterNumber, &adapter );
            Adapter1 result( adapter );
            return result;
        }

        Adapter1 FindAdapter( D3D_FEATURE_LEVEL minimumFeatureLevel = D3D_FEATURE_LEVEL_11_1 ) const
        {
            auto* pInterface = GetInterface( );
            for ( UINT adapterIndex = 0; ; ++adapterIndex )
            {
                auto adapter = EnumAdapters( adapterIndex );
                if ( adapter )
                {
                    if ( adapter.CanCreateD3D12Device( minimumFeatureLevel ) )
                    {
                        return adapter;
                    }
                }
            }
            return Adapter1( );
        }


        bool IsCurrent( void ) const
        {
            auto* pInterface = GetInterface( );
            return pInterface->IsCurrent( ) != FALSE;
        }
    };

    /// <summary>
    /// The Device1 class implements a derived class for DXGI objects that produce image data.
    /// </summary>
    class Device1 : public Device
    {
    public:
        using Base = Device;

        HCC_COM_STANDARD_METHODS_IMPL( Device1, Base, IDXGIDevice1, IDXGIDevice )
    public:
        void SetMaximumFrameLatency( UINT MaxLatency ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->SetMaximumFrameLatency( MaxLatency );
            CheckHRESULT( hr );
        }

        void GetMaximumFrameLatency( UINT* pMaxLatency ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetMaximumFrameLatency( pMaxLatency );
            CheckHRESULT( hr );
        }
    };

    /// <summary>
    /// The DisplayControl class exposes methods to indicate user preference for 
    /// the operating system's stereoscopic 3D display behavior and to set 
    /// stereoscopic 3D display status to enable or disable.
    /// </summary>
    class DisplayControl : public Unknown
    {
    public:
        using Base = Unknown;

        HCC_COM_STANDARD_METHODS_IMPL( DisplayControl, Base, IDXGIDisplayControl, IUnknown )
    public:
        bool IsStereoEnabled( void ) const
        {
            auto* pInterface = GetInterface( );
            return pInterface->IsStereoEnabled( ) != FALSE;
        }

        void SetStereoEnabled( bool enabled ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->SetStereoEnabled( enabled );
        }
    };

    /// <summary>
    /// The OutputDuplication class accesses and manipulates the duplicated desktop image.
    /// </summary>
    class OutputDuplication : public Object
    {
    public:
        using Base = Object;

        HCC_COM_STANDARD_METHODS_IMPL( OutputDuplication, Base, IDXGIOutputDuplication, IDXGIObject )
    public:
        void GetDesc( DXGI_OUTDUPL_DESC* pDesc ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->GetDesc( pDesc );
        }

        void AcquireNextFrame( UINT TimeoutInMilliseconds, DXGI_OUTDUPL_FRAME_INFO* pFrameInfo, IDXGIResource** ppDesktopResource ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->AcquireNextFrame( TimeoutInMilliseconds, pFrameInfo, ppDesktopResource );
            CheckHRESULT( hr );
        }

        void GetFrameDirtyRects( UINT DirtyRectsBufferSize, RECT* pDirtyRectsBuffer, UINT* pDirtyRectsBufferSizeRequired ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetFrameDirtyRects( DirtyRectsBufferSize, pDirtyRectsBuffer, pDirtyRectsBufferSizeRequired );
            CheckHRESULT( hr );
        }

        void GetFrameMoveRects( UINT MoveRectsBufferSize, DXGI_OUTDUPL_MOVE_RECT* pMoveRectBuffer, UINT* pMoveRectsBufferSizeRequired ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetFrameMoveRects( MoveRectsBufferSize, pMoveRectBuffer, pMoveRectsBufferSizeRequired );
            CheckHRESULT( hr );
        }

        void GetFramePointerShape( UINT PointerShapeBufferSize, void* pPointerShapeBuffer, UINT* pPointerShapeBufferSizeRequired, DXGI_OUTDUPL_POINTER_SHAPE_INFO* pPointerShapeInfo ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetFramePointerShape( PointerShapeBufferSize, pPointerShapeBuffer, pPointerShapeBufferSizeRequired, pPointerShapeInfo );
            CheckHRESULT( hr );
        }

        void MapDesktopSurface(DXGI_MAPPED_RECT* pLockedRect ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->MapDesktopSurface( pLockedRect );
            CheckHRESULT( hr );
        }

        void UnMapDesktopSurface( void ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->UnMapDesktopSurface( );
            CheckHRESULT( hr );
        }

        void ReleaseFrame( void ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->ReleaseFrame( );
            CheckHRESULT( hr );
        }
    };


    /// <summary>
    /// The Surface2 class extends the Surface1 class by adding support for 
    /// subresource surfaces and getting a handle to a shared resource.
    /// </summary>
    class Surface2 : public Surface1
    {
    public:
        using Base = Surface1;

        HCC_COM_STANDARD_METHODS_IMPL( Surface2, Base, IDXGISurface2, IDXGISurface1 )
    public:
        void GetResource( REFIID riid, void** ppParentResource, UINT* pSubresourceIndex ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetResource( riid, ppParentResource, pSubresourceIndex );
            CheckHRESULT( hr );
        }
    };

    /// <summary>
    /// The Resource1 class extends the Resource class by adding support for 
    /// creating a subresource surface object and for creating a handle to a shared resource.
    /// </summary>
    class Resource1 : public Resource
    {
    public:
        using Base = Resource;

        HCC_COM_STANDARD_METHODS_IMPL( Resource1, Base, IDXGIResource1, IDXGIResource )
    public:
        void CreateSubresourceSurface( UINT index, IDXGISurface2** ppSurface ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateSubresourceSurface( index, ppSurface );
            CheckHRESULT( hr );
        }

        void CreateSharedHandle( const SECURITY_ATTRIBUTES* pAttributes, DWORD dwAccess, LPCWSTR lpName, HANDLE* pHandle ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateSharedHandle( pAttributes, dwAccess, lpName, pHandle );
            CheckHRESULT( hr );
        }
    };

    /// <summary>
    /// The Device2 class implements a derived class for DXGI objects that produce image data. 
    /// The class exposes methods to block CPU processing until the GPU completes processing, 
    /// and to offer resources to the operating system.
    /// </summary>
    class Device2 : public Device1
    {
    public:
        using Base = Device1;

        HCC_COM_STANDARD_METHODS_IMPL( Device2, Base, IDXGIDevice2, IDXGIDevice1 )
    public:
        void OfferResources( UINT NumResources, IDXGIResource* const* ppResources, DXGI_OFFER_RESOURCE_PRIORITY Priority ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->OfferResources( NumResources, ppResources, Priority );
            CheckHRESULT( hr );
        }

        void ReclaimResources( UINT NumResources, IDXGIResource* const* ppResources, BOOL* pDiscarded ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->ReclaimResources( NumResources, ppResources, pDiscarded );
            CheckHRESULT( hr );
        }

        void EnqueueSetEvent( HANDLE hEvent ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->EnqueueSetEvent( hEvent );
            CheckHRESULT( hr );
        }
    };

    /// <summary>
    /// Provides presentation capabilities that are enhanced from SwapChain. 
    /// These presentation capabilities consist of specifying dirty rectangles 
    /// and scroll rectangle to optimize the presentation.
    /// </summary>
    class SwapChain1 : public SwapChain
    {
    public:
        using Base = SwapChain;

        HCC_COM_STANDARD_METHODS_IMPL( SwapChain1, Base, IDXGISwapChain1, IDXGISwapChain )
    public:
        void GetDesc1( DXGI_SWAP_CHAIN_DESC1* pDesc ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetDesc1( pDesc );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        DXGI_SWAP_CHAIN_DESC1 GetDesc1( ) const
        {
            DXGI_SWAP_CHAIN_DESC1 result{};
            GetDesc1( &result );
            return result;
        }


        void GetFullscreenDesc( DXGI_SWAP_CHAIN_FULLSCREEN_DESC* pDesc ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetFullscreenDesc( pDesc );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        DXGI_SWAP_CHAIN_FULLSCREEN_DESC GetFullscreenDesc( ) const
        {
            DXGI_SWAP_CHAIN_FULLSCREEN_DESC result{};
            GetFullscreenDesc( &result );
            return result;
        }


        void GetHwnd( HWND* pHwnd ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetHwnd( pHwnd );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        HWND GetHwnd( ) const
        {
            HWND result = nullptr;
            GetHwnd( &result );
            return result;
        }


        void GetCoreWindow( REFIID refiid, void** ppUnk ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetCoreWindow( refiid, ppUnk );
            CheckHRESULT( hr );
        }

        void Present1( UINT SyncInterval, UINT PresentFlags, const DXGI_PRESENT_PARAMETERS* pPresentParameters ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->Present1( SyncInterval, PresentFlags, pPresentParameters );
            CheckHRESULT( hr );
        }

        bool IsTemporaryMonoSupported( void ) const
        {
            auto* pInterface = GetInterface( );
            return pInterface->IsTemporaryMonoSupported( );
        }

        void GetRestrictToOutput( IDXGIOutput** ppRestrictToOutput ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetRestrictToOutput( ppRestrictToOutput );
            CheckHRESULT( hr );
        }

        void SetBackgroundColor( const DXGI_RGBA* pColor ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->SetBackgroundColor( pColor );
            CheckHRESULT( hr );
        }

        void GetBackgroundColor( DXGI_RGBA* pColor ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetBackgroundColor( pColor );
            CheckHRESULT( hr );
        }

        void SetRotation( DXGI_MODE_ROTATION Rotation ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->SetRotation( Rotation );
            CheckHRESULT( hr );
        }

        void GetRotation( DXGI_MODE_ROTATION* pRotation ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetRotation( pRotation );
            CheckHRESULT( hr );
        }
    };

    /// <summary>
    /// The Factory2 class includes methods to create a newer version 
    /// swap chain with more features than SwapChain and to monitor 
    /// stereoscopic 3D capabilities.
    /// </summary>
    class Factory2 : public Factory1
    {
    public:
        using Base = Factory1;

        HCC_COM_STANDARD_METHODS_IMPL( Factory2, Base, IDXGIFactory2, IDXGIFactory1 )
        static Factory2 Create( )
        {
            InterfaceType* factory = nullptr;
            auto hr = CreateDXGIFactory1( __uuidof( InterfaceType ), (void**)&factory );
            CheckHRESULT( hr );
            Factory2 result( factory );
            return result;
        }
    public:
        bool IsWindowedStereoEnabled( void ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->IsWindowedStereoEnabled( );
        }

        void CreateSwapChainForHwnd( IUnknown* pDevice, HWND hWnd, const DXGI_SWAP_CHAIN_DESC1* pDesc, const DXGI_SWAP_CHAIN_FULLSCREEN_DESC* pFullscreenDesc, IDXGIOutput* pRestrictToOutput, IDXGISwapChain1** ppSwapChain ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateSwapChainForHwnd( pDevice, hWnd, pDesc, pFullscreenDesc, pRestrictToOutput, ppSwapChain );
            CheckHRESULT( hr );
        }

        template<typename SwapChainT = SwapChain1,typename CommandQueueT = Unknown>
            requires (std::is_base_of_v<SwapChain1, SwapChainT> && std::is_base_of_v<Unknown, CommandQueueT>)
        SwapChainT CreateSwapChainForHwnd( const CommandQueueT& commandQueue, HWND hWnd, const DXGI_SWAP_CHAIN_DESC1* pDesc, const DXGI_SWAP_CHAIN_FULLSCREEN_DESC* fullscreenDesc = nullptr, IDXGIOutput* pRestrictToOutput = nullptr ) const
        {
            IDXGISwapChain1* pSwapChain = nullptr;
            auto* pInterface = GetInterface( );
            IUnknown* pDevice = commandQueue.GetInterfacePointer<IUnknown>();
            auto hr = pInterface->CreateSwapChainForHwnd( pDevice, hWnd, pDesc, fullscreenDesc, pRestrictToOutput, &pSwapChain );
            CheckHRESULT( hr );
            SwapChain1 swapChain1( pSwapChain );
            if constexpr ( std::is_same_v< SwapChainT, SwapChain1> )
            {
                return swapChain1;
            }
            else
            {
                return swapChain1.As<SwapChainT>( );
            }
        }


        void CreateSwapChainForCoreWindow( IUnknown* pDevice, IUnknown* pWindow, const DXGI_SWAP_CHAIN_DESC1* pDesc, IDXGIOutput* pRestrictToOutput, IDXGISwapChain1** ppSwapChain ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateSwapChainForCoreWindow( pDevice, pWindow, pDesc, pRestrictToOutput, ppSwapChain );
            CheckHRESULT( hr );
        }

        void GetSharedResourceAdapterLuid( HANDLE hResource, LUID* pLuid ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetSharedResourceAdapterLuid( hResource, pLuid );
            CheckHRESULT( hr );
        }

        void RegisterStereoStatusWindow( HWND WindowHandle, UINT wMsg, DWORD* pdwCookie ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->RegisterStereoStatusWindow( WindowHandle, wMsg, pdwCookie );
            CheckHRESULT( hr );
        }

        void RegisterStereoStatusEvent( HANDLE hEvent, DWORD* pdwCookie ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->RegisterStereoStatusEvent( hEvent, pdwCookie );
            CheckHRESULT( hr );
        }

        void UnregisterStereoStatus( DWORD dwCookie ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->UnregisterStereoStatus( dwCookie );
        }

        void RegisterOcclusionStatusWindow( HWND WindowHandle, UINT wMsg, DWORD* pdwCookie ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->RegisterOcclusionStatusWindow( WindowHandle, wMsg, pdwCookie );
            CheckHRESULT( hr );
        }

        void RegisterOcclusionStatusEvent( HANDLE hEvent, DWORD* pdwCookie ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->RegisterOcclusionStatusEvent( hEvent, pdwCookie );
            CheckHRESULT( hr );
        }

        void UnregisterOcclusionStatus( DWORD dwCookie ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->UnregisterOcclusionStatus( dwCookie );
        }

        void CreateSwapChainForComposition( IUnknown* pDevice, const DXGI_SWAP_CHAIN_DESC1* pDesc, IDXGIOutput* pRestrictToOutput, IDXGISwapChain1** ppSwapChain ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateSwapChainForComposition( pDevice, pDesc, pRestrictToOutput, ppSwapChain );
            CheckHRESULT( hr );
        }
    };

    /// <summary>
    /// The Adapter2 class represents a display subsystem, which 
    /// includes one or more GPUs, DACs, and video memory.
    /// </summary>
    class Adapter2 : public Adapter1
    {
    public:
        using Base = Adapter1;

        HCC_COM_STANDARD_METHODS_IMPL( Adapter2, Base, IDXGIAdapter2, IDXGIAdapter1 )
    public:
        void GetDesc2( DXGI_ADAPTER_DESC2* pDesc ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetDesc2( pDesc );
            CheckHRESULT( hr );
        }
    };

    /// <summary>
    /// An Output1 object represents an adapter output (such as a monitor).
    /// </summary>
    class Output1 : public Output
    {
    public:
        using Base = Output;

        HCC_COM_STANDARD_METHODS_IMPL( Output1, Base, IDXGIOutput1, IDXGIOutput )
    public:
        void GetDisplayModeList1( DXGI_FORMAT EnumFormat, UINT Flags, UINT* pNumModes, DXGI_MODE_DESC1* pDesc ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetDisplayModeList1( EnumFormat, Flags, pNumModes, pDesc );
            CheckHRESULT( hr );
        }

        void FindClosestMatchingMode1( const DXGI_MODE_DESC1* pModeToMatch, DXGI_MODE_DESC1* pClosestMatch, IUnknown* pConcernedDevice ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->FindClosestMatchingMode1( pModeToMatch, pClosestMatch, pConcernedDevice );
            CheckHRESULT( hr );
        }

        void GetDisplaySurfaceData1( IDXGIResource* pDestination ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetDisplaySurfaceData1( pDestination );
            CheckHRESULT( hr );
        }

        void DuplicateOutput( IUnknown* pDevice, IDXGIOutputDuplication** ppOutputDuplication ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->DuplicateOutput( pDevice, ppOutputDuplication );
            CheckHRESULT( hr );
        }
    };

    /// <summary>
    /// The Device3 class implements a derived class for DXGI objects that produce image data. 
    /// The class exposes a method to trim graphics memory usage by the DXGI device.
    /// </summary>
    class Device3 : public Device2
    {
    public:
        using Base = Device2;

        HCC_COM_STANDARD_METHODS_IMPL( Device3, Base, IDXGIDevice3, IDXGIDevice2 )
    public:
        void Trim( void ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->Trim(  );
        }
    };

    /// <summary>
    /// Extends SwapChain1 with methods to support swap back buffer 
    /// scaling and lower-latency swap chains.
    /// </summary>
    class SwapChain2 : public SwapChain1
    {
    public:
        using Base = SwapChain1;

        HCC_COM_STANDARD_METHODS_IMPL( SwapChain2, Base, IDXGISwapChain2, IDXGISwapChain1 )
    public:
        void SetSourceSize( UINT Width, UINT Height ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->SetSourceSize( Width, Height );
            CheckHRESULT( hr );
        }

        void GetSourceSize( UINT* pWidth, UINT* pHeight ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetSourceSize( pWidth, pHeight );
            CheckHRESULT( hr );
        }

        void SetMaximumFrameLatency( UINT MaxLatency ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->SetMaximumFrameLatency( MaxLatency );
            CheckHRESULT( hr );
        }

        void GetMaximumFrameLatency( UINT* pMaxLatency ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetMaximumFrameLatency( pMaxLatency );
            CheckHRESULT( hr );
        }

        HANDLE GetFrameLatencyWaitableObject( void ) const
        {
            auto* pInterface = GetInterface( );
            return pInterface->GetFrameLatencyWaitableObject( );
        }

        void SetMatrixTransform( const DXGI_MATRIX_3X2_F* pMatrix ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->SetMatrixTransform( pMatrix );
            CheckHRESULT( hr );
        }

        void GetMatrixTransform( DXGI_MATRIX_3X2_F* pMatrix ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetMatrixTransform( pMatrix );
            CheckHRESULT( hr );
        }
    };

    /// <summary>
    /// Represents an adapter output (such as a monitor). The Output2 class exposes 
    /// a method to check for multiplane overlay support on the primary output adapter.
    /// </summary>
    class Output2 : public Output1
    {
    public:
        using Base = Output1;

        HCC_COM_STANDARD_METHODS_IMPL( Output2, Base, IDXGIOutput2, IDXGIOutput1 )
    public:
        bool SupportsOverlays( void ) const
        {
            auto* pInterface = GetInterface( );
            return pInterface->SupportsOverlays( );
        }
    };

    /// <summary>
    /// Enables creating Microsoft DirectX Graphics Infrastructure (DXGI) objects.
    /// </summary>
    class Factory3 : public Factory2
    {
    public:
        using Base = Factory2;

        HCC_COM_STANDARD_METHODS_IMPL( Factory3, Base, IDXGIFactory3, IDXGIFactory2 )
        static Factory3 Create( )
        {
            InterfaceType* factory = nullptr;
            auto hr = CreateDXGIFactory1( __uuidof( InterfaceType ), (void**)&factory );
            CheckHRESULT( hr );
            Factory3 result( factory );
            return result;
        }
    public:
        UINT GetCreationFlags( void ) const
        {
            auto* pInterface = GetInterface( );
            return pInterface->GetCreationFlags( );
        }
    };

    /// <summary>
    /// Represents a swap chain that is used by desktop media apps to 
    /// decode video data and show it on a DirectComposition surface.
    /// </summary>
    class DecodeSwapChain : public Unknown
    {
    public:
        using Base = Unknown;

        HCC_COM_STANDARD_METHODS_IMPL( DecodeSwapChain, Base, IDXGIDecodeSwapChain, IUnknown )
    public:
        void PresentBuffer( UINT BufferToPresent, UINT SyncInterval, UINT Flags ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->PresentBuffer( BufferToPresent, SyncInterval, Flags );
            CheckHRESULT( hr );
        }

        void SetSourceRect( const RECT* pRect ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->SetSourceRect( pRect );
            CheckHRESULT( hr );
        }

        void SetTargetRect( const RECT* pRect ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->SetTargetRect( pRect );
            CheckHRESULT( hr );
        }

        void SetDestSize( UINT Width, UINT Height ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->SetDestSize( Width, Height );
            CheckHRESULT( hr );
        }

        void GetSourceRect( RECT* pRect ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetSourceRect( pRect );
            CheckHRESULT( hr );
        }

        void GetTargetRect( RECT* pRect ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetTargetRect( pRect );
            CheckHRESULT( hr );
        }

        void GetDestSize( UINT* pWidth, UINT* pHeight ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetDestSize( pWidth, pHeight );
            CheckHRESULT( hr );
        }

        void SetColorSpace( DXGI_MULTIPLANE_OVERLAY_YCbCr_FLAGS ColorSpace ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->SetColorSpace( ColorSpace );
            CheckHRESULT( hr );
        }

        DXGI_MULTIPLANE_OVERLAY_YCbCr_FLAGS GetColorSpace( void ) const
        {
            auto* pInterface = GetInterface( );
            return pInterface->GetColorSpace( );
        }
    };

    /// <summary>
    /// Creates swap chains for desktop media apps that use 
    /// DirectComposition surfaces to decode and display video.
    /// </summary>
    class FactoryMedia : public Unknown
    {
    public:
        using Base = Unknown;

        HCC_COM_STANDARD_METHODS_IMPL( FactoryMedia, Base, IDXGIFactoryMedia, IUnknown )
    public:
        void CreateSwapChainForCompositionSurfaceHandle(
            IUnknown* pDevice,
            HANDLE hSurface,
            const DXGI_SWAP_CHAIN_DESC1* pDesc,
            IDXGIOutput* pRestrictToOutput,
            IDXGISwapChain1** ppSwapChain ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateSwapChainForCompositionSurfaceHandle( pDevice, hSurface, pDesc, pRestrictToOutput, ppSwapChain );
            CheckHRESULT( hr );
        }

        void CreateDecodeSwapChainForCompositionSurfaceHandle(
            IUnknown* pDevice,
            HANDLE hSurface,
            DXGI_DECODE_SWAP_CHAIN_DESC* pDesc,
            IDXGIResource* pYuvDecodeBuffers,
            IDXGIOutput* pRestrictToOutput,
            IDXGIDecodeSwapChain** ppSwapChain ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateDecodeSwapChainForCompositionSurfaceHandle( pDevice, hSurface, pDesc, pYuvDecodeBuffers, pRestrictToOutput, ppSwapChain );
            CheckHRESULT( hr );
        }
    };


    /// <summary>
    /// This swap chain class allows desktop media applications to request a seamless change to a specific refresh rate.
    /// </summary>
    class SwapChainMedia : public Unknown
    {
    public:
        using Base = Unknown;

        HCC_COM_STANDARD_METHODS_IMPL( SwapChainMedia, Base, IDXGISwapChainMedia, IUnknown )
    public:
        void GetFrameStatisticsMedia( DXGI_FRAME_STATISTICS_MEDIA* pStats ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetFrameStatisticsMedia( pStats );
            CheckHRESULT( hr );
        }

        void SetPresentDuration( UINT Duration ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->SetPresentDuration( Duration );
            CheckHRESULT( hr );
        }

        void CheckPresentDurationSupport( UINT DesiredPresentDuration,  UINT* pClosestSmallerPresentDuration, UINT* pClosestLargerPresentDuration ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CheckPresentDurationSupport( DesiredPresentDuration, pClosestSmallerPresentDuration, pClosestLargerPresentDuration );
            CheckHRESULT( hr );
        }
    };

    /// <summary>
    /// Represents an adapter output (such as a monitor). The Output3 class 
    /// exposes a method to check for overlay support.
    /// </summary>
    class Output3 : public Output2
    {
    public:
        using Base = Output2;

        HCC_COM_STANDARD_METHODS_IMPL( Output3, Base, IDXGIOutput3, IDXGIOutput2 )
    public:
        void CheckOverlaySupport( DXGI_FORMAT EnumFormat, IUnknown* pConcernedDevice, UINT* pFlags ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CheckOverlaySupport( EnumFormat, pConcernedDevice, pFlags );
            CheckHRESULT( hr );
        }
    };

    /// <summary>
    /// Extends SwapChain2 with methods to support getting the index of 
    /// the swap chain's current back buffer and support for color space.
    /// </summary>
    class SwapChain3 : public SwapChain2
    {
    public:
        using Base = SwapChain2;

        HCC_COM_STANDARD_METHODS_IMPL( SwapChain3, Base, IDXGISwapChain3, IDXGISwapChain2 )
    public:
        UINT GetCurrentBackBufferIndex( void ) const
        {
            auto* pInterface = GetInterface( );
            return pInterface->GetCurrentBackBufferIndex( );
        }

        void CheckColorSpaceSupport( DXGI_COLOR_SPACE_TYPE colorSpace, UINT* pColorSpaceSupport ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CheckColorSpaceSupport( colorSpace, pColorSpaceSupport );
            CheckHRESULT( hr );
        }

        UINT CheckColorSpaceSupport( DXGI_COLOR_SPACE_TYPE colorSpace )
        {
            UINT result = 0;
            CheckColorSpaceSupport( colorSpace, &result );
            return result;
        }


        void SetColorSpace1( DXGI_COLOR_SPACE_TYPE ColorSpace ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->SetColorSpace1( ColorSpace );
            CheckHRESULT( hr );
        }

        void ResizeBuffers1( UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT Format, UINT SwapChainFlags, const UINT* pCreationNodeMask, IUnknown* const* ppPresentQueue ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->ResizeBuffers1( BufferCount, Width, Height, Format, SwapChainFlags, pCreationNodeMask, ppPresentQueue );
            CheckHRESULT( hr );
        }
    };

    /// <summary>
    /// Represents an adapter output (such as a monitor). The Output4 class 
    /// exposes a method to check for overlay color space support.
    /// </summary>
    class Output4 : public Output3
    {
    public:
        using Base = Output3;

        HCC_COM_STANDARD_METHODS_IMPL( Output4, Base, IDXGIOutput4, IDXGIOutput3 )
    public:
        void CheckOverlayColorSpaceSupport( DXGI_FORMAT Format, DXGI_COLOR_SPACE_TYPE ColorSpace, IUnknown* pConcernedDevice, UINT* pFlags ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CheckOverlayColorSpaceSupport( Format, ColorSpace, pConcernedDevice, pFlags );
            CheckHRESULT( hr );
        }
    };


    /// <summary>
    /// Enables creating Microsoft DirectX Graphics Infrastructure (DXGI) objects.
    /// </summary>
    class Factory4 : public Factory3
    {
    public:
        using Base = Factory3;

        HCC_COM_STANDARD_METHODS_IMPL( Factory4, Base, IDXGIFactory4, IDXGIFactory3 )
        static Factory4 Create( )
        {
            InterfaceType* factory = nullptr;
            auto hr = CreateDXGIFactory1( __uuidof( InterfaceType ), (void**)&factory );
            CheckHRESULT( hr );
            Factory4 result( factory );
            return result;
        }
        static Factory4 Create( UINT flags )
        {
            InterfaceType* factory = nullptr;
            auto hr = CreateDXGIFactory2( flags, __uuidof( InterfaceType ), ( void** )&factory );
            CheckHRESULT( hr );
            Factory4 result( factory );
            return result;
        }

    public:
        void EnumAdapterByLuid( LUID AdapterLuid, REFIID riid, void** ppvAdapter ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->EnumAdapterByLuid( AdapterLuid, riid, ppvAdapter );
            CheckHRESULT( hr );
        }

        template<typename T = Adapter>
            requires std::is_base_of_v<Adapter,T>
        T EnumAdapterByLuid( LUID AdapterLuid ) const
        {
            using ItfT = typename T::InterfaceType;
            constexpr auto riid = __uuidof( ItfT );
            ItfT* ptr = nullptr;
            EnumAdapterByLuid( AdapterLuid, riid, reinterpret_cast< void** >( &ptr ) );
            return T( ptr );
        }


        void EnumWarpAdapter( REFIID riid, void** ppvAdapter ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->EnumWarpAdapter( riid, ppvAdapter );
            CheckHRESULT( hr );
        }

        template<typename T = Adapter>
            requires std::is_base_of_v<Adapter, T>
        T EnumWarpAdapter( ) const
        {
            using ItfT = typename T::InterfaceType;
            constexpr auto riid = __uuidof( ItfT );
            ItfT* ptr = nullptr;
            EnumWarpAdapter( riid, reinterpret_cast< void** >( &ptr ) );
            return T( ptr );
        }

    };

    /// <summary>
    /// This class adds some memory residency methods, for budgeting and reserving physical memory.
    /// </summary>
    class Adapter3 : public Adapter2
    {
    public:
        using Base = Adapter2;

        HCC_COM_STANDARD_METHODS_IMPL( Adapter3, Base, IDXGIAdapter3, IDXGIAdapter2 )
    public:
        void RegisterHardwareContentProtectionTeardownStatusEvent( HANDLE hEvent, DWORD* pdwCookie ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->RegisterHardwareContentProtectionTeardownStatusEvent( hEvent, pdwCookie );
            CheckHRESULT( hr );
        }

        void UnregisterHardwareContentProtectionTeardownStatus( DWORD dwCookie ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->UnregisterHardwareContentProtectionTeardownStatus( dwCookie );
        }

        void QueryVideoMemoryInfo( UINT NodeIndex, DXGI_MEMORY_SEGMENT_GROUP MemorySegmentGroup, DXGI_QUERY_VIDEO_MEMORY_INFO* pVideoMemoryInfo ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->QueryVideoMemoryInfo( NodeIndex, MemorySegmentGroup, pVideoMemoryInfo );
            CheckHRESULT( hr );
        }

        void SetVideoMemoryReservation( UINT NodeIndex, DXGI_MEMORY_SEGMENT_GROUP MemorySegmentGroup, UINT64 Reservation ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->SetVideoMemoryReservation( NodeIndex, MemorySegmentGroup, Reservation );
            CheckHRESULT( hr );
        }

        void RegisterVideoMemoryBudgetChangeNotificationEvent( HANDLE hEvent, DWORD* pdwCookie ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->RegisterVideoMemoryBudgetChangeNotificationEvent( hEvent, pdwCookie );
            CheckHRESULT( hr );
        }

        void UnregisterVideoMemoryBudgetChangeNotification( DWORD dwCookie ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->UnregisterVideoMemoryBudgetChangeNotification( dwCookie );
        }
    };

    /// <summary>
    /// Represents an adapter output (such as a monitor). The Output5 class 
    /// exposes a single method to specify a list of supported formats for 
    /// full screen surfaces.
    /// </summary>
    class Output5 : public Output4
    {
    public:
        using Base = Output4;

        HCC_COM_STANDARD_METHODS_IMPL( Output5, Base, IDXGIOutput5, IDXGIOutput4 )
    public:
        void DuplicateOutput1( IUnknown* pDevice, UINT Flags, UINT SupportedFormatsCount, const DXGI_FORMAT* pSupportedFormats, IDXGIOutputDuplication** ppOutputDuplication ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->DuplicateOutput1( pDevice, Flags, SupportedFormatsCount, pSupportedFormats, ppOutputDuplication );
            CheckHRESULT( hr );
        }
    };

    /// <summary>
    /// This class exposes a single method for setting video metadata.
    /// </summary>
    class SwapChain4 : public SwapChain3
    {
    public:
        using Base = SwapChain3;

        HCC_COM_STANDARD_METHODS_IMPL( SwapChain4, Base, IDXGISwapChain4, IDXGISwapChain3 )
    public:
        void SetHDRMetaData( DXGI_HDR_METADATA_TYPE Type, UINT Size, void* pMetaData ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->SetHDRMetaData( Type, Size, pMetaData );
            CheckHRESULT( hr );
        }
    };

    /// <summary>
    /// This class provides updated methods to offer and reclaim resources.
    /// </summary>
    class Device4 : public Device3
    {
    public:
        using Base = Device3;

        HCC_COM_STANDARD_METHODS_IMPL( Device4, Base, IDXGIDevice4, IDXGIDevice3 )
    public:
        void OfferResources1( UINT NumResources, IDXGIResource* const* ppResources, DXGI_OFFER_RESOURCE_PRIORITY Priority, UINT Flags ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->OfferResources1( NumResources, ppResources, Priority, Flags );
            CheckHRESULT( hr );
        }

        void ReclaimResources1( UINT NumResources, IDXGIResource* const* ppResources, DXGI_RECLAIM_RESOURCE_RESULTS* pResults ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->ReclaimResources1( NumResources, ppResources, pResults );
            CheckHRESULT( hr );
        }
    };

    /// <summary>
    /// This class introduces a single method to support variable refresh rate displays.
    /// </summary>
    class Factory5 : public Factory4
    {
    public:
        using Base = Factory4;

        HCC_COM_STANDARD_METHODS_IMPL( Factory5, Base, IDXGIFactory5, IDXGIFactory4 )
        static Factory5 Create( )
        {
            InterfaceType* factory = nullptr;
            auto hr = CreateDXGIFactory1( __uuidof( InterfaceType ), (void**)&factory );
            CheckHRESULT( hr );
            Factory5 result( factory );
            return result;
        }
    public:
        void CheckFeatureSupport( DXGI_FEATURE Feature, void* pFeatureSupportData, UINT FeatureSupportDataSize ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CheckFeatureSupport( Feature, pFeatureSupportData, FeatureSupportDataSize );
            CheckHRESULT( hr );
        }
    };

    /// <summary>
    /// This class represents a display subsystem, and extends 
    /// Adapter3 to introduce a method to check for an adapter's 
    /// compatibility with Arbitrary Code Guard (ACG).
    /// </summary>
    class Adapter4 : public Adapter3
    {
    public:
        using Base = Adapter3;

        HCC_COM_STANDARD_METHODS_IMPL( Adapter4, Base, IDXGIAdapter4, IDXGIAdapter3 )
    public:
        void GetDesc3( DXGI_ADAPTER_DESC3* pDesc ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetDesc3( pDesc );
            CheckHRESULT( hr );
        }
    };

    /// <summary>
    /// Represents an adapter output (such as a monitor). The Output6 class 
    /// introduces methods to provide specific monitor capabilities.
    /// </summary>
    class Output6 : public Output5
    {
    public:
        using Base = Output5;

        HCC_COM_STANDARD_METHODS_IMPL( Output6, Base, IDXGIOutput6, IDXGIOutput5 )
    public:
        void GetDesc1( DXGI_OUTPUT_DESC1* pDesc ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetDesc1( pDesc );
            CheckHRESULT( hr );
        }
        void CheckHardwareCompositionSupport( UINT* pFlags ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CheckHardwareCompositionSupport( pFlags );
            CheckHRESULT( hr );
        }

    };


    /// <summary>
    /// This class introduces a single method that enumerates graphics adapters based on a given GPU preference.
    /// </summary>
    class Factory6 : public Factory5
    {
    public:
        using Base = Factory5;

        HCC_COM_STANDARD_METHODS_IMPL( Factory6, Base, IDXGIFactory6, IDXGIFactory5 )
        static Factory6 Create( )
        {
            InterfaceType* factory = nullptr;
            auto hr = CreateDXGIFactory1( __uuidof( InterfaceType ), (void**)&factory );
            CheckHRESULT( hr );
            Factory6 result( factory );
            return result;
        }

        static Factory6 Create( UINT flags )
        {
            InterfaceType* factory = nullptr;
            auto hr = CreateDXGIFactory2( flags, __uuidof( InterfaceType ), ( void** )&factory );
            CheckHRESULT( hr );
            Factory6 result( factory );
            return result;
        }

    public:
        void EnumAdapterByGpuPreference( UINT Adapter, DXGI_GPU_PREFERENCE GpuPreference, REFIID riid, void** ppvAdapter ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->EnumAdapterByGpuPreference( Adapter, GpuPreference, riid, ppvAdapter );
            CheckHRESULT( hr );
        }
    };

    /// <summary>
    /// This class enables registration for notifications to detect adapter enumeration state changes.
    /// </summary>
    class Factory7 : public Factory6
    {
    public:
        using Base = Factory6;

        HCC_COM_STANDARD_METHODS_IMPL( Factory7, Base, IDXGIFactory7, IDXGIFactory6 )

        static Factory7 Create( )
        {
            InterfaceType* factory = nullptr;
            auto hr = CreateDXGIFactory1( __uuidof( InterfaceType ), (void**)&factory );
            CheckHRESULT( hr );
            Factory7 result( factory );
            return result;
        }

    public:
        void RegisterAdaptersChangedEvent( HANDLE hEvent, DWORD* pdwCookie ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->RegisterAdaptersChangedEvent( hEvent, pdwCookie );
            CheckHRESULT( hr );
        }

        void UnregisterAdaptersChangedEvent( DWORD dwCookie ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->UnregisterAdaptersChangedEvent( dwCookie );
            CheckHRESULT( hr );
        }
    };

    /// <summary>
    /// Creates a DXGI 1.3 factory that you can use to generate other DXGI objects.
    /// </summary>
    /// <typeparam name="T">
    /// Either Factory2 or a class derived from Factory2. Defaults to Factory7.
    /// </typeparam>
    /// <param name="debug">
    /// If true explicitly request that DXGIDebug.dll be loaded.
    /// </param>
    /// <returns>
    /// The newly created factory.
    /// </returns>
    template<typename T = Factory7>
        requires std::is_base_of_v< Factory2, T>
    T CreateFactory( bool debug = false )
    {
        using InterfaceType = T::InterfaceType;
        auto InterfaceId = __uuidof( InterfaceType );
        InterfaceType* intf = nullptr;
        auto hr = CreateDXGIFactory2( debug? DXGI_CREATE_FACTORY_DEBUG : 0, InterfaceId, (void**)&intf );
        CheckHRESULT( hr );
        T result( intf );
        return result;
    }



}


#endif
