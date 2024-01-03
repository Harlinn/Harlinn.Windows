#pragma once
#ifndef HARLINN_SCENEGRAPH_SKSCENEGRAPH_H_
#define HARLINN_SCENEGRAPH_SKSCENEGRAPH_H_
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


#include <HWDef.h>

#include <skia/core/SkCanvas.h>
#include <skia/core/SkPath.h>
#include <skia/core/SkTextBlob.h>
#include <skia/core/SkFontMgr.h>
#include <skia/utils/SkTextUtils.h>
#include <skia/tools/Resources.h>
#include "DecodeFile.h"
#include <xxhash_cx.h>
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>

#include <HCCObservable.h>
#include <HCCDataSource.h>


#ifndef SK_API_EXT
#define SK_API_EXT
#endif

namespace Harlinn::Windows::Skia::SceneGraph
{
    using Matrix = SkM44;
    using namespace Harlinn::Common;

#define SCENEGRAPH_IMPLEMENT_PROPERTY(_propertyType_, _propertyName_, _propertyMemberVariableName_) HCC_OBSERVABLE_IMPLEMENT_PROPERTY(_propertyType_, _propertyName_, _propertyMemberVariableName_)
#define SCENEGRAPH_IMPLEMENT_POINTER_PROPERTY(_propertyType_, _propertyName_, _propertyMemberVariableName_) HCC_OBSERVABLE_IMPLEMENT_POINTER_PROPERTY(_propertyType_, _propertyName_, _propertyMemberVariableName_)





    class Group;
    class Scene;
    class Node : public Observable<Node>
    {
    public:
        using Base = Observable<Node>;
        using ThisType = Node;
    private:
        Node* owner_ = nullptr;
        SceneGraph::Matrix matrix_;
        mutable int restoreToCount_ = 0;
    protected:
        Node( ) 
        { }
        Node( Node* owner )
            : owner_( owner )
        { }
        Node( const Matrix& matrix ) 
            : matrix_( matrix )
        { }
        Node( Node* owner, const Matrix& matrix )
            : owner_( owner ), matrix_( matrix )
        { }
    public:
        void Render( SkCanvas* canvas ) const
        {
            this->OnPreRender( canvas );
            this->OnRender( canvas );
            this->OnPostRender( canvas );
        }
        SkScalar X( ) const
        {
            return matrix_.rc(0,3);
        }
        SkScalar Y( ) const
        {
            return matrix_.rc( 1, 3 );
        }
        SkScalar Z( ) const
        {
            return matrix_.rc( 2, 3 );
        }

        SkPoint ToNode( const SkPoint& point ) const
        {
            const float* m = reinterpret_cast<const float*>(&matrix_);
            float x = point.fX;
            float y = point.fY;

            float tx = x / m[0] - 
                       ( m[4]? y / m[4] : 0) -
                       m[12];
            float ty = y / m[5] -
                       ( m[1]? x / m[1] : 0) -
                       m[13];

            return { tx, ty };
        }

        SkPoint ToOwner( const SkPoint& point ) const
        {
            const float* m = reinterpret_cast<const float*>( &matrix_ );
            float x = point.fX;
            float y = point.fY;

            float tx = x * m[0] + y * m[4] + m[12];
            float ty = x * m[1] + y * m[5] + m[13];

            return { tx, ty };
        }


        void MoveTo( SkScalar x, SkScalar y )
        {
            matrix_.setRC( 0, 3, x );
            matrix_.setRC( 1, 3, y );
            this->DoOnChanged( );
        }

        void MoveTo( SkScalar x, SkScalar y, SkScalar z )
        {
            matrix_.setRC( 0, 3, x );
            matrix_.setRC( 1, 3, y );
            matrix_.setRC( 2, 3, z );
            this->DoOnChanged( );
        }
        void MoveBy( SkScalar dx, SkScalar dy )
        {
            auto x = matrix_.rc( 0, 3 ) + dx;
            auto y = matrix_.rc( 1, 3 ) + dy;

            matrix_.setRC( 0, 3, x );
            matrix_.setRC( 1, 3, y );
            this->DoOnChanged( );
        }

        void MoveBy( SkScalar dx, SkScalar dy, SkScalar dz )
        {
            auto x = matrix_.rc( 0, 3 ) + dx;
            auto y = matrix_.rc( 1, 3 ) + dy;
            auto z = matrix_.rc( 2, 3 ) + dz;

            matrix_.setRC( 0, 3, x );
            matrix_.setRC( 1, 3, y );
            matrix_.setRC( 2, 3, z );
            this->DoOnChanged( );
        }

        Node* NodeAt( const SkPoint& point ) const
        {
            return this->DoOnNodeAt( point );
        }

        SceneGraph::Group* Group( ) const
        {
            return this->DoOnGroup( );
        }
        SceneGraph::Scene* Scene( ) const
        {
            return this->DoOnScene( );
        }

        SCENEGRAPH_IMPLEMENT_POINTER_PROPERTY( SceneGraph::Node, Owner, owner_ );
        SCENEGRAPH_IMPLEMENT_PROPERTY( SceneGraph::Matrix, Matrix, matrix_ );

    protected:
        virtual void DoOnClip( SkCanvas* canvas ) const
        {

        }


