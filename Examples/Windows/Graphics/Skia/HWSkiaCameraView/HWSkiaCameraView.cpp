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


#include <HWSkiaSample.h>

#include "skia/core/SkImage.h"
#include "skia/core/SkShader.h"
#include "skia/core/SkString.h"
#include "skia/utils/SkCamera.h"
#include "DecodeFile.h"
#include "src/effects/SkEmbossMaskFilter.h"
#include "skia/tools/Resources.h"
#include "skia/tools/timer/TimeUtils.h"

class CameraView : public Harlinn::Windows::Skia::Sample
{
    SkTArray<sk_sp<SkShader>> fShaders;
    int fShaderIndex = 0;
    bool fFrontFace = false;
    SkScalar fRX = 0;
    SkScalar fRY = 0;

    SkString name( ) override { return SkString( "Camera" ); }

    void onOnceBeforeDraw( ) override
    {
        for ( const char* resource : {
            "images/mandrill_512_q075.jpg",
            "images/dog.jpg",
            "images/gamut.png",
            } )
        {
            SkBitmap bm;
            if ( GetResourceAsBitmap( resource, &bm ) )
            {
                SkRect src = { 0, 0, SkIntToScalar( bm.width( ) ), SkIntToScalar( bm.height( ) ) };
                SkRect dst = { -150, -150, 150, 150 };
                fShaders.push_back( bm.makeShader( SkSamplingOptions( SkFilterMode::kLinear ),
                    SkMatrix::RectToRect( src, dst ) ) );
            }
        }
        this->setBGColor( 0xFFDDDDDD );
    }

    void onDrawContent( SkCanvas* canvas ) override
    {
        if ( fShaders.count( ) > 0 )
        {
            canvas->translate( this->width( ) / 2, this->height( ) / 2 );

            Sk3DView    view;
            view.rotateX( fRX );
            view.rotateY( fRY );
            view.applyToCanvas( canvas );

            bool frontFace = view.dotWithNormal( 0, 0, SK_Scalar1 ) < 0;
            if ( frontFace != fFrontFace )
            {
                fFrontFace = frontFace;
                fShaderIndex = ( fShaderIndex + 1 ) % fShaders.count( );
            }

            SkPaint paint;
            paint.setAntiAlias( true );
            paint.setShader( fShaders[fShaderIndex] );
            SkRect r = { -150, -150, 150, 150 };
            canvas->drawRoundRect( r, 30, 30, paint );
        }
    }

    bool onAnimate( double nanos ) override
    {
        fRY = nanos ? TimeUtils::Scaled( 1e-9 * nanos, 90, 360 ) : 0;
        return true;
    }
};

int main()
{
    using namespace Harlinn::Windows::Skia;
    int result = SampleApplication<CameraView>::Run( );
    return result;
}

