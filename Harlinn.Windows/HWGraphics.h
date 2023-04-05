#pragma once
#ifndef __HWGRAPHICS_H__
#define __HWGRAPHICS_H__

#include <HWDef.h>
#include <HCCCOM.h>
#include <HCCObjBase.h>
#include <HCCException.h>
#include <HWCommon.h>
#include <HWDXGI.h>

#pragma comment(lib,"D2d1.lib")
#pragma comment(lib,"Dwrite.lib")

namespace Harlinn::Windows
{
    class Control;
}
namespace Harlinn::Windows::DXGI
{
    class Surface;
}

namespace Harlinn::Windows::DirectWrite
{
    class RenderingParams;
    class TextFormat;
    class TextLayout;
    class FontFace;
}

namespace Harlinn::Windows::Imaging
{
    class BitmapSource;
    class ColorContext;
    class ImagingFactory;
}

namespace Harlinn::Windows::DocumentTarget
{
    class PrintDocumentPackageTarget;
}

namespace Harlinn::Windows::Graphics
{
    namespace hcc = Harlinn::Common::Core;

#define COMMON_GRAPHICS_STANDARD_METHODS_IMPL( classType, baseClassType , interfaceType, baseInterfaceType ) HCC_COM_STANDARD_METHODS_IMPL(classType, baseClassType , interfaceType, baseInterfaceType)



    class Factory;
    class BitmapRenderTarget;

    /// <summary>
    /// Represents a Direct2D drawing resource.
    /// </summary>
    class Resource : public Unknown
    {
    public:
        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( Resource, Unknown, ID2D1Resource, IUnknown )
    public:
        template<typename T = Factory>
        requires std::is_base_of_v< Factory, T>
        inline T GetFactory( )
        {
            InterfaceType* pInterface = GetInterface( );
            ID2D1Factory* pFactory = nullptr;
            pInterface->GetFactory( &pFactory );
            if ( pFactory )
            {
                return T( pFactory );
            }
            return T( );
        }
    };


    /// <summary>
    /// Represents a producer of pixels that can fill an arbitrary 2D plane.
    /// </summary>
    /// <remarks>
    /// <p>
    /// An Image is abstract. Concrete instances can be created through 
    /// DeviceContext::CreateEffect and DeviceContext::CreateBitmap.
    /// </p>
    /// <p>
    /// Images are evaluated lazily. If the type of image passed in is concrete, 
    /// then the image can be directly sampled from. Other images can act only as 
    /// a source of pixels and can produce content only as a result of calling 
    /// DeviceContext::DrawImage.
    /// </p>
    /// </remarks>
    class Image : public Resource
    {
    public:
        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( Image, Resource, ID2D1Image, ID2D1Resource )
    };

    /// <summary>
    /// Represents a color context that can be used with an Bitmap object.
    /// </summary>
    class ColorContext : public Resource
    {
    public:
        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( ColorContext, Resource, ID2D1ColorContext, ID2D1Resource )

        /// <summary>
        /// Retrieves the color space of the color context.
        /// </summary>
        D2D1_COLOR_SPACE GetColorSpace( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetColorSpace( );
        }

        /// <summary>
        /// Retrieves the size of the color profile, in bytes.
        /// </summary>
        UINT32 GetProfileSize( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetProfileSize( );
        }

        /// <summary>
        /// Retrieves the color profile bytes.
        /// </summary>
        void GetProfile( BYTE* profile, UINT32 profileSize ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetProfile( profile, profileSize );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };


    /// <summary>
    /// Represents a bitmap that has been bound to a RenderTarget.
    /// </summary>
    class Bitmap : public Image
    {
    public:
        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( Bitmap, Image, ID2D1Bitmap, ID2D1Image )


        //
        // Returns the size of the bitmap in resolution independent units.
        //
        D2D1_SIZE_F GetSize( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetSize( );
        }


        //
        // Returns the size of the bitmap in resolution dependent units, (pixels).
        //
        D2D1_SIZE_U GetPixelSize( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetPixelSize( );
        }


        //
        // Retrieve the format of the bitmap.
        //
        D2D1_PIXEL_FORMAT GetPixelFormat( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetPixelFormat( );
        }


        //
        // Return the DPI of the bitmap.
        //
        void GetDpi( FLOAT* dpiX, FLOAT* dpiY ) const
        {
#ifdef _DEBUG
            CheckPointerNotNull( dpiX );
            CheckPointerNotNull( dpiY );
#endif
            InterfaceType* pInterface = GetInterface( );
            pInterface->GetDpi( dpiX, dpiY );
        }

        void GetDpi( FLOAT& dpiX, FLOAT& dpiY ) const
        {
            GetDpi( &dpiX, &dpiY );
        }

        D2D1_SIZE_F GetDpi( ) const
        {
            D2D1_SIZE_F result = { 0, };
            GetDpi( result.width, result.height );
            return result;
        }

        void CopyFromBitmap( const D2D1_POINT_2U* destPoint, ID2D1Bitmap* bitmap, const D2D1_RECT_U* srcRect ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->CopyFromBitmap( destPoint, bitmap, srcRect );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void CopyFromRenderTarget( const D2D1_POINT_2U* destPoint, ID2D1RenderTarget* renderTarget, const D2D1_RECT_U* srcRect ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->CopyFromRenderTarget( destPoint, renderTarget, srcRect );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void CopyFromMemory( const D2D1_RECT_U* dstRect, const void* srcData, UINT32 pitch ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->CopyFromMemory( dstRect, srcData, pitch );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

    };

    /// <summary>
    /// Represents a collection of D2D1_GRADIENT_STOP objects for linear and radial gradient brushes.
    /// </summary>
    class GradientStopCollection : public Resource
    {
    public:
        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( GradientStopCollection, Resource, ID2D1GradientStopCollection, ID2D1Resource )


        //
        // Returns the number of stops in the gradient.
        //
        UINT32 GetGradientStopCount( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetGradientStopCount( );
        }


        //
        // Copies the gradient stops from the collection into the caller's interface.  The
        // returned colors have straight alpha.
        //
        void GetGradientStops( D2D1_GRADIENT_STOP* gradientStops, UINT32 gradientStopsCount ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->GetGradientStops( gradientStops, gradientStopsCount );
        }


        //
        // Returns whether the interpolation occurs with 1.0 or 2.2 gamma.
        //
        D2D1_GAMMA GetColorInterpolationGamma( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetColorInterpolationGamma( );
        }

        D2D1_EXTEND_MODE GetExtendMode( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetExtendMode( );
        }

    };

    /// <summary>
    /// Defines an object that paints an area. Interfaces that derive from 
    /// ID2D1Brush describe how the area is painted.
    /// </summary>
    class Brush : public Resource
    {
    public:
        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( Brush, Resource, ID2D1Brush, ID2D1Resource )


        //
        // Sets the opacity for when the brush is drawn over the entire fill of the brush.
        //
        void SetOpacity( FLOAT opacity ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetOpacity( opacity );
        }

        FLOAT GetOpacity( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetOpacity( );
        }

        //
        // Sets the transform that applies to everything drawn by the brush.
        //
        void SetTransform( const D2D1_MATRIX_3X2_F* transform ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetTransform( transform );
        }

        void SetTransform( const D2D1_MATRIX_3X2_F& transform ) const
        {
            SetTransform( &transform );
        }

        

        void GetTransform( D2D1_MATRIX_3X2_F* transform ) const
        {
            CheckPointerNotNull( transform );
            InterfaceType* pInterface = GetInterface( );
            pInterface->GetTransform( transform );
        }
    };

    /// <summary>
    /// Paints an area with a bitmap.
    /// </summary>
    class BitmapBrush : public Brush
    {
    public:
        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( BitmapBrush, Brush, ID2D1BitmapBrush, ID2D1Brush )

        //
        // Sets how the bitmap is to be treated outside of its natural extent on the X
        // axis.
        //
        void SetExtendModeX( D2D1_EXTEND_MODE extendModeX ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetExtendModeX( extendModeX );
        }


        //
        // Sets how the bitmap is to be treated outside of its natural extent on the X
        // axis.
        //
        void SetExtendModeY( D2D1_EXTEND_MODE extendModeY ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetExtendModeY( extendModeY );
        }


        //
        // Sets the interpolation mode used when this brush is used.
        //
        void SetInterpolationMode( D2D1_BITMAP_INTERPOLATION_MODE interpolationMode ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetInterpolationMode( interpolationMode );
        }


        //
        // Sets the bitmap associated as the source of this brush.
        //
        void SetBitmap( ID2D1Bitmap* bitmap ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetBitmap( bitmap );
        }
        template<typename T>
        requires std::is_base_of_v<Bitmap,T>
        void SetBitmap( const T& bitmap ) const
        {
            SetBitmap( bitmap.GetInterfacePointer<ID2D1Bitmap>() );
        }

        D2D1_EXTEND_MODE GetExtendModeX( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetExtendModeX( );
        }

        D2D1_EXTEND_MODE GetExtendModeY( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetExtendModeY( );
        }

        D2D1_BITMAP_INTERPOLATION_MODE GetInterpolationMode( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetInterpolationMode( );
        }

        void GetBitmap( _Outptr_result_maybenull_ ID2D1Bitmap** bitmap ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->GetBitmap( bitmap );
        }

        template<typename T = Bitmap>
        requires std::is_base_of_v<Bitmap,T>
        T GetBitmap( ) const
        {
            typename T::InterfaceType* ptr = nullptr;
            GetBitmap( (ID2D1Bitmap**)&ptr );
            return T( ptr );
        }

    };


    /// <summary>
    /// Paints an area with a solid color.
    /// </summary>
    class SolidColorBrush : public Brush
    {
    public:
        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( SolidColorBrush, Brush, ID2D1SolidColorBrush, ID2D1Brush )

        void SetColor( const D2D1_COLOR_F* color ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetColor( color );
        }

        D2D1_COLOR_F GetColor( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetColor( );
        }

        void SetColor( const D2D1_COLOR_F& color ) const
        {
            SetColor( &color );
        }
    };


    /// <summary>
    /// Paints an area with a linear gradient.
    /// </summary>
    class LinearGradientBrush : public Brush
    {
    public:
        typedef Brush Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( LinearGradientBrush, Brush, ID2D1LinearGradientBrush, ID2D1Brush )

        void SetStartPoint( D2D1_POINT_2F startPoint ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetStartPoint( startPoint );
        }


        //
        // Sets the end point of the gradient in local coordinate space. This is not
        // influenced by the geometry being filled.
        //
        void SetEndPoint( D2D1_POINT_2F endPoint ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetEndPoint( endPoint );
        }

        D2D1_POINT_2F GetStartPoint( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetStartPoint( );
        }

        D2D1_POINT_2F GetEndPoint( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetEndPoint( );
        }

        void GetGradientStopCollection( _Outptr_ ID2D1GradientStopCollection** gradientStopCollection ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->GetGradientStopCollection( gradientStopCollection );
        }

        template <typename T = GradientStopCollection>
            requires std::is_base_of_v<GradientStopCollection,T>
        T GetGradientStopCollection( ) const
        {
            typename T::InterfaceType* ptr = nullptr;
            GetBitmap( (ID2D1GradientStopCollection**)&ptr );
            return T( ptr );
        }

    };

    /// <summary>
    /// Paints an area with a radial gradient.
    /// </summary>
    class RadialGradientBrush : public Brush
    {
    public:
        typedef Brush Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( RadialGradientBrush, Brush, ID2D1RadialGradientBrush, ID2D1Brush )

        //
        // Sets the center of the radial gradient. This will be in local coordinates and
        // will not depend on the geometry being filled.
        //
        void SetCenter( D2D1_POINT_2F center ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetCenter( center );
        }


        //
        // Sets offset of the origin relative to the radial gradient center.
        //
        void SetGradientOriginOffset( D2D1_POINT_2F gradientOriginOffset ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetGradientOriginOffset( gradientOriginOffset );
        }

        void SetRadiusX( FLOAT radiusX ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetRadiusX( radiusX );
        }

        void SetRadiusY( FLOAT radiusY ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetRadiusY( radiusY );
        }

        D2D1_POINT_2F GetCenter( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetCenter( );
        }

        D2D1_POINT_2F GetGradientOriginOffset( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetGradientOriginOffset( );
        }

        FLOAT GetRadiusX( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetRadiusX( );
        }

        FLOAT GetRadiusY( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetRadiusY( );
        }

        void GetGradientStopCollection( _Outptr_ ID2D1GradientStopCollection** gradientStopCollection ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->GetGradientStopCollection( gradientStopCollection );
        }

        template <typename T = GradientStopCollection>
            requires std::is_base_of_v<GradientStopCollection, T>
        T GetGradientStopCollection( ) const
        {
            typename T::InterfaceType* ptr = nullptr;
            GetBitmap( (ID2D1GradientStopCollection**)&ptr );
            return T( ptr );
        }

    };

    /// <summary>
    /// Describes the caps, miter limit, line join, and dash information for a stroke.
    /// </summary>
    class StrokeStyle : public Resource
    {
    public:
        typedef Resource Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( StrokeStyle, Resource, ID2D1StrokeStyle, ID2D1Resource )

        D2D1_CAP_STYLE GetStartCap( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetStartCap( );
        }

        D2D1_CAP_STYLE GetEndCap( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetEndCap( );
        }

        D2D1_CAP_STYLE GetDashCap( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetDashCap( );
        }

        FLOAT GetMiterLimit( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetMiterLimit( );
        }

        D2D1_LINE_JOIN GetLineJoin( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetLineJoin( );
        }

        FLOAT GetDashOffset( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetDashOffset( );
        }

        D2D1_DASH_STYLE GetDashStyle( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetDashStyle( );
        }

        UINT32 GetDashesCount( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetDashesCount( );
        }

        //
        // Returns the dashes from the object into a user allocated array. The user must
        // call GetDashesCount to retrieve the required size.
        //
        void GetDashes( FLOAT* dashes, UINT32 dashesCount ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->GetDashes( dashes, dashesCount );
        }

    };


    /// <summary>
    /// Represents a geometry resource and defines a set of helper methods 
    /// for manipulating and measuring geometric shapes. Interfaces that 
    /// inherit from ID2D1Geometry define specific shapes.
    /// </summary>
    class Geometry : public Resource
    {
    public:
        typedef Resource Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( Geometry, Resource, ID2D1Geometry, ID2D1Resource )

        //
        // Retrieve the bounds of the geometry, with an optional applied transform.
        //
        void GetBounds( const D2D1_MATRIX_3X2_F* worldTransform, D2D1_RECT_F* bounds ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetBounds( worldTransform, bounds );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        D2D1_RECT_F GetBounds( const D2D1_MATRIX_3X2_F* worldTransform = nullptr ) const
        {
            D2D1_RECT_F result;
            GetBounds( worldTransform, &result );
            return result;
        }
        D2D1_RECT_F GetBounds( const D2D1_MATRIX_3X2_F& worldTransform )
        {
            return GetBounds( &worldTransform );
        }



        /// <summary>
        /// Gets the bounds of the geometry after it has been widened by the specified 
        /// stroke width and style and transformed by the specified matrix.
        /// </summary>
        /// <param name="strokeWidth">
        /// The amount by which to widen the geometry by stroking its outline.
        /// </param>
        /// <param name="strokeStyle">
        /// The style of the stroke that widens the geometry.
        /// </param>
        /// <param name="worldTransform">
        /// A transform to apply to the geometry after the geometry is transformed and after the geometry has been stroked.
        /// </param>
        /// <param name="flatteningTolerance">
        /// The maximum error allowed when constructing a polygonal approximation of the 
        /// geometry. No point in the polygonal representation will diverge from the original 
        /// geometry by more than the flattening tolerance. Smaller values produce more 
        /// accurate results but cause slower execution.
        /// </param>
        /// <param name="bounds">
        /// When this method returns, contains the bounds of the widened geometry. 
        /// You must allocate storage for this parameter.
        /// </param>
        void GetWidenedBounds( FLOAT strokeWidth, ID2D1StrokeStyle* strokeStyle, const D2D1_MATRIX_3X2_F* worldTransform, FLOAT flatteningTolerance, D2D1_RECT_F* bounds ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetWidenedBounds( strokeWidth, strokeStyle, worldTransform, flatteningTolerance, bounds );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void GetWidenedBounds( FLOAT strokeWidth, const StrokeStyle& strokeStyle, const D2D1_MATRIX_3X2_F* worldTransform, FLOAT flatteningTolerance, D2D1_RECT_F* bounds ) const
        {
            return GetWidenedBounds( strokeWidth, strokeStyle.GetInterfacePointer<ID2D1StrokeStyle>(), worldTransform, flatteningTolerance, bounds );
        }

        D2D1_RECT_F GetWidenedBounds( FLOAT strokeWidth, ID2D1StrokeStyle* strokeStyle, const D2D1_MATRIX_3X2_F* worldTransform, FLOAT flatteningTolerance = D2D1_DEFAULT_FLATTENING_TOLERANCE ) const
        {
            D2D1_RECT_F result;
            GetWidenedBounds( strokeWidth, strokeStyle, worldTransform, flatteningTolerance, &result );
            return result;
        }
        D2D1_RECT_F GetWidenedBounds( FLOAT strokeWidth, ID2D1StrokeStyle* strokeStyle, const D2D1_MATRIX_3X2_F& worldTransform, FLOAT flatteningTolerance = D2D1_DEFAULT_FLATTENING_TOLERANCE ) const
        {
            return GetWidenedBounds( strokeWidth, strokeStyle, &worldTransform, flatteningTolerance );
        }

        D2D1_RECT_F GetWidenedBounds( FLOAT strokeWidth, const StrokeStyle& strokeStyle, const D2D1_MATRIX_3X2_F* worldTransform, FLOAT flatteningTolerance = D2D1_DEFAULT_FLATTENING_TOLERANCE ) const
        {
            D2D1_RECT_F result;
            GetWidenedBounds( strokeWidth, strokeStyle, worldTransform, flatteningTolerance, &result );
            return result;
        }
        D2D1_RECT_F GetWidenedBounds( FLOAT strokeWidth, const StrokeStyle& strokeStyle, const D2D1_MATRIX_3X2_F& worldTransform, FLOAT flatteningTolerance = D2D1_DEFAULT_FLATTENING_TOLERANCE ) const
        {
            return GetWidenedBounds( strokeWidth, strokeStyle, &worldTransform, flatteningTolerance );
        }



        /// <summary>
        /// Determines whether the geometry's stroke contains the specified point given the specified stroke thickness, style, and transform.
        /// </summary>
        /// <param name="point">
        /// The point to test for containment.
        /// </param>
        /// <param name="strokeWidth">
        /// The thickness of the stroke to apply.
        /// </param>
        /// <param name="strokeStyle">
        /// The style of stroke to apply.
        /// </param>
        /// <param name="worldTransform">
        /// The transform to apply to the stroked geometry.
        /// </param>
        /// <param name="flatteningTolerance">
        /// The numeric accuracy with which the precise geometric path and path 
        /// intersection is calculated. Points missing the stroke by less than 
        /// the tolerance are still considered inside. Smaller values produce more 
        /// accurate results but cause slower execution.
        /// </param>
        /// <param name="contains"></param>
        void StrokeContainsPoint( D2D1_POINT_2F point, FLOAT strokeWidth, ID2D1StrokeStyle* strokeStyle, const D2D1_MATRIX_3X2_F* worldTransform, FLOAT flatteningTolerance, BOOL* contains ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->StrokeContainsPoint( point, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, contains );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void StrokeContainsPoint( D2D1_POINT_2F point, FLOAT strokeWidth, ID2D1StrokeStyle* strokeStyle, const D2D1_MATRIX_3X2_F& worldTransform, FLOAT flatteningTolerance, BOOL* contains ) const
        {
            StrokeContainsPoint( point, strokeWidth, strokeStyle, &worldTransform, flatteningTolerance, contains );
        }

        bool StrokeContainsPoint( D2D1_POINT_2F point, FLOAT strokeWidth, ID2D1StrokeStyle* strokeStyle, const D2D1_MATRIX_3X2_F* worldTransform, FLOAT flatteningTolerance = D2D1_DEFAULT_FLATTENING_TOLERANCE ) const
        {
            BOOL result = FALSE;
            StrokeContainsPoint( point, strokeWidth, strokeStyle, worldTransform, flatteningTolerance, &result );
            return result != FALSE;
        }
        bool StrokeContainsPoint( D2D1_POINT_2F point, FLOAT strokeWidth, ID2D1StrokeStyle* strokeStyle, const D2D1_MATRIX_3X2_F& worldTransform, FLOAT flatteningTolerance = D2D1_DEFAULT_FLATTENING_TOLERANCE ) const
        {
            return StrokeContainsPoint( point, strokeWidth, strokeStyle, &worldTransform, flatteningTolerance );
        }
        void StrokeContainsPoint( D2D1_POINT_2F point, FLOAT strokeWidth, const StrokeStyle& strokeStyle, const D2D1_MATRIX_3X2_F* worldTransform, FLOAT flatteningTolerance, BOOL* contains ) const
        {
            StrokeContainsPoint( point, strokeWidth, strokeStyle.GetInterfacePointer<ID2D1StrokeStyle>(), worldTransform, flatteningTolerance, contains );
        }
        void StrokeContainsPoint( D2D1_POINT_2F point, FLOAT strokeWidth, const StrokeStyle& strokeStyle, const D2D1_MATRIX_3X2_F& worldTransform, FLOAT flatteningTolerance, BOOL* contains ) const
        {
            StrokeContainsPoint( point, strokeWidth, strokeStyle.GetInterfacePointer<ID2D1StrokeStyle>( ), &worldTransform, flatteningTolerance, contains );
        }
        bool StrokeContainsPoint( D2D1_POINT_2F point, FLOAT strokeWidth, const StrokeStyle& strokeStyle, const D2D1_MATRIX_3X2_F* worldTransform, FLOAT flatteningTolerance = D2D1_DEFAULT_FLATTENING_TOLERANCE ) const
        {
            return StrokeContainsPoint( point, strokeWidth, strokeStyle.GetInterfacePointer<ID2D1StrokeStyle>( ), worldTransform, flatteningTolerance );
        }
        bool StrokeContainsPoint( D2D1_POINT_2F point, FLOAT strokeWidth, const StrokeStyle& strokeStyle, const D2D1_MATRIX_3X2_F& worldTransform, FLOAT flatteningTolerance = D2D1_DEFAULT_FLATTENING_TOLERANCE ) const
        {
            return StrokeContainsPoint( point, strokeWidth, strokeStyle.GetInterfacePointer<ID2D1StrokeStyle>( ), worldTransform, flatteningTolerance );
        }

        /// <summary>
        /// Indicates whether the area filled by the geometry would contain the specified 
        /// point given the specified flattening tolerance.
        /// </summary>
        /// <param name="point">
        /// The point to test.
        /// </param>
        /// <param name="worldTransform">
        /// The transform to apply to the geometry prior to testing for containment.
        /// </param>
        /// <param name="flatteningTolerance">
        /// The numeric accuracy with which the precise geometric path and path 
        /// intersection is calculated. Points missing the fill by less than the 
        /// tolerance are still considered inside. Smaller values produce more 
        /// accurate results but cause slower execution.
        /// </param>
        /// <param name="contains">
        /// When this method returns, contains a bool value that is true if the 
        /// area filled by the geometry contains point; otherwise, false. You must 
        /// allocate storage for this parameter.
        /// </param>
        void FillContainsPoint( D2D1_POINT_2F point, const D2D1_MATRIX_3X2_F* worldTransform, FLOAT flatteningTolerance, BOOL* contains ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->FillContainsPoint( point, worldTransform, flatteningTolerance, contains );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void FillContainsPoint( D2D1_POINT_2F point, const D2D1_MATRIX_3X2_F& worldTransform, FLOAT flatteningTolerance, BOOL* contains ) const
        {
            FillContainsPoint( point, &worldTransform, flatteningTolerance, contains );
        }
        bool FillContainsPoint( D2D1_POINT_2F point, const D2D1_MATRIX_3X2_F* worldTransform = nullptr, FLOAT flatteningTolerance = D2D1_DEFAULT_FLATTENING_TOLERANCE ) const
        {
            BOOL result = FALSE;
            FillContainsPoint( point, worldTransform, flatteningTolerance, &result );
            return result != FALSE;
        }
        bool FillContainsPoint( D2D1_POINT_2F point, const D2D1_MATRIX_3X2_F& worldTransform, FLOAT flatteningTolerance = D2D1_DEFAULT_FLATTENING_TOLERANCE ) const
        {
            return FillContainsPoint( point, &worldTransform, flatteningTolerance );
        }


        /// <summary>
        /// Describes the intersection between this geometry and the specified geometry. 
        /// The comparison is performed using the specified flattening tolerance.
        /// </summary>
        /// <param name="inputGeometry">
        /// The geometry to test.
        /// </param>
        /// <param name="inputGeometryTransform">
        /// The transform to apply to inputGeometry.
        /// </param>
        /// <param name="flatteningTolerance">
        /// The maximum error allowed when constructing a polygonal approximation of 
        /// the geometry. No point in the polygonal representation will diverge from 
        /// the original geometry by more than the flattening tolerance. Smaller values 
        /// produce more accurate results but cause slower execution.
        /// </param>
        /// <param name="relation">
        /// When this method returns, contains a pointer to a value that describes how 
        /// this geometry is related to inputGeometry. You must allocate storage for this parameter.
        /// </param>
        /// <remarks>
        /// When interpreting the returned relation value, it is important to remember that the 
        /// member D2D1_GEOMETRY_RELATION_IS_CONTAINED of the D2D1_GEOMETRY_RELATION enumeration 
        /// type means that this geometry is contained inside inputGeometry, not that this geometry 
        /// contains inputGeometry.
        /// </remarks>
        void CompareWithGeometry( ID2D1Geometry* inputGeometry, const D2D1_MATRIX_3X2_F* inputGeometryTransform, FLOAT flatteningTolerance, D2D1_GEOMETRY_RELATION* relation ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->CompareWithGeometry( inputGeometry, inputGeometryTransform, flatteningTolerance, relation );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void CompareWithGeometry( const Geometry& inputGeometry, const D2D1_MATRIX_3X2_F* inputGeometryTransform, FLOAT flatteningTolerance, D2D1_GEOMETRY_RELATION* relation ) const
        {
            CompareWithGeometry( inputGeometry.GetInterfacePointer<ID2D1Geometry>(), inputGeometryTransform, flatteningTolerance, relation );
        }
        D2D1_GEOMETRY_RELATION CompareWithGeometry( ID2D1Geometry* inputGeometry, const D2D1_MATRIX_3X2_F* inputGeometryTransform = nullptr, FLOAT flatteningTolerance = D2D1_DEFAULT_FLATTENING_TOLERANCE ) const
        {
            D2D1_GEOMETRY_RELATION result = D2D1_GEOMETRY_RELATION::D2D1_GEOMETRY_RELATION_UNKNOWN;
            CompareWithGeometry( inputGeometry, inputGeometryTransform, flatteningTolerance, &result );
            return result;
        }
        D2D1_GEOMETRY_RELATION CompareWithGeometry( const Geometry& inputGeometry, const D2D1_MATRIX_3X2_F* inputGeometryTransform = nullptr, FLOAT flatteningTolerance = D2D1_DEFAULT_FLATTENING_TOLERANCE ) const
        {
            D2D1_GEOMETRY_RELATION result = D2D1_GEOMETRY_RELATION::D2D1_GEOMETRY_RELATION_UNKNOWN;
            CompareWithGeometry( inputGeometry.GetInterfacePointer<ID2D1Geometry>( ), inputGeometryTransform, flatteningTolerance, &result );
            return result;
        }

        void CompareWithGeometry( ID2D1Geometry* inputGeometry, const D2D1_MATRIX_3X2_F& inputGeometryTransform, FLOAT flatteningTolerance, D2D1_GEOMETRY_RELATION* relation ) const
        {
            CompareWithGeometry( inputGeometry, &inputGeometryTransform, flatteningTolerance, relation );
        }
        void CompareWithGeometry( const Geometry& inputGeometry, const D2D1_MATRIX_3X2_F& inputGeometryTransform, FLOAT flatteningTolerance, D2D1_GEOMETRY_RELATION* relation ) const
        {
            CompareWithGeometry( inputGeometry, &inputGeometryTransform, flatteningTolerance, relation );
        }
        D2D1_GEOMETRY_RELATION CompareWithGeometry( ID2D1Geometry* inputGeometry, const D2D1_MATRIX_3X2_F& inputGeometryTransform, FLOAT flatteningTolerance = D2D1_DEFAULT_FLATTENING_TOLERANCE ) const
        {
            return CompareWithGeometry( inputGeometry, &inputGeometryTransform, flatteningTolerance );
        }
        D2D1_GEOMETRY_RELATION CompareWithGeometry( const Geometry& inputGeometry, const D2D1_MATRIX_3X2_F& inputGeometryTransform, FLOAT flatteningTolerance )
        {
            return CompareWithGeometry( inputGeometry, &inputGeometryTransform, flatteningTolerance );
        }

        /// <summary>
        /// Creates a simplified version of the geometry that contains only lines 
        /// and (optionally) cubic Bezier curves and writes the result to an 
        /// ID2D1SimplifiedGeometrySink.
        /// </summary>
        /// <param name="simplificationOption">
        /// A value that specifies whether the simplified geometry should contain curves.
        /// </param>
        /// <param name="worldTransform">
        /// The transform to apply to the simplified geometry, or NULL.
        /// </param>
        /// <param name="flatteningTolerance">
        /// The maximum error allowed when constructing a polygonal approximation of the 
        /// geometry. No point in the polygonal representation will diverge from the original 
        /// geometry by more than the flattening tolerance. Smaller values produce more 
        /// accurate results but cause slower execution.
        /// </param>
        /// <param name="geometrySink">
        /// The ID2D1SimplifiedGeometrySink to which the simplified geometry is appended.
        /// </param>
        void Simplify( D2D1_GEOMETRY_SIMPLIFICATION_OPTION simplificationOption, const D2D1_MATRIX_3X2_F* worldTransform, FLOAT flatteningTolerance, ID2D1SimplifiedGeometrySink* geometrySink ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->Simplify( simplificationOption, worldTransform, flatteningTolerance, geometrySink );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Simplify( D2D1_GEOMETRY_SIMPLIFICATION_OPTION simplificationOption, const D2D1_MATRIX_3X2_F* worldTransform, ID2D1SimplifiedGeometrySink* geometrySink ) const
        {
            Simplify( simplificationOption, worldTransform, D2D1_DEFAULT_FLATTENING_TOLERANCE, geometrySink );
        }
        void Simplify( D2D1_GEOMETRY_SIMPLIFICATION_OPTION simplificationOption, ID2D1SimplifiedGeometrySink* geometrySink ) const
        {
            Simplify( simplificationOption, nullptr, D2D1_DEFAULT_FLATTENING_TOLERANCE, geometrySink );
        }
        void Simplify( ID2D1SimplifiedGeometrySink* geometrySink ) const
        {
            Simplify( D2D1_GEOMETRY_SIMPLIFICATION_OPTION_CUBICS_AND_LINES, nullptr, D2D1_DEFAULT_FLATTENING_TOLERANCE, geometrySink );
        }


        /// <summary>
        /// Creates a set of clockwise-wound triangles that cover the geometry after it has 
        /// been transformed using the specified matrix and flattened using the specified tolerance.
        /// </summary>
        /// <param name="worldTransform">
        /// The transform to apply to this geometry, or NULL.
        /// </param>
        /// <param name="flatteningTolerance">
        /// The maximum error allowed when constructing a polygonal approximation of the geometry. 
        /// No point in the polygonal representation will diverge from the original geometry by 
        /// more than the flattening tolerance. Smaller values produce more accurate results but 
        /// cause slower execution.
        /// </param>
        /// <param name="tessellationSink">
        /// The ID2D1TessellationSink to which the tessellated is appended.
        /// </param>
        void Tessellate( const D2D1_MATRIX_3X2_F* worldTransform, FLOAT flatteningTolerance, ID2D1TessellationSink* tessellationSink ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->Tessellate( worldTransform, flatteningTolerance, tessellationSink );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Tessellate( const D2D1_MATRIX_3X2_F* worldTransform, ID2D1TessellationSink* tessellationSink ) const
        {
            Tessellate( worldTransform, D2D1_DEFAULT_FLATTENING_TOLERANCE, tessellationSink );
        }
        void Tessellate( ID2D1TessellationSink* tessellationSink ) const
        {
            Tessellate( nullptr, D2D1_DEFAULT_FLATTENING_TOLERANCE, tessellationSink );
        }



        //
        // Performs a combine operation between the two geometries to produce a resulting
        // geometry.
        //

        /// <summary>
        /// Combines this geometry with the specified geometry and stores the result in an 
        /// ID2D1SimplifiedGeometrySink.
        /// </summary>
        /// <param name="inputGeometry">
        /// The geometry to combine with this instance.
        /// </param>
        /// <param name="combineMode">
        /// The type of combine operation to perform.
        /// </param>
        /// <param name="inputGeometryTransform">
        /// The transform to apply to inputGeometry before combining, or NULL.
        /// </param>
        /// <param name="flatteningTolerance">
        /// The maximum error allowed when constructing a polygonal approximation of the 
        /// geometry. No point in the polygonal representation will diverge from the original 
        /// geometry by more than the flattening tolerance. Smaller values produce more 
        /// accurate results but cause slower execution.
        /// </param>
        /// <param name="geometrySink">
        /// The result of the combine operation.
        /// </param>
        void CombineWithGeometry( ID2D1Geometry* inputGeometry, D2D1_COMBINE_MODE combineMode, const D2D1_MATRIX_3X2_F* inputGeometryTransform, FLOAT flatteningTolerance, ID2D1SimplifiedGeometrySink* geometrySink ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->CombineWithGeometry( inputGeometry, combineMode, inputGeometryTransform, flatteningTolerance, geometrySink );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void CombineWithGeometry( const Geometry& inputGeometry, D2D1_COMBINE_MODE combineMode, const D2D1_MATRIX_3X2_F* inputGeometryTransform, FLOAT flatteningTolerance, ID2D1SimplifiedGeometrySink* geometrySink ) const
        {
            CombineWithGeometry( inputGeometry.GetInterfacePointer<ID2D1Geometry>(), combineMode, inputGeometryTransform, flatteningTolerance, geometrySink );
        }
        void CombineWithGeometry( ID2D1Geometry* inputGeometry, D2D1_COMBINE_MODE combineMode, const D2D1_MATRIX_3X2_F* inputGeometryTransform, ID2D1SimplifiedGeometrySink* geometrySink ) const
        {
            CombineWithGeometry( inputGeometry, combineMode, inputGeometryTransform, D2D1_DEFAULT_FLATTENING_TOLERANCE, geometrySink );
        }
        void CombineWithGeometry( const Geometry& inputGeometry, D2D1_COMBINE_MODE combineMode, const D2D1_MATRIX_3X2_F* inputGeometryTransform, ID2D1SimplifiedGeometrySink* geometrySink ) const
        {
            CombineWithGeometry( inputGeometry, combineMode, inputGeometryTransform, D2D1_DEFAULT_FLATTENING_TOLERANCE, geometrySink );
        }
        void CombineWithGeometry( ID2D1Geometry* inputGeometry, D2D1_COMBINE_MODE combineMode, ID2D1SimplifiedGeometrySink* geometrySink ) const
        {
            CombineWithGeometry( inputGeometry, combineMode, nullptr, D2D1_DEFAULT_FLATTENING_TOLERANCE, geometrySink );
        }
        void CombineWithGeometry( const Geometry& inputGeometry, D2D1_COMBINE_MODE combineMode, ID2D1SimplifiedGeometrySink* geometrySink ) const
        {
            CombineWithGeometry( inputGeometry, combineMode, nullptr, D2D1_DEFAULT_FLATTENING_TOLERANCE, geometrySink );
        }


        /// <summary>
        /// Computes the outline of the geometry and writes the result to an 
        /// ID2D1SimplifiedGeometrySink.
        /// </summary>
        /// <param name="worldTransform">
        /// The transform to apply to the geometry outline.
        /// </param>
        /// <param name="flatteningTolerance">
        /// The maximum error allowed when constructing a polygonal approximation 
        /// of the geometry. No point in the polygonal representation will diverge 
        /// from the original geometry by more than the flattening tolerance. Smaller 
        /// values produce more accurate results but cause slower execution.
        /// </param>
        /// <param name="geometrySink">
        /// The ID2D1SimplifiedGeometrySink to which the geometry transformed outline is appended.
        /// </param>
        void Outline( const D2D1_MATRIX_3X2_F* worldTransform, FLOAT flatteningTolerance, ID2D1SimplifiedGeometrySink* geometrySink ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->Outline( worldTransform, flatteningTolerance, geometrySink );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void Outline( const D2D1_MATRIX_3X2_F* worldTransform, ID2D1SimplifiedGeometrySink* geometrySink ) const
        {
            Outline( worldTransform, D2D1_DEFAULT_FLATTENING_TOLERANCE, geometrySink );
        }
        void Outline( const D2D1_MATRIX_3X2_F& worldTransform, ID2D1SimplifiedGeometrySink* geometrySink ) const
        {
            Outline( &worldTransform, D2D1_DEFAULT_FLATTENING_TOLERANCE, geometrySink );
        }
        void Outline( ID2D1SimplifiedGeometrySink* geometrySink ) const
        {
            Outline( nullptr, D2D1_DEFAULT_FLATTENING_TOLERANCE, geometrySink );
        }


        /// <summary>
        /// Computes the area of the geometry after it has been transformed by the 
        /// specified matrix and flattened using the specified tolerance.
        /// </summary>
        /// <param name="worldTransform">
        /// The transform to apply to this geometry before computing its area, or NULL.
        /// </param>
        /// <param name="flatteningTolerance">
        /// The maximum error allowed when constructing a polygonal approximation of the 
        /// geometry. No point in the polygonal representation will diverge from the 
        /// original geometry by more than the flattening tolerance. Smaller values produce 
        /// more accurate results but cause slower execution.
        /// </param>
        /// <param name="area">
        /// When this method returns, it contains a pointer to the area of the transformed, 
        /// flattened version of this geometry. You must allocate storage for this parameter.
        /// </param>
        void ComputeArea( const D2D1_MATRIX_3X2_F* worldTransform, FLOAT flatteningTolerance, FLOAT* area ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->ComputeArea( worldTransform, flatteningTolerance, area );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void ComputeArea( const D2D1_MATRIX_3X2_F& worldTransform, FLOAT flatteningTolerance, FLOAT* area ) const
        {
            ComputeArea( &worldTransform, flatteningTolerance, area );
        }

        FLOAT ComputeArea( const D2D1_MATRIX_3X2_F* worldTransform = nullptr, FLOAT flatteningTolerance = D2D1_DEFAULT_FLATTENING_TOLERANCE ) const
        {
            FLOAT result = .0f;
            ComputeArea( worldTransform, flatteningTolerance, &result );
            return result;
        }
        FLOAT ComputeArea( const D2D1_MATRIX_3X2_F& worldTransform, FLOAT flatteningTolerance = D2D1_DEFAULT_FLATTENING_TOLERANCE ) const
        {
            return ComputeArea( &worldTransform, flatteningTolerance );
        }


        /// <summary>
        /// Calculates the length of the geometry as though each segment were unrolled into a line.
        /// </summary>
        /// <param name="worldTransform">
        /// The transform to apply to the geometry before calculating its length.
        /// </param>
        /// <param name="flatteningTolerance">
        /// The maximum error allowed when constructing a polygonal approximation of the geometry. 
        /// No point in the polygonal representation will diverge from the original geometry by 
        /// more than the flattening tolerance. Smaller values produce more accurate results but 
        /// cause slower execution.
        /// </param>
        /// <param name="length">
        /// When this method returns, contains a pointer to the length of the geometry. For closed 
        /// geometries, the length includes an implicit closing segment. You must allocate storage 
        /// for this parameter.
        /// </param>
        void ComputeLength( const D2D1_MATRIX_3X2_F* worldTransform, FLOAT flatteningTolerance, FLOAT* length ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->ComputeLength( worldTransform, flatteningTolerance, length );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void ComputeLength( const D2D1_MATRIX_3X2_F& worldTransform, FLOAT flatteningTolerance, FLOAT* length ) const
        {
            ComputeLength( &worldTransform, flatteningTolerance, length );
        }
        FLOAT ComputeLength( const D2D1_MATRIX_3X2_F* worldTransform = nullptr, FLOAT flatteningTolerance = D2D1_DEFAULT_FLATTENING_TOLERANCE ) const
        {
            FLOAT result = .0f;
            ComputeLength( worldTransform, flatteningTolerance, &result );
            return result;
        }
        FLOAT ComputeLength( const D2D1_MATRIX_3X2_F& worldTransform, FLOAT flatteningTolerance = D2D1_DEFAULT_FLATTENING_TOLERANCE ) const
        {
            return ComputeLength( &worldTransform, flatteningTolerance );
        }

        //
        // Computes the point and tangent a given distance along the path.
        //

        /// <summary>
        /// Calculates the point and tangent vector at the specified distance along 
        /// the geometry after it has been transformed by the specified matrix and 
        /// flattened using the default tolerance.
        /// </summary>
        /// <param name="length">
        /// The distance along the geometry of the point and tangent to find. If this 
        /// distance is less than 0, this method calculates the first point in the geometry. 
        /// If this distance is greater than the length of the geometry, this method 
        /// calculates the last point in the geometry.
        /// </param>
        /// <param name="worldTransform">
        /// The transform to apply to the geometry before calculating the specified point 
        /// and tangent, or NULL.
        /// </param>
        /// <param name="flatteningTolerance">
        /// The maximum error allowed when constructing a polygonal approximation of the 
        /// geometry. No point in the polygonal representation will diverge from the 
        /// original geometry by more than the flattening tolerance. Smaller values 
        /// produce more accurate results but cause slower execution.
        /// </param>
        /// <param name="point">
        /// The location at the specified distance along the geometry. If the geometry is 
        /// empty, this point contains NaN as its x and y values. You must allocate 
        /// storage for this parameter.
        /// </param>
        /// <param name="unitTangentVector">
        /// When this method returns, contains a pointer to the tangent vector at the specified 
        /// distance along the geometry. If the geometry is empty, this vector contains NaN as 
        /// its x and y values. You must allocate storage for this parameter.
        /// </param>
        void ComputePointAtLength( FLOAT length, const D2D1_MATRIX_3X2_F* worldTransform, FLOAT flatteningTolerance, D2D1_POINT_2F* point, D2D1_POINT_2F* unitTangentVector ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->ComputePointAtLength( length, worldTransform, flatteningTolerance, point, unitTangentVector );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void ComputePointAtLength( FLOAT length, const D2D1_MATRIX_3X2_F& worldTransform, FLOAT flatteningTolerance, D2D1_POINT_2F* point, D2D1_POINT_2F* unitTangentVector ) const
        {
            ComputePointAtLength( length, &worldTransform, flatteningTolerance, point, unitTangentVector );
        }

        void ComputePointAtLength( FLOAT length, const D2D1_MATRIX_3X2_F* worldTransform, D2D1_POINT_2F* point, D2D1_POINT_2F* unitTangentVector ) const
        {
            ComputePointAtLength( length, worldTransform, D2D1_DEFAULT_FLATTENING_TOLERANCE, point, unitTangentVector );
        }
        void ComputePointAtLength( FLOAT length, const D2D1_MATRIX_3X2_F& worldTransform, D2D1_POINT_2F* point, D2D1_POINT_2F* unitTangentVector ) const
        {
            ComputePointAtLength( length, &worldTransform, D2D1_DEFAULT_FLATTENING_TOLERANCE, point, unitTangentVector );
        }

        void ComputePointAtLength( FLOAT length, D2D1_POINT_2F* point, D2D1_POINT_2F* unitTangentVector ) const
        {
            ComputePointAtLength( length, nullptr, D2D1_DEFAULT_FLATTENING_TOLERANCE, point, unitTangentVector );
        }

        /// <summary>
        /// Widens the geometry by the specified stroke and writes the result to an 
        /// ID2D1SimplifiedGeometrySink after it has been transformed by the specified 
        /// matrix and flattened using the specified tolerance.
        /// </summary>
        /// <param name="strokeWidth">
        /// The amount by which to widen the geometry.
        /// </param>
        /// <param name="strokeStyle">
        /// The style of stroke to apply to the geometry, or NULL.
        /// </param>
        /// <param name="worldTransform">
        /// The transform to apply to the geometry after widening it.
        /// </param>
        /// <param name="flatteningTolerance">
        /// The maximum error allowed when constructing a polygonal approximation of the geometry. 
        /// No point in the polygonal representation will diverge from the original geometry by 
        /// more than the flattening tolerance. Smaller values produce more accurate results 
        /// but cause slower execution.
        /// </param>
        /// <param name="geometrySink">
        /// The ID2D1SimplifiedGeometrySink to which the widened geometry is appended.
        /// </param>
        void Widen( FLOAT strokeWidth, ID2D1StrokeStyle* strokeStyle, const D2D1_MATRIX_3X2_F* worldTransform, FLOAT flatteningTolerance, ID2D1SimplifiedGeometrySink* geometrySink ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->Widen( strokeWidth, strokeStyle, worldTransform, flatteningTolerance, geometrySink );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void Widen( FLOAT strokeWidth, const StrokeStyle& strokeStyle, const D2D1_MATRIX_3X2_F* worldTransform, FLOAT flatteningTolerance, ID2D1SimplifiedGeometrySink* geometrySink ) const
        {
            Widen( strokeWidth, strokeStyle.GetInterfacePointer<ID2D1StrokeStyle>(), worldTransform, flatteningTolerance, geometrySink );
        }
        void Widen( FLOAT strokeWidth, ID2D1StrokeStyle* strokeStyle, const D2D1_MATRIX_3X2_F& worldTransform, FLOAT flatteningTolerance, ID2D1SimplifiedGeometrySink* geometrySink ) const
        {
            Widen( strokeWidth, strokeStyle, &worldTransform, flatteningTolerance, geometrySink );
        }
        void Widen( FLOAT strokeWidth, const StrokeStyle& strokeStyle, const D2D1_MATRIX_3X2_F& worldTransform, FLOAT flatteningTolerance, ID2D1SimplifiedGeometrySink* geometrySink ) const
        {
            Widen( strokeWidth, strokeStyle, &worldTransform, flatteningTolerance, geometrySink );
        }

        void Widen( FLOAT strokeWidth, ID2D1StrokeStyle* strokeStyle, const D2D1_MATRIX_3X2_F* worldTransform, ID2D1SimplifiedGeometrySink* geometrySink ) const
        {
            Widen( strokeWidth, strokeStyle, worldTransform, D2D1_DEFAULT_FLATTENING_TOLERANCE, geometrySink );
        }
        void Widen( FLOAT strokeWidth, const StrokeStyle& strokeStyle, const D2D1_MATRIX_3X2_F* worldTransform, ID2D1SimplifiedGeometrySink* geometrySink ) const
        {
            Widen( strokeWidth, strokeStyle, worldTransform, D2D1_DEFAULT_FLATTENING_TOLERANCE, geometrySink );
        }

        void Widen( FLOAT strokeWidth, ID2D1StrokeStyle* strokeStyle, const D2D1_MATRIX_3X2_F& worldTransform, ID2D1SimplifiedGeometrySink* geometrySink ) const
        {
            Widen( strokeWidth, strokeStyle, &worldTransform, D2D1_DEFAULT_FLATTENING_TOLERANCE, geometrySink );
        }
        void Widen( FLOAT strokeWidth, const StrokeStyle& strokeStyle, const D2D1_MATRIX_3X2_F& worldTransform, ID2D1SimplifiedGeometrySink* geometrySink ) const
        {
            Widen( strokeWidth, strokeStyle, &worldTransform, D2D1_DEFAULT_FLATTENING_TOLERANCE, geometrySink );
        }

        void Widen( FLOAT strokeWidth, ID2D1StrokeStyle* strokeStyle, ID2D1SimplifiedGeometrySink* geometrySink ) const
        {
            Widen( strokeWidth, strokeStyle, nullptr, D2D1_DEFAULT_FLATTENING_TOLERANCE, geometrySink );
        }
        void Widen( FLOAT strokeWidth, const StrokeStyle& strokeStyle, ID2D1SimplifiedGeometrySink* geometrySink ) const
        {
            Widen( strokeWidth, strokeStyle, nullptr, D2D1_DEFAULT_FLATTENING_TOLERANCE, geometrySink );
        }
        void Widen( FLOAT strokeWidth, const D2D1_MATRIX_3X2_F* worldTransform, ID2D1SimplifiedGeometrySink* geometrySink ) const
        {
            Widen( strokeWidth, nullptr, worldTransform, D2D1_DEFAULT_FLATTENING_TOLERANCE, geometrySink );
        }
        void Widen( FLOAT strokeWidth, const D2D1_MATRIX_3X2_F& worldTransform, ID2D1SimplifiedGeometrySink* geometrySink ) const
        {
            Widen( strokeWidth, nullptr, &worldTransform, D2D1_DEFAULT_FLATTENING_TOLERANCE, geometrySink );
        }
        void Widen( FLOAT strokeWidth, ID2D1SimplifiedGeometrySink* geometrySink ) const
        {
            Widen( strokeWidth, nullptr, nullptr, D2D1_DEFAULT_FLATTENING_TOLERANCE, geometrySink );
        }
    };


    /// <summary>
    /// Describes a two-dimensional rectangle.
    /// </summary>
    class RectangleGeometry : public Geometry
    {
    public:
        typedef Geometry Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( RectangleGeometry, Geometry, ID2D1RectangleGeometry, ID2D1Geometry )

        /// <summary>
        /// Retrieves the rectangle that describes the rectangle geometry's dimensions.
        /// </summary>
        /// <param name="rect">
        /// Contains a pointer to a rectangle that describes the rectangle geometry's 
        /// dimensions when this method returns. You must allocate storage for this parameter.
        /// </param>
        void GetRect( D2D1_RECT_F* rect ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->GetRect( rect );
        }

        void GetRect( D2D1_RECT_F& rect ) const
        {
            GetRect( &rect );
        }


        const D2D1_RECT_F GetRect( ) const
        {
            D2D1_RECT_F result = { 0, };
            GetRect( &result );
            return result;
        }

    };

    /// <summary>
    /// Describes a rounded rectangle.
    /// </summary>
    class RoundedRectangleGeometry : public Geometry
    {
    public:
        typedef Geometry Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( RoundedRectangleGeometry, Geometry, ID2D1RoundedRectangleGeometry, ID2D1Geometry )

        /// <summary>
        /// Retrieves a rounded rectangle that describes this rounded rectangle geometry.
        /// </summary>
        /// <param name="roundedRect">
        /// A pointer that receives a rounded rectangle that describes this rounded 
        /// rectangle geometry. You must allocate storage for this parameter.
        /// </param>
        void GetRoundedRect( D2D1_ROUNDED_RECT* roundedRect ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->GetRoundedRect( roundedRect );
        }

        void GetRoundedRect( D2D1_ROUNDED_RECT& roundedRect ) const
        {
            GetRoundedRect( &roundedRect );
        }

        const D2D1_ROUNDED_RECT GetRoundedRect( ) const
        {
            D2D1_ROUNDED_RECT result = { 0, };
            GetRoundedRect( &result );
            return result;
        }
    };

    /// <summary>
    /// Represents an ellipse.
    /// </summary>
    class EllipseGeometry : public Geometry
    {
    public:
        typedef Geometry Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( EllipseGeometry, Geometry, ID2D1EllipseGeometry, ID2D1Geometry )


        /// <summary>
        /// Gets the D2D1_ELLIPSE structure that describes this ellipse geometry.
        /// </summary>
        /// <param name="ellipse">
        /// When this method returns, contains the D2D1_ELLIPSE that describes the 
        /// size and position of the ellipse. You must allocate storage for this parameter.
        /// </param>
        void GetEllipse( D2D1_ELLIPSE* ellipse ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->GetEllipse( ellipse );
        }


        void GetEllipse( D2D1_ELLIPSE& ellipse ) const
        {
            GetEllipse( &ellipse );
        }

        D2D1_ELLIPSE GetEllipse( ) const
        {
            D2D1_ELLIPSE result = { 0, };
            GetEllipse( &result );
            return result;
        }


    };


    /// <summary>
    /// Represents a composite geometry, composed of other 
    /// Geometry (ID2D1Geometry) objects.
    /// </summary>
    class GeometryGroup : public Geometry
    {
    public:
        typedef Geometry Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( GeometryGroup, Geometry, ID2D1GeometryGroup, ID2D1Geometry )

        /// <summary>
        /// Indicates how the intersecting areas of the geometries contained 
        /// in this geometry group are combined.
        /// </summary>
        /// <returns>
        /// A value that indicates how the intersecting areas of the geometries 
        /// contained in this geometry group are combined.
        /// </returns>
        D2D1_FILL_MODE GetFillMode( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetFillMode( );
        }


        /// <summary>
        /// Indicates the number of geometry objects in the geometry group.
        /// </summary>
        /// <returns>
        /// The number of geometries in the GeometryGroup (ID2D1GeometryGroup).
        /// </returns>
        UINT32 GetSourceGeometryCount( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetSourceGeometryCount( );
        }

        /// <summary>
        /// Retrieves the geometries in the geometry group.
        /// </summary>
        /// <param name="geometries">
        /// When this method returns, contains the address of a pointer to an array of geometries 
        /// to be filled by this method. The length of the array is specified by the geometryCount 
        /// parameter. If the array is NULL, then this method performs no operation. You must 
        /// allocate the memory for this array.
        /// </param>
        /// <param name="geometriesCount">
        /// A value indicating the number of geometries to return in the geometries array. If this 
        /// value is less than the number of geometries in the geometry group, the remaining 
        /// geometries are omitted. If this value is larger than the number of geometries in the 
        /// geometry group, the extra geometries are set to NULL. To obtain the number of geometries 
        /// currently in the geometry group, use the GetSourceGeometryCount method.
        /// </param>
        /// <remarks>
        /// The returned geometries are referenced and counted, and the caller must release them.
        /// </remarks>
        void GetSourceGeometries( ID2D1Geometry** geometries, UINT32 geometriesCount ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->GetSourceGeometries( geometries, geometriesCount );
        }
        template<typename ContainerType = std::vector<Geometry>>
            requires std::is_base_of_v< Geometry, typename ContainerType::value_type >
        void GetSourceGeometries( ContainerType& result ) const
        {
            result.clear( );
            auto size = GetSourceGeometryCount( );
            result.resize( static_cast<size_t>( size ) );
            GetSourceGeometries( reinterpret_cast<ID2D1Geometry**>( result.data( ) ), size );
        }
    };


    /// <summary>
    /// Represents a geometry that has been transformed.
    /// </summary>
    class TransformedGeometry : public Geometry
    {
    public:
        typedef Geometry Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( TransformedGeometry, Geometry, ID2D1TransformedGeometry, ID2D1Geometry )

        /// <summary>
        /// Retrieves the source geometry of this transformed geometry object.
        /// </summary>
        /// <param name="sourceGeometry">
        /// When this method returns, contains a pointer to a pointer to the 
        /// source geometry for this transformed geometry object. This parameter 
        /// is passed uninitialized.
        /// </param>
        void GetSourceGeometry( ID2D1Geometry** sourceGeometry ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->GetSourceGeometry( sourceGeometry );
        }
        Geometry GetSourceGeometry( ) const
        {
            ID2D1Geometry* ptr = nullptr;
            GetSourceGeometry( &ptr );
            return Geometry( ptr );
        }

        /// <summary>
        /// Retrieves the matrix used to transform the TransformedGeometry 
        /// (ID2D1TransformedGeometry) object's source geometry.
        /// </summary>
        /// <param name="transform">
        /// A pointer that receives the matrix used to transform the 
        /// ID2D1TransformedGeometry object's source geometry. You must allocate 
        /// storage for this parameter.
        /// </param>
        void GetTransform( D2D1_MATRIX_3X2_F* transform ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->GetTransform( transform );
        }

        void GetTransform( D2D1_MATRIX_3X2_F& transform ) const
        {
            GetTransform( &transform );
        }

        D2D1_MATRIX_3X2_F GetTransform( ) const
        {
            D2D1_MATRIX_3X2_F result{};
            GetTransform( &result );
            return result;
        }

    };

    /// <summary>
    /// Describes a geometric path that does not contain quadratic bezier curves or arcs.
    /// </summary>
    class SimplifiedGeometrySink : public Unknown
    {
    public:
        typedef Unknown Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( SimplifiedGeometrySink, Unknown, ID2D1SimplifiedGeometrySink, IUnknown )


        void SetFillMode( D2D1_FILL_MODE fillMode ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetFillMode( fillMode );
        }

        void SetSegmentFlags( D2D1_PATH_SEGMENT vertexFlags ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetSegmentFlags( vertexFlags );
        }

        void BeginFigure( D2D1_POINT_2F startPoint, D2D1_FIGURE_BEGIN figureBegin ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->BeginFigure( startPoint, figureBegin );
        }

        void AddLines( const D2D1_POINT_2F* points, UINT32 pointsCount ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->AddLines( points, pointsCount );
        }

        void AddBeziers( const D2D1_BEZIER_SEGMENT* beziers, UINT32 beziersCount ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->AddBeziers( beziers, beziersCount );
        }

        void EndFigure( D2D1_FIGURE_END figureEnd ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->EndFigure( figureEnd );
        }

        void Close( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->Close( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    /// <summary>
    /// Basic implementation of ID2D1SimplifiedGeometrySink
    /// </summary>
    /// <typeparam name="DerivedT"></typeparam>
    /// <typeparam name="InterfaceT"></typeparam>
    template <typename DerivedT, typename InterfaceT = ID2D1SimplifiedGeometrySink>
    class ID2D1SimplifiedGeometrySinkImplementationBase : public IUnknownImplementation<ID2D1SimplifiedGeometrySinkImplementationBase<DerivedT, InterfaceT>, ID2D1SimplifiedGeometrySink, InterfaceT>
    {
    public:
        using Base = IUnknownImplementation<ID2D1SimplifiedGeometrySinkImplementationBase<DerivedT, InterfaceT>, ID2D1SimplifiedGeometrySink, InterfaceT>;
        using DerivedType = DerivedT;
        using InterfaceType = InterfaceT;
    protected:
        void HandleSetFillMode( D2D1_FILL_MODE fillMode )
        {
        }

        void HandleSetSegmentFlags( D2D1_PATH_SEGMENT vertexFlags )
        {
        }

        void HandleBeginFigure( D2D1_POINT_2F startPoint, D2D1_FIGURE_BEGIN figureBegin )
        {
        }

        void HandleAddLines( _In_reads_( pointsCount ) CONST D2D1_POINT_2F* points, UINT32 pointsCount )
        {
        }

        void HandleAddBeziers( _In_reads_( beziersCount ) CONST D2D1_BEZIER_SEGMENT* beziers, UINT32 beziersCount )
        {
        }

        void HandleEndFigure( D2D1_FIGURE_END figureEnd )
        {
        }

        void HandleClose( )
        {
        }
    private:
        virtual void STDAPICALLTYPE SetFillMode( D2D1_FILL_MODE fillMode ) override
        {
            try
            {
                auto* self = static_cast<DerivedType*>( this );
                self->HandleSetFillMode( fillMode );
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN( );
        }

        virtual void STDAPICALLTYPE SetSegmentFlags( D2D1_PATH_SEGMENT vertexFlags ) override
        {
            try
            {
                auto* self = static_cast<DerivedType*>( this );
                self->HandleSetSegmentFlags( vertexFlags );
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN( );
        }

        virtual void STDAPICALLTYPE BeginFigure( D2D1_POINT_2F startPoint, D2D1_FIGURE_BEGIN figureBegin ) override
        {
            try
            {
                auto* self = static_cast<DerivedType*>( this );
                self->HandleBeginFigure( startPoint, figureBegin );
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN( );
        }

        virtual void STDAPICALLTYPE AddLines( _In_reads_( pointsCount ) CONST D2D1_POINT_2F* points, UINT32 pointsCount ) override
        {
            try
            {
                auto* self = static_cast<DerivedType*>( this );
                self->HandleAddLines( points, pointsCount );
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN( );
        }

        virtual void STDAPICALLTYPE AddBeziers( _In_reads_( beziersCount ) CONST D2D1_BEZIER_SEGMENT* beziers, UINT32 beziersCount) override
        {
            try
            {
                auto* self = static_cast<DerivedType*>( this );
                self->HandleAddBeziers( beziers, beziersCount );
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN( );
        }

        virtual void STDAPICALLTYPE EndFigure( D2D1_FIGURE_END figureEnd ) override
        {
            try
            {
                auto* self = static_cast<DerivedType*>( this );
                self->HandleEndFigure( figureEnd );
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN( );
        }

        virtual HRESULT STDAPICALLTYPE Close( ) override
        {
            try
            {
                auto* self = static_cast<DerivedType*>( this );
                self->HandleClose( );
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT( );
        }

    };

    /// <summary>
    /// Describes a geometric path that can contain lines, arcs, cubic Bezier curves, and quadratic Bezier curves.
    /// </summary>
    class GeometrySink : public SimplifiedGeometrySink
    {
    public:
        typedef SimplifiedGeometrySink Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( GeometrySink, SimplifiedGeometrySink, ID2D1GeometrySink, ID2D1SimplifiedGeometrySink )

        void AddLine( D2D1_POINT_2F point ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->AddLine( point );
        }

        void AddBezier( const D2D1_BEZIER_SEGMENT* bezier ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->AddBezier( bezier );
        }

        void AddQuadraticBezier( const D2D1_QUADRATIC_BEZIER_SEGMENT* bezier ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->AddQuadraticBezier( bezier );
        }

        void AddQuadraticBeziers( const D2D1_QUADRATIC_BEZIER_SEGMENT* beziers, UINT32 beziersCount ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->AddQuadraticBeziers( beziers, beziersCount );
        }

        void AddArc( const D2D1_ARC_SEGMENT* arc ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->AddArc( arc );
        }

        void AddBezier( const D2D1_BEZIER_SEGMENT& bezier )
        {
            return AddBezier( &bezier );
        }

        void AddQuadraticBezier( const D2D1_QUADRATIC_BEZIER_SEGMENT& bezier )
        {
            return AddQuadraticBezier( &bezier );
        }

        void AddArc( const D2D1_ARC_SEGMENT& arc )
        {
            return AddArc( &arc );
        }
    };


    /// <summary>
    /// Basic implementation of ID2D1GeometrySink
    /// </summary>
    /// <typeparam name="DerivedT"></typeparam>
    template <typename DerivedT>
    class ID2D1GeometrySinkImplementationBase : public ID2D1SimplifiedGeometrySinkImplementationBase<ID2D1GeometrySinkImplementationBase<DerivedT>, ID2D1GeometrySink>
    {
    public:
        using Base = ID2D1SimplifiedGeometrySinkImplementationBase<ID2D1GeometrySinkImplementationBase<DerivedT>, ID2D1GeometrySink>;
        using DerivedType = DerivedT;
        using InterfaceType = ID2D1GeometrySink;
    protected:
        void HandleAddLine( D2D1_POINT_2F point ) override
        {

        }

        void HandleAddBezier( _In_ CONST D2D1_BEZIER_SEGMENT* bezier )
        {

        }

        void HandleAddQuadraticBezier( _In_ CONST D2D1_QUADRATIC_BEZIER_SEGMENT* bezier )
        {

        }

        void HandleAddQuadraticBeziers( _In_reads_( beziersCount ) CONST D2D1_QUADRATIC_BEZIER_SEGMENT* beziers, UINT32 beziersCount )
        {

        }

        void HandleAddArc( _In_ CONST D2D1_ARC_SEGMENT* arc )
        {

        }
    private:
        virtual void STDAPICALLTYPE AddLine( D2D1_POINT_2F point ) override
        {
            try
            {
                auto* self = static_cast<DerivedType*>( this );
                self->HandleAddLine( point );
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN( );
        }

        virtual void STDAPICALLTYPE AddBezier( _In_ CONST D2D1_BEZIER_SEGMENT* bezier ) override
        {
            try
            {
                auto* self = static_cast<DerivedType*>( this );
                self->HandleAddBezier( bezier );
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN( );
        }

        virtual void STDAPICALLTYPE AddQuadraticBezier( _In_ CONST D2D1_QUADRATIC_BEZIER_SEGMENT* bezier ) override
        {
            try
            {
                auto* self = static_cast<DerivedType*>( this );
                self->HandleAddQuadraticBezier( bezier );
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN( );
        }

        virtual void STDAPICALLTYPE AddQuadraticBeziers( _In_reads_( beziersCount ) CONST D2D1_QUADRATIC_BEZIER_SEGMENT* beziers, UINT32 beziersCount ) override
        {
            try
            {
                auto* self = static_cast<DerivedType*>( this );
                self->HandleAddQuadraticBeziers( beziers, beziersCount );
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN( );
        }

        virtual void STDAPICALLTYPE AddArc( _In_ CONST D2D1_ARC_SEGMENT* arc ) override
        {
            try
            {
                auto* self = static_cast<DerivedType*>( this );
                self->HandleAddArc( arc );
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN( );
        }
    };




    /// <summary>
    /// Populates an ID2D1Mesh object with triangles.
    /// </summary>
    class TessellationSink : public Unknown
    {
    public:
        typedef Unknown Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( TessellationSink, Unknown, ID2D1TessellationSink, IUnknown )

        void AddTriangles( const D2D1_TRIANGLE* triangles, UINT32 trianglesCount ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->AddTriangles( triangles, trianglesCount );
        }

        void Close( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->Close( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    template<typename DerivedT>
    class ID2D1TessellationSinkImplementationBase : public IUnknownImplementation<ID2D1TessellationSinkImplementationBase<DerivedT>,ID2D1TessellationSink, ID2D1TessellationSink>
    {
    public:
        using Base = IUnknownImplementation<ID2D1TessellationSinkImplementationBase<DerivedT>, ID2D1TessellationSink, ID2D1TessellationSink>;
        using DerivedType = DerivedT;
        using InterfaceType = ID2D1TessellationSink;
    protected:
        void HandleAddTriangles( _In_reads_( trianglesCount ) CONST D2D1_TRIANGLE* triangles, UINT32 trianglesCount )
        {

        }
        void HandleClose( )
        {

        }
    private:
        virtual void STDAPICALLTYPE AddTriangles( _In_reads_( trianglesCount ) CONST D2D1_TRIANGLE* triangles, UINT32 trianglesCount ) override
        {
            try
            {
                auto* self = static_cast<DerivedType*>( this );
                self->HandleAddTriangles( triangles, trianglesCount );
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN( );
        }

        virtual HRESULT STDAPICALLTYPE Close( ) override
        {
            try
            {
                auto* self = static_cast<DerivedType*>( this );
                self->HandleClose( );
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT( );
        }
    };



    /// <summary>
    /// Represents a complex shape that may be composed of arcs, curves, and lines.
    /// </summary>
    class PathGeometry : public Geometry
    {
    public:
        typedef Geometry Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( PathGeometry, Geometry, ID2D1PathGeometry, ID2D1Geometry )

        /// <summary>
        /// Retrieves the geometry sink that is used to populate the path geometry with figures and segments.
        /// </summary>
        /// <param name="geometrySink">
        /// When this method returns, geometrySink contains the address of 
        /// a pointer to the geometry sink that is used to populate the path 
        /// geometry with figures and segments. This parameter is passed uninitialized.
        /// </param>
        /// <remarks>
        /// <p>
        /// Because path geometries are immutable and can only be populated once, 
        /// it is an error to call Open on a path geometry more than once.
        /// </p>
        /// <p>
        /// Note that the fill mode defaults to D2D1_FILL_MODE_ALTERNATE. To set 
        /// the fill mode, call SetFillMode before the first call to BeginFigure. 
        /// Failure to do so will put the geometry sink in an error state.
        /// </p>
        /// </remarks>
        void Open( ID2D1GeometrySink** geometrySink ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->Open( geometrySink );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        GeometrySink Open( ) const
        {
            ID2D1GeometrySink* ptr = nullptr;
            Open( &ptr );
            return GeometrySink( ptr );
        }


        /// <summary>
        /// Copies the contents of the path geometry to the specified ID2D1GeometrySink.
        /// </summary>
        /// <param name="geometrySink">
        /// The sink to which the path geometry's contents are copied. Modifying 
        /// this sink does not change the contents of this path geometry.
        /// </param>
        void Stream( ID2D1GeometrySink* geometrySink ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->Stream( geometrySink );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void Stream( const GeometrySink& geometrySink ) const
        {
            Stream( geometrySink.GetInterfacePointer<ID2D1GeometrySink>() );
        }

        /// <summary>
        /// Retrieves the number of segments in the path geometry.
        /// </summary>
        /// <param name="count">
        /// A pointer that receives the number of segments in the path 
        /// geometry when this method returns. You must allocate storage 
        /// for this parameter.
        /// </param>
        void GetSegmentCount( UINT32* count ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetSegmentCount( count );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        UINT32 GetSegmentCount( ) const
        {
            UINT32 result = 0;
            GetSegmentCount( &result );
            return result;
        }

        /// <summary>
        /// Retrieves the number of figures in the path geometry.
        /// </summary>
        /// <param name="count">
        /// A pointer that receives the number of figures in the path geometry 
        /// when this method returns. You must allocate storage for this parameter.
        /// </param>
        void GetFigureCount( UINT32* count ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetFigureCount( count );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        UINT32 GetFigureCount( ) const
        {
            UINT32 result = 0;
            GetFigureCount( &result );
            return result;
        }
    };

    /// <summary>
    /// Represents a set of vertices that form a list of triangles.
    /// </summary>
    /// <remarks>
    /// <p>
    /// To create a mesh, call the RenderTarget::CreateMesh function on 
    /// the render target with which the mesh will be used. A mesh can 
    /// only be used with the render target that created it and the render 
    /// target's compatible targets.
    /// </p>
    /// <p>
    /// A mesh is a device-dependent resource: your application should 
    /// create meshes after it initializes the render target with which 
    /// the meshes will be used, and recreate the meshes whenever the 
    /// render target needs recreated.
    /// </p>
    /// </remarks>
    class Mesh : public Resource
    {
    public:
        typedef Resource Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( Mesh, Resource, ID2D1Mesh, ID2D1Resource )

        /// <summary>
        /// Opens the mesh for population.
        /// </summary>
        /// <param name="tessellationSink">
        /// When this method returns, contains a pointer to a pointer to an 
        /// ID2D1TessellationSink that is used to populate the mesh. This 
        /// parameter is passed uninitialized.
        /// </param>
        void Open( ID2D1TessellationSink** tessellationSink ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->Open( tessellationSink );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        TessellationSink Open( ) const
        {
            ID2D1TessellationSink* ptr = nullptr;
            Open( &ptr );
            return TessellationSink( ptr );
        }

    };

    /// <summary>
    /// Represents the backing store required to render a layer.
    /// </summary>
    class Layer : public Resource
    {
    public:
        typedef Resource Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( Layer, Resource, ID2D1Layer, ID2D1Resource )

        /// <summary>
        /// Gets the size of the layer in device-independent pixels.
        /// </summary>
        /// <returns>
        /// The size of the layer in device-independent pixels.
        /// </returns>
        D2D1_SIZE_F GetSize( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetSize( );
        }

    };


    /// <summary>
    /// Represents the drawing state of a render target: the anti-aliasing 
    /// mode, transform, tags, and text-rendering options.
    /// </summary>
    class DrawingStateBlock : public Resource
    {
    public:
        typedef Resource Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( DrawingStateBlock, Resource, ID2D1DrawingStateBlock, ID2D1Resource )

        /// <summary>
        /// Retrieves the anti-aliasing mode, transform, and 
        /// tags portion of the drawing state.
        /// </summary>
        /// <param name="stateDescription">
        /// When this method returns, contains the anti-aliasing mode, 
        /// transform, and tags portion of the drawing state. You must 
        /// allocate storage for this parameter.
        /// </param>
        void GetDescription( D2D1_DRAWING_STATE_DESCRIPTION* stateDescription ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->GetDescription( stateDescription );
        }

        /// <summary>
        /// Specifies the anti-aliasing mode, transform, and 
        /// tags portion of the drawing state.
        /// </summary>
        /// <param name="stateDescription">
        /// The anti-aliasing mode, transform, and tags portion of 
        /// the drawing state.
        /// </param>
        void SetDescription( const D2D1_DRAWING_STATE_DESCRIPTION* stateDescription ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetDescription( stateDescription );
        }
        void SetDescription( const D2D1_DRAWING_STATE_DESCRIPTION& stateDescription ) const
        {
            SetDescription( &stateDescription );
        }


        /// <summary>
        /// Specifies the text-rendering configuration of the drawing state.
        /// </summary>
        /// <param name="textRenderingParams">
        /// The text-rendering configuration of the drawing state, or 
        /// nullptr to use default settings.
        /// </param>
        void SetTextRenderingParams( IDWriteRenderingParams* textRenderingParams = nullptr ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetTextRenderingParams( textRenderingParams );
        }

        inline void SetTextRenderingParams( const DirectWrite::RenderingParams& textRenderingParams ) const;

        /// <summary>
        /// Retrieves the text-rendering configuration of the drawing state.
        /// </summary>
        /// <param name="textRenderingParams">
        /// When this method returns, contains the address of a pointer to an 
        /// IDWriteRenderingParams object that describes the text-rendering 
        /// configuration of the drawing state.
        /// </param>
        void GetTextRenderingParams( IDWriteRenderingParams** textRenderingParams ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->GetTextRenderingParams( textRenderingParams );
        }
        inline DirectWrite::RenderingParams GetTextRenderingParams( ) const;


    };



    /// <summary>
    /// Represents an object that can receive drawing commands. Interfaces that 
    /// inherit from RenderTarget (ID2D1RenderTarget) render the drawing commands
    /// they receive in different ways.
    /// </summary>
    class RenderTarget : public Resource
    {
    public:
        typedef Resource Base;
    public:
        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( RenderTarget, Resource, ID2D1RenderTarget, ID2D1Resource )

        //
        // Create a D2D bitmap by copying from memory, or create uninitialized.
        //

        /// <summary>
        /// Creates a Direct2D bitmap from a pointer to in-memory source data.
        /// </summary>
        /// <param name="size">
        /// The dimensions of the bitmap to create in pixels.
        /// </param>
        /// <param name="srcData">
        /// A pointer to the memory location of the image data, or NULL to create 
        /// an uninitialized bitmap.
        /// </param>
        /// <param name="pitch">
        /// The byte count of each scanline, which is equal to (the image width in 
        /// pixels × the number of bytes per pixel) + memory padding. If srcData is 
        /// NULL, this value is ignored. (Note that pitch is also sometimes called 
        /// stride.)
        /// </param>
        /// <param name="bitmapProperties">
        /// The pixel format and dots per inch (DPI) of the bitmap to create.
        /// </param>
        /// <param name="bitmap">
        /// When this method returns, contains a pointer to a pointer to the 
        /// new bitmap. This parameter is passed uninitialized.
        /// </param>
        void CreateBitmap( D2D1_SIZE_U size, _In_opt_ CONST void* srcData, UINT32 pitch, _In_ CONST D2D1_BITMAP_PROPERTIES* bitmapProperties, _COM_Outptr_ ID2D1Bitmap** bitmap ) const
        {
#ifdef _DEBUG
            CheckPointerNotNull( bitmapProperties );
#endif
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->CreateBitmap( size, srcData, pitch, bitmapProperties, bitmap );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }


        Bitmap CreateBitmap( D2D1_SIZE_U size, const void* srcData, UINT32 pitch, const D2D1_BITMAP_PROPERTIES* bitmapProperties ) const
        {
            ID2D1Bitmap* ptr = nullptr;
            CreateBitmap( size, srcData, pitch, bitmapProperties, &ptr );
            return Bitmap( ptr );
        }
        Bitmap CreateBitmap( D2D1_SIZE_U size, const void* srcData, UINT32 pitch, const D2D1_BITMAP_PROPERTIES& bitmapProperties ) const
        {
            return CreateBitmap( size, srcData, pitch, &bitmapProperties );
        }

        Bitmap CreateBitmap( D2D1_SIZE_U size, const D2D1_BITMAP_PROPERTIES* bitmapProperties ) const
        {
            return CreateBitmap( size, nullptr, 0, bitmapProperties );
        }
        Bitmap CreateBitmap( D2D1_SIZE_U size, const D2D1_BITMAP_PROPERTIES& bitmapProperties ) const
        {
            return CreateBitmap( size, nullptr, 0, &bitmapProperties );
        }


        /// <summary>
        /// Creates an ID2D1Bitmap by copying the specified Microsoft 
        /// Windows Imaging Component (WIC) bitmap.
        /// </summary>
        /// <param name="wicBitmapSource">
        /// The WIC bitmap to copy.
        /// </param>
        /// <param name="bitmapProperties">
        /// The pixel format and DPI of the bitmap to create. The pixel 
        /// format must match the pixel format of wicBitmapSource, or the 
        /// method will fail. To prevent a mismatch, you can pass NULL or 
        /// pass the value obtained from calling the D2D1::PixelFormat helper 
        /// function without specifying any parameter values. If both dpiX 
        /// and dpiY are 0.0f, the default DPI, 96, is used. DPI information 
        /// embedded in wicBitmapSource is ignored.
        /// </param>
        /// <param name="bitmap">
        /// When this method returns, contains the address of a pointer to 
        /// the new bitmap. This parameter is passed uninitialized.
        /// </param>
        void CreateBitmapFromWicBitmap( _In_ IWICBitmapSource* wicBitmapSource, _In_opt_ CONST D2D1_BITMAP_PROPERTIES* bitmapProperties, _COM_Outptr_ ID2D1Bitmap** bitmap ) const
        {
#ifdef _DEBUG
            CheckPointerNotNull( wicBitmapSource );
#endif
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->CreateBitmapFromWicBitmap( wicBitmapSource, bitmapProperties, bitmap );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        HW_EXPORT void CreateBitmapFromWicBitmap( const Imaging::BitmapSource& wicBitmapSource, _In_opt_ CONST D2D1_BITMAP_PROPERTIES* bitmapProperties, _COM_Outptr_ ID2D1Bitmap** bitmap ) const;
        HW_EXPORT void CreateBitmapFromWicBitmap( const Imaging::BitmapSource& wicBitmapSource, const D2D1_BITMAP_PROPERTIES& bitmapProperties, _COM_Outptr_ ID2D1Bitmap** bitmap ) const;

        Bitmap CreateBitmapFromWicBitmap( IWICBitmapSource* wicBitmapSource, const D2D1_BITMAP_PROPERTIES* bitmapProperties = nullptr ) const
        {
            ID2D1Bitmap* ptr = nullptr;
            CreateBitmapFromWicBitmap( wicBitmapSource, bitmapProperties, &ptr );
            return Bitmap( ptr );
        }
        HW_EXPORT Bitmap CreateBitmapFromWicBitmap( const Imaging::BitmapSource& wicBitmapSource, const D2D1_BITMAP_PROPERTIES* bitmapProperties = nullptr ) const;

        Bitmap CreateBitmapFromWicBitmap( IWICBitmapSource* wicBitmapSource, const D2D1_BITMAP_PROPERTIES& bitmapProperties ) const
        {
            return CreateBitmapFromWicBitmap( wicBitmapSource, &bitmapProperties );
        }
        HW_EXPORT Bitmap CreateBitmapFromWicBitmap( const Imaging::BitmapSource& wicBitmapSource, const D2D1_BITMAP_PROPERTIES& bitmapProperties ) const;

        /// <summary>
        /// Creates an ID2D1Bitmap whose data is shared with another resource.
        /// </summary>
        /// <param name="riid">
        /// The interface ID of the object supplying the source data.
        /// </param>
        /// <param name="data">
        /// An ID2D1Bitmap, IDXGISurface, or an IWICBitmapLock that contains the data 
        /// to share with the new ID2D1Bitmap. For more information, see the Remarks section.
        /// </param>
        /// <param name="bitmapProperties">
        /// The pixel format and DPI of the bitmap to create . The DXGI_FORMAT portion of the 
        /// pixel format must match the DXGI_FORMAT of data or the method will fail, but the 
        /// alpha modes don't have to match. To prevent a mismatch, you can pass NULL or the 
        /// value obtained from the D2D1::PixelFormat helper function. The DPI settings do not 
        /// have to match those of data. If both dpiX and dpiY are 0.0f, the DPI of the render 
        /// target is used.
        /// </param>
        /// <param name="bitmap">
        /// When this method returns, contains the address of a pointer to the new bitmap. 
        /// This parameter is passed uninitialized.
        /// </param>
        /// <remarks>
        /// <p>
        /// The CreateSharedBitmap method is useful for efficiently reusing bitmap data and 
        /// can also be used to provide interoperability with Direct3D.
        /// </p>
        /// <p><strong>Sharing an ID2D1Bitmap</strong></p>
        /// <p>
        /// By passing an ID2D1Bitmap created by a render target that is resource-compatible, 
        /// you can share a bitmap with that render target; both the original ID2D1Bitmap and 
        /// the new ID2D1Bitmap created by this method will point to the same bitmap data.
        /// </p>
        /// <p>
        /// You may also use this method to reinterpret the data of an existing bitmap and 
        /// specify a new DPI or alpha mode. For example, in the case of a bitmap atlas, 
        /// an ID2D1Bitmap may contain multiple sub-images, each of which should be rendered 
        /// with a different D2D1_ALPHA_MODE (D2D1_ALPHA_MODE_PREMULTIPLIED or D2D1_ALPHA_MODE_IGNORE). 
        /// You could use the CreateSharedBitmap method to reinterpret the bitmap using the 
        /// desired alpha mode without having to load a separate copy of the bitmap into memory.
        /// </p>
        /// <p><strong>Sharing an IDXGISurface</strong></p>
        /// <p>
        /// When using a DXGI surface render target (an ID2D1RenderTarget object created by the 
        /// CreateDxgiSurfaceRenderTarget method), you can pass an IDXGISurface surface to the 
        /// CreateSharedBitmap method to share video memory with Direct3D and manipulate Direct3D 
        /// content as an ID2D1Bitmap.
        /// </p>
        /// <p><strong>Sharing an IWICBitmapLock</strong></p>
        /// <p>
        /// An IWICBitmapLock stores the content of a WIC bitmap and shields it from simultaneous 
        /// accesses. By passing an IWICBitmapLock to the CreateSharedBitmap method, you can create 
        /// an ID2D1Bitmap that points to the bitmap data already stored in the IWICBitmapLock.
        /// </p>
        /// <p>
        /// To use an IWICBitmapLock with the CreateSharedBitmap method, the render target must 
        /// use software rendering. To force a render target to use software rendering, set to 
        /// D2D1_RENDER_TARGET_TYPE_SOFTWARE the type field of the D2D1_RENDER_TARGET_PROPERTIES 
        /// structure that you use to create the render target. To check whether an existing 
        /// render target uses software rendering, use the IsSupported method.
        /// </p>
        /// </remarks>
        void CreateSharedBitmap( REFIID riid, _Inout_ void* data, _In_opt_ CONST D2D1_BITMAP_PROPERTIES* bitmapProperties, _COM_Outptr_ ID2D1Bitmap** bitmap ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->CreateSharedBitmap( riid, data, bitmapProperties, bitmap );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        Bitmap CreateSharedBitmap( REFIID riid, void* data, const D2D1_BITMAP_PROPERTIES* bitmapProperties = nullptr ) const
        {
            ID2D1Bitmap* ptr = nullptr;
            CreateSharedBitmap( riid, data, bitmapProperties, &ptr );
            return Bitmap( ptr );
        }
        Bitmap CreateSharedBitmap( REFIID riid, void* data, const D2D1_BITMAP_PROPERTIES& bitmapProperties ) const
        {
            return CreateSharedBitmap( riid, data, &bitmapProperties );
        }


        //
        // Creates a bitmap brush. The bitmap is scaled, rotated, skewed or tiled to fill
        // or pen a geometry.
        //

        /// <summary>
        /// Creates an ID2D1BitmapBrush from the specified bitmap.
        /// </summary>
        /// <param name="bitmap">
        /// The bitmap contents of the new brush.
        /// </param>
        /// <param name="bitmapBrushProperties"></param>
        /// <param name="brushProperties"></param>
        /// <param name="bitmapBrush"></param>
        void CreateBitmapBrush( _In_ ID2D1Bitmap* bitmap, _In_opt_ CONST D2D1_BITMAP_BRUSH_PROPERTIES* bitmapBrushProperties, _In_opt_ CONST D2D1_BRUSH_PROPERTIES* brushProperties, _COM_Outptr_ ID2D1BitmapBrush** bitmapBrush ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->CreateBitmapBrush( bitmap, bitmapBrushProperties, brushProperties, bitmapBrush );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void CreateBitmapBrush( const Bitmap& bitmap, _In_opt_ CONST D2D1_BITMAP_BRUSH_PROPERTIES* bitmapBrushProperties, _In_opt_ CONST D2D1_BRUSH_PROPERTIES* brushProperties, _COM_Outptr_ ID2D1BitmapBrush** bitmapBrush ) const
        {
            CreateBitmapBrush( bitmap.GetInterfacePointer<ID2D1Bitmap>( ), bitmapBrushProperties, brushProperties, bitmapBrush );
        }

        BitmapBrush CreateBitmapBrush( _In_ ID2D1Bitmap* bitmap, _In_opt_ CONST D2D1_BITMAP_BRUSH_PROPERTIES* bitmapBrushProperties = nullptr, _In_opt_ CONST D2D1_BRUSH_PROPERTIES* brushProperties = nullptr ) const
        {
            ID2D1BitmapBrush* ptr = nullptr;
            CreateBitmapBrush( bitmap, bitmapBrushProperties, brushProperties, &ptr );
            return BitmapBrush( ptr );
        }
        BitmapBrush CreateBitmapBrush( const Bitmap& bitmap, _In_opt_ CONST D2D1_BITMAP_BRUSH_PROPERTIES* bitmapBrushProperties = nullptr, _In_opt_ CONST D2D1_BRUSH_PROPERTIES* brushProperties = nullptr ) const
        {
            return CreateBitmapBrush( bitmap.GetInterfacePointer<ID2D1Bitmap>( ), bitmapBrushProperties, brushProperties );
        }

        BitmapBrush CreateBitmapBrush( _In_ ID2D1Bitmap* bitmap, const D2D1_BITMAP_BRUSH_PROPERTIES& bitmapBrushProperties, const D2D1_BRUSH_PROPERTIES& brushProperties ) const
        {
            return CreateBitmapBrush( bitmap, &bitmapBrushProperties, &brushProperties );
        }
        BitmapBrush CreateBitmapBrush( const Bitmap& bitmap, const D2D1_BITMAP_BRUSH_PROPERTIES& bitmapBrushProperties, const D2D1_BRUSH_PROPERTIES& brushProperties ) const
        {
            return CreateBitmapBrush( bitmap, &bitmapBrushProperties, &brushProperties );
        }

        BitmapBrush CreateBitmapBrush( _In_ ID2D1Bitmap* bitmap, const D2D1_BITMAP_BRUSH_PROPERTIES& bitmapBrushProperties ) const
        {
            return CreateBitmapBrush( bitmap, &bitmapBrushProperties, nullptr );
        }
        BitmapBrush CreateBitmapBrush( const Bitmap& bitmap, const D2D1_BITMAP_BRUSH_PROPERTIES& bitmapBrushProperties ) const
        {
            return CreateBitmapBrush( bitmap, &bitmapBrushProperties, nullptr );
        }
        BitmapBrush CreateBitmapBrush( _In_ ID2D1Bitmap* bitmap, const D2D1_BRUSH_PROPERTIES& brushProperties ) const
        {
            return CreateBitmapBrush( bitmap, nullptr, &brushProperties );
        }
        BitmapBrush CreateBitmapBrush( const Bitmap& bitmap, const D2D1_BRUSH_PROPERTIES& brushProperties ) const
        {
            return CreateBitmapBrush( bitmap, nullptr, &brushProperties );
        }

        /// <summary>
        /// Creates a new ID2D1SolidColorBrush that can be used to paint 
        /// areas with a solid color.
        /// </summary>
        /// <param name="color">
        /// The red, green, blue, and alpha values of the brush's color.
        /// </param>
        /// <param name="brushProperties">
        /// The base opacity of the brush.
        /// </param>
        /// <param name="solidColorBrush">
        /// When this method returns, contains the address of a pointer to 
        /// the new brush. This parameter is passed uninitialized.
        /// </param>
        void CreateSolidColorBrush( _In_ CONST D2D1_COLOR_F* color, _In_opt_ CONST D2D1_BRUSH_PROPERTIES* brushProperties, _COM_Outptr_ ID2D1SolidColorBrush** solidColorBrush ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->CreateSolidColorBrush( color, brushProperties, solidColorBrush );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void CreateSolidColorBrush( const D2D1_COLOR_F& color, _In_opt_ CONST D2D1_BRUSH_PROPERTIES* brushProperties, _COM_Outptr_ ID2D1SolidColorBrush** solidColorBrush ) const
        {
            CreateSolidColorBrush( &color, brushProperties, solidColorBrush );
        }
        void CreateSolidColorBrush( _In_ CONST D2D1_COLOR_F* color, const D2D1_BRUSH_PROPERTIES& brushProperties, _COM_Outptr_ ID2D1SolidColorBrush** solidColorBrush ) const
        {
            CreateSolidColorBrush( color, &brushProperties, solidColorBrush );
        }
        void CreateSolidColorBrush( const D2D1_COLOR_F& color, const D2D1_BRUSH_PROPERTIES& brushProperties, _COM_Outptr_ ID2D1SolidColorBrush** solidColorBrush ) const
        {
            CreateSolidColorBrush( &color, &brushProperties, solidColorBrush );
        }

        SolidColorBrush CreateSolidColorBrush( _In_ CONST D2D1_COLOR_F* color, _In_opt_ CONST D2D1_BRUSH_PROPERTIES* brushProperties = nullptr ) const
        {
            ID2D1SolidColorBrush* ptr = nullptr;
            CreateSolidColorBrush( color, brushProperties, &ptr );
            return SolidColorBrush( ptr );
        }
        SolidColorBrush CreateSolidColorBrush( _In_ CONST D2D1_COLOR_F* color, const D2D1_BRUSH_PROPERTIES& brushProperties ) const
        {
            return CreateSolidColorBrush( color, &brushProperties );
        }
        SolidColorBrush CreateSolidColorBrush( const D2D1_COLOR_F& color, _In_opt_ CONST D2D1_BRUSH_PROPERTIES* brushProperties = nullptr ) const
        {
            return CreateSolidColorBrush( &color, brushProperties );
        }
        SolidColorBrush CreateSolidColorBrush( const D2D1_COLOR_F& color, const D2D1_BRUSH_PROPERTIES& brushProperties ) const
        {
            return CreateSolidColorBrush( &color, &brushProperties );
        }

        /// <summary>
        /// Creates an ID2D1GradientStopCollection from the specified 
        /// array of D2D1_GRADIENT_STOP structures.
        /// </summary>
        /// <param name="gradientStops">
        /// A pointer to an array of D2D1_GRADIENT_STOP structures.
        /// </param>
        /// <param name="gradientStopsCount">
        /// A value greater than or equal to 1 that specifies the 
        /// number of gradient stops in the gradientStops array.
        /// </param>
        /// <param name="colorInterpolationGamma">
        /// The space in which color interpolation between the 
        /// gradient stops is performed.
        /// </param>
        /// <param name="extendMode">
        /// The behavior of the gradient outside the [0,1] 
        /// normalized range.
        /// </param>
        /// <param name="gradientStopCollection">
        /// When this function returns, contains a pointer to a pointer 
        /// to the new gradient stop collection.
        /// </param>
        void CreateGradientStopCollection( _In_reads_( gradientStopsCount ) CONST D2D1_GRADIENT_STOP* gradientStops, _In_range_(>=,1) UINT32 gradientStopsCount, D2D1_GAMMA colorInterpolationGamma, D2D1_EXTEND_MODE extendMode, _COM_Outptr_ ID2D1GradientStopCollection** gradientStopCollection ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->CreateGradientStopCollection( gradientStops, gradientStopsCount, colorInterpolationGamma, extendMode, gradientStopCollection );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        GradientStopCollection CreateGradientStopCollection( _In_reads_( gradientStopsCount ) CONST D2D1_GRADIENT_STOP* gradientStops, _In_range_( >= , 1 ) UINT32 gradientStopsCount, D2D1_GAMMA colorInterpolationGamma = D2D1_GAMMA_2_2, D2D1_EXTEND_MODE extendMode = D2D1_EXTEND_MODE_CLAMP ) const
        {
            ID2D1GradientStopCollection* ptr = nullptr;
            CreateGradientStopCollection( gradientStops, gradientStopsCount, colorInterpolationGamma, extendMode, &ptr );
            return GradientStopCollection( ptr );
        }

        /// <summary>
        /// Creates an ID2D1LinearGradientBrush object for painting 
        /// areas with a linear gradient.
        /// </summary>
        /// <param name="linearGradientBrushProperties">
        /// The start and end points of the gradient.
        /// </param>
        /// <param name="brushProperties">
        /// The transform and base opacity of the new brush.
        /// </param>
        /// <param name="gradientStopCollection">
        /// A collection of D2D1_GRADIENT_STOP structures that describe 
        /// the colors in the brush's gradient and their locations along 
        /// the gradient line.
        /// </param>
        /// <param name="linearGradientBrush">
        /// When this method returns, contains the address of a pointer to 
        /// the new brush. This parameter is passed uninitialized.
        /// </param>
        void CreateLinearGradientBrush( _In_ CONST D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES* linearGradientBrushProperties, _In_opt_ CONST D2D1_BRUSH_PROPERTIES* brushProperties, _In_ ID2D1GradientStopCollection* gradientStopCollection, _COM_Outptr_ ID2D1LinearGradientBrush** linearGradientBrush ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->CreateLinearGradientBrush( linearGradientBrushProperties, brushProperties, gradientStopCollection, linearGradientBrush );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void CreateLinearGradientBrush( _In_ CONST D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES* linearGradientBrushProperties, const D2D1_BRUSH_PROPERTIES& brushProperties, _In_ ID2D1GradientStopCollection* gradientStopCollection, _COM_Outptr_ ID2D1LinearGradientBrush** linearGradientBrush ) const
        {
            CreateLinearGradientBrush( linearGradientBrushProperties, &brushProperties, gradientStopCollection, linearGradientBrush );
        }
        void CreateLinearGradientBrush( const D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES& linearGradientBrushProperties, _In_opt_ CONST D2D1_BRUSH_PROPERTIES* brushProperties, _In_ ID2D1GradientStopCollection* gradientStopCollection, _COM_Outptr_ ID2D1LinearGradientBrush** linearGradientBrush ) const
        {
            CreateLinearGradientBrush( &linearGradientBrushProperties, brushProperties, gradientStopCollection, linearGradientBrush );
        }
        void CreateLinearGradientBrush( const D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES& linearGradientBrushProperties, _In_opt_ CONST D2D1_BRUSH_PROPERTIES& brushProperties, _In_ ID2D1GradientStopCollection* gradientStopCollection, _COM_Outptr_ ID2D1LinearGradientBrush** linearGradientBrush ) const
        {
            CreateLinearGradientBrush( linearGradientBrushProperties, brushProperties, gradientStopCollection, linearGradientBrush );
        }

        void CreateLinearGradientBrush( _In_ CONST D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES* linearGradientBrushProperties, _In_opt_ CONST D2D1_BRUSH_PROPERTIES* brushProperties, const GradientStopCollection& gradientStopCollection, _COM_Outptr_ ID2D1LinearGradientBrush** linearGradientBrush ) const
        {
            CreateLinearGradientBrush( linearGradientBrushProperties, brushProperties, gradientStopCollection.GetInterfacePointer<ID2D1GradientStopCollection>(), linearGradientBrush );
        }

        void CreateLinearGradientBrush( _In_ CONST D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES* linearGradientBrushProperties, const D2D1_BRUSH_PROPERTIES& brushProperties, const GradientStopCollection& gradientStopCollection, _COM_Outptr_ ID2D1LinearGradientBrush** linearGradientBrush ) const
        {
            CreateLinearGradientBrush( linearGradientBrushProperties, &brushProperties, gradientStopCollection, linearGradientBrush );
        }
        void CreateLinearGradientBrush( const D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES& linearGradientBrushProperties, _In_opt_ CONST D2D1_BRUSH_PROPERTIES* brushProperties, const GradientStopCollection& gradientStopCollection, _COM_Outptr_ ID2D1LinearGradientBrush** linearGradientBrush ) const
        {
            CreateLinearGradientBrush( &linearGradientBrushProperties, brushProperties, gradientStopCollection, linearGradientBrush );
        }
        void CreateLinearGradientBrush( const D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES& linearGradientBrushProperties, _In_opt_ CONST D2D1_BRUSH_PROPERTIES& brushProperties, const GradientStopCollection& gradientStopCollection, _COM_Outptr_ ID2D1LinearGradientBrush** linearGradientBrush ) const
        {
            CreateLinearGradientBrush( linearGradientBrushProperties, brushProperties, gradientStopCollection, linearGradientBrush );
        }

        LinearGradientBrush CreateLinearGradientBrush( _In_ CONST D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES* linearGradientBrushProperties, _In_opt_ CONST D2D1_BRUSH_PROPERTIES* brushProperties, _In_ ID2D1GradientStopCollection* gradientStopCollection ) const
        {
            ID2D1LinearGradientBrush* ptr = nullptr;
            CreateLinearGradientBrush( linearGradientBrushProperties, brushProperties, gradientStopCollection, &ptr );
            return LinearGradientBrush( ptr );
        }
        LinearGradientBrush CreateLinearGradientBrush( _In_ CONST D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES* linearGradientBrushProperties, const D2D1_BRUSH_PROPERTIES& brushProperties, _In_ ID2D1GradientStopCollection* gradientStopCollection ) const
        {
            return CreateLinearGradientBrush( linearGradientBrushProperties, &brushProperties, gradientStopCollection );
        }
        LinearGradientBrush CreateLinearGradientBrush( const D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES& linearGradientBrushProperties, _In_opt_ CONST D2D1_BRUSH_PROPERTIES* brushProperties, _In_ ID2D1GradientStopCollection* gradientStopCollection ) const
        {
            return CreateLinearGradientBrush( &linearGradientBrushProperties, brushProperties, gradientStopCollection );
        }
        LinearGradientBrush CreateLinearGradientBrush( const D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES& linearGradientBrushProperties, const D2D1_BRUSH_PROPERTIES& brushProperties, _In_ ID2D1GradientStopCollection* gradientStopCollection ) const
        {
            return CreateLinearGradientBrush( &linearGradientBrushProperties, &brushProperties, gradientStopCollection );
        }


        LinearGradientBrush CreateLinearGradientBrush( _In_ CONST D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES* linearGradientBrushProperties, _In_opt_ CONST D2D1_BRUSH_PROPERTIES* brushProperties, const GradientStopCollection& gradientStopCollection ) const
        {
            return CreateLinearGradientBrush( linearGradientBrushProperties, brushProperties, gradientStopCollection.GetInterfacePointer<ID2D1GradientStopCollection>() );
        }

        LinearGradientBrush CreateLinearGradientBrush( _In_ CONST D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES* linearGradientBrushProperties, const D2D1_BRUSH_PROPERTIES& brushProperties, const GradientStopCollection& gradientStopCollection ) const
        {
            return CreateLinearGradientBrush( linearGradientBrushProperties, &brushProperties, gradientStopCollection );
        }
        LinearGradientBrush CreateLinearGradientBrush( const D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES& linearGradientBrushProperties, _In_opt_ CONST D2D1_BRUSH_PROPERTIES* brushProperties, const GradientStopCollection& gradientStopCollection ) const
        {
            return CreateLinearGradientBrush( &linearGradientBrushProperties, brushProperties, gradientStopCollection );
        }
        LinearGradientBrush CreateLinearGradientBrush( const D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES& linearGradientBrushProperties, const D2D1_BRUSH_PROPERTIES& brushProperties, const GradientStopCollection& gradientStopCollection ) const
        {
            return CreateLinearGradientBrush( &linearGradientBrushProperties, &brushProperties, gradientStopCollection );
        }

        LinearGradientBrush CreateLinearGradientBrush( _In_ CONST D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES* linearGradientBrushProperties, ID2D1GradientStopCollection* gradientStopCollection ) const
        {
            return CreateLinearGradientBrush( linearGradientBrushProperties, nullptr, gradientStopCollection );
        }
        LinearGradientBrush CreateLinearGradientBrush( _In_ CONST D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES* linearGradientBrushProperties, const GradientStopCollection& gradientStopCollection ) const
        {
            return CreateLinearGradientBrush( linearGradientBrushProperties, nullptr, gradientStopCollection );
        }
        LinearGradientBrush CreateLinearGradientBrush( _In_ CONST D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES& linearGradientBrushProperties, const GradientStopCollection& gradientStopCollection ) const
        {
            return CreateLinearGradientBrush( &linearGradientBrushProperties, nullptr, gradientStopCollection );
        }

        LinearGradientBrush CreateLinearGradientBrush( const D2D1_POINT_2F& startPoint, const D2D1_POINT_2F& endPoint, ID2D1GradientStopCollection* gradientStopCollection ) const
        {
            D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES linearGradientBrushProperties = { startPoint, endPoint };
#ifdef _DEBUG
            CheckPointerNotNull( gradientStopCollection );
#endif

            auto result = CreateLinearGradientBrush( &linearGradientBrushProperties, nullptr, gradientStopCollection );
            return result;
        }
        LinearGradientBrush CreateLinearGradientBrush( const D2D1_POINT_2F& startPoint, const D2D1_POINT_2F& endPoint, const GradientStopCollection& gradientStopCollection ) const
        {
            return CreateLinearGradientBrush( startPoint, endPoint, gradientStopCollection.GetInterfacePointer<ID2D1GradientStopCollection>( ) );
        }

        
        /// <summary>
        /// Creates an ID2D1RadialGradientBrush object that can be used to paint 
        /// areas with a radial gradient.
        /// </summary>
        /// <param name="radialGradientBrushProperties">
        /// The center, gradient origin offset, and x-radius and y-radius of the 
        /// brush's gradient.
        /// </param>
        /// <param name="brushProperties">
        /// The transform and base opacity of the new brush.
        /// </param>
        /// <param name="gradientStopCollection">
        /// A collection of D2D1_GRADIENT_STOP structures that describe 
        /// the colors in the brush's gradient and their locations along 
        /// the gradient line.
        /// </param>
        /// <param name="linearGradientBrush">
        /// When this method returns, contains the address of a pointer to 
        /// the new brush. This parameter is passed uninitialized.
        /// </param>
        void CreateRadialGradientBrush( _In_ CONST D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES* radialGradientBrushProperties, _In_opt_ CONST D2D1_BRUSH_PROPERTIES* brushProperties, _In_ ID2D1GradientStopCollection* gradientStopCollection, _COM_Outptr_ ID2D1RadialGradientBrush** radialGradientBrush ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->CreateRadialGradientBrush( radialGradientBrushProperties, brushProperties, gradientStopCollection, radialGradientBrush );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void CreateRadialGradientBrush( _In_ CONST D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES* radialGradientBrushProperties, const D2D1_BRUSH_PROPERTIES& brushProperties, _In_ ID2D1GradientStopCollection* gradientStopCollection, _COM_Outptr_ ID2D1RadialGradientBrush** radialGradientBrush ) const
        {
            CreateRadialGradientBrush( radialGradientBrushProperties, &brushProperties, gradientStopCollection, radialGradientBrush );
        }
        void CreateRadialGradientBrush( const D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES& radialGradientBrushProperties, _In_opt_ CONST D2D1_BRUSH_PROPERTIES* brushProperties, _In_ ID2D1GradientStopCollection* gradientStopCollection, _COM_Outptr_ ID2D1RadialGradientBrush** radialGradientBrush ) const
        {
            CreateRadialGradientBrush( &radialGradientBrushProperties, brushProperties, gradientStopCollection, radialGradientBrush );
        }
        void CreateRadialGradientBrush( const D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES& radialGradientBrushProperties, _In_opt_ CONST D2D1_BRUSH_PROPERTIES& brushProperties, _In_ ID2D1GradientStopCollection* gradientStopCollection, _COM_Outptr_ ID2D1RadialGradientBrush** radialGradientBrush ) const
        {
            CreateRadialGradientBrush( radialGradientBrushProperties, brushProperties, gradientStopCollection, radialGradientBrush );
        }

        void CreateRadialGradientBrush( _In_ CONST D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES* radialGradientBrushProperties, _In_opt_ CONST D2D1_BRUSH_PROPERTIES* brushProperties, const GradientStopCollection& gradientStopCollection, _COM_Outptr_ ID2D1RadialGradientBrush** radialGradientBrush ) const
        {
            CreateRadialGradientBrush( radialGradientBrushProperties, brushProperties, gradientStopCollection.GetInterfacePointer<ID2D1GradientStopCollection>( ), radialGradientBrush );
        }

        void CreateRadialGradientBrush( _In_ CONST D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES* radialGradientBrushProperties, const D2D1_BRUSH_PROPERTIES& brushProperties, const GradientStopCollection& gradientStopCollection, _COM_Outptr_ ID2D1RadialGradientBrush** radialGradientBrush ) const
        {
            CreateRadialGradientBrush( radialGradientBrushProperties, &brushProperties, gradientStopCollection, radialGradientBrush );
        }
        void CreateRadialGradientBrush( const D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES& radialGradientBrushProperties, _In_opt_ CONST D2D1_BRUSH_PROPERTIES* brushProperties, const GradientStopCollection& gradientStopCollection, _COM_Outptr_ ID2D1RadialGradientBrush** radialGradientBrush ) const
        {
            CreateRadialGradientBrush( &radialGradientBrushProperties, brushProperties, gradientStopCollection, radialGradientBrush );
        }
        void CreateRadialGradientBrush( const D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES& radialGradientBrushProperties, _In_opt_ CONST D2D1_BRUSH_PROPERTIES& brushProperties, const GradientStopCollection& gradientStopCollection, _COM_Outptr_ ID2D1RadialGradientBrush** radialGradientBrush ) const
        {
            CreateRadialGradientBrush( radialGradientBrushProperties, brushProperties, gradientStopCollection, radialGradientBrush );
        }

        RadialGradientBrush CreateRadialGradientBrush( _In_ CONST D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES* radialGradientBrushProperties, _In_opt_ CONST D2D1_BRUSH_PROPERTIES* brushProperties, _In_ ID2D1GradientStopCollection* gradientStopCollection ) const
        {
            ID2D1RadialGradientBrush* ptr = nullptr;
            CreateRadialGradientBrush( radialGradientBrushProperties, brushProperties, gradientStopCollection, &ptr );
            return RadialGradientBrush( ptr );
        }
        RadialGradientBrush CreateRadialGradientBrush( _In_ CONST D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES* radialGradientBrushProperties, const D2D1_BRUSH_PROPERTIES& brushProperties, _In_ ID2D1GradientStopCollection* gradientStopCollection ) const
        {
            return CreateRadialGradientBrush( radialGradientBrushProperties, &brushProperties, gradientStopCollection );
        }
        RadialGradientBrush CreateRadialGradientBrush( const D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES& radialGradientBrushProperties, _In_opt_ CONST D2D1_BRUSH_PROPERTIES* brushProperties, _In_ ID2D1GradientStopCollection* gradientStopCollection ) const
        {
            return CreateRadialGradientBrush( &radialGradientBrushProperties, brushProperties, gradientStopCollection );
        }
        RadialGradientBrush CreateRadialGradientBrush( const D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES& radialGradientBrushProperties, const D2D1_BRUSH_PROPERTIES& brushProperties, _In_ ID2D1GradientStopCollection* gradientStopCollection ) const
        {
            return CreateRadialGradientBrush( &radialGradientBrushProperties, &brushProperties, gradientStopCollection );
        }


        RadialGradientBrush CreateRadialGradientBrush( _In_ CONST D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES* radialGradientBrushProperties, _In_opt_ CONST D2D1_BRUSH_PROPERTIES* brushProperties, const GradientStopCollection& gradientStopCollection ) const
        {
            return CreateRadialGradientBrush( radialGradientBrushProperties, brushProperties, gradientStopCollection.GetInterfacePointer<ID2D1GradientStopCollection>( ) );
        }

        RadialGradientBrush CreateRadialGradientBrush( _In_ CONST D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES* radialGradientBrushProperties, const D2D1_BRUSH_PROPERTIES& brushProperties, const GradientStopCollection& gradientStopCollection ) const
        {
            return CreateRadialGradientBrush( radialGradientBrushProperties, &brushProperties, gradientStopCollection );
        }
        RadialGradientBrush CreateRadialGradientBrush( const D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES& radialGradientBrushProperties, _In_opt_ CONST D2D1_BRUSH_PROPERTIES* brushProperties, const GradientStopCollection& gradientStopCollection ) const
        {
            return CreateRadialGradientBrush( &radialGradientBrushProperties, brushProperties, gradientStopCollection );
        }
        RadialGradientBrush CreateRadialGradientBrush( const D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES& radialGradientBrushProperties, const D2D1_BRUSH_PROPERTIES& brushProperties, const GradientStopCollection& gradientStopCollection ) const
        {
            return CreateRadialGradientBrush( &radialGradientBrushProperties, &brushProperties, gradientStopCollection );
        }

        RadialGradientBrush CreateRadialGradientBrush( _In_ CONST D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES* radialGradientBrushProperties, ID2D1GradientStopCollection* gradientStopCollection ) const
        {
            return CreateRadialGradientBrush( radialGradientBrushProperties, nullptr, gradientStopCollection );
        }
        RadialGradientBrush CreateRadialGradientBrush( _In_ CONST D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES* radialGradientBrushProperties, const GradientStopCollection& gradientStopCollection ) const
        {
            return CreateRadialGradientBrush( radialGradientBrushProperties, nullptr, gradientStopCollection );
        }

        RadialGradientBrush CreateRadialGradientBrush( const D2D1_POINT_2F& center, const D2D1_POINT_2F& gradientOriginOffset, FLOAT radiusX, FLOAT radiusY, _In_ ID2D1GradientStopCollection* gradientStopCollection ) const
        {
            D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES radialGradientBrushProperties = { center, gradientOriginOffset, radiusX, radiusY };
#ifdef _DEBUG
            CheckPointerNotNull( gradientStopCollection );
#endif
            auto result = CreateRadialGradientBrush( &radialGradientBrushProperties, nullptr, gradientStopCollection );
            return result;
        }
        RadialGradientBrush CreateRadialGradientBrush( const D2D1_POINT_2F& center, const D2D1_POINT_2F& gradientOriginOffset, FLOAT radiusX, FLOAT radiusY, const GradientStopCollection& gradientStopCollection ) const
        {
            return CreateRadialGradientBrush( center, gradientOriginOffset, radiusX, radiusY, gradientStopCollection.GetInterfacePointer<ID2D1GradientStopCollection>( ) );
        }


        /// <summary>
        /// Creates a bitmap render target for use during intermediate 
        /// off-screen drawing that is compatible with the current 
        /// render target.
        /// </summary>
        /// <param name="desiredSize">
        /// The desired size of the new render target (in device-independent 
        /// pixels), if it should be different from the original render target. 
        /// For more info, see the Remarks section.
        /// </param>
        /// <param name="desiredPixelSize">
        /// The desired size of the new render target in pixels if it should be 
        /// different from the original render target. For more information, see 
        /// the Remarks section.
        /// </param>
        /// <param name="desiredFormat">
        /// The desired pixel format and alpha mode of the new render target. 
        /// If the pixel format is set to DXGI_FORMAT_UNKNOWN, the new render 
        /// target uses the same pixel format as the original render target. 
        /// If the alpha mode is D2D1_ALPHA_MODE_UNKNOWN, the alpha mode of 
        /// the new render target defaults to D2D1_ALPHA_MODE_PREMULTIPLIED.
        /// </param>
        /// <param name="options">
        /// A value that specifies whether the new render target must be 
        /// compatible with GDI.
        /// </param>
        /// <param name="bitmapRenderTarget">
        /// When this method returns, contains a pointer to a pointer to a new 
        /// bitmap render target. This parameter is passed uninitialized.
        /// </param>
        /// <remarks>
        /// <p>
        /// The pixel size and DPI of the new render target can be altered by 
        /// specifying values for desiredSize or desiredPixelSize:
        /// </p>
        /// <ul>
        ///     <li>
        ///     If desiredSize is specified but desiredPixelSize is not, the 
        ///     pixel size is computed from the desired size using the parent 
        ///     target DPI. If the desiredSize maps to a integer-pixel size, 
        ///     the DPI of the compatible render target is the same as the DPI 
        ///     of the parent target. If desiredSize maps to a fractional-pixel 
        ///     size, the pixel size is rounded up to the nearest integer and 
        ///     the DPI for the compatible render target is slightly higher than 
        ///     the DPI of the parent render target. In all cases, the coordinate 
        ///     (desiredSize.width, desiredSize.height) maps to the lower-right 
        ///     corner of the compatible render target.
        ///     </li>
        ///     <li>
        ///     If the desiredPixelSize is specified and desiredSize is not, the 
        ///     DPI of the new render target is the same as the original render 
        ///     target.
        ///     </li>
        ///     <li>
        ///     If both desiredSize and desiredPixelSize are specified, the DPI 
        ///     of the new render target is computed to account for the difference 
        ///     in scale.
        ///     </li>
        ///     <li>
        ///     If neither desiredSize nor desiredPixelSize is specified, the new 
        ///     render target size and DPI match the original render target.
        ///     </li>
        /// </ul>
        /// </remarks>
        void CreateCompatibleRenderTarget( _In_opt_ CONST D2D1_SIZE_F* desiredSize, _In_opt_ CONST D2D1_SIZE_U* desiredPixelSize, _In_opt_ CONST D2D1_PIXEL_FORMAT* desiredFormat, D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS options, _COM_Outptr_ ID2D1BitmapRenderTarget** bitmapRenderTarget ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->CreateCompatibleRenderTarget( desiredSize, desiredPixelSize, desiredFormat, options, bitmapRenderTarget );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        inline BitmapRenderTarget CreateCompatibleRenderTarget( _In_opt_ CONST D2D1_SIZE_F* desiredSize = nullptr, _In_opt_ CONST D2D1_SIZE_U* desiredPixelSize = nullptr, _In_opt_ CONST D2D1_PIXEL_FORMAT* desiredFormat = nullptr, D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS options = D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS::D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS_NONE ) const;
        inline BitmapRenderTarget CreateCompatibleRenderTarget( _In_opt_ CONST D2D1_SIZE_F* desiredSize, _In_opt_ CONST D2D1_SIZE_U* desiredPixelSize, const D2D1_PIXEL_FORMAT& desiredFormat, D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS options = D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS::D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS_NONE ) const;
        inline BitmapRenderTarget CreateCompatibleRenderTarget( _In_opt_ CONST D2D1_SIZE_F* desiredSize, const D2D1_SIZE_U& desiredPixelSize, _In_opt_ CONST D2D1_PIXEL_FORMAT* desiredFormat, D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS options = D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS::D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS_NONE ) const;
        inline BitmapRenderTarget CreateCompatibleRenderTarget( const D2D1_SIZE_F& desiredSize, _In_opt_ CONST D2D1_SIZE_U* desiredPixelSize, _In_opt_ CONST D2D1_PIXEL_FORMAT* desiredFormat, D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS options = D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS::D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS_NONE ) const;
        inline BitmapRenderTarget CreateCompatibleRenderTarget( _In_opt_ CONST D2D1_SIZE_F* desiredSize, const D2D1_SIZE_U& desiredPixelSize, const D2D1_PIXEL_FORMAT& desiredFormat, D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS options = D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS::D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS_NONE ) const;
        inline BitmapRenderTarget CreateCompatibleRenderTarget( const D2D1_SIZE_F& desiredSize, _In_opt_ CONST D2D1_SIZE_U* desiredPixelSize, const D2D1_PIXEL_FORMAT& desiredFormat, D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS options = D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS::D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS_NONE ) const;
        inline BitmapRenderTarget CreateCompatibleRenderTarget( const D2D1_SIZE_F& desiredSize, const D2D1_SIZE_U& desiredPixelSize, const D2D1_PIXEL_FORMAT& desiredFormat, D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS options = D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS::D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS_NONE ) const;
        inline BitmapRenderTarget CreateCompatibleRenderTarget( const D2D1_SIZE_F& desiredSize, const D2D1_SIZE_U* desiredPixelSize ) const;
        inline BitmapRenderTarget CreateCompatibleRenderTarget( const D2D1_SIZE_F& desiredSize, const D2D1_SIZE_U& desiredPixelSize ) const;
        inline BitmapRenderTarget CreateCompatibleRenderTarget( const D2D1_SIZE_F& desiredSize, const D2D1_PIXEL_FORMAT* desiredFormat ) const;
        inline BitmapRenderTarget CreateCompatibleRenderTarget( const D2D1_SIZE_F& desiredSize, const D2D1_PIXEL_FORMAT& desiredFormat ) const;
        inline BitmapRenderTarget CreateCompatibleRenderTarget( const D2D1_SIZE_F& desiredSize ) const;


        /// <summary>
        /// Creates a layer resource that can be used with this render 
        /// target and its compatible render targets.
        /// </summary>
        /// <param name="size">
        /// If (0, 0) is specified, no backing store is created behind 
        /// the layer resource. The layer resource is allocated to the 
        /// minimum size when PushLayer is called.
        /// </param>
        /// <param name="">
        /// When the method returns, contains a pointer to a pointer to 
        /// the new layer. This parameter is passed uninitialized.
        /// </param>
        void CreateLayer( const D2D1_SIZE_F* size, ID2D1Layer** layer ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->CreateLayer( size, layer );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        Layer CreateLayer( const D2D1_SIZE_F* size = nullptr ) const
        {
            ID2D1Layer* ptr = nullptr;
            CreateLayer( size, &ptr );
            return Layer( ptr );
        }

        Layer CreateLayer( const D2D1_SIZE_F& size ) const
        {
            return CreateLayer( &size );
        }

        /// <summary>
        /// Create a mesh that uses triangles to describe a shape.
        /// </summary>
        /// <param name="mesh">
        /// When this method returns, contains a pointer to a pointer 
        /// to the new mesh.
        /// </param>
        void CreateMesh( ID2D1Mesh** mesh ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->CreateMesh( mesh );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        Mesh CreateMesh( ) const
        {
            ID2D1Mesh* ptr = nullptr;
            CreateMesh( &ptr );
            return Mesh( ptr );
        }

        /// <summary>
        /// Draws a line between the specified points using the 
        /// specified stroke style.
        /// </summary>
        /// <param name="point0">
        /// The start point of the line, in device-independent pixels.
        /// </param>
        /// <param name="point1">
        /// The end point of the line, in device-independent pixels.
        /// </param>
        /// <param name="brush">
        /// The brush used to paint the line's stroke.
        /// </param>
        /// <param name="strokeWidth">
        /// The width of the stroke, in device-independent pixels. The value 
        /// must be greater than or equal to 0.0f. If this parameter isn't 
        /// specified, it defaults to 1.0f. The stroke is centered on the line.
        /// </param>
        /// <param name="strokeStyle">
        /// The style of stroke to paint, or NULL to paint a solid line.
        /// </param>
        void DrawLine( const D2D1_POINT_2F& point0, const D2D1_POINT_2F& point1, ID2D1Brush* brush, FLOAT strokeWidth = 1.0f, ID2D1StrokeStyle* strokeStyle = nullptr ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->DrawLine( point0, point1, brush, strokeWidth, strokeStyle );
        }
        void DrawLine( const D2D1_POINT_2F& point0, const D2D1_POINT_2F& point1, ID2D1Brush* brush, FLOAT strokeWidth, const StrokeStyle& strokeStyle ) const
        {
            DrawLine( point0, point1, brush, strokeWidth, strokeStyle.GetInterfacePointer<ID2D1StrokeStyle>() );
        }
        void DrawLine( const D2D1_POINT_2F& point0, const D2D1_POINT_2F& point1, const Brush& brush, FLOAT strokeWidth, const StrokeStyle& strokeStyle ) const
        {
            DrawLine( point0, point1, brush.GetInterfacePointer<ID2D1Brush>(), strokeWidth, strokeStyle.GetInterfacePointer<ID2D1StrokeStyle>( ) );
        }
        void DrawLine( const D2D1_POINT_2F& point0, const D2D1_POINT_2F& point1, const Brush& brush, FLOAT strokeWidth = 1.0f ) const
        {
            DrawLine( point0, point1, brush.GetInterfacePointer<ID2D1Brush>( ), strokeWidth, nullptr );
        }


        /// <summary>
        /// Draws the outline of a rectangle that has the specified 
        /// dimensions and stroke style.
        /// </summary>
        /// <param name="rect">
        /// The dimensions of the rectangle to draw, in device-independent 
        /// pixels.
        /// </param>
        /// <param name="brush">
        /// The brush used to paint the rectangle's stroke.
        /// </param>
        /// <param name="strokeWidth">
        /// The width of the stroke, in device-independent pixels. The value 
        /// must be greater than or equal to 0.0f. If this parameter isn't 
        /// specified, it defaults to 1.0f. The stroke is centered on the line.
        /// </param>
        /// <param name="strokeStyle">
        /// The style of stroke to paint, or NULL to paint a solid stroke.
        /// </param>
        void DrawRectangle( const D2D1_RECT_F* rect, ID2D1Brush* brush, FLOAT strokeWidth = 1.0f, ID2D1StrokeStyle* strokeStyle = nullptr ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->DrawRectangle( rect, brush, strokeWidth, strokeStyle );
        }
        void DrawRectangle( const D2D1_RECT_F& rect, ID2D1Brush* brush, FLOAT strokeWidth = 1.0f, ID2D1StrokeStyle* strokeStyle = nullptr ) const
        {
            DrawRectangle( &rect, brush, strokeWidth, strokeStyle );
        }
        void DrawRectangle( const D2D1_RECT_F* rect, ID2D1Brush* brush, FLOAT strokeWidth, const StrokeStyle& strokeStyle ) const
        {
            DrawRectangle( rect, brush, strokeWidth, strokeStyle.GetInterfacePointer<ID2D1StrokeStyle>() );
        }
        void DrawRectangle( const D2D1_RECT_F* rect, const Brush& brush, FLOAT strokeWidth, const StrokeStyle& strokeStyle ) const
        {
            DrawRectangle( rect, brush.GetInterfacePointer<ID2D1Brush>(), strokeWidth, strokeStyle.GetInterfacePointer<ID2D1StrokeStyle>( ) );
        }
        void DrawRectangle( const D2D1_RECT_F* rect, const Brush& brush, FLOAT strokeWidth = 1.0f ) const
        {
            DrawRectangle( rect, brush.GetInterfacePointer<ID2D1Brush>( ), strokeWidth, nullptr );
        }

        void DrawRectangle( const D2D1_RECT_F& rect, ID2D1Brush* brush, FLOAT strokeWidth, const StrokeStyle& strokeStyle ) const
        {
            DrawRectangle( &rect, brush, strokeWidth, strokeStyle.GetInterfacePointer<ID2D1StrokeStyle>( ) );
        }
        void DrawRectangle( const D2D1_RECT_F& rect, const Brush& brush, FLOAT strokeWidth, const StrokeStyle& strokeStyle ) const
        {
            DrawRectangle( &rect, brush.GetInterfacePointer<ID2D1Brush>( ), strokeWidth, strokeStyle.GetInterfacePointer<ID2D1StrokeStyle>( ) );
        }
        void DrawRectangle( const D2D1_RECT_F& rect, const Brush& brush, FLOAT strokeWidth = 1.0f ) const
        {
            DrawRectangle( &rect, brush.GetInterfacePointer<ID2D1Brush>( ), strokeWidth, nullptr );
        }


        
        /// <summary>
        /// Paints the interior of the specified rectangle.
        /// </summary>
        /// <param name="rect">
        /// The dimension of the rectangle to paint, in device-independent pixels.
        /// </param>
        /// <param name="brush">
        /// The brush used to paint the rectangle's interior.
        /// </param>
        void FillRectangle( const D2D1_RECT_F* rect, ID2D1Brush* brush ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->FillRectangle( rect, brush );
        }
        void FillRectangle( const D2D1_RECT_F& rect, ID2D1Brush* brush ) const
        {
            FillRectangle( &rect, brush );
        }
        void FillRectangle( const D2D1_RECT_F* rect, const Brush& brush ) const
        {
            FillRectangle( rect, brush.GetInterfacePointer<ID2D1Brush>() );
        }
        void FillRectangle( const D2D1_RECT_F& rect, const Brush& brush ) const
        {
            FillRectangle( &rect, brush.GetInterfacePointer<ID2D1Brush>( ) );
        }
        
        /// <summary>
        /// Draws the outline of the specified rounded rectangle using 
        /// the specified stroke style.
        /// </summary>
        /// <param name="roundedRect">
        /// The dimensions of the rounded rectangle to draw, in device-independent 
        /// pixels.
        /// </param>
        /// <param name="brush">
        /// The brush used to paint the rounded rectangle's outline.
        /// </param>
        /// <param name="strokeWidth">
        /// The width of the stroke, in device-independent pixels. The value 
        /// must be greater than or equal to 0.0f. If this parameter isn't 
        /// specified, it defaults to 1.0f. The stroke is centered on the line.
        /// </param>
        /// <param name="strokeStyle">
        /// The style of the rounded rectangle's stroke, or nullptr to paint a 
        /// solid stroke. The default value is nullptr.
        /// </param>
        void DrawRoundedRectangle( const D2D1_ROUNDED_RECT* roundedRect, ID2D1Brush* brush, FLOAT strokeWidth = 1.0f, ID2D1StrokeStyle* strokeStyle = nullptr ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->DrawRoundedRectangle( roundedRect, brush, strokeWidth, strokeStyle );
        }
        void DrawRoundedRectangle( const D2D1_ROUNDED_RECT& roundedRect, ID2D1Brush* brush, FLOAT strokeWidth = 1.0f, ID2D1StrokeStyle* strokeStyle = nullptr ) const
        {
            DrawRoundedRectangle( &roundedRect, brush, strokeWidth, strokeStyle );
        }
        void DrawRoundedRectangle( const D2D1_ROUNDED_RECT* roundedRect, ID2D1Brush* brush, FLOAT strokeWidth, const StrokeStyle& strokeStyle ) const
        {
            DrawRoundedRectangle( roundedRect, brush, strokeWidth, strokeStyle.GetInterfacePointer<ID2D1StrokeStyle>( ) );
        }
        void DrawRoundedRectangle( const D2D1_ROUNDED_RECT* roundedRect, const Brush& brush, FLOAT strokeWidth, const StrokeStyle& strokeStyle ) const
        {
            DrawRoundedRectangle( roundedRect, brush.GetInterfacePointer<ID2D1Brush>( ), strokeWidth, strokeStyle.GetInterfacePointer<ID2D1StrokeStyle>( ) );
        }
        void DrawRoundedRectangle( const D2D1_ROUNDED_RECT* roundedRect, const Brush& brush, FLOAT strokeWidth = 1.0f ) const
        {
            DrawRoundedRectangle( roundedRect, brush.GetInterfacePointer<ID2D1Brush>( ), strokeWidth, nullptr );
        }
        void DrawRoundedRectangle( const D2D1_ROUNDED_RECT& roundedRect, ID2D1Brush* brush, FLOAT strokeWidth, const StrokeStyle& strokeStyle ) const
        {
            DrawRoundedRectangle( &roundedRect, brush, strokeWidth, strokeStyle.GetInterfacePointer<ID2D1StrokeStyle>( ) );
        }
        void DrawRoundedRectangle( const D2D1_ROUNDED_RECT& roundedRect, const Brush& brush, FLOAT strokeWidth, const StrokeStyle& strokeStyle ) const
        {
            DrawRoundedRectangle( &roundedRect, brush.GetInterfacePointer<ID2D1Brush>( ), strokeWidth, strokeStyle.GetInterfacePointer<ID2D1StrokeStyle>( ) );
        }
        void DrawRoundedRectangle( const D2D1_ROUNDED_RECT& roundedRect, const Brush& brush, FLOAT strokeWidth = 1.0f ) const
        {
            DrawRoundedRectangle( &roundedRect, brush.GetInterfacePointer<ID2D1Brush>( ), strokeWidth, nullptr );
        }

        /// <summary>
        /// Paints the interior of the specified rounded rectangle.
        /// </summary>
        /// <param name="roundedRect">
        /// The dimensions of the rounded rectangle to paint, in 
        /// device independent pixels.
        /// </param>
        /// <param name="brush">
        /// The brush used to paint the interior of the rounded rectangle.
        /// </param>
        void FillRoundedRectangle( const D2D1_ROUNDED_RECT* roundedRect, ID2D1Brush* brush ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->FillRoundedRectangle( roundedRect, brush );
        }
        void FillRoundedRectangle( const D2D1_ROUNDED_RECT& roundedRect, ID2D1Brush* brush ) const
        {
            FillRoundedRectangle( &roundedRect, brush );
        }
        void FillRoundedRectangle( const D2D1_ROUNDED_RECT* roundedRect, const Brush& brush ) const
        {
            FillRoundedRectangle( roundedRect, brush.GetInterfacePointer<ID2D1Brush>( ) );
        }
        void FillRoundedRectangle( const D2D1_ROUNDED_RECT& roundedRect, const Brush& brush ) const
        {
            FillRoundedRectangle( &roundedRect, brush.GetInterfacePointer<ID2D1Brush>( ) );
        }


        
        /// <summary>
        /// Draws the outline of the specified ellipse using the specified stroke style.
        /// </summary>
        /// <param name="roundedRect">
        /// The position and radius of the ellipse to draw, in device-independent pixels.
        /// </param>
        /// <param name="brush">
        /// The brush used to paint the ellipse's outline.
        /// </param>
        /// <param name="strokeWidth">
        /// The width of the stroke, in device-independent pixels. The value must 
        /// be greater than or equal to 0.0f. If this parameter isn't specified, 
        /// it defaults to 1.0f. The stroke is centered on the line.
        /// </param>
        /// <param name="strokeStyle">
        /// The style of stroke to apply to the ellipse's outline, or nullptr 
        /// to paint a solid stroke.
        /// </param>
        void DrawEllipse( const D2D1_ELLIPSE* ellipse, ID2D1Brush* brush, FLOAT strokeWidth = 1.0f, ID2D1StrokeStyle* strokeStyle = nullptr ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->DrawEllipse( ellipse, brush, strokeWidth, strokeStyle );
        }
        void DrawEllipse( const D2D1_ELLIPSE& ellipse, ID2D1Brush* brush, FLOAT strokeWidth = 1.0f, ID2D1StrokeStyle* strokeStyle = nullptr ) const
        {
            DrawEllipse( &ellipse, brush, strokeWidth, strokeStyle );
        }
        void DrawEllipse( const D2D1_ELLIPSE* ellipse, ID2D1Brush* brush, FLOAT strokeWidth, const StrokeStyle& strokeStyle ) const
        {
            DrawEllipse( ellipse, brush, strokeWidth, strokeStyle.GetInterfacePointer<ID2D1StrokeStyle>( ) );
        }
        void DrawEllipse( const D2D1_ELLIPSE* ellipse, const Brush& brush, FLOAT strokeWidth, const StrokeStyle& strokeStyle ) const
        {
            DrawEllipse( ellipse, brush.GetInterfacePointer<ID2D1Brush>( ), strokeWidth, strokeStyle.GetInterfacePointer<ID2D1StrokeStyle>( ) );
        }
        void DrawEllipse( const D2D1_ELLIPSE* ellipse, const Brush& brush, FLOAT strokeWidth = 1.0f ) const
        {
            DrawEllipse( ellipse, brush.GetInterfacePointer<ID2D1Brush>( ), strokeWidth, nullptr );
        }

        void DrawEllipse( const D2D1_ELLIPSE& ellipse, ID2D1Brush* brush, FLOAT strokeWidth, const StrokeStyle& strokeStyle ) const
        {
            DrawEllipse( &ellipse, brush, strokeWidth, strokeStyle.GetInterfacePointer<ID2D1StrokeStyle>( ) );
        }
        void DrawEllipse( const D2D1_ELLIPSE& ellipse, const Brush& brush, FLOAT strokeWidth, const StrokeStyle& strokeStyle ) const
        {
            DrawEllipse( &ellipse, brush.GetInterfacePointer<ID2D1Brush>( ), strokeWidth, strokeStyle.GetInterfacePointer<ID2D1StrokeStyle>( ) );
        }
        void DrawEllipse( const D2D1_ELLIPSE& ellipse, const Brush& brush, FLOAT strokeWidth = 1.0f ) const
        {
            DrawEllipse( &ellipse, brush.GetInterfacePointer<ID2D1Brush>( ), strokeWidth, nullptr );
        }


        /// <summary>
        /// Paints the interior of the specified ellipse.
        /// </summary>
        /// <param name="ellipse">
        /// The position and radius, in device-independent pixels, 
        /// of the ellipse to paint.
        /// </param>
        /// <param name="brush">
        /// The brush used to paint the interior of the ellipse.
        /// </param>
        void FillEllipse( const D2D1_ELLIPSE* ellipse, ID2D1Brush* brush ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->FillEllipse( ellipse, brush );
        }
        void FillEllipse( const D2D1_ELLIPSE& ellipse, ID2D1Brush* brush ) const
        {
            FillEllipse( &ellipse, brush );
        }
        void FillEllipse( const D2D1_ELLIPSE* ellipse, const Brush& brush ) const
        {
            FillEllipse( ellipse, brush.GetInterfacePointer<ID2D1Brush>( ) );
        }
        void FillEllipse( const D2D1_ELLIPSE& ellipse, const Brush& brush ) const
        {
            FillEllipse( &ellipse, brush.GetInterfacePointer<ID2D1Brush>( ) );
        }

        /// <summary>
        /// Draws the outline of the specified geometry using 
        /// the specified stroke style.
        /// </summary>
        /// <param name="geometry">
        /// The geometry to draw.
        /// </param>
        /// <param name="brush">
        /// The brush used to paint the geometry's stroke.
        /// </param>
        /// <param name="strokeWidth">
        /// The width of the stroke, in device-independent pixels. 
        /// The value must be greater than or equal to 0.0f. If 
        /// this parameter isn't specified, it defaults to 1.0f. 
        /// The stroke is centered on the line.
        /// </param>
        /// <param name="strokeStyle">
        /// The style of stroke to apply to the geometry's outline, 
        /// or nullptr to paint a solid stroke.
        /// </param>
        void DrawGeometry( ID2D1Geometry* geometry, ID2D1Brush* brush, FLOAT strokeWidth = 1.0f, ID2D1StrokeStyle* strokeStyle = nullptr ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->DrawGeometry( geometry, brush, strokeWidth, strokeStyle );
        }
        void DrawGeometry( const Geometry& geometry, ID2D1Brush* brush, FLOAT strokeWidth = 1.0f, ID2D1StrokeStyle* strokeStyle = nullptr ) const
        {
            DrawGeometry( geometry.GetInterfacePointer<ID2D1Geometry>( ), brush, strokeWidth, strokeStyle );
        }
        void DrawGeometry( ID2D1Geometry* geometry, ID2D1Brush* brush, FLOAT strokeWidth, const StrokeStyle& strokeStyle ) const
        {
            DrawGeometry( geometry, brush, strokeWidth, strokeStyle.GetInterfacePointer<ID2D1StrokeStyle>( ) );
        }
        void DrawGeometry( ID2D1Geometry* geometry, const Brush& brush, FLOAT strokeWidth, const StrokeStyle& strokeStyle ) const
        {
            DrawGeometry( geometry, brush.GetInterfacePointer<ID2D1Brush>( ), strokeWidth, strokeStyle.GetInterfacePointer<ID2D1StrokeStyle>( ) );
        }
        void DrawGeometry( ID2D1Geometry* geometry, const Brush& brush, FLOAT strokeWidth = 1.0f ) const
        {
            DrawGeometry( geometry, brush.GetInterfacePointer<ID2D1Brush>( ), strokeWidth, nullptr );
        }
        void DrawGeometry( const Geometry& geometry, ID2D1Brush* brush, FLOAT strokeWidth, const StrokeStyle& strokeStyle ) const
        {
            DrawGeometry( geometry.GetInterfacePointer<ID2D1Geometry>(), brush, strokeWidth, strokeStyle.GetInterfacePointer<ID2D1StrokeStyle>( ) );
        }
        void DrawGeometry( const Geometry& geometry, const Brush& brush, FLOAT strokeWidth, const StrokeStyle& strokeStyle ) const
        {
            DrawGeometry( geometry.GetInterfacePointer<ID2D1Geometry>( ), brush.GetInterfacePointer<ID2D1Brush>( ), strokeWidth, strokeStyle.GetInterfacePointer<ID2D1StrokeStyle>( ) );
        }
        void DrawGeometry( const Geometry& geometry, const Brush& brush, FLOAT strokeWidth = 1.0f ) const
        {
            DrawGeometry( geometry.GetInterfacePointer<ID2D1Geometry>( ), brush.GetInterfacePointer<ID2D1Brush>( ), strokeWidth, nullptr );
        }

        /// <summary>
        /// Paints the interior of the specified geometry.
        /// </summary>
        /// <param name="geometry">
        /// The geometry to paint.
        /// </param>
        /// <param name="brush">
        /// The brush used to paint the geometry's interior.
        /// </param>
        /// <param name="opacityBrush">
        /// The opacity mask to apply to the geometry, or nullptr for no 
        /// opacity mask. If an opacity mask (the opacityBrush parameter) 
        /// is specified, brush must be an ID2D1BitmapBrush that has its 
        /// x- and y-extend modes set to D2D1_EXTEND_MODE_CLAMP. 
        /// </param>
        /// <remarks>
        /// <p>
        /// If the opacityBrush parameter is not nullptr, the alpha value of 
        /// each pixel of the mapped opacityBrush is used to determine the 
        /// resulting opacity of each corresponding pixel of the geometry. 
        /// Only the alpha value of each color in the brush is used for this 
        /// processing; all other color information is ignored.
        /// </p>
        /// <p>
        /// The alpha value specified by the brush is multiplied by the alpha 
        /// value of the geometry after the geometry has been painted by brush.
        /// </p>
        /// </remarks>
        void FillGeometry( ID2D1Geometry* geometry, ID2D1Brush* brush, ID2D1Brush* opacityBrush = nullptr ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->FillGeometry( geometry, brush, opacityBrush );
        }
        void FillGeometry( ID2D1Geometry* geometry, ID2D1Brush* brush, const Brush& opacityBrush ) const
        {
            FillGeometry( geometry, brush, opacityBrush.GetInterfacePointer<ID2D1Brush>( ) );
        }
        void FillGeometry( ID2D1Geometry* geometry, const Brush& brush, const Brush& opacityBrush ) const
        {
            FillGeometry( geometry, brush.GetInterfacePointer<ID2D1Brush>(), opacityBrush.GetInterfacePointer<ID2D1Brush>( ) );
        }
        void FillGeometry( ID2D1Geometry* geometry, const Brush& brush, ID2D1Brush* opacityBrush = nullptr ) const
        {
            FillGeometry( geometry, brush.GetInterfacePointer<ID2D1Brush>( ), opacityBrush );
        }
        void FillGeometry( const Geometry& geometry, const Brush& brush, ID2D1Brush* opacityBrush = nullptr ) const
        {
            FillGeometry( geometry.GetInterfacePointer<ID2D1Geometry>(), brush.GetInterfacePointer<ID2D1Brush>( ), opacityBrush );
        }
        void FillGeometry( const Geometry& geometry, const Brush& brush, const Brush& opacityBrush ) const
        {
            FillGeometry( geometry.GetInterfacePointer<ID2D1Geometry>( ), brush.GetInterfacePointer<ID2D1Brush>( ), opacityBrush.GetInterfacePointer<ID2D1Brush>( ) );
        }



        /// <summary>
        /// Paints the interior of the specified mesh.
        /// </summary>
        /// <param name="mesh">
        /// The mesh to paint.
        /// </param>
        /// <param name="brush">
        /// The brush used to paint the mesh.
        /// </param>
        /// <remarks>
        /// <p>
        /// The current anti-alias mode of the render target must be 
        /// D2D1_ANTIALIAS_MODE_ALIASED when FillMesh is called. To 
        /// change the render target's anti-alias mode, use the 
        /// SetAntialiasMode function.
        /// </p>
        /// <p>
        /// FillMesh does not expect a particular winding order for the 
        /// triangles in the ID2D1Mesh; both clockwise and counter-clockwise 
        /// will work.
        /// </p>
        /// </remarks>
        void FillMesh( ID2D1Mesh* mesh, ID2D1Brush* brush ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->FillMesh( mesh, brush );
        }
        void FillMesh( ID2D1Mesh* mesh, const Brush& brush ) const
        {
            FillMesh( mesh, brush.GetInterfacePointer<ID2D1Brush>() );
        }
        void FillMesh( const Mesh& mesh, ID2D1Brush* brush ) const
        {
            FillMesh( mesh.GetInterfacePointer<ID2D1Mesh>( ), brush );
        }
        void FillMesh( const Mesh& mesh, const Brush& brush ) const
        {
            FillMesh( mesh.GetInterfacePointer<ID2D1Mesh>( ), brush.GetInterfacePointer<ID2D1Brush>( ) );
        }

        /// <summary>
        /// Applies the opacity mask described by the specified bitmap to a 
        /// brush and uses that brush to paint a region of the render target.
        /// </summary>
        /// <param name="opacityMask">
        /// The opacity mask to apply to the brush. The alpha value of each 
        /// pixel in the region specified by sourceRectangle is multiplied 
        /// with the alpha value of the brush after the brush has been mapped 
        /// to the area defined by destinationRectangle.
        /// </param>
        /// <param name="brush">
        /// The brush used to paint the region of the render target specified 
        /// by destinationRectangle.
        /// </param>
        /// <param name="content">
        /// The type of content the opacity mask contains. The value is used 
        /// to determine the color space in which the opacity mask is blended.
        /// </param>
        /// <param name="destinationRectangle">
        /// The region of the render target to paint, in device-independent pixels, 
        /// or NULL. If nullptr is specified, the brush paints a rectangle the same 
        /// size as sourceRectangle, but positioned on the origin. If sourceRectangle 
        /// isn't specified, the brush paints a rectangle the same size as the 
        /// opacityMask bitmap and positioned on the origin.
        /// </param>
        /// <param name="sourceRectangle">
        /// 
        /// </param>
        void FillOpacityMask( ID2D1Bitmap* opacityMask, ID2D1Brush* brush, D2D1_OPACITY_MASK_CONTENT content = D2D1_OPACITY_MASK_CONTENT_GRAPHICS, const D2D1_RECT_F* destinationRectangle = nullptr, const D2D1_RECT_F* sourceRectangle = nullptr ) const
        {
#ifdef _DEBUG
            CheckPointerNotNull( opacityMask );
            CheckPointerNotNull( brush );
#endif
            InterfaceType* pInterface = GetInterface( );
            pInterface->FillOpacityMask( opacityMask, brush, content, destinationRectangle, sourceRectangle );
        }

        void FillOpacityMask( const Bitmap& opacityMask, ID2D1Brush* brush, D2D1_OPACITY_MASK_CONTENT content = D2D1_OPACITY_MASK_CONTENT_GRAPHICS, const D2D1_RECT_F* destinationRectangle = nullptr, const D2D1_RECT_F* sourceRectangle = nullptr ) const
        {
            FillOpacityMask( opacityMask.GetInterfacePointer<ID2D1Bitmap>(), brush, content, destinationRectangle, sourceRectangle );
        }
        void FillOpacityMask( const Bitmap& opacityMask, const Brush& brush, D2D1_OPACITY_MASK_CONTENT content = D2D1_OPACITY_MASK_CONTENT_GRAPHICS, const D2D1_RECT_F* destinationRectangle = nullptr, const D2D1_RECT_F* sourceRectangle = nullptr ) const
        {
            FillOpacityMask( opacityMask.GetInterfacePointer<ID2D1Bitmap>( ), brush.GetInterfacePointer<ID2D1Brush>(), content, destinationRectangle, sourceRectangle );
        }


        /// <summary>
        /// Draws the specified bitmap after scaling it to the size 
        /// of the specified rectangle.
        /// </summary>
        /// <param name="bitmap">
        /// The bitmap to render.
        /// </param>
        /// <param name="destinationRectangle">
        /// The size and position, in device-independent pixels in 
        /// the render target's coordinate space, of the area to which 
        /// the bitmap is drawn. If the rectangle is not well-ordered, 
        /// nothing is drawn, but the render target does not enter an 
        /// error state.
        /// </param>
        /// <param name="opacity">
        /// A value between 0.0f and 1.0f, inclusive, that specifies 
        /// the opacity value to be applied to the bitmap; this value 
        /// is multiplied against the alpha values of the bitmap's 
        /// contents. Default is 1.0f.
        /// </param>
        /// <param name="interpolationMode">
        /// The interpolation mode to use if the bitmap is scaled or 
        /// rotated by the drawing operation. The default value is 
        /// D2D1_BITMAP_INTERPOLATION_MODE_LINEAR.
        /// </param>
        /// <param name="sourceRectangle">
        /// The size and position, in device-independent pixels in 
        /// the bitmap's coordinate space, of the area within the 
        /// bitmap to draw; nullptr to draw the entire bitmap.
        /// </param>
        void DrawBitmap( ID2D1Bitmap* bitmap, const D2D1_RECT_F* destinationRectangle, FLOAT opacity = 1.0f, D2D1_BITMAP_INTERPOLATION_MODE interpolationMode = D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, const D2D1_RECT_F* sourceRectangle = nullptr ) const
        {
#ifdef _DEBUG
            CheckPointerNotNull( bitmap );
#endif
            InterfaceType* pInterface = GetInterface( );
            pInterface->DrawBitmap( bitmap, destinationRectangle, opacity, interpolationMode, sourceRectangle );
        }
        void DrawBitmap( const Bitmap& bitmap, const D2D1_RECT_F* destinationRectangle, FLOAT opacity = 1.0f, D2D1_BITMAP_INTERPOLATION_MODE interpolationMode = D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, const D2D1_RECT_F* sourceRectangle = nullptr ) const
        {
            DrawBitmap( bitmap.GetInterfacePointer<ID2D1Bitmap>(), destinationRectangle, opacity, interpolationMode, sourceRectangle );
        }


        /// <summary>
        /// Draws the specified text using the format information 
        /// provided by an IDWriteTextFormat object.
        /// </summary>
        /// <param name="string">
        /// A pointer to an array of Unicode characters to draw.
        /// </param>
        /// <param name="stringLength">
        /// The number of characters in string.
        /// </param>
        /// <param name="textFormat">
        /// An object that describes formatting details of the text 
        /// to draw, such as the font, the font size, and flow direction.
        /// </param>
        /// <param name="layoutRect">
        /// The size and position of the area in which the text is drawn.
        /// </param>
        /// <param name="defaultForegroundBrush">
        /// The brush used to paint the text.
        /// </param>
        /// <param name="options">
        /// A value that indicates whether the text should be snapped to 
        /// pixel boundaries and whether the text should be clipped to the 
        /// layout rectangle. The default value is D2D1_DRAW_TEXT_OPTIONS_NONE, 
        /// which indicates that text should be snapped to pixel boundaries 
        /// and it should not be clipped to the layout rectangle.
        /// </param>
        /// <param name="measuringMode">
        /// A value that indicates how glyph metrics are used to measure text 
        /// when it is formatted. The default value is DWRITE_MEASURING_MODE_NATURAL.
        /// </param>
        void DrawText( const WCHAR* string, UINT32 stringLength, IDWriteTextFormat* textFormat, const D2D1_RECT_F* layoutRect, ID2D1Brush* defaultForegroundBrush, D2D1_DRAW_TEXT_OPTIONS options = D2D1_DRAW_TEXT_OPTIONS_NONE, DWRITE_MEASURING_MODE measuringMode = DWRITE_MEASURING_MODE_NATURAL ) const
        {
#ifdef _DEBUG
            CheckPointerNotNull( string );
#endif
            InterfaceType* pInterface = GetInterface( );
            pInterface->DrawText( string, stringLength, textFormat, layoutRect, defaultForegroundBrush, options, measuringMode );
        }

        inline void DrawText( const WCHAR* string, UINT32 stringLength, const DirectWrite::TextFormat& textFormat, const D2D1_RECT_F* layoutRect, const Brush& defaultForegroundBrush, D2D1_DRAW_TEXT_OPTIONS options = D2D1_DRAW_TEXT_OPTIONS_NONE, DWRITE_MEASURING_MODE measuringMode = DWRITE_MEASURING_MODE_NATURAL ) const;


        void DrawText( const std::wstring& text, IDWriteTextFormat* textFormat, const D2D1_RECT_F* layoutRect, ID2D1Brush* defaultForegroundBrush, D2D1_DRAW_TEXT_OPTIONS options = D2D1_DRAW_TEXT_OPTIONS_NONE, DWRITE_MEASURING_MODE measuringMode = DWRITE_MEASURING_MODE_NATURAL ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->DrawText( text.c_str( ), static_cast<UINT32>( text.length( ) ), textFormat, layoutRect, defaultForegroundBrush, options, measuringMode );
        }

        inline void DrawText( const std::wstring& text, const DirectWrite::TextFormat& textFormat, const D2D1_RECT_F* layoutRect, const Brush& defaultForegroundBrush, D2D1_DRAW_TEXT_OPTIONS options = D2D1_DRAW_TEXT_OPTIONS_NONE, DWRITE_MEASURING_MODE measuringMode = DWRITE_MEASURING_MODE_NATURAL ) const;


        /// <summary>
        /// Draws the formatted text described by the specified IDWriteTextLayout object.
        /// </summary>
        /// <param name="origin">
        /// The point, in device-independent pixels, at which the upper-left corner 
        /// of the text described by textLayout is drawn.
        /// </param>
        /// <param name="textLayout">
        /// The formatted text to draw. Any drawing effects that do not inherit from 
        /// ID2D1Resource are ignored. If there are drawing effects that inherit from 
        /// ID2D1Resource that are not brushes, this method fails and the render target
        /// is put in an error state.
        /// </param>
        /// <param name="defaultForegroundBrush">
        /// The brush used to paint any text in textLayout that does not already have 
        /// a brush associated with it as a drawing effect (specified by the 
        /// IDWriteTextLayout::SetDrawingEffect method).
        /// </param>
        /// <param name="options">
        /// A value that indicates whether the text should be snapped to pixel boundaries 
        /// and whether the text should be clipped to the layout rectangle. The default 
        /// value is D2D1_DRAW_TEXT_OPTIONS_NONE, which indicates that text should be 
        /// snapped to pixel boundaries and it should not be clipped to the layout rectangle.
        /// </param>
        void DrawTextLayout( const D2D1_POINT_2F& origin, IDWriteTextLayout* textLayout, ID2D1Brush* defaultForegroundBrush, D2D1_DRAW_TEXT_OPTIONS options = D2D1_DRAW_TEXT_OPTIONS_NONE ) const
        {
#ifdef _DEBUG
            CheckPointerNotNull( textLayout );
#endif
            InterfaceType* pInterface = GetInterface( );
            pInterface->DrawTextLayout( origin, textLayout, defaultForegroundBrush, options );
        }

        inline void DrawTextLayout( const D2D1_POINT_2F& origin, const DirectWrite::TextLayout& textLayout, const Brush& defaultForegroundBrush, D2D1_DRAW_TEXT_OPTIONS options = D2D1_DRAW_TEXT_OPTIONS_NONE ) const;


        /// <summary>
        /// Draws the specified glyphs.
        /// </summary>
        /// <param name="baselineOrigin">
        /// The origin, in device-independent pixels, of the glyphs' baseline.
        /// </param>
        /// <param name="glyphRun">
        /// The glyphs to render.
        /// </param>
        /// <param name="foregroundBrush">
        /// The brush used to paint the specified glyphs.
        /// </param>
        /// <param name="measuringMode">
        /// A value that indicates how glyph metrics are used to measure text 
        /// when it is formatted. The default value is DWRITE_MEASURING_MODE_NATURAL.
        /// </param>
        void DrawGlyphRun( const D2D1_POINT_2F& baselineOrigin, const DWRITE_GLYPH_RUN* glyphRun, ID2D1Brush* foregroundBrush, DWRITE_MEASURING_MODE measuringMode = DWRITE_MEASURING_MODE_NATURAL ) const
        {
#ifdef _DEBUG
            CheckPointerNotNull( glyphRun );
            CheckPointerNotNull( foregroundBrush );
#endif
            InterfaceType* pInterface = GetInterface( );
            pInterface->DrawGlyphRun( baselineOrigin, glyphRun, foregroundBrush, measuringMode );
        }

        void DrawGlyphRun( const D2D1_POINT_2F& baselineOrigin, const DWRITE_GLYPH_RUN* glyphRun, const Brush& foregroundBrush, DWRITE_MEASURING_MODE measuringMode = DWRITE_MEASURING_MODE_NATURAL ) const
        {
            DrawGlyphRun( baselineOrigin, glyphRun, foregroundBrush.GetInterfacePointer<ID2D1Brush>( ), measuringMode );
        }

        /// <summary>
        /// Applies the specified transform to the render target, replacing 
        /// the existing transformation. All subsequent drawing operations 
        /// occur in the transformed space.
        /// </summary>
        /// <param name="transform">
        /// The transform to apply to the render target.
        /// </param>
        void SetTransform( const D2D1_MATRIX_3X2_F* transform ) const
        {
#ifdef _DEBUG
            CheckPointerNotNull( transform );
#endif
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetTransform( transform );
        }
        void SetTransform( const D2D1_MATRIX_3X2_F& transform ) const
        {
            SetTransform( &transform );
        }


        /// <summary>
        /// Gets the current transform of the render target.
        /// </summary>
        /// <param name="transform">
        /// When this returns, contains the current transform of the render 
        /// target. This parameter is passed uninitialized.
        /// </param>
        void GetTransform( D2D1_MATRIX_3X2_F* transform ) const
        {
#ifdef _DEBUG
            CheckPointerNotNull( transform );
#endif
            InterfaceType* pInterface = GetInterface( );
            pInterface->GetTransform( transform );
        }
        void GetTransform( D2D1_MATRIX_3X2_F& transform ) const
        {
            GetTransform( &transform );
        }
        D2D1_MATRIX_3X2_F GetTransform( ) const
        {
            D2D1_MATRIX_3X2_F result{};
            GetTransform( &result );
            return result;
        }


        /// <summary>
        /// Sets the anti-aliasing mode of the render target. The anti-aliasing 
        /// mode applies to all subsequent drawing operations, excluding text 
        /// and glyph drawing operations.
        /// </summary>
        /// <param name="antialiasMode">
        /// The anti-aliasing mode for future drawing operations.
        /// </param>
        /// <remarks>
        /// To specify the anti-aliasing mode for text and glyph operations, use 
        /// the SetTextAntialiasMode function.
        /// </remarks>
        void SetAntialiasMode( D2D1_ANTIALIAS_MODE antialiasMode ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetAntialiasMode( antialiasMode );
        }

        /// <summary>
        /// Retrieves the current anti-aliasing mode for non-text drawing operations.
        /// </summary>
        /// <returns>
        /// The current anti-aliasing mode for non-text drawing operations.
        /// </returns>
        D2D1_ANTIALIAS_MODE GetAntialiasMode( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetAntialiasMode( );
        }

        /// <summary>
        /// Specifies the anti-aliasing mode to use for subsequent text and glyph 
        /// drawing operations.
        /// </summary>
        /// <param name="textAntialiasMode">
        /// The anti-aliasing mode to use for subsequent text and glyph drawing operations.
        /// </param>
        void SetTextAntialiasMode( D2D1_TEXT_ANTIALIAS_MODE textAntialiasMode ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetTextAntialiasMode( textAntialiasMode );
        }


        /// <summary>
        /// Gets the current anti-aliasing mode for text and glyph drawing operations.
        /// </summary>
        /// <returns>
        /// The current anti-aliasing mode for text and glyph drawing operations.
        /// </returns>
        D2D1_TEXT_ANTIALIAS_MODE GetTextAntialiasMode( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetTextAntialiasMode( );
        }


        /// <summary>
        /// Specifies text rendering options to be applied to all subsequent 
        /// text and glyph drawing operations.
        /// </summary>
        /// <param name="textRenderingParams">
        /// The text rendering options to be applied to all subsequent text and 
        /// glyph drawing operations; pass nullptr to clear current text rendering options.
        /// </param>
        /// <remarks>
        /// If the settings specified by textRenderingParams are incompatible with the render 
        /// target's text anti-aliasing mode (specified by SetTextAntialiasMode), subsequent 
        /// text and glyph drawing operations will fail and put the render target into an error 
        /// state.
        /// </remarks>
        void SetTextRenderingParams( IDWriteRenderingParams* textRenderingParams = nullptr ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetTextRenderingParams( textRenderingParams );
        }
        inline void SetTextRenderingParams( const DirectWrite::RenderingParams& textRenderingParams ) const;
        
        /// <summary>
        /// Retrieves the render target's current text rendering options.
        /// </summary>
        /// <param name="textRenderingParams">
        /// When this method returns, textRenderingParams contains the address of a pointer 
        /// to the render target's current text rendering options.
        /// </param>
        /// <remarks>
        /// If the settings specified by textRenderingParams are incompatible with the render 
        /// target's text anti-aliasing mode (specified by SetTextAntialiasMode), subsequent 
        /// text and glyph drawing operations will fail and put the render target into an error 
        /// state.
        /// </remarks>
        void GetTextRenderingParams( IDWriteRenderingParams** textRenderingParams ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->GetTextRenderingParams( textRenderingParams );
        }
        inline DirectWrite::RenderingParams GetTextRenderingParams( ) const;


        /// <summary>
        /// Specifies a label for subsequent drawing operations.
        /// </summary>
        /// <param name="tag1">
        /// A label to apply to subsequent drawing operations.
        /// </param>
        /// <param name="tag2">
        /// A label to apply to subsequent drawing operations.
        /// </param>
        /// <remarks>
        /// <p>
        /// A tag is an application-defined 64-bit value used to mark a set 
        /// of rendering operations.
        /// </p>
        /// <p>
        /// The labels specified by this method are printed by debug error 
        /// messages. If no tag is set, the default value for each tag is 0.
        /// </p>
        /// </remarks>
        void SetTags( D2D1_TAG tag1, D2D1_TAG tag2 ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetTags( tag1, tag2 );
        }


        /// <summary>
        /// Gets the label for subsequent drawing operations.
        /// </summary>
        /// <param name="tag1">
        /// When this method returns, contains the first label for subsequent 
        /// drawing operations. This parameter is passed uninitialized. If 
        /// nullptr is specified, no value is retrieved for this parameter.
        /// </param>
        /// <param name="tag2">
        /// When this method returns, contains the second label for subsequent 
        /// drawing operations. This parameter is passed uninitialized. If 
        /// nullptr is specified, no value is retrieved for this parameter.
        /// </param>
        void GetTags( D2D1_TAG* tag1, D2D1_TAG* tag2 ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->GetTags( tag1, tag2 );
        }

        D2D1_TAG GetTag1( ) const
        {
            D2D1_TAG result = 0;
            GetTags( &result, nullptr );
            return result;
        }
        D2D1_TAG GetTag2( ) const
        {
            D2D1_TAG result = 0;
            GetTags( nullptr, &result );
            return result;
        }
        std::pair<D2D1_TAG, D2D1_TAG> GetTags( ) const
        {
            std::pair<D2D1_TAG, D2D1_TAG> result{};
            GetTags( &result.first, &result.second );
            return result;
        }

        /// <summary>
        /// Adds the specified layer to the render target so that it receives 
        /// all subsequent drawing operations until PopLayer is called.
        /// </summary>
        /// <param name="layerParameters">
        /// The content bounds, geometric mask, opacity, opacity mask, and 
        /// anti-aliasing options for the layer.
        /// </param>
        /// <param name="layer">
        /// <p>
        /// The layer that receives subsequent drawing operations.
        /// </p>
        /// <p>
        /// Starting with Windows 8, this parameter is optional. If a layer 
        /// is not specified, Direct2D manages the layer resource automatically.
        /// </p>
        /// </param>
        /// <remarks>
        /// <p>
        /// The PushLayer method allows a caller to begin redirecting rendering to 
        /// a layer. All rendering operations are valid in a layer. The location 
        /// of the layer is affected by the world transform set on the render target.
        /// </p>
        /// <p>
        /// Each PushLayer must have a matching PopLayer call. If there are more 
        /// PopLayer calls than PushLayer calls, the render target is placed into 
        /// an error state. If Flush is called before all outstanding layers are popped, 
        /// the render target is placed into an error state, and an error is returned. 
        /// The error state can be cleared by a call to EndDraw.
        /// </p>
        /// <p>
        /// A particular ID2D1Layer resource can be active only at one time. In other 
        /// words, you cannot call a PushLayer method, and then immediately follow with 
        /// another PushLayer method with the same layer resource. Instead, you must 
        /// call the second PushLayer method with different layer resources.
        /// </p>
        /// </remarks>
        void PushLayer( const D2D1_LAYER_PARAMETERS* layerParameters, ID2D1Layer* layer = nullptr ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->PushLayer( layerParameters, layer );
        }
        void PushLayer( const D2D1_LAYER_PARAMETERS& layerParameters, ID2D1Layer* layer = nullptr ) const
        {
            PushLayer( &layerParameters, layer );
        }


        /// <summary>
        /// Stops redirecting drawing operations to the layer that is specified by the 
        /// last PushLayer call.
        /// </summary>
        /// <remarks>
        /// A call to PopLayer must match a previous PushLayer call.
        /// </remarks>
        void PopLayer( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->PopLayer( );
        }


        /// <summary>
        /// Executes all pending drawing commands.
        /// </summary>
        /// <param name="tag1">
        /// When this method returns, contains the tag for drawing operations that 
        /// caused errors or 0 if there were no errors. This parameter is passed 
        /// uninitialized.
        /// </param>
        /// <param name="tag2">
        /// When this method returns, contains the tag for drawing operations that 
        /// caused errors or 0 if there were no errors. This parameter is passed 
        /// uninitialized.
        /// </param>
        void Flush( D2D1_TAG* tag1 = nullptr, D2D1_TAG* tag2 = nullptr ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->Flush( tag1, tag2 );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Saves the current drawing state to the specified ID2D1DrawingStateBlock.
        /// </summary>
        /// <param name="drawingStateBlock">
        /// When this method returns, contains the current drawing state of the 
        /// render target. This parameter must be initialized before passing it 
        /// to the method.
        /// </param>
        void SaveDrawingState( ID2D1DrawingStateBlock* drawingStateBlock ) const
        {
#ifdef _DEBUG
            CheckPointerNotNull( drawingStateBlock );
#endif
            InterfaceType* pInterface = GetInterface( );
            pInterface->SaveDrawingState( drawingStateBlock );
        }
        void SaveDrawingState( const DrawingStateBlock& drawingStateBlock ) const
        {
            SaveDrawingState( drawingStateBlock.GetInterfacePointer<ID2D1DrawingStateBlock>() );
        }


        /// <summary>
        /// Sets the render target's drawing state to that of the specified 
        /// ID2D1DrawingStateBlock.
        /// </summary>
        /// <param name="drawingStateBlock">
        /// The new drawing state of the render target.
        /// </param>
        void RestoreDrawingState( ID2D1DrawingStateBlock* drawingStateBlock ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->RestoreDrawingState( drawingStateBlock );
        }
        void RestoreDrawingState( const DrawingStateBlock& drawingStateBlock ) const
        {
            RestoreDrawingState( drawingStateBlock.GetInterfacePointer<ID2D1DrawingStateBlock>( ) );
        }


        /// <summary>
        /// Specifies a rectangle to which all subsequent drawing operations are clipped.
        /// </summary>
        /// <param name="clipRect">
        /// The size and position of the clipping area, in device-independent pixels.
        /// </param>
        /// <param name="antialiasMode">
        /// The anti-aliasing mode that is used to draw the edges of clip rects that 
        /// have subpixel boundaries, and to blend the clip with the scene contents. 
        /// The blending is performed once when the PopAxisAlignedClip method is 
        /// called, and does not apply to each primitive within the layer.
        /// </param>
        void PushAxisAlignedClip( const D2D1_RECT_F* clipRect, D2D1_ANTIALIAS_MODE antialiasMode = D2D1_ANTIALIAS_MODE_PER_PRIMITIVE ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->PushAxisAlignedClip( clipRect, antialiasMode );
        }
        void PushAxisAlignedClip( const D2D1_RECT_F& clipRect, D2D1_ANTIALIAS_MODE antialiasMode = D2D1_ANTIALIAS_MODE_PER_PRIMITIVE ) const
        {
            PushAxisAlignedClip( &clipRect, antialiasMode );
        }

        /// <summary>
        /// Removes the last axis-aligned clip from the render target. After this 
        /// method is called, the clip is no longer applied to subsequent drawing 
        /// operations.
        /// </summary>
        void PopAxisAlignedClip( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->PopAxisAlignedClip( );
        }

        /// <summary>
        /// Clears the drawing area to the specified color.
        /// </summary>
        /// <param name="clearColor">
        /// The color to which the drawing area is cleared, or NULL for 
        /// transparent black.
        /// </param>
        void Clear( const D2D1_COLOR_F* clearColor = nullptr ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->Clear( clearColor );
        }
        void Clear( const D2D1_COLOR_F& clearColor ) const
        {
            Clear( &clearColor );
        }

        /// <summary>
        /// Initiates drawing on this render target.
        /// </summary>
        /// <remarks>
        /// <p>
        /// Drawing operations can only be issued between a BeginDraw and EndDraw call.
        /// </p>
        /// <p>
        /// BeginDraw and EndDraw are used to indicate that a render target is in use 
        /// by the Direct2D system. Different implementations of ID2D1RenderTarget 
        /// might behave differently when BeginDraw is called. An ID2D1BitmapRenderTarget 
        /// may be locked between BeginDraw/EndDraw calls, a DXGI surface render 
        /// target might be acquired on BeginDraw and released on EndDraw, while 
        /// an ID2D1HwndRenderTarget may begin batching at BeginDraw and may 
        /// present on EndDraw, for example.
        /// </p>
        /// <p>
        /// The BeginDraw method must be called before rendering operations can be 
        /// called, though state-setting and state-retrieval operations can be 
        /// performed even outside of BeginDraw/EndDraw.
        /// </p>
        /// <p>
        /// After BeginDraw is called, a render target will normally build up 
        /// a batch of rendering commands, but defer processing of these commands 
        /// until either an internal buffer is full, the Flush method is called, 
        /// or until EndDraw is called. The EndDraw method causes any batched 
        /// drawing operations to complete, and then returns an HRESULT indicating 
        /// the success of the operations and, optionally, the tag state of the 
        /// render target at the time the error occurred. The EndDraw method 
        /// always succeeds: it should not be called twice even if a previous 
        /// EndDraw resulted in a failing HRESULT.
        /// </p>
        /// <p>
        /// If EndDraw is called without a matched call to BeginDraw, it returns 
        /// an error indicating that BeginDraw must be called before EndDraw.
        /// </p>
        /// <p>
        /// Calling BeginDraw twice on a render target puts the target into an 
        /// error state where nothing further is drawn, and returns an appropriate 
        /// HRESULT and error information when EndDraw is called.
        /// </p>
        /// </remarks>
        void BeginDraw( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->BeginDraw( );
        }

        /// <summary>
        /// Ends drawing operations on the render target and indicates 
        /// the current error state and associated tags.
        /// </summary>
        /// <param name="tag1">
        /// When this method returns, contains the tag for drawing operations that 
        /// caused errors or 0 if there were no errors. This parameter is passed 
        /// uninitialized.
        /// </param>
        /// <param name="tag2">
        /// When this method returns, contains the tag for drawing operations that 
        /// caused errors or 0 if there were no errors. This parameter is passed 
        /// uninitialized.
        /// </param>
        void EndDraw( D2D1_TAG* tag1 = nullptr, D2D1_TAG* tag2 = nullptr) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->EndDraw( tag1, tag2 );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Retrieves the pixel format and alpha mode of the render target.
        /// </summary>
        /// <returns>
        /// The pixel format and alpha mode of the render target.
        /// </returns>
        D2D1_PIXEL_FORMAT GetPixelFormat( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetPixelFormat( );
        }

        /// <summary>
        /// Sets the dots per inch (DPI) of the render target.
        /// </summary>
        /// <param name="dpiX">
        /// A value greater than or equal to zero that specifies the 
        /// horizontal DPI of the render target.
        /// </param>
        /// <param name="dpiY">
        /// A value greater than or equal to zero that specifies the 
        /// vertical DPI of the render target.
        /// </param>
        void SetDpi( FLOAT dpiX, FLOAT dpiY ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetDpi( dpiX, dpiY );
        }
        void SetDpi( const D2D1_SIZE_F& dpi ) const
        {
            SetDpi( dpi.width, dpi.height );
        }

        /// <summary>
        /// Return the render target's dots per inch (DPI).
        /// </summary>
        /// <param name="dpiX">
        /// When this method returns, contains the horizontal DPI of the 
        /// render target. This parameter is passed uninitialized.
        /// </param>
        /// <param name="dpiY">
        /// When this method returns, contains the vertical DPI of the 
        /// render target. This parameter is passed uninitialized.
        /// </param>
        /// <remarks>
        /// <p>
        /// This method indicates the mapping from pixel space to 
        /// device-independent space for the render target.
        /// </p>
        /// <p>
        /// For ID2D1HwndRenderTarget, the DPI defaults to the most recently 
        /// factory-read system DPI. The default value for all other render 
        /// targets is 96 DPI.
        /// </p>
        /// </remarks>
        void GetDpi( FLOAT* dpiX, FLOAT* dpiY ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->GetDpi( dpiX, dpiY );
        }
        void GetDpi( FLOAT& dpiX, FLOAT& dpiY ) const
        {
            GetDpi( &dpiX, &dpiY );
        }
        D2D1_SIZE_F GetDpi( ) const
        {
            D2D1_SIZE_F result{};
            GetDpi( &result.width, &result.height );
            return result;
        }

        /// <summary>
        /// Returns the size of the render target in device-independent pixels.
        /// </summary>
        /// <returns>
        /// The current size of the render target in device-independent pixels.
        /// </returns>
        D2D1_SIZE_F GetSize( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetSize( );
        }

        /// <summary>
        /// Returns the size of the render target in device pixels.
        /// </summary>
        /// <returns>
        /// The size of the render target in device pixels.
        /// </returns>
        D2D1_SIZE_U GetPixelSize( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetPixelSize( );
        }

        /// <summary>
        /// Gets the maximum size, in device-dependent units (pixels), 
        /// of any one bitmap dimension supported by the render target.
        /// </summary>
        /// <returns>
        /// The maximum size, in pixels, of any one bitmap dimension 
        /// supported by the render target.
        /// </returns>
        UINT32 GetMaximumBitmapSize( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetMaximumBitmapSize( );
        }

        /// <summary>
        /// Indicates whether the render target supports the specified properties.
        /// </summary>
        /// <param name="renderTargetProperties">
        /// The render target properties to test.
        /// </param>
        /// <returns>
        /// true if the specified render target properties are supported by this 
        /// render target; otherwise, false.
        /// </returns>
        /// <remarks>
        /// This method does not evaluate the DPI settings specified by the 
        /// renderTargetProperties parameter.
        /// </remarks>
        bool IsSupported( const D2D1_RENDER_TARGET_PROPERTIES* renderTargetProperties ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->IsSupported( renderTargetProperties ) != FALSE;
        }

    };

    /// <summary>
    /// Renders to an intermediate texture created by the 
    /// CreateCompatibleRenderTarget function.
    /// </summary>
    class BitmapRenderTarget : public RenderTarget
    {
    public:
        typedef RenderTarget Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( BitmapRenderTarget, RenderTarget, ID2D1BitmapRenderTarget, ID2D1RenderTarget )

        /// <summary>
        /// Retrieves the bitmap for this render target. 
        /// The returned bitmap can be used for drawing operations.
        /// </summary>
        /// <param name="bitmap">
        /// When this method returns, contains the address of a 
        /// pointer to the bitmap for this render target. 
        /// This bitmap can be used for drawing operations.
        /// </param>
        void GetBitmap( ID2D1Bitmap** bitmap ) const
        {
#ifdef _DEBUG
            CheckPointerNotNull( bitmap );
#endif
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetBitmap( bitmap );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        Bitmap GetBitmap( ) const
        {
            ID2D1Bitmap* ptr = nullptr;
            GetBitmap( &ptr );
            return Bitmap( ptr );
        }

    };


    inline BitmapRenderTarget RenderTarget::CreateCompatibleRenderTarget( _In_opt_ CONST D2D1_SIZE_F* desiredSize, _In_opt_ CONST D2D1_SIZE_U* desiredPixelSize, _In_opt_ CONST D2D1_PIXEL_FORMAT* desiredFormat, D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS options ) const
    {
        ID2D1BitmapRenderTarget* ptr = nullptr;
        CreateCompatibleRenderTarget( desiredSize, desiredPixelSize, desiredFormat, options, &ptr );
        return BitmapRenderTarget( ptr );
    }

    inline BitmapRenderTarget RenderTarget::CreateCompatibleRenderTarget( _In_opt_ CONST D2D1_SIZE_F* desiredSize, _In_opt_ CONST D2D1_SIZE_U* desiredPixelSize, _In_opt_ CONST D2D1_PIXEL_FORMAT& desiredFormat, D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS options ) const
    {
        return CreateCompatibleRenderTarget( desiredSize, desiredPixelSize, &desiredFormat, options );
    }
    inline BitmapRenderTarget RenderTarget::CreateCompatibleRenderTarget( _In_opt_ CONST D2D1_SIZE_F* desiredSize, _In_opt_ CONST D2D1_SIZE_U& desiredPixelSize, _In_opt_ CONST D2D1_PIXEL_FORMAT* desiredFormat, D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS options ) const
    {
        return CreateCompatibleRenderTarget( desiredSize, &desiredPixelSize, desiredFormat, options );
    }
    inline BitmapRenderTarget RenderTarget::CreateCompatibleRenderTarget( _In_opt_ CONST D2D1_SIZE_F& desiredSize, _In_opt_ CONST D2D1_SIZE_U* desiredPixelSize, _In_opt_ CONST D2D1_PIXEL_FORMAT* desiredFormat, D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS options ) const
    {
        return CreateCompatibleRenderTarget( &desiredSize, desiredPixelSize, desiredFormat, options );
    }
    inline BitmapRenderTarget RenderTarget::CreateCompatibleRenderTarget( _In_opt_ CONST D2D1_SIZE_F* desiredSize, _In_opt_ CONST D2D1_SIZE_U& desiredPixelSize, _In_opt_ CONST D2D1_PIXEL_FORMAT& desiredFormat, D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS options ) const
    {
        return CreateCompatibleRenderTarget( desiredSize, &desiredPixelSize, &desiredFormat, options );
    }
    inline BitmapRenderTarget RenderTarget::CreateCompatibleRenderTarget( _In_opt_ CONST D2D1_SIZE_F& desiredSize, _In_opt_ CONST D2D1_SIZE_U* desiredPixelSize, _In_opt_ CONST D2D1_PIXEL_FORMAT& desiredFormat, D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS options ) const
    {
        return CreateCompatibleRenderTarget( &desiredSize, desiredPixelSize, &desiredFormat, options );
    }
    inline BitmapRenderTarget RenderTarget::CreateCompatibleRenderTarget( _In_opt_ CONST D2D1_SIZE_F& desiredSize, _In_opt_ CONST D2D1_SIZE_U& desiredPixelSize, _In_opt_ CONST D2D1_PIXEL_FORMAT& desiredFormat, D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS options  ) const
    {
        return CreateCompatibleRenderTarget( &desiredSize, &desiredPixelSize, &desiredFormat, options );
    }

    inline BitmapRenderTarget RenderTarget::CreateCompatibleRenderTarget( const D2D1_SIZE_F& desiredSize, const D2D1_SIZE_U* desiredPixelSize ) const
    {
        return CreateCompatibleRenderTarget( &desiredSize, desiredPixelSize );
    }
    inline BitmapRenderTarget RenderTarget::CreateCompatibleRenderTarget( const D2D1_SIZE_F& desiredSize, const D2D1_SIZE_U& desiredPixelSize ) const
    {
        return CreateCompatibleRenderTarget( &desiredSize, &desiredPixelSize );
    }
    inline BitmapRenderTarget RenderTarget::CreateCompatibleRenderTarget( const D2D1_SIZE_F& desiredSize, const D2D1_PIXEL_FORMAT* desiredFormat ) const
    {
        return CreateCompatibleRenderTarget( &desiredSize, nullptr, desiredFormat );
    }
    inline BitmapRenderTarget RenderTarget::CreateCompatibleRenderTarget( const D2D1_SIZE_F& desiredSize, const D2D1_PIXEL_FORMAT& desiredFormat ) const
    {
        return CreateCompatibleRenderTarget( &desiredSize, nullptr, &desiredFormat );
    }
    inline BitmapRenderTarget RenderTarget::CreateCompatibleRenderTarget( const D2D1_SIZE_F& desiredSize ) const
    {
        return CreateCompatibleRenderTarget( &desiredSize );
    }


    /// <summary>
    /// Renders drawing instructions to a window.
    /// </summary>
    class ControlRenderTarget : public RenderTarget
    {
    public:
        typedef RenderTarget Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( ControlRenderTarget, RenderTarget, ID2D1HwndRenderTarget, ID2D1RenderTarget )

        /// <summary>
        /// Indicates whether the HWND associated with this render target is occluded.
        /// </summary>
        /// <returns>
        /// A value that indicates whether the HWND associated with this render target 
        /// is occluded.
        /// </returns>
        /// <remarks>
        /// If the window was occluded the last time that EndDraw was called, the next 
        /// time that the render target calls CheckWindowState, it will return 
        /// D2D1_WINDOW_STATE_OCCLUDED regardless of the current window state. If you 
        /// want to use CheckWindowState to determine the current window state, you 
        /// should call CheckWindowState after every EndDraw call and ignore its return 
        /// value. This call will ensure that your next call to CheckWindowState state 
        /// will return the actual window state.
        /// </remarks>
        D2D1_WINDOW_STATE CheckWindowState( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->CheckWindowState( );
        }

        /// <summary>
        /// Changes the size of the render target to the specified pixel size.
        /// </summary>
        /// <param name="pixelSize">
        /// The new size of the render target in device pixels.
        /// </param>
        /// <remarks>
        /// <p>
        /// After this method is called, the contents of the render target's back-buffer 
        /// are not defined, even if the D2D1_PRESENT_OPTIONS_RETAIN_CONTENTS option was 
        /// specified when the render target was created.
        /// </p>
        /// <p>
        /// This operation might fail if there is insufficient video memory or system memory, 
        /// or if the render target is resized beyond the maximum bitmap size. If the method 
        /// fails, the render target will be placed in a zombie state and D2DERR_RECREATE_TARGET 
        /// will be returned from it when EndDraw is called. In addition an appropriate 
        /// failure result will be returned from Resize.
        /// </p>
        /// </remarks>
        void Resize( const D2D1_SIZE_U* pixelSize ) const
        {
#ifdef _DEBUG
            CheckPointerNotNull( pixelSize );
#endif
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->Resize( pixelSize );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void Resize( const D2D1_SIZE_U& pixelSize )
        {
            Resize( &pixelSize );
        }

        /// <summary>
        /// Returns the HWND associated with this render target.
        /// </summary>
        /// <returns>
        /// The HWND associated with this render target.
        /// </returns>
        HWND GetHwnd( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetHwnd( );
        }
    };

    /// <summary>
    /// Provides access to a device context that can accept GDI drawing commands.
    /// </summary>
    /// <remarks>
    /// <p>
    /// You don't create an ID2D1GdiInteropRenderTarget object directly; instead, 
    /// you use the QueryInterface method of an existing render target instance to 
    /// provide an ID2D1GdiInteropRenderTarget version of that render target.
    /// </p>
    /// <p>
    /// Not all render targets support the ID2D1GdiInteropRenderTarget interface. 
    /// The render target must be GDI-compatible (the D2D1_RENDER_TARGET_USAGE_GDI_COMPATIBLE 
    /// flag was specified when creating the render target), use the DXGI_FORMAT_B8G8R8A8_UNORM 
    /// pixel format, and use the D2D1_ALPHA_MODE_PREMULTIPLIED or D2D1_ALPHA_MODE_IGNORE alpha mode.
    /// </p>
    /// <p>
    /// Note that the QueryInterface method always succeeds; if the render target doesn't 
    /// support the ID2D1GdiInteropRenderTarget interface, calling GetDC will fail. 
    /// (For render targets created through the CreateCompatibleRenderTarget method, 
    /// the render target that created it must have these settings.)
    /// </p>
    /// <p>
    /// To test whether a given render target supports the ID2D1GdiInteropRenderTarget 
    /// interface, create a D2D1_RENDER_TARGET_PROPERTIES that specifies GDI compatibility 
    /// and the appropriate pixel format, then call the render target's IsSupported method 
    /// to see whether the render target is GDI-compatible.
    /// </p>
    /// </remarks>
    class GdiInteropRenderTarget : public RenderTarget
    {
    public:
        typedef RenderTarget Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( GdiInteropRenderTarget, RenderTarget, ID2D1GdiInteropRenderTarget, ID2D1RenderTarget )

        /// <summary>
        /// Retrieves the device context associated with this render target.
        /// </summary>
        /// <param name="mode">
        /// A value that specifies whether the device context should be cleared.
        /// </param>
        /// <param name="hdc">
        /// When this method returns, contains the device context associated 
        /// with this render target. You must allocate storage for this parameter.
        /// </param>
        void GetDC( D2D1_DC_INITIALIZE_MODE mode, HDC* hdc ) const
        {
#ifdef _DEBUG
            CheckPointerNotNull( hdc );
#endif
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetDC( mode, hdc );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        HDC GetDC( D2D1_DC_INITIALIZE_MODE mode = D2D1_DC_INITIALIZE_MODE_COPY ) const
        {
            HDC result = 0;
            GetDC( mode, &result );
            return result;
        }


        /// <summary>
        /// Indicates that drawing with the device context retrieved using the 
        /// GetDC method is finished.
        /// </summary>
        /// <param name="update">
        /// The modified region of the device context, or nullptr to specify the 
        /// entire render target.
        /// </param>
        void ReleaseDC( const RECT* update = nullptr ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->ReleaseDC( update );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

    };


    /// <summary>
    /// Issues drawing commands to a GDI device context.
    /// </summary>
    /// <remarks>
    /// 
    /// </remarks>
    class DeviceContextRenderTarget : public RenderTarget
    {
    public:
        typedef RenderTarget Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( DeviceContextRenderTarget, RenderTarget, ID2D1DCRenderTarget, ID2D1RenderTarget )

        /// <summary>
        /// Binds the render target to the device context to which it 
        /// issues drawing commands.
        /// </summary>
        /// <param name="hDC">
        /// The device context to which the render target issues 
        /// drawing commands.
        /// </param>
        /// <param name="pSubRect">
        /// The dimensions of the handle to a device context (HDC) to which 
        /// the render target is bound.
        /// </param>
        void BindDC( const HDC hDC, const RECT* subRect ) const
        {
#ifdef _DEBUG
            CheckPointerNotNull( subRect );
#endif
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->BindDC( hDC, subRect );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void BindDC( const HDC hDC, const RECT& subRect ) const
        {
            BindDC( hDC, &subRect );
        }

    };


    


    /// <summary>
    /// Creates Direct2D resources.
    /// </summary>
    class Factory : public Unknown
    {
    public:
        typedef Unknown Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( Factory, Unknown, ID2D1Factory, IUnknown )

        /// <summary>
        /// Creates a factory object that can be used to create Direct2D resources.
        /// </summary>
        Factory( D2D1_FACTORY_TYPE factoryType )
        {
            InterfaceType* pInterface = nullptr;
            HRESULT hr = D2D1CreateFactory( factoryType, &pInterface );
            HCC_COM_CHECK_HRESULT( hr );
            unknown_ = pInterface;
        }

        /// <summary>
        /// Forces the factory to refresh any system defaults that it 
        /// might have changed since factory creation.
        /// </summary>
        void ReloadSystemMetrics( ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->ReloadSystemMetrics( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Creates an ID2D1RectangleGeometry.
        /// </summary>
        /// <param name="rectangle">
        /// The coordinates of the rectangle geometry.
        /// </param>
        /// <param name="rectangleGeometry">
        /// When this method returns, contains the address of the pointer 
        /// to the rectangle geometry created by this function.
        /// </param>
        void CreateRectangleGeometry( const D2D1_RECT_F* rectangle, ID2D1RectangleGeometry** rectangleGeometry ) const
        {
#ifdef _DEBUG
            CheckPointerNotNull( rectangle );
#endif
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateRectangleGeometry( rectangle, rectangleGeometry );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void CreateRectangleGeometry( const D2D1_RECT_F& rectangle, ID2D1RectangleGeometry** rectangleGeometry ) const
        {
            CreateRectangleGeometry( &rectangle, rectangleGeometry );
        }
        RectangleGeometry CreateRectangleGeometry( const D2D1_RECT_F* rectangle ) const
        {
            ID2D1RectangleGeometry* ptr = nullptr;
            CreateRectangleGeometry( rectangle, &ptr );
            return RectangleGeometry( ptr );
        }
        RectangleGeometry CreateRectangleGeometry( const D2D1_RECT_F& rectangle ) const
        {
            return CreateRectangleGeometry( &rectangle );
        }
        RectangleGeometry CreateRectangleGeometry( const D2D1_POINT_2F* position, const D2D1_SIZE_F* size ) const
        {
#ifdef _DEBUG
            CheckPointerNotNull( position );
            CheckPointerNotNull( size );
#endif
            D2D1_RECT_F rectangle{ position->x, position->y, size->width + position->x, size->height + position->y };
            return CreateRectangleGeometry( &rectangle );
        }
        RectangleGeometry CreateRectangleGeometry( const D2D1_POINT_2F& position, const D2D1_SIZE_F& size ) const
        {
            D2D1_RECT_F rectangle{ position.x, position.y, size.width + position.x, size.height + position.y };
            return CreateRectangleGeometry( &rectangle );
        }
        RectangleGeometry CreateRectangleGeometry( FLOAT left, FLOAT top, FLOAT right, FLOAT bottom ) const
        {
            D2D1_RECT_F rectangle{ left, top, right, bottom };
            return CreateRectangleGeometry( &rectangle );
        }

        /// <summary>
        /// Creates an ID2D1RoundedRectangleGeometry.
        /// </summary>
        /// <param name="roundedRectangle">
        /// The coordinates and corner radii of the rounded rectangle geometry.
        /// </param>
        /// <param name="roundedRectangleGeometry">
        /// When this method returns, contains the address of the pointer to 
        /// the rounded rectangle geometry created by this method.
        /// </param>
        void CreateRoundedRectangleGeometry( const D2D1_ROUNDED_RECT* roundedRectangle, ID2D1RoundedRectangleGeometry** roundedRectangleGeometry ) const
        {
#ifdef _DEBUG
            CheckPointerNotNull( roundedRectangle );
#endif
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateRoundedRectangleGeometry( roundedRectangle, roundedRectangleGeometry );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void CreateRoundedRectangleGeometry( const D2D1_ROUNDED_RECT& roundedRectangle, ID2D1RoundedRectangleGeometry** roundedRectangleGeometry ) const
        {
            CreateRoundedRectangleGeometry( &roundedRectangle, roundedRectangleGeometry );
        }

        RoundedRectangleGeometry CreateRoundedRectangleGeometry( const D2D1_ROUNDED_RECT* roundedRectangle ) const
        {
            ID2D1RoundedRectangleGeometry* ptr = nullptr;
            CreateRoundedRectangleGeometry( roundedRectangle, &ptr );
            return RoundedRectangleGeometry( ptr );
        }
        RoundedRectangleGeometry CreateRoundedRectangleGeometry( const D2D1_ROUNDED_RECT& roundedRectangle ) const
        {
            return CreateRoundedRectangleGeometry( roundedRectangle );
        }
        RoundedRectangleGeometry CreateRoundedRectangleGeometry( const D2D1_RECT_F* rectangle, FLOAT radiusX, FLOAT readiusY ) const
        {
#ifdef _DEBUG
            CheckPointerNotNull( rectangle );
#endif
            D2D1_ROUNDED_RECT roundedRectangle{ { rectangle->left, rectangle->top, rectangle->right, rectangle->bottom }, radiusX, readiusY };
            return CreateRoundedRectangleGeometry( &roundedRectangle );
        }
        RoundedRectangleGeometry CreateRoundedRectangleGeometry( const D2D1_RECT_F& rectangle, FLOAT radiusX, FLOAT readiusY ) const
        {
            D2D1_ROUNDED_RECT roundedRectangle{ { rectangle.left, rectangle.top, rectangle.right, rectangle.bottom }, radiusX, readiusY };
            return CreateRoundedRectangleGeometry( &roundedRectangle );
        }
        RoundedRectangleGeometry CreateRoundedRectangleGeometry( const D2D1_POINT_2F* position, const D2D1_SIZE_F* size, FLOAT radiusX, FLOAT readiusY ) const
        {
            D2D1_ROUNDED_RECT roundedRectangle{ { position->x, position->y, position->x + size->width, position->y + size->height }, radiusX, readiusY };
            return CreateRoundedRectangleGeometry( &roundedRectangle );
        }
        RoundedRectangleGeometry CreateRoundedRectangleGeometry( const D2D1_POINT_2F& position, const D2D1_SIZE_F& size, FLOAT radiusX, FLOAT readiusY ) const
        {
            D2D1_ROUNDED_RECT roundedRectangle{ { position.x, position.y, position.x + size.width, position.y + size.height }, radiusX, readiusY };
            return CreateRoundedRectangleGeometry( &roundedRectangle );
        }
        RoundedRectangleGeometry CreateRoundedRectangleGeometry( FLOAT left, FLOAT top, FLOAT right, FLOAT bottom, FLOAT radiusX, FLOAT readiusY ) const
        {
            D2D1_ROUNDED_RECT roundedRectangle{ { left, top, right, bottom }, radiusX, readiusY };
            return CreateRoundedRectangleGeometry( &roundedRectangle );
        }

        /// <summary>
        /// Creates an ID2D1EllipseGeometry.
        /// </summary>
        /// <param name="ellipse">
        /// A value that describes the center point, x-radius, and y-radius 
        /// of the ellipse geometry.
        /// </param>
        /// <param name="ellipseGeometry">
        /// When this method returns, contains the address of the pointer to 
        /// the ellipse geometry created by this method.
        /// </param>
        void CreateEllipseGeometry( const D2D1_ELLIPSE* ellipse, ID2D1EllipseGeometry** ellipseGeometry ) const
        {
#ifdef _DEBUG
            CheckPointerNotNull( ellipse );
#endif
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateEllipseGeometry( ellipse, ellipseGeometry );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void CreateEllipseGeometry( const D2D1_ELLIPSE& ellipse, ID2D1EllipseGeometry** ellipseGeometry ) const
        {
            CreateEllipseGeometry( &ellipse, ellipseGeometry );
        }

        EllipseGeometry CreateEllipseGeometry( const D2D1_ELLIPSE* ellipse ) const
        {
            ID2D1EllipseGeometry* ptr = nullptr;
            CreateEllipseGeometry( ellipse, &ptr );
            return EllipseGeometry( ptr );
        }
        EllipseGeometry CreateEllipseGeometry( const D2D1_ELLIPSE& ellipse ) const
        {
            return CreateEllipseGeometry( &ellipse );
        }
        EllipseGeometry CreateEllipseGeometry( const D2D1_POINT_2F* centerPoint, FLOAT radiusX, FLOAT radiusY ) const
        {
#ifdef _DEBUG
            CheckPointerNotNull( centerPoint );
#endif
            D2D1_ELLIPSE ellipse{ *centerPoint, radiusX, radiusY };
            return CreateEllipseGeometry( &ellipse );
        }
        EllipseGeometry CreateEllipseGeometry( const D2D1_POINT_2F& centerPoint, FLOAT radiusX, FLOAT radiusY ) const
        {
            D2D1_ELLIPSE ellipse{ centerPoint, radiusX, radiusY };
            return CreateEllipseGeometry( &ellipse );
        }
        EllipseGeometry CreateEllipseGeometry( FLOAT centerX, FLOAT centerY, FLOAT radiusX, FLOAT radiusY ) const
        {
            D2D1_ELLIPSE ellipse{ {centerX,centerY}, radiusX, radiusY };
            return CreateEllipseGeometry( &ellipse );
        }


        //
        // Create a geometry which holds other geometries.
        //

        /// <summary>
        /// Creates an ID2D1GeometryGroup, which is an object 
        /// that holds other geometries.
        /// </summary>
        /// <param name="fillMode">
        /// A value that specifies the rule that a composite shape uses 
        /// to determine whether a given point is part of the geometry.
        /// </param>
        /// <param name="geometries">
        /// An array containing the geometry objects to add to the geometry 
        /// group. The number of elements in this array is indicated by the 
        /// geometriesCount parameter.
        /// </param>
        /// <param name="geometriesCount">
        /// The number of elements in geometries.
        /// </param>
        /// <param name="geometryGroup">
        /// When this method returns, contains the address of a pointer to 
        /// the geometry group created by this method.
        /// </param>
        /// <remarks>
        /// Geometry groups are a convenient way to group several geometries 
        /// simultaneously so all figures of several distinct geometries are 
        /// concatenated into one. To create a ID2D1GeometryGroup object, call 
        /// the CreateGeometryGroup method on the ID2D1Factory object, passing 
        /// in the fillMode with possible values of D2D1_FILL_MODE_ALTERNATE 
        /// (alternate) and D2D1_FILL_MODE_WINDING, an array of geometry objects 
        /// to add to the geometry group, and the number of elements in this array.
        /// </remarks>
        void CreateGeometryGroup( D2D1_FILL_MODE fillMode, ID2D1Geometry** geometries, UINT32 geometriesCount, ID2D1GeometryGroup** geometryGroup ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateGeometryGroup( fillMode, geometries, geometriesCount, geometryGroup );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void CreateGeometryGroup( D2D1_FILL_MODE fillMode, const Geometry* geometries, UINT32 geometriesCount, ID2D1GeometryGroup** geometryGroup ) const
        {
            static_assert( sizeof( Geometry ) == sizeof( ID2D1Geometry* ), "Geometry must only have a single data member, a pointer to an ID2D1Geometry object" );
            CreateGeometryGroup( fillMode, reinterpret_cast<ID2D1Geometry**>( const_cast<Geometry*>( geometries ) ), geometriesCount, geometryGroup );
        }
        GeometryGroup CreateGeometryGroup( D2D1_FILL_MODE fillMode, ID2D1Geometry** geometries, UINT32 geometriesCount ) const
        {
            ID2D1GeometryGroup* ptr = nullptr;
            CreateGeometryGroup( fillMode, geometries, geometriesCount, &ptr );
            return GeometryGroup( ptr );
        }
        GeometryGroup CreateGeometryGroup( D2D1_FILL_MODE fillMode, const Geometry* geometries, UINT32 geometriesCount ) const
        {
            ID2D1GeometryGroup* ptr = nullptr;
            CreateGeometryGroup( fillMode, geometries, geometriesCount, &ptr );
            return GeometryGroup( ptr );
        }


        /// <summary>
        /// Transforms the specified geometry and stores the result as an 
        /// ID2D1TransformedGeometry object.
        /// </summary>
        /// <param name="sourceGeometry">
        /// The geometry to transform.
        /// </param>
        /// <param name="transform">
        /// The transformation to apply.
        /// </param>
        /// <param name="transformedGeometry">
        /// When this method returns, contains the address of the pointer to 
        /// the new transformed geometry object. The transformed geometry stores 
        /// the result of transforming sourceGeometry by transform.
        /// </param>
        /// <remarks>
        /// <p>
        /// Like other resources, a transformed geometry inherits the resource space 
        /// and threading policy of the factory that created it. This object is immutable.
        /// </p>
        /// <p>
        /// When stroking a transformed geometry with the DrawGeometry method, the stroke 
        /// width is not affected by the transform applied to the geometry. The stroke 
        /// width is only affected by the world transform.
        /// </p>
        /// </remarks>
        void CreateTransformedGeometry( ID2D1Geometry* sourceGeometry, const D2D1_MATRIX_3X2_F* transform, ID2D1TransformedGeometry** transformedGeometry ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateTransformedGeometry( sourceGeometry, transform, transformedGeometry );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void CreateTransformedGeometry( ID2D1Geometry* sourceGeometry, const D2D1_MATRIX_3X2_F& transform, ID2D1TransformedGeometry** transformedGeometry ) const
        {
            CreateTransformedGeometry( sourceGeometry, &transform, transformedGeometry );
        }
        void CreateTransformedGeometry( const Geometry& sourceGeometry, const D2D1_MATRIX_3X2_F* transform, ID2D1TransformedGeometry** transformedGeometry ) const
        {
            CreateTransformedGeometry( sourceGeometry.GetInterfacePointer<ID2D1Geometry>(), transform, transformedGeometry );
        }
        void CreateTransformedGeometry( const Geometry& sourceGeometry, const D2D1_MATRIX_3X2_F& transform, ID2D1TransformedGeometry** transformedGeometry ) const
        {
            CreateTransformedGeometry( sourceGeometry, &transform, transformedGeometry );
        }
        TransformedGeometry CreateTransformedGeometry( ID2D1Geometry* sourceGeometry, const D2D1_MATRIX_3X2_F* transform ) const
        {
            ID2D1TransformedGeometry* ptr = nullptr;
            CreateTransformedGeometry( sourceGeometry, transform, &ptr );
            return TransformedGeometry( ptr );
        }
        TransformedGeometry CreateTransformedGeometry( ID2D1Geometry* sourceGeometry, const D2D1_MATRIX_3X2_F& transform ) const
        {
            return CreateTransformedGeometry( sourceGeometry, &transform );
        }
        TransformedGeometry CreateTransformedGeometry( const Geometry& sourceGeometry, const D2D1_MATRIX_3X2_F* transform ) const
        {
            return CreateTransformedGeometry( sourceGeometry.GetInterfacePointer<ID2D1Geometry>( ), transform );
        }
        TransformedGeometry CreateTransformedGeometry( const Geometry& sourceGeometry, const D2D1_MATRIX_3X2_F& transform ) const
        {
            return CreateTransformedGeometry( sourceGeometry, &transform );
        }

        /// <summary>
        /// Creates an empty ID2D1PathGeometry.
        /// </summary>
        /// <param name="pathGeometry">
        /// When this method returns, contains the address to a pointer to the path 
        /// geometry created by this method.
        /// </param>
        void CreatePathGeometry( ID2D1PathGeometry** pathGeometry ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreatePathGeometry( pathGeometry );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        PathGeometry CreatePathGeometry( ) const
        {
            ID2D1PathGeometry* ptr = nullptr;
            CreatePathGeometry( &ptr );
            return PathGeometry( ptr );
        }


        /// <summary>
        /// Creates an ID2D1StrokeStyle that describes start cap, dash pattern, 
        /// and other features of a stroke.
        /// </summary>
        /// <param name="strokeStyleProperties">
        /// A structure that describes the stroke's line cap, dash offset, and 
        /// other details of a stroke.
        /// </param>
        /// <param name="dashes">
        /// An array whose elements are set to the length of each dash and space 
        /// in the dash pattern. The first element sets the length of a dash, the 
        /// second element sets the length of a space, the third element sets the 
        /// length of a dash, and so on. The length of each dash and space in the 
        /// dash pattern is the product of the element value in the array and the 
        /// stroke width.
        /// </param>
        /// <param name="dashesCount">
        /// The number of elements in the dashes array.
        /// </param>
        /// <param name="strokeStyle">
        /// When this method returns, contains the address of the pointer to the 
        /// stroke style created by this method.
        /// </param>
        void CreateStrokeStyle( const D2D1_STROKE_STYLE_PROPERTIES* strokeStyleProperties, const FLOAT* dashes, UINT32 dashesCount, ID2D1StrokeStyle** strokeStyle ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateStrokeStyle( strokeStyleProperties, dashes, dashesCount, strokeStyle );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void CreateStrokeStyle( const D2D1_STROKE_STYLE_PROPERTIES& strokeStyleProperties, const FLOAT* dashes, UINT32 dashesCount, ID2D1StrokeStyle** strokeStyle ) const
        {
            CreateStrokeStyle( &strokeStyleProperties, dashes, dashesCount, strokeStyle );
        }
        StrokeStyle CreateStrokeStyle( const D2D1_STROKE_STYLE_PROPERTIES* strokeStyleProperties, const FLOAT* dashes = nullptr, UINT32 dashesCount = 0 ) const
        {
            ID2D1StrokeStyle* strokeStyle = nullptr;
            CreateStrokeStyle( strokeStyleProperties, dashes, dashesCount, &strokeStyle );
            return StrokeStyle( strokeStyle );
        }
        StrokeStyle CreateStrokeStyle( const D2D1_STROKE_STYLE_PROPERTIES& strokeStyleProperties, const FLOAT* dashes = nullptr, UINT32 dashesCount = 0 ) const
        {
            return CreateStrokeStyle( strokeStyleProperties, dashes, dashesCount );
        }


        //
        // Creates a new drawing state block, this can be used in subsequent
        // SaveDrawingState and RestoreDrawingState operations on the render target.
        //

        /// <summary>
        /// Creates an ID2D1DrawingStateBlock that can be used with the SaveDrawingState 
        /// and RestoreDrawingState methods of a render target.
        /// </summary>
        /// <param name="drawingStateDescription">
        /// A structure that contains anti-aliasing, transform, and tags information.
        /// </param>
        /// <param name="textRenderingParams">
        /// Optional text parameters that indicate how text should be rendered.
        /// </param>
        /// <param name="drawingStateBlock">
        /// When this method returns, contains the address of a pointer to the 
        /// new drawing state block created by this method.
        /// </param>
        void CreateDrawingStateBlock( const D2D1_DRAWING_STATE_DESCRIPTION* drawingStateDescription, IDWriteRenderingParams* textRenderingParams, ID2D1DrawingStateBlock** drawingStateBlock ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateDrawingStateBlock( drawingStateDescription, textRenderingParams, drawingStateBlock );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void CreateDrawingStateBlock( const D2D1_DRAWING_STATE_DESCRIPTION& drawingStateDescription, IDWriteRenderingParams* textRenderingParams, ID2D1DrawingStateBlock** drawingStateBlock ) const
        {
            CreateDrawingStateBlock( &drawingStateDescription, textRenderingParams, drawingStateBlock );
        }
        inline void CreateDrawingStateBlock( const D2D1_DRAWING_STATE_DESCRIPTION* drawingStateDescription, const DirectWrite::RenderingParams& textRenderingParams, ID2D1DrawingStateBlock** drawingStateBlock ) const;
        inline void CreateDrawingStateBlock( const D2D1_DRAWING_STATE_DESCRIPTION& drawingStateDescription, const DirectWrite::RenderingParams& textRenderingParams, ID2D1DrawingStateBlock** drawingStateBlock ) const;

        DrawingStateBlock CreateDrawingStateBlock( const D2D1_DRAWING_STATE_DESCRIPTION* drawingStateDescription = nullptr, IDWriteRenderingParams* textRenderingParams = nullptr ) const
        {
            ID2D1DrawingStateBlock* ptr = nullptr;
            CreateDrawingStateBlock( drawingStateDescription, textRenderingParams, &ptr );
            return DrawingStateBlock( ptr );
        }
        DrawingStateBlock CreateDrawingStateBlock( const D2D1_DRAWING_STATE_DESCRIPTION& drawingStateDescription, IDWriteRenderingParams* textRenderingParams = nullptr ) const
        {
            return CreateDrawingStateBlock( &drawingStateDescription, textRenderingParams );
        }
        inline DrawingStateBlock CreateDrawingStateBlock( const D2D1_DRAWING_STATE_DESCRIPTION* drawingStateDescription, const DirectWrite::RenderingParams& textRenderingParams ) const;
        inline DrawingStateBlock CreateDrawingStateBlock( const D2D1_DRAWING_STATE_DESCRIPTION& drawingStateDescription, const DirectWrite::RenderingParams& textRenderingParams ) const;

        /// <summary>
        /// Creates a render target that renders to a Microsoft Windows 
        /// Imaging Component (WIC) bitmap.
        /// </summary>
        /// <param name="target">
        /// The bitmap that receives the rendering output of the render target.
        /// </param>
        /// <param name="renderTargetProperties">
        /// The rendering mode, pixel format, remoting options, DPI information, 
        /// and the minimum DirectX support required for hardware rendering.
        /// </param>
        /// <param name="renderTarget">
        /// When this method returns, contains the address of the pointer to the 
        /// ID2D1RenderTarget object created by this method.
        /// </param>
        /// <remarks>
        /// <p>
        /// You must use D2D1_FEATURE_LEVEL_DEFAULT for the minLevel member of 
        /// the renderTargetProperties parameter with this method.
        /// </p>
        /// <p>
        /// Your application should create render targets once and hold onto them 
        /// for the life of the application or until the D2DERR_RECREATE_TARGET 
        /// error is received. When you receive this error, you need to recreate 
        /// the render target (and any resources it created).
        /// </p>
        /// <p>
        /// This library will throw a Harlinn::Common::Core::Exception 
        /// when it encounters a D2DERR_RECREATE_TARGET error.
        /// Call GetHRESULT( ) on the exception object to determine if a
        /// D2DERR_RECREATE_TARGET error occurred.
        /// </p>
        /// </remarks>
        void CreateWicBitmapRenderTarget( IWICBitmap* target, const D2D1_RENDER_TARGET_PROPERTIES* renderTargetProperties, ID2D1RenderTarget** renderTarget ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateWicBitmapRenderTarget( target, renderTargetProperties, renderTarget );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void CreateWicBitmapRenderTarget( IWICBitmap* target, const D2D1_RENDER_TARGET_PROPERTIES& renderTargetProperties, ID2D1RenderTarget** renderTarget ) const
        {
            CreateWicBitmapRenderTarget( target, &renderTargetProperties, renderTarget );
        }
        RenderTarget CreateWicBitmapRenderTarget( IWICBitmap* target, const D2D1_RENDER_TARGET_PROPERTIES* renderTargetProperties ) const
        {
            ID2D1RenderTarget* ptr = nullptr;
            CreateWicBitmapRenderTarget( target, renderTargetProperties, &ptr );
            return RenderTarget( ptr );
        }
        RenderTarget CreateWicBitmapRenderTarget( IWICBitmap* target, const D2D1_RENDER_TARGET_PROPERTIES& renderTargetProperties ) const
        {
            return CreateWicBitmapRenderTarget( target, &renderTargetProperties );
        }

        /// <summary>
        /// Creates an ID2D1HwndRenderTarget, a render target that 
        /// renders to a window.
        /// </summary>
        /// <param name="renderTargetProperties">
        /// The rendering mode, pixel format, remoting options, 
        /// DPI information, and the minimum DirectX support required 
        /// for hardware rendering.
        /// </param>
        /// <param name="hwndRenderTargetProperties">
        /// The window handle, initial size (in pixels), and present options.
        /// </param>
        /// <param name="hwndRenderTarget">
        /// When this method returns, contains the address of the pointer to 
        /// the ID2D1HwndRenderTarget object created by this method.
        /// </param>
        /// <remarks>
        /// <p>
        /// When you create a render target and hardware acceleration is available, 
        /// you allocate resources on the computer's GPU. By creating a render 
        /// target once and retaining it as long as possible, you gain performance 
        /// benefits. Your application should create render targets once and hold 
        /// onto them for the life of the application or until the D2DERR_RECREATE_TARGET 
        /// error is received. When you receive this error, you need to recreate 
        /// the render target (and any resources it created).
        /// </p>
        /// <p>
        /// This library will throw a Harlinn::Common::Core::Exception 
        /// when it encounters a D2DERR_RECREATE_TARGET error.
        /// Call GetHRESULT( ) on the exception object to determine if a
        /// D2DERR_RECREATE_TARGET error occurred.
        /// </p>
        /// </remarks>
        void CreateHwndRenderTarget( const D2D1_RENDER_TARGET_PROPERTIES* renderTargetProperties, const D2D1_HWND_RENDER_TARGET_PROPERTIES* hwndRenderTargetProperties, ID2D1HwndRenderTarget** hwndRenderTarget ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateHwndRenderTarget( renderTargetProperties, hwndRenderTargetProperties, hwndRenderTarget );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void CreateHwndRenderTarget( const D2D1_RENDER_TARGET_PROPERTIES& renderTargetProperties, const D2D1_HWND_RENDER_TARGET_PROPERTIES& hwndRenderTargetProperties, ID2D1HwndRenderTarget** hwndRenderTarget ) const
        {
            CreateHwndRenderTarget( &renderTargetProperties, &hwndRenderTargetProperties, hwndRenderTarget );
        }

        ControlRenderTarget CreateHwndRenderTarget( const D2D1_RENDER_TARGET_PROPERTIES* renderTargetProperties, const D2D1_HWND_RENDER_TARGET_PROPERTIES* hwndRenderTargetProperties ) const
        {
            ID2D1HwndRenderTarget* ptr = nullptr;
            CreateHwndRenderTarget( renderTargetProperties, hwndRenderTargetProperties, &ptr );
            return ControlRenderTarget( ptr );
        }
        ControlRenderTarget CreateHwndRenderTarget( const D2D1_RENDER_TARGET_PROPERTIES& renderTargetProperties, const D2D1_HWND_RENDER_TARGET_PROPERTIES& hwndRenderTargetProperties ) const
        {
            return CreateHwndRenderTarget( &renderTargetProperties, &hwndRenderTargetProperties );
        }
        HW_EXPORT ControlRenderTarget CreateHwndRenderTarget( Control& control ) const;
        HW_EXPORT ControlRenderTarget CreateHwndRenderTarget( HWND hwnd ) const;

        HW_EXPORT ControlRenderTarget CreateControlRenderTarget( Control& control ) const;
        HW_EXPORT ControlRenderTarget CreateControlRenderTarget( HWND hwnd ) const;


        //
        // Creates a render target that draws to a DXGI Surface. The device that owns the
        // surface is used for rendering.
        //

        /// <summary>
        /// Creates a render target that draws to a DirectX Graphics 
        /// Infrastructure (DXGI) surface.
        /// </summary>
        /// <param name="dxgiSurface">
        /// The IDXGISurface to which the render target will draw.
        /// </param>
        /// <param name="renderTargetProperties">
        /// The rendering mode, pixel format, remoting options, DPI information, 
        /// and the minimum DirectX support required for hardware rendering.
        /// </param>
        /// <param name="renderTarget">
        /// When this method returns, contains the address of the pointer to 
        /// the ID2D1RenderTarget object created by this method.
        /// </param>
        /// <remarks>
        /// <p>
        /// To write to a Direct3D surface, you obtain an IDXGISurface and pass 
        /// it to the CreateDxgiSurfaceRenderTarget method to create a DXGI 
        /// surface render target; you can then use the DXGI surface render 
        /// target to draw 2-D content to the DXGI surface.
        /// </p>
        /// <p>
        /// A DXGI surface render target is a type of ID2D1RenderTarget. Like 
        /// other Direct2D render targets, you can use it to create resources 
        /// and issue drawing commands.
        /// </p>
        /// <p>
        /// The DXGI surface render target and the DXGI surface must use the same 
        /// DXGI format. If you specify the DXGI_FORMAT_UNKOWN format when you 
        /// create the render target, it will automatically use the surface's format.
        /// </p>
        /// <p>
        /// The DXGI surface render target does not perform DXGI surface 
        /// synchronization.
        /// </p>
        /// <p>
        /// For more information about creating and using DXGI surface render 
        /// targets, see the <a href="https://docs.microsoft.com/en-us/windows/win32/Direct2D/direct2d-and-direct3d-interoperation-overview">Direct2D and Direct3D Interoperability Overview.</a>
        /// </p>
        /// <p>
        /// To work with Direct2D, the Direct3D device that provides the IDXGISurface 
        /// must be created with the D3D10_CREATE_DEVICE_BGRA_SUPPORT flag.
        /// </p>
        /// <p>
        /// When you create a render target and hardware acceleration is available, 
        /// you allocate resources on the computer's GPU. By creating a render target 
        /// once and retaining it as long as possible, you gain performance benefits. 
        /// Your application should create render targets once and hold onto them for 
        /// the life of the application or until the render target's EndDraw method 
        /// returns the D2DERR_RECREATE_TARGET error. When you receive this error, 
        /// you need to recreate the render target (and any resources it created).
        /// </p>
        /// <p>
        /// This library will throw a Harlinn::Common::Core::Exception 
        /// when it encounters a D2DERR_RECREATE_TARGET error.
        /// Call GetHRESULT( ) on the exception object to determine if a
        /// D2DERR_RECREATE_TARGET error occurred.
        /// </p>
        /// </remarks>
        void CreateDxgiSurfaceRenderTarget( IDXGISurface* dxgiSurface, const D2D1_RENDER_TARGET_PROPERTIES* renderTargetProperties, ID2D1RenderTarget** renderTarget ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateDxgiSurfaceRenderTarget( dxgiSurface, renderTargetProperties, renderTarget );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void CreateDxgiSurfaceRenderTarget( IDXGISurface* dxgiSurface, const D2D1_RENDER_TARGET_PROPERTIES& renderTargetProperties, ID2D1RenderTarget** renderTarget ) const
        {
            CreateDxgiSurfaceRenderTarget( dxgiSurface, &renderTargetProperties, renderTarget );
        }

        template<typename T>
            requires std::is_base_of_v< DXGI::Surface, T>
        void CreateDxgiSurfaceRenderTarget( const T& dxgiSurface, const D2D1_RENDER_TARGET_PROPERTIES* renderTargetProperties, ID2D1RenderTarget** renderTarget ) const
        {
            using ItfT = typename T::InterfaceType;
            CreateDxgiSurfaceRenderTarget( dxgiSurface.GetInterfacePointer<ItfT>( ), renderTargetProperties, renderTarget );
        }
        template<typename T>
            requires std::is_base_of_v< DXGI::Surface, T>
        void CreateDxgiSurfaceRenderTarget( const T& dxgiSurface, const D2D1_RENDER_TARGET_PROPERTIES& renderTargetProperties, ID2D1RenderTarget** renderTarget ) const
        {
            using ItfT = typename T::InterfaceType;
            CreateDxgiSurfaceRenderTarget( dxgiSurface.GetInterfacePointer<ItfT>( ), &renderTargetProperties, renderTarget );
        }

        RenderTarget CreateDxgiSurfaceRenderTarget( IDXGISurface* dxgiSurface, const D2D1_RENDER_TARGET_PROPERTIES* renderTargetProperties ) const
        {
            ID2D1RenderTarget* ptr = nullptr;
            CreateDxgiSurfaceRenderTarget( dxgiSurface, renderTargetProperties, &ptr );
            return RenderTarget( ptr );
        }
        RenderTarget CreateDxgiSurfaceRenderTarget( IDXGISurface* dxgiSurface, const D2D1_RENDER_TARGET_PROPERTIES& renderTargetProperties ) const
        {
            return CreateDxgiSurfaceRenderTarget( dxgiSurface, &renderTargetProperties );
        }
        template<typename T>
            requires std::is_base_of_v< DXGI::Surface, T>
        RenderTarget CreateDxgiSurfaceRenderTarget( const T& dxgiSurface, const D2D1_RENDER_TARGET_PROPERTIES* renderTargetProperties ) const
        {
            using ItfT = typename T::InterfaceType;
            return CreateDxgiSurfaceRenderTarget( dxgiSurface.GetInterfacePointer<ItfT>( ), renderTargetProperties );
        }
        template<typename T>
            requires std::is_base_of_v< DXGI::Surface, T>
        RenderTarget CreateDxgiSurfaceRenderTarget( const T& dxgiSurface, const D2D1_RENDER_TARGET_PROPERTIES& renderTargetProperties ) const
        {
            using ItfT = typename T::InterfaceType;
            return CreateDxgiSurfaceRenderTarget( dxgiSurface.GetInterfacePointer<ItfT>( ), &renderTargetProperties );
        }

        /// <summary>
        /// Creates a render target that draws to a Windows Graphics 
        /// Device Interface (GDI) device context.
        /// </summary>
        /// <param name="renderTargetProperties">
        /// The rendering mode, pixel format, remoting options, DPI information, 
        /// and the minimum DirectX support required for hardware rendering. To 
        /// enable the device context (DC) render target to work with GDI, set 
        /// the DXGI format to DXGI_FORMAT_B8G8R8A8_UNORM and the alpha mode to 
        /// D2D1_ALPHA_MODE_PREMULTIPLIED or D2D1_ALPHA_MODE_IGNORE.
        /// </param>
        /// <param name="dcRenderTarget">
        /// When this method returns, dcRenderTarget contains the address of the 
        /// pointer to the ID2D1DCRenderTarget created by the method.
        /// </param>
        void CreateDCRenderTarget( const D2D1_RENDER_TARGET_PROPERTIES* renderTargetProperties, ID2D1DCRenderTarget** dcRenderTarget ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateDCRenderTarget( renderTargetProperties, dcRenderTarget );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void CreateDCRenderTarget( const D2D1_RENDER_TARGET_PROPERTIES& renderTargetProperties, ID2D1DCRenderTarget** dcRenderTarget ) const
        {
            CreateDCRenderTarget( &renderTargetProperties, dcRenderTarget );
        }

        DeviceContextRenderTarget CreateDCRenderTarget( const D2D1_RENDER_TARGET_PROPERTIES* renderTargetProperties ) const
        {
            ID2D1DCRenderTarget* ptr = nullptr;
            CreateDCRenderTarget( renderTargetProperties, &ptr );
            return DeviceContextRenderTarget( ptr );
        }
        DeviceContextRenderTarget CreateDCRenderTarget( const D2D1_RENDER_TARGET_PROPERTIES& renderTargetProperties ) const
        {
            return CreateDCRenderTarget( &renderTargetProperties );
        }
    };


    

    /// <summary>
    /// A developer implemented interface that allows a meta-file to be replayed.
    /// </summary>
    class GdiMetafileSink : public Unknown
    {
    public:
        using Base = Unknown;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( GdiMetafileSink, Base, ID2D1GdiMetafileSink, IUnknown )
    public:
        void ProcessRecord( DWORD recordType, const void* recordData, DWORD recordDataSize ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->ProcessRecord( recordType, recordData, recordDataSize );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    /// <summary>
    /// Basic implementation of ID2D1GdiMetafileSink
    /// </summary>
    /// <typeparam name="DerivedT">
    /// Instantiate using a derived type that implements:
    ///     <code>void HandleProcessRecord( DWORD recordType, void* recordData, recordDataSize );</code>
    /// </typeparam>
    /// <typeparam name="InterfaceT">
    /// The most derived COM interface implemented by DerivedT.
    /// </typeparam>
    /// <typeparam name="InterfaceTypes">
    /// Additional COM interfaces implemented by DerivedT.
    /// </typeparam>
    template<typename DerivedT, typename InterfaceT, typename ...InterfaceTypes>
    class ID2D1GdiMetafileSinkImplementationBase : public IUnknownImplementation<ID2D1GdiMetafileSinkImplementationBase<DerivedT, InterfaceT, InterfaceTypes...>, InterfaceT, ID2D1GdiMetafileSink, InterfaceTypes...>
    {
    public:
        using Base = IUnknownImplementation<ID2D1GdiMetafileSinkImplementationBase<DerivedT, InterfaceT, InterfaceTypes...>, InterfaceT, ID2D1GdiMetafileSink, InterfaceTypes...>;
        using DerivedType = DerivedT;
        using InterfaceType = ID2D1GdiMetafileSink;
    protected:
        void HandleProcessRecord( DWORD recordType, void* recordData, DWORD recordDataSize )
        {
            
        }
    private:
        virtual HRESULT STDAPICALLTYPE ProcessRecord( DWORD recordType, _In_opt_ CONST void* recordData, DWORD recordDataSize ) override
        {
            try
            {
                auto* self = static_cast<DerivedType*>( this );
                self->HandleProcessRecord( recordType, recordData, recordDataSize );
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT( );
        }
    };
    template <typename DerivedT>
    using ID2D1GdiMetafileSinkImplementation = ID2D1GdiMetafileSinkImplementationBase<DerivedT, ID2D1GdiMetafileSink>;


    
    /// <summary>
    /// A Direct2D resource that wraps a WMF, EMF, or EMF+ metafile.
    /// </summary>
    class GdiMetafile : public Resource
    {
    public:
        using Base = Resource;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( GdiMetafile, Base, ID2D1GdiMetafile, ID2D1Resource )
    public:
        /// <summary>
        /// Play the meta-file into a caller-supplied sink interface.
        /// </summary>
        void Stream( ID2D1GdiMetafileSink* sink ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->Stream( sink );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Gets the bounds of the metafile.
        /// </summary>
        void GetBounds( D2D1_RECT_F* bounds ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetBounds( bounds );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void GetBounds( D2D1_RECT_F& bounds ) const
        {
            GetBounds( &bounds );
        }
    };

    
    /// <summary>
    /// <p>
    /// The command sink is implemented by you for an application when 
    /// you want to receive a playback of the commands recorded in a command 
    /// list. A typical usage will be for transforming the command list into 
    /// another format such as XPS when some degree of conversion between the 
    /// Direct2D primitives and the target format is required.
    /// </p>
    /// <p>
    /// The command sink interface doesn't have any resource creation methods 
    /// on it. The resources are still logically bound to the Direct2D device 
    /// on which the command list was created and will be passed in to the 
    /// command sink implementation.
    /// </p>
    /// </summary>
    class CommandSink : public Unknown
    {
    public:
        using Base = Unknown;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( CommandSink, Base, ID2D1CommandSink, IUnknown )
    public:
        void BeginDraw( ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->BeginDraw( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void EndDraw( ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->EndDraw( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetAntialiasMode( D2D1_ANTIALIAS_MODE antialiasMode ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->SetAntialiasMode( antialiasMode );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetTags( D2D1_TAG tag1, D2D1_TAG tag2 ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->SetTags( tag1, tag2 );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetTextAntialiasMode( D2D1_TEXT_ANTIALIAS_MODE textAntialiasMode ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->SetTextAntialiasMode( textAntialiasMode );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetTextRenderingParams( IDWriteRenderingParams* textRenderingParams ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->SetTextRenderingParams( textRenderingParams );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetTransform( const D2D1_MATRIX_3X2_F* transform ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->SetTransform( transform );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetPrimitiveBlend( D2D1_PRIMITIVE_BLEND primitiveBlend ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->SetPrimitiveBlend( primitiveBlend );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetUnitMode( D2D1_UNIT_MODE unitMode ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->SetUnitMode( unitMode );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Clear( const D2D1_COLOR_F* color ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->Clear( color );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void DrawGlyphRun( D2D1_POINT_2F baselineOrigin, const DWRITE_GLYPH_RUN* glyphRun, const DWRITE_GLYPH_RUN_DESCRIPTION* glyphRunDescription, ID2D1Brush* foregroundBrush, DWRITE_MEASURING_MODE measuringMode ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->DrawGlyphRun( baselineOrigin, glyphRun, glyphRunDescription, foregroundBrush, measuringMode );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void DrawLine( D2D1_POINT_2F point0, D2D1_POINT_2F point1, ID2D1Brush* brush, FLOAT strokeWidth, ID2D1StrokeStyle* strokeStyle ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->DrawLine( point0, point1, brush, strokeWidth, strokeStyle );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void DrawGeometry( ID2D1Geometry* geometry, ID2D1Brush* brush, FLOAT strokeWidth, ID2D1StrokeStyle* strokeStyle ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->DrawGeometry( geometry, brush, strokeWidth, strokeStyle );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void DrawRectangle( const D2D1_RECT_F* rect, ID2D1Brush* brush, FLOAT strokeWidth, ID2D1StrokeStyle* strokeStyle ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->DrawRectangle( rect, brush, strokeWidth, strokeStyle );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void DrawBitmap( ID2D1Bitmap* bitmap, const D2D1_RECT_F* destinationRectangle, FLOAT opacity, D2D1_INTERPOLATION_MODE interpolationMode, const D2D1_RECT_F* sourceRectangle, const D2D1_MATRIX_4X4_F* perspectiveTransform ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->DrawBitmap( bitmap, destinationRectangle, opacity, interpolationMode, sourceRectangle, perspectiveTransform );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void DrawImage( ID2D1Image* image, const D2D1_POINT_2F* targetOffset, const D2D1_RECT_F* imageRectangle, D2D1_INTERPOLATION_MODE interpolationMode, D2D1_COMPOSITE_MODE compositeMode ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->DrawImage( image, targetOffset, imageRectangle, interpolationMode, compositeMode );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void DrawGdiMetafile( ID2D1GdiMetafile* gdiMetafile, const D2D1_POINT_2F* targetOffset ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->DrawGdiMetafile( gdiMetafile, targetOffset );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void FillMesh( ID2D1Mesh* mesh, ID2D1Brush* brush ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->FillMesh( mesh, brush );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void FillOpacityMask( ID2D1Bitmap* opacityMask, ID2D1Brush* brush, const D2D1_RECT_F* destinationRectangle, const D2D1_RECT_F* sourceRectangle ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->FillOpacityMask( opacityMask, brush, destinationRectangle, sourceRectangle );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void FillGeometry( ID2D1Geometry* geometry, ID2D1Brush* brush, ID2D1Brush* opacityBrush ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->FillGeometry( geometry, brush, opacityBrush );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void FillRectangle( const D2D1_RECT_F* rect, ID2D1Brush* brush ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->FillRectangle( rect, brush );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void PushAxisAlignedClip( const D2D1_RECT_F* clipRect, D2D1_ANTIALIAS_MODE antialiasMode ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->PushAxisAlignedClip( clipRect, antialiasMode );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void PushLayer( const D2D1_LAYER_PARAMETERS1* layerParameters1, ID2D1Layer* layer ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->PushLayer( layerParameters1, layer );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void PopAxisAlignedClip( ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->PopAxisAlignedClip( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void PopLayer( ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->PopLayer( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    template<typename DerivedT>
    class ID2D1CommandSinkImplementationBase : public IUnknownImplementation<ID2D1CommandSinkImplementationBase<DerivedT>, ID2D1CommandSink>
    {
    public:
        using Base = IUnknownImplementation<ID2D1CommandSinkImplementationBase<DerivedT>, ID2D1CommandSink>;
        using DerivedType = DerivedT;
        using InterfaceType = ID2D1CommandSink;
    protected:
        void HandleBeginDraw( )
        {
        }

        void HandleEndDraw( )
        {
        }

        void HandleSetAntialiasMode( D2D1_ANTIALIAS_MODE antialiasMode )
        {
        }

        void HandleSetTags( D2D1_TAG tag1, D2D1_TAG tag2 )
        {
        }

        void HandleSetTextAntialiasMode( D2D1_TEXT_ANTIALIAS_MODE textAntialiasMode )
        {
        }

        void HandleSetTextRenderingParams( _In_opt_ IDWriteRenderingParams* textRenderingParams )
        {
        }

        void HandleSetTransform( _In_ CONST D2D1_MATRIX_3X2_F* transform )
        {
        }

        void HandleSetPrimitiveBlend( D2D1_PRIMITIVE_BLEND primitiveBlend )
        {
        }

        void HandleSetUnitMode( D2D1_UNIT_MODE unitMode )
        {
        }

        void HandleClear( _In_opt_ CONST D2D1_COLOR_F* color )
        {
        }

        void HandleDrawGlyphRun( D2D1_POINT_2F baselineOrigin, _In_ CONST DWRITE_GLYPH_RUN* glyphRun, _In_opt_ CONST DWRITE_GLYPH_RUN_DESCRIPTION* glyphRunDescription, _In_ ID2D1Brush* foregroundBrush, DWRITE_MEASURING_MODE measuringMode )
        {
        }

        void HandleDrawLine( D2D1_POINT_2F point0, D2D1_POINT_2F point1, _In_ ID2D1Brush* brush, FLOAT strokeWidth, _In_opt_ ID2D1StrokeStyle* strokeStyle )
        {
        }

        void HandleDrawGeometry( _In_ ID2D1Geometry* geometry, _In_ ID2D1Brush* brush, FLOAT strokeWidth, _In_opt_ ID2D1StrokeStyle* strokeStyle )
        {
        }

        void HandleDrawRectangle( _In_ CONST D2D1_RECT_F* rect, _In_ ID2D1Brush* brush, FLOAT strokeWidth, _In_opt_ ID2D1StrokeStyle* strokeStyle )
        {
        }

        void HandleDrawBitmap( _In_ ID2D1Bitmap* bitmap, _In_opt_ CONST D2D1_RECT_F* destinationRectangle, FLOAT opacity, D2D1_INTERPOLATION_MODE interpolationMode, _In_opt_ CONST D2D1_RECT_F* sourceRectangle, _In_opt_ CONST D2D1_MATRIX_4X4_F* perspectiveTransform )
        {
        }

        void HandleDrawImage( _In_ ID2D1Image* image, _In_opt_ CONST D2D1_POINT_2F* targetOffset, _In_opt_ CONST D2D1_RECT_F* imageRectangle, D2D1_INTERPOLATION_MODE interpolationMode, D2D1_COMPOSITE_MODE compositeMode )
        {
        }

        void HandleDrawGdiMetafile( _In_ ID2D1GdiMetafile* gdiMetafile, _In_opt_ CONST D2D1_POINT_2F* targetOffset )
        {
        }

        void HandleFillMesh( _In_ ID2D1Mesh* mesh, _In_ ID2D1Brush* brush )
        {
        }

        void HandleFillOpacityMask( _In_ ID2D1Bitmap* opacityMask, _In_ ID2D1Brush* brush, _In_opt_ CONST D2D1_RECT_F* destinationRectangle, _In_opt_ CONST D2D1_RECT_F* sourceRectangle )
        {
        }

        void HandleFillGeometry( _In_ ID2D1Geometry* geometry, _In_ ID2D1Brush* brush, _In_opt_ ID2D1Brush* opacityBrush )
        {
        }

        void HandleFillRectangle( _In_ CONST D2D1_RECT_F* rect, _In_ ID2D1Brush* brush )
        {
        }

        void HandlePushAxisAlignedClip( _In_ CONST D2D1_RECT_F* clipRect, D2D1_ANTIALIAS_MODE antialiasMode )
        {
        }

        void HandlePushLayer( _In_ CONST D2D1_LAYER_PARAMETERS1* layerParameters1, _In_opt_ ID2D1Layer* layer )
        {
        }

        void HandlePopAxisAlignedClip( )
        {
        }

        void HandlePopLayer( )
        {
        }
    private:
        virtual HRESULT STDAPICALLTYPE BeginDraw( ) override
        {
            try
            {
                auto* self = static_cast<DerivedType*>( this );
                self->HandleBeginDraw( );
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT( );
        }

        virtual HRESULT STDAPICALLTYPE EndDraw( ) override
        {
            try
            {
                auto* self = static_cast<DerivedType*>( this );
                self->HandleEndDraw( );
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT( );
        }

        virtual HRESULT STDAPICALLTYPE SetAntialiasMode( D2D1_ANTIALIAS_MODE antialiasMode ) override
        {
            try
            {
                auto* self = static_cast<DerivedType*>( this );
                self->HandleSetAntialiasMode( antialiasMode );
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT( );
        }

        virtual HRESULT STDAPICALLTYPE SetTags( D2D1_TAG tag1, D2D1_TAG tag2 ) override
        {
            try
            {
                auto* self = static_cast<DerivedType*>( this );
                self->HandleSetTags( tag1, tag2 );
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT( );
        }

        virtual HRESULT STDAPICALLTYPE SetTextAntialiasMode( D2D1_TEXT_ANTIALIAS_MODE textAntialiasMode ) override
        {
            try
            {
                auto* self = static_cast<DerivedType*>( this );
                self->HandleSetTextAntialiasMode( textAntialiasMode );
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT( );
        }

        virtual HRESULT STDAPICALLTYPE SetTextRenderingParams( _In_opt_ IDWriteRenderingParams* textRenderingParams ) override
        {
            try
            {
                auto* self = static_cast<DerivedType*>( this );
                self->HandleSetTextRenderingParams( textRenderingParams );
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT( );
        }

        virtual HRESULT STDAPICALLTYPE SetTransform( _In_ CONST D2D1_MATRIX_3X2_F* transform ) override
        {
            try
            {
                auto* self = static_cast<DerivedType*>( this );
                self->HandleSetTransform( transform );
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT( );
        }

        virtual HRESULT STDAPICALLTYPE SetPrimitiveBlend( D2D1_PRIMITIVE_BLEND primitiveBlend ) override
        {
            try
            {
                auto* self = static_cast<DerivedType*>( this );
                self->HandleSetPrimitiveBlend( primitiveBlend );
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT( );
        }

        virtual HRESULT STDAPICALLTYPE SetUnitMode( D2D1_UNIT_MODE unitMode ) override
        {
            try
            {
                auto* self = static_cast<DerivedType*>( this );
                self->HandleSetUnitMode( unitMode );
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT( );
        }

        virtual HRESULT STDAPICALLTYPE Clear( _In_opt_ CONST D2D1_COLOR_F* color ) override
        {
            try
            {
                auto* self = static_cast<DerivedType*>( this );
                self->HandleClear( color );
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT( );
        }

        virtual HRESULT STDAPICALLTYPE DrawGlyphRun( D2D1_POINT_2F baselineOrigin, _In_ CONST DWRITE_GLYPH_RUN* glyphRun, _In_opt_ CONST DWRITE_GLYPH_RUN_DESCRIPTION* glyphRunDescription, _In_ ID2D1Brush* foregroundBrush, DWRITE_MEASURING_MODE measuringMode ) override
        {
            try
            {
                auto* self = static_cast<DerivedType*>( this );
                self->HandleDrawGlyphRun( baselineOrigin, glyphRun, glyphRunDescription, foregroundBrush, measuringMode );
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT( );
        }

        virtual HRESULT STDAPICALLTYPE DrawLine( D2D1_POINT_2F point0, D2D1_POINT_2F point1, _In_ ID2D1Brush* brush, FLOAT strokeWidth, _In_opt_ ID2D1StrokeStyle* strokeStyle ) override
        {
            try
            {
                auto* self = static_cast<DerivedType*>( this );
                self->HandleDrawLine( point0, point1, brush, strokeWidth, strokeStyle );
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT( );
        }

        virtual HRESULT STDAPICALLTYPE DrawGeometry( _In_ ID2D1Geometry* geometry, _In_ ID2D1Brush* brush, FLOAT strokeWidth, _In_opt_ ID2D1StrokeStyle* strokeStyle ) override
        {
            try
            {
                auto* self = static_cast<DerivedType*>( this );
                self->HandleDrawGeometry( geometry, brush, strokeWidth, strokeStyle );
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT( );
        }

        virtual HRESULT STDAPICALLTYPE DrawRectangle( _In_ CONST D2D1_RECT_F* rect, _In_ ID2D1Brush* brush, FLOAT strokeWidth, _In_opt_ ID2D1StrokeStyle* strokeStyle ) override
        {
            try
            {
                auto* self = static_cast<DerivedType*>( this );
                self->HandleDrawRectangle( rect, brush, strokeWidth, strokeStyle );
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT( );
        }

        virtual HRESULT STDAPICALLTYPE DrawBitmap( _In_ ID2D1Bitmap* bitmap, _In_opt_ CONST D2D1_RECT_F* destinationRectangle, FLOAT opacity, D2D1_INTERPOLATION_MODE interpolationMode, _In_opt_ CONST D2D1_RECT_F* sourceRectangle, _In_opt_ CONST D2D1_MATRIX_4X4_F* perspectiveTransform ) override
        {
            try
            {
                auto* self = static_cast<DerivedType*>( this );
                self->HandleDrawBitmap( bitmap, destinationRectangle, opacity, interpolationMode, sourceRectangle, perspectiveTransform );
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT( );
        }

        virtual HRESULT STDAPICALLTYPE DrawImage( _In_ ID2D1Image* image, _In_opt_ CONST D2D1_POINT_2F* targetOffset, _In_opt_ CONST D2D1_RECT_F* imageRectangle, D2D1_INTERPOLATION_MODE interpolationMode, D2D1_COMPOSITE_MODE compositeMode ) override
        {
            try
            {
                auto* self = static_cast<DerivedType*>( this );
                self->HandleDrawImage( image, targetOffset, imageRectangle, interpolationMode, compositeMode );
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT( );
        }

        virtual HRESULT STDAPICALLTYPE DrawGdiMetafile( _In_ ID2D1GdiMetafile* gdiMetafile, _In_opt_ CONST D2D1_POINT_2F* targetOffset ) override
        {
            try
            {
                auto* self = static_cast<DerivedType*>( this );
                self->HandleDrawGdiMetafile( gdiMetafile, targetOffset );
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT( );
        }

        virtual HRESULT STDAPICALLTYPE FillMesh( _In_ ID2D1Mesh* mesh, _In_ ID2D1Brush* brush ) override
        {
            try
            {
                auto* self = static_cast<DerivedType*>( this );
                self->HandleFillMesh( mesh, brush );
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT( );
        }

        virtual HRESULT STDAPICALLTYPE FillOpacityMask( _In_ ID2D1Bitmap* opacityMask, _In_ ID2D1Brush* brush, _In_opt_ CONST D2D1_RECT_F* destinationRectangle, _In_opt_ CONST D2D1_RECT_F* sourceRectangle ) override
        {
            try
            {
                auto* self = static_cast<DerivedType*>( this );
                self->HandleFillOpacityMask( opacityMask, brush, destinationRectangle, sourceRectangle );
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT( );
        }

        virtual HRESULT STDAPICALLTYPE FillGeometry( _In_ ID2D1Geometry* geometry, _In_ ID2D1Brush* brush, _In_opt_ ID2D1Brush* opacityBrush ) override
        {
            try
            {
                auto* self = static_cast<DerivedType*>( this );
                self->HandleFillGeometry( geometry, brush, opacityBrush );
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT( );
        }

        virtual HRESULT STDAPICALLTYPE FillRectangle( _In_ CONST D2D1_RECT_F* rect, _In_ ID2D1Brush* brush ) override
        {
            try
            {
                auto* self = static_cast<DerivedType*>( this );
                self->HandleFillRectangle( rect, brush );
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT( );
        }

        virtual HRESULT STDAPICALLTYPE PushAxisAlignedClip( _In_ CONST D2D1_RECT_F* clipRect, D2D1_ANTIALIAS_MODE antialiasMode ) override
        {
            try
            {
                auto* self = static_cast<DerivedType*>( this );
                self->HandlePushAxisAlignedClip( clipRect, antialiasMode );
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT( );
        }

        virtual HRESULT STDAPICALLTYPE PushLayer( _In_ CONST D2D1_LAYER_PARAMETERS1* layerParameters1, _In_opt_ ID2D1Layer* layer ) override
        {
            try
            {
                auto* self = static_cast<DerivedType*>( this );
                self->HandlePushLayer( layerParameters1, layer );
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT( );
        }

        virtual HRESULT STDAPICALLTYPE PopAxisAlignedClip( ) override
        {
            try
            {
                auto* self = static_cast<DerivedType*>( this );
                self->HandlePopAxisAlignedClip( );
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT( );
        }

        virtual HRESULT STDAPICALLTYPE PopLayer( ) override
        {
            try
            {
                auto* self = static_cast<DerivedType*>( this );
                self->HandlePopLayer( );
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT( );
        }
    };



    /// <summary>
    /// Represents a sequence of commands that can be recorded and played back.
    /// </summary>
    class CommandList : public Image
    {
    public:
        using Base = Image;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( CommandList, Base, ID2D1CommandList, ID2D1Image )
    public:
        /// <summary>
        /// Streams the contents of the command list to the specified command sink.
        /// </summary>
        /// <param name="sink">
        /// The sink into which the command list will be streamed.
        /// </param>
        /// <remarks>
        /// <p>
        /// The command sink can be implemented by any caller of the API.
        /// </p>
        /// <p>
        /// If the caller makes any design-time failure calls while a command 
        /// list is selected as a target, the command list is placed in an error 
        /// state. The stream call fails without making any calls to the passed 
        /// in sink.
        /// </p>
        /// </remarks>
        void Stream( ID2D1CommandSink* sink ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->Stream( sink );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Instructs the command list to stop accepting commands so that you 
        /// can use it as an input to an effect or in a call to ID2D1DeviceContext::DrawImage. 
        /// You should call the method after it has been attached to an ID2D1DeviceContext 
        /// and written to but before the command list is used.
        /// </summary>
        void Close( ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->Close( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    
    /// <summary>
    /// Converts Direct2D primitives stored in an ID2D1CommandList into a 
    /// fixed page representation. The print sub-system then consumes the 
    /// primitives.
    /// </summary>
    class PrintControl : public Unknown
    {
    public:
        using Base = Unknown;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( PrintControl, Base, ID2D1PrintControl, IUnknown )
    public:
        /// <summary>
        /// Converts Direct2D primitives in the passed-in command list 
        /// into a fixed page representation for use by the print subsystem.
        /// </summary>
        /// <param name="commandList">
        /// The command list that contains the rendering operations.
        /// </param>
        /// <param name="pageSize">
        /// The size of the page to add.
        /// </param>
        /// <param name="pagePrintTicketStream">
        /// The print ticket stream.
        /// </param>
        /// <param name="tag1">
        /// Contains the first label for subsequent drawing operations. This 
        /// parameter is passed uninitialized. If nullptr is specified, no 
        /// value is retrieved for this parameter.
        /// </param>
        /// <param name="tag2">
        /// Contains the second label for subsequent drawing operations. This 
        /// parameter is passed uninitialized. If nullptr is specified, no 
        /// value is retrieved for this parameter.
        /// </param>
        void AddPage( ID2D1CommandList* commandList, D2D_SIZE_F pageSize, IStream* pagePrintTicketStream, D2D1_TAG* tag1 = nullptr, D2D1_TAG* tag2 = nullptr ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->AddPage( commandList, pageSize, pagePrintTicketStream, tag1, tag2 );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void AddPage( const CommandList& commandList, D2D_SIZE_F pageSize, IStream* pagePrintTicketStream, D2D1_TAG* tag1 = nullptr, D2D1_TAG* tag2 = nullptr ) const
        {
            AddPage( commandList.GetInterfacePointer<ID2D1CommandList>(), pageSize, pagePrintTicketStream, tag1, tag2 );
        }
        void AddPage( const CommandList& commandList, D2D_SIZE_F pageSize, const hcc::Stream& pagePrintTicketStream, D2D1_TAG* tag1 = nullptr, D2D1_TAG* tag2 = nullptr ) const
        {
            AddPage( commandList.GetInterfacePointer<ID2D1CommandList>( ), pageSize, pagePrintTicketStream.GetInterfacePointer<IStream>( ), tag1, tag2 );
        }


        /// <summary>
        /// Passes all remaining resources to the print sub-system, then 
        /// clean up and close the current print job.
        /// </summary>
        void Close( ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->Close( );
            CheckHRESULT( hr );
        }
    };

    


    /// <summary>
    /// Represents a brush based on an ID2D1Image.
    /// </summary>
    class ImageBrush : public Brush
    {
    public:
        using Base = Brush;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( ImageBrush, Base, ID2D1ImageBrush, ID2D1Brush )
    public:
        /// <summary>
        /// Sets the image associated with the provided image brush.
        /// </summary>
        /// <param name="image">
        /// The image to be associated with the image brush.
        /// </param>
        void SetImage( ID2D1Image* image ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->SetImage( image );
        }
        void SetImage( const Image& image ) const
        {
            SetImage( image.GetInterfacePointer<ID2D1Image>( ) );
        }

        /// <summary>
        /// Sets how the content inside the source rectangle in the image brush 
        /// will be extended on the x-axis.
        /// </summary>
        /// <param name="extendModeX">
        /// The extend mode on the x-axis of the image.
        /// </param>
        void SetExtendModeX( D2D1_EXTEND_MODE extendModeX ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->SetExtendModeX( extendModeX );
        }

        /// <summary>
        /// Sets the extend mode on the y-axis.
        /// </summary>
        /// <param name="extendModeY">
        /// The extend mode on the y-axis of the image.
        /// </param>
        void SetExtendModeY( D2D1_EXTEND_MODE extendModeY ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->SetExtendModeY( extendModeY );
        }

        /// <summary>
        /// Sets the interpolation mode for the image brush.
        /// </summary>
        /// <param name="interpolationMode">
        /// How the contents of the image will be interpolated 
        /// to handle the brush transform.
        /// </param>
        void SetInterpolationMode( D2D1_INTERPOLATION_MODE interpolationMode ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->SetInterpolationMode( interpolationMode );
        }

        /// <summary>
        /// Sets the source rectangle in the image brush.
        /// </summary>
        /// <param name="sourceRectangle">
        /// The source rectangle that defines the portion of the image to tile.
        /// </param>
        void SetSourceRectangle( const D2D1_RECT_F* sourceRectangle ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->SetSourceRectangle( sourceRectangle );
        }
        void SetSourceRectangle( const D2D1_RECT_F& sourceRectangle ) const
        {
            SetSourceRectangle( &sourceRectangle );
        }

        /// <summary>
        /// Gets the image associated with the image brush.
        /// </summary>
        /// <param name="image">
        /// When this method returns, contains the address of a pointer 
        /// to the image associated with this brush.
        /// </param>
        void GetImage( ID2D1Image** image ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->GetImage( image );
        }
        Image GetImage( ) const
        {
            ID2D1Image* ptr = nullptr;
            GetImage( &ptr );
            return Image( ptr );
        }


        /// <summary>
        /// Gets the extend mode of the image brush on the x-axis.
        /// </summary>
        /// <returns>
        /// This method returns the x-extend mode.
        /// </returns>
        D2D1_EXTEND_MODE GetExtendModeX( ) const
        {
            auto* pInterface = GetInterface( );
            return pInterface->GetExtendModeX( );
        }

        /// <summary>
        /// Gets the extend mode of the image brush on the y-axis of the image.
        /// </summary>
        /// <returns>
        /// This method returns the y-extend mode.
        /// </returns>
        D2D1_EXTEND_MODE GetExtendModeY( ) const
        {
            auto* pInterface = GetInterface( );
            return pInterface->GetExtendModeY( );
        }

        /// <summary>
        /// Gets the interpolation mode of the image brush.
        /// </summary>
        /// <returns>
        /// This method returns the interpolation mode.
        /// </returns>
        D2D1_INTERPOLATION_MODE GetInterpolationMode( ) const
        {
            auto* pInterface = GetInterface( );
            return pInterface->GetInterpolationMode( );
        }

        /// <summary>
        /// Gets the rectangle that will be used as the bounds of 
        /// the image when drawn as an image brush.
        /// </summary>
        /// <param name="sourceRectangle">
        /// When this method returns, contains the address of the 
        /// output source rectangle.
        /// </param>
        void GetSourceRectangle( D2D1_RECT_F* sourceRectangle ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->GetSourceRectangle( sourceRectangle );
        }
        void GetSourceRectangle( D2D1_RECT_F& sourceRectangle ) const
        {
            GetSourceRectangle( &sourceRectangle );
        }
        D2D1_RECT_F GetSourceRectangle( ) const
        {
            D2D1_RECT_F result{};
            GetSourceRectangle( &result );
            return result;
        }

    };

    /// <summary>
    /// Paints an area with a bitmap.
    /// </summary>
    class BitmapBrush1 : public BitmapBrush
    {
    public:
        using Base = BitmapBrush;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( BitmapBrush1, Base, ID2D1BitmapBrush1, ID2D1BitmapBrush )
    public:
        /// <summary>
        /// Sets the interpolation mode for the brush.
        /// </summary>
        /// <param name="">
        /// The mode to use.
        /// </param>
        /// <remakrs>
        ///  If interpolationMode is not a valid member of D2D1_INTERPOLATION_MODE, 
        /// then this method silently ignores the call.
        /// </remarks>
        void SetInterpolationMode1( D2D1_INTERPOLATION_MODE interpolationMode ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->SetInterpolationMode1( interpolationMode );
        }

        /// <summary>
        /// Returns the current interpolation mode of the brush.
        /// </summary>
        /// <returns>
        /// The current interpolation mode.
        /// </returns>
        D2D1_INTERPOLATION_MODE GetInterpolationMode1( ) const
        {
            auto* pInterface = GetInterface( );
            return pInterface->GetInterpolationMode1( );
        }
    };

    /// <summary>
    /// Describes the caps, miter limit, line join, and dash information for a stroke.
    /// </summary>
    class StrokeStyle1 : public StrokeStyle
    {
    public:
        using Base = StrokeStyle;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( StrokeStyle1, Base, ID2D1StrokeStyle1, ID2D1StrokeStyle )
    public:
        /// <summary>
        /// Gets the stroke transform type.
        /// </summary>
        /// <returns>
        /// This method returns the stroke transform type.
        /// </returns>
        D2D1_STROKE_TRANSFORM_TYPE GetStrokeTransformType( ) const
        {
            auto* pInterface = GetInterface( );
            return pInterface->GetStrokeTransformType( );
        }
    };

    /// <summary>
    /// The PathGeometry1 adds functionality to PathGeometry. In particular, 
    /// it provides the path geometry-specific ComputePointAndSegmentAtLength method.
    /// </summary>
    class PathGeometry1 : public PathGeometry
    {
    public:
        using Base = PathGeometry;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( PathGeometry1, Base, ID2D1PathGeometry1, ID2D1PathGeometry )
    public:
        /// <summary>
        /// Computes the point that exists at a given distance along the path geometry 
        /// along with the index of the segment the point is on and the directional 
        /// vector at that point.
        /// </summary>
        /// <param name="length">
        /// The distance to walk along the path.
        /// </param>
        /// <param name="startSegment">
        /// The index of the segment at which to begin walking. Note: This index is 
        /// global to the entire path, not just a particular figure.
        /// </param>
        /// <param name="worldTransform">
        /// The transform to apply to the path prior to walking.
        /// </param>
        /// <param name="flatteningTolerance">
        /// The flattening tolerance to use when walking along an arc or Bezier segment. 
        /// The flattening tolerance is the maximum error allowed when constructing a 
        /// polygonal approximation of the geometry. No point in the polygonal representation 
        /// will diverge from the original geometry by more than the flattening tolerance. 
        /// Smaller values produce more accurate results but cause slower execution.
        /// </param>
        /// <param name="pointDescription">
        /// When this method returns, contains a description of the point that can be found at 
        /// the given location.
        /// </param>
        void ComputePointAndSegmentAtLength( FLOAT length, UINT32 startSegment, const D2D1_MATRIX_3X2_F* worldTransform, FLOAT flatteningTolerance, D2D1_POINT_DESCRIPTION* pointDescription ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->ComputePointAndSegmentAtLength( length, startSegment, worldTransform, flatteningTolerance, pointDescription );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void ComputePointAndSegmentAtLength( FLOAT length, UINT32 startSegment, const D2D1_MATRIX_3X2_F& worldTransform, FLOAT flatteningTolerance, D2D1_POINT_DESCRIPTION* pointDescription ) const
        {
            ComputePointAndSegmentAtLength( length, startSegment, &worldTransform, flatteningTolerance, pointDescription );
        }

        void ComputePointAndSegmentAtLength( FLOAT length, UINT32 startSegment, const D2D1_MATRIX_3X2_F* worldTransform, D2D1_POINT_DESCRIPTION* pointDescription ) const
        {
            ComputePointAndSegmentAtLength( length, startSegment, worldTransform, D2D1_DEFAULT_FLATTENING_TOLERANCE, pointDescription );
        }

        void ComputePointAndSegmentAtLength( FLOAT length, UINT32 startSegment, const D2D1_MATRIX_3X2_F& worldTransform, D2D1_POINT_DESCRIPTION* pointDescription ) const
        {
            ComputePointAndSegmentAtLength( length, startSegment, &worldTransform, D2D1_DEFAULT_FLATTENING_TOLERANCE, pointDescription );
        }
    };

    /// <summary>
    /// Represents a set of run-time bindable and discoverable properties that 
    /// allow a data-driven application to modify the state of a Direct2D effect.
    /// </summary>
    class Properties : public Unknown
    {
    public:
        using Base = Unknown;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( Properties, Base, ID2D1Properties, IUnknown )
    public:
        /// <summary>
        /// Gets the number of top-level properties.
        /// </summary>
        /// <returns>
        /// This function returns the number of custom (non-system) properties 
        /// that can be accessed by the object.
        /// </returns>
        /// <remarks>
        /// This method returns the number of custom properties on the ID2D1Properties 
        /// interface. System properties and sub-properties are part of a closed set, 
        /// and are enumerable by iterating over this closed set.
        /// </remarks>
        UINT32 GetPropertyCount( ) const
        {
            auto* pInterface = GetInterface( );
            return pInterface->GetPropertyCount( );
        }

        /// <summary>
        /// Gets the property name that corresponds to the given index.
        /// </summary>
        /// <param name="index">
        /// The index of the property for which the name is being returned.
        /// </param>
        /// <param name="nameBuffer">
        /// When this method returns, contains the name being retrieved.
        /// </param>
        /// <param name="nameBufferSize">
        /// The number of characters in the name buffer.
        /// </param>
        /// <returns>
        /// false if the property does not exist, otherwise true.
        /// </returns>
        bool GetPropertyName( UINT32 index, PWSTR nameBuffer, UINT32 nameBufferSize ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetPropertyName( index, nameBuffer, nameBufferSize );
            if ( hr != HRESULT_FROM_WIN32( ERROR_INSUFFICIENT_BUFFER ) && hr != D2DERR_INVALID_PROPERTY )
            {
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
            }
            return hr != D2DERR_INVALID_PROPERTY;
        }



        /// <summary>
        /// Gets the number of characters for the given property name.
        /// </summary>
        /// <param name="index">
        /// The index of the property name to retrieve.
        /// </param>
        /// <returns>
        /// This method returns the size in characters of the name corresponding 
        /// to the given property index, or zero if the property index does not exist.
        /// </returns>
        UINT32 GetPropertyNameLength( UINT32 index ) const
        {
            auto* pInterface = GetInterface( );
            return pInterface->GetPropertyNameLength( index );
        }

        /// <summary>
        /// Gets the D2D1_PROPERTY_TYPE of the selected property.
        /// </summary>
        /// <param name="index">
        /// The index of the property for which the type will be retrieved.
        /// </param>
        /// <returns>
        /// This method returns a D2D1_PROPERTY_TYPE-typed value for the 
        /// type of the selected property.
        /// </returns>
        /// <remakrs>
        /// If the property does not exist, the method returns D2D1_PROPERTY_TYPE_UNKNOWN.
        /// </remarks>
        D2D1_PROPERTY_TYPE GetType( UINT32 index ) const
        {
            auto* pInterface = GetInterface( );
            return pInterface->GetType( index );

        }

        /// <summary>
        /// Gets the index corresponding to the given property name.
        /// </summary>
        /// <param name="propertyName">
        /// The name of the property to retrieve.
        /// </param>
        /// <returns>
        /// The index of the corresponding property name.
        /// </returns>
        /// <remarks>
        /// If the property doesn't exist, then this method returns D2D1_INVALID_PROPERTY_INDEX. 
        /// This reserved value will never map to a valid index, and will cause NULL or sentinel 
        /// values to be returned from other parts of the property interface.
        /// </remarks>
        UINT32 GetPropertyIndex( PCWSTR propertyName ) const
        {
            auto* pInterface = GetInterface( );
            return pInterface->GetPropertyIndex( propertyName );
        }

        /// <summary>
        /// Sets the named property to the given value.
        /// </summary>
        /// <param name="propertyName">
        /// The name of the property to set.
        /// </param>
        /// <param name="propertyType">
        /// The type of the property to set.
        /// </param>
        /// <param name="data">
        /// The data to set.
        /// </param>
        /// <param name="dataSize">
        /// The number of bytes in the data to set.
        /// </param>
        void SetValueByName( PCWSTR propertyName, D2D1_PROPERTY_TYPE propertyType, const BYTE* data, UINT32 dataSize ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->SetValueByName( propertyName, propertyType, data, dataSize );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Sets the corresponding property by index.
        /// </summary>
        /// <param name="propertyIndex">
        /// The index of the property to set.
        /// </param>
        /// <param name="propertyType">
        /// The type of the property to set.
        /// </param>
        /// <param name="data">
        /// The data to set.
        /// </param>
        /// <param name="dataSize">
        /// The number of bytes in the data to set.
        /// </param>
        void SetValue( UINT32 propertyIndex, D2D1_PROPERTY_TYPE propertyType, const BYTE* data, UINT32 dataSize ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->SetValue( propertyIndex, propertyType, data, dataSize );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Retrieves the given property or sub-property by name. '.' is the delimiter for
        /// sub-properties.
        /// </summary>
        /// <param name="propertyName">
        /// The name of the property to get.
        /// </param>
        /// <param name="propertyType">
        /// The type of the property to get.
        /// </param>
        /// <param name="data">
        /// When this method returns, contains the buffer with the data value.
        /// </param>
        /// <param name="dataSize">
        /// The number of bytes in the data to be retrieved.
        /// </param>
        void GetValueByName( PCWSTR propertyName, D2D1_PROPERTY_TYPE propertyType, BYTE* data, UINT32 dataSize ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetValueByName( propertyName, propertyType, data, dataSize );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Gets the value of the specified property by index.
        /// </summary>
        /// <param name="index">
        /// The index of the property from which the data is to be obtained.
        /// </param>
        /// <param name="propertyType">
        /// The type of the property to get.
        /// </param>
        /// <param name="data">
        /// When this method returns, contains the buffer with the data value.
        /// </param>
        /// <param name="dataSize">
        /// The number of bytes in the data to be retrieved.
        /// </param>
        void GetValue( UINT32 index, D2D1_PROPERTY_TYPE propertyType, BYTE* data, UINT32 dataSize ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetValue( index, propertyType, data, dataSize );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Gets the size of the property value in bytes, using the property index.
        /// </summary>
        /// <param name="index">
        /// The index of the property.
        /// </param>
        /// <returns>
        /// This method returns size of the value in bytes, using the property index.
        /// </returns>
        /// <remarks>
        /// This method returns zero if index does not exist.
        /// </remarks>
        UINT32 GetValueSize( UINT32 index ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetValueSize( index );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Retrieves the sub-properties of the given property by index.
        /// </summary>
        /// <param name="index">
        /// The index of the sub-properties to be retrieved.
        /// </param>
        /// <param name="subProperties">
        /// When this method returns, contains the address of a pointer 
        /// to the sub-properties.
        /// </param>
        /// <returns>
        /// true if the function was able to retrieve the sub-properties 
        /// of the given property by index, otherwise false.
        /// </returns>
        bool GetSubProperties( UINT32 index, ID2D1Properties** subProperties ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetSubProperties( index, subProperties );
            if ( hr != D2DERR_NO_SUBPROPERTIES && hr != D2DERR_INVALID_PROPERTY )
            {
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
            }
            return hr != D2DERR_NO_SUBPROPERTIES && hr != D2DERR_INVALID_PROPERTY;
        }
        Properties GetSubProperties( UINT32 index ) const
        {
            ID2D1Properties* ptr = nullptr;
            if ( GetSubProperties( index, &ptr ) )
            {
                return Properties( ptr );
            }
            else
            {
                return Properties( );
            }
        }

        void SetValueByName( PCWSTR name, const BYTE* data, UINT32 dataSize ) const
        {
            SetValueByName( name, D2D1_PROPERTY_TYPE_UNKNOWN, data, dataSize );
        }

        void SetValue( UINT32 index, const BYTE* data, UINT32 dataSize ) const
        {
            SetValue( index, D2D1_PROPERTY_TYPE_UNKNOWN, data, dataSize );
        }

        void GetValueByName( PCWSTR name, BYTE* data, UINT32 dataSize ) const
        {
            GetValueByName( name, D2D1_PROPERTY_TYPE_UNKNOWN, data, dataSize );
        }

        void GetValue( UINT32 index, BYTE* data, UINT32 dataSize ) const
        {
            GetValue( index, D2D1_PROPERTY_TYPE_UNKNOWN, data, dataSize );
        }

        //
        // Templatized helper functions:
        //
        template<typename T>
        void GetValueByName( PCWSTR propertyName, T* value ) const
        {
            GetValueByName( propertyName, reinterpret_cast<BYTE*>( value ), sizeof( *value ) );
        }

        template<typename T>
        T GetValueByName( PCWSTR propertyName ) const
        {
            T value;
            GetValueByName( propertyName, reinterpret_cast<BYTE*>( &value ), sizeof( value ) );
            return value;
        }


        template<typename T>
        void SetValueByName(PCWSTR propertyName, const T& value ) const
        {
            SetValueByName( propertyName, reinterpret_cast<const BYTE*>( &value ), sizeof( value ) );
        }

        template<typename U>
        void GetValue(U index, BYTE* data, UINT32 dataSize ) const
        {
            GetValue( static_cast<UINT32>( index ), data, dataSize );
        }

        template<typename T, typename U>
        void GetValue(U index, T* value) const
        {
            GetValue( static_cast<UINT32>( index ), reinterpret_cast<BYTE*>( value ), sizeof( *value ) );
        }

        template<typename T, typename U>
        T GetValue(U index) const
        {
            T value;
            GetValue( static_cast<UINT32>( index ), reinterpret_cast<BYTE*>( &value ), sizeof( value ) );
            return value;
        }

        template<typename U>
        void SetValue(U index,const BYTE* data, UINT32 dataSize ) const
        {
            return SetValue( static_cast<UINT32>( index ), data, dataSize );
        }

        template<typename T, typename U>
        void SetValue(U index, const T& value ) const
        {
            return SetValue( static_cast<UINT32>( index ), reinterpret_cast<const BYTE*>( &value ), sizeof( value ) );
        }

        template<typename U>
        void GetPropertyName(U index, PWSTR name, UINT32 nameCount ) const
        {
            GetPropertyName( static_cast<UINT32>( index ), name, nameCount );
        }

        template<typename U> UINT32 GetPropertyNameLength( U index ) const
        {
            return GetPropertyNameLength( static_cast<UINT32>( index ) );
        }

        template<typename U>
        D2D1_PROPERTY_TYPE GetType( U index ) const
        {
            return GetType( static_cast<UINT32>( index ) );
        }

        template<typename U>
        UINT32 GetValueSize( U index ) const
        {
            return GetValueSize( static_cast<UINT32>( index ) );
        }

        template<typename U>
        void GetSubProperties(U index, ID2D1Properties** subProperties ) const
        {
            GetSubProperties( static_cast<UINT32>( index ), subProperties );
        }
    };


    /// <summary>
    /// Represents a basic image-processing construct in Direct2D.
    /// </summary>
    class Effect : public Properties
    {
    public:
        using Base = Properties;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( Effect, Base, ID2D1Effect, ID2D1Properties )
    public:
        /// <summary>
        /// Sets the input to the given effect. The input can be a concrete bitmap or the
        /// output of another effect.
        /// </summary>
        /// <param name="index">
        /// The index of the image to set.
        /// </param>
        /// <param name="inputImage">
        /// The input image to set.
        /// </param>
        /// <param name="invalidate">
        /// Whether to invalidate the graph at the location of the effect input
        /// </param>
        /// <remarks>
        /// If the input index is out of range, the input image is ignored.
        /// </remarks>
        void SetInput( UINT32 index, ID2D1Image* inputImage, BOOL invalidate = TRUE ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->SetInput( index, inputImage, invalidate );
        }
        void SetInput( UINT32 index, const Image& inputImage, BOOL invalidate = TRUE ) const
        {
            SetInput( index, inputImage.GetInterfacePointer<ID2D1Image>( ), invalidate );
        }

        /// <summary>
        /// If the effect supports a variable number of inputs, this sets the number of
        /// inputs that are currently active on the effect.
        /// </summary>
        /// <param name="inputCount">
        /// The number of inputs to the effect.
        /// </param>
        /// <remarks>
        /// <p>
        /// Most effects do not support a variable number of inputs. Use Properties::GetValue 
        /// with the D2D1_PROPERTY_MIN_INPUTS and D2D1_PROPERTY_MAX_INPUTS values to determine 
        /// the number of inputs supported by an effect.
        /// </p>
        /// <p>
        /// If the input count is less than the minimum or more than the maximum supported inputs, 
        /// the call will fail and throw a Harlinn::Common::Core::Exception.
        /// </p>
        /// <p>
        /// If the input count is unchanged, the call will succeed.
        /// </p>
        /// <p>
        /// Any inputs currently selected on the effect will be unaltered by this call unless 
        /// the number of inputs is made smaller. If the number of inputs is made smaller, 
        /// inputs beyond the selected range will be released.
        /// </p>
        /// <p>
        /// If the method fails, the existing input and input count will remain unchanged.
        /// </p>
        /// </remarks>
        void SetInputCount( UINT32 inputCount ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->SetInputCount( inputCount );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Returns the input image to the effect. The input could be another effect or a
        /// bitmap.
        /// </summary>
        /// <param name="index">
        /// The index of the image to retrieve.
        /// </param>
        /// <param name="inputImage">
        /// When this method returns, contains the address of a pointer to the image that 
        /// is identified by Index.
        /// </param>
        void GetInput( UINT32 index, ID2D1Image** inputImage ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->GetInput( index, inputImage );
        }
        Image GetInput( UINT32 index ) const
        {
            ID2D1Image* ptr = nullptr;
            GetInput( index, &ptr );
            return Image( ptr );
        }

        /// <summary>
        /// This returns the number of input that are bound into this effect.
        /// </summary>
        /// <returns>
        /// This function returns the number of inputs to the effect.
        /// </returns>
        UINT32 GetInputCount( ) const
        {
            auto* pInterface = GetInterface( );
            return pInterface->GetInputCount( );
        }

        /// <summary>
        /// Returns the output image of the given effect. This can be set as the input to
        /// another effect or can be drawn with DrawImage.
        /// </summary>
        /// <param name="outputImage">
        /// When this method returns, contains the address of a pointer to the output image for the effect.
        /// </param>
        void GetOutput( ID2D1Image** outputImage ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->GetOutput( outputImage );
        }
        Image GetOutput( ) const
        {
            ID2D1Image* ptr = nullptr;
            GetOutput( &ptr );
            return Image( ptr );
        }

        /// <summary>
        /// <p>
        /// Sets the given input effect by index.
        /// </p>
        /// <p>
        /// This method gets the output of the given effect and then passes 
        /// the output image to the SetInput method.
        /// </p>
        /// </summary>
        /// <param name="index">
        /// The index of the input to set.
        /// </param>
        /// <param name="inputEffect">
        /// The input effect to set.
        /// </param>
        /// <param name="invalidate">
        /// Whether to invalidate the graph at the location of the effect input
        /// </param>
        void SetInputEffect( UINT32 index, ID2D1Effect* inputEffect, BOOL invalidate = TRUE ) const
        {
            ID2D1Image* output = nullptr;
            if ( inputEffect != nullptr )
            {
                inputEffect->GetOutput( &output );
            }
            SetInput( index, output, invalidate );
            if ( output != nullptr )
            {
                output->Release( );
            }
        }
        void SetInputEffect( UINT32 index, const Effect& inputEffect, BOOL invalidate = TRUE ) const
        {
            SetInputEffect( index, inputEffect.GetInterfacePointer<ID2D1Effect>(), invalidate );
        }
    };

    /// <summary>
    /// Represents a bitmap that can be used as a surface for a DeviceContext 
    /// or mapped into system memory, and can contain additional color context 
    /// information.
    /// </summary>
    class Bitmap1 : public Bitmap
    {
    public:
        using Base = Bitmap;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( Bitmap1, Base, ID2D1Bitmap1, ID2D1Bitmap )
    public:
        /// <summary>
        /// Retrieves the color context information associated with the bitmap.
        /// </summary>
        /// <param name="colorContext">
        /// When this method returns, contains the address of a pointer to the 
        /// color context interface associated with the bitmap.
        /// </param>
        void GetColorContext( ID2D1ColorContext** colorContext ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->GetColorContext( colorContext );
        }
        ColorContext GetColorContext( ) const
        {
            ID2D1ColorContext* ptr = nullptr;
            GetColorContext( &ptr );
            return ColorContext( ptr );
        }

        /// <summary>
        /// Retrieves the bitmap options used when creating the API.
        /// </summary>
        /// <returns>
        /// The options used when creating the bitmap.
        /// </returns>
        D2D1_BITMAP_OPTIONS GetOptions( ) const
        {
            auto* pInterface = GetInterface( );
            return pInterface->GetOptions( );
        }

        /// <summary>
        /// Retrieves the DXGI surface from the corresponding bitmap, if the bitmap was
        /// created from a device derived from a D3D device.
        /// </summary>
        /// <param name="dxgiSurface">
        /// The underlying DXGI surface for the bitmap.
        /// </param>
        /// <remarks>
        /// <p>
        /// The bitmap used must have been created from a DXGI surface render target, 
        /// a derived render target, or a device context created from an ID2D1Device.
        /// </p>
        /// <p>
        /// The returned surface can be used with Microsoft Direct3D or any other API 
        /// that interoperates with shared surfaces. The application must transitively 
        /// ensure that the surface is usable on the Direct3D device that is used in 
        /// this context. For example, if using the surface with Direct2D then the Direct2D 
        /// render target must have been created through Graphics::Factory::CreateDxgiSurfaceRenderTarget 
        /// or on a device context created on the same device.
        /// </p>
        /// </remarks>
        void GetSurface( IDXGISurface** dxgiSurface ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetSurface( dxgiSurface );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        DXGI::Surface GetSurface( ) const
        {
            IDXGISurface* ptr = nullptr;
            GetSurface( &ptr );
            return DXGI::Surface( ptr );
        }

        /// <summary>
        /// Maps the given bitmap into memory. The bitmap must have been created with the
        /// D2D1_BITMAP_OPTIONS_CPU_READ flag.
        /// </summary>
        /// <param name="options">
        /// The options used in mapping the bitmap into memory.
        /// </param>
        /// <param name="mappedRect">
        /// When this method returns, contains a reference to the rectangle that is 
        /// mapped into memory.
        /// </param>
        /// <remarks>
        /// <p>
        /// You can't use bitmaps for some purposes while mapped. Particularly, the 
        /// Bitmap::CopyFromBitmap method doesn't work if either the source or 
        /// destination bitmap is mapped.
        /// </p>
        /// <p>
        /// The bitmap must have been created with the D2D1_BITMAP_OPTIONS_CPU_READ 
        /// flag specified.
        /// </p>
        /// </remarks>
        void Map( D2D1_MAP_OPTIONS options, D2D1_MAPPED_RECT* mappedRect ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->Map( options, mappedRect );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Unmaps the given bitmap from memory.
        /// </summary>
        /// <remarks>
        /// <p>
        /// Any memory returned from the Map call is now invalid and may be reclaimed by 
        /// the operating system or used for other purposes.
        /// </p>
        /// <p>
        /// The bitmap must have been previously mapped.
        /// </p>
        /// </remarks>
        void Unmap( ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->Unmap( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    /// <summary>
    /// Represents a collection of D2D1_GRADIENT_STOP objects for linear and radial 
    /// gradient brushes. It provides get methods for all the new parameters added 
    /// to the gradient stop collection.
    /// </summary>
    class GradientStopCollection1 : public GradientStopCollection
    {
    public:
        using Base = GradientStopCollection;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( GradientStopCollection1, Base, ID2D1GradientStopCollection1, ID2D1GradientStopCollection )
    public:
        /// <summary>
        /// Copies the gradient stops from the collection into memory.
        /// </summary>
        /// <param name="gradientStops">
        /// When this method returns, contains a pointer to a one-dimensional 
        /// array of D2D1_GRADIENT_STOP structures.
        /// </param>
        /// <param name="gradientStopsCount">
        /// The number of gradient stops to copy.
        /// </param>
        /// <remarks>
        /// <p>
        /// If the collection was created using DeviceContext::CreateGradientStopCollection, 
        /// this function returns the same values specified in the creation function. If the 
        /// collection was created using ID2D1RenderTarget::CreateGradientStopCollection, the 
        /// stops returned here will first be transformed into the gamma space specified by 
        /// the colorInterpolationGamma parameter. 
        /// </p>
        /// <p>
        /// If gradientStopsCount is less than the number of gradient stops in the collection, 
        /// the remaining gradient stops are omitted. If gradientStopsCount is larger than the 
        /// number of gradient stops in the collection, the extra gradient stops are set to NULL. 
        /// To obtain the number of gradient stops in the collection, use the GetGradientStopCount 
        /// function.
        /// </p>
        /// </remarks>
        void GetGradientStops1( D2D1_GRADIENT_STOP* gradientStops, UINT32 gradientStopsCount ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->GetGradientStops1( gradientStops, gradientStopsCount );
        }

        /// <summary>
        /// Gets the color space of the input colors as well as the space 
        /// in which gradient stops are interpolated.
        /// </summary>
        /// <returns>
        /// This method returns the color space.
        /// </returns>
        /// <remarks>
        /// If the collection was created using RenderTarget::CreateGradientStopCollection, 
        /// this function returns the color space related to the color interpolation gamma.
        /// </remarks>
        D2D1_COLOR_SPACE GetPreInterpolationSpace( ) const
        {
            auto* pInterface = GetInterface( );
            return pInterface->GetPreInterpolationSpace( );
        }

        /// <summary>
        /// Returns the color space colors will be converted to after interpolation occurs.
        /// </summary>
        /// <returns>
        /// This function returns the color space.
        /// </returns>
        /// <remarks>
        /// If the collection was created using RenderTarget::CreateGradientStopCollection, 
        /// this method returns D2D1_COLOR_SPACE_SRGB.
        /// </remarks>
        D2D1_COLOR_SPACE GetPostInterpolationSpace( ) const
        { 
            auto* pInterface = GetInterface( );
            return pInterface->GetPostInterpolationSpace( );
        }

        /// <summary>
        /// Gets the precision of the gradient buffer.
        /// </summary>
        /// <returns>
        /// The buffer precision of the gradient buffer.
        /// </returns>
        /// <remarks>
        /// If collection was created using RenderTarget::CreateGradientStopCollection, 
        /// this method returns D2D1_BUFFER_PRECISION_8BPC_UNORM.
        /// </remarks>
        D2D1_BUFFER_PRECISION GetBufferPrecision( ) const
        {
            auto* pInterface = GetInterface( );
            return pInterface->GetBufferPrecision( );
        }

        /// <summary>
        /// Retrieves the color interpolation mode that the gradient stop collection uses.
        /// </summary>
        /// <returns>
        /// The color interpolation mode.
        /// </returns>
        D2D1_COLOR_INTERPOLATION_MODE GetColorInterpolationMode( ) const
        {
            auto* pInterface = GetInterface( );
            return pInterface->GetColorInterpolationMode( );
        }
    };


    /// <summary>
    /// Implementation of a drawing state block that adds the functionality 
    /// of primitive blend in addition to already existing anti-alias mode, 
    /// transform, tags and text rendering mode.
    /// </summary>
    class DrawingStateBlock1 : public DrawingStateBlock
    {
    public:
        using Base = DrawingStateBlock;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( DrawingStateBlock1, Base, ID2D1DrawingStateBlock1, ID2D1DrawingStateBlock )
    public:
        /// <summary>
        /// Gets the anti-aliasing mode, transform, tags, primitive blend, 
        /// and unit mode portion of the drawing state.
        /// </summary>
        /// <param name="stateDescription">
        /// When this method returns, contains the anti-aliasing mode, transform, 
        /// tags, primitive blend, and unit mode portion of the drawing state. 
        /// You must allocate storage for this parameter.
        /// </param>
        void GetDescription( D2D1_DRAWING_STATE_DESCRIPTION1* stateDescription ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->GetDescription( stateDescription );
        }
        void GetDescription( D2D1_DRAWING_STATE_DESCRIPTION1& stateDescription ) const
        {
            GetDescription( &stateDescription );
        }

        using Base::GetDescription;

        /// <summary>
        /// Sets the D2D1_DRAWING_STATE_DESCRIPTION1 associated with this drawing state block.
        /// </summary>
        /// <param name="stateDescription">
        /// The D2D1_DRAWING_STATE_DESCRIPTION1 to be set associated with this drawing state block.
        /// </param>
        void SetDescription( const D2D1_DRAWING_STATE_DESCRIPTION1* stateDescription ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->SetDescription( stateDescription );
        }
        void SetDescription( const D2D1_DRAWING_STATE_DESCRIPTION1& stateDescription ) const
        {
            SetDescription( &stateDescription );
        }

        using Base::SetDescription;
    };

    

    class Device;
    /// <summary>
    /// <p>
    /// Represents a set of state and command buffers that are used to render to a target.
    /// </p>
    /// <p>
    /// The device context can render to a target bitmap or a command list.
    /// </p>
    /// </summary>
    class DeviceContext : public RenderTarget
    {
    public:
        typedef RenderTarget Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( DeviceContext, RenderTarget, ID2D1DeviceContext, ID2D1RenderTarget )

        /// <summary>
        /// Creates a bitmap that can be used as a target surface, for reading back to 
        /// the CPU, or as a source for the DrawBitmap and BitmapBrush APIs. In addition, 
        /// color context information can be passed to the bitmap.
        /// </summary>
        /// <param name="size">
        /// The pixel size of the bitmap to be created.
        /// </param>
        /// <param name="sourceData">
        /// The initial data that will be loaded into the bitmap.
        /// </param>
        /// <param name="pitch">
        /// The pitch of the source data, if specified.
        /// </param>
        /// <param name="bitmapProperties">
        /// The properties of the bitmap to be created.
        /// </param>
        /// <param name="bitmap">
        /// When this method returns, contains the address of a pointer to a 
        /// new bitmap object.
        /// </param>
        /// <remarks>
        /// The new bitmap can be used as a target for SetTarget if it is created 
        /// with D2D1_BITMAP_OPTIONS_TARGET.
        /// </remarks>
        void CreateBitmap( const D2D1_SIZE_U& size, const void* sourceData, UINT32 pitch, const D2D1_BITMAP_PROPERTIES1* bitmapProperties, ID2D1Bitmap1** bitmap ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateBitmap( size, sourceData, pitch, bitmapProperties, bitmap );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void CreateBitmap( const D2D1_SIZE_U& size, const void* sourceData, UINT32 pitch, const D2D1_BITMAP_PROPERTIES1& bitmapProperties, ID2D1Bitmap1** bitmap ) const
        {
            CreateBitmap( size, sourceData, pitch, &bitmapProperties, bitmap );
        }
        void CreateBitmap( const D2D1_SIZE_U& size, const void* sourceData, const D2D1_BITMAP_PROPERTIES1* bitmapProperties, ID2D1Bitmap1** bitmap ) const
        {
            CreateBitmap( size, sourceData, 0, bitmapProperties, bitmap );
        }
        void CreateBitmap( const D2D1_SIZE_U& size, const void* sourceData, const D2D1_BITMAP_PROPERTIES1& bitmapProperties, ID2D1Bitmap1** bitmap ) const
        {
            CreateBitmap( size, sourceData, 0, &bitmapProperties, bitmap );
        }
        void CreateBitmap( const D2D1_SIZE_U& size, UINT32 pitch, const D2D1_BITMAP_PROPERTIES1* bitmapProperties, ID2D1Bitmap1** bitmap ) const
        {
            CreateBitmap( size, nullptr, pitch, bitmapProperties, bitmap );
        }
        void CreateBitmap( const D2D1_SIZE_U& size, UINT32 pitch, const D2D1_BITMAP_PROPERTIES1& bitmapProperties, ID2D1Bitmap1** bitmap ) const
        {
            CreateBitmap( size, nullptr, pitch, &bitmapProperties, bitmap );
        }
        void CreateBitmap( const D2D1_SIZE_U& size, const D2D1_BITMAP_PROPERTIES1* bitmapProperties, ID2D1Bitmap1** bitmap ) const
        {
            CreateBitmap( size, nullptr, 0, bitmapProperties, bitmap );
        }
        void CreateBitmap( const D2D1_SIZE_U& size, const D2D1_BITMAP_PROPERTIES1& bitmapProperties, ID2D1Bitmap1** bitmap ) const
        {
            CreateBitmap( size, nullptr, 0, &bitmapProperties, bitmap );
        }
        void CreateBitmap( const D2D1_SIZE_U& size, const void* sourceData, UINT32 pitch, const D2D1_BITMAP_PROPERTIES1& bitmapProperties, ID2D1Bitmap1** bitmap )
        {
            CreateBitmap( size, sourceData, pitch, &bitmapProperties, bitmap );
        }
        Bitmap1 CreateBitmap( const D2D1_SIZE_U& size, const void* sourceData, UINT32 pitch, const D2D1_BITMAP_PROPERTIES1* bitmapProperties ) const
        {
            ID2D1Bitmap1* ptr = nullptr;
            CreateBitmap( size, sourceData, pitch, bitmapProperties, &ptr );
            return Bitmap1( ptr );
        }
        Bitmap1 CreateBitmap( const D2D1_SIZE_U& size, const void* sourceData, UINT32 pitch, const D2D1_BITMAP_PROPERTIES1& bitmapProperties ) const
        {
            return CreateBitmap( size, sourceData, pitch, &bitmapProperties );
        }
        Bitmap1 CreateBitmap( const D2D1_SIZE_U& size, const void* sourceData, const D2D1_BITMAP_PROPERTIES1* bitmapProperties ) const
        {
            return CreateBitmap( size, sourceData, 0, bitmapProperties );
        }
        Bitmap1 CreateBitmap( const D2D1_SIZE_U& size, const void* sourceData, const D2D1_BITMAP_PROPERTIES1& bitmapProperties ) const
        {
            return CreateBitmap( size, sourceData, 0, &bitmapProperties );
        }
        Bitmap1 CreateBitmap( const D2D1_SIZE_U& size, UINT32 pitch, const D2D1_BITMAP_PROPERTIES1* bitmapProperties ) const
        {
            return CreateBitmap( size, nullptr, pitch, bitmapProperties );
        }
        Bitmap1 CreateBitmap( const D2D1_SIZE_U& size, UINT32 pitch, const D2D1_BITMAP_PROPERTIES1& bitmapProperties ) const
        {
            return CreateBitmap( size, nullptr, pitch, bitmapProperties );
        }
        Bitmap1 CreateBitmap( const D2D1_SIZE_U& size, const D2D1_BITMAP_PROPERTIES1* bitmapProperties ) const
        {
            return CreateBitmap( size, nullptr, 0, bitmapProperties );
        }
        Bitmap1 CreateBitmap( const D2D1_SIZE_U& size, const D2D1_BITMAP_PROPERTIES1& bitmapProperties ) const
        {
            return CreateBitmap( size, nullptr, 0, bitmapProperties );
        }
        


        using Base::CreateBitmap;

        /// <summary>
        /// Create a D2D bitmap by copying a WIC bitmap.
        /// </summary>
        /// <param name="wicBitmapSource">
        /// The WIC bitmap source to copy from.
        /// </param>
        /// <param name="bitmapProperties">
        /// A bitmap properties structure that specifies bitmap creation options.
        /// </param>
        /// <param name="bitmap">
        /// The address of the newly created bitmap object.
        /// </param>
        /// <remarks>
        /// <p>
        /// Starting with Windows 8.1, the bitmapProperties parameter is optional. 
        /// When it is not specified, the created bitmap inherits the pixel format 
        /// and alpha mode from wicBitmapSource.
        /// </p>
        /// <p>
        /// When the bitmapProperties parameter is specified, the value in 
        /// bitmapProperties->pixelFormat must either be DXGI_FORMAT_UNKNOWN 
        /// or must match the WIC pixel format in wicBitmapSource.
        /// </p>
        /// <p>
        /// When bitmapProperties->pixelFormat.alphaMode is set to 
        /// D2D1_ALPHA_MODE_UNKNOWN, the newly created bitmap inherits the alpha 
        /// mode from wicBitmapSource. When bitmapProperties->pixelFormat.alphaMode 
        /// is set to D2D1_ALPHA_MODE_PREMULTIPLIED, D2D1_ALPHA_MODE_STRAIGHT, 
        /// or D2D1_ALPHA_MODE_IGNORE, this forces the newly created bitmap to use 
        /// the specified alpha mode.
        /// </p>
        /// </remarks>
        void CreateBitmapFromWicBitmap( IWICBitmapSource* wicBitmapSource, D2D1_BITMAP_PROPERTIES1* bitmapProperties, ID2D1Bitmap1** bitmap ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateBitmapFromWicBitmap( wicBitmapSource, bitmapProperties, bitmap );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void CreateBitmapFromWicBitmap( IWICBitmapSource* wicBitmapSource, D2D1_BITMAP_PROPERTIES1& bitmapProperties, ID2D1Bitmap1** bitmap ) const
        {
            CreateBitmapFromWicBitmap( wicBitmapSource, &bitmapProperties, bitmap );
        }
        void CreateBitmapFromWicBitmap( IWICBitmapSource* wicBitmapSource, ID2D1Bitmap1** bitmap ) const
        {
            CreateBitmapFromWicBitmap( wicBitmapSource, nullptr, bitmap );
        }

        Bitmap1 CreateBitmapFromWicBitmap( IWICBitmapSource* wicBitmapSource, D2D1_BITMAP_PROPERTIES1* bitmapProperties = nullptr ) const
        {
            ID2D1Bitmap1* ptr = nullptr;
            CreateBitmapFromWicBitmap( wicBitmapSource, bitmapProperties, &ptr );
            return Bitmap1( ptr );
        }
        Bitmap1 CreateBitmapFromWicBitmap( IWICBitmapSource* wicBitmapSource, D2D1_BITMAP_PROPERTIES1& bitmapProperties ) const
        {
            return CreateBitmapFromWicBitmap( wicBitmapSource, &bitmapProperties );
        }
        
        HW_EXPORT void CreateBitmapFromWicBitmap( const Imaging::BitmapSource& wicBitmapSource, D2D1_BITMAP_PROPERTIES1* bitmapProperties, ID2D1Bitmap1** bitmap ) const;
        HW_EXPORT void CreateBitmapFromWicBitmap( const Imaging::BitmapSource& wicBitmapSource, D2D1_BITMAP_PROPERTIES1& bitmapProperties, ID2D1Bitmap1** bitmap ) const;
        HW_EXPORT void CreateBitmapFromWicBitmap( const Imaging::BitmapSource& wicBitmapSource, ID2D1Bitmap1** bitmap ) const;
        HW_EXPORT Bitmap1 CreateBitmapFromWicBitmap( const Imaging::BitmapSource& wicBitmapSource, D2D1_BITMAP_PROPERTIES1* bitmapProperties = nullptr ) const;
        HW_EXPORT Bitmap1 CreateBitmapFromWicBitmap( const Imaging::BitmapSource& wicBitmapSource, D2D1_BITMAP_PROPERTIES1& bitmapProperties ) const;



        using Base::CreateBitmapFromWicBitmap;

        /// <summary>
        /// Creates a color context from a color space.  If the space is Custom, the context
        /// is initialized from the profile/profileSize arguments.  Otherwise the context is
        /// initialized with the profile bytes associated with the space and
        /// profile/profileSize are ignored.
        /// </summary>
        /// <param name="space">
        /// The space of color context to create.
        /// </param>
        /// <param name="profile">
        /// A buffer containing the ICC profile bytes used to initialize the color context when 
        /// space is D2D1_COLOR_SPACE_CUSTOM. For other types, the parameter is ignored and 
        /// should be set to nullptr.
        /// </param>
        /// <param name="profileSize">
        /// The size in bytes of profile.
        /// </param>
        /// <param name="colorContext">
        /// When this method returns, contains the address of a pointer to a new color 
        /// context object.
        /// </param>
        void CreateColorContext( D2D1_COLOR_SPACE space, CONST BYTE* profile, UINT32 profileSize, ID2D1ColorContext** colorContext ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateColorContext( space, profile, profileSize, colorContext );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void CreateColorContext( D2D1_COLOR_SPACE space, ID2D1ColorContext** colorContext ) const
        {
            CreateColorContext( space, nullptr, 0, colorContext );
        }
        void CreateColorContext( ID2D1ColorContext** colorContext ) const
        {
            CreateColorContext( D2D1_COLOR_SPACE_SRGB, nullptr, 0, colorContext );
        }
        ColorContext CreateColorContext( D2D1_COLOR_SPACE space = D2D1_COLOR_SPACE_SRGB, CONST BYTE* profile = nullptr, UINT32 profileSize = 0 ) const
        {
            ID2D1ColorContext* ptr = nullptr;
            CreateColorContext( space, profile, profileSize, &ptr );
            return ColorContext( ptr );
        }

        /// <summary>
        /// Creates a color context by loading it from the specified filename. 
        /// The profile bytes are the contents of the file specified by Filename.
        /// </summary>
        /// <param name="filename">
        /// The path to the file containing the profile bytes to initialize 
        /// the color context with.
        /// </param>
        /// <param name="colorContext">
        /// When this method returns, contains the address of a pointer to a 
        /// new color context.
        /// </param>
        void CreateColorContextFromFilename( PCWSTR filename, ID2D1ColorContext** colorContext ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateColorContextFromFilename( filename, colorContext );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        ColorContext CreateColorContextFromFilename( PCWSTR filename ) const
        {
            ID2D1ColorContext* ptr = nullptr;
            CreateColorContextFromFilename( filename, &ptr );
            return ColorContext( ptr );
        }

        /// <summary>
        /// Creates a color context from an IWICColorContext.
        /// </summary>
        /// <param name="wicColorContext">
        /// The IWICColorContext used to initialize the color context.
        /// </param>
        /// <param name="colorContext">
        /// When this method returns, contains the address of a pointer 
        /// to a new color context.
        /// </param>
        /// <remarks>
        /// The new color context can be used in D2D1_BITMAP_PROPERTIES1 to initialize 
        /// the color context of a created bitmap. The model field of the profile 
        /// header is inspected to determine whether this profile is sRGB or scRGB and 
        /// the color space is updated respectively. Otherwise the space is custom.
        /// </remarks>
        void CreateColorContextFromWicColorContext( IWICColorContext* wicColorContext, ID2D1ColorContext** colorContext ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateColorContextFromWicColorContext( wicColorContext, colorContext );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        ColorContext CreateColorContextFromWicColorContext( IWICColorContext* wicColorContext ) const
        {
            ID2D1ColorContext* ptr = nullptr;
            CreateColorContextFromWicColorContext( wicColorContext, &ptr );
            return ColorContext( ptr );
        }
        HW_EXPORT void CreateColorContextFromWicColorContext( const Imaging::ColorContext& wicColorContext, ID2D1ColorContext** colorContext ) const;
        HW_EXPORT ColorContext CreateColorContextFromWicColorContext( const Imaging::ColorContext& wicColorContext ) const;

        /// <summary>
        /// Creates a bitmap from a DXGI surface that can be set as a target 
        /// surface or have additional color context information specified.
        /// </summary>
        /// <param name="surface">
        /// <p>
        /// The DXGI surface from which the bitmap can be created.
        /// </p>
        /// <p>
        /// The DXGI surface must have been created from the same Direct3D device 
        /// that the Direct2D device context is associated with.
        /// </p>
        /// </param>
        /// <param name="bitmapProperties">
        /// The bitmap properties specified in addition to the surface.
        /// </param>
        /// <param name="bitmap">
        /// When this method returns, contains the address of a pointer to 
        /// a new bitmap object.
        /// </param>
        void CreateBitmapFromDxgiSurface( IDXGISurface* surface, const D2D1_BITMAP_PROPERTIES1* bitmapProperties, ID2D1Bitmap1** bitmap ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateBitmapFromDxgiSurface( surface, bitmapProperties, bitmap );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void CreateBitmapFromDxgiSurface( IDXGISurface* surface, const D2D1_BITMAP_PROPERTIES1& bitmapProperties, ID2D1Bitmap1** bitmap ) const
        {
            CreateBitmapFromDxgiSurface( surface, &bitmapProperties, bitmap );
        }

        template<typename T>
            requires std::is_base_of_v<DXGI::Surface, T>
        void CreateBitmapFromDxgiSurface( const T& surface, const D2D1_BITMAP_PROPERTIES1* bitmapProperties, ID2D1Bitmap1** bitmap ) const
        {
            using ItfT = typename T::InterfaceType;
            CreateBitmapFromDxgiSurface( surface.GetInterfacePointer<ItfT>(), bitmapProperties, bitmap );
        }
        template<typename T>
            requires std::is_base_of_v<DXGI::Surface, T>
        void CreateBitmapFromDxgiSurface( const T& surface, const D2D1_BITMAP_PROPERTIES1& bitmapProperties, ID2D1Bitmap1** bitmap ) const
        {
            CreateBitmapFromDxgiSurface( surface, &bitmapProperties, bitmap );
        }
        void CreateBitmapFromDxgiSurface( IDXGISurface* surface, ID2D1Bitmap1** bitmap ) const
        {
            CreateBitmapFromDxgiSurface( surface, nullptr, bitmap );
        }
        template<typename T>
            requires std::is_base_of_v<DXGI::Surface, T>
        void CreateBitmapFromDxgiSurface( const T& surface, ID2D1Bitmap1** bitmap ) const
        {
            using ItfT = typename T::InterfaceType;
            CreateBitmapFromDxgiSurface( surface.GetInterfacePointer<ItfT>( ), nullptr, bitmap );
        }
        Bitmap1 CreateBitmapFromDxgiSurface( IDXGISurface* surface, const D2D1_BITMAP_PROPERTIES1* bitmapProperties = nullptr ) const
        {
            ID2D1Bitmap1* ptr = nullptr;
            CreateBitmapFromDxgiSurface( surface, bitmapProperties, &ptr );
            return Bitmap1( ptr );
        }
        Bitmap1 CreateBitmapFromDxgiSurface( IDXGISurface* surface, const D2D1_BITMAP_PROPERTIES1& bitmapProperties ) const
        {
            return CreateBitmapFromDxgiSurface( surface, &bitmapProperties );
        }

        template<typename T>
            requires std::is_base_of_v<DXGI::Surface, T>
        Bitmap1 CreateBitmapFromDxgiSurface( const T& surface, const D2D1_BITMAP_PROPERTIES1* bitmapProperties = nullptr ) const
        {
            using ItfT = typename T::InterfaceType;
            return CreateBitmapFromDxgiSurface( surface.GetInterfacePointer<ItfT>( ), bitmapProperties );
        }
        template<typename T>
            requires std::is_base_of_v<DXGI::Surface, T>
        Bitmap1 CreateBitmapFromDxgiSurface( const T& surface, const D2D1_BITMAP_PROPERTIES1& bitmapProperties ) const
        {
            return CreateBitmapFromDxgiSurface( surface, &bitmapProperties );
        }



        /// <summary>
        /// Create a new effect, the effect must either be built in or previously registered
        /// through ID2D1Factory1::RegisterEffectFromStream or
        /// ID2D1Factory1::RegisterEffectFromString.
        /// </summary>
        void CreateEffect( REFCLSID effectId, ID2D1Effect** effect ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateEffect( effectId, effect );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        Effect CreateEffect( REFCLSID effectId ) const
        {
            ID2D1Effect* ptr = nullptr;
            CreateEffect( effectId, &ptr );
            return Effect( ptr );
        }

        /// <summary>
        /// A gradient stop collection represents a set of stops in an ideal unit length.
        /// This is the source resource for a linear gradient and radial gradient brush.
        /// </summary>
        /// <param name="preInterpolationSpace">Specifies both the input color space and the
        /// space in which the color interpolation occurs.</param>
        /// <param name="postInterpolationSpace">Specifies the color space colors will be
        /// converted to after interpolation occurs.</param>
        /// <param name="bufferPrecision">Specifies the precision in which the gradient
        /// buffer will be held.</param>
        /// <param name="extendMode">Specifies how the gradient will be extended outside of
        /// the unit length.</param>
        /// <param name="colorInterpolationMode">Determines if colors will be interpolated
        /// in straight alpha or premultiplied alpha space.</param>
        void CreateGradientStopCollection( CONST D2D1_GRADIENT_STOP* straightAlphaGradientStops,
            UINT32 straightAlphaGradientStopsCount,
            D2D1_COLOR_SPACE preInterpolationSpace,
            D2D1_COLOR_SPACE postInterpolationSpace,
            D2D1_BUFFER_PRECISION bufferPrecision,
            D2D1_EXTEND_MODE extendMode,
            D2D1_COLOR_INTERPOLATION_MODE colorInterpolationMode,
            ID2D1GradientStopCollection1** gradientStopCollection1 ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateGradientStopCollection( straightAlphaGradientStops,
                straightAlphaGradientStopsCount, preInterpolationSpace, postInterpolationSpace,
                bufferPrecision, extendMode, colorInterpolationMode, gradientStopCollection1 );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        GradientStopCollection1 CreateGradientStopCollection( CONST D2D1_GRADIENT_STOP* straightAlphaGradientStops,
            UINT32 straightAlphaGradientStopsCount,
            D2D1_COLOR_SPACE preInterpolationSpace = D2D1_COLOR_SPACE_SRGB,
            D2D1_COLOR_SPACE postInterpolationSpace = D2D1_COLOR_SPACE_SRGB,
            D2D1_BUFFER_PRECISION bufferPrecision = D2D1_BUFFER_PRECISION_8BPC_UNORM,
            D2D1_EXTEND_MODE extendMode = D2D1_EXTEND_MODE_CLAMP,
            D2D1_COLOR_INTERPOLATION_MODE colorInterpolationMode = D2D1_COLOR_INTERPOLATION_MODE_PREMULTIPLIED ) const
        {
            ID2D1GradientStopCollection1* ptr = nullptr;
            CreateGradientStopCollection( straightAlphaGradientStops,
                straightAlphaGradientStopsCount, preInterpolationSpace, postInterpolationSpace,
                bufferPrecision, extendMode, colorInterpolationMode, &ptr );
            return GradientStopCollection1( ptr );
        }


        using Base::CreateGradientStopCollection;

        /// <summary>
        /// Creates an image brush. The input image can be any type of image, 
        /// including a bitmap, effect, or a command list.
        /// </summary>
        /// <param name="image">
        /// The image to be used as a source for the image brush.
        /// </param>
        /// <param name="imageBrushProperties">
        /// The properties specific to an image brush.
        /// </param>
        /// <param name="brushProperties">
        /// Properties common to all brushes.
        /// </param>
        /// <param name="imageBrush">
        /// When this method returns, contains the address of a pointer to 
        /// the new ID2D1ImageBrush object.
        /// </param>
        void CreateImageBrush( ID2D1Image* image, const D2D1_IMAGE_BRUSH_PROPERTIES* imageBrushProperties, const D2D1_BRUSH_PROPERTIES* brushProperties, ID2D1ImageBrush** imageBrush ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateImageBrush( image, imageBrushProperties, brushProperties, imageBrush );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void CreateImageBrush( const Image& image, const D2D1_IMAGE_BRUSH_PROPERTIES* imageBrushProperties, const D2D1_BRUSH_PROPERTIES* brushProperties, ID2D1ImageBrush** imageBrush ) const
        {
            CreateImageBrush( image.GetInterfacePointer<ID2D1Image>(), imageBrushProperties, brushProperties, imageBrush );
        }
        void CreateImageBrush( ID2D1Image* image, const D2D1_IMAGE_BRUSH_PROPERTIES* imageBrushProperties, ID2D1ImageBrush** imageBrush ) const
        {
            CreateImageBrush( image, imageBrushProperties, nullptr, imageBrush );
        }
        void CreateImageBrush( const Image& image, const D2D1_IMAGE_BRUSH_PROPERTIES* imageBrushProperties, ID2D1ImageBrush** imageBrush ) const
        {
            CreateImageBrush( image.GetInterfacePointer<ID2D1Image>( ), imageBrushProperties, nullptr, imageBrush );
        }
        void CreateImageBrush( ID2D1Image* image, const D2D1_IMAGE_BRUSH_PROPERTIES& imageBrushProperties, ID2D1ImageBrush** imageBrush ) const
        {
            CreateImageBrush( image, &imageBrushProperties, nullptr, imageBrush );
        }
        void CreateImageBrush( const Image& image, const D2D1_IMAGE_BRUSH_PROPERTIES& imageBrushProperties, ID2D1ImageBrush** imageBrush ) const
        {
            CreateImageBrush( image.GetInterfacePointer<ID2D1Image>( ), &imageBrushProperties, nullptr, imageBrush );
        }
        void CreateImageBrush( ID2D1Image* image, const D2D1_IMAGE_BRUSH_PROPERTIES& imageBrushProperties, const D2D1_BRUSH_PROPERTIES& brushProperties, ID2D1ImageBrush** imageBrush ) const
        {
            CreateImageBrush( image, &imageBrushProperties, &brushProperties, imageBrush );
        }
        void CreateImageBrush( const Image& image, const D2D1_IMAGE_BRUSH_PROPERTIES& imageBrushProperties, const D2D1_BRUSH_PROPERTIES& brushProperties, ID2D1ImageBrush** imageBrush ) const
        {
            CreateImageBrush( image.GetInterfacePointer<ID2D1Image>( ), &imageBrushProperties, &brushProperties, imageBrush );
        }

        ImageBrush CreateImageBrush( ID2D1Image* image, const D2D1_IMAGE_BRUSH_PROPERTIES* imageBrushProperties, const D2D1_BRUSH_PROPERTIES* brushProperties = nullptr ) const
        {
            ID2D1ImageBrush* ptr = nullptr;
            CreateImageBrush( image, imageBrushProperties, brushProperties, &ptr );
            return ImageBrush( ptr );
        }
        ImageBrush CreateImageBrush( const Image& image, const D2D1_IMAGE_BRUSH_PROPERTIES* imageBrushProperties, const D2D1_BRUSH_PROPERTIES* brushProperties = nullptr ) const
        {
            return CreateImageBrush( image.GetInterfacePointer<ID2D1Image>( ), imageBrushProperties, brushProperties );
        }
        ImageBrush CreateImageBrush( ID2D1Image* image, const D2D1_IMAGE_BRUSH_PROPERTIES& imageBrushProperties, const D2D1_BRUSH_PROPERTIES& brushProperties ) const
        {
            return CreateImageBrush( image, &imageBrushProperties, &brushProperties );
        }
        ImageBrush CreateImageBrush( const Image& image, const D2D1_IMAGE_BRUSH_PROPERTIES& imageBrushProperties, const D2D1_BRUSH_PROPERTIES& brushProperties ) const
        {
            return CreateImageBrush( image.GetInterfacePointer<ID2D1Image>( ), &imageBrushProperties, &brushProperties );
        }
        ImageBrush CreateImageBrush( ID2D1Image* image, const D2D1_IMAGE_BRUSH_PROPERTIES& imageBrushProperties, const D2D1_BRUSH_PROPERTIES* brushProperties = nullptr ) const
        {
            return CreateImageBrush( image, &imageBrushProperties, brushProperties );
        }
        ImageBrush CreateImageBrush( const Image& image, const D2D1_IMAGE_BRUSH_PROPERTIES& imageBrushProperties, const D2D1_BRUSH_PROPERTIES* brushProperties = nullptr ) const
        {
            return CreateImageBrush( image.GetInterfacePointer<ID2D1Image>( ), &imageBrushProperties, brushProperties );
        }


        /// <summary>
        /// Creates a bitmap brush, the input image is a Direct2D bitmap object.
        /// </summary>
        /// <param name="bitmap">
        /// The bitmap to use as the brush.
        /// </param>
        /// <param name="bitmapBrushProperties">
        /// A bitmap brush properties structure.
        /// </param>
        /// <param name="brushProperties">
        /// A brush properties structure.
        /// </param>
        /// <param name="bitmapBrush">
        /// The address of the newly created bitmap brush object.
        /// </param>
        void CreateBitmapBrush( ID2D1Bitmap* bitmap, const D2D1_BITMAP_BRUSH_PROPERTIES1* bitmapBrushProperties, const D2D1_BRUSH_PROPERTIES* brushProperties, ID2D1BitmapBrush1** bitmapBrush ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateBitmapBrush( bitmap, bitmapBrushProperties, brushProperties, bitmapBrush );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        template<typename T>
            requires std::is_base_of_v<Bitmap,T>
        void CreateBitmapBrush( const T& bitmap, const D2D1_BITMAP_BRUSH_PROPERTIES1* bitmapBrushProperties, const D2D1_BRUSH_PROPERTIES* brushProperties, ID2D1BitmapBrush1** bitmapBrush ) const
        {
            using ItfT = typename T::InterfaceType;
            CreateBitmapBrush( bitmap.GetInterfacePointer<ItfT>( ), bitmapBrushProperties, brushProperties, bitmapBrush );
        }

        void CreateBitmapBrush( ID2D1Bitmap* bitmap, const D2D1_BITMAP_BRUSH_PROPERTIES1& bitmapBrushProperties, const D2D1_BRUSH_PROPERTIES& brushProperties, ID2D1BitmapBrush1** bitmapBrush ) const
        {
            CreateBitmapBrush( bitmap, &bitmapBrushProperties, &brushProperties, bitmapBrush );
        }
        template<typename T>
            requires std::is_base_of_v<Bitmap, T>
        void CreateBitmapBrush( const T& bitmap, const D2D1_BITMAP_BRUSH_PROPERTIES1& bitmapBrushProperties, const D2D1_BRUSH_PROPERTIES& brushProperties, ID2D1BitmapBrush1** bitmapBrush ) const
        {
            using ItfT = typename T::InterfaceType;
            CreateBitmapBrush( bitmap.GetInterfacePointer<ItfT>( ), &bitmapBrushProperties, &brushProperties, bitmapBrush );
        }

        void CreateBitmapBrush( ID2D1Bitmap* bitmap, const D2D1_BITMAP_BRUSH_PROPERTIES1* bitmapBrushProperties, ID2D1BitmapBrush1** bitmapBrush ) const
        {
            CreateBitmapBrush( bitmap, bitmapBrushProperties, nullptr, bitmapBrush );
        }
        template<typename T>
            requires std::is_base_of_v<Bitmap, T>
        void CreateBitmapBrush( const T& bitmap, const D2D1_BITMAP_BRUSH_PROPERTIES1* bitmapBrushProperties, ID2D1BitmapBrush1** bitmapBrush ) const
        {
            using ItfT = typename T::InterfaceType;
            CreateBitmapBrush( bitmap.GetInterfacePointer<ItfT>( ), bitmapBrushProperties, nullptr, bitmapBrush );
        }

        void CreateBitmapBrush( ID2D1Bitmap* bitmap, const D2D1_BITMAP_BRUSH_PROPERTIES1& bitmapBrushProperties, ID2D1BitmapBrush1** bitmapBrush ) const
        {
            CreateBitmapBrush( bitmap, &bitmapBrushProperties, nullptr, bitmapBrush );
        }
        template<typename T>
            requires std::is_base_of_v<Bitmap, T>
        void CreateBitmapBrush( const T& bitmap, const D2D1_BITMAP_BRUSH_PROPERTIES1& bitmapBrushProperties, ID2D1BitmapBrush1** bitmapBrush ) const
        {
            using ItfT = typename T::InterfaceType;
            CreateBitmapBrush( bitmap.GetInterfacePointer<ItfT>( ), &bitmapBrushProperties, nullptr, bitmapBrush );
        }

        void CreateBitmapBrush( ID2D1Bitmap* bitmap, ID2D1BitmapBrush1** bitmapBrush ) const
        {
            CreateBitmapBrush( bitmap, nullptr, nullptr, bitmapBrush );
        }
        template<typename T>
            requires std::is_base_of_v<Bitmap, T>
        void CreateBitmapBrush( const T& bitmap, ID2D1BitmapBrush1** bitmapBrush ) const
        {
            using ItfT = typename T::InterfaceType;
            CreateBitmapBrush( bitmap.GetInterfacePointer<ItfT>( ), nullptr, nullptr, bitmapBrush );
        }

        BitmapBrush1 CreateBitmapBrush( ID2D1Bitmap* bitmap, const D2D1_BITMAP_BRUSH_PROPERTIES1* bitmapBrushProperties = nullptr, const D2D1_BRUSH_PROPERTIES* brushProperties = nullptr ) const
        {
            ID2D1BitmapBrush1* ptr = nullptr;
            CreateBitmapBrush( bitmap, bitmapBrushProperties, brushProperties, &ptr );
            return BitmapBrush1( ptr );
        }
        template<typename T>
            requires std::is_base_of_v<Bitmap, T>
        BitmapBrush1 CreateBitmapBrush( const T& bitmap, const D2D1_BITMAP_BRUSH_PROPERTIES1* bitmapBrushProperties = nullptr, const D2D1_BRUSH_PROPERTIES* brushProperties = nullptr ) const
        {
            using ItfT = typename T::InterfaceType;
            return CreateBitmapBrush( bitmap.GetInterfacePointer<ItfT>( ), bitmapBrushProperties, brushProperties );
        }


        BitmapBrush1 CreateBitmapBrush( ID2D1Bitmap* bitmap, const D2D1_BITMAP_BRUSH_PROPERTIES1& bitmapBrushProperties, const D2D1_BRUSH_PROPERTIES& brushProperties ) const
        {
            return CreateBitmapBrush( bitmap, &bitmapBrushProperties, &brushProperties );
        }
        template<typename T>
            requires std::is_base_of_v<Bitmap, T>
        BitmapBrush1 CreateBitmapBrush( const T& bitmap, const D2D1_BITMAP_BRUSH_PROPERTIES1& bitmapBrushProperties, const D2D1_BRUSH_PROPERTIES& brushProperties ) const
        {
            using ItfT = typename T::InterfaceType;
            return CreateBitmapBrush( bitmap.GetInterfacePointer<ItfT>( ), &bitmapBrushProperties, &brushProperties );
        }

        BitmapBrush1 CreateBitmapBrush( ID2D1Bitmap* bitmap, const D2D1_BITMAP_BRUSH_PROPERTIES1& bitmapBrushProperties, const D2D1_BRUSH_PROPERTIES* brushProperties = nullptr ) const
        {
            return CreateBitmapBrush( bitmap, &bitmapBrushProperties, brushProperties );
        }
        template<typename T>
            requires std::is_base_of_v<Bitmap, T>
        BitmapBrush1 CreateBitmapBrush( const T& bitmap, const D2D1_BITMAP_BRUSH_PROPERTIES1& bitmapBrushProperties, const D2D1_BRUSH_PROPERTIES* brushProperties = nullptr ) const
        {
            using ItfT = typename T::InterfaceType;
            return CreateBitmapBrush( bitmap.GetInterfacePointer<ItfT>( ), &bitmapBrushProperties, brushProperties );
        }


        using Base::CreateBitmapBrush;

        /// <summary>
        /// Creates a new command list.
        /// </summary>
        /// <param name="commandList">
        /// When this method returns, contains the address of a pointer 
        /// to a command list.
        /// </param>
        /// <remarks>
        /// A CommandList can store Direct2D commands to be displayed later through 
        /// DeviceContext::DrawImage or through an image brush.
        /// </remarks>
        void CreateCommandList( ID2D1CommandList** commandList ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateCommandList( commandList );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        CommandList CreateCommandList( ) const
        {
            ID2D1CommandList* ptr = nullptr;
            CreateCommandList( &ptr );
            return CommandList( ptr );
        }

        /// <summary>
        /// Indicates whether the format is supported by D2D.
        /// </summary>
        bool IsDxgiFormatSupported( DXGI_FORMAT format ) const
        {
            auto* pInterface = GetInterface( );
            return pInterface->IsDxgiFormatSupported( format );
        }

        /// <summary>
        /// Indicates whether the buffer precision is supported by D2D.
        /// </summary>
        bool IsBufferPrecisionSupported( D2D1_BUFFER_PRECISION bufferPrecision ) const
        {
            auto* pInterface = GetInterface( );
            return pInterface->IsBufferPrecisionSupported( bufferPrecision );
        }

        /// <summary>
        /// Gets the bounds of an image without the world transform of 
        /// the context applied.
        /// </summary>
        /// <param name="image">
        /// The image whose bounds will be calculated.
        /// </param>
        /// <param name="localBounds">
        /// When this method returns, contains a pointer to the bounds of 
        /// the image in device independent pixels (DIPs) and in local space.
        /// </param>
        /// <remarks>
        /// <p>
        /// The image bounds don't include multiplication by the world transform. 
        /// They do reflect the current DPI, unit mode, and interpolation mode of 
        /// the context. To get the bounds that include the world transform, use 
        /// DeviceContext::GetImageWorldBounds.
        /// </p>
        /// <p>
        /// The returned bounds reflect which pixels would be impacted by calling 
        /// DrawImage with a target offset of (0,0) and an identity world transform 
        /// matrix. They do not reflect the current clip rectangle set on the device 
        /// context or the extent of the context's current target image.
        /// </p>
        /// </remarks>
        void GetImageLocalBounds( ID2D1Image* image, D2D1_RECT_F* localBounds ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetImageLocalBounds( image, localBounds );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void GetImageLocalBounds( const Image& image, D2D1_RECT_F* localBounds ) const
        {
            GetImageLocalBounds( image.GetInterfacePointer<ID2D1Image>( ), localBounds );
        }

        void GetImageLocalBounds( ID2D1Image* image, D2D1_RECT_F& localBounds ) const
        {
            GetImageLocalBounds( image, &localBounds );
        }
        void GetImageLocalBounds( const Image& image, D2D1_RECT_F& localBounds ) const
        {
            GetImageLocalBounds( image.GetInterfacePointer<ID2D1Image>( ), &localBounds );
        }

        /// <summary>
        /// Gets the bounds of an image with the world transform of the context applied.
        /// </summary>
        /// <param name="image">
        /// The image whose bounds will be calculated.
        /// </param>
        /// <param name="worldBounds">
        /// When this method returns, contains a pointer to the bounds of the image in 
        /// device independent pixels (DIPs).
        /// </param>
        /// <remarks>
        /// <p>
        /// The image bounds reflect the current DPI, unit mode, and world transform of 
        /// the context. To get bounds which don't include the world transform, use 
        /// DeviceContext::GetImageLocalBounds.
        /// </p>
        /// <p>
        /// The returned bounds reflect which pixels would be impacted by calling 
        /// DrawImage with the same image and a target offset of (0,0). They do not 
        /// reflect the current clip rectangle set on the device context or the extent 
        /// of the context’s current target image.
        /// </p>
        /// </remarks>
        void GetImageWorldBounds( ID2D1Image* image, D2D1_RECT_F* worldBounds ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetImageWorldBounds( image, worldBounds );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void GetImageWorldBounds( const Image& image, D2D1_RECT_F* worldBounds ) const
        {
            GetImageWorldBounds( image.GetInterfacePointer<ID2D1Image>( ), worldBounds );
        }
        void GetImageWorldBounds( ID2D1Image* image, D2D1_RECT_F& worldBounds ) const
        {
            GetImageWorldBounds( image, &worldBounds );
        }
        void GetImageWorldBounds( const Image& image, D2D1_RECT_F& worldBounds ) const
        {
            GetImageWorldBounds( image.GetInterfacePointer<ID2D1Image>( ), &worldBounds );
        }

        /// <summary>
        /// Gets the world-space bounds in DIPs of the glyph run using the device 
        /// context DPI.
        /// </summary>
        /// <param name="baselineOrigin">
        /// The origin of the baseline for the glyph run.
        /// </param>
        /// <param name="glyphRun">
        /// The glyph run to render.
        /// </param>
        /// <param name="measuringMode">
        /// The DirectWrite measuring mode that indicates how glyph metrics are 
        /// used to measure text when it is formatted.
        /// </param>
        /// <param name="bounds">
        /// The bounds of the glyph run in DIPs and in world space.
        /// </param>
        /// <remarks>
        /// The bounds reflect the current DPI, unit mode, and world transform of the context.
        /// </remarks>
        void GetGlyphRunWorldBounds( const D2D1_POINT_2F& baselineOrigin, const DWRITE_GLYPH_RUN* glyphRun, DWRITE_MEASURING_MODE measuringMode, D2D1_RECT_F* bounds ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetGlyphRunWorldBounds( baselineOrigin, glyphRun, measuringMode, bounds );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void GetGlyphRunWorldBounds( const D2D1_POINT_2F& baselineOrigin, const DWRITE_GLYPH_RUN& glyphRun, DWRITE_MEASURING_MODE measuringMode, D2D1_RECT_F& bounds ) const
        {
            GetGlyphRunWorldBounds( baselineOrigin, &glyphRun, measuringMode, &bounds );
        }


        /// <summary>
        /// Retrieves the device associated with this device context.
        /// </summary>
        /// <param name="device">
        /// When this method returns, contains the address of a pointer to 
        /// a Direct2D device associated with this device context.
        /// </param>
        /// <remarks>
        /// The application can retrieve the device even if it is created from an earlier 
        /// render target code-path. The application must use an ID2D1DeviceContext 
        /// interface and then call GetDevice. Some functionality for controlling all of 
        /// the resources for a set of device contexts is maintained only on an 
        /// ID2D1Device object.
        /// </remarks>
        void GetDevice( _Outptr_ ID2D1Device** device ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->GetDevice( device );
        }
        inline Device GetDevice( ) const;

        /// <summary>
        /// The bitmap or command list to which the Direct2D device context will now render.
        /// </summary>
        /// <param name="image">
        /// The surface or command list to which the Direct2D device context will render.
        /// </param>
        /// <remarks>
        /// <p>
        /// The target can be changed at any time, including while the context is drawing.
        /// </p>
        /// <p>
        /// The target can be either a bitmap created with the D2D1_BITMAP_OPTIONS_TARGET 
        /// flag, or it can be a command list. Other kinds of images cannot be set as a 
        /// target. For example, you cannot set the output of an effect as target. If the 
        /// target is not valid the context will enter the D2DERR_INVALID_TARGET error state.
        /// </p>
        /// <p>
        /// You cannot use SetTarget to render to a bitmap/command list from multiple device 
        /// contexts simultaneously. An image is considered “being rendered to” if it has 
        /// ever been set on a device context within a BeginDraw/EndDraw timespan. If an 
        /// attempt is made to render to an image through multiple device contexts, all 
        /// subsequent device contexts after the first will enter an error state.
        /// </p>
        /// <p>
        /// Callers wishing to attach an image to a second device context should first call 
        /// EndDraw on the first device context.
        /// </p>
        /// <p>
        /// Changing the target does not change the bitmap that an HWND render target presents 
        /// from, nor does it change the bitmap that a DC render target blts to/from.
        /// </p>
        /// <p>
        /// This API makes it easy for an application to use a bitmap as a source (like in 
        /// DrawBitmap) and as a destination at the same time. Attempting to use a bitmap as a 
        /// source on the same device context to which it is bound as a target will put the 
        /// device context into the D2DERR_BITMAP_BOUND_AS_TARGET error state.
        /// </p>
        /// <p>
        /// It is acceptable to have a bitmap bound as a target bitmap on multiple render 
        /// targets at once. Applications that do this must properly synchronize rendering 
        /// with Flush or EndDraw.
        /// </p>
        /// <p>
        /// You can change the target at any time, including while the context is drawing.
        /// </p>
        /// <p>
        /// You can set the target to NULL, in which case drawing calls will put the device 
        /// context into an error state with D2DERR_WRONG_STATE. Calling SetTarget with a 
        /// NULL target does not restore the original target bitmap to the device context.
        /// </p>
        /// <p>
        /// If the device context has an outstanding HDC, the context will enter the 
        /// D2DERR_WRONG_STATE error state. The target will not be changed.
        /// </p>
        /// <p>
        /// If the bitmap and the device context are not in the same resource domain, 
        /// the context will enter \ error state. The target will not be changed.
        /// </p>
        /// <p>
        /// RenderTarget::GetPixelSize returns the size of the current target bitmap 
        /// (or 0, 0) if there is no bitmap bound). ID2D1RenderTarget::GetSize returns the 
        /// pixel size of the current bitmap scaled by the DPI of the render target. 
        /// SetTarget does not affect the DPI of the render target.
        /// </p>
        /// <p>
        /// RenderTarget::GetPixelFormat returns the pixel format of the current target 
        /// bitmap (or DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_UNKNOWN if there is none).
        /// </p>
        /// <p>
        /// Bitmap::CopyFromRenderTarget copies from the currently bound target bitmap.
        /// </p>
        /// </remarks>
        void SetTarget( ID2D1Image* image ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->SetTarget( image );
        }
        void SetTarget( const Image& image ) const
        {
            SetTarget( image.GetInterfacePointer<ID2D1Image>( ) );
        }

        /// <summary>
        /// Gets the target currently associated with the device context.
        /// </summary>
        /// <param name="image">
        /// When this method returns, contains the address of a pointer to the target 
        /// currently associated with the device context.
        /// </param>
        /// <remarks>
        /// <p>
        /// If a target is not associated with the device context, target will contain 
        /// NULL when the methods returns.
        /// </p>
        /// <p>
        /// If the currently selected target is a bitmap rather than a command list, 
        /// the application can gain access to the initial bitmaps created by using 
        /// one of the following methods:
        /// </p>
        /// <ul>
        ///   <li>CreateHwndRenderTarget</li>
        ///   <li>CreateDxgiSurfaceRenderTarget</li>
        ///   <li>CreateWicBitmapRenderTarget</li>
        ///   <li>CreateDCRenderTarget</li>
        ///   <li>CreateCompatibleRenderTarget</li>
        /// </ul>
        /// <p>
        /// It is not possible for an application to destroy these bitmaps. All of these 
        /// bitmaps are bindable as bitmap targets. However not all of these bitmaps can 
        /// be used as bitmap sources for RenderTarget functions.
        /// </p>
        /// <p>
        /// CreateDxgiSurfaceRenderTarget will create a bitmap that is usable as a bitmap 
        /// source if the DXGI surface is bindable as a shader resource view.
        /// </p>
        /// <p>
        /// CreateCompatibleRenderTarget will always create bitmaps that are usable as a 
        /// bitmap source.
        /// </p>
        /// <p>
        /// RenderTarget::BeginDraw will copy from the HDC to the original bitmap associated 
        /// with it. RenderTarget::EndDraw will copy from the original bitmap to the HDC.
        /// </p>
        /// <p>
        /// IWICBitmap objects will be locked in the following circumstances:
        /// </p>
        /// <ul>
        ///     <li>
        ///         BeginDraw has been called and the currently selected target bitmap 
        ///         is a WIC bitmap.    
        ///     </li>
        ///     <li>
        ///         A WIC bitmap is set as the target of a device context after BeginDraw 
        ///         has been called and before EndDraw has been called.
        ///     </li>
        ///     <li>
        ///         Any of the ID2D1Bitmap::Copy* methods are called with a WIC bitmap as 
        ///         either the source or destination.
        ///     </li>
        /// </ul>
        /// <p>
        /// IWICBitmap objects will be unlocked in the following circumstances:
        /// </p>
        /// <ul>
        ///     <li>
        ///         EndDraw is called and the currently selected target bitmap is a WIC 
        ///         bitmap.
        ///     </li>
        ///     <li>
        ///         A WIC bitmap is removed as the target of a device context between the 
        ///         calls to BeginDraw and EndDraw.
        ///     </li>
        ///     <li>
        ///         Any of the ID2D1Bitmap::Copy* methods are called with a WIC bitmap as 
        ///         either the source or destination.
        ///     </li>
        /// </ul>
        /// <p>
        /// Direct2D will only lock bitmaps that are not currently locked.
        /// </p>
        /// <p>
        /// Calling QueryInterface for GdiInteropRenderTarget will always succeed. 
        /// GdiInteropRenderTarget::GetDC will return a device context corresponding to the 
        /// currently bound target bitmap. GetDC will fail if the target bitmap was not 
        /// created with the GDI_COMPATIBLE flag set.
        /// </p>
        /// <p>
        /// ControlRenderTarget::Resize will throw a Harlinn::Common::Core::Exception for 
        /// DXGI_ERROR_INVALID_CALL if there are any outstanding references to the original 
        /// target bitmap associated with the render target.
        /// </p>
        /// <p>
        /// Although the target can be a command list, it cannot be any other type of image. 
        /// It cannot be the output image of an effect.
        /// </p>
        /// </remarks>
        void GetTarget( ID2D1Image** image ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->GetTarget( image );
        }
        Image GetTarget( ) const
        {
            ID2D1Image* ptr = nullptr;
            GetTarget( &ptr );
            return Image( ptr );
        }


        /// <summary>
        /// Sets tuning parameters for internal rendering inside the device context.
        /// </summary>
        /// <param name="renderingControls">
        /// The rendering controls to be applied.
        /// </param>
        /// <remarks>
        /// The rendering controls allow the application to tune the precision, 
        /// performance, and resource usage of rendering operations.
        /// </remarks>
        void SetRenderingControls( const D2D1_RENDERING_CONTROLS* renderingControls ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->SetRenderingControls( renderingControls );
        }
        void SetRenderingControls( const D2D1_RENDERING_CONTROLS& renderingControls ) const
        {
            SetRenderingControls( &renderingControls );
        }

        /// <summary>
        /// Gets the rendering controls that have been applied to the context.
        /// </summary>
        /// <param name="renderingControls">
        /// When this method returns, contains a pointer to the rendering controls 
        /// for this context.
        /// </param>
        void GetRenderingControls( D2D1_RENDERING_CONTROLS* renderingControls ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->GetRenderingControls( renderingControls );
        }
        void GetRenderingControls( D2D1_RENDERING_CONTROLS& renderingControls ) const
        {
            GetRenderingControls( &renderingControls );
        }

        /// <summary>
        /// Changes the primitive blending mode for all of the rendering operations.
        /// </summary>
        /// <param name="primitiveBlend">
        /// The primitive blend to use.
        /// </param>
        /// <remarks>
        /// <p>
        /// The primitive blend will apply to all of the primitive drawn on the context, 
        /// unless this is overridden with the compositeMode parameter on the DrawImage API.
        /// </p>
        /// <p>
        /// The primitive blend applies to the interior of any primitives drawn on the context. 
        /// In the case of DrawImage, this will be implied by the image rectangle, offset and 
        /// world transform.
        /// </p>
        /// <p>
        /// If the primitive blend is anything other than D2D1_PRIMITIVE_BLEND_SOURCE_OVER then 
        /// ClearType rendering will be turned off. If the application explicitly forces 
        /// ClearType rendering in these modes, the drawing context will be placed in an 
        /// error state. A Harlinn::Common::Core::Exception for D2DERR_WRONG_STATE will be 
        /// thrown from either EndDraw or Flush.
        /// </p>
        /// </remarks>
        void SetPrimitiveBlend( D2D1_PRIMITIVE_BLEND primitiveBlend = D2D1_PRIMITIVE_BLEND_SOURCE_OVER ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->SetPrimitiveBlend( primitiveBlend );
        }

        /// <summary>
        /// Returns the primitive blend currently selected into the device context.
        /// </summary>
        /// <returns>
        /// The current primitive blend. The default value is D2D1_PRIMITIVE_BLEND_SOURCE_OVER.
        /// </returns>
        D2D1_PRIMITIVE_BLEND GetPrimitiveBlend( ) const
        {
            auto* pInterface = GetInterface( );
            return pInterface->GetPrimitiveBlend( );
        }

        /// <summary>
        /// Sets what units will be used to interpret values passed into the 
        /// device context.
        /// </summary>
        /// <param name="unitMode">
        /// A value from the enumeration defining how passed-in units will be 
        /// interpreted by the device context.
        /// </param>
        /// <remarks>
        /// This method will affect all properties and parameters affected by 
        /// SetDpi and GetDpi. This affects all coordinates, lengths, and other 
        /// properties that are not explicitly defined as being in another unit. 
        /// For example:
        /// <ul>
        ///     <li>
        ///         <strong>SetUnitMode</strong> will affect a coordinate passed 
        ///         into DeviceContext::DrawLine, and the scaling of a geometry 
        ///         passed into DeviceContext::FillGeometry.
        ///     <li>
        ///     <li>
        ///         <strong>SetUnitMode</strong> will not affect the value returned 
        ///         by ID2D1Bitmap::GetPixelSize.
        ///     <li>
        /// </ul>
        /// </remarks>
        void SetUnitMode( D2D1_UNIT_MODE unitMode ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->SetUnitMode( unitMode );
        }

        /// <summary>
        /// Returns the unit mode currently set on the device context.
        /// </summary>
        /// <returns>
        /// The unit mode.
        /// </returns> 
        D2D1_UNIT_MODE GetUnitMode( ) const
        {
            auto* pInterface = GetInterface( );
            return pInterface->GetUnitMode( );
        }

        /// <summary>
        /// Draws the glyph run with an extended description to describe the glyphs.
        /// </summary>
        /// <param name="baselineOrigin">
        /// Origin of first glyph in the series.
        /// </param>
        /// <param name="glyphRun">
        /// The glyphs to render. 
        /// </param>
        /// <param name="glyphRunDescription">
        /// Supplementary glyph series information.
        /// </param>
        /// <param name="foregroundBrush">
        /// The brush that defines the text color.
        /// </param>
        /// <param name="measuringMode">
        /// The measuring mode of the glyph series, used to determine the advances and 
        /// offsets. The default value is DWRITE_MEASURING_MODE_NATURAL. 
        /// </param>
        /// <remarks>
        /// The glyphRunDescription is ignored when rendering, but can be useful for 
        /// printing and serialization of rendering commands, such as to an XPS or SVG 
        /// file. This extends RenderTarget::DrawGlyphRun, which lacked the glyph run 
        /// description.
        /// </remarks>
        void DrawGlyphRun( const D2D1_POINT_2F& baselineOrigin, const DWRITE_GLYPH_RUN* glyphRun, const DWRITE_GLYPH_RUN_DESCRIPTION* glyphRunDescription,
            ID2D1Brush* foregroundBrush, DWRITE_MEASURING_MODE measuringMode = DWRITE_MEASURING_MODE_NATURAL ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->DrawGlyphRun( baselineOrigin, glyphRun, glyphRunDescription, foregroundBrush, measuringMode );
        }
        void DrawGlyphRun( const D2D1_POINT_2F& baselineOrigin, const DWRITE_GLYPH_RUN* glyphRun, const DWRITE_GLYPH_RUN_DESCRIPTION* glyphRunDescription,
            const Brush& foregroundBrush, DWRITE_MEASURING_MODE measuringMode = DWRITE_MEASURING_MODE_NATURAL ) const
        {
            DrawGlyphRun( baselineOrigin, glyphRun, glyphRunDescription, foregroundBrush.GetInterfacePointer<ID2D1Brush>( ), measuringMode );
        }

        void DrawGlyphRun( const D2D1_POINT_2F& baselineOrigin, const DWRITE_GLYPH_RUN& glyphRun, const DWRITE_GLYPH_RUN_DESCRIPTION& glyphRunDescription,
            ID2D1Brush* foregroundBrush, DWRITE_MEASURING_MODE measuringMode = DWRITE_MEASURING_MODE_NATURAL ) const
        {
            DrawGlyphRun( baselineOrigin, &glyphRun, &glyphRunDescription, foregroundBrush, measuringMode );
        }
        void DrawGlyphRun( const D2D1_POINT_2F& baselineOrigin, const DWRITE_GLYPH_RUN& glyphRun, const DWRITE_GLYPH_RUN_DESCRIPTION& glyphRunDescription,
            const Brush& foregroundBrush, DWRITE_MEASURING_MODE measuringMode = DWRITE_MEASURING_MODE_NATURAL ) const
        {
            DrawGlyphRun( baselineOrigin, &glyphRun, &glyphRunDescription, foregroundBrush.GetInterfacePointer<ID2D1Brush>( ), measuringMode );
        }


        using Base::DrawGlyphRun;

        /// <summary>
        /// Draw an image to the device context. The image represents either a concrete
        /// bitmap or the output of an effect graph.
        /// </summary>
        /// <param name="image">
        /// The image to be drawn to the device context.
        /// </param>
        /// <param name="targetOffset">
        /// The offset in the destination space that the image will be rendered to. The 
        /// entire logical extent of the image will be rendered to the corresponding 
        /// destination. If not specified, the destination origin will be (0, 0). The 
        /// top-left corner of the image will be mapped to the target offset. This will 
        /// not necessarily be the origin. This default value is nullptr.
        /// </param>
        /// <param name="imageRectangle">
        /// The corresponding rectangle in the image space will be mapped to the given 
        /// origins when processing the image. This default value is NULL.
        /// </param>
        /// <param name="interpolationMode">
        /// The interpolation mode that will be used to scale the image if necessary.
        /// </param>
        /// <param name="compositeMode">
        /// The composite mode that will be applied to the limits of the currently 
        /// selected clip. The default value is D2D1_COMPOSITE_MODE_SOURCE_OVER
        /// </param>
        void DrawImage( ID2D1Image* image,
            const D2D1_POINT_2F* targetOffset = nullptr,
            const D2D1_RECT_F* imageRectangle = nullptr,
            D2D1_INTERPOLATION_MODE interpolationMode = D2D1_INTERPOLATION_MODE_LINEAR,
            D2D1_COMPOSITE_MODE compositeMode = D2D1_COMPOSITE_MODE_SOURCE_OVER ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->DrawImage( image, targetOffset, imageRectangle, interpolationMode, compositeMode );
        }

        void DrawImage( const Image& image,
            const D2D1_POINT_2F* targetOffset = nullptr,
            const D2D1_RECT_F* imageRectangle = nullptr,
            D2D1_INTERPOLATION_MODE interpolationMode = D2D1_INTERPOLATION_MODE_LINEAR,
            D2D1_COMPOSITE_MODE compositeMode = D2D1_COMPOSITE_MODE_SOURCE_OVER ) const
        {
            DrawImage( image.GetInterfacePointer<ID2D1Image>( ), targetOffset, imageRectangle, interpolationMode, compositeMode );
        }

        void DrawImage( ID2D1Effect* effect,
            const D2D1_POINT_2F* targetOffset = nullptr,
            const D2D1_RECT_F* imageRectangle = nullptr,
            D2D1_INTERPOLATION_MODE interpolationMode = D2D1_INTERPOLATION_MODE_LINEAR,
            D2D1_COMPOSITE_MODE compositeMode = D2D1_COMPOSITE_MODE_SOURCE_OVER ) const
        {
            ID2D1Image* output = nullptr;
            effect->GetOutput( &output );
            auto pInterface = GetInterface( );
            pInterface->DrawImage( output, targetOffset, imageRectangle, interpolationMode, compositeMode );
            output->Release( );
        }
        void DrawImage( const Effect& effect,
            const D2D1_POINT_2F* targetOffset = nullptr,
            const D2D1_RECT_F* imageRectangle = nullptr,
            D2D1_INTERPOLATION_MODE interpolationMode = D2D1_INTERPOLATION_MODE_LINEAR,
            D2D1_COMPOSITE_MODE compositeMode = D2D1_COMPOSITE_MODE_SOURCE_OVER ) const
        {
            DrawImage( effect.GetInterfacePointer<ID2D1Effect>( ), targetOffset, imageRectangle, interpolationMode, compositeMode );
        }

        void DrawImage( ID2D1Image* image, D2D1_INTERPOLATION_MODE interpolationMode, D2D1_COMPOSITE_MODE compositeMode = D2D1_COMPOSITE_MODE_SOURCE_OVER )
        {
            DrawImage( image, nullptr, nullptr, interpolationMode, compositeMode );
        }
        void DrawImage( const Image& image, D2D1_INTERPOLATION_MODE interpolationMode, D2D1_COMPOSITE_MODE compositeMode = D2D1_COMPOSITE_MODE_SOURCE_OVER )
        {
            DrawImage( image, nullptr, nullptr, interpolationMode, compositeMode );
        }

        void DrawImage( ID2D1Effect* effect, D2D1_INTERPOLATION_MODE interpolationMode,
            D2D1_COMPOSITE_MODE compositeMode = D2D1_COMPOSITE_MODE_SOURCE_OVER ) const
        {
            DrawImage( effect, nullptr, nullptr, interpolationMode, compositeMode );
        }
        void DrawImage( const Effect& effect, D2D1_INTERPOLATION_MODE interpolationMode,
            D2D1_COMPOSITE_MODE compositeMode = D2D1_COMPOSITE_MODE_SOURCE_OVER ) const
        {
            DrawImage( effect, nullptr, nullptr, interpolationMode, compositeMode );
        }

        void DrawImage( ID2D1Image* image, const D2D1_POINT_2F& targetOffset,
            D2D1_INTERPOLATION_MODE interpolationMode = D2D1_INTERPOLATION_MODE_LINEAR,
            D2D1_COMPOSITE_MODE compositeMode = D2D1_COMPOSITE_MODE_SOURCE_OVER ) const
        {
            DrawImage( image, &targetOffset, nullptr, interpolationMode, compositeMode );
        }
        void DrawImage( const Image& image, const D2D1_POINT_2F& targetOffset,
            D2D1_INTERPOLATION_MODE interpolationMode = D2D1_INTERPOLATION_MODE_LINEAR,
            D2D1_COMPOSITE_MODE compositeMode = D2D1_COMPOSITE_MODE_SOURCE_OVER ) const
        {
            DrawImage( image, &targetOffset, nullptr, interpolationMode, compositeMode );
        }

        void DrawImage( ID2D1Effect* effect, const D2D1_POINT_2F& targetOffset,
            D2D1_INTERPOLATION_MODE interpolationMode = D2D1_INTERPOLATION_MODE_LINEAR,
            D2D1_COMPOSITE_MODE compositeMode = D2D1_COMPOSITE_MODE_SOURCE_OVER ) const
        {
            DrawImage( effect, &targetOffset, nullptr, interpolationMode, compositeMode );
        }
        void DrawImage( const Effect& effect, const D2D1_POINT_2F& targetOffset,
            D2D1_INTERPOLATION_MODE interpolationMode = D2D1_INTERPOLATION_MODE_LINEAR,
            D2D1_COMPOSITE_MODE compositeMode = D2D1_COMPOSITE_MODE_SOURCE_OVER ) const
        {
            DrawImage( effect, &targetOffset, nullptr, interpolationMode, compositeMode );
        }

        void DrawImage( ID2D1Image* image, const D2D1_POINT_2F& targetOffset, const D2D1_RECT_F& imageRectangle, D2D1_INTERPOLATION_MODE interpolationMode = D2D1_INTERPOLATION_MODE_LINEAR, D2D1_COMPOSITE_MODE compositeMode = D2D1_COMPOSITE_MODE_SOURCE_OVER ) const
        {
            DrawImage( image, &targetOffset, &imageRectangle, interpolationMode, compositeMode );
        }
        void DrawImage( const Image& image, const D2D1_POINT_2F& targetOffset, const D2D1_RECT_F& imageRectangle, D2D1_INTERPOLATION_MODE interpolationMode = D2D1_INTERPOLATION_MODE_LINEAR, D2D1_COMPOSITE_MODE compositeMode = D2D1_COMPOSITE_MODE_SOURCE_OVER ) const
        {
            DrawImage( image, &targetOffset, &imageRectangle, interpolationMode, compositeMode );
        }

        void DrawImage( ID2D1Effect* effect, const D2D1_POINT_2F& targetOffset, const D2D1_RECT_F& imageRectangle, D2D1_INTERPOLATION_MODE interpolationMode = D2D1_INTERPOLATION_MODE_LINEAR, D2D1_COMPOSITE_MODE compositeMode = D2D1_COMPOSITE_MODE_SOURCE_OVER ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->DrawImage( effect, &targetOffset, &imageRectangle, interpolationMode, compositeMode );
        }
        void DrawImage( const Effect& effect, const D2D1_POINT_2F& targetOffset, const D2D1_RECT_F& imageRectangle, D2D1_INTERPOLATION_MODE interpolationMode = D2D1_INTERPOLATION_MODE_LINEAR, D2D1_COMPOSITE_MODE compositeMode = D2D1_COMPOSITE_MODE_SOURCE_OVER ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->DrawImage( effect, &targetOffset, &imageRectangle, interpolationMode, compositeMode );
        }


        /// <summary>
        /// Draw a metafile to the device context.
        /// </summary>
        /// <param name="gdiMetafile">
        /// The metafile to draw.
        /// </param>
        /// <param name="targetOffset">
        /// The offset from the upper left corner of the render target.
        /// </param>
        void DrawGdiMetafile( ID2D1GdiMetafile* gdiMetafile, const D2D1_POINT_2F* targetOffset = nullptr ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->DrawGdiMetafile( gdiMetafile, targetOffset );
        }
        void DrawGdiMetafile( const GdiMetafile& gdiMetafile, const D2D1_POINT_2F* targetOffset = nullptr ) const
        {
            DrawGdiMetafile( gdiMetafile.GetInterfacePointer<ID2D1GdiMetafile>( ), targetOffset );
        }
        void DrawGdiMetafile( ID2D1GdiMetafile* gdiMetafile, const D2D1_POINT_2F& targetOffset ) const
        {
            DrawGdiMetafile( gdiMetafile, &targetOffset );
        }
        void DrawGdiMetafile( const GdiMetafile& gdiMetafile, const D2D1_POINT_2F& targetOffset ) const
        {
            DrawGdiMetafile( gdiMetafile.GetInterfacePointer<ID2D1GdiMetafile>( ), targetOffset );
        }


        /// <summary>
        /// Draws a bitmap to the render target.
        /// </summary>
        /// <param name="bitmap">
        /// The bitmap to draw.
        /// </param>
        /// <param name="destinationRectangle">
        /// The destination rectangle. The default is the size of the bitmap and the location is 
        /// the upper left corner of the render target.
        /// </param>
        /// <param name="opacity">
        /// The opacity of the bitmap.
        /// </param>
        /// <param name="interpolationMode">
        /// The interpolation mode to use.
        /// </param>
        /// <param name="sourceRectangle">
        /// An optional source rectangle.
        /// </param>
        /// <param name="perspectiveTransform">
        /// An optional perspective transform.
        /// </param>
        /// <remarks>
        /// <p>
        /// The destinationRectangle parameter defines the rectangle in the target where the 
        /// bitmap will appear (in device-independent pixels (DIPs)). This is affected by the 
        /// currently set transform and the perspective transform, if set. If NULL is specified, 
        /// then the destination rectangle is (left=0, top=0, right = width(sourceRectangle), 
        /// bottom = height(sourceRectangle)).
        /// </p>
        /// <p>
        /// The sourceRectangle parameter defines the sub-rectangle of the source bitmap (in DIPs). 
        /// DrawBitmap will clip this rectangle to the size of the source bitmap, thus making it 
        /// impossible to sample outside of the bitmap. If NULL is specified, then the source 
        /// rectangle is taken to be the size of the source bitmap.
        /// </p>
        /// <p>
        /// If you specify perspectiveTransform it is applied to the rect in addition to the 
        /// transform set on the render target.
        /// </p>
        /// </remarks>
        void DrawBitmap( ID2D1Bitmap* bitmap, const D2D1_RECT_F* destinationRectangle,
            FLOAT opacity, D2D1_INTERPOLATION_MODE interpolationMode = D2D1_INTERPOLATION_MODE_LINEAR,
            const D2D1_RECT_F* sourceRectangle = nullptr,
            const D2D1_MATRIX_4X4_F* perspectiveTransform = nullptr ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->DrawBitmap( bitmap, destinationRectangle, opacity, interpolationMode, sourceRectangle, perspectiveTransform );
        }

        void DrawBitmap( const Bitmap& bitmap, const D2D1_RECT_F* destinationRectangle,
            FLOAT opacity, D2D1_INTERPOLATION_MODE interpolationMode = D2D1_INTERPOLATION_MODE_LINEAR,
            const D2D1_RECT_F* sourceRectangle = nullptr,
            const D2D1_MATRIX_4X4_F* perspectiveTransform = nullptr ) const
        {
            DrawBitmap( bitmap.GetInterfacePointer<ID2D1Bitmap>( ), destinationRectangle, opacity, interpolationMode, sourceRectangle, perspectiveTransform );
        }

        void DrawBitmap( ID2D1Bitmap* bitmap, const D2D1_RECT_F& destinationRectangle, FLOAT opacity,
            D2D1_INTERPOLATION_MODE interpolationMode = D2D1_INTERPOLATION_MODE_LINEAR, const D2D1_RECT_F* sourceRectangle = nullptr, const D2D1_MATRIX_4X4_F* perspectiveTransform = nullptr ) const
        {
            DrawBitmap( bitmap, &destinationRectangle, opacity, interpolationMode, sourceRectangle, perspectiveTransform );
        }
        void DrawBitmap( const Bitmap& bitmap, const D2D1_RECT_F& destinationRectangle, FLOAT opacity,
            D2D1_INTERPOLATION_MODE interpolationMode = D2D1_INTERPOLATION_MODE_LINEAR, const D2D1_RECT_F* sourceRectangle = nullptr, const D2D1_MATRIX_4X4_F* perspectiveTransform = nullptr ) const
        {
            DrawBitmap( bitmap.GetInterfacePointer<ID2D1Bitmap>( ), &destinationRectangle, opacity, interpolationMode, sourceRectangle, perspectiveTransform );
        }

        void DrawBitmap( ID2D1Bitmap* bitmap, const D2D1_RECT_F& destinationRectangle, FLOAT opacity,
            D2D1_INTERPOLATION_MODE interpolationMode, const D2D1_RECT_F& sourceRectangle,
            const D2D1_MATRIX_4X4_F* perspectiveTransform = nullptr ) const
        {
            DrawBitmap( bitmap, &destinationRectangle, opacity, interpolationMode, &sourceRectangle, perspectiveTransform );
        }
        void DrawBitmap( const Bitmap& bitmap, const D2D1_RECT_F& destinationRectangle, FLOAT opacity,
            D2D1_INTERPOLATION_MODE interpolationMode, const D2D1_RECT_F& sourceRectangle,
            const D2D1_MATRIX_4X4_F* perspectiveTransform = nullptr ) const
        {
            DrawBitmap( bitmap.GetInterfacePointer<ID2D1Bitmap>( ), &destinationRectangle, opacity, interpolationMode, &sourceRectangle, perspectiveTransform );
        }

        void DrawBitmap( ID2D1Bitmap* bitmap, const D2D1_RECT_F& destinationRectangle, FLOAT opacity, D2D1_INTERPOLATION_MODE interpolationMode, const D2D1_RECT_F& sourceRectangle, const D2D1_MATRIX_4X4_F& perspectiveTransform ) const
        {
            DrawBitmap( bitmap, &destinationRectangle, opacity, interpolationMode, &sourceRectangle, &perspectiveTransform );
        }
        void DrawBitmap( const Bitmap& bitmap, const D2D1_RECT_F& destinationRectangle, FLOAT opacity, D2D1_INTERPOLATION_MODE interpolationMode, const D2D1_RECT_F& sourceRectangle, const D2D1_MATRIX_4X4_F& perspectiveTransform ) const
        {
            DrawBitmap( bitmap.GetInterfacePointer<ID2D1Bitmap>( ), &destinationRectangle, opacity, interpolationMode, &sourceRectangle, &perspectiveTransform );
        }

        using Base::DrawBitmap;

        /// <summary>
        /// Push a layer onto the clip and layer stack of the device context.
        /// </summary>
        /// <param name="layerParameters">
        /// The parameters that defines the layer.
        /// </param>
        /// <param name="layer">
        /// <p>
        /// The layer resource to push on the device context that receives subsequent drawing operations.
        /// </p>
        /// <p>
        /// If a layer is not specified, Direct2D manages the layer resource automatically.
        /// </p>
        /// </param>
        void PushLayer( const D2D1_LAYER_PARAMETERS1* layerParameters, ID2D1Layer* layer = nullptr ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->PushLayer( layerParameters, layer );
        }
        void PushLayer( const D2D1_LAYER_PARAMETERS1* layerParameters, const Layer& layer ) const
        {
            PushLayer( layerParameters, layer.GetInterfacePointer<ID2D1Layer>( ) );
        }

        void PushLayer( const D2D1_LAYER_PARAMETERS1& layerParameters, ID2D1Layer* layer = nullptr ) const
        {
            PushLayer( &layerParameters, layer );
        }
        void PushLayer( const D2D1_LAYER_PARAMETERS1& layerParameters, const Layer& layer ) const
        {
            PushLayer( &layerParameters, layer.GetInterfacePointer<ID2D1Layer>( ) );
        }

        using Base::PushLayer;

        /// <summary>
        /// <p>
        /// This indicates that a portion of an effect's input is invalid. 
        /// This method can be called many times.
        /// </p>
        /// <p>
        /// You can use this method to propagate invalid rectangles through an 
        /// effect graph. You can query Direct2D using the GetEffectInvalidRectangles method.
        /// </p>
        /// <p>
        /// Direct2D does not automatically use these invalid rectangles to reduce the region 
        /// of an effect that is rendered.
        /// </p>
        /// <p>
        /// You can also use this method to invalidate caches that have accumulated while 
        /// rendering effects that have the D2D1_PROPERTY_CACHED property set to true.
        /// </p>
        /// </summary>
        /// <param name="effect">
        /// The effect to invalidate.
        /// </param>
        /// <param name="input">
        /// The input index.
        /// </param>
        /// <param name="inputRectangle">
        /// The rect to invalidate.
        /// </param>
        void InvalidateEffectInputRectangle( ID2D1Effect* effect, UINT32 input, const D2D1_RECT_F* inputRectangle ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->InvalidateEffectInputRectangle( effect, input, inputRectangle );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void InvalidateEffectInputRectangle( ID2D1Effect* effect, UINT32 input, const D2D1_RECT_F& inputRectangle ) const
        {
            InvalidateEffectInputRectangle( effect, input, &inputRectangle );
        }
        void InvalidateEffectInputRectangle( const Effect& effect, UINT32 input, const D2D1_RECT_F* inputRectangle ) const
        {
            InvalidateEffectInputRectangle( effect.GetInterfacePointer<ID2D1Effect>( ), input, inputRectangle );
        }
        void InvalidateEffectInputRectangle( const Effect& effect, UINT32 input, const D2D1_RECT_F& inputRectangle ) const
        {
            InvalidateEffectInputRectangle( effect.GetInterfacePointer<ID2D1Effect>( ), input, &inputRectangle );
        }


        /// <summary>
        /// Gets the number of invalid output rectangles that have accumulated on the effect.
        /// </summary>
        /// <param name="effect">
        /// The effect to count the invalid rectangles on.
        /// </param>
        /// <param name="rectangleCount">
        /// The returned rectangle count.
        /// </param>
        void GetEffectInvalidRectangleCount( ID2D1Effect* effect, UINT32* rectangleCount ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetEffectInvalidRectangleCount( effect, rectangleCount );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void GetEffectInvalidRectangleCount( const Effect& effect, UINT32* rectangleCount ) const
        {
            GetEffectInvalidRectangleCount( effect.GetInterfacePointer<ID2D1Effect>( ), rectangleCount );
        }

        UINT32 GetEffectInvalidRectangleCount( ID2D1Effect* effect ) const
        {
            UINT32 result = 0;
            GetEffectInvalidRectangleCount( effect, &result );
            return result;
        }
        UINT32 GetEffectInvalidRectangleCount( const Effect& effect ) const
        {
            return GetEffectInvalidRectangleCount( effect.GetInterfacePointer<ID2D1Effect>( ) );
        }

        /// <summary>
        /// Gets the invalid rectangles that have accumulated since the last time 
        /// the effect was drawn and EndDraw was then called on the device context.
        /// </summary>
        /// <param name="effect">
        /// The effect to get the invalid rectangles from.
        /// </param>
        /// <param name="rectangles">
        /// An array of D2D1_RECT_F structures. You must allocate this to the correct 
        /// size. You can get the count of the invalid rectangles using the 
        /// GetEffectInvalidRectangleCount method.
        /// </param>
        /// <param name="rectanglesCount">
        /// The number of rectangles to get.
        /// </param>
        /// <remarks>
        /// <p>
        /// You can use the InvalidateEffectInputRectangle method to specify invalidated 
        /// rectangles for Direct2D to propagate through an effect graph.
        /// </p>
        /// <p>
        /// If multiple invalid rectangles are requested, the rectangles that this method 
        /// returns may overlap. When this is the case, the rectangle count might be lower 
        /// than the count that GetEffectInvalidRectangleCount.
        /// </p>
        /// <p>
        /// Direct2D does not automatically use these invalid rectangles to reduce the region of an effect that is rendered.
        /// </p>
        /// </remarks>
        void GetEffectInvalidRectangles( ID2D1Effect* effect, D2D1_RECT_F* rectangles, UINT32 rectanglesCount ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetEffectInvalidRectangles( effect, rectangles, rectanglesCount );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void GetEffectInvalidRectangles( const Effect& effect, D2D1_RECT_F* rectangles, UINT32 rectanglesCount ) const
        {
            GetEffectInvalidRectangles( effect.GetInterfacePointer<ID2D1Effect>( ), rectangles, rectanglesCount );
        }

        /// <summary>
        /// Returns the input rectangles that are required to be supplied by 
        /// the caller to produce the given output rectangle.
        /// </summary>
        /// <param name="renderEffect">
        /// The effect whose output is being rendered.
        /// </param>
        /// <param name="renderImageRectangle">
        /// The portion of the output effect whose inputs are being inspected.
        /// </param>
        /// <param name="inputDescriptions">
        /// A list of the inputs whose rectangles are being queried.
        /// </param>
        /// <param name="requiredInputRects">
        /// The input rectangles returned to the caller.
        /// </param>
        /// <param name="inputCount">
        /// The number of inputs.
        /// </param>
        /// <remarks>
        /// The caller should be very careful not to place a reliance on the 
        /// required input rectangles returned. Small changes for correctness 
        /// to an effect's behavior can result in different rectangles being 
        /// returned. In addition, different kinds of optimization applied 
        /// inside the render can also influence the result.
        /// </remarks>
        void GetEffectRequiredInputRectangles( ID2D1Effect* renderEffect, const D2D1_RECT_F* renderImageRectangle, const D2D1_EFFECT_INPUT_DESCRIPTION* inputDescriptions, D2D1_RECT_F* requiredInputRects, UINT32 inputCount ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetEffectRequiredInputRectangles( renderEffect, renderImageRectangle, inputDescriptions, requiredInputRects, inputCount );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void GetEffectRequiredInputRectangles( const Effect& renderEffect, const D2D1_RECT_F* renderImageRectangle, const D2D1_EFFECT_INPUT_DESCRIPTION* inputDescriptions, D2D1_RECT_F* requiredInputRects, UINT32 inputCount ) const
        {
            GetEffectRequiredInputRectangles( renderEffect.GetInterfacePointer<ID2D1Effect>( ), renderImageRectangle, inputDescriptions, requiredInputRects, inputCount );
        }

        /// <summary>
        /// Fill using the alpha channel of the supplied opacity mask bitmap. 
        /// The brush opacity will be modulated by the mask. The render target 
        /// anti-aliasing mode must be set to aliased.
        /// </summary>
        /// <param name="opacityMask">
        /// The bitmap that acts as the opacity mask
        /// </param>
        /// <param name="brush">
        /// The brush to use for filling the primitive.
        /// </param>
        /// <param name="destinationRectangle">
        /// The destination rectangle to output to in the render target
        /// </param>
        /// <param name="sourceRectangle">
        /// The source rectangle from the opacity mask bitmap.
        /// </param>
        void FillOpacityMask( ID2D1Bitmap* opacityMask, ID2D1Brush* brush, const D2D1_RECT_F* destinationRectangle = nullptr, const D2D1_RECT_F* sourceRectangle = nullptr ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->FillOpacityMask( opacityMask, brush, destinationRectangle, sourceRectangle );
        }
        void FillOpacityMask( const Bitmap& opacityMask, const Brush& brush, const D2D1_RECT_F* destinationRectangle = nullptr, const D2D1_RECT_F* sourceRectangle = nullptr ) const
        {
            FillOpacityMask( opacityMask.GetInterfacePointer<ID2D1Bitmap>( ), brush.GetInterfacePointer<ID2D1Brush>( ), destinationRectangle, sourceRectangle );
        }
        void FillOpacityMask( ID2D1Bitmap* opacityMask, ID2D1Brush* brush, const D2D1_RECT_F& destinationRectangle, const D2D1_RECT_F* sourceRectangle = nullptr ) const
        {
            FillOpacityMask( opacityMask, brush, &destinationRectangle, sourceRectangle );
        }
        void FillOpacityMask( const Bitmap& opacityMask, const Brush& brush, const D2D1_RECT_F& destinationRectangle, const D2D1_RECT_F* sourceRectangle = nullptr ) const
        {
            FillOpacityMask( opacityMask.GetInterfacePointer<ID2D1Bitmap>( ), brush.GetInterfacePointer<ID2D1Brush>( ), &destinationRectangle, sourceRectangle );
        }

        void FillOpacityMask( ID2D1Bitmap* opacityMask, ID2D1Brush* brush, const D2D1_RECT_F& destinationRectangle, const D2D1_RECT_F& sourceRectangle ) const
        {
            FillOpacityMask( opacityMask, brush, &destinationRectangle, &sourceRectangle );
        }
        void FillOpacityMask( const Bitmap& opacityMask, const Brush& brush, const D2D1_RECT_F& destinationRectangle, const D2D1_RECT_F& sourceRectangle ) const
        {
            FillOpacityMask( opacityMask.GetInterfacePointer<ID2D1Bitmap>( ), brush.GetInterfacePointer<ID2D1Brush>( ), &destinationRectangle, &sourceRectangle );
        }

        using Base::FillOpacityMask;

        

    };

    

    class PrintDocumentPackageTarget;
    class PrintControl;
    /// <summary>
    /// Represents a resource domain whose objects and device 
    /// contexts can be used together.
    /// </summary>
    class Device : public Resource
    {
    public:
        using Base = Resource;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( Device, Base, ID2D1Device, ID2D1Resource )
    public:

        /// <summary>
        /// Creates a new device context with no initially assigned target.
        /// </summary>
        /// <param name="options">
        /// The options to be applied to the created device context.
        /// </param>
        /// <param name="deviceContext">
        /// When this method returns, contains the address of a pointer to 
        /// the new device context.
        /// </param>
        /// <remarks>
        /// The new device context will not have a selected target bitmap. 
        /// The caller must create and select a bitmap as the target surface 
        /// of the context.
        /// </remarks>
        void CreateDeviceContext( D2D1_DEVICE_CONTEXT_OPTIONS options, ID2D1DeviceContext** deviceContext ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateDeviceContext( options, deviceContext );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        [[nodiscard]]
        DeviceContext CreateDeviceContext( D2D1_DEVICE_CONTEXT_OPTIONS options = D2D1_DEVICE_CONTEXT_OPTIONS_NONE ) const
        {
            ID2D1DeviceContext* deviceContext = nullptr;
            CreateDeviceContext( options, &deviceContext );
            return DeviceContext( deviceContext );
        }

        DeviceContext CreateDeviceContext0( D2D1_DEVICE_CONTEXT_OPTIONS options ) const
        {
            return CreateDeviceContext( options );
        }


        /// <summary>
        /// Creates an ID2D1PrintControl object that converts Direct2D primitives 
        /// stored in ID2D1CommandList into a fixed page representation. The print 
        /// sub-system then consumes the primitives.
        /// </summary>
        /// <param name="wicFactory">
        /// A WIC imaging factory.
        /// </param>
        /// <param name="documentTarget">
        /// The target print job for this control.
        /// </param>
        /// <param name="printControlProperties">
        /// The options to be applied to the print control.
        /// </param>
        /// <param name="printControl">
        /// When this method returns, contains the address of a pointer to an ID2D1PrintControl object.
        /// </param>
        void CreatePrintControl( IWICImagingFactory* wicFactory, IPrintDocumentPackageTarget* documentTarget, const D2D1_PRINT_CONTROL_PROPERTIES* printControlProperties, ID2D1PrintControl** printControl ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreatePrintControl( wicFactory, documentTarget, printControlProperties, printControl );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void CreatePrintControl( IWICImagingFactory* wicFactory, IPrintDocumentPackageTarget* documentTarget, const D2D1_PRINT_CONTROL_PROPERTIES& printControlProperties, ID2D1PrintControl** printControl ) const
        {
            CreatePrintControl( wicFactory, documentTarget, &printControlProperties, printControl );
        }

        HW_EXPORT void CreatePrintControl( const Imaging::ImagingFactory& wicFactory, const DocumentTarget::PrintDocumentPackageTarget& documentTarget, const D2D1_PRINT_CONTROL_PROPERTIES* printControlProperties, ID2D1PrintControl** printControl ) const;

        PrintControl CreatePrintControl( IWICImagingFactory* wicFactory, IPrintDocumentPackageTarget* documentTarget, const D2D1_PRINT_CONTROL_PROPERTIES* printControlProperties = nullptr ) const
        {
            ID2D1PrintControl* ptr = nullptr;
            CreatePrintControl( wicFactory, documentTarget, printControlProperties, &ptr );
            return PrintControl( ptr );
        }

        HW_EXPORT PrintControl CreatePrintControl( const Imaging::ImagingFactory& wicFactory, const DocumentTarget::PrintDocumentPackageTarget& documentTarget, const D2D1_PRINT_CONTROL_PROPERTIES* printControlProperties = nullptr ) const;



        /// <summary>
        /// Sets the maximum amount of texture memory Direct2D accumulates before 
        /// it purges the image caches and cached texture allocations.
        /// </summary>
        /// <param name="maximumTextureMemoryInBytes">
        /// The new maximum texture memory in bytes.
        /// </param>
        /// <remarks>
        /// Direct2D may exceed the maximum texture memory you set with this method 
        /// for a single frame if necessary to render the frame.
        /// </remarks>
        void SetMaximumTextureMemory( UINT64 maximumTextureMemoryInBytes ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->SetMaximumTextureMemory( maximumTextureMemoryInBytes );
        }

        /// <summary>
        /// Gets the maximum amount of texture memory to maintain before evicting caches.
        /// </summary>
        /// <returns>
        /// The maximum amount of texture memory in bytes.
        /// </returns>
        UINT64 GetMaximumTextureMemory( ) const
        {
            auto* pInterface = GetInterface( );
            return pInterface->GetMaximumTextureMemory( );
        }

        /// <summary>
        /// Clears all resources that are cached but not held in use by the application
        /// through an interface reference.
        /// </summary>
        /// <param name="millisecondsSinceUse">
        /// Discards only resources that haven't been used for greater than the 
        /// specified time in milliseconds. The default is 0 milliseconds.
        /// </param>
        void ClearResources( UINT32 millisecondsSinceUse = 0 ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->ClearResources( millisecondsSinceUse );
        }

    };

    inline Device DeviceContext::GetDevice( ) const
    {
        ID2D1Device* ptr = nullptr;
        GetDevice( &ptr );
        return Device( ptr );
    }

    class Multithread;
    /// <summary>
    /// Creates Direct2D resources.
    /// </summary>
    class Factory1 : public Factory
    {
    public:
        using Base = Factory;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( Factory1, Base, ID2D1Factory1, ID2D1Factory )

        /// <summary>
        /// Constructs a factory object that can be used to create Direct2D resources.
        /// </summary>
        /// <param name="factoryType">
        /// The threading model of the factory and the resources it creates.
        /// </param>
        Factory1( D2D1_FACTORY_TYPE factoryType )
        {
            ID2D1Factory1* d2d1Factory1 = nullptr;
            auto hr = D2D1CreateFactory( factoryType, __uuidof( ID2D1Factory1 ), (void**)&d2d1Factory1 );
            HCC_COM_CHECK_HRESULT( hr );
            unknown_ = d2d1Factory1;
        }

    public:
        /// <summary>
        /// This creates a new Direct2D device from the given IDXGIDevice.
        /// </summary>
        /// <param name="dxgiDevice">
        /// he IDXGIDevice object used when creating the ID2D1Device.
        /// </param>
        /// <param name="d2dDevice">
        /// The requested ID2D1Device object.
        /// </param>
        /// <remarks>
        /// The Direct2D device defines a resource domain in which a set of Direct2D 
        /// objects and Direct2D device contexts can be used together. Each call to 
        /// CreateDevice returns a unique ID2D1Device object, even if you pass the 
        /// same IDXGIDevice multiple times.
        /// </remarks>
        void CreateDevice( IDXGIDevice* dxgiDevice, ID2D1Device** d2dDevice ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateDevice( dxgiDevice, d2dDevice );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void CreateDevice( const DXGI::Device& dxgiDevice, ID2D1Device** d2dDevice ) const
        {
            CreateDevice( dxgiDevice.GetInterfacePointer<IDXGIDevice>( ), d2dDevice );
        }

        [[nodiscard]] 
        Device CreateDevice( IDXGIDevice* dxgiDevice ) const
        {
            ID2D1Device* d2dDevice = nullptr;
            CreateDevice( dxgiDevice, &d2dDevice );
            Device result( d2dDevice );
            return result;
        }
        [[nodiscard]]
        Device CreateDevice( const DXGI::Device& dxgiDevice ) const
        {
            return CreateDevice( dxgiDevice.GetInterfacePointer<IDXGIDevice>( ) );
        }

        /// <summary>
        /// This creates a stroke style with the ability to preserve stroke width in various
        /// ways.
        /// </summary>
        /// <param name="strokeStyleProperties">
        /// The stroke style properties to apply.
        /// </param>
        /// <param name="dashes">
        /// An array of widths for the dashes and gaps.
        /// </param>
        /// <param name="dashesCount">
        /// The size of the dash array.
        /// </param>
        /// <param name="strokeStyle">
        /// When this method returns, contains the address of a pointer to the newly created stroke style.
        /// </param>
        /// <remarks>
        /// It is valid to specify a dash array only if D2D1_DASH_STYLE_CUSTOM is also specified.
        /// </remarks>
        void CreateStrokeStyle( const D2D1_STROKE_STYLE_PROPERTIES1* strokeStyleProperties, const FLOAT* dashes, UINT32 dashesCount, ID2D1StrokeStyle1** strokeStyle ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateStrokeStyle( strokeStyleProperties, dashes, dashesCount, strokeStyle );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void CreateStrokeStyle( const D2D1_STROKE_STYLE_PROPERTIES1& strokeStyleProperties, const FLOAT* dashes, UINT32 dashesCount, ID2D1StrokeStyle1** strokeStyle ) const
        {
            CreateStrokeStyle( &strokeStyleProperties, dashes, dashesCount, strokeStyle );
        }
        void CreateStrokeStyle( const D2D1_STROKE_STYLE_PROPERTIES1* strokeStyleProperties, ID2D1StrokeStyle1** strokeStyle ) const
        {
            CreateStrokeStyle( strokeStyleProperties, nullptr, 0, strokeStyle );
        }
        void CreateStrokeStyle( const D2D1_STROKE_STYLE_PROPERTIES1& strokeStyleProperties, ID2D1StrokeStyle1** strokeStyle ) const
        {
            CreateStrokeStyle( &strokeStyleProperties, nullptr, 0, strokeStyle );
        }

        StrokeStyle1 CreateStrokeStyle( const D2D1_STROKE_STYLE_PROPERTIES1* strokeStyleProperties, const FLOAT* dashes = nullptr, UINT32 dashesCount = 0 ) const
        {
            ID2D1StrokeStyle1* ptr = nullptr;
            CreateStrokeStyle( strokeStyleProperties, dashes, dashesCount, &ptr );
            return StrokeStyle1( ptr );
        }
        StrokeStyle1 CreateStrokeStyle( const D2D1_STROKE_STYLE_PROPERTIES1& strokeStyleProperties, const FLOAT* dashes = nullptr, UINT32 dashesCount = 0 ) const
        {
            return CreateStrokeStyle( &strokeStyleProperties, dashes, dashesCount );
        }


        using Base::CreateStrokeStyle;

        /// <summary>
        /// Creates a path geometry with new operational methods.
        /// </summary>
        /// <param name="pathGeometry">
        /// When this method returns, contains the address of a pointer to the 
        /// newly created path geometry.
        /// </param>
        void CreatePathGeometry( ID2D1PathGeometry1** pathGeometry ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreatePathGeometry( pathGeometry );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        PathGeometry1 CreatePathGeometry( ) const
        {
            ID2D1PathGeometry1* ptr = nullptr;
            CreatePathGeometry( &ptr );
            return PathGeometry1( ptr );
        }

        using Base::CreatePathGeometry;

        /// <summary>
        /// Creates a new drawing state block, this can be used in subsequent 
        /// SaveDrawingState and RestoreDrawingState operations on the render target.
        /// </summary>
        /// <param name="drawingStateDescription">
        /// The drawing state description structure.
        /// </param>
        /// <param name="textRenderingParams">
        /// The DirectWrite rendering params interface.
        /// </param>
        /// <param name="drawingStateBlock">
        /// The address of the newly created drawing state block.
        /// </param>
        void CreateDrawingStateBlock( const D2D1_DRAWING_STATE_DESCRIPTION1* drawingStateDescription, IDWriteRenderingParams* textRenderingParams, ID2D1DrawingStateBlock1** drawingStateBlock ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateDrawingStateBlock( drawingStateDescription, textRenderingParams, drawingStateBlock );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        inline void CreateDrawingStateBlock( const D2D1_DRAWING_STATE_DESCRIPTION1* drawingStateDescription, const DirectWrite::RenderingParams& textRenderingParams, ID2D1DrawingStateBlock1** drawingStateBlock ) const;

        void CreateDrawingStateBlock( const D2D1_DRAWING_STATE_DESCRIPTION1& drawingStateDescription, IDWriteRenderingParams* textRenderingParams, ID2D1DrawingStateBlock1** drawingStateBlock ) const
        {
            CreateDrawingStateBlock( &drawingStateDescription, textRenderingParams, drawingStateBlock );
        }
        inline void CreateDrawingStateBlock( const D2D1_DRAWING_STATE_DESCRIPTION1& drawingStateDescription, const DirectWrite::RenderingParams& textRenderingParams, ID2D1DrawingStateBlock1** drawingStateBlock ) const;

        void CreateDrawingStateBlock( const D2D1_DRAWING_STATE_DESCRIPTION1& drawingStateDescription, ID2D1DrawingStateBlock1** drawingStateBlock )
        {
            CreateDrawingStateBlock( &drawingStateDescription, nullptr, drawingStateBlock );
        }

        void CreateDrawingStateBlock( ID2D1DrawingStateBlock1** drawingStateBlock )
        {
            CreateDrawingStateBlock( nullptr, nullptr, drawingStateBlock );
        }

        DrawingStateBlock1 CreateDrawingStateBlock( const D2D1_DRAWING_STATE_DESCRIPTION1* drawingStateDescription, IDWriteRenderingParams* textRenderingParams = nullptr ) const
        {
            ID2D1DrawingStateBlock1* ptr = nullptr;
            CreateDrawingStateBlock( drawingStateDescription, textRenderingParams, &ptr );
            return DrawingStateBlock1( ptr );
        }
        inline DrawingStateBlock1 CreateDrawingStateBlock( const D2D1_DRAWING_STATE_DESCRIPTION1* drawingStateDescription, const DirectWrite::RenderingParams& textRenderingParams ) const;
        inline DrawingStateBlock1 CreateDrawingStateBlock( const D2D1_DRAWING_STATE_DESCRIPTION1& drawingStateDescription, const DirectWrite::RenderingParams& textRenderingParams ) const;

        DrawingStateBlock1 CreateDrawingStateBlock( const D2D1_DRAWING_STATE_DESCRIPTION1& drawingStateDescription, IDWriteRenderingParams* textRenderingParams = nullptr ) const
        {
            return CreateDrawingStateBlock( &drawingStateDescription, textRenderingParams );
        }


        using Base::CreateDrawingStateBlock;

        /// <summary>
        /// Creates a new ID2D1GdiMetafile object that you can use to replay metafile content.
        /// </summary>
        /// <param name="metafileStream">
        /// A stream object that has the metafile data.
        /// </param>
        /// <param name="metafile">
        /// The address of the newly created GDI metafile object.
        /// </param>
        void CreateGdiMetafile( IStream* metafileStream, ID2D1GdiMetafile** metafile ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateGdiMetafile( metafileStream, metafile );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void CreateGdiMetafile( const Stream& metafileStream, ID2D1GdiMetafile** metafile ) const
        {
            CreateGdiMetafile( metafileStream.GetInterfacePointer<IStream>( ), metafile );
        }
        GdiMetafile CreateGdiMetafile( IStream* metafileStream ) const
        {
            ID2D1GdiMetafile* ptr = nullptr;
            CreateGdiMetafile( metafileStream, &ptr );
            return GdiMetafile( ptr );
        }
        GdiMetafile CreateGdiMetafile( const Stream& metafileStream ) const
        {
            return CreateGdiMetafile( metafileStream.GetInterfacePointer<IStream>( ) );
        }


        /// <summary>
        /// This globally registers the given effect. The effect can later be instantiated
        /// by using the registered class id. The effect registration is reference counted.
        /// </summary>
        /// <param name="classId">
        /// The identifier of the effect to be registered.
        /// </param>
        /// <param name="propertyXml">
        /// A list of the effect properties, types, and metadata.
        /// </param>
        /// <param name="bindings">
        /// <p>
        /// An array of properties and methods.
        /// </p>
        /// <p>
        /// This binds a property by name to a particular method implemented by the effect 
        /// author to handle the property. The name must be found in the corresponding propertyXml.
        /// </p>
        /// </param>
        /// <param name="bindingsCount">
        /// The number of bindings in the binding array.
        /// </param>
        /// <param name="effectFactory">
        /// The static factory that is used to create the corresponding effect.
        /// </param>
        /// <remarks>
        /// <p>
        /// Direct2D effects must define their properties at registration time via registration XML. 
        /// An effect declares several required system properties, and can also declare custom properties. 
        /// See <a href="https://docs.microsoft.com/en-us/windows/win32/direct2d/custom-effects">Custom effects</a> for more information about formatting the propertyXml parameter.
        /// </p>
        /// <p>
        /// RegisterEffectFromStream is both atomic and reference counted. To unregister an effect, 
        /// call UnregisterEffect with the classId of the effect.
        /// </p>
        /// <p>
        /// RegisterEffectFromStream does not hold a reference to the DLL or executable file in which 
        /// the effect is contained. The application must independently make sure that the 
        /// lifetime of the DLL or executable file completely contains all instances of 
        /// each registered and created effect.
        /// </p>
        /// <p>
        /// Aside from the built-in effects that are globally registered, this API registers 
        /// effects only for this factory, derived device, and device context interfaces.
        /// </p>
        /// </remarks>
        void RegisterEffectFromStream( REFCLSID classId, IStream* propertyXml, const D2D1_PROPERTY_BINDING* bindings, UINT32 bindingsCount, const PD2D1_EFFECT_FACTORY effectFactory ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->RegisterEffectFromStream( classId, propertyXml, bindings, bindingsCount, effectFactory );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void RegisterEffectFromStream( REFCLSID classId, IStream* propertyXml, const PD2D1_EFFECT_FACTORY effectFactory ) const
        {
            RegisterEffectFromStream( classId, propertyXml, nullptr, 0, effectFactory );
        }
        void RegisterEffectFromStream( REFCLSID classId, const Stream& propertyXml, const D2D1_PROPERTY_BINDING* bindings, UINT32 bindingsCount, const PD2D1_EFFECT_FACTORY effectFactory ) const
        {
            RegisterEffectFromStream( classId, propertyXml.GetInterfacePointer<IStream>(), bindings, bindingsCount, effectFactory );
        }
        void RegisterEffectFromStream( REFCLSID classId, const Stream& propertyXml, const PD2D1_EFFECT_FACTORY effectFactory ) const
        {
            RegisterEffectFromStream( classId, propertyXml.GetInterfacePointer<IStream>( ), nullptr, 0, effectFactory );
        }

        /// <summary>
        /// This globally registers the given effect. The effect can later be instantiated
        /// by using the registered class id. The effect registration is reference counted.
        /// </summary>
        /// <param name="classId">
        /// The identifier of the effect to be registered.
        /// </param>
        /// <param name="propertyXml">
        /// A list of the effect properties, types, and metadata.
        /// </param>
        /// <param name="bindings">
        /// <p>
        /// An array of properties and methods.
        /// </p>
        /// <p>
        /// This binds a property by name to a particular method implemented by the effect 
        /// author to handle the property. The name must be found in the corresponding propertyXml.
        /// </p>
        /// </param>
        /// <param name="bindingsCount">
        /// The number of bindings in the binding array.
        /// </param>
        /// <param name="effectFactory">
        /// The static factory that is used to create the corresponding effect.
        /// </param>
        /// <remarks>
        /// <p>
        /// Direct2D effects must define their properties at registration time via registration XML. 
        /// An effect declares several required system properties, and can also declare custom properties. 
        /// See <a href="https://docs.microsoft.com/en-us/windows/win32/direct2d/custom-effects">Custom effects</a> for more information about formatting the propertyXml parameter.
        /// </p>
        /// <p>
        /// RegisterEffectFromString is both atomic and reference counted. To unregister an effect, 
        /// call UnregisterEffect with the classId of the effect.
        /// </p>
        /// <p>
        /// RegisterEffectFromString does not hold a reference to the DLL or executable file in which 
        /// the effect is contained. The application must independently make sure that the 
        /// lifetime of the DLL or executable file completely contains all instances of 
        /// each registered and created effect.
        /// </p>
        /// <p>
        /// Aside from the built-in effects that are globally registered, this API registers 
        /// effects only for this factory, derived device, and device context interfaces.
        /// </p>
        /// </remarks>
        void RegisterEffectFromString( REFCLSID classId, PCWSTR propertyXml, const D2D1_PROPERTY_BINDING* bindings, UINT32 bindingsCount, const PD2D1_EFFECT_FACTORY effectFactory ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->RegisterEffectFromString( classId, propertyXml, bindings, bindingsCount, effectFactory );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void RegisterEffectFromString( REFCLSID classId, PCWSTR propertyXml, const PD2D1_EFFECT_FACTORY effectFactory ) const
        {
            RegisterEffectFromString( classId, propertyXml, nullptr, 0, effectFactory );
        }

        /// <summary>
        /// This unregisters the given effect by its class id, you need to call
        /// UnregisterEffect for every call to ID2D1Factory1::RegisterEffectFromStream and
        /// ID2D1Factory1::RegisterEffectFromString to completely unregister it.
        /// </summary>
        /// <param name="classId">
        /// The identifier of the effect to be unregistered.
        /// </param>
        /// <remarks>
        /// <p>
        /// In order for the effect to be fully unloaded, you must call UnregisterEffect 
        /// the same number of times that you have registered the effect.
        /// </p>
        /// <p>
        /// The UnregisterEffect method unregisters only those effects that are registered 
        /// on the same factory. It cannot be used to unregister a built-in effect.
        /// </p>
        /// </remarks>
        void UnregisterEffect( REFCLSID classId ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->UnregisterEffect( classId );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Returns the class IDs of the currently registered effects and global effects on this factory.
        /// </summary>
        /// <param name="effects">
        /// When this method returns, contains an array of effects. NULL if no effects are retrieved.
        /// </param>
        /// <param name="effectsCount">
        /// The capacity of the effects array.
        /// </param>
        /// <param name="effectsReturned">
        /// When this method returns, contains the number of effects copied into effects.
        /// </param>
        /// <param name="effectsRegistered">
        /// When this method returns, contains the number of effects currently registered in the system.
        /// </param>
        /// <remarks>
        /// <p>
        /// The set of class IDs will be atomically returned by the API. The set will not be 
        /// interrupted by other threads registering or unregistering effects.
        /// </p>
        /// <p>
        /// If effectsRegistered is larger than effectCount, the supplied array will still be 
        /// filled to capacity with the current set of registered effects. This method returns 
        /// the CLSIDs for all global effects and all effects registered to this factory.
        /// </p>
        /// </remarks>
        void GetRegisteredEffects( CLSID* effects, UINT32 effectsCount, UINT32* effectsReturned, UINT32* effectsRegistered ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetRegisteredEffects( effects, effectsCount, effectsReturned, effectsRegistered );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }


        /// <summary>
        /// Returns the number of currently registered effects and global effects on this factory.
        /// </summary>
        /// <param name="effectsRegistered">
        /// When this method returns, contains the number of effects currently registered in the system.
        /// </param>
        void GetRegisteredEffectsCount( UINT32* effectsRegistered ) const
        {
            GetRegisteredEffects( nullptr, 0, nullptr, effectsRegistered );
        }
        UINT32 GetRegisteredEffectsCount( ) const
        {
            UINT32 result = 0;
            GetRegisteredEffectsCount( &result );
            return result;
        }



        /// <summary>
        /// This retrieves the effect properties for the given effect, all of the effect
        /// properties will be set to a default value since an effect is not instantiated to
        /// implement the returned property interface.
        /// </summary>
        /// <param name="effectId">
        /// The ID of the effect to retrieve properties from.
        /// </param>
        /// <param name="properties">
        /// When this method returns, contains the address of a pointer to the property 
        /// interface that can be used to query the metadata of the effect.
        /// </param>
        /// <remarks>
        /// <p>
        /// The returned effect properties will have all the mutable properties for the 
        /// effect set to a default of NULL, or an empty value.
        /// </p>
        /// <ul>
        ///     <li>
        ///     Value types will be zero-filled.
        ///     </li>
        ///     <li>
        ///     Blob and string types will be zero-length.
        ///     </li>
        ///     <li>
        ///     Array types will have length 1 and the element of the array will 
        ///     conform to the above rules.
        ///     </li>
        /// </ul>
        /// <p>
        /// This method cannot be used to return the properties for any effect not visible 
        /// to DeviceContext::CreateEffect.
        /// </p>
        /// </remarks>
        void GetEffectProperties( REFCLSID effectId, ID2D1Properties** properties ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetEffectProperties( effectId, properties );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        Properties GetEffectProperties( REFCLSID effectId ) const
        {
            ID2D1Properties* ptr = nullptr;
            GetEffectProperties( effectId, &ptr );
            return Properties( ptr );
        }

        /// <summary>
        /// Retrieves the locking mechanism for the Direct2D factory that 
        /// Direct2D uses to control exclusive resource access in an application 
        /// that is uses multiple threads.
        /// </summary>
        /// <returns>
        /// The Direct2D factory locking mechanism.
        /// </returns>
        inline Multithread GetMultithread( ) const;

    };


    /// <summary>
    /// A locking mechanism from a Direct2D factory that Direct2D uses to control
    /// exclusive resource access in an application that is uses multiple threads.
    /// </summary>
    class Multithread : public Unknown
    {
    public:
        using Base = Unknown;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( Multithread, Base, ID2D1Multithread, IUnknown )
    public:
        /// <summary>
        /// Returns whether the D2D factory was created with
        /// D2D1_FACTORY_TYPE_MULTI_THREADED.
        /// </summary>
        BOOL GetMultithreadProtected( ) const
        {
            auto* pInterface = GetInterface( );
            return pInterface->GetMultithreadProtected( );
        }

        /// <summary>
        /// Enters the D2D API critical section, if it exists.
        /// </summary>
        void Enter( ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->Enter( );
        }
        /// <summary>
        /// Leaves the D2D API critical section, if it exists.
        /// </summary>
        void Leave( ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->Leave( );
        }
    };

    inline Multithread Factory1::GetMultithread( ) const
    {
        return Multithread( __uuidof( ID2D1Multithread ), *this, true );
    }


    /// <summary>
    /// Encapsulates a device- and transform-dependent representation of a filled 
    /// or stroked geometry. Callers should consider creating a geometry realization 
    /// when they wish to accelerate repeated rendering of a given geometry. This 
    /// interface exposes no methods.
    /// </summary>
    class GeometryRealization : public Resource
    {
    public:
        using Base = Resource;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( GeometryRealization, Base, ID2D1GeometryRealization, ID2D1Resource )
    public:
    };

    /// <summary>
    /// Enables creation and drawing of geometry realization objects.
    /// </summary>
    class DeviceContext1 : public DeviceContext
    {
    public:
        using Base = DeviceContext;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( DeviceContext1, Base, ID2D1DeviceContext1, ID2D1DeviceContext )
    public:
        /// <summary>
        /// Creates a device-dependent representation of the fill of the geometry 
        /// that can be subsequently rendered.
        /// </summary>
        /// <param name="geometry">
        /// The geometry to realize.
        /// </param>
        /// <param name="flatteningTolerance">
        /// The flattening tolerance to use when converting Beziers to line segments. 
        /// This parameter shares the same units as the coordinates of the geometry.
        /// </param>
        /// <param name="geometryRealization">
        /// When this method returns, contains the address of a pointer to a new 
        /// geometry realization object.
        /// </param>
        /// <remarks>
        /// <p>
        /// This method is used in conjunction with DrawGeometryRealization. The 
        /// D2D1::ComputeFlatteningTolerance helper API may be used to determine 
        /// the proper flattening tolerance.
        /// </p>
        /// <p>
        /// If the provided stroke style specifies a stroke transform type other 
        /// than D2D1_STROKE_TRANSFORM_TYPE_NORMAL, then the stroke will be 
        /// realized assuming the identity transform and a DPI of 96.
        /// </p>
        /// </remarks>
        void CreateFilledGeometryRealization( ID2D1Geometry* geometry, FLOAT flatteningTolerance, ID2D1GeometryRealization** geometryRealization ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateFilledGeometryRealization( geometry, flatteningTolerance, geometryRealization );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void CreateFilledGeometryRealization( const Geometry& geometry, FLOAT flatteningTolerance, ID2D1GeometryRealization** geometryRealization ) const
        {
            CreateFilledGeometryRealization( geometry.GetInterfacePointer<ID2D1Geometry>(), flatteningTolerance, geometryRealization );
        }
        GeometryRealization CreateFilledGeometryRealization( ID2D1Geometry* geometry, FLOAT flatteningTolerance = D2D1_DEFAULT_FLATTENING_TOLERANCE ) const
        {
            ID2D1GeometryRealization* ptr = nullptr;
            CreateFilledGeometryRealization( geometry, flatteningTolerance, &ptr );
            return GeometryRealization( ptr );
        }
        GeometryRealization CreateFilledGeometryRealization( const Geometry& geometry, FLOAT flatteningTolerance = D2D1_DEFAULT_FLATTENING_TOLERANCE ) const
        {
            return CreateFilledGeometryRealization( geometry.GetInterfacePointer<ID2D1Geometry>( ), flatteningTolerance );
        }


        /// <summary>
        /// Creates a device-dependent representation of the stroke of a geometry 
        /// that can be subsequently rendered.
        /// </summary>
        /// <param name="geometry">
        /// The geometry to realize.
        /// </param>
        /// <param name="flatteningTolerance">
        /// The flattening tolerance to use when converting Beziers to line segments. 
        /// This parameter shares the same units as the coordinates of the geometry.
        /// </param>
        /// <param name="strokeWidth">
        /// The width of the stroke. This parameter shares the same units as the 
        /// coordinates of the geometry.
        /// </param>
        /// <param name="strokeStyle">
        /// The stroke style (optional).
        /// </param>
        /// <param name="geometryRealization">
        /// When this method returns, contains the address of a pointer to a 
        /// new geometry realization object.
        /// </param>
        void CreateStrokedGeometryRealization( ID2D1Geometry* geometry, FLOAT flatteningTolerance, FLOAT strokeWidth, ID2D1StrokeStyle* strokeStyle, ID2D1GeometryRealization** geometryRealization ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateStrokedGeometryRealization( geometry, flatteningTolerance, strokeWidth, strokeStyle, geometryRealization );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void CreateStrokedGeometryRealization( const Geometry& geometry, FLOAT flatteningTolerance, FLOAT strokeWidth, const StrokeStyle& strokeStyle, ID2D1GeometryRealization** geometryRealization ) const
        {
            CreateStrokedGeometryRealization( geometry.GetInterfacePointer<ID2D1Geometry>( ), flatteningTolerance, strokeWidth, strokeStyle.GetInterfacePointer<ID2D1StrokeStyle>( ), geometryRealization );
        }
        void CreateStrokedGeometryRealization( ID2D1Geometry* geometry, FLOAT flatteningTolerance, FLOAT strokeWidth, ID2D1GeometryRealization** geometryRealization ) const
        {
            CreateStrokedGeometryRealization( geometry, flatteningTolerance, strokeWidth, nullptr, geometryRealization );
        }
        void CreateStrokedGeometryRealization( const Geometry& geometry, FLOAT flatteningTolerance, FLOAT strokeWidth, ID2D1GeometryRealization** geometryRealization ) const
        {
            CreateStrokedGeometryRealization( geometry.GetInterfacePointer<ID2D1Geometry>( ), flatteningTolerance, strokeWidth, nullptr, geometryRealization );
        }
        GeometryRealization CreateStrokedGeometryRealization( ID2D1Geometry* geometry, FLOAT flatteningTolerance, FLOAT strokeWidth, ID2D1StrokeStyle* strokeStyle = nullptr ) const
        {
            ID2D1GeometryRealization* ptr = nullptr;
            CreateStrokedGeometryRealization( geometry, flatteningTolerance, strokeWidth, strokeStyle, &ptr );
            return GeometryRealization( ptr );
        }
        GeometryRealization CreateStrokedGeometryRealization( const Geometry& geometry, FLOAT flatteningTolerance, FLOAT strokeWidth, ID2D1StrokeStyle* strokeStyle = nullptr ) const
        {
            return CreateStrokedGeometryRealization( geometry.GetInterfacePointer<ID2D1Geometry>( ), flatteningTolerance, strokeWidth, strokeStyle );
        }
        GeometryRealization CreateStrokedGeometryRealization( const Geometry& geometry, FLOAT flatteningTolerance, FLOAT strokeWidth, const StrokeStyle& strokeStyle ) const
        {
            return CreateStrokedGeometryRealization( geometry.GetInterfacePointer<ID2D1Geometry>( ), flatteningTolerance, strokeWidth, strokeStyle.GetInterfacePointer<ID2D1StrokeStyle>( ) );
        }
        GeometryRealization CreateStrokedGeometryRealization( ID2D1Geometry* geometry, FLOAT strokeWidth, ID2D1StrokeStyle* strokeStyle = nullptr ) const
        {
            return CreateStrokedGeometryRealization( geometry, D2D1_DEFAULT_FLATTENING_TOLERANCE, strokeWidth, strokeStyle );
        }
        GeometryRealization CreateStrokedGeometryRealization( const Geometry& geometry, FLOAT strokeWidth, ID2D1StrokeStyle* strokeStyle = nullptr ) const
        {
            return CreateStrokedGeometryRealization( geometry.GetInterfacePointer<ID2D1Geometry>( ), D2D1_DEFAULT_FLATTENING_TOLERANCE, strokeWidth, strokeStyle );
        }
        GeometryRealization CreateStrokedGeometryRealization( const Geometry& geometry, FLOAT strokeWidth, const StrokeStyle& strokeStyle ) const
        {
            return CreateStrokedGeometryRealization( geometry.GetInterfacePointer<ID2D1Geometry>( ), D2D1_DEFAULT_FLATTENING_TOLERANCE, strokeWidth, strokeStyle.GetInterfacePointer<ID2D1StrokeStyle>( ) );
        }


        /// <summary>
        /// Renders a given geometry realization to the target with the specified brush.
        /// </summary>
        /// <param name="geometryRealization">
        /// The geometry realization to be rendered.
        /// </param>
        /// <param name="brush">
        /// The brush to render the realization with.
        /// </param>
        /// <remarks>
        /// <p>
        /// This function respects all currently set state (transform, DPI, unit mode, 
        /// target image, clips, layers); however, artifacts such as faceting may appear 
        /// when rendering the realizations with a large effective scale (either via 
        /// the transform or the DPI). Callers should create their realizations with an 
        /// appropriate flattening tolerance using either D2D1_DEFAULT_FLATTENING_TOLERANCE 
        /// or ComputeFlatteningTolerance to compensate for this.
        /// </p>
        /// <p>
        /// Additionally, callers should be aware of the safe render bounds when creating 
        /// geometry realizations. If a geometry extends outside of [-524,287, 524,287] 
        /// DIPs in either the X- or the Y- direction in its original (pre-transform) 
        /// coordinate space, then it may be clipped to those bounds when it is realized. 
        /// This clipping will be visible even if the realization is subsequently 
        /// transformed to fit within the safe render bounds.
        /// </p>
        /// </remarks>
        void DrawGeometryRealization( ID2D1GeometryRealization* geometryRealization, ID2D1Brush* brush ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->DrawGeometryRealization( geometryRealization, brush );
        }
        void DrawGeometryRealization( ID2D1GeometryRealization* geometryRealization, const Brush& brush ) const
        {
            DrawGeometryRealization( geometryRealization, brush.GetInterfacePointer<ID2D1Brush>( ) );
        }
        void DrawGeometryRealization( const GeometryRealization& geometryRealization, ID2D1Brush* brush ) const
        {
            DrawGeometryRealization( geometryRealization.GetInterfacePointer<ID2D1GeometryRealization>( ), brush );
        }
        void DrawGeometryRealization( const GeometryRealization& geometryRealization, const Brush& brush ) const
        {
            DrawGeometryRealization( geometryRealization.GetInterfacePointer<ID2D1GeometryRealization>( ), brush.GetInterfacePointer<ID2D1Brush>( ) );
        }
    };

    /// <summary>
    /// Represents a resource domain whose objects and device contexts can 
    /// be used together. This interface performs all the same functions as 
    /// the existing Device class. It also enables control of the device's 
    /// rendering priority.
    /// </summary>
    class Device1 : public Device
    {
    public:
        using Base = Device;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( Device1, Base, ID2D1Device1, ID2D1Device )
    public:
        /// <summary>
        /// Retrieves the rendering priority currently set on the device.
        /// </summary>
        D2D1_RENDERING_PRIORITY GetRenderingPriority( ) const
        {
            auto* pInterface = GetInterface( );
            return pInterface->GetRenderingPriority( );
        }

        /// <summary>
        /// Sets the rendering priority of the device.
        /// </summary>
        /// <param name="renderingPriority">
        /// Sets the priority of Direct2D rendering operations performed 
        /// on any device context associated with the device.
        /// </param>
        /// <remarks>
        /// Calling this method affects the rendering priority of all device 
        /// contexts associated with the device. This method can be called 
        /// at any time, but is not guaranteed to take effect until the beginning 
        /// of the next frame. The recommended usage is to call this method outside 
        /// of BeginDraw and EndDraw blocks. Cycling this property frequently 
        /// within drawing blocks will effectively reduce the benefits of any 
        /// throttling that is applied.
        /// </remarks>
        void SetRenderingPriority( D2D1_RENDERING_PRIORITY renderingPriority ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->SetRenderingPriority( renderingPriority );
        }

        /// <summary>
        /// Creates a new device context with no initially assigned target.
        /// </summary>
        /// <param name="options">
        /// The options to be applied to the created device context.
        /// The default is D2D1_DEVICE_CONTEXT_OPTIONS_NONE.
        /// </param>
        /// <param name="deviceContext1">
        /// When this method returns, contains the address of a pointer to 
        /// the new device context.
        /// </param>
        void CreateDeviceContext( D2D1_DEVICE_CONTEXT_OPTIONS options, ID2D1DeviceContext1** deviceContext1 ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateDeviceContext( options, deviceContext1 );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        DeviceContext1 CreateDeviceContext( D2D1_DEVICE_CONTEXT_OPTIONS options = D2D1_DEVICE_CONTEXT_OPTIONS_NONE ) const
        {
            ID2D1DeviceContext1* ptr = nullptr;
            CreateDeviceContext( options, &ptr );
            return DeviceContext1( ptr );
        }

        DeviceContext1 CreateDeviceContext1( D2D1_DEVICE_CONTEXT_OPTIONS options = D2D1_DEVICE_CONTEXT_OPTIONS_NONE ) const
        {
            return CreateDeviceContext( options );
        }

        
    };

    /// <summary>
    /// This factory enables the creation of Device1 (ID2D1Device1) objects.
    /// </summary>
    class Factory2 : public Factory1
    {
    public:
        using Base = Factory1;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( Factory2, Base, ID2D1Factory2, ID2D1Factory1 )
    public:
        Factory2( D2D1_FACTORY_TYPE factoryType )
        {
            ID2D1Factory2* d2d1Factory2 = nullptr;
            auto hr = D2D1CreateFactory( factoryType, __uuidof( ID2D1Factory2 ), (void**)&d2d1Factory2 );
            HCC_COM_CHECK_HRESULT( hr );
            unknown_ = d2d1Factory2;
        }
        /// <summary>
        /// This creates a new Direct2D device from the given IDXGIDevice.
        /// </summary>
        /// <param name="dxgiDevice">
        /// The IDXGIDevice object used when creating the ID2D1Device1.
        /// </param>
        /// <param name="d2dDevice1">
        /// The requested ID2D1Device1 object.
        /// </param>
        void CreateDevice( IDXGIDevice* dxgiDevice, ID2D1Device1** d2dDevice1 ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateDevice( dxgiDevice, d2dDevice1 );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void CreateDevice( const DXGI::Device& dxgiDevice, ID2D1Device1** d2dDevice1 ) const
        {
            CreateDevice( dxgiDevice.GetInterfacePointer<IDXGIDevice>( ), d2dDevice1 );
        }

        Device1 CreateDevice( IDXGIDevice* dxgiDevice ) const
        {
            ID2D1Device1* ptr = nullptr;
            CreateDevice( dxgiDevice, &ptr );
            return Device1( ptr );
        }

        Device1 CreateDevice( const DXGI::Device& dxgiDevice ) const
        {
            return CreateDevice( dxgiDevice.GetInterfacePointer<IDXGIDevice>( ) );
        }

        Device1 CreateDevice1( _In_ IDXGIDevice* dxgiDevice ) const
        {
            return CreateDevice( dxgiDevice );
        }
        Device1 CreateDevice1( const DXGI::Device& dxgiDevice ) const
        {
            return CreateDevice( dxgiDevice );
        }
    };

    /// <summary>
    /// This class performs all the same functions as the 
    /// existing CommandSink (ID2D1CommandSink) class. It 
    /// also enables access to the new primitive blend modes, 
    /// MIN and ADD, through its SetPrimitiveBlend1 method.
    /// </summary>
    class CommandSink1 : public CommandSink
    {
    public:
        using Base = CommandSink;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( CommandSink1, Base, ID2D1CommandSink1, ID2D1CommandSink )
    public:
        /// <summary>
        /// Sets a new primitive blend mode.
        /// </summary>
        /// <param name="primitiveBlend">
        /// The primitive blend that will apply to subsequent primitives.
        /// </param>
        void SetPrimitiveBlend1( D2D1_PRIMITIVE_BLEND primitiveBlend ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->SetPrimitiveBlend1( primitiveBlend );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    /// <summary>
    /// Represents a collection of style properties to be used by methods like
    /// ID2D1DeviceContext2::DrawInk when rendering ink. The ink style defines the nib
    /// (pen tip) shape and transform.
    /// </summary>
    class InkStyle : public Resource
    {
    public:
        using Base = Resource;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( InkStyle, Base, ID2D1InkStyle, ID2D1Resource )
    public:
        /// <summary>
        /// Sets the transform to apply to this style's nib shape.
        /// </summary>
        /// <param name="transform">
        /// The transform to apply to this style’s nib shape. Note that 
        /// the translation components of the transform matrix are ignored 
        /// for the purposes of rendering.
        /// </param>
        void SetNibTransform( const D2D1_MATRIX_3X2_F* transform ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->SetNibTransform( transform );
        }
        void SetNibTransform( const D2D1_MATRIX_3X2_F& transform ) const
        {
            SetNibTransform( &transform );
        }

        /// <summary>
        /// Retrieves the transform to be applied to this style's nib shape.
        /// </summary>
        /// <param name="transform">
        /// When this method returns, contains a pointer to the transform to be applied to this style's nib shape.
        /// </param>
        void GetNibTransform( D2D1_MATRIX_3X2_F* transform ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->GetNibTransform( transform );
        }
        void GetNibTransform( D2D1_MATRIX_3X2_F& transform ) const
        {
            GetNibTransform( &transform );
        }

        /// <summary>
        /// Sets the pre-transform nib shape for this style.
        /// </summary>
        /// <param name="nibShape">
        /// The pre-transform nib shape to use in this style.
        /// </param>
        void SetNibShape( D2D1_INK_NIB_SHAPE nibShape ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->SetNibShape( nibShape );
        }

        /// <summary>
        /// Retrieves the pre-transform nib shape for this style.
        /// </summary>
        /// <returns>
        /// Returns the pre-transform nib shape for this style.
        /// </returns>
        D2D1_INK_NIB_SHAPE GetNibShape( ) const
        {
            auto* pInterface = GetInterface( );
            return pInterface->GetNibShape( );
        }

    };


    /// <summary>
    /// Represents a single continuous stroke of variable-width ink, as defined by a
    /// series of Bezier segments and widths.
    /// </summary>
    class Ink : public Resource
    {
    public:
        using Base = Resource;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( Ink, Base, ID2D1Ink, ID2D1Resource )
    public:
        /// <summary>
        /// Sets the starting point for this ink object. This determines 
        /// where this ink object will start rendering.
        /// </summary>
        /// <param name="startPoint">
        /// The new starting point for this ink object.
        /// </param>
        void SetStartPoint( const D2D1_INK_POINT* startPoint ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->SetStartPoint( startPoint );
        }
        void SetStartPoint( const D2D1_INK_POINT& startPoint ) const
        {
            SetStartPoint( &startPoint );
        }

        /// <summary>
        /// Retrieve the start point with which the ink was initialized.
        /// </summary>
        /// <returns>
        /// The starting point for this ink object.
        /// </returns>
        D2D1_INK_POINT GetStartPoint( ) const
        {
            auto* pInterface = GetInterface( );
            return pInterface->GetStartPoint( );
        }

        /// <summary>
        /// Adds the given segments to the end of this ink object.
        /// </summary>
        /// <param name="segments">
        /// A pointer to an array of segments to be added to this ink object.
        /// </param>
        /// <param name="segmentsCount">
        /// The number of segments to be added to this ink object.
        /// </param>
        void AddSegments(const D2D1_INK_BEZIER_SEGMENT* segments, UINT32 segmentsCount ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->AddSegments( segments, segmentsCount );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Removes the given number of segments from the end of this ink object.
        /// </summary>
        /// <param name="segmentsCount">
        /// The number of segments to be removed from the end of this ink object. 
        /// Note that segmentsCount must be less or equal to the number of segments 
        /// in the ink object.
        /// </param>
        void RemoveSegmentsAtEnd( UINT32 segmentsCount ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->RemoveSegmentsAtEnd( segmentsCount );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Updates the specified segments in this ink object with new control points.
        /// </summary>
        /// <param name="startSegment">
        /// The index of the first segment in this ink object to update.
        /// </param>
        /// <param name="segments">
        /// A pointer to the array of segment data to be used in the update.
        /// </param>
        /// <param name="segmentsCount">
        /// The number of segments in this ink object that will be updated with 
        /// new data. Note that segmentsCount must be less than or equal to the 
        /// number of segments in the ink object minus startSegment.
        /// </param>
        void SetSegments(UINT32 startSegment, const D2D1_INK_BEZIER_SEGMENT* segments, UINT32 segmentsCount ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->SetSegments( startSegment, segments, segmentsCount );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Updates the last segment in this ink object with new control points.
        /// </summary>
        /// <param name="segment">
        /// A pointer to the segment data with which to overwrite this ink object's 
        /// last segment. Note that if there are currently no segments in the ink 
        /// object, SetSegmentsAtEnd will return an error causing a 
        /// Harlinn::Common::Core::Exception to be thrown.
        /// </param>
        void SetSegmentAtEnd(const D2D1_INK_BEZIER_SEGMENT* segment ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->SetSegmentAtEnd( segment );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Returns the number of segments in this ink object.
        /// </summary>
        /// <returns>
        /// Returns the number of segments in this ink object.
        /// </returns>
        UINT32 GetSegmentCount( ) const
        {
            auto* pInterface = GetInterface( );
            return pInterface->GetSegmentCount( );
        }

        /// <summary>
        /// Retrieves the specified subset of segments stored in this ink object.
        /// </summary>
        /// <param name="startSegment">
        /// The index of the first segment in this ink object to retrieve.
        /// </param>
        /// <param name="segments">
        /// When this method returns, contains a pointer to an array of retrieved segments.
        /// </param>
        /// <param name="segmentsCount">
        /// The number of segments to retrieve. Note that segmentsCount must be less than 
        /// or equal to the number of segments in the ink object minus startSegment.
        /// </param>
        void GetSegments( UINT32 startSegment, D2D1_INK_BEZIER_SEGMENT* segments, UINT32 segmentsCount ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetSegments( startSegment, segments, segmentsCount );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Retrieves a geometric representation of this ink object.
        /// </summary>
        /// <param name="inkStyle">
        /// The ink style to be used in determining the geometric representation.
        /// </param>
        /// <param name="worldTransform">
        /// The world transform to be used in determining the geometric representation.
        /// </param>
        /// <param name="flatteningTolerance">
        /// The flattening tolerance to be used in determining the geometric representation.
        /// </param>
        /// <param name="geometrySink">
        /// The geometry sink to which the geometry representation will be streamed.
        /// </param>
        void StreamAsGeometry(ID2D1InkStyle* inkStyle, const D2D1_MATRIX_3X2_F* worldTransform, FLOAT flatteningTolerance, ID2D1SimplifiedGeometrySink* geometrySink ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->StreamAsGeometry( inkStyle, worldTransform, flatteningTolerance, geometrySink );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void StreamAsGeometry( ID2D1InkStyle* inkStyle, const D2D1_MATRIX_3X2_F& worldTransform, FLOAT flatteningTolerance, ID2D1SimplifiedGeometrySink* geometrySink ) const
        {
            StreamAsGeometry( inkStyle, &worldTransform, flatteningTolerance, geometrySink );
        }
        void StreamAsGeometry( const InkStyle& inkStyle, const D2D1_MATRIX_3X2_F* worldTransform, FLOAT flatteningTolerance, ID2D1SimplifiedGeometrySink* geometrySink ) const
        {
            StreamAsGeometry( inkStyle.GetInterfacePointer<ID2D1InkStyle>( ), worldTransform, flatteningTolerance, geometrySink );
        }
        void StreamAsGeometry( const InkStyle& inkStyle, const D2D1_MATRIX_3X2_F& worldTransform, FLOAT flatteningTolerance, ID2D1SimplifiedGeometrySink* geometrySink ) const
        {
            StreamAsGeometry( inkStyle.GetInterfacePointer<ID2D1InkStyle>( ), &worldTransform, flatteningTolerance, geometrySink );
        }
        void StreamAsGeometry( const D2D1_MATRIX_3X2_F* worldTransform, FLOAT flatteningTolerance, ID2D1SimplifiedGeometrySink* geometrySink ) const
        {
            StreamAsGeometry( nullptr, worldTransform, flatteningTolerance, geometrySink );
        }
        void StreamAsGeometry( const D2D1_MATRIX_3X2_F& worldTransform, FLOAT flatteningTolerance, ID2D1SimplifiedGeometrySink* geometrySink ) const
        {
            StreamAsGeometry( nullptr, worldTransform, flatteningTolerance, geometrySink );
        }
        void StreamAsGeometry( ID2D1InkStyle* inkStyle, const D2D1_MATRIX_3X2_F* worldTransform, ID2D1SimplifiedGeometrySink* geometrySink ) const
        {
            StreamAsGeometry( inkStyle, worldTransform, D2D1_DEFAULT_FLATTENING_TOLERANCE, geometrySink );
        }
        void StreamAsGeometry( ID2D1InkStyle* inkStyle, const D2D1_MATRIX_3X2_F& worldTransform, ID2D1SimplifiedGeometrySink* geometrySink ) const
        {
            StreamAsGeometry( inkStyle, &worldTransform, D2D1_DEFAULT_FLATTENING_TOLERANCE, geometrySink );
        }
        void StreamAsGeometry( const InkStyle& inkStyle, const D2D1_MATRIX_3X2_F* worldTransform, ID2D1SimplifiedGeometrySink* geometrySink ) const
        {
            StreamAsGeometry( inkStyle.GetInterfacePointer<ID2D1InkStyle>( ), worldTransform, D2D1_DEFAULT_FLATTENING_TOLERANCE, geometrySink );
        }
        void StreamAsGeometry( const InkStyle& inkStyle, const D2D1_MATRIX_3X2_F& worldTransform, ID2D1SimplifiedGeometrySink* geometrySink ) const
        {
            StreamAsGeometry( inkStyle.GetInterfacePointer<ID2D1InkStyle>( ), &worldTransform, D2D1_DEFAULT_FLATTENING_TOLERANCE, geometrySink );
        }
        void StreamAsGeometry( const D2D1_MATRIX_3X2_F* worldTransform, ID2D1SimplifiedGeometrySink* geometrySink ) const
        {
            StreamAsGeometry( nullptr, worldTransform, D2D1_DEFAULT_FLATTENING_TOLERANCE, geometrySink );
        }
        void StreamAsGeometry( const D2D1_MATRIX_3X2_F& worldTransform, ID2D1SimplifiedGeometrySink* geometrySink ) const
        {
            StreamAsGeometry( nullptr, worldTransform, D2D1_DEFAULT_FLATTENING_TOLERANCE, geometrySink );
        }

        void StreamAsGeometry( ID2D1InkStyle* inkStyle, FLOAT flatteningTolerance, ID2D1SimplifiedGeometrySink* geometrySink ) const
        {
            StreamAsGeometry( inkStyle, nullptr, flatteningTolerance, geometrySink );
        }
        void StreamAsGeometry( const InkStyle& inkStyle, FLOAT flatteningTolerance, ID2D1SimplifiedGeometrySink* geometrySink ) const
        {
            StreamAsGeometry( inkStyle.GetInterfacePointer<ID2D1InkStyle>( ), nullptr, flatteningTolerance, geometrySink );
        }
        void StreamAsGeometry( FLOAT flatteningTolerance, ID2D1SimplifiedGeometrySink* geometrySink ) const
        {
            StreamAsGeometry( nullptr, nullptr, flatteningTolerance, geometrySink );
        }
        void StreamAsGeometry( ID2D1InkStyle* inkStyle, ID2D1SimplifiedGeometrySink* geometrySink ) const
        {
            StreamAsGeometry( inkStyle, nullptr, D2D1_DEFAULT_FLATTENING_TOLERANCE, geometrySink );
        }
        void StreamAsGeometry( const InkStyle& inkStyle, ID2D1SimplifiedGeometrySink* geometrySink ) const
        {
            StreamAsGeometry( inkStyle.GetInterfacePointer<ID2D1InkStyle>( ), nullptr, D2D1_DEFAULT_FLATTENING_TOLERANCE, geometrySink );
        }
        void StreamAsGeometry( ID2D1SimplifiedGeometrySink* geometrySink ) const
        {
            StreamAsGeometry( nullptr, nullptr, D2D1_DEFAULT_FLATTENING_TOLERANCE, geometrySink );
        }


        /// <summary>
        /// Retrieve the bounds of the ink, with an optional applied transform.
        /// </summary>
        /// <param name="inkStyle">
        /// The ink style to be used in determining the bounds of this ink object.
        /// </param>
        /// <param name="worldTransform">
        /// The world transform to be used in determining the bounds of this ink object.
        /// </param>
        /// <param name="bounds">
        /// When this method returns, contains the bounds of this ink object.
        /// </param>
        void GetBounds(ID2D1InkStyle* inkStyle, const D2D1_MATRIX_3X2_F* worldTransform,  D2D1_RECT_F* bounds ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetBounds( inkStyle, worldTransform, bounds );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void GetBounds( const InkStyle& inkStyle, const D2D1_MATRIX_3X2_F* worldTransform, D2D1_RECT_F* bounds ) const
        {
            GetBounds( inkStyle.GetInterfacePointer<ID2D1InkStyle>( ), worldTransform, bounds );
        }
        void GetBounds( ID2D1InkStyle* inkStyle, const D2D1_MATRIX_3X2_F& worldTransform, D2D1_RECT_F& bounds ) const
        {
            GetBounds( inkStyle, &worldTransform, &bounds );
        }
        void GetBounds( const InkStyle& inkStyle, const D2D1_MATRIX_3X2_F& worldTransform, D2D1_RECT_F& bounds ) const
        {
            GetBounds( inkStyle.GetInterfacePointer<ID2D1InkStyle>( ), &worldTransform, &bounds );
        }
        void GetBounds( ID2D1InkStyle* inkStyle, D2D1_RECT_F* bounds ) const
        {
            GetBounds( inkStyle, nullptr, bounds );
        }
        void GetBounds( const InkStyle& inkStyle, D2D1_RECT_F* bounds ) const
        {
            GetBounds( inkStyle.GetInterfacePointer<ID2D1InkStyle>( ), nullptr, bounds );
        }
        void GetBounds( ID2D1InkStyle* inkStyle, D2D1_RECT_F& bounds ) const
        {
            GetBounds( inkStyle, nullptr, &bounds );
        }
        void GetBounds( const InkStyle& inkStyle, D2D1_RECT_F& bounds ) const
        {
            GetBounds( inkStyle.GetInterfacePointer<ID2D1InkStyle>( ), nullptr, &bounds );
        }
        void GetBounds( D2D1_RECT_F* bounds ) const
        {
            GetBounds( nullptr, nullptr, bounds );
        }
        void GetBounds( D2D1_RECT_F& bounds ) const
        {
            GetBounds( nullptr, nullptr, &bounds );
        }

    };

    /// <summary>
    /// Represents a device-dependent representation of a 
    /// gradient mesh composed of patches. Use the 
    /// DeviceContext2::CreateGradientMesh function to create an 
    /// instance of GradientMesh.
    /// </summary>
    class GradientMesh : public Resource
    {
    public:
        using Base = Resource;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( GradientMesh, Base, ID2D1GradientMesh, ID2D1Resource )
    public:
        /// <summary>
        /// Returns the number of patches of the gradient mesh.
        /// </summary>
        /// <returns>
        /// Returns the number of patches that make up this gradient mesh.
        /// </returns>
        UINT32 GetPatchCount( ) const
        {
            auto* pInterface = GetInterface( );
            return pInterface->GetPatchCount( );
        }

        /// <summary>
        /// Retrieve the patch data stored in the gradient mesh.
        /// </summary>
        /// <param name="startIndex">
        /// Index of the first patch to return.
        /// </param>
        /// <param name="patches">
        /// A pointer to the array to be filled with the patch data.
        /// </param>
        /// <param name="patchesCount">
        /// The number of patches to be returned.
        /// </param>
        void GetPatches( UINT32 startIndex, D2D1_GRADIENT_MESH_PATCH* patches, UINT32 patchesCount ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetPatches( startIndex, patches, patchesCount );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    /// <summary>
    /// Represents a producer of pixels that can fill an arbitrary 2D plane.
    /// </summary>
    class ImageSource : public Image
    {
    public:
        using Base = Image;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( ImageSource, Base, ID2D1ImageSource, ID2D1Image )
    public:
        /// <summary>
        /// Allows the operating system to free the video memory of 
        /// resources by discarding their content.
        /// </summary>
        void OfferResources( ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->OfferResources( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Restores access to resources that were previously offered by 
        /// calling OfferResources.
        /// </summary>
        /// <param name="resourcesDiscarded">
        /// Returns with TRUE if the corresponding resource’s content was 
        /// discarded and is now undefined, or FALSE if the corresponding 
        /// resource’s old content is still intact. The caller can pass in 
        /// nullptr, if the caller intends to fill the resources with new 
        /// content regardless of whether the old content was discarded.
        /// </param>
        void TryReclaimResources( BOOL* resourcesDiscarded = nullptr ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->TryReclaimResources( resourcesDiscarded );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        bool TryReclaimResources( ) const
        {
            BOOL result = FALSE;
            TryReclaimResources( &result );
            return result != FALSE;
        }
    };

    /// <summary>
    /// Produces 2D pixel data that has been sourced from WIC.
    /// </summary>
    class ImageSourceFromWic : public ImageSource
    {
    public:
        using Base = ImageSource;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( ImageSourceFromWic, Base, ID2D1ImageSourceFromWic, ID2D1ImageSource )
    public:
        /// <summary>
        /// Ensures that a specified region of the image source cache is populated. 
        /// This method can be used to minimize glitches by performing expensive 
        /// work to populate caches outside of a rendering loop. This method can 
        /// also be used to speculatively load image data before it is needed by 
        /// drawing routines.
        /// </summary>
        /// <param name="rectangleToFill">
        /// Specifies the region of the image, in pixels, that should be populated 
        /// in the cache. By default, this is the entire extent of the image.
        /// </param>
        /// <remarks>
        /// <p>
        /// This API loads image data into caches of image sources, if that data was 
        /// not already cached. It does not trim pre-existing caches, if any.
        /// </p>
        /// <p>
        /// More areas within the cache can be populated than actually requested.
        /// </p>
        /// <p>
        /// The provided region must be constructed to include the scale with which 
        /// the image source will subsequently be drawn.
        /// </p>
        /// <p>
        /// These coordinates must be provided in local coordinates.
        /// </p>
        /// <p>
        /// This means that they must be adjusted prior to calling the API according 
        /// to the DPI and other relevant transforms, which can include the world 
        /// transform and brush transforms.
        /// </p>
        /// <p>
        /// This operation is only supported when the image source has been initialized 
        /// using the D2D1_IMAGE_SOURCE_LOADING_OPTIONS_CACHE_ON_DEMAND option.
        /// </p>
        /// </remarks>
        void EnsureCached( const D2D1_RECT_U* rectangleToFill = nullptr ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->EnsureCached( rectangleToFill );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void EnsureCached( const D2D1_RECT_U& rectangleToFill ) const
        {
            EnsureCached( &rectangleToFill );
        }


        /// <summary>
        /// This method trims the populated regions of the image source cache to just 
        /// the specified rectangle.
        /// </summary>
        /// <param name="rectangleToPreserve">
        /// Specifies the region of the image, in pixels, which should be preserved in 
        /// the image source cache. Regions which are outside of the rectangle are 
        /// evicted from the cache. By default, this is an empty rectangle, meaning 
        /// that the entire image is evicted from the cache.
        /// </param>
        /// <remarks>
        /// <p>
        /// The provided region must be constructed to include the scale at which the 
        /// image source will be drawn at. These coordinates must be provided in local 
        /// coordinates.
        /// </p>
        /// <p>
        /// This means that they must be adjusted prior to calling the API according to 
        /// the DPI and other relevant transforms, which can include the world transform 
        /// and brush transforms.
        /// </p>
        /// <p>
        /// This method will fail if on - demand caching was not requested when the 
        /// image source was created.
        /// </p>
        /// <p>
        /// As with Device::ClearResources, the caller can need to subsequently issue 
        /// a D3D flush before memory usage is reduced.
        /// </p>
        /// <p>
        /// This operation is only supported when the image source has been initialized 
        /// using the D2D1_IMAGE_SOURCE_LOADING_OPTIONS_CACHE_ON_DEMAND option.
        /// </p>
        /// </remarks>
        void TrimCache( const D2D1_RECT_U* rectangleToPreserve ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->TrimCache( rectangleToPreserve );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void TrimCache( const D2D1_RECT_U& rectangleToPreserve ) const
        {
            TrimCache( &rectangleToPreserve );
        }

        /// <summary>
        /// Retrieves the underlying bitmap image source from the Windows Imaging 
        /// Component (WIC)
        /// </summary>
        /// <param name="wicBitmapSource">
        /// On return contains the bitmap image source.
        /// </param>
        void GetSource( IWICBitmapSource** wicBitmapSource ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->GetSource( wicBitmapSource );
        }
        HW_EXPORT Imaging::BitmapSource GetSource( ) const;

    };


    /// <summary>
    /// Represents an image source which shares resources with an original image source.
    /// </summary>
    class TransformedImageSource : public Image
    {
    public:
        using Base = Image;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( TransformedImageSource, Base, ID2D1TransformedImageSource, ID2D1Image )
    public:
        /// <summary>
        /// Retrieves the source image used to create the transformed image source. 
        /// This value corresponds to the value passed to CreateTransformedImageSource.
        /// </summary>
        /// <param name="imageSource">
        /// The source image used to create the transformed image source.
        /// </param>
        void GetSource( ID2D1ImageSource** imageSource ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->GetSource( imageSource );
        }
        ImageSource GetSource( ) const
        {
            ID2D1ImageSource* ptr = nullptr;
            GetSource( &ptr );
            return ImageSource( ptr );
        }

        /// <summary>
        /// Retrieves the properties specified when the transformed image source 
        /// was created. This value corresponds to the value passed to 
        /// CreateTransformedImageSource.
        /// </summary>
        /// <param name="properties">
        /// The properties specified when the transformed image source was created.
        /// </param>
        void GetProperties( D2D1_TRANSFORMED_IMAGE_SOURCE_PROPERTIES* properties ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->GetProperties( properties );
        }
        void GetProperties( D2D1_TRANSFORMED_IMAGE_SOURCE_PROPERTIES& properties ) const
        {
            GetProperties( &properties );
        }
    };

    /// <summary>
    /// A container for 3D lookup table data that can be passed to the LookupTable3D
    /// effect.
    /// </summary>
    /// <remarks>
    /// An LookupTable3D instance is created using DeviceContext2::CreateLookupTable3D 
    /// or EffectContext1::CreateLookupTable3D.
    /// </remarks>
    class LookupTable3D : public Resource
    {
    public:
        using Base = Resource;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( LookupTable3D, Base, ID2D1LookupTable3D, ID2D1Resource )
    public:
        
    };


    /// <summary>
    /// This interface performs all the same functions as the ID2D1DeviceContext1
    /// interface, plus it enables functionality such as ink rendering, gradient mesh
    /// rendering, and improved image loading.
    /// </summary>
    class DeviceContext2 : public DeviceContext1
    {
    public:
        using Base = DeviceContext1;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( DeviceContext2, Base, ID2D1DeviceContext2, ID2D1DeviceContext1 )
    public:

        /// <summary>
        /// Creates a new ID2D1Ink object that starts at the given point.
        /// </summary>
        /// <param name="startPoint">
        /// The starting point of the first segment of the first stroke in the new ink object.
        /// </param>
        /// <param name="ink">
        /// When this method returns, contains the address of a pointer to a new ink object.
        /// </param>
        void CreateInk( const D2D1_INK_POINT* startPoint, ID2D1Ink** ink ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateInk( startPoint, ink );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void CreateInk( const D2D1_INK_POINT& startPoint, ID2D1Ink** ink ) const
        {
            CreateInk( &startPoint, ink );
        }
        Ink CreateInk( const D2D1_INK_POINT* startPoint ) const
        {
            ID2D1Ink* ptr = nullptr;
            CreateInk( startPoint, &ptr );
            return Ink( ptr );
        }
        Ink CreateInk( const D2D1_INK_POINT& startPoint ) const
        {
            return CreateInk( &startPoint );
        }

        /// <summary>
        /// Creates a new ID2D1InkStyle object, for use with ink 
        /// rendering methods such as DrawInk.
        /// </summary>
        /// <param name="inkStyleProperties">
        /// The properties of the ink style to be created.
        /// </param>
        /// <param name="inkStyle">
        /// When this method returns, contains the address of a 
        /// pointer to a new ink style object.
        /// </param>
        void CreateInkStyle( const D2D1_INK_STYLE_PROPERTIES* inkStyleProperties, ID2D1InkStyle** inkStyle ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateInkStyle( inkStyleProperties, inkStyle );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void CreateInkStyle( const D2D1_INK_STYLE_PROPERTIES& inkStyleProperties, ID2D1InkStyle** inkStyle ) const
        {
            CreateInkStyle( &inkStyleProperties, inkStyle );
        }
        void CreateInkStyle( ID2D1InkStyle** inkStyle ) const
        {
            CreateInkStyle( nullptr, inkStyle );
        }

        InkStyle CreateInkStyle( const D2D1_INK_STYLE_PROPERTIES* inkStyleProperties = nullptr) const
        {
            ID2D1InkStyle* ptr = nullptr;
            CreateInkStyle( inkStyleProperties, &ptr );
            return InkStyle( ptr );
        }
        InkStyle CreateInkStyle( const D2D1_INK_STYLE_PROPERTIES& inkStyleProperties ) const
        {
            return CreateInkStyle( &inkStyleProperties );
        }

        /// <summary>
        /// Creates a new GradientMesh (ID2D1GradientMesh) instance 
        /// using the given array of patches.
        /// </summary>
        /// <param name="patches">
        /// A pointer to the array containing the patches to be used in this mesh.
        /// </param>
        /// <param name="patchesCount">
        /// The number of patches in the patches argument to read.
        /// </param>
        /// <param name="gradientMesh">
        /// When this method returns, contains the address of a pointer 
        /// to the new gradient mesh.
        /// </param>
        void CreateGradientMesh( const D2D1_GRADIENT_MESH_PATCH* patches, UINT32 patchesCount, ID2D1GradientMesh** gradientMesh ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateGradientMesh( patches, patchesCount, gradientMesh );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        GradientMesh CreateGradientMesh( const D2D1_GRADIENT_MESH_PATCH* patches, UINT32 patchesCount ) const
        {
            ID2D1GradientMesh* ptr = nullptr;
            CreateGradientMesh( patches, patchesCount, &ptr );
            return GradientMesh( ptr );
        }

        /// <summary>
        /// <p>
        /// Creates an image source object from a WIC bitmap source, while populating 
        /// all pixel memory within the image source.
        /// </p>
        /// <p>
        /// The image is loadedand stored while using a minimal amount of memory.
        /// </p>
        /// </summary>
        /// <param name="wicBitmapSource">
        /// The WIC bitmap source to create the image source from.
        /// </param>
        /// <param name="loadingOptions">
        /// Options for creating the image source. Default options are used if 
        /// D2D1_IMAGE_SOURCE_LOADING_OPTIONS_NONE is passed.
        /// </param>
        /// <param name="alphaMode">
        /// The alpha mode of the image; this is determined automatically from 
        /// the source’s pixel format if D2D1_ALPHA_MODE_UNKNOWN is passed.
        /// </param>
        /// <param name="imageSource">
        /// 
        /// </param>
        void CreateImageSourceFromWic( IWICBitmapSource* wicBitmapSource, D2D1_IMAGE_SOURCE_LOADING_OPTIONS loadingOptions, D2D1_ALPHA_MODE alphaMode, ID2D1ImageSourceFromWic** imageSource ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateImageSourceFromWic( wicBitmapSource, loadingOptions, alphaMode, imageSource );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        HW_EXPORT void CreateImageSourceFromWic( const Imaging::BitmapSource& wicBitmapSource, D2D1_IMAGE_SOURCE_LOADING_OPTIONS loadingOptions, D2D1_ALPHA_MODE alphaMode, ID2D1ImageSourceFromWic** imageSource ) const;

        ImageSourceFromWic CreateImageSourceFromWic( IWICBitmapSource* wicBitmapSource, D2D1_IMAGE_SOURCE_LOADING_OPTIONS loadingOptions = D2D1_IMAGE_SOURCE_LOADING_OPTIONS_NONE, D2D1_ALPHA_MODE alphaMode = D2D1_ALPHA_MODE_UNKNOWN ) const
        {
            ID2D1ImageSourceFromWic* ptr = nullptr;
            CreateImageSourceFromWic( wicBitmapSource, loadingOptions, alphaMode, &ptr );
            return ImageSourceFromWic( ptr );
        }
        HW_EXPORT ImageSourceFromWic CreateImageSourceFromWic( const Imaging::BitmapSource& wicBitmapSource, D2D1_IMAGE_SOURCE_LOADING_OPTIONS loadingOptions = D2D1_IMAGE_SOURCE_LOADING_OPTIONS_NONE, D2D1_ALPHA_MODE alphaMode = D2D1_ALPHA_MODE_UNKNOWN ) const;


        /// <summary>
        /// Creates a 3D lookup table for mapping a 3-channel input to a 3-channel output. 
        /// The table data must be provided in 4-channel format.
        /// </summary>
        /// <param name="precision">
        /// Precision of the input lookup table data.
        /// </param>
        /// <param name="extents">
        /// Number of lookup table elements per dimension (X, Y, Z).
        /// </param>
        /// <param name="data">
        /// Buffer holding the lookup table data.
        /// </param>
        /// <param name="dataCount">
        /// Size of the lookup table data buffer.
        /// </param>
        /// <param name="strides">
        /// <p>
        /// An array containing two values. The first value is the size in bytes from 
        /// one row (X dimension) of LUT data to the next.
        /// </p>
        /// <p>
        /// The second value is the size in bytes from one LUT data plane( Xand Y dimensions ) 
        /// to the next.
        /// </p>
        /// </param>
        /// <param name="lookupTable">
        /// Receives the new lookup table instance.
        /// </param>
        void CreateLookupTable3D( D2D1_BUFFER_PRECISION precision, const UINT32* extents, const BYTE* data, UINT32 dataCount, const UINT32* strides, ID2D1LookupTable3D** lookupTable ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateLookupTable3D( precision, extents, data, dataCount, strides, lookupTable );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        LookupTable3D CreateLookupTable3D( D2D1_BUFFER_PRECISION precision, const UINT32* extents, const BYTE* data, UINT32 dataCount, const UINT32* strides ) const
        {
            ID2D1LookupTable3D* ptr = nullptr;
            CreateLookupTable3D( precision, extents, data, dataCount, strides, &ptr );
            return LookupTable3D( ptr );
        }

        /// <summary>
        /// Creates an image source from a set of DXGI surface(s). The YCbCr surface(s) 
        /// are converted to RGBA automatically during subsequent drawing.
        /// </summary>
        /// <param name="surfaces">
        /// The DXGI surfaces to create the image source from.
        /// </param>
        /// <param name="surfaceCount">
        /// The number of surfaces provided; must be between one and three.
        /// </param>
        /// <param name="colorSpace">
        /// The color space of the input.
        /// </param>
        /// <param name="options">
        /// Options controlling color space conversions.
        /// </param>
        /// <param name="imageSource">
        /// Receives the new image source instance.
        /// </param>
        void CreateImageSourceFromDxgi( IDXGISurface** surfaces, UINT32 surfaceCount, DXGI_COLOR_SPACE_TYPE colorSpace, D2D1_IMAGE_SOURCE_FROM_DXGI_OPTIONS options, ID2D1ImageSource** imageSource ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateImageSourceFromDxgi( surfaces, surfaceCount, colorSpace, options, imageSource );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        ImageSource CreateImageSourceFromDxgi( IDXGISurface** surfaces, UINT32 surfaceCount, DXGI_COLOR_SPACE_TYPE colorSpace = DXGI_COLOR_SPACE_RGB_FULL_G22_NONE_P709, D2D1_IMAGE_SOURCE_FROM_DXGI_OPTIONS options = D2D1_IMAGE_SOURCE_FROM_DXGI_OPTIONS_NONE ) const
        {
            ID2D1ImageSource* ptr = nullptr;
            CreateImageSourceFromDxgi( surfaces, surfaceCount, colorSpace, options, &ptr );
            return ImageSource( ptr );
        }

        ImageSource CreateImageSourceFromDxgi( const DXGI::Surface& surface, DXGI_COLOR_SPACE_TYPE colorSpace = DXGI_COLOR_SPACE_RGB_FULL_G22_NONE_P709, D2D1_IMAGE_SOURCE_FROM_DXGI_OPTIONS options = D2D1_IMAGE_SOURCE_FROM_DXGI_OPTIONS_NONE ) const
        {
            ID2D1ImageSource* ptr = nullptr;
            IDXGISurface* surfaces[1] = { surface.GetInterfacePointer<IDXGISurface>( ) };
            CreateImageSourceFromDxgi( surfaces, 1, colorSpace, options, &ptr );
            return ImageSource( ptr );
        }
        ImageSource CreateImageSourceFromDxgi( const DXGI::Surface* surfaces, UINT32 surfaceCount, DXGI_COLOR_SPACE_TYPE colorSpace = DXGI_COLOR_SPACE_RGB_FULL_G22_NONE_P709, D2D1_IMAGE_SOURCE_FROM_DXGI_OPTIONS options = D2D1_IMAGE_SOURCE_FROM_DXGI_OPTIONS_NONE ) const
        {
            static_assert( sizeof( DXGI::Surface ) == sizeof( IDXGISurface* ) );
            ID2D1ImageSource* ptr = nullptr;
            CreateImageSourceFromDxgi( reinterpret_cast<IDXGISurface**>( const_cast<DXGI::Surface*>( surfaces ) ), surfaceCount, colorSpace, options, &ptr );
            return ImageSource( ptr );
        }



        /// <summary>
        /// Retrieves the world-space bounds in DIPs of the gradient mesh using the device
        /// context DPI.
        /// </summary>
        /// <param name="gradientMesh">
        /// Returns the world bounds of a given gradient mesh.
        /// </param>
        /// <param name="bounds">
        /// 
        /// </param>
        void GetGradientMeshWorldBounds( ID2D1GradientMesh* gradientMesh, D2D1_RECT_F* bounds ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetGradientMeshWorldBounds( gradientMesh, bounds );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void GetGradientMeshWorldBounds( ID2D1GradientMesh* gradientMesh, D2D1_RECT_F& bounds ) const
        {
            GetGradientMeshWorldBounds( gradientMesh, &bounds );
        }
        void GetGradientMeshWorldBounds( const GradientMesh& gradientMesh, D2D1_RECT_F* bounds ) const
        {
            GetGradientMeshWorldBounds( gradientMesh.GetInterfacePointer<ID2D1GradientMesh>( ), bounds );
        }
        void GetGradientMeshWorldBounds( const GradientMesh& gradientMesh, D2D1_RECT_F& bounds ) const
        {
            GetGradientMeshWorldBounds( gradientMesh.GetInterfacePointer<ID2D1GradientMesh>( ), &bounds );
        }

        /// <summary>
        /// Renders the given ink object using the given brush and ink style.
        /// </summary>
        /// <param name="ink">
        /// The ink object to be rendered.
        /// </param>
        /// <param name="brush">
        /// The brush with which to render the ink object.
        /// </param>
        /// <param name="inkStyle">
        /// The ink style to use when rendering the ink object.
        /// </param>
        void DrawInk( ID2D1Ink* ink, ID2D1Brush* brush, ID2D1InkStyle* inkStyle = nullptr ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->DrawInk( ink, brush, inkStyle );
        }
        void DrawInk( const Ink& ink, ID2D1Brush* brush, ID2D1InkStyle* inkStyle = nullptr ) const
        {
            DrawInk( ink.GetInterfacePointer<ID2D1Ink>( ), brush, inkStyle );
        }
        void DrawInk( const Ink& ink, const Brush& brush, ID2D1InkStyle* inkStyle = nullptr ) const
        {
            DrawInk( ink.GetInterfacePointer<ID2D1Ink>( ), brush.GetInterfacePointer<ID2D1Brush>( ), inkStyle );
        }
        void DrawInk( const Ink& ink, const Brush& brush, const InkStyle& inkStyle ) const
        {
            DrawInk( ink.GetInterfacePointer<ID2D1Ink>( ), brush.GetInterfacePointer<ID2D1Brush>( ), inkStyle.GetInterfacePointer<ID2D1InkStyle>( ) );
        }


        /// <summary>
        /// Renders a given gradient mesh to the target.
        /// </summary>
        /// <param name="gradientMesh">
        /// The gradient mesh to be rendered.
        /// </param>
        void DrawGradientMesh( ID2D1GradientMesh* gradientMesh ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->DrawGradientMesh( gradientMesh );
        }
        void DrawGradientMesh( const GradientMesh& gradientMesh ) const
        {
            DrawGradientMesh( gradientMesh.GetInterfacePointer<ID2D1GradientMesh>( ) );
        }

        /// <summary>
        /// Draws a metafile to the device context using the given source 
        /// and destination rectangles.
        /// </summary>
        /// <param name="gdiMetafile">
        /// The metafile to draw.
        /// </param>
        /// <param name="destinationRectangle">
        /// The rectangle in the target where the metafile will be drawn, 
        /// relative to the upper left corner (defined in DIPs) of the 
        /// render target. If NULL is specified, the destination rectangle 
        /// is {0, 0, w, h}, where w and h are the width and height of the 
        /// metafile as reported by ID2D1GdiMetafile::GetBounds.
        /// </param>
        /// <param name="sourceRectangle">
        /// The rectangle of the source metafile that will be drawn, relative 
        /// to the upper left corner (defined in DIPs) of the metafile. 
        /// If nullptr is specified, the source rectangle is the value 
        /// returned by ID2D1GdiMetafile1::GetSourceBounds.
        /// </param>
        void DrawGdiMetafile( ID2D1GdiMetafile* gdiMetafile, const D2D1_RECT_F* destinationRectangle = nullptr, const D2D1_RECT_F* sourceRectangle = nullptr ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->DrawGdiMetafile( gdiMetafile, destinationRectangle, sourceRectangle );
        }
        void DrawGdiMetafile( const GdiMetafile& gdiMetafile, const D2D1_RECT_F* destinationRectangle = nullptr, const D2D1_RECT_F* sourceRectangle = nullptr ) const
        {
            DrawGdiMetafile( gdiMetafile.GetInterfacePointer<ID2D1GdiMetafile>( ), destinationRectangle, sourceRectangle );
        }
        void DrawGdiMetafile( ID2D1GdiMetafile* gdiMetafile, const D2D1_RECT_F& destinationRectangle, const D2D1_RECT_F* sourceRectangle = nullptr ) const
        {
            DrawGdiMetafile( gdiMetafile, &destinationRectangle, sourceRectangle );
        }
        void DrawGdiMetafile( const GdiMetafile& gdiMetafile, const D2D1_RECT_F& destinationRectangle, const D2D1_RECT_F* sourceRectangle = nullptr ) const
        {
            DrawGdiMetafile( gdiMetafile.GetInterfacePointer<ID2D1GdiMetafile>( ), &destinationRectangle, sourceRectangle );
        }
        void DrawGdiMetafile( ID2D1GdiMetafile* gdiMetafile, const D2D1_RECT_F& destinationRectangle, const D2D1_RECT_F& sourceRectangle ) const
        {
            DrawGdiMetafile( gdiMetafile, &destinationRectangle, &sourceRectangle );
        }
        void DrawGdiMetafile( const GdiMetafile& gdiMetafile, const D2D1_RECT_F& destinationRectangle, const D2D1_RECT_F& sourceRectangle ) const
        {
            DrawGdiMetafile( gdiMetafile.GetInterfacePointer<ID2D1GdiMetafile>( ), &destinationRectangle, &sourceRectangle );
        }

        using Base::DrawGdiMetafile;

        /// <summary>
        /// Creates an image source which shares resources with an original.
        /// </summary>
        /// <param name="imageSource">
        /// The original image.
        /// </param>
        /// <param name="properties">
        /// Properties for the source image.
        /// </param>
        /// <param name="transformedImageSource">
        /// Receives the new image source.
        /// </param>
        void CreateTransformedImageSource( ID2D1ImageSource* imageSource, const D2D1_TRANSFORMED_IMAGE_SOURCE_PROPERTIES* properties, ID2D1TransformedImageSource** transformedImageSource ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateTransformedImageSource( imageSource, properties, transformedImageSource );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void CreateTransformedImageSource( ID2D1ImageSource* imageSource, const D2D1_TRANSFORMED_IMAGE_SOURCE_PROPERTIES& properties, ID2D1TransformedImageSource** transformedImageSource ) const
        {
            CreateTransformedImageSource( imageSource, &properties, transformedImageSource );
        }
        void CreateTransformedImageSource( const ImageSource& imageSource, const D2D1_TRANSFORMED_IMAGE_SOURCE_PROPERTIES* properties, ID2D1TransformedImageSource** transformedImageSource ) const
        {
            CreateTransformedImageSource( imageSource.GetInterfacePointer<ID2D1ImageSource>( ), properties, transformedImageSource );
        }
        void CreateTransformedImageSource( const ImageSource& imageSource, const D2D1_TRANSFORMED_IMAGE_SOURCE_PROPERTIES& properties, ID2D1TransformedImageSource** transformedImageSource ) const
        {
            CreateTransformedImageSource( imageSource.GetInterfacePointer<ID2D1ImageSource>( ), &properties, transformedImageSource );
        }
        TransformedImageSource CreateTransformedImageSource( ID2D1ImageSource* imageSource, const D2D1_TRANSFORMED_IMAGE_SOURCE_PROPERTIES* properties ) const
        {
            ID2D1TransformedImageSource* ptr = nullptr;
            CreateTransformedImageSource( imageSource, properties, &ptr );
            return TransformedImageSource( ptr );
        }
        TransformedImageSource CreateTransformedImageSource( ID2D1ImageSource* imageSource, const D2D1_TRANSFORMED_IMAGE_SOURCE_PROPERTIES& properties ) const
        {
            return CreateTransformedImageSource( imageSource, &properties );
        }

        TransformedImageSource CreateTransformedImageSource( const ImageSource& imageSource, const D2D1_TRANSFORMED_IMAGE_SOURCE_PROPERTIES* properties ) const
        {
            return CreateTransformedImageSource( imageSource.GetInterfacePointer<ID2D1ImageSource>( ), properties );
        }
        TransformedImageSource CreateTransformedImageSource( const ImageSource& imageSource, const D2D1_TRANSFORMED_IMAGE_SOURCE_PROPERTIES& properties ) const
        {
            return CreateTransformedImageSource( imageSource.GetInterfacePointer<ID2D1ImageSource>( ), &properties );
        }


    };

    /// <summary>
    /// Represents a resource domain whose objects and device contexts can be used
    /// together. This interface performs all the same functions as the existing
    /// ID2D1Device1 interface. It also enables the creation of ID2D1DeviceContext2
    /// objects.
    /// </summary>
    class Device2 : public Device1
    {
    public:
        using Base = Device1;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( Device2, Base, ID2D1Device2, ID2D1Device1 )
    public:
        /// <summary>
        /// Creates a new ID2D1DeviceContext2 from a Direct2D device with no initially assigned target.
        /// </summary>
        /// <param name="options">
        /// The options to be applied to the created device context.
        /// The default is D2D1_DEVICE_CONTEXT_OPTIONS_NONE.
        /// </param>
        /// <param name="deviceContext2">
        /// When this method returns, contains the address of a pointer to the new device context.
        /// </param>
        void CreateDeviceContext( D2D1_DEVICE_CONTEXT_OPTIONS options, ID2D1DeviceContext2** deviceContext2 ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateDeviceContext( options, deviceContext2 );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        DeviceContext2 CreateDeviceContext( D2D1_DEVICE_CONTEXT_OPTIONS options = D2D1_DEVICE_CONTEXT_OPTIONS_NONE ) const
        {
            ID2D1DeviceContext2* ptr = nullptr;
            CreateDeviceContext( options, &ptr );
            return DeviceContext2( ptr );
        }

        DeviceContext2 CreateDeviceContext2( D2D1_DEVICE_CONTEXT_OPTIONS options = D2D1_DEVICE_CONTEXT_OPTIONS_NONE ) const
        {
            return CreateDeviceContext( options );
        }


        /// <summary>
        /// Flush all device contexts that reference a given bitmap.
        /// </summary>
        /// <param name="bitmap">
        /// The bitmap, created on this device, for which all referencing device 
        /// contexts will be flushed.
        /// </param>
        void FlushDeviceContexts( ID2D1Bitmap* bitmap ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->FlushDeviceContexts( bitmap );
        }
        void FlushDeviceContexts( const Bitmap& bitmap ) const
        {
            FlushDeviceContexts( bitmap.GetInterfacePointer<ID2D1Bitmap>( ) );
        }

        /// <summary>
        /// Returns the DXGI device associated with this D2D device.
        /// </summary>
        /// <param name="dxgiDevice">
        /// The DXGI device associated with this Direct2D device.
        /// </param>
        void GetDxgiDevice(IDXGIDevice** dxgiDevice ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->GetDxgiDevice( dxgiDevice );
        }
        DXGI::Device GetDxgiDevice( ) const
        {
            IDXGIDevice* ptr = nullptr;
            GetDxgiDevice( &ptr );
            return DXGI::Device( ptr );
        }

    };


    /// <summary>
    /// Creates Direct2D resources. This interface also enables the creation of
    /// ID2D1Device2 objects.
    /// </summary>
    class Factory3 : public Factory2
    {
    public:
        using Base = Factory2;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( Factory3, Base, ID2D1Factory3, ID2D1Factory2 )
    public:
        Factory3( D2D1_FACTORY_TYPE factoryType )
        {
            ID2D1Factory3* d2d1Factory3 = nullptr;
            auto hr = D2D1CreateFactory( factoryType, __uuidof( ID2D1Factory3 ), (void**)&d2d1Factory3 );
            HCC_COM_CHECK_HRESULT( hr );
            unknown_ = d2d1Factory3;
        }

        /// <summary>
        /// This creates a new Direct2D device from the given IDXGIDevice.
        /// </summary>
        /// <param name="dxgiDevice">
        /// The IDXGIDevice object used when creating the ID2D1Device2.
        /// </param>
        /// <param name="d2dDevice2">
        /// The requested ID2D1Device2 object.
        /// </param>
        void CreateDevice( IDXGIDevice* dxgiDevice, ID2D1Device2** d2dDevice2 ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateDevice( dxgiDevice, d2dDevice2 );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void CreateDevice( const DXGI::Device& dxgiDevice, ID2D1Device2** d2dDevice2 ) const
        {
            CreateDevice( dxgiDevice.GetInterfacePointer<IDXGIDevice>( ), d2dDevice2 );
        }
        Device2 CreateDevice( IDXGIDevice* dxgiDevice ) const
        {
            ID2D1Device2* ptr = nullptr;
            CreateDevice( dxgiDevice, &ptr );
            return Device2( ptr );
        }
        Device2 CreateDevice( const DXGI::Device& dxgiDevice ) const
        {
            return Factory3::CreateDevice( dxgiDevice.GetInterfacePointer<IDXGIDevice>( ) );
        }

        Device2 CreateDevice2( _In_ IDXGIDevice* dxgiDevice ) const
        {
            return CreateDevice( dxgiDevice );
        }
        Device2 CreateDevice2( const DXGI::Device& dxgiDevice ) const
        {
            return CreateDevice( dxgiDevice );
        }

    };

    /// <summary>
    /// This interface performs all the same functions as the existing ID2D1CommandSink1
    /// interface. It also enables access to ink rendering and gradient mesh rendering.
    /// </summary>
    class CommandSink2 : public CommandSink1
    {
    public:
        using Base = CommandSink1;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( CommandSink2, Base, ID2D1CommandSink2, ID2D1CommandSink1 )
    public:
        /// <summary>
        /// Renders the given ink object using the given brush and ink style.
        /// </summary>
        /// <param name="ink">
        /// The ink object to be rendered.
        /// </param>
        /// <param name="brush">
        /// The brush with which to render the ink object.
        /// </param>
        /// <param name="inkStyle">
        /// The ink style to use when rendering the ink object.
        /// </param>
        void DrawInk( ID2D1Ink* ink, ID2D1Brush* brush, ID2D1InkStyle* inkStyle = nullptr ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->DrawInk( ink, brush, inkStyle );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void DrawInk( const Ink& ink, const Brush& brush, ID2D1InkStyle* inkStyle = nullptr ) const
        {
            DrawInk( ink.GetInterfacePointer<ID2D1Ink>( ), brush.GetInterfacePointer<ID2D1Brush>( ), inkStyle );
        }
        void DrawInk( const Ink& ink, const Brush& brush, const InkStyle& inkStyle ) const
        {
            DrawInk( ink.GetInterfacePointer<ID2D1Ink>( ), brush.GetInterfacePointer<ID2D1Brush>( ), inkStyle.GetInterfacePointer<ID2D1InkStyle>( ) );
        }



        /// <summary>
        /// Renders a given gradient mesh to the target.
        /// </summary>
        /// <param name="gradientMesh">
        /// The gradient mesh to be rendered.
        /// </param>
        void DrawGradientMesh(ID2D1GradientMesh* gradientMesh ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->DrawGradientMesh( gradientMesh );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void DrawGradientMesh( const GradientMesh& gradientMesh ) const
        {
            DrawGradientMesh( gradientMesh.GetInterfacePointer<ID2D1GradientMesh>( ) );
        }

        /// <summary>
        /// Draws a metafile to the command sink using the given source and destination rectangles.
        /// </summary>
        /// <param name="gdiMetafile">
        /// The metafile to draw.
        /// </param>
        /// <param name="destinationRectangle">
        /// The rectangle in the target where the metafile will be drawn, relative 
        /// to the upper left corner (defined in DIPs). If nullptr is specified, the 
        /// destination rectangle is the size of the target.
        /// </param>
        /// <param name="sourceRectangle">
        /// The rectangle of the source metafile that will be drawn, relative to the 
        /// upper left corner (defined in DIPs). If nullptr is specified, the source 
        /// rectangle is the value returned by ID2D1GdiMetafile1::GetSourceBounds.
        /// </param>
        void DrawGdiMetafile(ID2D1GdiMetafile* gdiMetafile,const D2D1_RECT_F* destinationRectangle = nullptr,const D2D1_RECT_F* sourceRectangle = nullptr ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->DrawGdiMetafile( gdiMetafile, destinationRectangle, sourceRectangle );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void DrawGdiMetafile( const GdiMetafile& gdiMetafile, const D2D1_RECT_F* destinationRectangle = nullptr, const D2D1_RECT_F* sourceRectangle = nullptr ) const
        {
            DrawGdiMetafile( gdiMetafile.GetInterfacePointer<ID2D1GdiMetafile>( ), destinationRectangle, sourceRectangle );
        }
        void DrawGdiMetafile( ID2D1GdiMetafile* gdiMetafile, const D2D1_RECT_F& destinationRectangle, const D2D1_RECT_F* sourceRectangle = nullptr ) const
        {
            DrawGdiMetafile( gdiMetafile, &destinationRectangle, sourceRectangle );
        }
        void DrawGdiMetafile( const GdiMetafile& gdiMetafile, const D2D1_RECT_F& destinationRectangle, const D2D1_RECT_F* sourceRectangle = nullptr ) const
        {
            DrawGdiMetafile( gdiMetafile.GetInterfacePointer<ID2D1GdiMetafile>( ), &destinationRectangle, sourceRectangle );
        }
        void DrawGdiMetafile( ID2D1GdiMetafile* gdiMetafile, const D2D1_RECT_F& destinationRectangle, const D2D1_RECT_F& sourceRectangle ) const
        {
            DrawGdiMetafile( gdiMetafile, &destinationRectangle, &sourceRectangle );
        }
        void DrawGdiMetafile( const GdiMetafile& gdiMetafile, const D2D1_RECT_F& destinationRectangle, const D2D1_RECT_F& sourceRectangle ) const
        {
            DrawGdiMetafile( gdiMetafile.GetInterfacePointer<ID2D1GdiMetafile>( ), &destinationRectangle, &sourceRectangle );
        }


        using Base::DrawGdiMetafile;

    };

    /// <summary>
    /// Interface encapsulating a GDI/GDI+ metafile.
    /// </summary>
    class GdiMetafile1 : public GdiMetafile
    {
    public:
        using Base = GdiMetafile;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( GdiMetafile1, Base, ID2D1GdiMetafile1, ID2D1GdiMetafile )
    public:
        /// <summary>
        /// Gets the DPI reported by the metafile.
        /// </summary>
        /// <param name="dpiX">
        /// Receives the horizontal DPI reported by the metafile.
        /// </param>
        /// <param name="dpiY">
        /// Receives the vertical DPI reported by the metafile.
        /// </param>
        void GetDpi( FLOAT* dpiX, FLOAT* dpiY ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetDpi( dpiX, dpiY );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void GetDpi( FLOAT& dpiX, FLOAT& dpiY ) const
        {
            GetDpi( dpiX, dpiY );
        }
        D2D1_SIZE_F GetDpi( ) const
        {
            D2D1_SIZE_F result{};
            GetDpi( &result.width, &result.height );
            return result;
        }

        /// <summary>
        /// Gets the bounds of the metafile in source space in DIPs. This corresponds
        /// to the frame rect in an EMF / EMF + .
        /// </summary>
        /// <param name="bounds">
        /// The bounds, in DIPs, of the metafile.
        /// </param>
        void GetSourceBounds( D2D1_RECT_F* bounds ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetSourceBounds( bounds );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void GetSourceBounds( D2D1_RECT_F& bounds ) const
        {
            GetSourceBounds( &bounds );
        }
    };

    /// <summary>
    /// This interface performs all the same functions as the existing 
    /// ID2D1GdiMetafileSink interface. It also enables access to metafile records.
    /// </summary>
    class GdiMetafileSink1: public GdiMetafileSink
    {
    public:
        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( GdiMetafileSink1, GdiMetafileSink, ID2D1GdiMetafileSink1, ID2D1GdiMetafileSink )

        /// <summary>
        /// Provides access to metafile records, including their type, data, and flags.
        /// </summary>
        /// <param name="recordType">
        /// The type of metafile record being processed. Please see 
        /// <a href="https://docs.microsoft.com/en-us/openspecs/windows_protocols/ms-emf">MS-EMF</a> and 
        /// <a href="https://docs.microsoft.com/en-us/openspecs/windows_protocols/ms-emfplus">MS-EMFPLUS</a> for a list of record types.
        /// </param>
        /// <param name="recordData">
        /// The data contained in this record. Please see 
        /// <a href="https://docs.microsoft.com/en-us/openspecs/windows_protocols/ms-emf">MS-EMF</a> and 
        /// <a href="https://docs.microsoft.com/en-us/openspecs/windows_protocols/ms-emfplus">MS-EMFPLUS</a> for a list of record layouts.
        /// </param>
        /// <param name="recordDataSize">
        /// The size of the data pointed to by recordData.
        /// </param>
        /// <param name="flags">
        /// The set of flags set for this record. Please see 
        /// <a href="https://docs.microsoft.com/en-us/openspecs/windows_protocols/ms-emf">MS-EMF</a> and 
        /// <a href="https://docs.microsoft.com/en-us/openspecs/windows_protocols/ms-emfplus">MS-EMFPLUS</a> for information on record flags.
        /// </param>
        void ProcessRecord( DWORD recordType, _In_opt_ CONST void* recordData, DWORD recordDataSize, UINT32 flags ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->ProcessRecord( recordType, recordData, recordDataSize, flags );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        using GdiMetafileSink::ProcessRecord;
    };


    /// <summary>
    /// Represents a single group of sprites with their associated drawing properties.
    /// </summary>
    class SpriteBatch : public Resource
    {
        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( SpriteBatch, Resource, ID2D1SpriteBatch, ID2D1Resource )

        /// <summary>
        /// Adds the given sprites to the end of this sprite batch.
        /// </summary>
        /// <param name="spriteCount">
        /// The number of sprites to be added. This determines how 
        /// many strides into each given array Direct2D will read.
        /// </param>
        /// <param name="destinationRectangles">
        /// A pointer to an array containing the destination rectangles specifying 
        /// where to draw the sprites on the destination device context.
        /// </param>
        /// <param name="sourceRectangles">
        /// A pointer to an array containing the source rectangles specifying the 
        /// regions of the source bitmap to draw as sprites. Direct2D will use the 
        /// entire source bitmap for sprites that are assigned a null value or the 
        /// InfiniteRectU. If this parameter is omitted entirely or set to a null value, 
        /// then Direct2D will use the entire source bitmap for all the added sprites.
        /// </param>
        /// <param name="colors">
        /// <p>
        /// A pointer to an array containing the colors to apply to each sprite. 
        /// The output color is the result of component-wise multiplication of 
        /// the source bitmap color and the provided color. The output color is 
        /// not clamped.
        /// </p>
        /// <p>
        /// Direct2D will not change the color of sprites that are assigned a null 
        /// value. If this parameter is omitted entirely or set to a null value, 
        /// then Direct2D will not change the color of any of the added sprites.
        /// </p>
        /// </param>
        /// <param name="transforms">
        /// <p>
        /// A pointer to an array containing the transforms to apply to each 
        /// sprite’s destination rectangle.
        /// </p>
        /// <p>
        /// Direct2D will not transform the destination rectangle of any sprites 
        /// that are assigned a null value. If this parameter is omitted entirely 
        /// or set to a null value, then Direct2D will not transform the destination 
        /// rectangle of any of the added sprites.
        /// </p>
        /// </param>
        /// <param name="destinationRectanglesStride">
        /// Specifies the distance, in bytes, between each rectangle in the 
        /// destinationRectangles array. If you provide a stride of 0, then the same 
        /// destination rectangle will be used for each added sprite.
        /// </param>
        /// <param name="sourceRectanglesStride">
        /// Specifies the distance, in bytes, between each rectangle in the sourceRectangles 
        /// array (if that array is given). If you provide a stride of 0, then the 
        /// same source rectangle will be used for each added sprite.
        /// </param>
        /// <param name="colorsStride">
        /// Specifies the distance, in bytes, between each color in the colors array 
        /// (if that array is given). If you provide a stride of 0, then the same color 
        /// will be used for each added sprite.
        /// </param>
        /// <param name="transformsStride">
        /// Specifies the distance, in bytes, between each transform in the transforms 
        /// array (if that array is given). If you provide a stride of 0, then the same 
        /// transform will be used for each added sprite.
        /// </param>
        /// <remarks>
        /// <p>
        /// In Direct2D, a sprite is defined by four properties: a destination rectangle, 
        /// a source rectangle, a color, and a transform. Destination rectangles are 
        /// mandatory, but the remaining properties are optional.
        /// </p>
        /// <p>
        /// Always omit or pass a null value for properties you do not wish to use. This 
        /// allows Direct2D to avoid storing values for those properties and to skip 
        /// their handling entirely, which improves drawing speed. For example, suppose 
        /// you have a batch of 500 sprites, and you do not wish to transform any of their 
        /// destination rectangles. Rather than passing an array of identity matrices, 
        /// simply omit the transforms parameter. This allows Direct2D to avoid storing 
        /// any transforms and will yield the fastest drawing performance. On the other 
        /// hand, if any sprite in the batch has any value set for a property, then internally 
        /// Direct2D must allocate space for that property array and assign every sprite a 
        /// value for that property (even if it’s just the default value).
        /// </p>
        /// </remarks>
        void AddSprites(UINT32 spriteCount, const D2D1_RECT_F* destinationRectangles, const D2D1_RECT_U* sourceRectangles = nullptr, const D2D1_COLOR_F* colors = nullptr, const D2D1_MATRIX_3X2_F* transforms = nullptr, UINT32 destinationRectanglesStride = sizeof( D2D1_RECT_F ), UINT32 sourceRectanglesStride = sizeof( D2D1_RECT_U ), UINT32 colorsStride = sizeof( D2D1_COLOR_F ), UINT32 transformsStride = sizeof( D2D1_MATRIX_3X2_F ) ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->AddSprites( spriteCount, destinationRectangles, sourceRectangles, colors, transforms, destinationRectanglesStride, sourceRectanglesStride, colorsStride, transformsStride );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Updates the properties of the specified sprites in this sprite batch. 
        /// Providing a null value for any property will leave that property unmodified 
        /// for that sprite.
        /// </summary>
        /// <param name="startIndex">
        /// The index of the first sprite in this sprite batch to update.
        /// </param>
        /// <param name="spriteCount">
        /// The number of sprites to update with new properties. This determines 
        /// how many strides into each given array Direct2D will read.
        /// </param>
        /// <param name="destinationRectangles">
        /// A pointer to an array containing the destination rectangles specifying 
        /// where to draw the sprites on the destination device context.
        /// </param>
        /// <param name="sourceRectangles">
        /// <p>
        /// A pointer to an array containing the source rectangles specifying the 
        /// regions of the source bitmap to draw as sprites.
        /// </p>
        /// <p>
        /// Direct2D will use the entire source bitmap for sprites that are assigned 
        /// a null value or the InfiniteRectU. If this parameter is omitted entirely 
        /// or set to a null value, then Direct2D will use the entire source bitmap 
        /// for all the updated sprites.
        /// </p>
        /// </param>
        /// <param name="colors">
        /// <p>
        /// A pointer to an array containing the colors to apply to each sprite. The output 
        /// color is the result of component-wise multiplication of the source bitmap color 
        /// and the provided color. The output color is not clamped.
        /// </p>
        /// <p>
        /// Direct2D will not change the color of sprites that are assigned a null value. 
        /// If this parameter is omitted entirely or set to a null value, then Direct2D 
        /// will not change the color of any of the updated sprites.
        /// </p>
        /// </param>
        /// <param name="transforms">
        /// <p>
        /// A pointer to an array containing the transforms to apply to each sprite’s 
        /// destination rectangle.
        /// </p>
        /// <p>
        /// Direct2D will not transform the destination rectangle of any sprites that 
        /// are assigned a null value. If this parameter is omitted entirely or set to 
        /// a null value, then Direct2D will not transform the destination rectangle 
        /// of any of the updated sprites.
        /// </p>
        /// </param>
        /// <param name="destinationRectanglesStride">
        /// Specifies the distance, in bytes, between each rectangle in the 
        /// destinationRectangles array. If you provide a stride of 0, then 
        /// the same destination rectangle will be used for each updated sprite.
        /// </param>
        /// <param name="sourceRectanglesStride">
        /// Specifies the distance, in bytes, between each rectangle in the 
        /// sourceRectangles array (if that array is given). If you provide 
        /// a stride of 0, then the same source rectangle will be used for 
        /// each updated sprite.
        /// </param>
        /// <param name="colorsStride">
        /// Specifies the distance, in bytes, between each color in the colors 
        /// array (if that array is given). If you provide a stride of 0, then 
        /// the same color will be used for each updated sprite.
        /// </param>
        /// <param name="transformsStride">
        /// Specifies the distance, in bytes, between each transform in the 
        /// transforms array (if that array is given). If you provide a stride 
        /// of 0, then the same transform will be used for each updated sprite.
        /// </param>
        void SetSprites( UINT32 startIndex, UINT32 spriteCount, const D2D1_RECT_F* destinationRectangles = nullptr, const D2D1_RECT_U* sourceRectangles = nullptr, const D2D1_COLOR_F* colors = nullptr, const D2D1_MATRIX_3X2_F* transforms = nullptr, UINT32 destinationRectanglesStride = sizeof( D2D1_RECT_F ), UINT32 sourceRectanglesStride = sizeof( D2D1_RECT_U ), UINT32 colorsStride = sizeof( D2D1_COLOR_F ), UINT32 transformsStride = sizeof( D2D1_MATRIX_3X2_F ) ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->SetSprites( startIndex, spriteCount, destinationRectangles, sourceRectangles, colors, transforms, destinationRectanglesStride, sourceRectanglesStride, colorsStride, transformsStride );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Retrieves the specified subset of sprites from this sprite batch. 
        /// For the best performance, use nullptr for properties that you do 
        /// not need to retrieve.
        /// </summary>
        /// <param name="startIndex">
        /// The index of the first sprite in this sprite batch to retrieve.
        /// </param>
        /// <param name="spriteCount">
        /// The number of sprites to retrieve.
        /// </param>
        /// <param name="destinationRectangles">
        /// When this method returns, contains a pointer to an array containing 
        /// the destination rectangles for the retrieved sprites.
        /// </param>
        /// <param name="sourceRectangles">
        /// <p>
        /// When this method returns, contains a pointer to an array containing 
        /// the source rectangles for the retrieved sprites.
        /// </p>
        /// <p>
        /// The InfiniteRectU is returned for any sprites that were not assigned 
        /// a source rectangle.
        /// </p>
        /// </param>
        /// <param name="colors">
        /// <p>
        /// When this method returns, contains a pointer to an array containing 
        /// the colors to be applied to the retrieved sprites.
        /// </p>
        /// <p>
        /// The color {1.0f, 1.0f, 1.0f, 1.0f} is returned for any sprites that 
        /// were not assigned a color.
        /// </p>
        /// </param>
        /// <param name="transforms">
        /// <p>
        /// When this method returns, contains a pointer to an array containing 
        /// the transforms to be applied to the retrieved sprites.
        /// </p>
        /// <p>
        /// The identity matrix is returned for any sprites that were not assigned 
        /// a transform.
        /// </p>
        /// </param>
        void GetSprites( UINT32 startIndex, UINT32 spriteCount, D2D1_RECT_F* destinationRectangles = nullptr, D2D1_RECT_U* sourceRectangles = nullptr, D2D1_COLOR_F* colors = nullptr, D2D1_MATRIX_3X2_F* transforms = nullptr ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetSprites( startIndex, spriteCount, destinationRectangles, sourceRectangles, colors, transforms );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Retrieves the number of sprites in the sprite batch.
        /// </summary>
        /// <returns>
        /// The number of sprites in this sprite batch.
        /// </returns>
        UINT32 GetSpriteCount( ) const
        {
            auto* pInterface = GetInterface( );
            return pInterface->GetSpriteCount( );
        }

        /// <summary>
        /// Removes all sprites from this sprite batch.
        /// </summary>
        void Clear( ) const
        {
            auto* pInterface = GetInterface( );
            return pInterface->Clear( );
        }
    };

    /// <summary>
    /// This class performs all the same functions as the DeviceContext2 class, 
    /// plus it enables functionality for creating and drawing sprite batches.
    /// </summary>
    class DeviceContext3 : public DeviceContext2
    {
        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( DeviceContext3, DeviceContext2, ID2D1DeviceContext3, ID2D1DeviceContext2 )

        /// <summary>
        /// Creates a new, empty sprite batch. After creating a sprite batch, 
        /// use SpriteBatch::AddSprites to add sprites to it, then use 
        /// DeviceContext3::DrawSpriteBatch to draw it.
        /// </summary>
        /// <param name="spriteBatch">
        /// When this method returns, contains a pointer to a new, empty sprite 
        /// batch to be populated by the app.
        /// </param>
        void CreateSpriteBatch( ID2D1SpriteBatch** spriteBatch ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateSpriteBatch( spriteBatch );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        SpriteBatch CreateSpriteBatch( ) const
        {
            ID2D1SpriteBatch* ptr = nullptr;
            CreateSpriteBatch( &ptr );
            return SpriteBatch( ptr );
        }

        /// <summary>
        /// Renders all sprites in the given sprite batch to the device context 
        /// using the specified drawing options.
        /// </summary>
        /// <param name="spriteBatch">
        /// The sprite batch to draw.
        /// </param>
        /// <param name="startIndex">
        /// The index of the first sprite in the sprite batch to draw.
        /// </param>
        /// <param name="spriteCount">
        /// The number of sprites to draw.
        /// </param>
        /// <param name="bitmap">
        /// The bitmap from which the sprites are to be sourced. Each sprite's 
        /// source rectangle refers to a portion of this bitmap.
        /// </param>
        /// <param name="interpolationMode">
        /// The interpolation mode to use when drawing this sprite batch. This 
        /// determines how Direct2D interpolates pixels within the drawn sprites if 
        /// scaling is performed. The default is D2D1_BITMAP_INTERPOLATION_MODE_LINEAR.
        /// </param>
        /// <param name="spriteOptions">
        /// The additional drawing options, if any, to be used for this sprite batch.
        /// The default is D2D1_SPRITE_OPTIONS_NONE,
        /// </param>
        void DrawSpriteBatch( _In_ ID2D1SpriteBatch* spriteBatch, UINT32 startIndex, UINT32 spriteCount, _In_ ID2D1Bitmap* bitmap, D2D1_BITMAP_INTERPOLATION_MODE interpolationMode = D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1_SPRITE_OPTIONS spriteOptions = D2D1_SPRITE_OPTIONS_NONE ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->DrawSpriteBatch( spriteBatch, startIndex, spriteCount, bitmap, interpolationMode, spriteOptions );
        }
        void DrawSpriteBatch( const SpriteBatch& spriteBatch, UINT32 startIndex, UINT32 spriteCount, const Bitmap& bitmap, D2D1_BITMAP_INTERPOLATION_MODE interpolationMode = D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1_SPRITE_OPTIONS spriteOptions = D2D1_SPRITE_OPTIONS_NONE ) const
        {
            DrawSpriteBatch( spriteBatch.GetInterfacePointer<ID2D1SpriteBatch>( ), startIndex, spriteCount, bitmap.GetInterfacePointer<ID2D1Bitmap>(), interpolationMode, spriteOptions );
        }

        /// <summary>
        /// Draws all sprites in a sprite batch.
        /// </summary>
        void DrawSpriteBatch( _In_ ID2D1SpriteBatch* spriteBatch, _In_ ID2D1Bitmap* bitmap, D2D1_BITMAP_INTERPOLATION_MODE interpolationMode = D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1_SPRITE_OPTIONS spriteOptions = D2D1_SPRITE_OPTIONS_NONE ) const
        {
            return DrawSpriteBatch( spriteBatch, 0, spriteBatch->GetSpriteCount( ), bitmap, interpolationMode, spriteOptions );
        }
        void DrawSpriteBatch( const SpriteBatch& spriteBatch, const Bitmap& bitmap, D2D1_BITMAP_INTERPOLATION_MODE interpolationMode = D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1_SPRITE_OPTIONS spriteOptions = D2D1_SPRITE_OPTIONS_NONE ) const
        {
            return DrawSpriteBatch( spriteBatch.GetInterfacePointer<ID2D1SpriteBatch>( ), 0, spriteBatch.GetSpriteCount( ), bitmap.GetInterfacePointer<ID2D1Bitmap>( ), interpolationMode, spriteOptions );
        }
    };

    /// <summary>
    /// Represents a resource domain whose objects and device contexts can 
    /// be used together. This class performs all the same functions as the 
    /// Device2 class. It also enables the creation of DeviceContext3 
    /// (ID2D1DeviceContext3) objects.
    /// </summary>
    class Device3 : public Device2
    {
    public:
        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( Device3, Device2, ID2D1Device3, ID2D1Device2 )

        /// <summary>
        /// Creates a new ID2D1DeviceContext3 from this Direct2D device 
        /// with no initially assigned target.
        /// </summary>
        /// <param name="options">
        /// The options to be applied to the created device context.
        /// The default is D2D1_DEVICE_CONTEXT_OPTIONS_NONE.
        /// </param>
        /// <param name="deviceContext3">
        /// When this method returns, contains a pointer to the new device context.
        /// </param>
        void CreateDeviceContext( D2D1_DEVICE_CONTEXT_OPTIONS options, ID2D1DeviceContext3** deviceContext3 ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateDeviceContext( options, deviceContext3 );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void CreateDeviceContext( ID2D1DeviceContext3** deviceContext3 ) const
        {
            CreateDeviceContext( D2D1_DEVICE_CONTEXT_OPTIONS_NONE, deviceContext3 );
        }
        DeviceContext3 CreateDeviceContext( D2D1_DEVICE_CONTEXT_OPTIONS options = D2D1_DEVICE_CONTEXT_OPTIONS_NONE ) const
        {
            ID2D1DeviceContext3* ptr = nullptr;
            CreateDeviceContext( options, &ptr );
            return DeviceContext3( ptr );
        }

        DeviceContext3 CreateDeviceContext3( D2D1_DEVICE_CONTEXT_OPTIONS options = D2D1_DEVICE_CONTEXT_OPTIONS_NONE ) const
        {
            return CreateDeviceContext( options );
        }
    };

    /// <summary>
    /// Creates Direct2D resources. This class also adds the ability to 
    /// create ID2D1Device3 objects.
    /// </summary>
    class Factory4 : public Factory3
    {
    public:
        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( Factory4, Factory3, ID2D1Factory4, ID2D1Factory3 )


        Factory4( D2D1_FACTORY_TYPE factoryType )
        {
            ID2D1Factory4* d2d1Factory4 = nullptr;
            auto hr = D2D1CreateFactory( factoryType, __uuidof( ID2D1Factory4 ), (void**)&d2d1Factory4 );
            HCC_COM_CHECK_HRESULT( hr );
            unknown_ = d2d1Factory4;
        }
        /// <summary>
        /// This creates a new Direct2D device from the given IDXGIDevice.
        /// </summary>
        /// <param name="dxgiDevice">
        /// The IDXGIDevice object used when creating the ID2D1Device3.
        /// </param>
        /// <param name="d2dDevice3">
        /// The requested ID2D1Device3 object.
        /// </param>
        void CreateDevice( IDXGIDevice* dxgiDevice, ID2D1Device3** d2dDevice3 ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateDevice( dxgiDevice, d2dDevice3 );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void CreateDevice( const DXGI::Device& dxgiDevice, ID2D1Device3** d2dDevice3 ) const
        {
            CreateDevice( dxgiDevice.GetInterfacePointer<IDXGIDevice>( ), d2dDevice3 );
        }

        Device3 CreateDevice( _In_ IDXGIDevice* dxgiDevice ) const
        {
            ID2D1Device3* ptr = nullptr;
            CreateDevice( dxgiDevice, &ptr );
            return Device3( ptr );
        }
        Device3 CreateDevice( const DXGI::Device& dxgiDevice ) const
        {
            return CreateDevice( dxgiDevice.GetInterfacePointer<IDXGIDevice>( ) );
        }

        Device3 CreateDevice3( _In_ IDXGIDevice* dxgiDevice ) const
        {
            return CreateDevice( dxgiDevice );
        }
        Device3 CreateDevice3( const DXGI::Device& dxgiDevice ) const
        {
            return CreateDevice( dxgiDevice );
        }
    };

    /// <summary>
    /// This class performs all the same functions as the existing 
    /// CommandSink2 class. It also enables access to sprite batch 
    /// rendering.
    /// </summary>
    class CommandSink3 : public CommandSink2
    {
    public:
        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( CommandSink3, CommandSink2, ID2D1CommandSink3, ID2D1CommandSink2 )

        /// <summary>
        /// Renders part or all of the given sprite batch to the device 
        /// context using the specified drawing options.
        /// </summary>
        /// <param name="spriteBatch">
        /// The sprite batch to draw.
        /// </param>
        /// <param name="startIndex">
        /// The index of the first sprite in the sprite batch to draw.
        /// </param>
        /// <param name="spriteCount">
        /// The number of sprites to draw.
        /// </param>
        /// <param name="bitmap">
        /// The bitmap from which the sprites are to be sourced. Each 
        /// sprite’s source rectangle refers to a portion of this bitmap.
        /// </param>
        /// <param name="interpolationMode">
        /// The interpolation mode to use when drawing this sprite batch. This 
        /// determines how Direct2D interpolates pixels within the drawn sprites 
        /// if scaling is performed. The default is D2D1_BITMAP_INTERPOLATION_MODE_LINEAR.
        /// </param>
        /// <param name="spriteOptions">
        /// The additional drawing options, if any, to be used for this sprite batch.
        /// The default is D2D1_SPRITE_OPTIONS_NONE.
        /// </param>
        void DrawSpriteBatch( _In_ ID2D1SpriteBatch* spriteBatch, UINT32 startIndex, UINT32 spriteCount, _In_ ID2D1Bitmap* bitmap, D2D1_BITMAP_INTERPOLATION_MODE interpolationMode = D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1_SPRITE_OPTIONS spriteOptions = D2D1_SPRITE_OPTIONS_NONE ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->DrawSpriteBatch( spriteBatch, startIndex, spriteCount, bitmap, interpolationMode, spriteOptions );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void DrawSpriteBatch( const SpriteBatch& spriteBatch, UINT32 startIndex, UINT32 spriteCount, const Bitmap& bitmap, D2D1_BITMAP_INTERPOLATION_MODE interpolationMode = D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1_SPRITE_OPTIONS spriteOptions = D2D1_SPRITE_OPTIONS_NONE ) const
        {
            DrawSpriteBatch( spriteBatch.GetInterfacePointer<ID2D1SpriteBatch>(), startIndex, spriteCount, bitmap.GetInterfacePointer<ID2D1Bitmap>( ), interpolationMode, spriteOptions );
        }

    };

    /// <summary>
    /// This object supplies the values for context-fill, context-stroke, 
    /// and context-value that are used when rendering SVG glyphs.
    /// </summary>
    class SvgGlyphStyle : public Resource
    {
    public:
        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( SvgGlyphStyle, Resource, ID2D1SvgGlyphStyle, ID2D1Resource )
        /// <summary>
        /// Provides values to an SVG glyph for fill. The brush with opacity set to 1 is
        /// used as the 'context-fill'. The opacity of the brush is used as the
        /// 'context-fill-opacity' value.
        /// </summary>
        /// <param name="brush">
        /// Describes how the area is painted. A null brush will cause the context-fill 
        /// value to come from the defaultFillBrush. If the defaultFillBrush is also null, 
        /// the context-fill value will be 'none'. To set the ‘context-fill’ value, this 
        /// method uses the provided brush with its opacity set to 1. To set the 
        /// ‘context-fill-opacity’ value, this method uses the opacity of the provided brush.
        /// </param>
        void SetFill( ID2D1Brush* brush = nullptr ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->SetFill( brush );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void SetFill( const Brush& brush ) const
        {
            SetFill( brush.GetInterfacePointer<ID2D1Brush>( ) );
        }

        /// <summary>
        /// Returns the requested fill parameters.
        /// </summary>
        /// <param name="brush">
        /// Describes how the area is painted.
        /// </param>
        void GetFill( ID2D1Brush** brush ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->GetFill( brush );
        }
        Brush GetFill( ) const
        {
            ID2D1Brush* ptr = nullptr;
            GetFill( &ptr );
            return Brush( ptr );
        }

        /// <summary>
        /// Provides values to an SVG glyph for stroke properties. The brush with opacity
        /// set to 1 is used as the 'context-stroke'. The opacity of the brush is used as
        /// the 'context-stroke-opacity' value.
        /// </summary>
        /// <param name="brush">
        /// Describes how the stroke is painted. A null brush will cause the context-stroke 
        /// value to be none.
        /// </param>
        /// <param name="strokeWidth">
        /// Specifies the 'context-value' for the 'stroke-width' property.
        /// </param>
        /// <param name="dashes">
        /// Specifies the 'context-value' for the 'stroke-dasharray' property. A null 
        /// value will cause the stroke-dasharray to be set to 'none'.
        /// </param>
        /// <param name="dashesCount">
        /// The the number of dashes in the dash array.
        /// </param>
        /// <param name="dashOffset">
        /// Specifies the 'context-value' for the 'stroke-dashoffset' property.
        /// </param>
        void SetStroke( _In_opt_ ID2D1Brush* brush, FLOAT strokeWidth = 1.0f, const FLOAT* dashes = nullptr, UINT32 dashesCount = 0, FLOAT dashOffset = 1.0f ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->SetStroke( brush, strokeWidth, dashes, dashesCount, dashOffset );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void SetStroke( const Brush& brush, FLOAT strokeWidth = 1.0f, const FLOAT* dashes = nullptr, UINT32 dashesCount = 0, FLOAT dashOffset = 1.0f ) const
        {
            SetStroke( brush.GetInterfacePointer<ID2D1Brush>( ), strokeWidth, dashes, dashesCount, dashOffset );
        }

        /// <summary>
        /// Returns the number of dashes in the dash array.
        /// </summary>
        UINT32 GetStrokeDashesCount( ) const
        {
            auto* pInterface = GetInterface( );
            return pInterface->GetStrokeDashesCount( );
        }

        /// <summary>
        /// Returns the requested stroke parameters. Any parameters that are 
        /// non-null will receive the value of the requested parameter.
        /// </summary>
        /// <param name="brush">
        /// Describes how the stroke is painted.
        /// </param>
        /// <param name="strokeWidth">
        /// The 'context-value' for the 'stroke-width' property.
        /// </param>
        /// <param name="dashes">
        /// The 'context-value' for the 'stroke-dasharray' property.
        /// </param>
        /// <param name="dashesCount">
        /// The the number of dashes in the dash array.
        /// </param>
        /// <param name="dashOffset">
        /// The 'context-value' for the 'stroke-dashoffset' property.
        /// </param>
        void GetStroke( ID2D1Brush** brush, FLOAT* strokeWidth = nullptr, FLOAT* dashes = nullptr, UINT32 dashesCount = 0, _Out_opt_ FLOAT* dashOffset = nullptr ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->GetStroke( brush, strokeWidth, dashes, dashesCount, dashOffset );
        }
    };

    /// <summary>
    /// This class performs all the same functions as the DeviceContext3 class, 
    /// plus it adds the functionality for requires for handling new types of 
    /// color font glyphs.
    /// </summary>
    class DeviceContext4 : public DeviceContext3
    {
    public:
        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( DeviceContext4, DeviceContext3, ID2D1DeviceContext4, ID2D1DeviceContext3 )
        /// <summary>
        /// Creates an SVG glyph style object.
        /// </summary>
        /// <param name="svgGlyphStyle">
        /// On completion points to the created ID2D1SvgGlyphStyle object.
        /// </param>
        void CreateSvgGlyphStyle( ID2D1SvgGlyphStyle** svgGlyphStyle ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateSvgGlyphStyle( svgGlyphStyle );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        SvgGlyphStyle CreateSvgGlyphStyle( ) const
        {
            ID2D1SvgGlyphStyle* ptr = nullptr;
            CreateSvgGlyphStyle( &ptr );
            return SvgGlyphStyle( ptr );
        }

        /// <summary>
        /// Draws the text within the given layout rectangle. By default, this method
        /// performs baseline snapping and renders color versions of glyphs in color fonts.
        /// </summary>
        /// <param name="string">
        /// A pointer to an array of Unicode characters to draw.
        /// </param>
        /// <param name="stringLength">
        /// The number of characters in string.
        /// </param>
        /// <param name="textFormat">
        /// An object that describes formatting details of the text to draw, such as 
        /// the font, the font size, and flow direction.
        /// </param>
        /// <param name="layoutRect">
        /// The size and position of the area in which the text is drawn.
        /// </param>
        /// <param name="defaultFillBrush">
        /// The brush used to paint the text.
        /// </param>
        /// <param name="svgGlyphStyle">
        /// Values for context-fill, context-stroke, and context-value that are 
        /// used when rendering SVG glyphs.
        /// </param>
        /// <param name="colorPaletteIndex">
        /// The index used to select a color palette within a color font.
        /// </param>
        /// <param name="options">
        /// A value that indicates whether the text should be snapped to pixel 
        /// boundaries and whether the text should be clipped to the layout rectangle. 
        /// The default value is D2D1_DRAW_TEXT_OPTIONS_NONE, which indicates that 
        /// text should be snapped to pixel boundaries and it should not be clipped 
        /// to the layout rectangle.
        /// </param>
        /// <param name="measuringMode">
        /// A value that indicates how glyph metrics are used to measure text when 
        /// it is formatted. The default value is DWRITE_MEASURING_MODE_NATURAL.
        /// </param>
        void DrawText( const WCHAR* string, UINT32 stringLength, _In_ IDWriteTextFormat* textFormat, const D2D1_RECT_F* layoutRect, ID2D1Brush* defaultFillBrush = nullptr, ID2D1SvgGlyphStyle* svgGlyphStyle = nullptr, UINT32 colorPaletteIndex = 0, D2D1_DRAW_TEXT_OPTIONS options = D2D1_DRAW_TEXT_OPTIONS_ENABLE_COLOR_FONT, DWRITE_MEASURING_MODE measuringMode = DWRITE_MEASURING_MODE_NATURAL ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->DrawText( string, stringLength, textFormat, layoutRect, defaultFillBrush, svgGlyphStyle, colorPaletteIndex, options, measuringMode );
        }
        inline void DrawText( const WCHAR* string, UINT32 stringLength, const DirectWrite::TextFormat& textFormat, const D2D1_RECT_F* layoutRect, ID2D1Brush* defaultFillBrush = nullptr, ID2D1SvgGlyphStyle* svgGlyphStyle = nullptr, UINT32 colorPaletteIndex = 0, D2D1_DRAW_TEXT_OPTIONS options = D2D1_DRAW_TEXT_OPTIONS_ENABLE_COLOR_FONT, DWRITE_MEASURING_MODE measuringMode = DWRITE_MEASURING_MODE_NATURAL ) const;
        inline void DrawText( const WCHAR* string, UINT32 stringLength, const DirectWrite::TextFormat& textFormat, const D2D1_RECT_F* layoutRect, const Brush& defaultFillBrush, ID2D1SvgGlyphStyle* svgGlyphStyle = nullptr, UINT32 colorPaletteIndex = 0, D2D1_DRAW_TEXT_OPTIONS options = D2D1_DRAW_TEXT_OPTIONS_ENABLE_COLOR_FONT, DWRITE_MEASURING_MODE measuringMode = DWRITE_MEASURING_MODE_NATURAL ) const;
        inline void DrawText( const WCHAR* string, UINT32 stringLength, const DirectWrite::TextFormat& textFormat, const D2D1_RECT_F* layoutRect, const Brush& defaultFillBrush, const SvgGlyphStyle& svgGlyphStyle, UINT32 colorPaletteIndex = 0, D2D1_DRAW_TEXT_OPTIONS options = D2D1_DRAW_TEXT_OPTIONS_ENABLE_COLOR_FONT, DWRITE_MEASURING_MODE measuringMode = DWRITE_MEASURING_MODE_NATURAL ) const;

        void DrawText( const WCHAR* string, UINT32 stringLength, _In_ IDWriteTextFormat* textFormat, CONST D2D1_RECT_F& layoutRect, _In_opt_ ID2D1Brush* defaultFillBrush = nullptr, _In_opt_ ID2D1SvgGlyphStyle* svgGlyphStyle = nullptr, UINT32 colorPaletteIndex = 0, D2D1_DRAW_TEXT_OPTIONS options = D2D1_DRAW_TEXT_OPTIONS_ENABLE_COLOR_FONT, DWRITE_MEASURING_MODE measuringMode = DWRITE_MEASURING_MODE_NATURAL ) const
        {
            return DrawText( string, stringLength, textFormat, &layoutRect, defaultFillBrush, svgGlyphStyle, colorPaletteIndex, options, measuringMode );
        }
        inline void DrawText( const WCHAR* string, UINT32 stringLength, const DirectWrite::TextFormat& textFormat, CONST D2D1_RECT_F& layoutRect, _In_opt_ ID2D1Brush* defaultFillBrush = nullptr, _In_opt_ ID2D1SvgGlyphStyle* svgGlyphStyle = nullptr, UINT32 colorPaletteIndex = 0, D2D1_DRAW_TEXT_OPTIONS options = D2D1_DRAW_TEXT_OPTIONS_ENABLE_COLOR_FONT, DWRITE_MEASURING_MODE measuringMode = DWRITE_MEASURING_MODE_NATURAL ) const;
        inline void DrawText( const WCHAR* string, UINT32 stringLength, const DirectWrite::TextFormat& textFormat, CONST D2D1_RECT_F& layoutRect, const Brush& defaultFillBrush, _In_opt_ ID2D1SvgGlyphStyle* svgGlyphStyle = nullptr, UINT32 colorPaletteIndex = 0, D2D1_DRAW_TEXT_OPTIONS options = D2D1_DRAW_TEXT_OPTIONS_ENABLE_COLOR_FONT, DWRITE_MEASURING_MODE measuringMode = DWRITE_MEASURING_MODE_NATURAL ) const;
        inline void DrawText( const WCHAR* string, UINT32 stringLength, const DirectWrite::TextFormat& textFormat, CONST D2D1_RECT_F& layoutRect, const Brush& defaultFillBrush, const SvgGlyphStyle& svgGlyphStyle, UINT32 colorPaletteIndex = 0, D2D1_DRAW_TEXT_OPTIONS options = D2D1_DRAW_TEXT_OPTIONS_ENABLE_COLOR_FONT, DWRITE_MEASURING_MODE measuringMode = DWRITE_MEASURING_MODE_NATURAL ) const;


        using RenderTarget::DrawText;

        /// <summary>
        /// Draw a text layout object. If the layout is not subsequently changed, this can
        /// be more efficient than DrawText when drawing the same layout repeatedly.
        /// </summary>
        /// <param name="origin">
        /// The point, described in device-independent pixels, at which the upper-left 
        /// corner of the text described by textLayout is drawn.
        /// </param>
        /// <param name="textLayout">
        /// The formatted text to draw. Any drawing effects that do not inherit from 
        /// ID2D1Resource are ignored. If there are drawing effects that inherit 
        /// from ID2D1Resource that are not brushes, this method fails and the render 
        /// target is put in an error state.
        /// </param>
        /// <param name="defaultFillBrush">
        /// The brush used to paint the text.
        /// </param>
        /// <param name="svgGlyphStyle">
        /// The values for context-fill, context-stroke, and context-value that are 
        /// used when rendering SVG glyphs.
        /// </param>
        /// <param name="colorPaletteIndex">
        /// The index used to select a color palette within a color font.
        /// </param>
        /// <param name="options">
        /// A value that indicates whether the text should be snapped to pixel boundaries 
        /// and whether the text should be clipped to the layout rectangle. The default 
        /// value is D2D1_DRAW_TEXT_OPTIONS_NONE, which indicates that text should be 
        /// snapped to pixel boundaries and it should not be clipped to the layout rectangle.
        /// </param>
        void DrawTextLayout( const D2D1_POINT_2F& origin, _In_ IDWriteTextLayout* textLayout, _In_opt_ ID2D1Brush* defaultFillBrush = nullptr, _In_opt_ ID2D1SvgGlyphStyle* svgGlyphStyle = nullptr, UINT32 colorPaletteIndex = 0, D2D1_DRAW_TEXT_OPTIONS options = D2D1_DRAW_TEXT_OPTIONS_ENABLE_COLOR_FONT ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->DrawTextLayout( origin, textLayout, defaultFillBrush, svgGlyphStyle, colorPaletteIndex, options );
        }
        void DrawTextLayout( const D2D1_POINT_2F& origin, _In_ IDWriteTextLayout* textLayout, ID2D1SvgGlyphStyle* svgGlyphStyle, UINT32 colorPaletteIndex = 0, D2D1_DRAW_TEXT_OPTIONS options = D2D1_DRAW_TEXT_OPTIONS_ENABLE_COLOR_FONT ) const
        {
            DrawTextLayout( origin, textLayout, nullptr, svgGlyphStyle, colorPaletteIndex, options );
        }
        void DrawTextLayout( const D2D1_POINT_2F& origin, _In_ IDWriteTextLayout* textLayout, ID2D1Brush* defaultFillBrush, UINT32 colorPaletteIndex = 0, D2D1_DRAW_TEXT_OPTIONS options = D2D1_DRAW_TEXT_OPTIONS_ENABLE_COLOR_FONT ) const
        {
            DrawTextLayout( origin, textLayout, defaultFillBrush, nullptr, colorPaletteIndex, options );
        }
        void DrawTextLayout( const D2D1_POINT_2F& origin, _In_ IDWriteTextLayout* textLayout, UINT32 colorPaletteIndex, D2D1_DRAW_TEXT_OPTIONS options = D2D1_DRAW_TEXT_OPTIONS_ENABLE_COLOR_FONT ) const
        {
            DrawTextLayout( origin, textLayout, nullptr, nullptr, colorPaletteIndex, options );
        }
        void DrawTextLayout( const D2D1_POINT_2F& origin, _In_ IDWriteTextLayout* textLayout, const SvgGlyphStyle& svgGlyphStyle, UINT32 colorPaletteIndex = 0, D2D1_DRAW_TEXT_OPTIONS options = D2D1_DRAW_TEXT_OPTIONS_ENABLE_COLOR_FONT ) const
        {
            DrawTextLayout( origin, textLayout, nullptr, svgGlyphStyle.GetInterfacePointer<ID2D1SvgGlyphStyle>( ), colorPaletteIndex, options );
        }
        void DrawTextLayout( const D2D1_POINT_2F& origin, _In_ IDWriteTextLayout* textLayout, const Brush& defaultFillBrush, UINT32 colorPaletteIndex = 0, D2D1_DRAW_TEXT_OPTIONS options = D2D1_DRAW_TEXT_OPTIONS_ENABLE_COLOR_FONT ) const
        {
            DrawTextLayout( origin, textLayout, defaultFillBrush.GetInterfacePointer<ID2D1Brush>( ), nullptr, colorPaletteIndex, options );
        }


        inline void DrawTextLayout( const D2D1_POINT_2F& origin, const DirectWrite::TextLayout& textLayout, _In_opt_ ID2D1Brush* defaultFillBrush = nullptr, _In_opt_ ID2D1SvgGlyphStyle* svgGlyphStyle = nullptr, UINT32 colorPaletteIndex = 0, D2D1_DRAW_TEXT_OPTIONS options = D2D1_DRAW_TEXT_OPTIONS_ENABLE_COLOR_FONT ) const;
        inline void DrawTextLayout( const D2D1_POINT_2F& origin, const DirectWrite::TextLayout& textLayout, const Brush& defaultFillBrush, _In_opt_ ID2D1SvgGlyphStyle* svgGlyphStyle = nullptr, UINT32 colorPaletteIndex = 0, D2D1_DRAW_TEXT_OPTIONS options = D2D1_DRAW_TEXT_OPTIONS_ENABLE_COLOR_FONT ) const;
        inline void DrawTextLayout( const D2D1_POINT_2F& origin, const DirectWrite::TextLayout& textLayout, const Brush& defaultFillBrush, const SvgGlyphStyle& svgGlyphStyle, UINT32 colorPaletteIndex = 0, D2D1_DRAW_TEXT_OPTIONS options = D2D1_DRAW_TEXT_OPTIONS_ENABLE_COLOR_FONT ) const;
        inline void DrawTextLayout( const D2D1_POINT_2F& origin, const DirectWrite::TextLayout& textLayout, UINT32 colorPaletteIndex, D2D1_DRAW_TEXT_OPTIONS options = D2D1_DRAW_TEXT_OPTIONS_ENABLE_COLOR_FONT ) const;
        inline void DrawTextLayout( const D2D1_POINT_2F& origin, const DirectWrite::TextLayout& textLayout, const SvgGlyphStyle& svgGlyphStyle, UINT32 colorPaletteIndex = 0, D2D1_DRAW_TEXT_OPTIONS options = D2D1_DRAW_TEXT_OPTIONS_ENABLE_COLOR_FONT ) const;
        inline void DrawTextLayout( const D2D1_POINT_2F& origin, const DirectWrite::TextLayout& textLayout, const Brush& defaultFillBrush, UINT32 colorPaletteIndex = 0, D2D1_DRAW_TEXT_OPTIONS options = D2D1_DRAW_TEXT_OPTIONS_ENABLE_COLOR_FONT ) const;

        using RenderTarget::DrawTextLayout;

        /// <summary>
        /// Draws a color bitmap glyph run using one of the bitmap formats.
        /// </summary>
        /// <param name="glyphImageFormat">
        /// <p>
        /// Specifies the format of the glyph image. Supported formats are
        /// </p> 
        /// <ul>
        /// <li>DWRITE_GLYPH_IMAGE_FORMATS_PNG</li>
        /// <li>DWRITE_GLYPH_IMAGE_FORMATS_JPEG</li>
        /// <li>DWRITE_GLYPH_IMAGE_FORMATS_TIFF</li>
        /// <li>DWRITE_GLYPH_IMAGE_FORMATS_PREMULTIPLIED_B8G8R8A8</li>
        /// <p>
        /// This method will result in an error if the color glyph run does not contain the requested format.
        /// </p>
        /// </param>
        /// <param name="baselineOrigin">
        /// The origin of the baseline for the glyph run.
        /// </param>
        /// <param name="glyphRun">
        /// The glyphs to render.
        /// </param>
        /// <param name="measuringMode">
        /// Indicates the measuring method. The default is DWRITE_MEASURING_MODE_NATURAL
        /// </param>
        /// <param name="bitmapSnapOption">
        /// Specifies the pixel snapping policy when rendering color bitmap glyphs.
        /// The default is D2D1_COLOR_BITMAP_GLYPH_SNAP_OPTION_DEFAULT.
        /// </param>
        void DrawColorBitmapGlyphRun( DWRITE_GLYPH_IMAGE_FORMATS glyphImageFormat, const D2D1_POINT_2F& baselineOrigin, _In_ const DWRITE_GLYPH_RUN* glyphRun, DWRITE_MEASURING_MODE measuringMode = DWRITE_MEASURING_MODE_NATURAL, D2D1_COLOR_BITMAP_GLYPH_SNAP_OPTION bitmapSnapOption = D2D1_COLOR_BITMAP_GLYPH_SNAP_OPTION_DEFAULT ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->DrawColorBitmapGlyphRun( glyphImageFormat, baselineOrigin, glyphRun, measuringMode, bitmapSnapOption );
        }
        void DrawColorBitmapGlyphRun( DWRITE_GLYPH_IMAGE_FORMATS glyphImageFormat, const D2D1_POINT_2F& baselineOrigin, const DWRITE_GLYPH_RUN& glyphRun, DWRITE_MEASURING_MODE measuringMode = DWRITE_MEASURING_MODE_NATURAL, D2D1_COLOR_BITMAP_GLYPH_SNAP_OPTION bitmapSnapOption = D2D1_COLOR_BITMAP_GLYPH_SNAP_OPTION_DEFAULT ) const
        {
            DrawColorBitmapGlyphRun( glyphImageFormat, baselineOrigin, &glyphRun, measuringMode, bitmapSnapOption );
        }

        /// <summary>
        /// Draws a color glyph run that has the format of DWRITE_GLYPH_IMAGE_FORMATS_SVG.
        /// </summary>
        /// <param name="baselineOrigin">
        /// The origin of the baseline for the glyph run.
        /// </param>
        /// <param name="glyphRun">
        /// The glyphs to render.
        /// </param>
        /// <param name="defaultFillBrush">
        /// The brush used to paint the specified glyphs.
        /// </param>
        /// <param name="svgGlyphStyle">
        /// Values for context-fill, context-stroke, and context-value that are used when 
        /// rendering SVG glyphs.
        /// </param>
        /// <param name="colorPaletteIndex">
        /// The index used to select a color palette within a color font. Note that this 
        /// not the same as the paletteIndex in the DWRITE_COLOR_GLYPH_RUN struct, which 
        /// is not relevant for SVG glyphs.
        /// </param>
        /// <param name="measuringMode">
        /// Indicates the measuring method used for text layout.
        /// </param>
        void DrawSvgGlyphRun( const D2D1_POINT_2F& baselineOrigin, _In_ const DWRITE_GLYPH_RUN* glyphRun, _In_opt_ ID2D1Brush* defaultFillBrush = nullptr, _In_opt_ ID2D1SvgGlyphStyle* svgGlyphStyle = nullptr, UINT32 colorPaletteIndex = 0, DWRITE_MEASURING_MODE measuringMode = DWRITE_MEASURING_MODE_NATURAL ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->DrawSvgGlyphRun( baselineOrigin, glyphRun, defaultFillBrush, svgGlyphStyle, colorPaletteIndex, measuringMode );
        }
        void DrawSvgGlyphRun( const D2D1_POINT_2F& baselineOrigin, const DWRITE_GLYPH_RUN& glyphRun, _In_opt_ ID2D1Brush* defaultFillBrush = nullptr, _In_opt_ ID2D1SvgGlyphStyle* svgGlyphStyle = nullptr, UINT32 colorPaletteIndex = 0, DWRITE_MEASURING_MODE measuringMode = DWRITE_MEASURING_MODE_NATURAL ) const
        {
            DrawSvgGlyphRun( baselineOrigin, &glyphRun, defaultFillBrush, svgGlyphStyle, colorPaletteIndex, measuringMode );
        }
        void DrawSvgGlyphRun( const D2D1_POINT_2F& baselineOrigin, const DWRITE_GLYPH_RUN* glyphRun, const Brush& defaultFillBrush, _In_opt_ ID2D1SvgGlyphStyle* svgGlyphStyle = nullptr, UINT32 colorPaletteIndex = 0, DWRITE_MEASURING_MODE measuringMode = DWRITE_MEASURING_MODE_NATURAL ) const
        {
            DrawSvgGlyphRun( baselineOrigin, glyphRun, defaultFillBrush.GetInterfacePointer<ID2D1Brush>( ), svgGlyphStyle, colorPaletteIndex, measuringMode );
        }
        void DrawSvgGlyphRun( const D2D1_POINT_2F& baselineOrigin, const DWRITE_GLYPH_RUN& glyphRun, const Brush& defaultFillBrush, _In_opt_ ID2D1SvgGlyphStyle* svgGlyphStyle = nullptr, UINT32 colorPaletteIndex = 0, DWRITE_MEASURING_MODE measuringMode = DWRITE_MEASURING_MODE_NATURAL ) const
        {
            DrawSvgGlyphRun( baselineOrigin, &glyphRun, defaultFillBrush.GetInterfacePointer<ID2D1Brush>( ), svgGlyphStyle, colorPaletteIndex, measuringMode );
        }
        void DrawSvgGlyphRun( const D2D1_POINT_2F& baselineOrigin, const DWRITE_GLYPH_RUN* glyphRun, const Brush& defaultFillBrush, const SvgGlyphStyle& svgGlyphStyle, UINT32 colorPaletteIndex = 0, DWRITE_MEASURING_MODE measuringMode = DWRITE_MEASURING_MODE_NATURAL ) const
        {
            DrawSvgGlyphRun( baselineOrigin, glyphRun, defaultFillBrush.GetInterfacePointer<ID2D1Brush>( ), svgGlyphStyle.GetInterfacePointer<ID2D1SvgGlyphStyle>( ), colorPaletteIndex, measuringMode );
        }
        void DrawSvgGlyphRun( const D2D1_POINT_2F& baselineOrigin, const DWRITE_GLYPH_RUN& glyphRun, const Brush& defaultFillBrush, const SvgGlyphStyle& svgGlyphStyle, UINT32 colorPaletteIndex = 0, DWRITE_MEASURING_MODE measuringMode = DWRITE_MEASURING_MODE_NATURAL ) const
        {
            DrawSvgGlyphRun( baselineOrigin, glyphRun, defaultFillBrush.GetInterfacePointer<ID2D1Brush>( ), svgGlyphStyle.GetInterfacePointer<ID2D1SvgGlyphStyle>( ), colorPaletteIndex, measuringMode );
        }

        /// <summary>
        /// Retrieves an image of the color bitmap glyph from the color glyph cache. 
        /// If the cache does not already contain the requested resource, it will be 
        /// created. This method may be used to extend the lifetime of a glyph image 
        /// even after it is evicted from the color glyph cache.
        /// </summary>
        /// <param name="glyphImageFormat">
        /// The format for the glyph image. If there is no image data in the requested 
        /// format for the requested glyph, this method will return an error.
        /// </param>
        /// <param name="glyphOrigin">
        /// The origin for the glyph.
        /// </param>
        /// <param name="fontFace">
        /// Reference to a font face which contains font face type, appropriate file 
        /// references, face identification data and various font data such as metrics, 
        /// names and glyph outlines.
        /// </param>
        /// <param name="fontEmSize">
        /// The specified font size affects the choice of which bitmap to use from the 
        /// font. It also affects the output glyphTransform, causing it to properly 
        /// scale the glyph.
        /// </param>
        /// <param name="glyphIndex">
        /// Index of the glyph.
        /// </param>
        /// <param name="isSideways">
        /// If true, specifies that glyphs are rotated 90 degrees to the left and 
        /// vertical metrics are used. Vertical writing is achieved by specifying 
        /// isSideways as true and rotating the entire run 90 degrees to the right 
        /// via a rotate transform.
        /// </param>
        /// <param name="worldTransform">
        /// The transform to apply to the image. This input transform affects 
        /// the choice of which bitmap to use from the font. It is also factored 
        /// into the output glyphTransform.
        /// </param>
        /// <param name="dpiX">
        /// Dots per inch along the x-axis.
        /// </param>
        /// <param name="dpiY">
        /// Dots per inch along the y-axis.
        /// </param>
        /// <param name="glyphTransform">
        /// Output transform, which transforms from the glyph's space to the same 
        /// output space as the worldTransform. This includes the input glyphOrigin, 
        /// the glyph's offset from the glyphOrigin, and any other required transformations.
        /// </param>
        /// <param name="glyphImage">
        /// On completion contains the retrieved glyph image.
        /// </param>
        void GetColorBitmapGlyphImage( DWRITE_GLYPH_IMAGE_FORMATS glyphImageFormat, const D2D1_POINT_2F& glyphOrigin, _In_ IDWriteFontFace* fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, _In_opt_ const D2D1_MATRIX_3X2_F* worldTransform, FLOAT dpiX, FLOAT dpiY, _Out_ D2D1_MATRIX_3X2_F* glyphTransform, ID2D1Image** glyphImage ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetColorBitmapGlyphImage( glyphImageFormat, glyphOrigin, fontFace, fontEmSize, glyphIndex, isSideways, worldTransform, dpiX, dpiY, glyphTransform, glyphImage );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void GetColorBitmapGlyphImage( DWRITE_GLYPH_IMAGE_FORMATS glyphImageFormat, const D2D1_POINT_2F& glyphOrigin, _In_ IDWriteFontFace* fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, _In_opt_ const D2D1_MATRIX_3X2_F* worldTransform, FLOAT dpiX, FLOAT dpiY, D2D1_MATRIX_3X2_F& glyphTransform, ID2D1Image** glyphImage ) const
        {
            GetColorBitmapGlyphImage( glyphImageFormat, glyphOrigin, fontFace, fontEmSize, glyphIndex, isSideways, worldTransform, dpiX, dpiY, &glyphTransform, glyphImage );
        }
        void GetColorBitmapGlyphImage( DWRITE_GLYPH_IMAGE_FORMATS glyphImageFormat, const D2D1_POINT_2F& glyphOrigin, _In_ IDWriteFontFace* fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const D2D1_MATRIX_3X2_F& worldTransform, FLOAT dpiX, FLOAT dpiY, _Out_ D2D1_MATRIX_3X2_F* glyphTransform, ID2D1Image** glyphImage ) const
        {
            GetColorBitmapGlyphImage( glyphImageFormat, glyphOrigin, fontFace, fontEmSize, glyphIndex, isSideways, &worldTransform, dpiX, dpiY, glyphTransform, glyphImage );
        }
        void GetColorBitmapGlyphImage( DWRITE_GLYPH_IMAGE_FORMATS glyphImageFormat, const D2D1_POINT_2F& glyphOrigin, _In_ IDWriteFontFace* fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const D2D1_MATRIX_3X2_F& worldTransform, FLOAT dpiX, FLOAT dpiY, _Out_ D2D1_MATRIX_3X2_F& glyphTransform, ID2D1Image** glyphImage ) const
        {
            GetColorBitmapGlyphImage( glyphImageFormat, glyphOrigin, fontFace, fontEmSize, glyphIndex, isSideways, &worldTransform, dpiX, dpiY, &glyphTransform, glyphImage );
        }

        void GetColorBitmapGlyphImage( DWRITE_GLYPH_IMAGE_FORMATS glyphImageFormat, const D2D1_POINT_2F& glyphOrigin, _In_ IDWriteFontFace* fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, FLOAT dpiX, FLOAT dpiY, _Out_ D2D1_MATRIX_3X2_F* glyphTransform, ID2D1Image** glyphImage ) const
        {
            GetColorBitmapGlyphImage( glyphImageFormat, glyphOrigin, fontFace, fontEmSize, glyphIndex, isSideways, nullptr, dpiX, dpiY, glyphTransform, glyphImage );
        }
        void GetColorBitmapGlyphImage( DWRITE_GLYPH_IMAGE_FORMATS glyphImageFormat, const D2D1_POINT_2F& glyphOrigin, _In_ IDWriteFontFace* fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, FLOAT dpiX, FLOAT dpiY, _Out_ D2D1_MATRIX_3X2_F& glyphTransform, ID2D1Image** glyphImage ) const
        {
            GetColorBitmapGlyphImage( glyphImageFormat, glyphOrigin, fontFace, fontEmSize, glyphIndex, isSideways, nullptr, dpiX, dpiY, &glyphTransform, glyphImage );
        }

        inline void GetColorBitmapGlyphImage( DWRITE_GLYPH_IMAGE_FORMATS glyphImageFormat, const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, _In_opt_ const D2D1_MATRIX_3X2_F* worldTransform, FLOAT dpiX, FLOAT dpiY, _Out_ D2D1_MATRIX_3X2_F* glyphTransform, ID2D1Image** glyphImage ) const;
        inline void GetColorBitmapGlyphImage( DWRITE_GLYPH_IMAGE_FORMATS glyphImageFormat, const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, _In_opt_ const D2D1_MATRIX_3X2_F* worldTransform, FLOAT dpiX, FLOAT dpiY, D2D1_MATRIX_3X2_F& glyphTransform, ID2D1Image** glyphImage ) const;
        inline void GetColorBitmapGlyphImage( DWRITE_GLYPH_IMAGE_FORMATS glyphImageFormat, const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const D2D1_MATRIX_3X2_F& worldTransform, FLOAT dpiX, FLOAT dpiY, _Out_ D2D1_MATRIX_3X2_F* glyphTransform, ID2D1Image** glyphImage ) const;
        inline void GetColorBitmapGlyphImage( DWRITE_GLYPH_IMAGE_FORMATS glyphImageFormat, const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const D2D1_MATRIX_3X2_F& worldTransform, FLOAT dpiX, FLOAT dpiY, _Out_ D2D1_MATRIX_3X2_F& glyphTransform, ID2D1Image** glyphImage ) const;
        inline void GetColorBitmapGlyphImage( DWRITE_GLYPH_IMAGE_FORMATS glyphImageFormat, const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, FLOAT dpiX, FLOAT dpiY, _Out_ D2D1_MATRIX_3X2_F* glyphTransform, ID2D1Image** glyphImage ) const;
        inline void GetColorBitmapGlyphImage( DWRITE_GLYPH_IMAGE_FORMATS glyphImageFormat, const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, FLOAT dpiX, FLOAT dpiY, _Out_ D2D1_MATRIX_3X2_F& glyphTransform, ID2D1Image** glyphImage ) const;

        Image GetColorBitmapGlyphImage( DWRITE_GLYPH_IMAGE_FORMATS glyphImageFormat, const D2D1_POINT_2F& glyphOrigin, _In_ IDWriteFontFace* fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, _In_opt_ const D2D1_MATRIX_3X2_F* worldTransform, FLOAT dpiX, FLOAT dpiY, _Out_ D2D1_MATRIX_3X2_F* glyphTransform ) const
        {
            ID2D1Image* ptr = nullptr;
            GetColorBitmapGlyphImage( glyphImageFormat, glyphOrigin, fontFace, fontEmSize, glyphIndex, isSideways, worldTransform, dpiX, dpiY, glyphTransform, &ptr );
            return Image( ptr );
        }
        Image GetColorBitmapGlyphImage( DWRITE_GLYPH_IMAGE_FORMATS glyphImageFormat, const D2D1_POINT_2F& glyphOrigin, _In_ IDWriteFontFace* fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, _In_opt_ const D2D1_MATRIX_3X2_F* worldTransform, FLOAT dpiX, FLOAT dpiY, D2D1_MATRIX_3X2_F& glyphTransform ) const
        {
            return GetColorBitmapGlyphImage( glyphImageFormat, glyphOrigin, fontFace, fontEmSize, glyphIndex, isSideways, worldTransform, dpiX, dpiY, &glyphTransform );
        }
        Image GetColorBitmapGlyphImage( DWRITE_GLYPH_IMAGE_FORMATS glyphImageFormat, const D2D1_POINT_2F& glyphOrigin, _In_ IDWriteFontFace* fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const D2D1_MATRIX_3X2_F& worldTransform, FLOAT dpiX, FLOAT dpiY, _Out_ D2D1_MATRIX_3X2_F* glyphTransform ) const
        {
            return GetColorBitmapGlyphImage( glyphImageFormat, glyphOrigin, fontFace, fontEmSize, glyphIndex, isSideways, &worldTransform, dpiX, dpiY, glyphTransform );
        }
        Image GetColorBitmapGlyphImage( DWRITE_GLYPH_IMAGE_FORMATS glyphImageFormat, const D2D1_POINT_2F& glyphOrigin, _In_ IDWriteFontFace* fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const D2D1_MATRIX_3X2_F& worldTransform, FLOAT dpiX, FLOAT dpiY, _Out_ D2D1_MATRIX_3X2_F& glyphTransform ) const
        {
            return GetColorBitmapGlyphImage( glyphImageFormat, glyphOrigin, fontFace, fontEmSize, glyphIndex, isSideways, &worldTransform, dpiX, dpiY, &glyphTransform );
        }

        Image GetColorBitmapGlyphImage( DWRITE_GLYPH_IMAGE_FORMATS glyphImageFormat, const D2D1_POINT_2F& glyphOrigin, _In_ IDWriteFontFace* fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, FLOAT dpiX, FLOAT dpiY, _Out_ D2D1_MATRIX_3X2_F* glyphTransform ) const
        {
            return GetColorBitmapGlyphImage( glyphImageFormat, glyphOrigin, fontFace, fontEmSize, glyphIndex, isSideways, nullptr, dpiX, dpiY, glyphTransform );
        }
        Image GetColorBitmapGlyphImage( DWRITE_GLYPH_IMAGE_FORMATS glyphImageFormat, const D2D1_POINT_2F& glyphOrigin, _In_ IDWriteFontFace* fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, FLOAT dpiX, FLOAT dpiY, _Out_ D2D1_MATRIX_3X2_F& glyphTransform ) const
        {
            return GetColorBitmapGlyphImage( glyphImageFormat, glyphOrigin, fontFace, fontEmSize, glyphIndex, isSideways, nullptr, dpiX, dpiY, &glyphTransform );
        }
        inline Image GetColorBitmapGlyphImage( DWRITE_GLYPH_IMAGE_FORMATS glyphImageFormat, const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, _In_opt_ const D2D1_MATRIX_3X2_F* worldTransform, FLOAT dpiX, FLOAT dpiY, _Out_ D2D1_MATRIX_3X2_F* glyphTransform ) const;
        inline Image GetColorBitmapGlyphImage( DWRITE_GLYPH_IMAGE_FORMATS glyphImageFormat, const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, _In_opt_ const D2D1_MATRIX_3X2_F* worldTransform, FLOAT dpiX, FLOAT dpiY, D2D1_MATRIX_3X2_F& glyphTransform ) const;
        inline Image GetColorBitmapGlyphImage( DWRITE_GLYPH_IMAGE_FORMATS glyphImageFormat, const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const D2D1_MATRIX_3X2_F& worldTransform, FLOAT dpiX, FLOAT dpiY, _Out_ D2D1_MATRIX_3X2_F* glyphTransform ) const;
        inline Image GetColorBitmapGlyphImage( DWRITE_GLYPH_IMAGE_FORMATS glyphImageFormat, const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const D2D1_MATRIX_3X2_F& worldTransform, FLOAT dpiX, FLOAT dpiY, _Out_ D2D1_MATRIX_3X2_F& glyphTransform ) const;
        inline Image GetColorBitmapGlyphImage( DWRITE_GLYPH_IMAGE_FORMATS glyphImageFormat, const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, FLOAT dpiX, FLOAT dpiY, _Out_ D2D1_MATRIX_3X2_F* glyphTransform ) const;
        inline Image GetColorBitmapGlyphImage( DWRITE_GLYPH_IMAGE_FORMATS glyphImageFormat, const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, FLOAT dpiX, FLOAT dpiY, _Out_ D2D1_MATRIX_3X2_F& glyphTransform ) const;


        /// <summary>
        /// Retrieves an image of the SVG glyph from the color glyph cache. If the cache
        /// does not already contain the requested resource, it will be created. This method
        /// may be used to extend the lifetime of a glyph image even after it is evicted
        /// from the color glyph cache.
        /// </summary>
        /// <param name="glyphOrigin">
        /// Origin of the glyph.
        /// </param>
        /// <param name="fontFace">
        /// Reference to a font face which contains font face type, appropriate file references, face 
        /// identification data and various font data such as metrics, names and glyph outlines.
        /// </param>
        /// <param name="fontEmSize">
        /// The specified font size affects the output glyphTransform, causing it to properly 
        /// scale the glyph.
        /// </param>
        /// <param name="glyphIndex">
        /// Index of the glyph to retrieve.
        /// </param>
        /// <param name="isSideways">
        /// If true, specifies that glyphs are rotated 90 degrees to the left and vertical metrics 
        /// are used. Vertical writing is achieved by specifying isSideways as true and rotating 
        /// the entire run 90 degrees to the right via a rotate transform.
        /// </param>
        /// <param name="worldTransform">
        /// The transform to apply to the image.
        /// </param>
        /// <param name="defaultFillBrush">
        /// Describes how the area is painted.
        /// </param>
        /// <param name="svgGlyphStyle">
        /// The values for context-fill, context-stroke, and context-value that are used when 
        /// rendering SVG glyphs.
        /// </param>
        /// <param name="colorPaletteIndex">
        /// The index used to select a color palette within a color font. Note that this not 
        /// the same as the paletteIndex in the DWRITE_COLOR_GLYPH_RUN struct, which is not 
        /// relevant for SVG glyphs.
        /// </param>
        /// <param name="glyphTransform">
        /// Output transform, which transforms from the glyph's space to the same output space 
        /// as the worldTransform. This includes the input glyphOrigin, the glyph's offset from 
        /// the glyphOrigin, and any other required transformations.
        /// </param>
        /// <param name="glyphImage">
        /// On completion, contains the retrieved glyph image.
        /// </param>
        void GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, _In_ IDWriteFontFace* fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, _In_opt_ const D2D1_MATRIX_3X2_F* worldTransform, _In_opt_ ID2D1Brush* defaultFillBrush, _In_opt_ ID2D1SvgGlyphStyle* svgGlyphStyle, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F* glyphTransform, _COM_Outptr_ ID2D1CommandList** glyphImage ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetSvgGlyphImage( glyphOrigin, fontFace, fontEmSize, glyphIndex, isSideways, worldTransform, defaultFillBrush, svgGlyphStyle, colorPaletteIndex, glyphTransform, glyphImage );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, _In_ IDWriteFontFace* fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const D2D1_MATRIX_3X2_F& worldTransform, _In_opt_ ID2D1Brush* defaultFillBrush, _In_opt_ ID2D1SvgGlyphStyle* svgGlyphStyle, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform, _COM_Outptr_ ID2D1CommandList** glyphImage ) const
        {
            GetSvgGlyphImage( glyphOrigin, fontFace, fontEmSize, glyphIndex, isSideways, &worldTransform, defaultFillBrush, svgGlyphStyle, colorPaletteIndex, &glyphTransform, glyphImage );
        }
        void GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, _In_ IDWriteFontFace* fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const D2D1_MATRIX_3X2_F& worldTransform, const Brush& defaultFillBrush, _In_opt_ ID2D1SvgGlyphStyle* svgGlyphStyle, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform, _COM_Outptr_ ID2D1CommandList** glyphImage ) const
        {
            GetSvgGlyphImage( glyphOrigin, fontFace, fontEmSize, glyphIndex, isSideways, &worldTransform, defaultFillBrush.GetInterfacePointer<ID2D1Brush>( ), svgGlyphStyle, colorPaletteIndex, &glyphTransform, glyphImage );
        }
        void GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, _In_ IDWriteFontFace* fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const D2D1_MATRIX_3X2_F& worldTransform, const Brush& defaultFillBrush, const SvgGlyphStyle& svgGlyphStyle, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform, _COM_Outptr_ ID2D1CommandList** glyphImage ) const
        {
            GetSvgGlyphImage( glyphOrigin, fontFace, fontEmSize, glyphIndex, isSideways, &worldTransform, defaultFillBrush.GetInterfacePointer<ID2D1Brush>( ), svgGlyphStyle.GetInterfacePointer<ID2D1SvgGlyphStyle>( ), colorPaletteIndex, &glyphTransform, glyphImage );
        }
        void GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, _In_ IDWriteFontFace* fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const D2D1_MATRIX_3X2_F& worldTransform, const SvgGlyphStyle& svgGlyphStyle, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform, _COM_Outptr_ ID2D1CommandList** glyphImage ) const
        {
            GetSvgGlyphImage( glyphOrigin, fontFace, fontEmSize, glyphIndex, isSideways, &worldTransform, nullptr, svgGlyphStyle.GetInterfacePointer<ID2D1SvgGlyphStyle>( ), colorPaletteIndex, &glyphTransform, glyphImage );
        }
        void GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, _In_ IDWriteFontFace* fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const D2D1_MATRIX_3X2_F& worldTransform, const Brush& defaultFillBrush, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform, _COM_Outptr_ ID2D1CommandList** glyphImage ) const
        {
            GetSvgGlyphImage( glyphOrigin, fontFace, fontEmSize, glyphIndex, isSideways, &worldTransform, defaultFillBrush.GetInterfacePointer<ID2D1Brush>( ), nullptr, colorPaletteIndex, &glyphTransform, glyphImage );
        }
        void GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, _In_ IDWriteFontFace* fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const D2D1_MATRIX_3X2_F& worldTransform, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform, _COM_Outptr_ ID2D1CommandList** glyphImage ) const
        {
            GetSvgGlyphImage( glyphOrigin, fontFace, fontEmSize, glyphIndex, isSideways, &worldTransform, nullptr, nullptr, colorPaletteIndex, &glyphTransform, glyphImage );
        }

        void GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, _In_ IDWriteFontFace* fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, _In_opt_ ID2D1Brush* defaultFillBrush, _In_opt_ ID2D1SvgGlyphStyle* svgGlyphStyle, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F* glyphTransform, _COM_Outptr_ ID2D1CommandList** glyphImage ) const
        {
            GetSvgGlyphImage( glyphOrigin, fontFace, fontEmSize, glyphIndex, isSideways, nullptr, defaultFillBrush, svgGlyphStyle, colorPaletteIndex, glyphTransform, glyphImage );
        }
        void GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, _In_ IDWriteFontFace* fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, _In_opt_ ID2D1Brush* defaultFillBrush, _In_opt_ ID2D1SvgGlyphStyle* svgGlyphStyle, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform, _COM_Outptr_ ID2D1CommandList** glyphImage ) const
        {
            GetSvgGlyphImage( glyphOrigin, fontFace, fontEmSize, glyphIndex, isSideways, nullptr, defaultFillBrush, svgGlyphStyle, colorPaletteIndex, &glyphTransform, glyphImage );
        }
        void GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, _In_ IDWriteFontFace* fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const Brush& defaultFillBrush, _In_opt_ ID2D1SvgGlyphStyle* svgGlyphStyle, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform, _COM_Outptr_ ID2D1CommandList** glyphImage ) const
        {
            GetSvgGlyphImage( glyphOrigin, fontFace, fontEmSize, glyphIndex, isSideways, nullptr, defaultFillBrush.GetInterfacePointer<ID2D1Brush>( ), svgGlyphStyle, colorPaletteIndex, &glyphTransform, glyphImage );
        }
        void GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, _In_ IDWriteFontFace* fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const Brush& defaultFillBrush, const SvgGlyphStyle& svgGlyphStyle, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform, _COM_Outptr_ ID2D1CommandList** glyphImage ) const
        {
            GetSvgGlyphImage( glyphOrigin, fontFace, fontEmSize, glyphIndex, isSideways, nullptr, defaultFillBrush.GetInterfacePointer<ID2D1Brush>( ), svgGlyphStyle.GetInterfacePointer<ID2D1SvgGlyphStyle>( ), colorPaletteIndex, &glyphTransform, glyphImage );
        }
        void GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, _In_ IDWriteFontFace* fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const SvgGlyphStyle& svgGlyphStyle, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform, _COM_Outptr_ ID2D1CommandList** glyphImage ) const
        {
            GetSvgGlyphImage( glyphOrigin, fontFace, fontEmSize, glyphIndex, isSideways, nullptr, nullptr, svgGlyphStyle.GetInterfacePointer<ID2D1SvgGlyphStyle>( ), colorPaletteIndex, &glyphTransform, glyphImage );
        }
        void GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, _In_ IDWriteFontFace* fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const Brush& defaultFillBrush, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform, _COM_Outptr_ ID2D1CommandList** glyphImage ) const
        {
            GetSvgGlyphImage( glyphOrigin, fontFace, fontEmSize, glyphIndex, isSideways, nullptr, defaultFillBrush.GetInterfacePointer<ID2D1Brush>( ), nullptr, colorPaletteIndex, &glyphTransform, glyphImage );
        }
        void GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, _In_ IDWriteFontFace* fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform, _COM_Outptr_ ID2D1CommandList** glyphImage ) const
        {
            GetSvgGlyphImage( glyphOrigin, fontFace, fontEmSize, glyphIndex, isSideways, nullptr, nullptr, nullptr, colorPaletteIndex, &glyphTransform, glyphImage );
        }

        
        inline void GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, _In_opt_ const D2D1_MATRIX_3X2_F* worldTransform, _In_opt_ ID2D1Brush* defaultFillBrush, _In_opt_ ID2D1SvgGlyphStyle* svgGlyphStyle, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F* glyphTransform, _COM_Outptr_ ID2D1CommandList** glyphImage ) const;
        inline void GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const D2D1_MATRIX_3X2_F& worldTransform, _In_opt_ ID2D1Brush* defaultFillBrush, _In_opt_ ID2D1SvgGlyphStyle* svgGlyphStyle, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform, _COM_Outptr_ ID2D1CommandList** glyphImage ) const;
        inline void GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const D2D1_MATRIX_3X2_F& worldTransform, const Brush& defaultFillBrush, _In_opt_ ID2D1SvgGlyphStyle* svgGlyphStyle, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform, _COM_Outptr_ ID2D1CommandList** glyphImage ) const;
        inline void GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const D2D1_MATRIX_3X2_F& worldTransform, const Brush& defaultFillBrush, const SvgGlyphStyle& svgGlyphStyle, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform, _COM_Outptr_ ID2D1CommandList** glyphImage ) const;
        inline void GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const D2D1_MATRIX_3X2_F& worldTransform, const SvgGlyphStyle& svgGlyphStyle, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform, _COM_Outptr_ ID2D1CommandList** glyphImage ) const;
        inline void GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const D2D1_MATRIX_3X2_F& worldTransform, const Brush& defaultFillBrush, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform, _COM_Outptr_ ID2D1CommandList** glyphImage ) const;
        inline void GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const D2D1_MATRIX_3X2_F& worldTransform, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform, _COM_Outptr_ ID2D1CommandList** glyphImage ) const;
        inline void GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, _In_opt_ ID2D1Brush* defaultFillBrush, _In_opt_ ID2D1SvgGlyphStyle* svgGlyphStyle, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F* glyphTransform, _COM_Outptr_ ID2D1CommandList** glyphImage ) const;
        inline void GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, _In_opt_ ID2D1Brush* defaultFillBrush, _In_opt_ ID2D1SvgGlyphStyle* svgGlyphStyle, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform, _COM_Outptr_ ID2D1CommandList** glyphImage ) const;
        inline void GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const Brush& defaultFillBrush, _In_opt_ ID2D1SvgGlyphStyle* svgGlyphStyle, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform, _COM_Outptr_ ID2D1CommandList** glyphImage ) const;
        inline void GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const Brush& defaultFillBrush, const SvgGlyphStyle& svgGlyphStyle, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform, _COM_Outptr_ ID2D1CommandList** glyphImage ) const;
        inline void GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const SvgGlyphStyle& svgGlyphStyle, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform, _COM_Outptr_ ID2D1CommandList** glyphImage ) const;
        inline void GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const Brush& defaultFillBrush, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform, _COM_Outptr_ ID2D1CommandList** glyphImage ) const;
        inline void GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform, _COM_Outptr_ ID2D1CommandList** glyphImage ) const;

        Image GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, _In_ IDWriteFontFace* fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, _In_opt_ const D2D1_MATRIX_3X2_F* worldTransform, _In_opt_ ID2D1Brush* defaultFillBrush, _In_opt_ ID2D1SvgGlyphStyle* svgGlyphStyle, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F* glyphTransform ) const
        {
            ID2D1CommandList* ptr = nullptr;
            GetSvgGlyphImage( glyphOrigin, fontFace, fontEmSize, glyphIndex, isSideways, worldTransform, defaultFillBrush, svgGlyphStyle, colorPaletteIndex, glyphTransform, &ptr );
            return Image( ptr );
        }
        Image GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, _In_ IDWriteFontFace* fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const D2D1_MATRIX_3X2_F& worldTransform, _In_opt_ ID2D1Brush* defaultFillBrush, _In_opt_ ID2D1SvgGlyphStyle* svgGlyphStyle, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform ) const
        {
            return GetSvgGlyphImage( glyphOrigin, fontFace, fontEmSize, glyphIndex, isSideways, &worldTransform, defaultFillBrush, svgGlyphStyle, colorPaletteIndex, &glyphTransform );
        }
        Image GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, _In_ IDWriteFontFace* fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const D2D1_MATRIX_3X2_F& worldTransform, const Brush& defaultFillBrush, _In_opt_ ID2D1SvgGlyphStyle* svgGlyphStyle, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform ) const
        {
            return GetSvgGlyphImage( glyphOrigin, fontFace, fontEmSize, glyphIndex, isSideways, &worldTransform, defaultFillBrush.GetInterfacePointer<ID2D1Brush>( ), svgGlyphStyle, colorPaletteIndex, &glyphTransform );
        }
        Image GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, _In_ IDWriteFontFace* fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const D2D1_MATRIX_3X2_F& worldTransform, const Brush& defaultFillBrush, const SvgGlyphStyle& svgGlyphStyle, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform ) const
        {
            return GetSvgGlyphImage( glyphOrigin, fontFace, fontEmSize, glyphIndex, isSideways, &worldTransform, defaultFillBrush.GetInterfacePointer<ID2D1Brush>( ), svgGlyphStyle.GetInterfacePointer<ID2D1SvgGlyphStyle>( ), colorPaletteIndex, &glyphTransform );
        }
        Image GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, _In_ IDWriteFontFace* fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const D2D1_MATRIX_3X2_F& worldTransform, const SvgGlyphStyle& svgGlyphStyle, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform ) const
        {
            return GetSvgGlyphImage( glyphOrigin, fontFace, fontEmSize, glyphIndex, isSideways, &worldTransform, nullptr, svgGlyphStyle.GetInterfacePointer<ID2D1SvgGlyphStyle>( ), colorPaletteIndex, &glyphTransform );
        }
        Image GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, _In_ IDWriteFontFace* fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const D2D1_MATRIX_3X2_F& worldTransform, const Brush& defaultFillBrush, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform ) const
        {
            return GetSvgGlyphImage( glyphOrigin, fontFace, fontEmSize, glyphIndex, isSideways, &worldTransform, defaultFillBrush.GetInterfacePointer<ID2D1Brush>( ), nullptr, colorPaletteIndex, &glyphTransform );
        }
        Image GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, _In_ IDWriteFontFace* fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const D2D1_MATRIX_3X2_F& worldTransform, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform ) const
        {
            return GetSvgGlyphImage( glyphOrigin, fontFace, fontEmSize, glyphIndex, isSideways, &worldTransform, nullptr, nullptr, colorPaletteIndex, &glyphTransform );
        }

        Image GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, _In_ IDWriteFontFace* fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, _In_opt_ ID2D1Brush* defaultFillBrush, _In_opt_ ID2D1SvgGlyphStyle* svgGlyphStyle, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F* glyphTransform ) const
        {
            return GetSvgGlyphImage( glyphOrigin, fontFace, fontEmSize, glyphIndex, isSideways, nullptr, defaultFillBrush, svgGlyphStyle, colorPaletteIndex, glyphTransform );
        }
        Image GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, _In_ IDWriteFontFace* fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, _In_opt_ ID2D1Brush* defaultFillBrush, _In_opt_ ID2D1SvgGlyphStyle* svgGlyphStyle, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform ) const
        {
            return GetSvgGlyphImage( glyphOrigin, fontFace, fontEmSize, glyphIndex, isSideways, nullptr, defaultFillBrush, svgGlyphStyle, colorPaletteIndex, &glyphTransform );
        }
        Image GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, _In_ IDWriteFontFace* fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const Brush& defaultFillBrush, _In_opt_ ID2D1SvgGlyphStyle* svgGlyphStyle, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform ) const
        {
            return GetSvgGlyphImage( glyphOrigin, fontFace, fontEmSize, glyphIndex, isSideways, nullptr, defaultFillBrush.GetInterfacePointer<ID2D1Brush>( ), svgGlyphStyle, colorPaletteIndex, &glyphTransform );
        }
        Image GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, _In_ IDWriteFontFace* fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const Brush& defaultFillBrush, const SvgGlyphStyle& svgGlyphStyle, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform ) const
        {
            return GetSvgGlyphImage( glyphOrigin, fontFace, fontEmSize, glyphIndex, isSideways, nullptr, defaultFillBrush.GetInterfacePointer<ID2D1Brush>( ), svgGlyphStyle.GetInterfacePointer<ID2D1SvgGlyphStyle>( ), colorPaletteIndex, &glyphTransform );
        }
        Image GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, _In_ IDWriteFontFace* fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const SvgGlyphStyle& svgGlyphStyle, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform ) const
        {
            return GetSvgGlyphImage( glyphOrigin, fontFace, fontEmSize, glyphIndex, isSideways, nullptr, nullptr, svgGlyphStyle.GetInterfacePointer<ID2D1SvgGlyphStyle>( ), colorPaletteIndex, &glyphTransform );
        }
        Image GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, _In_ IDWriteFontFace* fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const Brush& defaultFillBrush, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform ) const
        {
            return GetSvgGlyphImage( glyphOrigin, fontFace, fontEmSize, glyphIndex, isSideways, nullptr, defaultFillBrush.GetInterfacePointer<ID2D1Brush>( ), nullptr, colorPaletteIndex, &glyphTransform );
        }
        Image GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, _In_ IDWriteFontFace* fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform ) const
        {
            return GetSvgGlyphImage( glyphOrigin, fontFace, fontEmSize, glyphIndex, isSideways, nullptr, nullptr, nullptr, colorPaletteIndex, &glyphTransform );
        }

        inline Image GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, _In_opt_ const D2D1_MATRIX_3X2_F* worldTransform, _In_opt_ ID2D1Brush* defaultFillBrush, _In_opt_ ID2D1SvgGlyphStyle* svgGlyphStyle, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F* glyphTransform ) const;
        inline Image GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const D2D1_MATRIX_3X2_F& worldTransform, _In_opt_ ID2D1Brush* defaultFillBrush, _In_opt_ ID2D1SvgGlyphStyle* svgGlyphStyle, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform ) const;
        inline Image GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const D2D1_MATRIX_3X2_F& worldTransform, const Brush& defaultFillBrush, _In_opt_ ID2D1SvgGlyphStyle* svgGlyphStyle, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform ) const;
        inline Image GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const D2D1_MATRIX_3X2_F& worldTransform, const Brush& defaultFillBrush, const SvgGlyphStyle& svgGlyphStyle, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform ) const;
        inline Image GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const D2D1_MATRIX_3X2_F& worldTransform, const SvgGlyphStyle& svgGlyphStyle, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform ) const;
        inline Image GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const D2D1_MATRIX_3X2_F& worldTransform, const Brush& defaultFillBrush, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform ) const;
        inline Image GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const D2D1_MATRIX_3X2_F& worldTransform, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform ) const;
        inline Image GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, _In_opt_ ID2D1Brush* defaultFillBrush, _In_opt_ ID2D1SvgGlyphStyle* svgGlyphStyle, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F* glyphTransform ) const;
        inline Image GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, _In_opt_ ID2D1Brush* defaultFillBrush, _In_opt_ ID2D1SvgGlyphStyle* svgGlyphStyle, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform ) const;
        inline Image GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const Brush& defaultFillBrush, _In_opt_ ID2D1SvgGlyphStyle* svgGlyphStyle, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform ) const;
        inline Image GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const Brush& defaultFillBrush, const SvgGlyphStyle& svgGlyphStyle, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform ) const;
        inline Image GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const SvgGlyphStyle& svgGlyphStyle, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform ) const;
        inline Image GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const Brush& defaultFillBrush, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform ) const;
        inline Image GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform ) const;



    };

    /// <summary>
    /// Represents a resource domain whose objects and device contexts can be 
    /// used together. This class performs all the same functions as the Device3 
    /// class. It also enables the creation of DeviceContext4 (ID2D1DeviceContext4) 
    /// objects.
    /// </summary>
    class Device4 : public Device3
    {
    public:
        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( Device4, Device3, ID2D1Device4, ID2D1Device3 )
        /// <summary>
        /// Creates a new device context with no initially assigned target.
        /// </summary>
        /// <param name="options">
        /// The options to be applied to the created device context.
        /// The default is D2D1_DEVICE_CONTEXT_OPTIONS_NONE.
        /// </param>
        /// <param name="deviceContext4">
        /// When this method returns, contains a pointer to the new device context.
        /// </param>
        void CreateDeviceContext( D2D1_DEVICE_CONTEXT_OPTIONS options, _COM_Outptr_ ID2D1DeviceContext4** deviceContext4 ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateDeviceContext( options, deviceContext4 );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        DeviceContext4 CreateDeviceContext( D2D1_DEVICE_CONTEXT_OPTIONS options = D2D1_DEVICE_CONTEXT_OPTIONS_NONE ) const
        {
            ID2D1DeviceContext4* ptr = nullptr;
            CreateDeviceContext( options, &ptr );
            return DeviceContext4( ptr );
        }

        DeviceContext4 CreateDeviceContext4( D2D1_DEVICE_CONTEXT_OPTIONS options = D2D1_DEVICE_CONTEXT_OPTIONS_NONE ) const
        {
            return CreateDeviceContext( options );
        }

        /// <summary>
        /// Sets the maximum capacity of the color glyph cache. This cache is used to store
        /// color bitmap glyphs and SVG glyphs, enabling faster performance if the same
        /// glyphs are needed again. If the application still references a glyph using
        /// GetColorBitmapGlyphImage or GetSvgGlyphImage after it has been evicted, this
        /// glyph does not count toward the cache capacity.
        /// </summary>
        /// <param name="maximumInBytes">
        /// The maximum capacity of the color glyph cache.
        /// </param>
        void SetMaximumColorGlyphCacheMemory( UINT64 maximumInBytes ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->SetMaximumColorGlyphCacheMemory( maximumInBytes );
        }

        /// <summary>
        /// Gets the maximum capacity of the color glyph cache.
        /// </summary>
        UINT64 GetMaximumColorGlyphCacheMemory( ) const
        {
            auto* pInterface = GetInterface( );
            return pInterface->GetMaximumColorGlyphCacheMemory( );
        }
    };

    /// <summary>
    ///
    /// </summary>
    class Factory5 : public Factory4
    {
    public:
        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( Factory5, Factory4, ID2D1Factory5, ID2D1Factory4 )

        Factory5( D2D1_FACTORY_TYPE factoryType )
        {
            ID2D1Factory5* d2d1Factory5 = nullptr;
            auto hr = D2D1CreateFactory( factoryType, __uuidof( ID2D1Factory5 ), (void**)&d2d1Factory5 );
            HCC_COM_CHECK_HRESULT( hr );
            unknown_ = d2d1Factory5;
        }
        /// <summary>
        /// This creates a new Direct2D device from the given IDXGIDevice.
        /// </summary>
        /// <param name="dxgiDevice">
        /// The IDXGIDevice object used when creating the ID2D1Device4.
        /// </param>
        /// <param name="d2dDevice4">
        /// The requested ID2D1Device4 object.
        /// </param>
        void CreateDevice( _In_ IDXGIDevice* dxgiDevice, ID2D1Device4** d2dDevice4 ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateDevice( dxgiDevice, d2dDevice4 );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void CreateDevice( const DXGI::Device& dxgiDevice, ID2D1Device4** d2dDevice4 ) const
        {
            CreateDevice( dxgiDevice.GetInterfacePointer<IDXGIDevice>( ), d2dDevice4 );
        }

        Device4 CreateDevice( _In_ IDXGIDevice* dxgiDevice ) const
        {
            ID2D1Device4* ptr = nullptr;
            CreateDevice( dxgiDevice, &ptr );
            return Device4( ptr );
        }
        Device4 CreateDevice( const DXGI::Device& dxgiDevice ) const
        {
            return CreateDevice( dxgiDevice.GetInterfacePointer<IDXGIDevice>( ) );
        }

        Device4 CreateDevice4( _In_ IDXGIDevice* dxgiDevice ) const
        {
            return CreateDevice( dxgiDevice );
        }
        Device4 CreateDevice4( const DXGI::Device& dxgiDevice ) const
        {
            return CreateDevice( dxgiDevice );
        }

    };

    /// <summary>
    ///
    /// </summary>
    class CommandSink4 : public CommandSink3
    {
    public:
        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( CommandSink4, CommandSink3, ID2D1CommandSink4, ID2D1CommandSink3 )
        /// <summary>
        /// A new function to set blend mode that respects the new MAX blend.
        /// 
        /// Implementers of SetPrimitiveBlend2 should expect and handle blend mode:
        /// D2D1_PRIMITIVE_BLEND_MAX
        /// 
        /// Implementers of SetPrimitiveBlend1 should expect and handle blend modes:
        /// D2D1_PRIMITIVE_BLEND_MIN and D2D1_PRIMITIVE_BLEND_ADD
        /// 
        /// Implementers of SetPrimitiveBlend should expect and handle blend modes:
        /// D2D1_PRIMITIVE_BLEND_SOURCE_OVER and D2D1_PRIMITIVE_BLEND_COPY
        /// </summary>
        /// <param name="primitiveBlend">
        /// The primitive blend that will apply to subsequent primitives.
        /// </param>
        void SetPrimitiveBlend2( D2D1_PRIMITIVE_BLEND primitiveBlend ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->SetPrimitiveBlend2( primitiveBlend );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    /// <summary>
    /// Represents a color context to be used with the Color Management Effect.
    /// </summary>
    class ColorContext1 : public ColorContext
    {
    public:
        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( ColorContext1, ColorContext, ID2D1ColorContext1, ID2D1ColorContext )
        /// <summary>
        /// Retrieves the color context type.
        /// </summary>
        D2D1_COLOR_CONTEXT_TYPE GetColorContextType( ) const
        {
            auto* pInterface = GetInterface( );
            return pInterface->GetColorContextType( );
        }

        /// <summary>
        /// Retrieves the DXGI color space of this context. Returns DXGI_COLOR_SPACE_CUSTOM
        /// when color context type is ICC.
        /// </summary>
        DXGI_COLOR_SPACE_TYPE GetDXGIColorSpace( ) const
        {
            auto* pInterface = GetInterface( );
            return pInterface->GetDXGIColorSpace( );
        }

        /// <summary>
        /// Retrieves a set simple color profile.
        /// </summary>
        /// <param name="simpleProfile">
        /// Pointer to a D2D1_SIMPLE_COLOR_PROFILE that will contain the 
        /// simple color profile when the function returns.
        /// </param>
        void GetSimpleColorProfile( _Out_ D2D1_SIMPLE_COLOR_PROFILE* simpleProfile ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetSimpleColorProfile( simpleProfile );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void GetSimpleColorProfile( D2D1_SIMPLE_COLOR_PROFILE& simpleProfile ) const
        {
            GetSimpleColorProfile( &simpleProfile );
        }
    };

    class SvgElement;
    /// <summary>
    /// 
    /// </summary>
    class SvgAttribute : public Resource
    {
    public:
        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( SvgAttribute, Resource, ID2D1SvgAttribute, ID2D1Resource )

        /// <summary>
        /// Returns the element on which this attribute is set. Returns null if the
        /// attribute is not set on any element.
        /// </summary>
        void GetElement( ID2D1SvgElement** element ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->GetElement( element );
        }

        /// <summary>
        /// Creates a clone of this attribute value. On creation, the cloned attribute is
        /// not set on any element.
        /// </summary>
        void Clone( ID2D1SvgAttribute** attribute ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->Clone( attribute );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };


    class SvgPaint : public SvgAttribute
    {
    public:
        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( SvgPaint, SvgAttribute, ID2D1SvgPaint, ID2D1SvgAttribute )
        /// <summary>
        /// Sets the paint type.
        /// </summary>
        void SetPaintType( D2D1_SVG_PAINT_TYPE paintType ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->SetPaintType( paintType );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Gets the paint type.
        /// </summary>
        D2D1_SVG_PAINT_TYPE GetPaintType( ) const
        {
            auto* pInterface = GetInterface( );
            return pInterface->GetPaintType( );
        }

        /// <summary>
        /// Sets the paint color that is used if the paint type is
        /// D2D1_SVG_PAINT_TYPE_COLOR.
        /// </summary>
        void SetColor( _In_ const D2D1_COLOR_F* color ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->SetColor( color );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void SetColor( const D2D1_COLOR_F& color ) const
        {
            SetColor( &color );
        }

        /// <summary>
        /// Gets the paint color that is used if the paint type is
        /// D2D1_SVG_PAINT_TYPE_COLOR.
        /// </summary>
        void GetColor( _Out_ D2D1_COLOR_F* color ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->GetColor( color );
        }
        void GetColor( D2D1_COLOR_F& color ) const
        {
            GetColor( &color );
        }

        /// <summary>
        /// Sets the element id which acts as the paint server. This id is used if the paint
        /// type is D2D1_SVG_PAINT_TYPE_URI.
        /// </summary>
        void SetId( _In_ PCWSTR id ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->SetId( id );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Gets the element id which acts as the paint server. This id is used if the paint
        /// type is D2D1_SVG_PAINT_TYPE_URI.
        /// </summary>
        void GetId( PWSTR id, UINT32 idCount ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetId( id, idCount );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Gets the string length of the element id which acts as the paint server. This id
        /// is used if the paint type is D2D1_SVG_PAINT_TYPE_URI. The returned string length
        /// does not include room for the null terminator.
        /// </summary>
        UINT32 GetIdLength( ) const
        {
            auto* pInterface = GetInterface( );
            return pInterface->GetIdLength( );
        }
    };

    class SvgStrokeDashArray : public SvgAttribute
    {
    public:
        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( SvgStrokeDashArray, SvgAttribute, ID2D1SvgStrokeDashArray, ID2D1SvgAttribute )
        /// <summary>
        /// Removes dashes from the end of the array.
        /// </summary>
        /// <param name="dashesCount">Specifies how many dashes to remove.</param>
        void RemoveDashesAtEnd( UINT32 dashesCount ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->RemoveDashesAtEnd( dashesCount );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Updates the array. Existing dashes not updated by this method are preserved. The
        /// array is resized larger if necessary to accomodate the new dashes.
        /// </summary>
        /// <param name="dashes">The dashes array.</param>
        /// <param name="dashesCount">The number of dashes to update.</param>
        /// <param name="startIndex">The index at which to begin updating dashes. Must be
        /// less than or equal to the size of the array.</param>
        void UpdateDashes( const FLOAT* dashes, UINT32 dashesCount, UINT32 startIndex = 0 ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->UpdateDashes( dashes, dashesCount, startIndex );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Updates the array. Existing dashes not updated by this method are preserved. The
        /// array is resized larger if necessary to accomodate the new dashes.
        /// </summary>
        /// <param name="dashes">The dashes array.</param>
        /// <param name="dashesCount">The number of dashes to update.</param>
        /// <param name="startIndex">The index at which to begin updating dashes. Must be
        /// less than or equal to the size of the array.</param>
        STDMETHOD( UpdateDashes )( const D2D1_SVG_LENGTH* dashes, UINT32 dashesCount, UINT32 startIndex = 0 ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->UpdateDashes( dashes, dashesCount, startIndex );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Gets dashes from the array.
        /// </summary>
        /// <param name="dashes">Buffer to contain the dashes.</param>
        /// <param name="dashesCount">The element count of buffer.</param>
        /// <param name="startIndex">The index of the first dash to retrieve.</param>
        void GetDashes( FLOAT* dashes, UINT32 dashesCount, UINT32 startIndex = 0 ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetDashes( dashes, dashesCount, startIndex );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Gets dashes from the array.
        /// </summary>
        /// <param name="dashes">Buffer to contain the dashes.</param>
        /// <param name="dashesCount">The element count of buffer.</param>
        /// <param name="startIndex">The index of the first dash to retrieve.</param>
        void GetDashes( D2D1_SVG_LENGTH* dashes, UINT32 dashesCount, UINT32 startIndex = 0 ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetDashes( dashes, dashesCount, startIndex );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Gets the number of the dashes in the array.
        /// </summary>
        UINT32 GetDashesCount( ) const
        {
            auto* pInterface = GetInterface( );
            return pInterface->GetDashesCount( );
        }
    };

    class SvgPointCollection : public SvgAttribute
    {
    public:
        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( SvgPointCollection, SvgAttribute, ID2D1SvgPointCollection, ID2D1SvgAttribute )
        /// <summary>
        /// Removes points from the end of the array.
        /// </summary>
        /// <param name="pointsCount">Specifies how many points to remove.</param>
        void RemovePointsAtEnd( UINT32 pointsCount ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->RemovePointsAtEnd( pointsCount );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Updates the points array. Existing points not updated by this method are
        /// preserved. The array is resized larger if necessary to accomodate the new
        /// points.
        /// </summary>
        /// <param name="points">The points array.</param>
        /// <param name="pointsCount">The number of points to update.</param>
        /// <param name="startIndex">The index at which to begin updating points. Must be
        /// less than or equal to the size of the array.</param>
        void UpdatePoints( const D2D1_POINT_2F* points, UINT32 pointsCount, UINT32 startIndex = 0 ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->UpdatePoints( points, pointsCount, startIndex );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Gets points from the points array.
        /// </summary>
        /// <param name="points">Buffer to contain the points.</param>
        /// <param name="pointsCount">The element count of the buffer.</param>
        /// <param name="startIndex">The index of the first point to retrieve.</param>
        void GetPoints(D2D1_POINT_2F* points, UINT32 pointsCount, UINT32 startIndex = 0 ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetPoints( points, pointsCount, startIndex );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Gets the number of points in the array.
        /// </summary>
        UINT32 GetPointsCount( ) const
        {
            auto* pInterface = GetInterface( );
            return pInterface->GetPointsCount( );
        }
    };


    class SvgPathData : public SvgAttribute
    {
    public:
        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( SvgPathData, SvgAttribute, ID2D1SvgPathData, ID2D1SvgAttribute )
        /// <summary>
        /// Removes data from the end of the segment data array.
        /// </summary>
        /// <param name="dataCount">Specifies how much data to remove.</param>
        void RemoveSegmentDataAtEnd( UINT32 dataCount ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->RemoveSegmentDataAtEnd( dataCount );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Updates the segment data array. Existing segment data not updated by this method
        /// are preserved. The array is resized larger if necessary to accomodate the new
        /// segment data.
        /// </summary>
        /// <param name="data">The data array.</param>
        /// <param name="dataCount">The number of data to update.</param>
        /// <param name="startIndex">The index at which to begin updating segment data. Must
        /// be less than or equal to the size of the segment data array.</param>
        void UpdateSegmentData( const FLOAT* data, UINT32 dataCount, UINT32 startIndex = 0 ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->UpdateSegmentData( data, dataCount, startIndex );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Gets data from the segment data array.
        /// </summary>
        /// <param name="data">Buffer to contain the segment data array.</param>
        /// <param name="dataCount">The element count of the buffer.</param>
        /// <param name="startIndex">The index of the first segment data to retrieve.
        /// </param>
        void GetSegmentData( FLOAT* data, UINT32 dataCount, UINT32 startIndex = 0 ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetSegmentData( data, dataCount, startIndex );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Gets the size of the segment data array.
        /// </summary>
        UINT32 GetSegmentDataCount( ) const
        {
            auto* pInterface = GetInterface( );
            return pInterface->GetSegmentDataCount( );
        }

        /// <summary>
        /// Removes commands from the end of the commands array.
        /// </summary>
        /// <param name="commandsCount">Specifies how many commands to remove.</param>
        void RemoveCommandsAtEnd( UINT32 commandsCount ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->RemoveCommandsAtEnd( commandsCount );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Updates the commands array. Existing commands not updated by this method are
        /// preserved. The array is resized larger if necessary to accomodate the new
        /// commands.
        /// </summary>
        /// <param name="commands">The commands array.</param>
        /// <param name="commandsCount">The number of commands to update.</param>
        /// <param name="startIndex">The index at which to begin updating commands. Must be
        /// less than or equal to the size of the commands array.</param>
        void UpdateCommands( const D2D1_SVG_PATH_COMMAND* commands, UINT32 commandsCount, UINT32 startIndex = 0 ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->UpdateCommands( commands, commandsCount, startIndex );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Gets commands from the commands array.
        /// </summary>
        /// <param name="commands">Buffer to contain the commands</param>
        /// <param name="commandsCount">The element count of the buffer.</param>
        /// <param name="startIndex">The index of the first commands to retrieve.</param>
        void GetCommands( D2D1_SVG_PATH_COMMAND* commands, UINT32 commandsCount, UINT32 startIndex = 0 ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetCommands( commands, commandsCount, startIndex );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Gets the size of the commands array.
        /// </summary>
        UINT32 GetCommandsCount( ) const
        {
            auto* pInterface = GetInterface( );
            return pInterface->GetCommandsCount( );
        }

        /// <summary>
        /// Creates a path geometry object representing the path data.
        /// </summary>
        void CreatePathGeometry( D2D1_FILL_MODE fillMode, ID2D1PathGeometry1** pathGeometry ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreatePathGeometry( fillMode, pathGeometry );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        PathGeometry1 CreatePathGeometry( D2D1_FILL_MODE fillMode ) const
        {
            ID2D1PathGeometry1* ptr = nullptr;
            CreatePathGeometry( fillMode, &ptr );
            return PathGeometry1( ptr );
        }
    };

    class SvgDocument;

    class SvgElement : public Resource
    {
    public:
        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( SvgElement, Resource, ID2D1SvgElement, ID2D1Resource )
        /// <summary>
        /// Gets the document that contains this element. Returns null if the element has
        /// been removed from the tree.
        /// </summary>
        void GetDocument( ID2D1SvgDocument** document ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->GetDocument( document );
        }
        inline SvgDocument GetDocument( ) const;

        /// <summary>
        /// Gets the tag name.
        /// </summary>
        void GetTagName( PWSTR name, UINT32 nameCount ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetTagName( name, nameCount );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        std::wstring GetTagName( ) const
        {
            std::wstring result;
            auto tagNameLength = GetTagNameLength( );
            result.resize( tagNameLength );
            GetTagName( result.data(), static_cast<size_t>(tagNameLength) );
            return result;
        }

        /// <summary>
        /// Gets the string length of the tag name. The returned string length does not
        /// include room for the null terminator.
        /// </summary>
        UINT32 GetTagNameLength( ) const
        {
            auto* pInterface = GetInterface( );
            return pInterface->GetTagNameLength( );
        }

        /// <summary>
        /// Returns TRUE if this element represents text content, e.g. the content of a
        /// 'title' or 'desc' element. Text content does not have a tag name.
        /// </summary>
        bool IsTextContent( ) const
        {
            auto* pInterface = GetInterface( );
            return pInterface->IsTextContent( ) != FALSE;
        }

        /// <summary>
        /// Gets the parent element.
        /// </summary>
        void GetParent( ID2D1SvgElement** parent ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->GetParent( parent );
        }
        SvgElement GetParent( ) const
        {
            ID2D1SvgElement* ptr = nullptr;
            GetParent( &ptr );
            return SvgElement( ptr );
        }

        /// <summary>
        /// Returns whether this element has children.
        /// </summary>
        bool HasChildren( ) const
        {
            auto* pInterface = GetInterface( );
            return pInterface->HasChildren( ) != FALSE;
        }

        /// <summary>
        /// Gets the first child of this element.
        /// </summary>
        void GetFirstChild( ID2D1SvgElement** child ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->GetFirstChild( child );
        }
#pragma warning(push)
#pragma warning(disable:4003)
        SvgElement GetFirstChild( ) const
        {
            ID2D1SvgElement* ptr = nullptr;
            GetFirstChild( &ptr );
            return SvgElement( ptr );
        }
#pragma warning(pop)
        /// <summary>
        /// Gets the last child of this element.
        /// </summary>
        void GetLastChild( ID2D1SvgElement** child ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->GetLastChild( child );
        }
        SvgElement GetLastChild( ) const
        {
            ID2D1SvgElement* ptr = nullptr;
            GetLastChild( &ptr );
            return SvgElement( ptr );
        }

        /// <summary>
        /// Gets the previous sibling of the referenceChild element.
        /// </summary>
        /// <param name="referenceChild">The referenceChild must be an immediate child of
        /// this element.</param>
        /// <param name="previousChild">The output previousChild element will be non-null if
        /// the referenceChild has a previous sibling. If the referenceChild is the first
        /// child, the output is null.</param>
        void GetPreviousChild( _In_ ID2D1SvgElement* referenceChild, ID2D1SvgElement** previousChild ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetPreviousChild( referenceChild, previousChild );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void GetPreviousChild( const SvgElement& referenceChild, ID2D1SvgElement** previousChild ) const
        {
            GetPreviousChild( referenceChild.GetInterfacePointer<ID2D1SvgElement>( ), previousChild );
        }

        SvgElement GetPreviousChild( _In_ ID2D1SvgElement* referenceChild ) const
        {
            ID2D1SvgElement* ptr = nullptr;
            GetPreviousChild( referenceChild, &ptr );
            return SvgElement( ptr );
        }
        SvgElement GetPreviousChild( const SvgElement& referenceChild ) const
        {
            return GetPreviousChild( referenceChild.GetInterfacePointer<ID2D1SvgElement>( ) );
        }


        /// <summary>
        /// Gets the next sibling of the referenceChild element.
        /// </summary>
        /// <param name="referenceChild">The referenceChild must be an immediate child of
        /// this element.</param>
        /// <param name="nextChild">The output nextChild element will be non-null if the
        /// referenceChild has a next sibling. If the referenceChild is the last child, the
        /// output is null.</param>
        void GetNextChild( _In_ ID2D1SvgElement* referenceChild, ID2D1SvgElement** nextChild ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetNextChild( referenceChild, nextChild );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void GetNextChild( const SvgElement& referenceChild, ID2D1SvgElement** nextChild ) const
        {
            GetNextChild( referenceChild.GetInterfacePointer<ID2D1SvgElement>( ), nextChild );
        }

        SvgElement GetNextChild( _In_ ID2D1SvgElement* referenceChild ) const
        {
            ID2D1SvgElement* ptr = nullptr;
            GetNextChild( referenceChild, &ptr );
            return SvgElement( ptr );
        }
        SvgElement GetNextChild( const SvgElement& referenceChild ) const
        {
            return GetNextChild( referenceChild.GetInterfacePointer<ID2D1SvgElement>( ) );
        }


        /// <summary>
        /// Inserts newChild as a child of this element, before the referenceChild element.
        /// If the newChild element already has a parent, it is removed from this parent as
        /// part of the insertion. Returns an error if this element cannot accept children
        /// of the type of newChild. Returns an error if the newChild is an ancestor of this
        /// element.
        /// </summary>
        /// <param name="newChild">The element to be inserted.</param>
        /// <param name="referenceChild">The element that the child should be inserted
        /// before. If referenceChild is null, the newChild is placed as the last child. If
        /// referenceChild is non-null, it must be an immediate child of this element.
        /// </param>
        void InsertChildBefore( _In_ ID2D1SvgElement* newChild, _In_opt_ ID2D1SvgElement* referenceChild = nullptr ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->InsertChildBefore( newChild, referenceChild );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void InsertChildBefore( const SvgElement& newChild, _In_opt_ ID2D1SvgElement* referenceChild = nullptr ) const
        {
            InsertChildBefore( newChild.GetInterfacePointer<ID2D1SvgElement>( ), referenceChild );
        }
        void InsertChildBefore( const SvgElement& newChild, const SvgElement& referenceChild ) const
        {
            InsertChildBefore( newChild.GetInterfacePointer<ID2D1SvgElement>( ), referenceChild.GetInterfacePointer<ID2D1SvgElement>( ) );
        }

        /// <summary>
        /// Appends newChild to the list of children. If the newChild element already has a
        /// parent, it is removed from this parent as part of the append operation. Returns
        /// an error if this element cannot accept children of the type of newChild. Returns
        /// an error if the newChild is an ancestor of this element.
        /// </summary>
        /// <param name="newChild">The element to be appended.</param>
        void AppendChild( _In_ ID2D1SvgElement* newChild ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->AppendChild( newChild );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void AppendChild( const SvgElement& newChild ) const
        {
            AppendChild( newChild.GetInterfacePointer<ID2D1SvgElement>( ) );
        }

        /// <summary>
        /// Replaces the oldChild element with the newChild. This operation removes the
        /// oldChild from the tree. If the newChild element already has a parent, it is
        /// removed from this parent as part of the replace operation. Returns an error if
        /// this element cannot accept children of the type of newChild. Returns an error if
        /// the newChild is an ancestor of this element.
        /// </summary>
        /// <param name="newChild">The element to be inserted.</param>
        /// <param name="oldChild">The child element to be replaced. The oldChild element
        /// must be an immediate child of this element.</param>
        void ReplaceChild( _In_ ID2D1SvgElement* newChild, _In_ ID2D1SvgElement* oldChild ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->ReplaceChild( newChild, oldChild );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void ReplaceChild( const SvgElement& newChild, _In_ ID2D1SvgElement* oldChild ) const
        {
            ReplaceChild( newChild.GetInterfacePointer<ID2D1SvgElement>( ), oldChild );
        }
        void ReplaceChild( _In_ ID2D1SvgElement* newChild, const SvgElement& oldChild ) const
        {
            ReplaceChild( newChild, oldChild.GetInterfacePointer<ID2D1SvgElement>( ) );
        }
        void ReplaceChild( const SvgElement& newChild, const SvgElement& oldChild ) const
        {
            ReplaceChild( newChild.GetInterfacePointer<ID2D1SvgElement>( ), oldChild.GetInterfacePointer<ID2D1SvgElement>( ) );
        }

        /// <summary>
        /// Removes the oldChild from the tree. Children of oldChild remain children of
        /// oldChild.
        /// </summary>
        /// <param name="oldChild">The child element to be removed. The oldChild element
        /// must be an immediate child of this element.</param>
        void RemoveChild( _In_ ID2D1SvgElement* oldChild ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->RemoveChild( oldChild );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void RemoveChild( const SvgElement& oldChild ) const
        {
            RemoveChild( oldChild.GetInterfacePointer<ID2D1SvgElement>( ) );
        }

        /// <summary>
        /// Creates an element from a tag name. The element is appended to the list of
        /// children. Returns an error if this element cannot accept children of the
        /// specified type.
        /// </summary>
        /// <param name="tagName">The tag name of the new child. An empty string is
        /// interpreted to be a text content element.</param>
        /// <param name="newChild">The new child element.</param>
        void CreateChild( _In_ PCWSTR tagName, ID2D1SvgElement** newChild ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateChild( tagName, newChild );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        SvgElement CreateChild( _In_ PCWSTR tagName ) const
        {
            ID2D1SvgElement* ptr = nullptr;
            CreateChild( tagName, &ptr );
            return SvgElement( ptr );
        }

        /// <summary>
        /// Returns true if the attribute is explicitly set on the element or if it is
        /// present within an inline style. Returns FALSE if the attribute is not a valid
        /// attribute on this element.
        /// </summary>
        /// <param name="name">The name of the attribute.</param>
        /// <param name="inherited">Outputs whether the attribute is set to the 'inherit'
        /// value.</param>
        bool IsAttributeSpecified( _In_ PCWSTR name, BOOL* inherited = NULL ) const
        {
            auto* pInterface = GetInterface( );
            return pInterface->IsAttributeSpecified( name, inherited ) != FALSE;
        }

        /// <summary>
        /// Returns the number of specified attributes on this element. Attributes are only
        /// considered specified if they are explicitly set on the element or present within
        /// an inline style. Properties that receive their value through CSS inheritance are
        /// not considered specified. An attribute can become specified if it is set through
        /// a method call. It can become unspecified if it is removed via RemoveAttribute.
        /// </summary>
        UINT32 GetSpecifiedAttributeCount( ) const
        {
            auto* pInterface = GetInterface( );
            return pInterface->GetSpecifiedAttributeCount( );
        }

        /// <summary>
        /// Gets the name of the specified attribute at the given index.
        /// </summary>
        /// <param name="index">The specified index of the attribute.</param>
        /// <param name="name">Outputs the name of the attribute.</param>
        /// <param name="inherited">Outputs whether the attribute is set to the 'inherit'
        /// value.</param>
        void GetSpecifiedAttributeName( UINT32 index, PWSTR name, UINT32 nameCount, _Out_opt_ BOOL* inherited = nullptr ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetSpecifiedAttributeName( index, name, nameCount, inherited );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        std::wstring GetSpecifiedAttributeName( UINT32 index, _Out_opt_ BOOL* inherited = nullptr ) const
        {
             UINT32 attributeNameLength = GetSpecifiedAttributeNameLength( index );
             std::wstring result;
             result.resize( static_cast<size_t>( attributeNameLength ) );
             GetSpecifiedAttributeName( index, result.data( ), attributeNameLength, inherited );
             return result;
        }

        /// <summary>
        /// Gets the string length of the name of the specified attribute at the given
        /// index. The output string length does not include room for the null terminator.
        /// </summary>
        /// <param name="index">The specified index of the attribute.</param>
        /// <param name="nameLength">Outputs the string length of the name of the specified
        /// attribute.</param>
        /// <param name="inherited">Outputs whether the attribute is set to the 'inherit'
        /// value.</param>
        void GetSpecifiedAttributeNameLength( UINT32 index, _Out_ UINT32* nameLength, _Out_opt_ BOOL* inherited = nullptr ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetSpecifiedAttributeNameLength( index, nameLength, inherited );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        UINT32 GetSpecifiedAttributeNameLength( UINT32 index, _Out_opt_ BOOL* inherited = nullptr ) const
        {
            UINT32 result = 0;
            GetSpecifiedAttributeNameLength( index, &result, inherited );
            return result;
        }


        /// <summary>
        /// Removes the attribute from this element. Also removes this attribute from within
        /// an inline style if present. Returns an error if the attribute name is not valid
        /// on this element.
        /// </summary>
        void RemoveAttribute( _In_ PCWSTR name ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->RemoveAttribute( name );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Sets the value of a text content element.
        /// </summary>
        void SetTextValue( const WCHAR* value, UINT32 valueCount ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->SetTextValue( value, valueCount );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void SetTextValue( const std::wstring& value ) const
        {
            SetTextValue( value.c_str(), static_cast<UINT32>( value.size() ) );
        }
        void SetTextValue( const std::wstring_view& value ) const
        {
            SetTextValue( value.data( ), static_cast<UINT32>( value.size( ) ) );
        }

        /// <summary>
        /// Gets the value of a text content element.
        /// </summary>
        void GetTextValue(PWSTR value, UINT32 valueCount ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetTextValue( value, valueCount );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        std::wstring GetTextValue( ) const
        {
            auto textValueLength = GetTextValueLength( );
            std::wstring result;
            result.resize( static_cast<size_t>( textValueLength ) );
            GetTextValue( result.data(), textValueLength );
            return result;
        }

        /// <summary>
        /// Gets the length of the text content value. The returned string length does not
        /// include room for the null terminator.
        /// </summary>
        UINT32 GetTextValueLength( ) const
        {
            auto* pInterface = GetInterface( );
            return pInterface->GetTextValueLength( );
        }

        /// <summary>
        /// Sets an attribute of this element using a string. Returns an error if the
        /// attribute name is not valid on this element. Returns an error if the attribute
        /// cannot be expressed as the specified type.
        /// </summary>
        void SetAttributeValue( _In_ PCWSTR name, D2D1_SVG_ATTRIBUTE_STRING_TYPE type, _In_ PCWSTR value ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->SetAttributeValue( name, type, value );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Gets an attribute of this element as a string. Returns an error if the attribute
        /// is not specified. Returns an error if the attribute name is not valid on this
        /// element. Returns an error if the attribute cannot be expressed as the specified
        /// string type.
        /// </summary>
        void GetAttributeValue( _In_ PCWSTR name, D2D1_SVG_ATTRIBUTE_STRING_TYPE type, PWSTR value, UINT32 valueCount ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetAttributeValue( name, type, value, valueCount );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        std::wstring GetAttributeValue( _In_ PCWSTR name, D2D1_SVG_ATTRIBUTE_STRING_TYPE type = D2D1_SVG_ATTRIBUTE_STRING_TYPE_SVG ) const
        {
            auto attributeValueLength = GetAttributeValueLength( name, type );
            std::wstring result;
            result.resize( static_cast<size_t>( attributeValueLength ) );
            GetAttributeValue( name, type, result.data( ), attributeValueLength );
            return result;
        }

        /// <summary>
        /// Gets the string length of an attribute of this element. The returned string
        /// length does not include room for the null terminator. Returns an error if the
        /// attribute is not specified. Returns an error if the attribute name is not valid
        /// on this element. Returns an error if the attribute cannot be expressed as the
        /// specified string type.
        /// </summary>
        void GetAttributeValueLength( _In_ PCWSTR name, D2D1_SVG_ATTRIBUTE_STRING_TYPE type, _Out_ UINT32* valueLength ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetAttributeValueLength( name, type, valueLength );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        UINT32 GetAttributeValueLength( _In_ PCWSTR name, D2D1_SVG_ATTRIBUTE_STRING_TYPE type ) const
        {
            UINT32 result = 0;
            GetAttributeValueLength( name, type, &result );
            return result;
        }


        /// <summary>
        /// Sets an attribute of this element using a POD type. Returns an error if the
        /// attribute name is not valid on this element. Returns an error if the attribute
        /// cannot be expressed as the specified type.
        /// </summary>
        void SetAttributeValue( _In_ PCWSTR name, D2D1_SVG_ATTRIBUTE_POD_TYPE type, const void* value, UINT32 valueSizeInBytes ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->SetAttributeValue( name, type, value, valueSizeInBytes );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Gets an attribute of this element as a POD type. Returns an error if the
        /// attribute is not specified. Returns an error if the attribute name is not valid
        /// on this element. Returns an error if the attribute cannot be expressed as the
        /// specified POD type.
        /// </summary>
        void GetAttributeValue( _In_ PCWSTR name, D2D1_SVG_ATTRIBUTE_POD_TYPE type, void* value, UINT32 valueSizeInBytes ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetAttributeValue( name, type, value, valueSizeInBytes );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Sets an attribute of this element using an interface. Returns an error if the
        /// attribute name is not valid on this element. Returns an error if the attribute
        /// cannot be expressed as the specified interface type. Returns an error if the
        /// attribute object is already set on an element. A given attribute object may only
        /// be set on one element in one attribute location at a time.
        /// </summary>
        void SetAttributeValue( _In_ PCWSTR name, _In_ ID2D1SvgAttribute* value ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->SetAttributeValue( name, value );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Gets an attribute of this element as an interface type. Returns an error if the
        /// attribute is not specified. Returns an error if the attribute name is not valid
        /// on this element. Returns an error if the attribute cannot be expressed as the
        /// specified interface type.
        /// </summary>
        /// <param name="riid">The interface ID of the attribute value.</param>
        void GetAttributeValue( _In_ PCWSTR name, _In_ REFIID riid, void** value ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetAttributeValue( name, riid, value );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Sets an attribute of this element using a float.
        /// </summary>
        void SetAttributeValue( _In_ PCWSTR name, FLOAT value ) const
        {
            SetAttributeValue( name, D2D1_SVG_ATTRIBUTE_POD_TYPE_FLOAT, &value, sizeof( value ) );
        }

        /// <summary>
        /// Gets an attribute of this element as a float.
        /// </summary>
        void GetAttributeValue( _In_ PCWSTR name, _Out_ FLOAT* value ) const
        {
            GetAttributeValue( name, D2D1_SVG_ATTRIBUTE_POD_TYPE_FLOAT, value, sizeof( *value ) );
        }

        /// <summary>
        /// Sets an attribute of this element as a color.
        /// </summary>
        void SetAttributeValue( _In_ PCWSTR name, CONST D2D1_COLOR_F& value ) const
        {
            SetAttributeValue( name, D2D1_SVG_ATTRIBUTE_POD_TYPE_COLOR, &value, sizeof( value ) );
        }

        /// <summary>
        /// Gets an attribute of this element as a color.
        /// </summary>
        void GetAttributeValue( _In_ PCWSTR name, _Out_ D2D1_COLOR_F* value ) const
        {
            GetAttributeValue( name, D2D1_SVG_ATTRIBUTE_POD_TYPE_COLOR, value, sizeof( *value ) );
        }

        /// <summary>
        /// Sets an attribute of this element as a fill mode. This method can be used to set
        /// the value of the 'fill-rule' or 'clip-rule' properties.
        /// </summary>
        void SetAttributeValue(_In_ PCWSTR name, D2D1_FILL_MODE value ) const
        {
            SetAttributeValue( name, D2D1_SVG_ATTRIBUTE_POD_TYPE_FILL_MODE, &value, sizeof( value ) );
        }

        /// <summary>
        /// Gets an attribute of this element as a fill mode. This method can be used to get
        /// the value of the 'fill-rule' or 'clip-rule' properties.
        /// </summary>
        void GetAttributeValue(_In_ PCWSTR name, _Out_ D2D1_FILL_MODE* value ) const
        {
            GetAttributeValue( name, D2D1_SVG_ATTRIBUTE_POD_TYPE_FILL_MODE, value, sizeof( *value ) );
        }

        /// <summary>
        /// Sets an attribute of this element as a display value. This method can be used to
        /// set the value of the 'display' property.
        /// </summary>
        void SetAttributeValue( _In_ PCWSTR name, D2D1_SVG_DISPLAY value ) const
        {
            SetAttributeValue( name, D2D1_SVG_ATTRIBUTE_POD_TYPE_DISPLAY, &value, sizeof( value ) );
        }

        /// <summary>
        /// Gets an attribute of this element as a display value. This method can be used to
        /// get the value of the 'display' property.
        /// </summary>
        void GetAttributeValue( _In_ PCWSTR name, _Out_ D2D1_SVG_DISPLAY* value ) const
        {
            GetAttributeValue( name, D2D1_SVG_ATTRIBUTE_POD_TYPE_DISPLAY, value, sizeof( *value ) );
        }

        /// <summary>
        /// Sets an attribute of this element as an overflow value. This method can be used
        /// to set the value of the 'overflow' property.
        /// </summary>
        void SetAttributeValue( _In_ PCWSTR name, D2D1_SVG_OVERFLOW value ) const
        {
            SetAttributeValue( name, D2D1_SVG_ATTRIBUTE_POD_TYPE_OVERFLOW, &value, sizeof( value ) );
        }

        /// <summary>
        /// Gets an attribute of this element as an overflow value. This method can be used
        /// to get the value of the 'overflow' property.
        /// </summary>
        void GetAttributeValue(_In_ PCWSTR name, _Out_ D2D1_SVG_OVERFLOW* value ) const
        {
            GetAttributeValue( name, D2D1_SVG_ATTRIBUTE_POD_TYPE_OVERFLOW, value, sizeof( *value ) );
        }

        /// <summary>
        /// Sets an attribute of this element as a line join value. This method can be used
        /// to set the value of the 'stroke-linejoin' property.
        /// </summary>
        void SetAttributeValue( _In_ PCWSTR name, D2D1_SVG_LINE_JOIN value ) const
        {
            SetAttributeValue( name, D2D1_SVG_ATTRIBUTE_POD_TYPE_LINE_JOIN, &value, sizeof( value ) );
        }

        /// <summary>
        /// Gets an attribute of this element as a line join value. This method can be used
        /// to get the value of the 'stroke-linejoin' property.
        /// </summary>
        void GetAttributeValue(_In_ PCWSTR name, _Out_ D2D1_SVG_LINE_JOIN* value ) const
        {
            GetAttributeValue( name, D2D1_SVG_ATTRIBUTE_POD_TYPE_LINE_JOIN, value, sizeof( *value ) );
        }

        /// <summary>
        /// Sets an attribute of this element as a line cap value. This method can be used
        /// to set the value of the 'stroke-linecap' property.
        /// </summary>
        void SetAttributeValue( _In_ PCWSTR name, D2D1_SVG_LINE_CAP value ) const
        {
            SetAttributeValue( name, D2D1_SVG_ATTRIBUTE_POD_TYPE_LINE_CAP, &value, sizeof( value ) );
        }

        /// <summary>
        /// Gets an attribute of this element as a line cap value. This method can be used
        /// to get the value of the 'stroke-linecap' property.
        /// </summary>
        void GetAttributeValue( _In_ PCWSTR name, _Out_ D2D1_SVG_LINE_CAP* value ) const
        {
            GetAttributeValue( name, D2D1_SVG_ATTRIBUTE_POD_TYPE_LINE_CAP, value, sizeof( *value ) );
        }

        /// <summary>
        /// Sets an attribute of this element as a visibility value. This method can be used
        /// to set the value of the 'visibility' property.
        /// </summary>
        void SetAttributeValue( _In_ PCWSTR name, D2D1_SVG_VISIBILITY value ) const
        {
            SetAttributeValue( name, D2D1_SVG_ATTRIBUTE_POD_TYPE_VISIBILITY, &value, sizeof( value ) );
        }

        /// <summary>
        /// Gets an attribute of this element as a visibility value. This method can be used
        /// to get the value of the 'visibility' property.
        /// </summary>
        void GetAttributeValue( _In_ PCWSTR name, _Out_ D2D1_SVG_VISIBILITY* value ) const
        {
            GetAttributeValue( name, D2D1_SVG_ATTRIBUTE_POD_TYPE_VISIBILITY, value, sizeof( *value ) );
        }

        /// <summary>
        /// Sets an attribute of this element as a matrix value. This method can be used to
        /// set the value of a 'transform' or 'gradientTransform' attribute.
        /// </summary>
        void SetAttributeValue( _In_ PCWSTR name, const D2D1_MATRIX_3X2_F& value )
        {
            SetAttributeValue( name, D2D1_SVG_ATTRIBUTE_POD_TYPE_MATRIX, &value, sizeof( value ) );
        }

        /// <summary>
        /// Gets an attribute of this element as a matrix value. This method can be used to
        /// get the value of a 'transform' or 'gradientTransform' attribute.
        /// </summary>
        void GetAttributeValue( _In_ PCWSTR name, _Out_ D2D1_MATRIX_3X2_F* value ) const
        {
            GetAttributeValue( name, D2D1_SVG_ATTRIBUTE_POD_TYPE_MATRIX, value, sizeof( *value ) );
        }

        /// <summary>
        /// Sets an attribute of this element as a unit type value. This method can be used
        /// to set the value of a 'gradientUnits' or 'clipPathUnits' attribute.
        /// </summary>
        void SetAttributeValue(_In_ PCWSTR name, D2D1_SVG_UNIT_TYPE value ) const
        {
            SetAttributeValue( name, D2D1_SVG_ATTRIBUTE_POD_TYPE_UNIT_TYPE, &value, sizeof( value ) );
        }

        /// <summary>
        /// Gets an attribute of this element as a unit type value. This method can be used
        /// to get the value of a 'gradientUnits' or 'clipPathUnits' attribute.
        /// </summary>
        void GetAttributeValue(_In_ PCWSTR name, _Out_ D2D1_SVG_UNIT_TYPE* value ) const
        {
            GetAttributeValue( name, D2D1_SVG_ATTRIBUTE_POD_TYPE_UNIT_TYPE, value, sizeof( *value ) );
        }

        /// <summary>
        /// Sets an attribute of this element as an extend mode value. This method can be
        /// used to set the value of a 'spreadMethod' attribute.
        /// </summary>
        void SetAttributeValue( _In_ PCWSTR name, D2D1_EXTEND_MODE value ) const
        {
            SetAttributeValue( name, D2D1_SVG_ATTRIBUTE_POD_TYPE_EXTEND_MODE, &value, sizeof( value ) );
        }

        /// <summary>
        /// Gets an attribute of this element as a extend mode value. This method can be
        /// used to get the value of a 'spreadMethod' attribute.
        /// </summary>
        void GetAttributeValue( _In_ PCWSTR name, _Out_ D2D1_EXTEND_MODE* value ) const
        {
            GetAttributeValue( name, D2D1_SVG_ATTRIBUTE_POD_TYPE_EXTEND_MODE, value, sizeof( *value ) );
        }

        /// <summary>
        /// Sets an attribute of this element as a preserve aspect ratio value. This method
        /// can be used to set the value of a 'preserveAspectRatio' attribute.
        /// </summary>
        void SetAttributeValue( _In_ PCWSTR name, CONST D2D1_SVG_PRESERVE_ASPECT_RATIO& value ) const
        {
            SetAttributeValue( name, D2D1_SVG_ATTRIBUTE_POD_TYPE_PRESERVE_ASPECT_RATIO, &value, sizeof( value ) );
        }

        /// <summary>
        /// Gets an attribute of this element as a preserve aspect ratio value. This method
        /// can be used to get the value of a 'preserveAspectRatio' attribute.
        /// </summary>
        void GetAttributeValue( _In_ PCWSTR name, _Out_ D2D1_SVG_PRESERVE_ASPECT_RATIO* value ) const
        {
            GetAttributeValue( name, D2D1_SVG_ATTRIBUTE_POD_TYPE_PRESERVE_ASPECT_RATIO, value, sizeof( *value ) );
        }

        /// <summary>
        /// Sets an attribute of this element as a length value.
        /// </summary>
        void SetAttributeValue( _In_ PCWSTR name, const D2D1_SVG_LENGTH& value ) const
        {
            SetAttributeValue( name, D2D1_SVG_ATTRIBUTE_POD_TYPE_LENGTH, &value, sizeof( value ) );
        }

        /// <summary>
        /// Gets an attribute of this element as length value.
        /// </summary>
        void GetAttributeValue( _In_ PCWSTR name, _Out_ D2D1_SVG_LENGTH* value ) const
        {
            GetAttributeValue( name, D2D1_SVG_ATTRIBUTE_POD_TYPE_LENGTH, value, sizeof( *value ) );
        }

        /// <summary>
        /// Gets an attribute of this element.
        /// </summary>
        void GetAttributeValue( _In_ PCWSTR name, ID2D1SvgAttribute** value ) const
        {
            GetAttributeValue( name, IID_ID2D1SvgAttribute, reinterpret_cast<void**>( value ) );
        }

        /// <summary>
        /// Gets an attribute of this element as a paint. This method can be used to get the
        /// value of the 'fill' or 'stroke' properties.
        /// </summary>
        void GetAttributeValue( _In_ PCWSTR name, ID2D1SvgPaint** value ) const
        {
            GetAttributeValue( name, IID_ID2D1SvgPaint, reinterpret_cast<void**>( value ) );
        }

        /// <summary>
        /// Gets an attribute of this element as a stroke dash array. This method can be
        /// used to get the value of the 'stroke-dasharray' property.
        /// </summary>
        void GetAttributeValue( _In_ PCWSTR name, ID2D1SvgStrokeDashArray** value ) const
        {
            GetAttributeValue( name, IID_ID2D1SvgStrokeDashArray, reinterpret_cast<void**>( value ) );
        }

        /// <summary>
        /// Gets an attribute of this element as points. This method can be used to get the
        /// value of the 'points' attribute on a 'polygon' or 'polyline' element.
        /// </summary>
        void GetAttributeValue( _In_ PCWSTR name, ID2D1SvgPointCollection** value ) const
        {
            GetAttributeValue( name, IID_ID2D1SvgPointCollection, reinterpret_cast<void**>( value ) );
        }

        /// <summary>
        /// Gets an attribute of this element as path data. This method can be used to get
        /// the value of the 'd' attribute on a 'path' element.
        /// </summary>
        void GetAttributeValue( _In_ PCWSTR name, ID2D1SvgPathData** value ) const
        {
            GetAttributeValue( name, IID_ID2D1SvgPathData, reinterpret_cast<void**>( value ) );
        }
    };

    class SvgDocument : public Resource
    {
    public:
        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( SvgDocument, Resource, ID2D1SvgDocument, ID2D1Resource )

        /// <summary>
        /// Sets the size of the initial viewport.
        /// </summary>
        void SetViewportSize( const D2D1_SIZE_F& viewportSize ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->SetViewportSize( viewportSize );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Returns the size of the initial viewport.
        /// </summary>
        D2D1_SIZE_F GetViewportSize( ) const
        {
            auto* pInterface = GetInterface( );
            return pInterface->GetViewportSize( );
        }

        /// <summary>
        /// Sets the root element of the document. The root element must be an 'svg'
        /// element. If the element already exists within an svg tree, it is first removed.
        /// </summary>
        void SetRoot( _In_opt_ ID2D1SvgElement* root ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->SetRoot( root );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void SetRoot( const SvgElement& root ) const
        {
            SetRoot( root.GetInterfacePointer<ID2D1SvgElement>( ) );
        }

        /// <summary>
        /// Gets the root element of the document.
        /// </summary>
        void GetRoot( ID2D1SvgElement** root ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->GetRoot( root );
        }
        SvgElement GetRoot( ) const
        {
            ID2D1SvgElement* ptr = nullptr;
            GetRoot( &ptr );
            return SvgElement( ptr );
        }

        /// <summary>
        /// Gets the SVG element with the specified ID. If the element cannot be found, the
        /// returned element will be null.
        /// </summary>
        void FindElementById( _In_ PCWSTR id, ID2D1SvgElement** svgElement ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->FindElementById( id, svgElement );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        SvgElement FindElementById( _In_ PCWSTR id ) const
        {
            ID2D1SvgElement* ptr = nullptr;
            FindElementById( id, &ptr );
            return SvgElement( ptr );
        }


        /// <summary>
        /// Serializes an element and its subtree to XML. The output XML is encoded as
        /// UTF-8.
        /// </summary>
        /// <param name="outputXmlStream">An output stream to contain the SVG XML subtree.
        /// </param>
        /// <param name="subtree">The root of the subtree. If null, the entire document is
        /// serialized.</param>
        void Serialize( _In_ IStream* outputXmlStream, _In_opt_ ID2D1SvgElement* subtree = nullptr ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->Serialize( outputXmlStream, subtree );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void Serialize( const Stream& outputXmlStream, _In_opt_ ID2D1SvgElement* subtree = nullptr ) const
        {
            Serialize( outputXmlStream.GetInterfacePointer<IStream>( ), subtree );
        }
        void Serialize( const Stream& outputXmlStream, const SvgElement& subtree ) const
        {
            Serialize( outputXmlStream.GetInterfacePointer<IStream>( ), subtree.GetInterfacePointer<ID2D1SvgElement>( ) );
        }

        /// <summary>
        /// Deserializes a subtree from the stream. The stream must have only one root
        /// element, but that root element need not be an 'svg' element. The output element
        /// is not inserted into this document tree.
        /// </summary>
        /// <param name="inputXmlStream">An input stream containing the SVG XML subtree.
        /// </param>
        /// <param name="subtree">The root of the subtree.</param>
        void Deserialize( _In_ IStream* inputXmlStream, ID2D1SvgElement** subtree ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->Deserialize( inputXmlStream, subtree );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void Deserialize( const Stream& inputXmlStream, ID2D1SvgElement** subtree ) const
        {
            Deserialize( inputXmlStream.GetInterfacePointer<IStream>( ), subtree );
        }
        SvgElement Deserialize( _In_ IStream* inputXmlStream ) const
        {
            ID2D1SvgElement* ptr = nullptr;
            Deserialize( inputXmlStream, &ptr );
            return SvgElement( ptr );
        }
        SvgElement Deserialize( const Stream& inputXmlStream ) const
        {
            return Deserialize( inputXmlStream.GetInterfacePointer<IStream>( ) );
        }

        /// <summary>
        /// Creates a paint object which can be used to set the 'fill' or 'stroke'
        /// properties.
        /// </summary>
        /// <param name="color">The color used if the paintType is
        /// D2D1_SVG_PAINT_TYPE_COLOR.</param>
        /// <param name="id">The element id which acts as the paint server. This id is used
        /// if the paint type is D2D1_SVG_PAINT_TYPE_URI.</param>
        void CreatePaint( D2D1_SVG_PAINT_TYPE paintType, _In_opt_ const D2D1_COLOR_F* color, _In_opt_ PCWSTR id, ID2D1SvgPaint** paint ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreatePaint( paintType, color, id, paint );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        SvgPaint CreatePaint( D2D1_SVG_PAINT_TYPE paintType, _In_opt_ const D2D1_COLOR_F* color = nullptr, _In_opt_ PCWSTR id = nullptr ) const
        {
            ID2D1SvgPaint* ptr = nullptr;
            CreatePaint( paintType, color, id, &ptr );
            return SvgPaint( ptr );
        }
        SvgPaint CreatePaint( const D2D1_COLOR_F* color ) const
        {
            return CreatePaint( D2D1_SVG_PAINT_TYPE_COLOR, color, nullptr );
        }
        SvgPaint CreatePaint( PCWSTR id ) const
        {
            return CreatePaint( D2D1_SVG_PAINT_TYPE_URI, nullptr, id );
        }


        /// <summary>
        /// Creates a dash array object which can be used to set the 'stroke-dasharray'
        /// property.
        /// </summary>
        void CreateStrokeDashArray( const D2D1_SVG_LENGTH* dashes, UINT32 dashesCount, ID2D1SvgStrokeDashArray** strokeDashArray ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateStrokeDashArray( dashes, dashesCount, strokeDashArray );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        SvgStrokeDashArray CreateStrokeDashArray( const D2D1_SVG_LENGTH* dashes, UINT32 dashesCount ) const
        {
            ID2D1SvgStrokeDashArray* ptr = nullptr;
            CreateStrokeDashArray( dashes, dashesCount, &ptr );
            return SvgStrokeDashArray( ptr );
        }

        /// <summary>
        /// Creates a points object which can be used to set a 'points' attribute on a
        /// 'polygon' or 'polyline' element.
        /// </summary>
        void CreatePointCollection( const D2D1_POINT_2F* points, UINT32 pointsCount, ID2D1SvgPointCollection** pointCollection ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreatePointCollection( points, pointsCount, pointCollection );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        SvgPointCollection CreatePointCollection( const D2D1_POINT_2F* points, UINT32 pointsCount ) const
        {
            ID2D1SvgPointCollection* ptr = nullptr;
            CreatePointCollection( points, pointsCount, &ptr );
            return SvgPointCollection( ptr );
        }

        /// <summary>
        /// Creates a path data object which can be used to set a 'd' attribute on a 'path'
        /// element.
        /// </summary>
        void CreatePathData( const FLOAT* segmentData, UINT32 segmentDataCount, const D2D1_SVG_PATH_COMMAND* commands, UINT32 commandsCount, ID2D1SvgPathData** pathData ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreatePathData( segmentData, segmentDataCount, commands, commandsCount, pathData );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        SvgPathData CreatePathData( const FLOAT* segmentData, UINT32 segmentDataCount, const D2D1_SVG_PATH_COMMAND* commands, UINT32 commandsCount ) const
        {
            ID2D1SvgPathData* ptr = nullptr;
            CreatePathData( segmentData, segmentDataCount, commands, commandsCount, &ptr );
            return SvgPathData( ptr );
        }

    };



    inline SvgDocument SvgElement::GetDocument( ) const
    {
        ID2D1SvgDocument* ptr = nullptr;
        GetDocument( &ptr );
        return SvgDocument( ptr );
    }

    /// <summary>
    /// This class performs all the same functions as the DeviceContext4 (ID2D1DeviceContext4) class, 
    /// plus it enables the creation of color contexts and Svg documents.
    /// </summary>
    class DeviceContext5 : public DeviceContext4
    {
    public:
        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( DeviceContext5, DeviceContext4, ID2D1DeviceContext5, ID2D1DeviceContext4 )
        /// <summary>
        /// Creates an SVG document from a stream.
        /// </summary>
        /// <param name="inputXmlStream">
        /// An input stream containing the SVG XML document. If null, an empty document is created.
        /// </param>
        /// <param name="viewportSize">
        /// Size of the initial viewport of the document.
        /// </param>
        /// <param name="svgDocument">
        /// When this method returns, contains a pointer to the created SVG document.
        /// </param>
        void CreateSvgDocument( _In_opt_ IStream* inputXmlStream, const D2D1_SIZE_F& viewportSize, ID2D1SvgDocument** svgDocument ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateSvgDocument( inputXmlStream, viewportSize, svgDocument );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void CreateSvgDocument( const Stream& inputXmlStream, const D2D1_SIZE_F& viewportSize, ID2D1SvgDocument** svgDocument ) const
        {
            CreateSvgDocument( inputXmlStream.GetInterfacePointer<IStream>( ), viewportSize, svgDocument );
        }
        SvgDocument CreateSvgDocument( _In_opt_ IStream* inputXmlStream, const D2D1_SIZE_F& viewportSize ) const
        {
            ID2D1SvgDocument* ptr = nullptr;
            CreateSvgDocument( inputXmlStream, viewportSize, &ptr );
            return SvgDocument( ptr );
        }
        SvgDocument CreateSvgDocument( const Stream& inputXmlStream, const D2D1_SIZE_F& viewportSize ) const
        {
            return CreateSvgDocument( inputXmlStream.GetInterfacePointer<IStream>( ), viewportSize );
        }

        /// <summary>
        /// Draw an SVG document.
        /// </summary>
        /// <param name="svgDocument">
        /// The SVG document to draw.
        /// </param>
        void DrawSvgDocument( _In_ ID2D1SvgDocument* svgDocument ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->DrawSvgDocument( svgDocument );
        }
        void DrawSvgDocument( const SvgDocument& svgDocument ) const
        {
            DrawSvgDocument( svgDocument.GetInterfacePointer<ID2D1SvgDocument>( ) );
        }

        /// <summary>
        /// Creates a color context from a DXGI color space type. It is only valid to use
        /// this with the Color Management Effect in 'Best' mode.
        /// </summary>
        /// <param name="colorSpace">
        /// The color space to create the color context from.
        /// </param>
        /// <param name="colorContext">
        /// The created color context.
        /// </param>
        void CreateColorContextFromDxgiColorSpace( DXGI_COLOR_SPACE_TYPE colorSpace, ID2D1ColorContext1** colorContext ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateColorContextFromDxgiColorSpace( colorSpace, colorContext );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        ColorContext1 CreateColorContextFromDxgiColorSpace( DXGI_COLOR_SPACE_TYPE colorSpace ) const
        {
            ID2D1ColorContext1* ptr = nullptr;
            CreateColorContextFromDxgiColorSpace( colorSpace, &ptr );
            return ColorContext1( ptr );
        }


        /// <summary>
        /// Creates a color context from a simple color profile. It is only valid to use
        /// this with the Color Management Effect in 'Best' mode.
        /// </summary>
        /// <param name="simpleProfile">
        /// The simple color profile to create the color context from.
        /// </param>
        /// <param name="colorContext">
        /// The created color context.
        /// </param>
        void CreateColorContextFromSimpleColorProfile( const D2D1_SIMPLE_COLOR_PROFILE* simpleProfile, ID2D1ColorContext1** colorContext ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateColorContextFromSimpleColorProfile( simpleProfile, colorContext );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void CreateColorContextFromSimpleColorProfile( const D2D1_SIMPLE_COLOR_PROFILE& simpleProfile, ID2D1ColorContext1** colorContext ) const
        {
            return CreateColorContextFromSimpleColorProfile( &simpleProfile, colorContext );
        }

        ColorContext1 CreateColorContextFromSimpleColorProfile( const D2D1_SIMPLE_COLOR_PROFILE* simpleProfile ) const
        {
            ID2D1ColorContext1* ptr = nullptr;
            CreateColorContextFromSimpleColorProfile( simpleProfile, &ptr );
            return ColorContext1( ptr );
        }

    };

    /// <summary>
    /// Represents a resource domain whose objects and device contexts can be used together. 
    /// This class performs all the same functions as the Device4 (ID2D1Device4) class. It 
    /// also enables the creation of ID2D1DeviceContext5 objects.
    /// </summary>
    class Device5 : public Device4
    {
    public:
        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( Device5, Device4, ID2D1Device5, ID2D1Device4 )

        /// <summary>
        /// Creates a new device context with no initially assigned target.
        /// </summary>
        /// <param name="options">
        /// Options for creating the device context.
        /// The default is D2D1_DEVICE_CONTEXT_OPTIONS_NONE.
        /// </param>
        /// <param name="deviceContext5">
        /// The created device context.
        /// </param>
        void CreateDeviceContext( D2D1_DEVICE_CONTEXT_OPTIONS options, ID2D1DeviceContext5** deviceContext5 ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateDeviceContext( options, deviceContext5 );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        DeviceContext5 CreateDeviceContext( D2D1_DEVICE_CONTEXT_OPTIONS options = D2D1_DEVICE_CONTEXT_OPTIONS_NONE ) const
        {
            ID2D1DeviceContext5* ptr = nullptr;
            CreateDeviceContext( options, &ptr );
            return DeviceContext5( ptr );
        }

        DeviceContext5 CreateDeviceContext5( D2D1_DEVICE_CONTEXT_OPTIONS options = D2D1_DEVICE_CONTEXT_OPTIONS_NONE ) const
        {
            return CreateDeviceContext( options );
        }
    };

    /// <summary>
    ///
    /// </summary>
    class Factory6 : public Factory5
    {
    public:
        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( Factory6, Factory5, ID2D1Factory6, ID2D1Factory5 )

        Factory6( D2D1_FACTORY_TYPE factoryType )
        {
            ID2D1Factory6* d2d1Factory6 = nullptr;
            auto hr = D2D1CreateFactory( factoryType, __uuidof( ID2D1Factory6 ), (void**)&d2d1Factory6 );
            HCC_COM_CHECK_HRESULT( hr );
            unknown_ = d2d1Factory6;
        }
        /// <summary>
        /// This creates a new Direct2D device from the given IDXGIDevice.
        /// </summary>
        /// <param name="dxgiDevice">
        /// The IDXGIDevice to create the Direct2D device from.
        /// </param>
        /// <param name="d2dDevice5">
        /// The created device.
        /// </param>
        void CreateDevice( _In_ IDXGIDevice* dxgiDevice, ID2D1Device5** d2dDevice5 ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateDevice( dxgiDevice, d2dDevice5 );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void CreateDevice( const DXGI::Device& dxgiDevice, ID2D1Device5** d2dDevice5 ) const
        {
            CreateDevice( dxgiDevice.GetInterfacePointer<IDXGIDevice>( ), d2dDevice5 );
        }
        Device5 CreateDevice( _In_ IDXGIDevice* dxgiDevice ) const
        {
            ID2D1Device5* ptr = nullptr;
            CreateDevice( dxgiDevice, &ptr );
            return Device5( ptr );
        }
        Device5 CreateDevice( const DXGI::Device& dxgiDevice ) const
        {
            return CreateDevice( dxgiDevice.GetInterfacePointer<IDXGIDevice>( ) );
        }

        Device5 CreateDevice5( _In_ IDXGIDevice* dxgiDevice ) const
        {
            return CreateDevice( dxgiDevice );
        }
        Device5 CreateDevice5( const DXGI::Device& dxgiDevice ) const
        {
            return CreateDevice( dxgiDevice );
        }

    };

    /// <summary>
    /// This class performs all the same functions as the existing CommandSink4 
    /// (ID2D1CommandSink4) class, plus it enables access to the BlendImage method.
    /// </summary>
    class CommandSink5 : public CommandSink4
    {
    public:
        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( CommandSink5, CommandSink4, ID2D1CommandSink5, ID2D1CommandSink4 )
        /// <summary>
        /// Draws an image to the device context using the specified blend mode. 
        /// Results are equivalent to using Direct2D's built-in Blend effect.
        /// </summary>
        /// <param name="image">
        /// The image to be drawn to the device context.
        /// </param>
        /// <param name="blendMode">
        /// The blend mode to be used. See Blend modes for more info.
        /// </param>
        /// <param name="targetOffset">
        /// The offset in the destination space that the image will be rendered to. The 
        /// entire logical extent of the image will be rendered to the corresponding 
        /// destination. If not specified, the destination origin will be (0, 0). The 
        /// top-left corner of the image will be mapped to the target offset. This 
        /// will not necessarily be the origin. The default value is nullptr.
        /// </param>
        /// <param name="imageRectangle">
        /// The corresponding rectangle in the image space will be mapped to the given 
        /// origins when processing the image. The default value is nullptr.
        /// </param>
        /// <param name="interpolationMode">
        /// The interpolation mode that will be used to scale the image if necessary. 
        /// The default value is D2D1_INTERPOLATION_MODE_LINEAR.
        /// </param>
        void BlendImage( _In_ ID2D1Image* image, D2D1_BLEND_MODE blendMode, const D2D1_POINT_2F* targetOffset = nullptr, _In_opt_ const D2D1_RECT_F* imageRectangle = nullptr, D2D1_INTERPOLATION_MODE interpolationMode = D2D1_INTERPOLATION_MODE_LINEAR ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->BlendImage( image, blendMode, targetOffset, imageRectangle, interpolationMode );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    /// <summary>
    /// This class performs all the same functions as the existing 
    /// DeviceContext5 (ID2D1DeviceContext5) class, plus it provides 
    /// access to the BlendImage method.
    /// </summary>
    class DeviceContext6 : public DeviceContext5
    {
    public:
        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( DeviceContext6, DeviceContext5, ID2D1DeviceContext6, ID2D1DeviceContext5 )

        /// <summary>
        /// Draw an image to the device context.
        /// </summary>
        /// <param name="image">
        /// The image to be drawn to the device context.
        /// </param>
        /// <param name="blendMode">
        /// The blend mode to be used. 
        /// </param>
        /// <param name="targetOffset">
        /// The offset in the destination space that the image will be rendered to. 
        /// The entire logical extent of the image will be rendered to the corresponding 
        /// destination. If not specified, the destination origin will be (0, 0). The 
        /// top-left corner of the image will be mapped to the target offset. This will 
        /// not necessarily be the origin. The default value is nullptr.
        /// </param>
        /// <param name="imageRectangle">
        /// The corresponding rectangle in the image space will be mapped to the given 
        /// origins when processing the image. The default value is nullptr.
        /// </param>
        /// <param name="interpolationMode">
        /// The interpolation mode that will be used to scale the image if necessary. 
        /// The default value is D2D1_INTERPOLATION_MODE_LINEAR.
        /// </param>
        void BlendImage( _In_ ID2D1Image* image, D2D1_BLEND_MODE blendMode, _In_opt_ const D2D1_POINT_2F* targetOffset = nullptr, _In_opt_ const D2D1_RECT_F* imageRectangle = nullptr, D2D1_INTERPOLATION_MODE interpolationMode = D2D1_INTERPOLATION_MODE_LINEAR ) const
        {
            auto* pInterface = GetInterface( );
            pInterface->BlendImage( image, blendMode, targetOffset, imageRectangle, interpolationMode );
        }
    };

    /// <summary>
    /// Represents a resource domain whose objects and device contexts can be 
    /// used together. This class performs all the same functions as the Device5 
    /// (ID2D1Device5) class, plus it enables the creation of ID2D1DeviceContext6 
    /// objects.
    /// </summary>
    class Device6 : public Device5
    {
    public:
        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( Device6, Device5, ID2D1Device6, ID2D1Device5 )
        /// <summary>
        /// Creates a new device context with no initially assigned target.
        /// </summary>
        /// <param name="options">
        /// Options for creating the device context.
        /// The default is D2D1_DEVICE_CONTEXT_OPTIONS_NONE
        /// </param>
        /// <param name="deviceContext6">
        /// The created device context.
        /// </param>
        void CreateDeviceContext( D2D1_DEVICE_CONTEXT_OPTIONS options, ID2D1DeviceContext6** deviceContext6 ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateDeviceContext( options, deviceContext6 );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        DeviceContext6 CreateDeviceContext( D2D1_DEVICE_CONTEXT_OPTIONS options = D2D1_DEVICE_CONTEXT_OPTIONS_NONE ) const
        {
            ID2D1DeviceContext6* ptr = nullptr;
            CreateDeviceContext( options, &ptr );
            return DeviceContext6( ptr );
        }
        DeviceContext6 CreateDeviceContext6( D2D1_DEVICE_CONTEXT_OPTIONS options = D2D1_DEVICE_CONTEXT_OPTIONS_NONE ) const
        {
            return CreateDeviceContext( options );
        }

    };

    /// <summary>
    /// Creates Direct2D resources. This class performs all the same 
    /// functions as the Factory6 (ID2D1Factory6) class, plus it enables 
    /// the creation of ID2D1Device6 objects.
    /// </summary>
    class Factory7 : public Factory6
    {
    public:
        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( Factory7, Factory6, ID2D1Factory7, ID2D1Factory6 )

        Factory7( D2D1_FACTORY_TYPE factoryType )
        {
            ID2D1Factory7* d2d1Factory7 = nullptr;
            auto hr = D2D1CreateFactory( factoryType, __uuidof( ID2D1Factory7 ), (void**)&d2d1Factory7 );
            HCC_COM_CHECK_HRESULT( hr );
            unknown_ = d2d1Factory7;
        }

        static Factory7 Create( D2D1_FACTORY_TYPE factoryType = D2D1_FACTORY_TYPE::D2D1_FACTORY_TYPE_SINGLE_THREADED )
        {
            return Factory7( factoryType );
        }


        /// <summary>
        /// This creates a new Direct2D device from the given IDXGIDevice.
        /// </summary>
        /// <param name="dxgiDevice">
        /// The IDXGIDevice from which to create the Direct2D device.
        /// </param>
        /// <param name="d2dDevice6">
        /// The created device.
        /// </param>
        void CreateDevice( _In_ IDXGIDevice* dxgiDevice, ID2D1Device6** d2dDevice6 ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateDevice( dxgiDevice, d2dDevice6 );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void CreateDevice( const DXGI::Device& dxgiDevice, ID2D1Device6** d2dDevice6 ) const
        {
            CreateDevice( dxgiDevice.GetInterfacePointer<IDXGIDevice>( ), d2dDevice6 );
        }
        Device6 CreateDevice( _In_ IDXGIDevice* dxgiDevice ) const
        {
            ID2D1Device6* ptr = nullptr;
            CreateDevice( dxgiDevice, &ptr );
            return Device6( ptr );
        }
        Device6 CreateDevice( const DXGI::Device& dxgiDevice ) const
        {
            return CreateDevice( dxgiDevice.GetInterfacePointer<IDXGIDevice>( ) );
        }

        Device6 CreateDevice6( _In_ IDXGIDevice* dxgiDevice ) const
        {
            return CreateDevice( dxgiDevice );
        }
        Device6 CreateDevice6( const DXGI::Device& dxgiDevice ) const
        {
            return CreateDevice( dxgiDevice );
        }

    };







    [[nodiscard]] inline Device CreateDevice( IDXGIDevice* dxgiDevice, const D2D1_CREATION_PROPERTIES* creationProperties )
    {
        ID2D1Device* d2dDevice = nullptr;
        auto hr = D2D1CreateDevice( dxgiDevice, creationProperties, &d2dDevice );
        HCC_COM_CHECK_HRESULT( hr );
        Device result( d2dDevice );
        return result;
    }

    [[nodiscard]] inline DeviceContext CreateDeviceContext( IDXGISurface* dxgiSurface, const D2D1_CREATION_PROPERTIES* creationProperties )
    {
        ID2D1DeviceContext* d2dDeviceContext = nullptr;
        auto hr = D2D1CreateDeviceContext( dxgiSurface, creationProperties, &d2dDeviceContext );
        HCC_COM_CHECK_HRESULT( hr );
        DeviceContext result( d2dDeviceContext );
        return result;
    }

    [[nodiscard]] inline D2D1_COLOR_F ConvertColorSpace( D2D1_COLOR_SPACE sourceColorSpace, D2D1_COLOR_SPACE destinationColorSpace, const D2D1_COLOR_F* color )
    {
        return D2D1ConvertColorSpace( sourceColorSpace, destinationColorSpace, color );
    }

    inline void SinCos( FLOAT angle, FLOAT* s, FLOAT* c )
    {
        D2D1SinCos( angle, s, c );
    }

    [[nodiscard]] inline FLOAT Tan( FLOAT angle )
    {
        return D2D1Tan( angle );
    }

    [[nodiscard]] inline FLOAT Length( FLOAT x, FLOAT y, FLOAT z )
    {
        return D2D1Vec3Length( x, y, z );
    }

    
}

#endif