        virtual void OnPreRender( SkCanvas* canvas ) const
        {
            restoreToCount_ = canvas->getSaveCount( );
            canvas->save( );
            canvas->concat( matrix_ );
            this->DoOnClip( canvas );
        }

        virtual void OnRender( SkCanvas* canvas ) const = 0;

        virtual void OnPostRender( SkCanvas* canvas ) const
        {
            canvas->restoreToCount( restoreToCount_ );
        }

        virtual Node* DoOnNodeAt( const SkPoint& point ) const
        {
            return nullptr;
        }

        virtual SceneGraph::Group* DoOnGroup( ) const
        {
            if ( owner_ )
            {
                return owner_->Group( );
            }
            return nullptr;
        }
        virtual SceneGraph::Scene* DoOnScene( ) const
        {
            if ( owner_ )
            {
                return owner_->Scene( );
            }
            return nullptr;
        }

    };

    
    enum class DataType
    {
        Unknown = 0,

    };
    
    




    class Style : public Observable<SceneGraph::Style>
    {
    public:
        using Base = Observable<SceneGraph::Style>;
        using ThisType = SceneGraph::Style;
    private:
        SkScalar opacity_ = 1;
        SkScalar strokeWidth_ = 1;
        SkScalar strokeMiter_ = 4;
        bool antiAlias_ = false;
        SkBlendMode blendMode_ = SkBlendMode::kSrcOver;
        SkPaint::Style paintStyle_ = SkPaint::kFill_Style;
        SkPaint::Join strokeJoin_ = SkPaint::kMiter_Join;
        SkPaint::Cap strokeCap_ = SkPaint::kButt_Cap;
    public:
        Style( ) = default;
        virtual ~Style( ) noexcept override = default;
    public:
        SkPaint MakePaint( ) const
        {
            SkPaint result;

            result.setAntiAlias( antiAlias_ );
            result.setBlendMode( blendMode_ );
            result.setStyle( paintStyle_ );
            result.setStrokeWidth( strokeWidth_ );
            result.setStrokeMiter( strokeMiter_ );
            result.setStrokeJoin( strokeJoin_ );
            result.setStrokeCap( strokeCap_ );

            this->DoOnApplyToPaint( result );

            result.setAlpha( SkScalarRoundToInt( result.getAlpha( ) * SkTPin<SkScalar>( opacity_, 0, 1 ) ) );
            
            return result;
        }


        SCENEGRAPH_IMPLEMENT_PROPERTY( SkScalar, Opacity, opacity_ );
        SCENEGRAPH_IMPLEMENT_PROPERTY( SkScalar, StrokeWidth, strokeWidth_ );
        SCENEGRAPH_IMPLEMENT_PROPERTY( SkScalar, StrokeMiter, strokeMiter_ );
        SCENEGRAPH_IMPLEMENT_PROPERTY( bool, AntiAlias, antiAlias_ );
        SCENEGRAPH_IMPLEMENT_PROPERTY( SkBlendMode, BlendMode, blendMode_ );
        SCENEGRAPH_IMPLEMENT_PROPERTY( SkPaint::Style, PaintStyle, paintStyle_ );
        SCENEGRAPH_IMPLEMENT_PROPERTY( SkPaint::Join, StrokeJoin, strokeJoin_ );
        SCENEGRAPH_IMPLEMENT_PROPERTY( SkPaint::Cap, StrokeCap, strokeCap_ );
    protected:
        virtual void DoOnApplyToPaint( SkPaint& paint ) const
        {
        }
    };

    class ColorStyle : public Style
    {
    public:
        using Base = SceneGraph::Style;
        using ThisType = ColorStyle;
    private:
        SkColor color_;
    protected:
        ColorStyle( SkColor color )
            : color_( color )
        { }
    public:
        SCENEGRAPH_IMPLEMENT_PROPERTY( SkColor, Color, color_ );
    protected:
        virtual void DoOnApplyToPaint( SkPaint& paint ) const override
        {
            Base::DoOnApplyToPaint( paint );
            paint.setColor( color_ );
        }
    };
    
    


    class ShaderStyle : public Style
    {
    public:
        using Base = SceneGraph::Style;
        using ThisType = ShaderStyle;
    private:
        sk_sp<SkShader> shader_;
    protected:
        ShaderStyle( sk_sp<SkShader> shader )
            : shader_( shader )
        { }
    public:
        SCENEGRAPH_IMPLEMENT_PROPERTY( sk_sp<SkShader>, Shader, shader_ );
    protected:
        virtual void DoOnApplyToPaint( SkPaint& paint ) const override
        {
            Base::DoOnApplyToPaint( paint );
            paint.setShader( shader_ );
        }
    };


    enum class HitTestResult
    {
        Unknown = 0,
        No,
        Yes
    };


    class Geometry : public Node
    {
    public:
        using Base = Node;
        using ThisType = Geometry;
    private:
        ReferenceCountedPtr<SceneGraph::Style> style_;
    protected:
        Geometry( Node* owner, ReferenceCountedPtr<SceneGraph::Style> style )
            : Base( owner ), style_( std::move( style ) )
        { }
        Geometry( Node* owner, const SceneGraph::Matrix& matrix, ReferenceCountedPtr<SceneGraph::Style> style )
            : Base( owner, matrix ), style_( std::move( style ) )
        { }
    public:
        SCENEGRAPH_IMPLEMENT_PROPERTY( ReferenceCountedPtr<SceneGraph::Style>, Style, style_ );

