#include <HWSkiaSampleLayers.h>
#include "skia/effects/SkImageFilters.h"
#include "skia/tools/Resources.h"

using namespace Harlinn::Windows::Skia;

class BackdropView : public Sample
{
    SkPoint fCenter;
    SkScalar fAngle;
    sk_sp<SkImage> fImage;
    sk_sp<SkImageFilter> fFilter;
public:
    BackdropView( )
    {
        fCenter.set( 200, 150 );
        fAngle = 0;
        fImage = GetResourceAsImage( "images/mandrill_512.png" );
        fFilter = SkImageFilters::Dilate( 8, 8, nullptr );
    }

protected:
    SkString name( ) override { return SkString( "Backdrop" ); }

    void onDrawContent( SkCanvas* canvas ) override
    {
        canvas->drawImage( fImage.get( ), 0, 0 );

        const SkScalar w = 250;
        const SkScalar h = 150;
        SkPath path;
        path.addOval( SkRect::MakeXYWH( -w / 2, -h / 2, w, h ) );
        SkMatrix m;
        m.setRotate( fAngle );
        m.postTranslate( fCenter.x( ), fCenter.y( ) );
        path.transform( m );

        canvas->clipPath( path, SkClipOp::kIntersect, true );
        const SkRect bounds = path.getBounds( );

        SkPaint paint;
        paint.setAlpha( 0xCC );
        canvas->saveLayer( SkCanvas::SaveLayerRec( &bounds, &paint, fFilter.get( ), 0 ) );

        canvas->restore( );
    }

    bool onAnimate( double nanos ) override
    {
        fAngle = SkDoubleToScalar( fmod( 1e-9 * nanos * 360 / 5, 360 ) );
        return true;
    }

    Sample::Click* onFindClickHandler( SkScalar x, SkScalar y, skui::ModifierKey modi ) override
    {
        return new Click( );
    }

    bool onClick( Click* click ) override
    {
        fCenter = click->fCurr;
        return true;
    }

private:
    using INHERITED = Sample;
};

int main()
{
    int result = SampleApplication<BackdropView>::Run( );
    return result;
}

