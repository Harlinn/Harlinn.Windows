#pragma once

#ifndef SkSGCircle_DEFINED
#define SkSGCircle_DEFINED

#include "skia/sg/SkSGGeometryNode.h"

#include "skia/core/SkPath.h"
#include "skia/core/SkRect.h"

class SkCanvas;
class SkPaint;

#ifndef SK_API_EXT
#define SK_API_EXT
#endif


namespace sksg
{
    class Circle final : public GeometryNode
    {
    public:
        static sk_sp<Circle> Make( ) { return sk_sp<Circle>( new Circle( SkRect::MakeEmpty( ) ) ); }
        static sk_sp<Circle> Make( const SkRect& r ) { return sk_sp<Circle>( new Circle( r ) ); }

        SG_ATTRIBUTE( L, SkScalar, fRect.fLeft )
        SG_ATTRIBUTE( T, SkScalar, fRect.fTop )
        SG_ATTRIBUTE( R, SkScalar, fRect.fRight )
        SG_ATTRIBUTE( B, SkScalar, fRect.fBottom )

        SG_MAPPED_ATTRIBUTE( Direction, SkPathDirection, fAttrContaier )
        SG_MAPPED_ATTRIBUTE( InitialPointIndex, uint8_t, fAttrContaier )

    protected:
        SK_API_EXT void onClip( SkCanvas*, bool antiAlias ) const override;
        SK_API_EXT void onDraw( SkCanvas*, const SkPaint& paint ) const override;
        SK_API_EXT bool onContains( const SkPoint& point ) const override;

        SK_API_EXT SkRect onRevalidate( InvalidationController*, const SkMatrix& ) override;
        SK_API_EXT SkPath onAsPath( ) const override;

    private:
        SK_API_EXT explicit Circle( const SkRect& );

        SkRect   fRect;

        struct AttrContainer
        {
            uint8_t fDirection : 1;
            uint8_t fInitialPointIndex : 2;

            SkPathDirection getDirection( ) const
            {
                return static_cast<SkPathDirection>( fDirection );
            }
            void setDirection( SkPathDirection dir ) { fDirection = SkTo<uint8_t>( dir ); }

            uint8_t getInitialPointIndex( ) const { return fInitialPointIndex; }
            void setInitialPointIndex( uint8_t idx ) { fInitialPointIndex = idx; }
        };
        AttrContainer fAttrContaier = { (int)SkPathDirection::kCW, 0 };

        using INHERITED = GeometryNode;
    };


}



#endif