        SkPath AsPath( ) const
        {
            return this->DoOnAsPath( );
        }

    protected:
        HitTestResult HitTest( const SkPoint& point, const SkPaint& paint ) const
        {
            auto hitTestResult = this->DoOnSimpleHitTest( point, paint );
            if ( hitTestResult == HitTestResult::Unknown )
            {
                hitTestResult = this->DoOnComplexHitTest( point, paint );
            }
            return hitTestResult;
        }


        virtual SkPath DoOnAsPath( ) const = 0;

        virtual HitTestResult DoOnSimpleHitTest( const SkPoint& point, const SkPaint& paint ) const
        {
            return HitTestResult::Unknown;
        }
        virtual HitTestResult DoOnComplexHitTest( const SkPoint& point, const SkPaint& paint ) const
        {
            SkPath stroke_path;
            if ( !paint.getFillPath( AsPath( ), &stroke_path ) )
            {
                return HitTestResult::No;
            }
            return stroke_path.contains( point.x( ), point.y( ) ) ? HitTestResult::Yes : HitTestResult::No;
        }



        virtual Node* DoOnNodeAt( const SkPoint& point ) const override
        {
            Node* result = nullptr;
            auto paint = Style( )->MakePaint( );
            // Not transparent?
            if ( paint.getAlpha( ) )
            {
                auto hitTestResult = HitTest( point, paint );
                if ( hitTestResult == HitTestResult::Yes )
                {
                    result = const_cast<ThisType*>( this );
                }
            }

            return result;
        }
    };


    class SimpleGeometry : public Geometry
    {
    public:
        using Base = Geometry;
        using ThisType = SimpleGeometry;
    private:
        SkPathDirection pathDirection_ = SkPathDirection::kCW;
    protected:
        SimpleGeometry( Node* owner, ReferenceCountedPtr<SceneGraph::Style> style )
            : Base( owner, std::move( style ) )
        { }
        SimpleGeometry( Node* owner, const SceneGraph::Matrix& matrix, ReferenceCountedPtr<SceneGraph::Style> style )
            : Base( owner, matrix, std::move( style ) )
        { }
    public:
        SCENEGRAPH_IMPLEMENT_PROPERTY( SkPathDirection, PathDirection, pathDirection_ );
    };


    
    class Rectangle : public SimpleGeometry
    {
    public:
        using Base = SimpleGeometry;
        using ThisType = Rectangle;
    private:
        SkSize size_;
        uint32_t initialPointIndex_ = 0;
    protected:
        Rectangle( Node* owner, ReferenceCountedPtr<SceneGraph::Style> style, const SkSize& size )
            : Base( owner, std::move( style ) ), size_( size )
        { }
        Rectangle( Node* owner, const SceneGraph::Matrix& matrix, ReferenceCountedPtr<SceneGraph::Style> style, const SkSize& size )
            : Base( owner, matrix, std::move( style ) ), size_( size )
        { }
    public:
        SCENEGRAPH_IMPLEMENT_PROPERTY( SkSize, Size, size_ );
        SCENEGRAPH_IMPLEMENT_PROPERTY( uint32_t, InitialPointIndex, initialPointIndex_ );
    protected:
        virtual HitTestResult DoOnSimpleHitTest( const SkPoint& point, const SkPaint& paint ) const
        {
            if ( paint.getStyle( ) == SkPaint::Style::kFill_Style )
            {
                return ( point.x( ) >= 0 && point.x( ) < size_.width( ) &&
                         point.y( ) >= 0 && point.y( ) < size_.height( ) ) ? HitTestResult::Yes : HitTestResult::No;
            }
            return HitTestResult::Unknown;
        }

        virtual void OnRender( SkCanvas* canvas ) const override
        {
            auto rect = SkRect::MakeXYWH( 0, 0, size_.width( ), size_.height( ) );
            auto paint = Style( )->MakePaint( );
            canvas->drawRect( rect, paint );
        }

        virtual SkPath DoOnAsPath( ) const override
        {
            auto rect = SkRect::MakeXYWH( 0, 0, size_.width( ), size_.height( ) );
            return SkPath::Rect( rect, PathDirection(), InitialPointIndex() );
        }
    };

    class RoundedRectangle : public SimpleGeometry
    {
    public:
        using Base = SimpleGeometry;
        using ThisType = RoundedRectangle;
    private:
        SkRRect data_;
        uint32_t initialPointIndex_ = 0;
    protected:
        RoundedRectangle( Node* owner, ReferenceCountedPtr<SceneGraph::Style> style, const SkRRect& data )
            : Base( owner, std::move( style ) ), data_( data )
        {
        }
        RoundedRectangle( Node* owner, const SceneGraph::Matrix& matrix, ReferenceCountedPtr<SceneGraph::Style> style, const SkRRect& data )
            : Base( owner, matrix, std::move( style ) ), data_( data )
        {
        }
    public:
        SCENEGRAPH_IMPLEMENT_PROPERTY( SkRRect, Data, data_ );
        SCENEGRAPH_IMPLEMENT_PROPERTY( uint32_t, InitialPointIndex, initialPointIndex_ );
    protected:
        virtual void OnRender( SkCanvas* canvas ) const override
        {
            auto paint = Style( )->MakePaint( );
            canvas->drawRRect( data_, paint );
        }

