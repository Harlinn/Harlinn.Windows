#include <HWSkiaSamplePath.h>

using namespace Harlinn::Windows::Skia;


// http://code.google.com/p/skia/issues/detail?id=32
static void test_cubic( )
{
    SkPoint src[4] = {
        { 556.25000f, 523.03003f },
        { 556.23999f, 522.96002f },
        { 556.21997f, 522.89001f },
        { 556.21997f, 522.82001f }
    };
    SkPoint dst[11];
    dst[10].set( 42, -42 );   // one past the end, that we don't clobber these
    SkScalar tval[] = { 0.33333334f, 0.99999994f };

    SkChopCubicAt( src, dst, tval, 2 );

#if 0
    for ( int i = 0; i < 11; i++ )
    {
        SkDebugf( "--- %d [%g %g]\n", i, dst[i].fX, dst[i].fY );
    }
#endif
}

static void test_cubic2( )
{
    const char* str = "M2242 -590088L-377758 9.94099e+07L-377758 9.94099e+07L2242 -590088Z";
    SkPath path;
    SkParsePath::FromSVGString( str, &path );

    {
        SkRect r = path.getBounds( );
        SkIRect ir;
        r.round( &ir );
        SkDebugf( "[%g %g %g %g] [%x %x %x %x]\n",
            SkScalarToDouble( r.fLeft ), SkScalarToDouble( r.fTop ),
            SkScalarToDouble( r.fRight ), SkScalarToDouble( r.fBottom ),
            ir.fLeft, ir.fTop, ir.fRight, ir.fBottom );
    }

    SkBitmap bitmap;
    bitmap.allocN32Pixels( 300, 200 );

    SkCanvas canvas( bitmap );
    SkPaint paint;
    paint.setAntiAlias( true );
    canvas.drawPath( path, paint );
}

class PathView : public Sample
{
    SkScalar fPrevSecs;
public:
    SkScalar fDStroke, fStroke, fMinStroke, fMaxStroke;
    SkPath fPath[6];
    bool fShowHairline;
    bool fOnce;

    PathView( )
    {
        fPrevSecs = 0;
        fOnce = false;
    }

    void init( )
    {
        if ( fOnce )
        {
            return;
        }
        fOnce = true;

        test_cubic( );
        test_cubic2( );

        fShowHairline = false;

        fDStroke = 1;
        fStroke = 10;
        fMinStroke = 10;
        fMaxStroke = 180;

        const SkScalar V = 85;

        fPath[0].moveTo( 40, 70 );
        fPath[0].lineTo( 70, 70 + SK_ScalarHalf );
        fPath[0].lineTo( 110, 70 );

        fPath[1].moveTo( 40, 70 );
        fPath[1].lineTo( 70, 70 - SK_ScalarHalf );
        fPath[1].lineTo( 110, 70 );

        fPath[2].moveTo( V, V );
        fPath[2].lineTo( 50, V );
        fPath[2].lineTo( 50, 50 );

        fPath[3].moveTo( 50, 50 );
        fPath[3].lineTo( 50, V );
        fPath[3].lineTo( V, V );

        fPath[4].moveTo( 50, 50 );
        fPath[4].lineTo( 50, V );
        fPath[4].lineTo( 52, 50 );

        fPath[5].moveTo( 52, 50 );
        fPath[5].lineTo( 50, V );
        fPath[5].lineTo( 50, 50 );

        this->setBGColor( 0xFFDDDDDD );
    }

protected:
    SkString name( ) override { return SkString( "Paths" ); }

    void drawPath( SkCanvas* canvas, const SkPath& path, SkPaint::Join j )
    {
        SkPaint paint;

        paint.setAntiAlias( true );
        paint.setStyle( SkPaint::kStroke_Style );
        paint.setStrokeJoin( j );
        paint.setStrokeWidth( fStroke );

        if ( fShowHairline )
        {
            SkPath  fill;

            paint.getFillPath( path, &fill );
            paint.setStrokeWidth( 0 );
            canvas->drawPath( fill, paint );
        }
        else
        {
            canvas->drawPath( path, paint );
        }

        paint.setColor( SK_ColorRED );
        paint.setStrokeWidth( 0 );
        canvas->drawPath( path, paint );
    }

    void onDrawContent( SkCanvas* canvas ) override
    {
        this->init( );
        canvas->translate( 50, 50 );

        static const SkPaint::Join gJoins[] = {
            SkPaint::kBevel_Join,
            SkPaint::kMiter_Join,
            SkPaint::kRound_Join
        };

        for ( size_t i = 0; i < SK_ARRAY_COUNT( gJoins ); i++ )
        {
            canvas->save( );
            for ( size_t j = 0; j < SK_ARRAY_COUNT( fPath ); j++ )
            {
                this->drawPath( canvas, fPath[j], gJoins[i] );
                canvas->translate( 200, 0 );
            }
            canvas->restore( );

            canvas->translate( 0, 200 );
        }
    }

    bool onAnimate( double nanos ) override
    {
        SkScalar currSecs = TimeUtils::Scaled( 1e-9 * nanos, 100 );
        SkScalar delta = currSecs - fPrevSecs;
        fPrevSecs = currSecs;

        fStroke += fDStroke * delta;
        if ( fStroke > fMaxStroke || fStroke < fMinStroke )
        {
            fDStroke = -fDStroke;
        }
        return true;
    }

    Sample::Click* onFindClickHandler( SkScalar x, SkScalar y, skui::ModifierKey modi ) override
    {
        fShowHairline = !fShowHairline;
        return nullptr;
    }

private:
    using INHERITED = Sample;
};

int main()
{
    int result = SampleApplication<PathView>::Run( );
    return result;
}

