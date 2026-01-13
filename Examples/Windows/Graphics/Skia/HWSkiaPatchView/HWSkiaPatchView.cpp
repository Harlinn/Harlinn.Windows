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

struct PatchView : public Sample
{
    sk_sp<SkShader> fShader0;
    sk_sp<SkShader> fShader1;
    SkScalar fAngle = 0;
    SkIPoint fSize0 = { 0, 0 },
        fSize1 = { 0, 0 };
    SkPoint  fPts[12] = {
        {kS * 0, kT * 1},
        {kS * 1, kT * 1},
        {kS * 2, kT * 1},
        {kS * 3, kT * 1},
        {kS * 3, kT * 2},
        {kS * 3, kT * 3},
        {kS * 3, kT * 4},
        {kS * 2, kT * 4},
        {kS * 1, kT * 4},
        {kS * 0, kT * 4},
        {kS * 0, kT * 3},
        {kS * 0, kT * 2},
    };

    void onOnceBeforeDraw( ) override
    {
        fShader0 = make_shader0( &fSize0 );
        fSize1 = fSize0;
        if ( fSize0.fX == 0 || fSize0.fY == 0 )
        {
            fSize1.set( 2, 2 );
        }
        fShader1 = make_shader1( fSize1 );
        this->setBGColor( SK_ColorGRAY );
    }

    SkString name( ) override { return SkString( "Patch" ); }

    void onDrawContent( SkCanvas* canvas ) override
    {
        const int nu = 10;
        const int nv = 10;

        SkPaint paint;
        paint.setDither( true );

        canvas->translate( DX, DY );

        Patch   patch;

        paint.setShader( fShader0 );
        if ( fSize0.fX == 0 )
        {
            fSize0.fX = 1;
        }
        if ( fSize0.fY == 0 )
        {
            fSize0.fY = 1;
        }
        patch.setBounds( fSize0.fX, fSize0.fY );

        patch.setPatch( fPts );
        drawpatches( canvas, paint, nu, nv, &patch );

        paint.setShader( nullptr );
        paint.setAntiAlias( true );
        paint.setStrokeWidth( SkIntToScalar( 5 ) );
        canvas->drawPoints( SkCanvas::kPoints_PointMode, SK_ARRAY_COUNT( fPts ), fPts, paint );

        canvas->translate( 0, SkIntToScalar( 300 ) );

        paint.setAntiAlias( false );
        paint.setShader( fShader1 );
        {
            SkMatrix m;
            m.setSkew( 1, 0 );
            paint.setShader( paint.getShader( )->makeWithLocalMatrix( m ) );
        }
        {
            SkMatrix m;
            m.setRotate( fAngle );
            paint.setShader( paint.getShader( )->makeWithLocalMatrix( m ) );
        }
        patch.setBounds( fSize1.fX, fSize1.fY );
        drawpatches( canvas, paint, nu, nv, &patch );
    }

    bool onAnimate( double nanos ) override
    {
        fAngle = TimeUtils::Scaled( 1e-9 * nanos, 60, 360 );
        return true;
    }

    class PtClick : public Click
    {
    public:
        int fIndex;
        PtClick( int index ) : fIndex( index ) {}
    };

    static bool hittest( const SkPoint& pt, SkScalar x, SkScalar y )
    {
        return SkPoint::Length( pt.fX - x, pt.fY - y ) < SkIntToScalar( 5 );
    }

    Sample::Click* onFindClickHandler( SkScalar x, SkScalar y, skui::ModifierKey modi ) override
    {
        x -= DX;
        y -= DY;
        for ( size_t i = 0; i < SK_ARRAY_COUNT( fPts ); i++ )
        {
            if ( hittest( fPts[i], x, y ) )
            {
                return new PtClick( (int)i );
            }
        }
        return nullptr;
    }

    bool onClick( Click* click ) override
    {
        fPts[( (PtClick*)click )->fIndex].set( click->fCurr.fX - DX, click->fCurr.fY - DY );
        return true;
    }

private:
    using INHERITED = Sample;
};

int main()
{
    int result = SampleApplication<PatchView>::Run( );
    return result;
}