        virtual SkPath DoOnAsPath( ) const override
        {
            return SkPath::RRect( data_, PathDirection( ), InitialPointIndex( ) );
        }
    };

    class Oval : public SimpleGeometry
    {
    public:
        using Base = SimpleGeometry;
        using ThisType = Oval;
    private:
        SkSize size_;
        uint32_t initialPointIndex_ = 0;
    protected:
        Oval( Node* owner, ReferenceCountedPtr<SceneGraph::Style> style, const SkSize& size )
            : Base( owner, std::move( style ) ), size_( size )
        {
        }
        Oval( Node* owner, const SceneGraph::Matrix& matrix, ReferenceCountedPtr<SceneGraph::Style> style, const SkSize& size )
            : Base( owner, matrix, std::move( style ) ), size_( size )
        {
        }
    public:
        SCENEGRAPH_IMPLEMENT_PROPERTY( SkSize, Size, size_ );
        SCENEGRAPH_IMPLEMENT_PROPERTY( uint32_t, InitialPointIndex, initialPointIndex_ );
    protected:
        virtual void OnRender( SkCanvas* canvas ) const override
        {
            auto rect = SkRect::MakeXYWH( 0, 0, size_.width( ), size_.height( ) );
            auto paint = Style( )->MakePaint( );
            canvas->drawOval( rect, paint );
        }

        virtual SkPath DoOnAsPath( ) const override
        {
            auto rect = SkRect::MakeXYWH( 0, 0, size_.width( ), size_.height( ) );
            return SkPath::Oval( rect, PathDirection( ), InitialPointIndex( ) );
        }
    };




    class Circle : public SimpleGeometry
    {
    public:
        using Base = SimpleGeometry;
        using ThisType = Circle;
    private:
        SkScalar radius_;
    protected:
        Circle( Node* owner, ReferenceCountedPtr<SceneGraph::Style> style, SkScalar radius )
            : Base( owner, std::move( style ) ), radius_( radius )
        {
        }
        Circle( Node* owner, const SceneGraph::Matrix& matrix, ReferenceCountedPtr<SceneGraph::Style> style, SkScalar radius )
            : Base( owner, matrix, std::move( style ) ), radius_( radius )
        {
        }
    public:
        SCENEGRAPH_IMPLEMENT_PROPERTY( SkScalar, Radius, radius_ );
    protected:
        virtual HitTestResult DoOnSimpleHitTest( const SkPoint& point, const SkPaint& paint ) const
        {
            if ( paint.getStyle( ) == SkPaint::Style::kFill_Style )
            {
                auto r = sqrt( point.x() * point.x( ) + point.y( ) * point.y( ) );
                return r <= radius_ ? HitTestResult::Yes : HitTestResult::No;
            }
            return HitTestResult::Unknown;
        }

        virtual void OnRender( SkCanvas* canvas ) const override
        {
            auto paint = Style( )->MakePaint( );
            canvas->drawCircle( 0,0, radius_, paint );
        }

        virtual SkPath DoOnAsPath( ) const override
        {
            return SkPath::Circle(0,0, radius_, PathDirection( ) );
        }
    };




    class Path : public Geometry
    {
    public:
        using Base = Geometry;
        using ThisType = Path;
    private:
        SkPath data_;
    protected:
        Path( Node* owner, ReferenceCountedPtr<SceneGraph::Style> style, const SkPath& path )
            : Base( owner, std::move( style ) ), data_( path )
        {
        }
        Path( Node* owner, const SceneGraph::Matrix& matrix, ReferenceCountedPtr<SceneGraph::Style> style, const SkPath& path )
            : Base( owner, matrix, std::move( style ) ), data_( path )
        {
        }
    public:
        SCENEGRAPH_IMPLEMENT_PROPERTY( SkPath, Data, data_ );
    protected:
        virtual void OnRender( SkCanvas* canvas ) const override
        {
            auto paint = Style( )->MakePaint( );
            canvas->drawPath( data_, paint );
        }

        virtual SkPath DoOnAsPath( ) const override
        {
            return data_;
        }
    };


    class Text : public Geometry
    {
    public:
        using Base = Geometry;
        using ThisType = Text;
    private:
        sk_sp<SkTypeface> typeface_;
        SkString data_;
        SkScalar fontSize_ = 12;
        SkScalar scale_ = 1;
        SkScalar skew_ = 0;
        SkTextUtils::Align align_ = SkTextUtils::kLeft_Align;
        SkFont::Edging edging_ = SkFont::Edging::kAntiAlias;
        SkFontHinting hinting_ = SkFontHinting::kNormal;

