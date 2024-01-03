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

#include <skia/sg/SkSGDrawList.h>
#include "skia/core/SkCanvas.h"
#include "skia/core/SkPath.h"

namespace sksg
{
    DrawList::DrawList( std::vector<sk_sp<GeometryNode>>&& geometries, sk_sp<PaintNode> paint )
        : geometries_( std::move( geometries ) ),
          paint_( std::move( paint ) )
    {
        for ( const auto& geometry : geometries_ )
        {
            this->observeInval( geometry );
        }
        this->observeInval( paint_ );
    }

    DrawList::DrawList( sk_sp<PaintNode> paint )
        : paint_( std::move( paint ) )
    {
        this->observeInval( paint_ );
    }

    DrawList::~DrawList( )
    {
        for ( const auto& geometry : geometries_ )
        {
            this->unobserveInval( geometry );
        }
        this->unobserveInval( paint_ );
    }

    void DrawList::clear( )
    {
        for ( const auto& geometry : geometries_ )
        {
            this->unobserveInval( geometry );
        }
        geometries_.clear( );
    }
    void DrawList::addChild( sk_sp<GeometryNode> node )
    {
        for ( const auto& geometry : geometries_ )
        {
            if ( geometry == node )
            {
                return;
            }
        }

        this->observeInval( node );
        geometries_.push_back( std::move( node ) );

        this->invalidate( );
    }
    void DrawList::removeChild( const sk_sp<GeometryNode>& node )
    {
        SkDEBUGCODE( const auto origSize = geometries_.size( ) );
        geometries_.erase( std::remove( geometries_.begin( ), geometries_.end( ), node ), geometries_.end( ) );
        SkASSERT( geometries_.size( ) == origSize - 1 );

        this->unobserveInval( node );
        this->invalidate( );
    }


    void DrawList::onRender( SkCanvas* canvas, const RenderContext* ctx ) const
    {
        const auto local_ctx = ScopedRenderContext( canvas, ctx ).setIsolation( this->bounds( ), canvas->getTotalMatrix( ), requiresIsolation_ );

        auto paint = paint_->makePaint( );
        if ( ctx )
        {
            local_ctx->modulatePaint( canvas->getTotalMatrix( ), &paint );
        }
        const auto skipDraw = paint.nothingToDraw( ) || ( paint.getStyle( ) == SkPaint::kStroke_Style && paint.getStrokeWidth( ) <= 0 );

        if ( !skipDraw )
        {

            for ( const auto& geometry : geometries_ )
            {
                geometry->draw( canvas, paint );
            }
        }
    }

    const RenderNode* DrawList::onNodeAt( const SkPoint& p ) const
    {
        const auto paint = paint_->makePaint( );

        if ( !paint.getAlpha( ) )
        {
            return nullptr;
        }

        if ( paint.getStyle( ) == SkPaint::Style::kFill_Style )
        {
            for ( const auto& geometry : geometries_ )
            {
                if ( geometry->contains( p ) )
                {
                    return this;
                }
            }
        }

        for ( const auto& geometry : geometries_ )
        {
            SkPath stroke_path;
            if ( paint.getFillPath( geometry->asPath( ), &stroke_path ) )
            {
                if ( stroke_path.contains( p.x( ), p.y( ) ) )
                {
                    return this;
                }
            }
        }
        return nullptr;
    }

    SkRect DrawList::onRevalidate( InvalidationController* ic, const SkMatrix& ctm )
    {
        SkASSERT( this->hasInval( ) );

        SkRect bounds = SkRect::MakeEmpty( );
        requiresIsolation_ = false;

        for ( size_t i = 0; i < geometries_.size( ); ++i )
        {
            const auto child_bounds = geometries_[i]->revalidate( ic, ctm );

            // If any of the child nodes overlap, group effects require layer isolation.
            if ( !requiresIsolation_ && i > 0 && child_bounds.intersects( bounds ) )
            {
                requiresIsolation_ = true;
            }

            bounds.join( child_bounds );
        }

        paint_->revalidate( ic, ctm );

        const auto paint = paint_->makePaint( );
        SkASSERT( paint.canComputeFastBounds( ) );

        return paint.computeFastBounds( bounds, &bounds );
    }
}