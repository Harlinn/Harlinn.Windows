#include <HWSkia.h>
#include <HWForm.h>
#include "skia/core/SkCanvas.h"
#include "skia/core/SkColorPriv.h"
#include "skia/core/SkFont.h"
#include "skia/core/SkPaint.h"
#include "skia/core/SkPathBuilder.h"
#include "skia/utils/SkRandom.h"
#include "src/core/SkPathPriv.h"
#include "skia/tools/Resources.h"

using namespace Harlinn::Windows;

static constexpr int W = 150;
static constexpr int H = 200;

static void show_text( SkCanvas* canvas, bool doAA )
{
    SkRandom rand;
    SkPaint paint;
    SkFont font( nullptr, 20 );
    font.setEdging( doAA ? SkFont::Edging::kSubpixelAntiAlias : SkFont::Edging::kAlias );

    for ( int i = 0; i < 200; ++i )
    {
        paint.setColor( ( SK_A32_MASK << SK_A32_SHIFT ) | rand.nextU( ) );
        canvas->drawString( "Hamburgefons", rand.nextSScalar1( ) * W, rand.nextSScalar1( ) * H + 20,
            font, paint );
    }
}

static void show_fill( SkCanvas* canvas, bool doAA )
{
    SkRandom rand;
    SkPaint paint;
    paint.setAntiAlias( doAA );

    for ( int i = 0; i < 50; ++i )
    {
        SkRect r;

        r.setXYWH( rand.nextSScalar1( ) * W, rand.nextSScalar1( ) * H,
            rand.nextUScalar1( ) * W, rand.nextUScalar1( ) * H );
        paint.setColor( rand.nextU( ) );
        canvas->drawRect( r, paint );

        r.setXYWH( rand.nextSScalar1( ) * W, rand.nextSScalar1( ) * H,
            rand.nextUScalar1( ) * W, rand.nextUScalar1( ) * H );
        paint.setColor( rand.nextU( ) );
        canvas->drawOval( r, paint );
    }
}

static SkScalar randRange( SkRandom& rand, SkScalar min, SkScalar max )
{
    SkASSERT( min <= max );
    return min + rand.nextUScalar1( ) * ( max - min );
}

static void show_stroke( SkCanvas* canvas, bool doAA, SkScalar strokeWidth, int n )
{
    SkRandom rand;
    SkPaint paint;
    paint.setAntiAlias( doAA );
    paint.setStyle( SkPaint::kStroke_Style );
    paint.setStrokeWidth( strokeWidth );

    for ( int i = 0; i < n; ++i )
    {
        SkRect r;

        r.setXYWH( rand.nextSScalar1( ) * W, rand.nextSScalar1( ) * H,
            rand.nextUScalar1( ) * W, rand.nextUScalar1( ) * H );
        paint.setColor( rand.nextU( ) );
        canvas->drawRect( r, paint );

        r.setXYWH( rand.nextSScalar1( ) * W, rand.nextSScalar1( ) * H,
            rand.nextUScalar1( ) * W, rand.nextUScalar1( ) * H );
        paint.setColor( rand.nextU( ) );
        canvas->drawOval( r, paint );

        const SkScalar minx = -SkIntToScalar( W ) / 4;
        const SkScalar maxx = 5 * SkIntToScalar( W ) / 4;
        const SkScalar miny = -SkIntToScalar( H ) / 4;
        const SkScalar maxy = 5 * SkIntToScalar( H ) / 4;
        paint.setColor( rand.nextU( ) );
        canvas->drawLine( randRange( rand, minx, maxx ), randRange( rand, miny, maxy ),
            randRange( rand, minx, maxx ), randRange( rand, miny, maxy ),
            paint );
    }
}

static void show_hair( SkCanvas* canvas, bool doAA )
{
    show_stroke( canvas, doAA, 0, 150 );
}

static void show_thick( SkCanvas* canvas, bool doAA )
{
    show_stroke( canvas, doAA, SkIntToScalar( 5 ), 50 );
}

typedef void ( *CanvasProc )( SkCanvas*, bool );


class SkiaClipViewForm : public Form
{
public:
    using Base = Form;
private:
    std::unique_ptr<SkiaControl> control_;
public:
    SkiaClipViewForm( )
        : Base( )
    {
        SetText( L"Clip View" );

        control_ = make_control<SkiaControl>( this );
        control_->OnRender.connect( [this]( Control* control, SkCanvas* canvas )
        {
            //canvas->clear( SK_ColorWHITE );
            canvas->drawColor( SK_ColorWHITE );
            canvas->translate( SkIntToScalar( 20 ), SkIntToScalar( 20 ) );

            static const CanvasProc gProc[] = {
                show_text, show_thick, show_hair, show_fill
            };

            SkRect r = { 0, 0, SkIntToScalar( W ), SkIntToScalar( H ) };
            r.inset( SK_Scalar1 / 4, SK_Scalar1 / 4 );
            SkPath clipPath = SkPathBuilder( ).addRRect( SkRRect::MakeRectXY( r, 20, 20 ) ).detach( );

            //        clipPath.toggleInverseFillType();

            for ( int aa = 0; aa <= 1; ++aa )
            {
                canvas->save( );
                for ( size_t i = 0; i < SK_ARRAY_COUNT( gProc ); ++i )
                {
                    canvas->save( );
                    canvas->clipPath( clipPath, SkClipOp::kIntersect, SkToBool( aa ) );
                    gProc[i]( canvas, SkToBool( aa ) );
                    canvas->restore( );
                    canvas->translate( W * SK_Scalar1 * 8 / 7, 0 );
                }
                canvas->restore( );
                canvas->translate( 0, H * SK_Scalar1 * 8 / 7 );
            }
        } );
    }

protected:
    void DoOnSize( Message& message ) override
    {
        if ( control_ )
        {
            Harlinn::Windows::Rectangle clientRect = GetClientRect( );
            control_->MoveWindow( 0, 0, clientRect.Width( ), clientRect.Height( ) );
        }
    }
};




int main( )
{
    try
    {
        SetThreadDpiAwarenessContext( DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2 );

        Harlinn::Windows::Application application;
        application.Start( );

        SkGraphics::Init( );

        SkiaClipViewForm form;
        form.Initialize( );

        auto result = application.Run( form );

        application.Stop( );

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
