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


#include "EWDX2D02Primitives.h"

#include <HWApplication.h>
#include "HWForm.h"
#include "HWMenu.h"
#include "HCCDatetime.h"
#include "HWGraphics.h"
#include "HWImaging.h"

using namespace Harlinn::Windows;
#pragma comment(lib, "D3D11.lib")
class Direct2D
{
    D3D_FEATURE_LEVEL featureLevel_ = D3D_FEATURE_LEVEL_9_2;
    using DX3DDevice = ID3D11Device;
    UnknownPtr<DX3DDevice> d3dDevice_;
    Graphics::Factory7 factory_;
    Graphics::Device6 device_;

    
public:
    Direct2D( )
        : factory_( D2D1_FACTORY_TYPE_SINGLE_THREADED )
    {
    }



    void InitializeDX( )
    {
        UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT | D3D11_CREATE_DEVICE_DEBUG;


        D3D_FEATURE_LEVEL featureLevels[] =
        {
            D3D_FEATURE_LEVEL_11_1,
            D3D_FEATURE_LEVEL_11_0,
            D3D_FEATURE_LEVEL_10_1,
            D3D_FEATURE_LEVEL_10_0,
            D3D_FEATURE_LEVEL_9_3,
            D3D_FEATURE_LEVEL_9_2,
            D3D_FEATURE_LEVEL_9_1
        };


        auto hr = D3D11CreateDevice(
            nullptr,                    // specify null to use the default adapter
            D3D_DRIVER_TYPE_HARDWARE,
            0,
            creationFlags,              // optionally set debug and Direct2D compatibility flags
            featureLevels,              // list of feature levels this app can support
            ARRAYSIZE( featureLevels ),   // number of possible feature levels
            D3D11_SDK_VERSION,
            &d3dDevice_,                    // returns the Direct3D device created
            &featureLevel_,            // returns feature level of device created
            nullptr );                    // returns the device immediate context

        CheckHRESULT( hr );
    }


    void InitializeDXGI( )
    {
        DXGI::Device1 dxgiDevice = d3dDevice_.As<DXGI::Device1>( );
        // Ensure that DXGI doesn't queue more than one frame at a time.
        dxgiDevice.SetMaximumFrameLatency( 1 );
        device_ = factory_.CreateDevice( dxgiDevice );
    }

    void Initialize( )
    {
        InitializeDX( );
        InitializeDXGI( );
    }


    Graphics::DeviceContext6 CreateDeviceContext( )
    {
        return device_.CreateDeviceContext( );
    }


    DXGI::SwapChain1 CreateSwapChain( Control* constrol )
    {
        DXGI_SWAP_CHAIN_DESC1 swapChainDesc{ 0, };
        swapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
        swapChainDesc.SampleDesc.Count = 1;
        swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swapChainDesc.BufferCount = 2;
        swapChainDesc.Scaling = DXGI_SCALING_NONE;
        swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;

        DXGI::Device1 dxgiDevice = d3dDevice_.As<DXGI::Device1>( );

        DXGI::Adapter dxgiAdapter = dxgiDevice.GetAdapter( );
        auto dxgiFactory = dxgiAdapter.GetParent<DXGI::Factory2>( );

        DXGI::SwapChain1 dxgiSwapChain;
        dxgiSwapChain = dxgiFactory.CreateSwapChainForHwnd<DXGI::SwapChain1>( dxgiDevice, constrol->GetHandle( ), &swapChainDesc );

        return dxgiSwapChain;
    }

};

class Direct2DControl
{
    Control* control_;
    Direct2D& direct2D_;
    DXGI::SwapChain1 dxgiSwapChain_;
    Graphics::DeviceContext6 deviceContext_;
public:
    Direct2DControl( Direct2D& direct2D, Control* control )
        : direct2D_( direct2D ), control_( control )
    {

    }

    const Graphics::DeviceContext6& DeviceContext( )
    {
        return deviceContext_;
    }

    void Reset( )
    {
        deviceContext_.ResetPtr( );
        dxgiSwapChain_.ResetPtr( );
    }
    void Present( )
    {
        dxgiSwapChain_.Present( 1, 0 );
    }
private:
    void InitializeDeviceContext( )
    {
        deviceContext_ = direct2D_.CreateDeviceContext( );
        deviceContext_.SetUnitMode( D2D1_UNIT_MODE_DIPS );
    }


