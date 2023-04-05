#include "pch.h"
#include <HWGraphics.h>
#include <HWImaging.h>
#include <HWControl.h>
#include <HWDocumentTarget.h>

namespace Harlinn::Windows::Graphics
{

    // ================================================================
    // RenderTarget
    // ================================================================
    void RenderTarget::CreateBitmapFromWicBitmap( const Imaging::BitmapSource& wicBitmapSource, _In_opt_ CONST D2D1_BITMAP_PROPERTIES* bitmapProperties, _COM_Outptr_ ID2D1Bitmap** bitmap ) const
    {
        CreateBitmapFromWicBitmap( wicBitmapSource.GetInterfacePointer<IWICBitmapSource>( ), bitmapProperties, bitmap );
    }
    void RenderTarget::CreateBitmapFromWicBitmap( const Imaging::BitmapSource& wicBitmapSource, const D2D1_BITMAP_PROPERTIES& bitmapProperties, _COM_Outptr_ ID2D1Bitmap** bitmap ) const
    {
        CreateBitmapFromWicBitmap( wicBitmapSource.GetInterfacePointer<IWICBitmapSource>( ), &bitmapProperties, bitmap );
    }
    Bitmap RenderTarget::CreateBitmapFromWicBitmap( const Imaging::BitmapSource& wicBitmapSource, const D2D1_BITMAP_PROPERTIES* bitmapProperties ) const
    {
        return CreateBitmapFromWicBitmap( wicBitmapSource.GetInterfacePointer<IWICBitmapSource>( ), bitmapProperties );
    }
    Bitmap RenderTarget::CreateBitmapFromWicBitmap( const Imaging::BitmapSource& wicBitmapSource, const D2D1_BITMAP_PROPERTIES& bitmapProperties ) const
    {
        return CreateBitmapFromWicBitmap( wicBitmapSource.GetInterfacePointer<IWICBitmapSource>( ), &bitmapProperties );
    }


    // ================================================================
    // Factory
    // ================================================================

    ControlRenderTarget Factory::CreateHwndRenderTarget( Control& control ) const
    {
        return CreateControlRenderTarget( control );
    }
    ControlRenderTarget Factory::CreateHwndRenderTarget( HWND hwnd ) const
    {
        return CreateControlRenderTarget( hwnd );
    }

    ControlRenderTarget Factory::CreateControlRenderTarget( Control& control ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HWND hwnd = control.GetHandle( );
        RECT rect;
        control.GetClientRect( rect );

        auto size = D2D1::SizeU( rect.right - rect.left, rect.bottom - rect.top );

        ID2D1HwndRenderTarget* pRenderTarget = nullptr;
        HRESULT hr = pInterface->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties( ),
            D2D1::HwndRenderTargetProperties( hwnd, size ), &pRenderTarget );
        HCC_COM_CHECK_HRESULT2( hr, pInterface );

