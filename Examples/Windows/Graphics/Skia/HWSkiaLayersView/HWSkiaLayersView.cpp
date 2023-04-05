#include <HWSkiaSampleLayers.h>


using namespace Harlinn::Windows::Skia;

class LayersView : public Sample
{
public:
    LayersView( ) {}

protected:
    SkString name( ) override { return SkString( "Layers" ); }

    void drawBG( SkCanvas* canvas )
    {
        canvas->drawColor( SK_ColorGRAY );
    }

    void onDrawContent( SkCanvas* canvas ) override
    {
        this->drawBG( canvas );

        if ( true )
        {
            SkRect r;
            r.setWH( 220, 120 );
            SkPaint p;
            canvas->saveLayer( &r, &p );
            canvas->drawColor( 0xFFFF0000 );
            p.setAlpha( 0 );  // or 0
            p.setBlendMode( SkBlendMode::kSrc );
            canvas->drawOval( r, p );
            canvas->restore( );
            return;
        }

        if ( false )
        {
            SkRect r;
            r.setWH( 220, 120 );
            SkPaint p;
            p.setAlpha( 0x88 );
            p.setAntiAlias( true );

            if ( true )
            {
                canvas->saveLayer( &r, &p );
                p.setColor( 0xFFFF0000 );
                canvas->drawOval( r, p );
                canvas->restore( );
            }

            p.setColor( 0xFF0000FF );
            r.offset( SkIntToScalar( 20 ), SkIntToScalar( 50 ) );
            canvas->drawOval( r, p );
        }

        if ( false )
        {
            SkPaint p;
            p.setAlpha( 0x88 );
            p.setAntiAlias( true );

            canvas->translate( SkIntToScalar( 300 ), 0 );

            SkRect r;
            r.setWH( 220, 60 );

            canvas->saveLayer( &r, &p );

            r.setWH( 220, 120 );
            p.setColor( SK_ColorBLUE );
            canvas->drawOval( r, p );
            canvas->restore( );
            return;
        }

        test_fade( canvas );
    }

private:
    using INHERITED = Sample;
};

int main()
{
    int result = SampleApplication<LayersView>::Run( );
    return result;
}

