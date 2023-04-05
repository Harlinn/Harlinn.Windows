#include <HWSkiaSample3D.h>
#include "skia/skottie/Skottie.h"

class SampleSkottieCube : public SampleCubeBase
{
    sk_sp<skottie::Animation> fAnim[6];

public:
    SampleSkottieCube( ) : SampleCubeBase( kCanRunOnCPU ) {}

    SkString name( ) override { return SkString( "skottie3d" ); }

    void onOnceBeforeDraw( ) override
    {
        const char* files[] = {
            "skottie/skottie-chained-mattes.json",
            "skottie/skottie-gradient-ramp.json",
            "skottie/skottie_sample_2.json",
            "skottie/skottie-3d-3planes.json",
            "skottie/skottie-text-animator-4.json",
            "skottie/skottie-motiontile-effect-phase.json",

        };
        for ( unsigned i = 0; i < SK_ARRAY_COUNT( files ); ++i )
        {
            if ( auto stream = GetResourceAsStream( files[i] ) )
            {
                fAnim[i] = skottie::Animation::Make( stream.get( ) );
            }
        }
    }

    void drawContent(
        SkCanvas* canvas, SkColor color, int index, bool drawFront, const SkM44& ) override
    {
        if ( !drawFront || !front( canvas->getLocalToDevice( ) ) )
        {
            return;
        }

        SkPaint paint;
        paint.setColor( color );
        SkRect r = { 0, 0, 400, 400 };
        canvas->drawRect( r, paint );
        fAnim[index]->render( canvas, &r );
    }

    bool onAnimate( double nanos ) override
    {
        for ( auto& anim : fAnim )
        {
            SkScalar dur = anim->duration( );
            SkScalar t = fmod( 1e-9 * nanos, dur ) / dur;
            anim->seek( t );
        }
        return true;
    }
};


int main()
{
    using namespace Harlinn::Windows::Skia;
    int result = SampleApplication<SampleSkottieCube>::Run( );
    return result;
}
