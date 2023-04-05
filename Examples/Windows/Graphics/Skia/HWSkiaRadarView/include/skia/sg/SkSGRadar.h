#pragma once

#ifndef SkSGRadar_DEFINED
#define SkSGRadar_DEFINED

#include "skia/sg/SkSGRenderNode.h"
#include "skia/sg/SkSGCircle.h"
#include "skia/sg/SkSGGroup.h"

namespace sksg
{

    class Radar : public Group
    {
    public:
        using Base = Group;
        SkRect rect_;
    protected:
        Radar( std::vector<sk_sp<RenderNode>> children, const SkRect& rect )
            : Base( std::move( children ) ), rect_( rect )
        {
            CreateGeometries( );
        }
    public:
        static sk_sp<Radar> Make( std::vector<sk_sp<RenderNode>> children, const SkRect& rect )
        {
            return sk_sp<Radar>( new Radar( std::move( children ), rect ) );
        }

        SkPoint center( ) const
        {
            return SkPoint( rect_.centerX( ), rect_.centerY( ) );
        }
        SkScalar centerX( ) const
        {
            return rect_.centerX( );
        }
        SkScalar centerY( ) const
        {
            return rect_.centerY( );
        }

        SkScalar radius( ) const
        {
            return std::min( rect_.width( ), rect_.height( ) ) / static_cast<SkScalar>(2.0);
        }

        SG_ATTRIBUTE( L, SkScalar, rect_.fLeft )
        SG_ATTRIBUTE( T, SkScalar, rect_.fTop )
        SG_ATTRIBUTE( R, SkScalar, rect_.fRight )
        SG_ATTRIBUTE( B, SkScalar, rect_.fBottom )

    private:
        SK_API_EXT void CreateGeometries( );
        
    };
}


#endif