    void InitializeSwapChain( )
    {
        dxgiSwapChain_ = direct2D_.CreateSwapChain( control_ );
    }

    void InitializeTargetBitmap( )
    {
        DXGI::Surface backBuffer = dxgiSwapChain_.GetBuffer<IDXGISurface>( 0 );

        auto bitmapProperties = D2D1::BitmapProperties1( D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
            D2D1::PixelFormat( DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_IGNORE ) );

        auto targetBitmap = deviceContext_.CreateBitmapFromDxgiSurface( backBuffer, bitmapProperties );
        deviceContext_.SetTarget( targetBitmap );
    }
public:
    void Initialize( )
    {
        InitializeDeviceContext( );
        InitializeSwapChain( );
        InitializeTargetBitmap( );
    }
    void Resize( )
    {
        if ( dxgiSwapChain_ )
        {
            deviceContext_.SetTarget( nullptr );
            dxgiSwapChain_.ResetPtr( );
            InitializeSwapChain( );
            InitializeTargetBitmap( );
        }
    }
};

namespace Primitives
{
    struct Primitive;
}
class MyForm : public Form
{

    Graphics::SolidColorBrush blackBrush_;
    Graphics::LinearGradientBrush backgroundBrush_;

    Direct2D direct2D_;
    Direct2DControl direct2DControl_;
    WideString titleText_;
    Primitives::Primitive* curretPrimitive_ = nullptr;
public:
    typedef Form Base;

    MyForm( );
    void SetCurrentPrimitive( Primitives::Primitive* primitive )
    {
        curretPrimitive_ = primitive;
    }
    void ResetCurrentPrimitive( )
    {
        curretPrimitive_ = nullptr;
    }

protected:
    virtual void DoOnInitialize( ) override;
    virtual void DoOnShown( ) override;
    virtual void DoOnDestroy( Message& message ) override;
    virtual void DoOnDisplayChange( Message& message ) override;
    virtual void DoOnPaint( Message& message ) override;
    virtual void DoOnSize( Message& message ) override;
private:
    void InitializeMenuBar( );

};
namespace Primitives
{
    struct Primitive
    {
        std::wstring title_;
        Primitive( const std::wstring& title )
            : title_( title )
        {
        }
        Primitive( const wchar_t* title )
            : title_( title )
        {
        }
        virtual void Render( const Graphics::DeviceContext6& deviceContext6, const Graphics::RectangleF& rect, const Graphics::Brush& brush ) = 0;
    };

    struct Rectangle : Primitive
    {
        Rectangle( )
            : Primitive( L"Rectangle" )
        {
        }
        void Render( const Graphics::DeviceContext6& deviceContext6, const Graphics::RectangleF& rect, const Graphics::Brush& brush ) override
        {
            float margin = 80;
            auto left = rect.Left() + margin;
            auto top = rect.Top( ) + margin;
            auto right = rect.Right( ) - margin;
            auto bottom = rect.Bottom( ) - margin;

            Graphics::RectangleF rectangleRect( left, top, right, bottom );

            deviceContext6.DrawRectangle( rectangleRect, brush, 5.0f );
        }
    };

    struct RoundedRectangle : Primitive
    {
        RoundedRectangle( )
            : Primitive( L"Rounded Rectangle" )
        {
        }
        void Render( const Graphics::DeviceContext6& deviceContext6, const Graphics::RectangleF& rect, const Graphics::Brush& brush ) override
        {
            float margin = 80;
            auto left = rect.Left( ) + margin;
            auto top = rect.Top( ) + margin;
            auto right = rect.Right( ) - margin;
            auto bottom = rect.Bottom( ) - margin;

            Graphics::RectangleF rectangleRect( left, top, right, bottom );

            D2D1_ROUNDED_RECT reoundedRect{ rectangleRect,25,25 };
            deviceContext6.DrawRoundedRectangle( reoundedRect, brush, 5.0f );
        }
    };
}


std::unique_ptr<Primitives::Primitive> primitives[] =
{
    std::make_unique<Primitives::Rectangle>(),
    std::make_unique<Primitives::RoundedRectangle>( )
};

