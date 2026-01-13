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

#include <skia/sg/SkSGCircle.h>

#include "skia/core/SkCanvas.h"
#include "skia/core/SkPaint.h"
#include "skia/core/SkPath.h"


namespace sksg
{
    Circle::Circle( const SkRect& rect ) : fRect( rect ) {}

    void Circle::onClip( SkCanvas* canvas, bool antiAlias ) const
    {
        canvas->clipRect( fRect, SkClipOp::kIntersect, antiAlias );
    }

    void Circle::onDraw( SkCanvas* canvas, const SkPaint& paint ) const
    {
        SkPoint center( fRect.centerX(), fRect.centerY( ) );
        SkScalar radius = std::min( fRect.width( ), fRect.height() )/2;
        canvas->drawCircle( center, radius, paint );
    }

    bool Circle::onContains( const SkPoint& p ) const
    {
        return fRect.contains( p.x( ), p.y( ) );
    }

    SkRect Circle::onRevalidate( InvalidationController*, const SkMatrix& )
    {
        SkASSERT( this->hasInval( ) );

        return fRect;
    }

    SkPath Circle::onAsPath( ) const
    {
        SkPoint center( fRect.centerX( ), fRect.centerY( ) );
        SkScalar radius = std::min( fRect.width( ), fRect.height( ) ) / 2;
        return SkPath::Circle( fRect.centerX( ), fRect.centerY( ), radius, this->getDirection( ) );
    }

}