        // cached text blob
        mutable sk_sp<SkTextBlob> blob_;
    protected:
        Text( Node* owner, ReferenceCountedPtr<SceneGraph::Style> style, sk_sp<SkTypeface> typeface, const SkString& data )
            : Base( owner, std::move( style ) ), typeface_( std::move(typeface) ), data_( data )
        { }
        Text( Node* owner, const SceneGraph::Matrix& matrix, ReferenceCountedPtr<SceneGraph::Style> style, sk_sp<SkTypeface> typeface, const SkString& data )
            : Base( owner, matrix, std::move( style ) ), typeface_( std::move( typeface ) ), data_( data )
        { }
    public:
        SCENEGRAPH_IMPLEMENT_PROPERTY( sk_sp<SkTypeface>, Typeface, typeface_ );
        SCENEGRAPH_IMPLEMENT_PROPERTY( SkString, Data, data_ );
        SCENEGRAPH_IMPLEMENT_PROPERTY( SkScalar, FontSize, fontSize_);
        SCENEGRAPH_IMPLEMENT_PROPERTY( SkScalar, Scale, scale_);
        SCENEGRAPH_IMPLEMENT_PROPERTY( SkScalar, Skew, skew_);
        SCENEGRAPH_IMPLEMENT_PROPERTY( SkTextUtils::Align, Align, align_);
        SCENEGRAPH_IMPLEMENT_PROPERTY( SkFont::Edging, Edging, edging_);
        SCENEGRAPH_IMPLEMENT_PROPERTY( SkFontHinting, Hinting, hinting_);
    private:
        SkPoint alignedPosition( SkScalar advance ) const
        {
            SkPoint aligned;
            switch ( align_ )
            {
                case SkTextUtils::kCenter_Align:
                    aligned.offset( -advance / 2, 0 );
                    break;
                case SkTextUtils::kRight_Align:
                    aligned.offset( -advance, 0 );
                    break;
            }
            return aligned;
        }
        sk_sp<SkTextBlob> Blob( ) const
        {
            if ( !blob_ )
            {
                SkFont font;
                font.setTypeface( typeface_ );
                font.setSize( fontSize_ );
                font.setScaleX( scale_ );
                font.setSkewX( skew_ );
                font.setEdging( edging_ );
                font.setHinting( hinting_ );

                blob_ = SkTextBlob::MakeFromText( data_.c_str( ), data_.size( ), font, SkTextEncoding::kUTF8 );
            }
            return blob_;
        }
    protected:
        

        virtual void OnRender( SkCanvas* canvas ) const override
        {
            auto paint = Style( )->MakePaint( );
            auto blob = Blob( );

            //const auto aligned_pos = this->alignedPosition( this->bounds( ).width( ) );
            //canvas->drawTextBlob( blob, aligned_pos.x( ), aligned_pos.y( ), paint );
            canvas->drawTextBlob( blob, 0, 0, paint );
        }

        virtual SkPath DoOnAsPath( ) const override
        {
            return SkPath( );
        }
    };




    class Image : public Node
    {
    public:
        using Base = Node;
        using ThisType = Image;
    private:
        sk_sp<SkImage> data_;
        SkSamplingOptions samplingOptions_;
        bool antiAlias_ = true;
    protected:
        Image( Node* owner, sk_sp<SkImage> data, const SkSamplingOptions& samplingOptions )
            : Base( owner ), data_( std::move( data ) ), samplingOptions_( samplingOptions )
        {
        }
        Image( Node* owner, const SceneGraph::Matrix& matrix, sk_sp<SkImage> data, const SkSamplingOptions& samplingOptions )
            : Base( owner, matrix ), data_( std::move( data ) ), samplingOptions_( samplingOptions )
        {
        }
    public:


        SCENEGRAPH_IMPLEMENT_PROPERTY( sk_sp<SkImage>, Data, data_ );
        SCENEGRAPH_IMPLEMENT_PROPERTY( SkSamplingOptions, SamplingOptions, samplingOptions_ );
        SCENEGRAPH_IMPLEMENT_PROPERTY( bool, AntiAlias, antiAlias_ );
    protected:
        virtual void OnRender( SkCanvas* canvas ) const override
        {
            if ( !data_ )
            {
                return;
            }

            SkPaint paint;
            paint.setAntiAlias( antiAlias_ );

            canvas->drawImage( data_, 0, 0, samplingOptions_, &paint );
        }

        virtual Node* DoOnNodeAt( const SkPoint& point ) const
        {
            if ( data_ )
            {
                return point.x( ) >= 0 && point.x( ) < data_->width( ) &&
                    point.y( ) >= 0 && point.y( ) < data_->height( ) ? const_cast<ThisType*>( this ) : nullptr;
            }
            return nullptr;
        }

    };

    namespace Chart
    {
        class Diagram;
        class SeriesBase;
        class Series;
        class ViewBase;

        enum class ScaleType
        {
            Auto = 0,
            Numerical,
            DateTime,
            TimeSpan,
            Qualitative
        };


        class DiagramStyle : public Observable<DiagramStyle>
        {
        public:
            using Base = Observable<DiagramStyle>;
            using ThisType = DiagramStyle;
        private:

        public:
            DiagramStyle( ) = default;
        };

        
        class SeriesLabelBase : public Observable<SeriesLabelBase>
        {
        public:
            using Base = Observable<SeriesLabelBase>;
            using ThisType = SeriesLabelBase;
        private:

        public:
            SeriesLabelBase( ) = default;
        };


        class SeriesCollection;

        class SeriesBase : public Observable<SeriesBase>
        {
        public:
            using Base = Observable<SeriesBase>;
            using ThisType = SeriesBase;
        private:
            SeriesCollection* collection_;
            ReferenceCountedPtr<SeriesLabelBase> label_;
        public:
            SeriesBase( SeriesCollection* collection ) 
                : collection_( collection )
            { }

