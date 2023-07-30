#pragma once
#ifndef HARLINN_WINDOWS_HWSKIA_H_
#define HARLINN_WINDOWS_HWSKIA_H_

#include <HWControl.h>
#include <HWStdCtrls.h>
#include <HWApplication.h>
#include <HWForm.h>
#include <HWDXGI.h>
#include <HWGraphicsD3D12.h>

#include <HCCSync.h>
#include <HCCEnvironment.h>

#include <skia/core/SkGraphics.h>
#include <skia/core/SkCanvas.h>
#include <skia/core/SkImageInfo.h>
#include <skia/core/SkSurfaceProps.h>
#include <skia/core/SkSurface.h>

#include <skia/gpu/GrContextOptions.h>
#include <skia/gpu/GrDirectContext.h>

#include <skia/gpu/d3d/GrD3DBackendContext.h>


#pragma comment(lib,"DXGI.lib")

namespace Harlinn::Windows
{
    

    using namespace Harlinn::Windows::Graphics;
    using namespace Harlinn::Windows;

    class SkiaDisplayParams
    {
    private:
        SkColorType colorType_ = kN32_SkColorType;
        sk_sp<SkColorSpace> colorSpace_;
        int msaaSampleCount_ = 1;
        GrContextOptions contextOptions_;
        SkSurfaceProps surfaceProps_ = { 0, kRGB_H_SkPixelGeometry };
    public:
        SkiaDisplayParams( ) = default;

        [[nodiscard]]
        SkColorType ColorType( ) const
        {
            return colorType_;
        }
        [[nodiscard]]
        const sk_sp<SkColorSpace>& ColorSpace( ) const
        {
            return colorSpace_;
        }
        [[nodiscard]]
        int MSAASampleCount( ) const
        {
            return msaaSampleCount_;
        }
        [[nodiscard]]
        const GrContextOptions& ContextOptions( ) const
        {
            return contextOptions_;
        }
        [[nodiscard]]
        const SkSurfaceProps& SurfaceProps( ) const
        {
            return surfaceProps_;
        }
    };


    template<typename ControlT, int numFrames = 2>
    class SkiaContext
    {
    public:
        using ControlType = ControlT;
        static constexpr int NumFrames = numFrames;
        static constexpr Size MinSurfaceSize = { 8,8 };
    private:
        ControlType& control_;
        sk_sp<GrDirectContext> directContext_;
        SkiaDisplayParams displayParams_;
        int sampleCount_ = 1;
        int stencilBits_ = 0;

        D3D12Device device_;
        D3D12CommandQueue queue_;
        DXGI::SwapChain3 swapChain_;
        D3D12Resource buffers_[NumFrames];
        sk_sp<SkSurface> surfaces_[NumFrames];

        // Synchronization objects.
        unsigned int bufferIndex_ = 0;
        Common::Core::EventWaitHandle fenceEvent_;
        D3D12Fence fence_;
        uint64_t fenceValues_[NumFrames] = {};

        boost::signals2::connection onHandleCreatedConnection_;
        boost::signals2::connection onBeforeHandleDestroyConnection_;
        boost::signals2::connection onSizeConnection_;
    public:
        SkiaContext( ControlType& control, SkiaDisplayParams displayParams )
            : control_( control ), displayParams_( displayParams ), fenceEvent_( false, false )
        {
            onHandleCreatedConnection_ = control_.OnHandleCreated.connect( [this]( Control* control )
            {
                this->InitializeContext( );
            } );
            onBeforeHandleDestroyConnection_ = control_.OnBeforeHandleDestroy.connect( [this]( Control* control )
            {
                this->DestroyContext( );
            } );
            onSizeConnection_ = control_.OnSize.connect( [this]( Control* sender, Message& message ) 
            {
                if ( sender->IsHandleCreated( ) )
                {
                    Resize( );
                    sender->InvalidateRect( );
                }
            } );
            if ( control_.IsHandleCreated( ) )
            {
                InitializeContext( );
            }
        }

        ~SkiaContext( )
        {
            onSizeConnection_.disconnect( );
            onHandleCreatedConnection_.disconnect( );
            onBeforeHandleDestroyConnection_.disconnect( );
            if ( control_.IsHandleCreated( ) )
            {
                DestroyContext( );
            }
        }
    private:


        bool CreateD3DBackendContext( GrD3DBackendContext* ctx )
        {
#if defined(SK_ENABLE_D3D_DEBUG_LAYER)
            // Enable the D3D12 debug layer.
            {
                gr_cp<ID3D12Debug> debugController;
                if ( SUCCEEDED( D3D12GetDebugInterface( IID_PPV_ARGS( &debugController ) ) ) )
                {
                    debugController->EnableDebugLayer( );
                }
            }
#endif
            auto dxgiFactory = DXGI::CreateFactory<DXGI::Factory4>( );
            auto hardwareAdapter = dxgiFactory.FindAdapter( D3D_FEATURE_LEVEL_12_1 );
            auto device = CreateDevice( hardwareAdapter, D3D_FEATURE_LEVEL_12_1 );

            D3D12_COMMAND_QUEUE_DESC queueDesc = {};
            queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
            queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
            auto queue = device.CreateCommandQueue( queueDesc );

            ctx->fAdapter.reset( hardwareAdapter.Detach() );
            ctx->fDevice.reset( device.Detach( ) );
            ctx->fQueue.reset( queue.Detach( ) );
            ctx->fProtectedContext = GrProtected::kNo;

            return true;
        }
    public:

        void InitializeContext( )
        {
            if ( control_.IsHandleCreated( ) )
            {
                GrD3DBackendContext backendContext;
                CreateD3DBackendContext( &backendContext );
                device_.ResetPtr( backendContext.fDevice.get( ), true );
                queue_.ResetPtr( backendContext.fQueue.get( ), true );

                directContext_ = GrDirectContext::MakeDirect3D( backendContext, displayParams_.ContextOptions( ) );
                SkASSERT( directContext_ );

                // Make the swapchain
                RECT clientRect{};
                control_.GetClientRect( clientRect );

                UInt32 width = static_cast<UInt32>( clientRect.right - clientRect.left );
                UInt32 height = static_cast<UInt32>( clientRect.bottom - clientRect.top );


                if ( width == CW_USEDEFAULT )
                {
                    width = 0;
                }
                if ( height == CW_USEDEFAULT )
                {
                    height = 0;
                }

                bool dxgiDebugFactoryFlag = false;
                SkDEBUGCODE( dxgiDebugFactoryFlag = true;)

                auto factory = DXGI::CreateFactory<DXGI::Factory4>( dxgiDebugFactoryFlag );

                DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
                swapChainDesc.BufferCount = NumFrames;
                swapChainDesc.Width = width;
                swapChainDesc.Height = height;
                swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
                swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
                swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
                swapChainDesc.Scaling = DXGI_SCALING_NONE;
                swapChainDesc.SampleDesc.Count = 1;

                auto windowHandle = control_.GetHandle( );
                
                auto swapChain = factory.CreateSwapChainForHwnd( queue_, windowHandle, &swapChainDesc );

                factory.MakeWindowAssociation( windowHandle, DXGI_MWA_NO_ALT_ENTER );

                swapChain_ = swapChain.As<DXGI::SwapChain3>( );

                bufferIndex_ = swapChain_.GetCurrentBackBufferIndex( );

                sampleCount_ = displayParams_.MSAASampleCount();

                SetupSurfaces( width, height );

                for ( int i = 0; i < NumFrames; ++i )
                {
                    fenceValues_[i] = 10000;
                }

                fence_ = device_.CreateFence( fenceValues_[bufferIndex_], D3D12_FENCE_FLAG_NONE );
            }
        }

        void SetupSurfaces( int width, int height )
        {
            width = std::max( width, MinSurfaceSize.Width() );
            height = std::max( height, MinSurfaceSize.Height() );
            // set up base resource info
            GrD3DTextureResourceInfo info( nullptr, nullptr, D3D12_RESOURCE_STATE_PRESENT, DXGI_FORMAT_R8G8B8A8_UNORM, 1, 1, 0 );
            for ( int i = 0; i < NumFrames; ++i )
            {
                buffers_[i] = swapChain_.GetBuffer<D3D12Resource>( i );
#ifdef _DEBUG
                auto desc = buffers_[i].GetDesc( );
                SkASSERT( desc.Width == (UINT64)width && desc.Height == (UINT64)height );
#else
                SkASSERT( buffers_[i].GetDesc( ).Width == (UINT64)width && buffers_[i]->GetDesc( ).Height == (UINT64)height );
#endif
                auto& surfaceProps = displayParams_.SurfaceProps( );

                info.fResource.retain( buffers_[i].GetInterfacePointer<ID3D12Resource>() );
                if ( sampleCount_ > 1 )
                {
                    GrBackendTexture backendTexture( width, height, info );
                    surfaces_[i] = SkSurface::MakeFromBackendTexture( directContext_.get( ), backendTexture, kTopLeft_GrSurfaceOrigin, sampleCount_, kRGBA_8888_SkColorType, displayParams_.ColorSpace(), &surfaceProps );
                }
                else
                {
                    GrBackendRenderTarget backendRT( width, height, info );
                    surfaces_[i] = SkSurface::MakeFromBackendRenderTarget( directContext_.get( ), backendRT, kTopLeft_GrSurfaceOrigin, kRGBA_8888_SkColorType, displayParams_.ColorSpace( ), &surfaceProps );
                }
            }
        }

