/*
   Copyright 2024-2026 Espen Harlinn

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include <HWSkiaSamplePatch.h>

using namespace Harlinn::Windows::Skia;

// Show stroking options using patheffects (and pathops)
// and why strokeandfill is a hacks
class ManyStrokesView : public Sample
{
    SkPath              fPath;
    sk_sp<SkPathEffect> fPE[6];

public:
    ManyStrokesView( )
    {
        fPE[0] = SkStrokePathEffect::Make( 20, SkPaint::kRound_Join, SkPaint::kRound_Cap );

        auto p0 = SkStrokePathEffect::Make( 25, SkPaint::kRound_Join, SkPaint::kRound_Cap );
        auto p1 = SkStrokePathEffect::Make( 20, SkPaint::kRound_Join, SkPaint::kRound_Cap );
        fPE[1] = SkMergePathEffect::Make( p0, p1, SkPathOp::kDifference_SkPathOp );

        fPE[2] = SkMergePathEffect::Make( nullptr, p1, SkPathOp::kDifference_SkPathOp );
        fPE[3] = SkMergePathEffect::Make( nullptr, p1, SkPathOp::kUnion_SkPathOp );
        fPE[4] = SkMergePathEffect::Make( p0, nullptr, SkPathOp::kDifference_SkPathOp );
        fPE[5] = SkMergePathEffect::Make( p0, nullptr, SkPathOp::kIntersect_SkPathOp );
    }

protected:
    SkString name( ) override { return SkString( "ManyStrokes" ); }

    bool onAnimate( double nanos ) override { return true; }

    void dodraw( SkCanvas* canvas, sk_sp<SkPathEffect> pe, SkScalar x, SkScalar y,
        const SkPaint* ptr = nullptr )
    {
        SkPaint paint;
        paint.setAntiAlias( true );
        paint.setPathEffect( pe );
        canvas->save( );
        canvas->translate( x, y );
        canvas->drawPath( fPath, ptr ? *ptr : paint );

        paint.setPathEffect( nullptr );
        paint.setStyle( SkPaint::kStroke_Style );
        paint.setColor( SK_ColorGREEN );
        canvas->drawPath( fPath, paint );

        canvas->restore( );
    }

    void onDrawContent( SkCanvas* canvas ) override
    {
        SkPaint p;
        p.setColor( 0 );
        this->dodraw( canvas, nullptr, 0, 0, &p );

        this->dodraw( canvas, fPE[0], 300, 0 );
        this->dodraw( canvas, fPE[1], 0, 300 );
        this->dodraw( canvas, fPE[2], 300, 300 );
        this->dodraw( canvas, fPE[3], 600, 300 );
        this->dodraw( canvas, fPE[4], 900, 0 );
        this->dodraw( canvas, fPE[5], 900, 300 );

        p.setColor( SK_ColorBLACK );
        p.setStyle( SkPaint::kStrokeAndFill_Style );
        p.setStrokeJoin( SkPaint::kRound_Join );
        p.setStrokeCap( SkPaint::kRound_Cap );
        p.setStrokeWidth( 20 );
        this->dodraw( canvas, nullptr, 600, 0, &p );
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
    int result = SampleApplication<ManyStrokesView>::Run( );
    return result;
}