            SCENEGRAPH_IMPLEMENT_PROPERTY( ReferenceCountedPtr<SeriesLabelBase>, Label, label_ );
        protected:
            inline virtual void DoOnChanged( uint64_t key = 0, void* data = nullptr ) override;
        };


        class Series : public SeriesBase
        {
        public:
            using Base = SeriesBase;
            using ThisType = Series;
        private:
            ReferenceCountedPtr<Core::DataSource> dataSource_;
        public:
            Series( SeriesCollection* collection )
                : Base( collection )
            { }
            virtual ~Series( ) noexcept override = default;

            SCENEGRAPH_IMPLEMENT_PROPERTY( ReferenceCountedPtr<Core::DataSource>, DataSource, dataSource_ );
        };


        class SeriesCollection 
        {
            friend class SeriesBase;
        private:
            Chart::Diagram* diagram_;
            std::vector< ReferenceCountedPtr<SeriesBase> > items_;
        public:
            SeriesCollection( Chart::Diagram* diagram )
                : diagram_( diagram )
            { }

            Chart::Diagram* Diagram( ) const
            {
                return diagram_;
            }


        protected:
            virtual void DoOnSeriesChanged( SeriesBase* series, uint64_t key, void* data )
            {

            }
        };

        inline void SeriesBase::DoOnChanged( uint64_t key, void* data )
        {
            Base::DoOnChanged( key, data );
            collection_->DoOnSeriesChanged( this, key, data );
        }





        class AxisBase : public Observable<AxisBase>
        {
        public:
            using Base = Observable<AxisBase>;
            using ThisType = AxisBase;
        private:
        public:
            AxisBase( ) = default;
            virtual ~AxisBase( ) noexcept override = default;
        };


        class Axis2D : public AxisBase
        {
        public:
            using Base = AxisBase;
            using ThisType = AxisBase;
        private:
        public:
            Axis2D( ) = default;
            virtual ~Axis2D( ) noexcept override = default;
        };


        class Axis : public Axis2D
        {
        public:
            using Base = Axis2D;
            using ThisType = Axis;
        private:
        public:
            Axis( ) = default;
            virtual ~Axis( ) noexcept override = default;
        };

        class AxisXBase : public Axis
        {
        public:
            using Base = Axis;
            using ThisType = AxisXBase;
        private:
        public:
            AxisXBase( ) = default;
            virtual ~AxisXBase( ) noexcept override = default;
        };

        class AxisYBase : public Axis
        {
        public:
            using Base = Axis;
            using ThisType = AxisYBase;
        private:
        public:
            AxisYBase( ) = default;
            virtual ~AxisYBase( ) noexcept override = default;
        };


        class ViewSeriesCollection
        {
            ViewBase* view_;
            std::vector< SeriesBase* > items_;
        public:
            ViewSeriesCollection( ViewBase* view )
                : view_( view )
            { }
        };


        class ViewCollection;
        class ViewBase : public Observable<ViewBase>
        {
        public:
            using Base = Observable<ViewBase>;
            using ThisType = ViewBase;
        private:
            ViewCollection* collection_;
            ViewSeriesCollection series_;
        public: 
            ViewBase( ViewCollection* collection )
                : collection_( collection ), series_(this)
            { }
        };



        class RadarView : public ViewBase
        {
        public:
            using Base = ViewBase;
            using ThisType = RadarView;
        private:

        };



        class ViewCollection
        {
        private:
            Chart::Diagram* diagram_;
            std::vector< ReferenceCountedPtr<ViewBase> > items_;
        public:
            ViewCollection( Chart::Diagram* diagram )
                : diagram_( diagram )
            { }

            Chart::Diagram* Diagram( ) const
            {
                return diagram_;
            }
        };




        class Diagram : public Node
        {
        public:
            using Base = Node;
            using ThisType = Diagram;
        private:
            ReferenceCountedPtr<Chart::DiagramStyle> style_;
            SeriesCollection series_;
            ViewCollection views_;
            boost::signals2::connection styleConnection_;
        protected:
            Diagram( Node* owner, ReferenceCountedPtr<Chart::DiagramStyle> style )
                : Base( owner ), style_( std::move( style ) ), series_( this ), views_( this )
            {
                AttachToStyle( );
            }
            Diagram( Node* owner, const SceneGraph::Matrix& matrix, ReferenceCountedPtr<Chart::DiagramStyle> style, sk_sp<DataSource> dataSource )
                : Base( owner, matrix ), style_( std::move( style ) ), series_( this ), views_( this )
            {
                AttachToStyle( );
            }
        public:
            ~Diagram( )
            {
                DetachFromStyle( );
            }
        protected:

            void AttachToStyle( )
            {
                if ( style_ )
                {
                    styleConnection_ = style_->OnChanged.connect( [this]( Chart::DiagramStyle* diagramStyle, uint64_t key, void* data )
                    {
                        this->DoOnStyleChanged( diagramStyle );
                    } );
                    this->DoOnStyleChanged( style_.get( ) );
                }

            }
            void DetachFromStyle( )
            {
                if ( styleConnection_.connected( ) )
                {
                    styleConnection_.disconnect( );
                }
                style_.ResetPtr( );
                this->DoOnStyleChanged( nullptr );
            }

            virtual void DoOnStyleChanged( Chart::DiagramStyle* style )
            {
            }

