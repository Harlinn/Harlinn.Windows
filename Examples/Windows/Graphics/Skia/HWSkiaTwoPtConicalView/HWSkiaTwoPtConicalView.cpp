#include <HWSkiaSample.h>
#include "skia/effects/SkGradientShader.h"

using namespace Harlinn::Windows::Skia;

class TwoPtConicalView : public Sample
{
public:
    TwoPtConicalView( ) {}

protected:
    SkString name( ) override { return SkString( "2PtConical" ); }

    void onDrawContent( SkCanvas* canvas ) override
    {
        canvas->translate( SkIntToScalar( 10 ), SkIntToScalar( 20 ) );

        SkColor colors[] = { SK_ColorRED, SK_ColorBLUE };
        SkPoint c0 = { 0, 0 };
        SkScalar r0 = 100;
        SkPoint c1 = { 100, 100 };
        SkScalar r1 = 100;
        SkPaint paint;
        paint.setShader( SkGradientShader::MakeTwoPointConical( c0, r0, c1, r1, colors,
            nullptr, 2,
            SkTileMode::kClamp ) );
        canvas->drawPaint( paint );
    }

private:
    using INHERITED = Sample;
};

int main()
{
    int result = SampleApplication<TwoPtConicalView>::Run( );
    return result;
}