        void DestroyContext( )
        {
            fence_.ResetPtr( );

            for ( int i = 0; i < NumFrames; ++i )
            {
                surfaces_[i].reset( nullptr );
                buffers_[i].ResetPtr( );
            }

            swapChain_.ResetPtr( );
            queue_.ResetPtr( );
            device_.ResetPtr( );
        }

        sk_sp<SkSurface> GetBackbufferSurface( )
        {
            const UINT64 currentFenceValue = fenceValues_[bufferIndex_];
            bufferIndex_ = swapChain_.GetCurrentBackBufferIndex( );

            if ( fence_.GetCompletedValue( ) < fenceValues_[bufferIndex_] )
            {
                fence_.SetEventOnCompletion( fenceValues_[bufferIndex_], fenceEvent_.GetHandle() );
                fenceEvent_.Wait( );
            }

            // Set the fence value for the next frame.
            fenceValues_[bufferIndex_] = currentFenceValue + 1;

            return surfaces_[bufferIndex_];
        }

        void SwapBuffers( )
        {
            SkSurface* surface = surfaces_[bufferIndex_].get( );

            GrFlushInfo info;
            surface->flush( SkSurface::BackendSurfaceAccess::kPresent, info );
            directContext_->submit( );

            swapChain_.Present( 1, 0 );

            // Schedule a Signal command in the queue.
            queue_.Signal( fence_, fenceValues_[bufferIndex_] );
        }

        void Resize( )
        {
            RECT clientRect{};
            control_.GetClientRect( clientRect );

            Int32 width = static_cast<Int32>( clientRect.right - clientRect.left );
            Int32 height = static_cast<Int32>( clientRect.bottom - clientRect.top );


            // Clean up any outstanding resources in command lists
            directContext_->flush( {} );
            directContext_->submit( true );

            // release the previous surface and backbuffer resources
            for ( int i = 0; i < NumFrames; ++i )
            {
                // Let present complete
                if ( fence_.GetCompletedValue( ) < fenceValues_[i] )
                {
                    fence_.SetEventOnCompletion( fenceValues_[i], fenceEvent_.GetHandle() );
                    fenceEvent_.Wait( );
                }
                surfaces_[i].reset( nullptr );
                buffers_[i].ResetPtr( );
            }

            swapChain_.ResizeBuffers( 0, width, height, DXGI_FORMAT_UNKNOWN, 0 );

            SetupSurfaces( width, height );
        }

        void SetDisplayParams( const SkiaDisplayParams& params )
        {
            DestroyContext( );
            displayParams_ = params;
            InitializeContext( );
        }
    };


    class SkiaControl : public Control
    {
        using Base = Harlinn::Windows::Control;
        using SkiaContext = Harlinn::Windows::SkiaContext<SkiaControl>;
    private:
        SkiaContext skiaContext_;
        bool doOnBeforeFirstRenderCalled_ = false;
    public:
        boost::signals2::signal<void( Control* sender, SkCanvas* canvas )> OnRender;
        boost::signals2::signal<void( Control* sender, SkCanvas* canvas )> OnBeforeFirstRender;

        SkiaControl( )
            : Base( ), skiaContext_( *this, SkiaDisplayParams( ) )
        {
        }

        void DoOnPaint( Harlinn::Windows::Message& message ) override
        {
            PAINTSTRUCT ps{};
            BeginPaint( ps );

            sk_sp<SkSurface> backbuffer = skiaContext_.GetBackbufferSurface( );

            auto canvas = backbuffer->getCanvas( );

            if ( !doOnBeforeFirstRenderCalled_ )
            {
                doOnBeforeFirstRenderCalled_ = true;
                this->DoOnBeforeFirstRender( canvas );
            }
            this->DoOnRender( canvas );

            backbuffer->flushAndSubmit( );

            skiaContext_.SwapBuffers( );

            EndPaint( ps );
            message.handled = true;

        }

        virtual void DoOnRender( SkCanvas* canvas )
        {
            OnRender( this, canvas );
        }

        virtual void DoOnBeforeFirstRender( SkCanvas* canvas )
        {
            OnBeforeFirstRender( this, canvas );
        }

    };
}

#endif