        public:
            const ReferenceCountedPtr<DiagramStyle>& Style( ) const
            {
                return style_;
            }
            void SetStyle( const ReferenceCountedPtr<DiagramStyle>& style )
            {
                if ( style_ != style )
                {
                    DetachFromStyle( );
                    style_ = style;
                    AttachToStyle( );
                }
            }
        };



    } // End of namespace Chart

    class Radar : public SimpleGeometry
    {
    public:
        using Base = SimpleGeometry;
        using ThisType = Radar;
    private:
        SkScalar radius_;
        int lineCount_ = 12;
        int circleCount_ = 6;
    protected:
        Radar( Node* owner, ReferenceCountedPtr<SceneGraph::Style> style, SkScalar radius )
            : Base( owner, std::move( style ) ), radius_( radius )
        {
        }
        Radar( Node* owner, const SceneGraph::Matrix& matrix, ReferenceCountedPtr<SceneGraph::Style> style, SkScalar radius )
            : Base( owner, matrix, std::move( style ) ), radius_( radius )
        {
        }
    public:
        SCENEGRAPH_IMPLEMENT_PROPERTY( SkScalar, Radius, radius_ );
    protected:
        void PolarToCartesian( SkScalar r, SkScalar q, SkScalar& x, SkScalar& y )
        {
            x = r * cos( q ); 
            y = r * sin( q );
        }

        virtual void OnRender( SkCanvas* canvas ) const override
        {
            auto paint = Style( )->MakePaint( );

            auto r = radius_;
            auto dr = r / static_cast<SkScalar>( circleCount_ );
            for ( int i = 0; i < circleCount_; i++ )
            {
                canvas->drawCircle( 0, 0, r, paint );
                r -= dr;
            }

            r = radius_;
            SkScalar l = 0.0f;
            SkScalar dl = 2.0f * static_cast<SkScalar>( M_PI ) / static_cast<SkScalar>( lineCount_ );

            SkFont font;
            font.setSize( 25 );
            char buffer[10]{};

            for ( int i = 0; i < lineCount_; i++ )
            {
                SkScalar x = r * cos( -l );
                SkScalar y = r * sin( -l );
                canvas->drawLine( 0, 0, x, y, paint );

                auto tr = r + dr;

                x = tr * cos( -l );
                y = tr * sin( -l );

                auto degrees = static_cast<int>( std::roundf( SkRadiansToDegrees( l ) ) );
                itoa( degrees, buffer, 10 );
                size_t length = strlen( buffer );

                canvas->drawSimpleText( buffer, length, SkTextEncoding::kUTF8, x, y, font, paint );

                l += dl;
            }
        }


        virtual SkPath DoOnAsPath( ) const override
        {
            return SkPath::Circle( 0, 0, radius_, PathDirection( ) );
        }

    };






    class Group : public Node
    {
    public:
        using Base = Node;
        using ThisType = Group;
    private:
        std::vector< ReferenceCountedPtr<Node> > nodes_;

    protected:
        Group( )
        { }
        Group( Node* owner )
            : Base( owner )
        { }
        Group( const SceneGraph::Matrix& matrix )
            : Base( matrix )
        { }
        Group( Node* owner, const SceneGraph::Matrix& matrix )
            : Base( owner, matrix )
        { }
    public:

    protected:
        void AddNode( ReferenceCountedPtr<Node> node )
        {
            nodes_.emplace_back( std::move( node ) );
        }
    public:
        template<typename T, typename ...Args>
        ReferenceCountedPtr<T> Add( const SceneGraph::Matrix& matrix, ReferenceCountedPtr<Style> style, Args&&... args )
        {
            auto result = MakeReferenceCounted<T>( this, matrix, std::move( style ), std::forward<Args>( args )... );
            AddNode( result );
            return result;
        }
        template<typename T, typename ...Args>
        ReferenceCountedPtr<T> Add( SkScalar x, SkScalar y, ReferenceCountedPtr<Style> style, Args&&... args )
        {
            auto m = SceneGraph::Matrix::Translate( x, y );
            return Add<T>( m, std::move( style ), std::forward<Args>( args )... );
        }



        ReferenceCountedPtr<Rectangle> AddRectangle( const SceneGraph::Matrix& matrix, ReferenceCountedPtr<Style> style, const SkSize& size )
        {
            auto result = MakeReferenceCounted<Rectangle>( this, matrix, std::move( style ), size );
            AddNode( result );
            return result;
        }

        ReferenceCountedPtr<Rectangle> AddRectangle( const SkRect& rect, ReferenceCountedPtr<Style> style )
        {
            auto m = SceneGraph::Matrix::Translate( rect.left( ), rect.top( ) );
            SkSize size( rect.width(), rect.height() );
            return AddRectangle(m, std::move( style ), size );
        }

        ReferenceCountedPtr<Oval> AddOval( const SceneGraph::Matrix& matrix, ReferenceCountedPtr<Style> style, const SkSize& size )
        {
            auto result = MakeReferenceCounted<Oval>( this, matrix, std::move( style ), size );
            AddNode( result );
            return result;
        }

        ReferenceCountedPtr<Oval> AddOval( const SkRect& rect, ReferenceCountedPtr<Style> style )
        {
            auto m = SceneGraph::Matrix::Translate( rect.left( ), rect.top( ) );
            SkSize size( rect.width( ), rect.height( ) );
            return AddOval( m, std::move( style ), size );
        }