        ControlRenderTarget result( pRenderTarget );
        return result;

    }

    ControlRenderTarget Factory::CreateControlRenderTarget( HWND hwnd ) const
    {
        InterfaceType* pInterface = GetInterface( );
        RECT rect;
        if ( GetClientRect( hwnd, &rect ) == FALSE )
        {
            ThrowLastOSError( );
        }

        ID2D1HwndRenderTarget* pRenderTarget = nullptr;
        HRESULT hr = pInterface->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties( ),
            D2D1::HwndRenderTargetProperties( hwnd, D2D1::SizeU( rect.right - rect.left, rect.bottom - rect.top ) ), &pRenderTarget );
        HCC_COM_CHECK_HRESULT2( hr, pInterface );

        ControlRenderTarget result( pRenderTarget );
        return result;
    }

    // ================================================================
    // DeviceContext
    // ================================================================
    void DeviceContext::CreateBitmapFromWicBitmap( const Imaging::BitmapSource& wicBitmapSource, D2D1_BITMAP_PROPERTIES1* bitmapProperties, ID2D1Bitmap1** bitmap ) const
    {
        CreateBitmapFromWicBitmap( wicBitmapSource.GetInterfacePointer<IWICBitmapSource>( ), bitmapProperties, bitmap );
    }
    void DeviceContext::CreateBitmapFromWicBitmap( const Imaging::BitmapSource& wicBitmapSource, D2D1_BITMAP_PROPERTIES1& bitmapProperties, ID2D1Bitmap1** bitmap ) const
    {
        CreateBitmapFromWicBitmap( wicBitmapSource.GetInterfacePointer<IWICBitmapSource>( ), &bitmapProperties, bitmap );
    }
    void DeviceContext::CreateBitmapFromWicBitmap( const Imaging::BitmapSource& wicBitmapSource, ID2D1Bitmap1** bitmap ) const
    {
        CreateBitmapFromWicBitmap( wicBitmapSource.GetInterfacePointer<IWICBitmapSource>( ), nullptr, bitmap );
    }
    Bitmap1 DeviceContext::CreateBitmapFromWicBitmap( const Imaging::BitmapSource& wicBitmapSource, D2D1_BITMAP_PROPERTIES1* bitmapProperties ) const
    {
        return CreateBitmapFromWicBitmap( wicBitmapSource.GetInterfacePointer<IWICBitmapSource>( ), bitmapProperties );
    }
    Bitmap1 DeviceContext::CreateBitmapFromWicBitmap( const Imaging::BitmapSource& wicBitmapSource, D2D1_BITMAP_PROPERTIES1& bitmapProperties ) const
    {
        return CreateBitmapFromWicBitmap( wicBitmapSource.GetInterfacePointer<IWICBitmapSource>( ), &bitmapProperties );
    }
    void DeviceContext::CreateColorContextFromWicColorContext( const Imaging::ColorContext& wicColorContext, ID2D1ColorContext** colorContext ) const
    {
        CreateColorContextFromWicColorContext( wicColorContext.GetInterfacePointer<IWICColorContext>( ), colorContext );
    }
    ColorContext DeviceContext::CreateColorContextFromWicColorContext( const Imaging::ColorContext& wicColorContext ) const
    {
        return CreateColorContextFromWicColorContext( wicColorContext.GetInterfacePointer<IWICColorContext>( ) );
    }

    // ================================================================
    // Device
    // ================================================================
    void Device::CreatePrintControl( const Imaging::ImagingFactory& wicFactory, const DocumentTarget::PrintDocumentPackageTarget& documentTarget, const D2D1_PRINT_CONTROL_PROPERTIES* printControlProperties, ID2D1PrintControl** printControl ) const
    {
        CreatePrintControl( wicFactory.GetInterfacePointer<IWICImagingFactory>( ), documentTarget.GetInterfacePointer<IPrintDocumentPackageTarget>( ), printControlProperties, printControl );
    }

    PrintControl Device::CreatePrintControl( const Imaging::ImagingFactory& wicFactory, const DocumentTarget::PrintDocumentPackageTarget& documentTarget, const D2D1_PRINT_CONTROL_PROPERTIES* printControlProperties ) const
    {
        return CreatePrintControl( wicFactory.GetInterfacePointer<IWICImagingFactory>( ), documentTarget.GetInterfacePointer<IPrintDocumentPackageTarget>( ), printControlProperties );
    }

    // ================================================================
    // ImageSourceFromWic
    // ================================================================
    Imaging::BitmapSource ImageSourceFromWic::GetSource( ) const
    {
        IWICBitmapSource* ptr = nullptr;
        GetSource( &ptr );
        return Imaging::BitmapSource( ptr );
    }
    // ================================================================
    // DeviceContext2
    // ================================================================
    void DeviceContext2::CreateImageSourceFromWic( const Imaging::BitmapSource& wicBitmapSource, D2D1_IMAGE_SOURCE_LOADING_OPTIONS loadingOptions, D2D1_ALPHA_MODE alphaMode, ID2D1ImageSourceFromWic** imageSource ) const
    {
        CreateImageSourceFromWic( wicBitmapSource.GetInterfacePointer<IWICBitmapSource>( ), loadingOptions, alphaMode, imageSource );
    }
    ImageSourceFromWic DeviceContext2::CreateImageSourceFromWic( const Imaging::BitmapSource& wicBitmapSource, D2D1_IMAGE_SOURCE_LOADING_OPTIONS loadingOptions, D2D1_ALPHA_MODE alphaMode ) const
    {
        return CreateImageSourceFromWic( wicBitmapSource.GetInterfacePointer<IWICBitmapSource>( ), loadingOptions, alphaMode );
    }


}