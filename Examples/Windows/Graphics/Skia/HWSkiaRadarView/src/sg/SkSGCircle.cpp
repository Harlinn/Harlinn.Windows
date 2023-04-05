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