        ReferenceCountedPtr<Circle> AddCircle( const SceneGraph::Matrix& matrix, ReferenceCountedPtr<Style> style, const SkScalar& radius )
        {
            auto result = MakeReferenceCounted<Circle>( this, matrix, std::move( style ), radius );
            AddNode( result );
            return result;
        }
        ReferenceCountedPtr<Circle> AddCircle( SkScalar centerX, SkScalar centerY, SkScalar radius, ReferenceCountedPtr<Style> style )
        {
            auto m = SceneGraph::Matrix::Translate( centerX, centerY );
            return AddCircle(m, std::move( style ), radius );
        }

        ReferenceCountedPtr<Path> AddPath( const SceneGraph::Matrix& matrix, ReferenceCountedPtr<Style> style, const SkPath& path )
        {
            auto result = MakeReferenceCounted<Path>( this, matrix, std::move( style ), path );
            AddNode( result );
            return result;
        }

        ReferenceCountedPtr<Path> AddPath( SkScalar x, SkScalar y, ReferenceCountedPtr<Style> style, const SkPath& path )
        {
            auto m = SceneGraph::Matrix::Translate( x, y );
            return AddPath( m, std::move( style ), path );
        }

        ReferenceCountedPtr<Text> AddText( const SceneGraph::Matrix& matrix, ReferenceCountedPtr<Style> style, sk_sp<SkTypeface> typeface, const SkString& data )
        {
            auto result = MakeReferenceCounted<Text>( this, matrix, std::move( style ), std::move( typeface ), data );
            AddNode( result );
            return result;
        }

        ReferenceCountedPtr<Text> AddText( SkScalar x, SkScalar y, ReferenceCountedPtr<Style> style, sk_sp<SkTypeface> typeface, const SkString& data )
        {
            auto m = SceneGraph::Matrix::Translate( x, y );
            return AddText( m, std::move( style ), std::move( typeface ), data );
        }


        ReferenceCountedPtr<Image> AddImage( const SceneGraph::Matrix& matrix, sk_sp<SkImage> data, const SkSamplingOptions& samplingOptions = SkSamplingOptions() )
        {
            auto result = MakeReferenceCounted<Image>( this, matrix, std::move( data ), samplingOptions );
            AddNode( result );
            return result;
        }
        ReferenceCountedPtr<Image> AddImage( SkScalar x, SkScalar y, sk_sp<SkImage> data, const SkSamplingOptions& samplingOptions = SkSamplingOptions( ) )
        {
            auto m = SceneGraph::Matrix::Translate( x, y );
            return AddImage( m, std::move( data ), samplingOptions );
        }

        ReferenceCountedPtr<Image> AddImage( const SceneGraph::Matrix& matrix, const char* resourceName, const SkSamplingOptions& samplingOptions = SkSamplingOptions( ) )
        {
            SkBitmap bm;
            decode_file( GetResourceAsData( resourceName ), &bm );
            sk_sp<SkImage> data = SkImage::MakeFromBitmap( bm );
            return AddImage( matrix, std::move( data ), samplingOptions );
        }

        ReferenceCountedPtr<Image> AddImage( SkScalar x, SkScalar y, const char* resourceName, const SkSamplingOptions& samplingOptions = SkSamplingOptions( ) )
        {
            auto m = SceneGraph::Matrix::Translate( x, y );
            return AddImage( m, resourceName, samplingOptions );
        }


        


        ReferenceCountedPtr<Group> AddGroup( const SceneGraph::Matrix& matrix )
        {
            auto result = MakeReferenceCounted<Group>( this, matrix );
            AddNode( result );
            return result;
        }

        ReferenceCountedPtr<Group> AddGroup(SkScalar x, SkScalar y )
        {
            auto m = SceneGraph::Matrix::Translate( x, y );
            return AddGroup( m );
        }
        ReferenceCountedPtr<Group> AddGroup( const SkPoint& point )
        {
            return AddGroup( point.x(), point.y() );
        }



    protected:
        virtual void OnRender( SkCanvas* canvas ) const override
        {
            for ( const auto& node : nodes_ )
            {
                node->Render( canvas );
            }
        }
        virtual Node* DoOnNodeAt( const SkPoint& point ) const override
        {
            for ( auto it = nodes_.crbegin( ); it != nodes_.crend( ); ++it )
            {
                auto node = it->get( );
                auto mappedPoint = node->ToNode( point );
                if ( auto* foundNode = node->NodeAt( mappedPoint ) )
                {
                    return foundNode;
                }
            }
            return nullptr;
        }
        virtual SceneGraph::Group* DoOnGroup( ) const override
        {
            return const_cast<ThisType*>(this);
        }
        
        

    };


    class Scene : public Group
    {
    public:
        using Base = Group;
        using ThisType = Scene;
    private:
    protected:
        Scene( )
        { }
        Scene( const SceneGraph::Matrix& matrix )
            : Base( matrix )
        { }
    public:
        
    protected:
        virtual SceneGraph::Group* DoOnGroup( ) const override
        {
            return nullptr;
        }
        virtual SceneGraph::Scene* DoOnScene( ) const override
        {
            return const_cast<ThisType*>( this );
        }
    };


}

#endif
