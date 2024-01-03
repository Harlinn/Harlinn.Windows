/*
   Copyright 2024 Espen Harlinn

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
#include "skia/effects/SkGradientShader.h"

using namespace Harlinn::Windows::Skia;

enum class Transform
{
    None,
    MoveBy200x200,
    ScaleBy2,
    Center,
    CenterRotate90
};


class TransformRect : public Sample
{
public:
    TransformRect( ) {}
    Transform transform_ = Transform::None;
protected:
    SkString name( ) override { return SkString( "Transform Rect" ); }

    void onDrawContent( SkCanvas* canvas ) override
    {
        auto rect = SkRect::MakeXYWH( 20,20, 50, 100 );
        SkPaint paint;
        paint.setAntiAlias( true );
        paint.setStyle( SkPaint::Style::kStroke_Style );
        paint.setStrokeWidth( 4 );

        switch ( transform_ )
        {
            case Transform::MoveBy200x200:
                canvas->translate( 200, 200 );
                break;
            case Transform::ScaleBy2:
                canvas->scale(2.0f,2.0f);
                break;
            case Transform::Center:
                canvas->translate( ((this->width() - rect.width())/2) - rect.left(),
                    (this->height() - rect.height() )/2 - rect.top( ) ) ;
                break;
            case Transform::CenterRotate90:
                canvas->translate( ( ( this->width( ) - rect.width( ) ) / 2 ) - rect.left( ),
                    ( this->height( ) - rect.height( ) ) / 2 - rect.top( ) );
                canvas->rotate( 90, rect.centerX(), rect.centerY() );
                break;
        }

        canvas->drawRect( rect, paint );

    }

    bool onChar( SkUnichar uni ) override
    {
        Transform originalTransform = transform_;
        switch ( uni )
        {
            case '1':
                transform_ = Transform::None;
                break;
            case '2':
                transform_ = Transform::MoveBy200x200;
                break;
            case '3':
                transform_ = Transform::ScaleBy2;
                break;
            case '4':
                transform_ = Transform::Center;
                break;
            case '5':
                transform_ = Transform::CenterRotate90;
                break;
        }

        return originalTransform != transform_;
    }

private:
    using INHERITED = Sample;
};

int main()
{
    int result = SampleApplication<TransformRect>::Run( );
    return result;
}

