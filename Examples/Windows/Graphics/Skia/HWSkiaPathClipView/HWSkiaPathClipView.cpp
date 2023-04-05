#include <HWSkiaSample.h>
#include "skia/core/SkCanvas.h"
#include "skia/core/SkColorFilter.h"
#include "skia/core/SkColorPriv.h"
#include "skia/core/SkGraphics.h"
#include "skia/core/SkPath.h"
#include "skia/core/SkRegion.h"
#include "skia/core/SkShader.h"
#include "skia/core/SkTime.h"
#include "skia/core/SkTypeface.h"
#include "skia/effects/SkGradientShader.h"
#include "skia/private/SkTo.h"
#include "src/utils/SkUTF.h"

#include <utility>

using namespace Harlinn::Windows::Skia;

class PathClipView : public Sample
{
public:
    SkRect fOval;
    SkPoint fCenter;

    PathClipView( ) : fOval( SkRect::MakeWH( 200, 50 ) ), fCenter( SkPoint::Make( 250, 250 ) ) {}

protected:
    SkString name( ) override { return SkString( "PathClip" ); }

    void onDrawContent( SkCanvas* canvas ) override
    {
        const SkRect oval = fOval.makeOffset( fCenter.fX - fOval.centerX( ),
            fCenter.fY - fOval.centerY( ) );

        SkPaint p;
        p.setAntiAlias( true );

        p.setStyle( SkPaint::kStroke_Style );
        canvas->drawOval( oval, p );

        const SkRect r = SkRect::MakeLTRB( 200, 200, 300, 300 );
        canvas->clipRect( r );

        p.setStyle( SkPaint::kFill_Style );
        p.setColor( SK_ColorRED );
        canvas->drawRect( r, p );

        p.setColor( 0x800000FF );
        canvas->drawOval( oval, p );
    }

    Sample::Click* onFindClickHandler( SkScalar x, SkScalar y, skui::ModifierKey ) override
    {
        return new Click( [&]( Click* c ) {
            fCenter = c->fCurr;
            return false;
        } );
    }

private:
    using INHERITED = Sample;
};


int main()
{
    int result = SampleApplication<PathClipView>::Run( );
    return result;
}

