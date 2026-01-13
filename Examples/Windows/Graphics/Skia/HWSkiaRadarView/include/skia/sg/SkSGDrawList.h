#pragma once

#ifndef SkSGDrawList_DEFINED
#define SkSGDrawList_DEFINED
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


#include "skia/sg/SkSGGeometryNode.h"
#include "skia/sg/SkSGPaint.h"
#include "skia/sg/SkSGRenderNode.h"

#ifndef SK_API_EXT
#define SK_API_EXT
#endif

namespace sksg
{

    class DrawList : public RenderNode
    {
    public:
        using Base = RenderNode;
    private:
        std::vector<sk_sp<GeometryNode>> geometries_;
        sk_sp<PaintNode> paint_;
        bool requiresIsolation_ = false;
    protected:
        SK_API_EXT DrawList( std::vector<sk_sp<GeometryNode>>&& geometries, sk_sp<PaintNode> paint );
        SK_API_EXT DrawList( sk_sp<PaintNode> paint );
        SK_API_EXT ~DrawList( ) override;
    public:
        static sk_sp<DrawList> Make( std::vector<sk_sp<GeometryNode>>&& geometries, sk_sp<PaintNode> paint )
        {
            return ( geometries.size() && paint ) ? sk_sp<DrawList>( new DrawList( std::move( geometries ), std::move( paint ) ) ) : nullptr;
        }
        static sk_sp<DrawList> Make( sk_sp<PaintNode> paint )
        {
            return ( paint ) ? sk_sp<DrawList>( new DrawList( std::move( paint ) ) ) : nullptr;
        }

        SK_API_EXT void clear( );
        SK_API_EXT void addChild( sk_sp<GeometryNode> node );
        SK_API_EXT void removeChild( const sk_sp<GeometryNode>& node );
        size_t size( ) const { return geometries_.size( ); }
        bool  empty( ) const { return geometries_.empty( ); }
    protected:
        SK_API_EXT void onRender( SkCanvas*, const RenderContext* ) const override;
        SK_API_EXT const RenderNode* onNodeAt( const SkPoint& ) const override;

        SK_API_EXT SkRect onRevalidate( InvalidationController*, const SkMatrix& ) override;
    };

} // namespace sksg

#endif // SkSGDraw_DEFINED

