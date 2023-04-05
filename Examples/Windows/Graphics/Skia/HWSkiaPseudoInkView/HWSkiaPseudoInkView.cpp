#include <HWSkiaSamplePatch.h>


using namespace Harlinn::Windows::Skia;

class PseudoInkView : public Sample
{
    enum { N = 100 };
    SkPath            fPath;
    sk_sp<SkVertices> fVertices[N];
    SkPaint           fSkeletonP, fStrokeP, fVertsP;
    bool              fDirty = true;

public:
    PseudoInkView( )
    {
        fSkeletonP.setStyle( SkPaint::kStroke_Style );
        fSkeletonP.setAntiAlias( true );

        fStrokeP.setStyle( SkPaint::kStroke_Style );
        fStrokeP.setStrokeWidth( 30 );
        fStrokeP.setColor( 0x44888888 );
    }

protected:
    SkString name( ) override { return SkString( "PseudoInk" ); }

    bool onAnimate( double nanos ) override { return true; }

    void onDrawContent( SkCanvas* canvas ) override
    {
        if ( fDirty )
        {
            for ( int i = 0; i < N; ++i )
            {
                fVertices[i] = make_verts( fPath, 30 );
            }
            fDirty = false;
        }
        for ( int i = 0; i < N; ++i )
        {
            canvas->drawVertices( fVertices[i], SkBlendMode::kSrc, fVertsP );
            canvas->translate( 1, 1 );
        }
        //        canvas->drawPath(fPath, fStrokeP);
         //       canvas->drawPath(fPath, fSkeletonP);
    }

    Click* onFindClickHandler( SkScalar x, SkScalar y, skui::ModifierKey modi ) override
    {
        Click* click = new Click( );
        fPath.reset( );
        fPath.moveTo( x, y );
        return click;
    }

    bool onClick( Click* click ) override
    {
        switch ( click->fState )
        {
            case skui::InputState::kMove:
                fPath.lineTo( click->fCurr );
                fDirty = true;
                break;
            default:
                break;
        }
        return true;
    }

private:
    using INHERITED = Sample;
};

int main()
{
    int result = SampleApplication<PseudoInkView>::Run( );
    return result;
}