size_t primitivesCount = sizeof( primitives ) / sizeof( std::unique_ptr<Primitives::Primitive> );




MyForm::MyForm( )
    : Base( ),
      direct2DControl_( direct2D_, this ),
      titleText_( L"Windows Development in C++ - DirectX2D Primitives" )
{
}




void MyForm::DoOnInitialize( )
{
    SetText( titleText_ ); 
    InitializeMenuBar( );
}


void MyForm::InitializeMenuBar( )
{
    MyForm* self = this;
    auto menuBar = std::make_unique<MenuBar>( );

    auto fileSubMenu = menuBar->AddSubMenu( L"&File" );

    fileSubMenu->AddMenuItem( L"E&xit", [self]( MenuItem* )
    {
        self->ResetCurrentPrimitive( );
        self->InvalidateRect( );
        self->Close( );
    } );

    auto primitivesSubMenu = menuBar->AddSubMenu( L"&Primitives" );

    for ( size_t i = 0; i < primitivesCount; i++ )
    {
        auto* primitive = primitives[i].get();
        primitivesSubMenu->AddMenuItem( primitive->title_.c_str(), [self, primitive]( MenuItem* )
        {
            self->SetCurrentPrimitive( primitive );
            self->InvalidateRect( );
        } );
    }

    SetMenu( std::move( menuBar ) );
}




void MyForm::DoOnShown( )
{
    Base::DoOnShown( );
    direct2D_.Initialize( );
    direct2DControl_.Initialize( );

    auto& deviceContext = direct2DControl_.DeviceContext( );

    blackBrush_ = deviceContext.CreateSolidColorBrush( D2D1::ColorF( D2D1::ColorF::Black ) );

    D2D1_GRADIENT_STOP gradientStops[2];
    gradientStops[0].color = D2D1::ColorF( D2D1::ColorF::White, 1 );
    gradientStops[0].position = 0.0f;
    gradientStops[1].color = D2D1::ColorF( D2D1::ColorF::DeepSkyBlue, 1 );
    gradientStops[1].position = 1.0f;

    Graphics::GradientStopCollection gradientStopCollection = deviceContext.CreateGradientStopCollection( gradientStops, 2, D2D1_GAMMA_2_2, D2D1_EXTEND_MODE_MIRROR );

    backgroundBrush_ = deviceContext.CreateLinearGradientBrush( D2D1::LinearGradientBrushProperties( Graphics::PointF( 0, 0 ), Graphics::PointF( 300, 300 ) ), gradientStopCollection );
}
void MyForm::DoOnDestroy( Message& message )
{
    Base::DoOnDestroy( message );
    blackBrush_.ResetPtr( );
    
    direct2DControl_.Reset( );
}

void MyForm::DoOnDisplayChange( Message& message )
{
    InvalidateRect( );
}

void MyForm::DoOnPaint( Message& message )
{
    Base::DoOnPaint( message );
    ValidateRect( );

    auto& deviceContext = direct2DControl_.DeviceContext( );
    auto size = deviceContext.GetSize( );
    float margin = 50;

    deviceContext.BeginDraw( );

    deviceContext.Clear( D2D1::ColorF( D2D1::ColorF::White ) );

    Graphics::RectangleF layoutRect( margin, margin, size.width - margin, size.height - margin );

    deviceContext.FillRectangle( layoutRect, backgroundBrush_ );

    if ( curretPrimitive_ )
    {
        curretPrimitive_->Render( deviceContext, layoutRect, blackBrush_ );
    }

    deviceContext.EndDraw( );

    direct2DControl_.Present( );
}

void MyForm::DoOnSize( Message& message )
{
    Base::DoOnSize( message );
    direct2DControl_.Resize( );
}


int APIENTRY wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow )
{

    try
    {
        auto application = std::make_shared<Harlinn::Windows::Application>( );
        application->Start( );

        UNREFERENCED_PARAMETER( hPrevInstance );
        UNREFERENCED_PARAMETER( lpCmdLine );
        SetThreadDpiAwarenessContext( DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2 );
        
        auto result = application->Run<MyForm>( );
        application->Stop( );
        return result;
    }
    catch ( std::exception& exc )
    {
        std::cout << exc.what( ) << std::endl;
    }
    catch ( ... )
    {

    }
    return 0;
}
