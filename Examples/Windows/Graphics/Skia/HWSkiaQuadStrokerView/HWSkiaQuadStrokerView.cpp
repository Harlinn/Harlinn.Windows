/*
   Copyright 2024-2025 Espen Harlinn

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
#include "skia/core/SkBlendMode.h"
#include "skia/core/SkCanvas.h"
#include "skia/core/SkColor.h"
#include "skia/core/SkFont.h"
#include "skia/core/SkImageInfo.h"
#include "skia/core/SkMatrix.h"
#include "skia/core/SkPaint.h"
#include "skia/core/SkPath.h"
#include "skia/core/SkPathMeasure.h"
#include "skia/core/SkPoint.h"
#include "skia/core/SkRRect.h"
#include "skia/core/SkRect.h"
#include "skia/core/SkRefCnt.h"
#include "skia/core/SkScalar.h"
#include "skia/core/SkShader.h"
#include "skia/core/SkString.h"
#include "skia/core/SkSurface.h"
#include "skia/core/SkTypes.h"
#include "skia/private/SkTArray.h"
#include "skia/private/SkTemplates.h"
#include "skia/utils/SkTextUtils.h"
#include "src/core/SkGeometry.h"
#include "src/core/SkPathPriv.h"
#include "src/core/SkPointPriv.h"
#include "src/core/SkStroke.h"
#include "skia/tools/ToolUtils.h"

#include <cfloat>

using namespace Harlinn::Windows::Skia;


class SkEvent;

static bool hittest( const SkPoint& target, SkScalar x, SkScalar y )
{
    const SkScalar TOL = 7;
    return SkPoint::Distance( target, SkPoint::Make( x, y ) ) <= TOL;
}

static int getOnCurvePoints( const SkPath& path, SkPoint storage[] )
{
    int count = 0;
    for ( auto [verb, pts, w] : SkPathPriv::Iterate( path ) )
    {
        switch ( verb )
        {
            case SkPathVerb::kMove:
            case SkPathVerb::kLine:
            case SkPathVerb::kQuad:
            case SkPathVerb::kConic:
            case SkPathVerb::kCubic:
                storage[count++] = pts[0];
                break;
            default:
                break;
        }
    }
    return count;
}

static void getContourCounts( const SkPath& path, SkTArray<int>* contourCounts )
{
    int count = 0;
    for ( auto [verb, pts, w] : SkPathPriv::Iterate( path ) )
    {
        switch ( verb )
        {
            case SkPathVerb::kMove:
            case SkPathVerb::kLine:
                count += 1;
                break;
            case SkPathVerb::kQuad:
            case SkPathVerb::kConic:
                count += 2;
                break;
            case SkPathVerb::kCubic:
                count += 3;
                break;
            case SkPathVerb::kClose:
                contourCounts->push_back( count );
                count = 0;
                break;
            default:
                break;
        }
    }
    if ( count > 0 )
    {
        contourCounts->push_back( count );
    }
}

static void erase( const sk_sp<SkSurface>& surface )
{
    SkCanvas* canvas = surface->getCanvas( );
    if ( canvas )
    {
        canvas->clear( SK_ColorTRANSPARENT );
    }
}

struct StrokeTypeButton
{
    SkRect fBounds;
    char fLabel;
    bool fEnabled;
};

struct CircleTypeButton : public StrokeTypeButton
{
    bool fFill;
};

class QuadStrokerView : public Sample
{
    enum
    {
        SKELETON_COLOR = 0xFF0000FF,
        WIREFRAME_COLOR = 0x80FF0000
    };

    enum
    {
        kCount = 18
    };
    SkPoint fPts[kCount];
    SkRect fWeightControl;
    SkRect fRadiusControl;
    SkRect fErrorControl;
    SkRect fWidthControl;
    SkRect fBounds;
    SkMatrix fMatrix, fInverse;
    sk_sp<SkShader> fShader;
    sk_sp<SkSurface> fMinSurface;
    sk_sp<SkSurface> fMaxSurface;
    StrokeTypeButton fCubicButton;
    StrokeTypeButton fConicButton;
    StrokeTypeButton fQuadButton;
    StrokeTypeButton fArcButton;
    StrokeTypeButton fRRectButton;
    CircleTypeButton fCircleButton;
    StrokeTypeButton fTextButton;
    SkString fText;
    SkScalar fTextSize;
    SkScalar fWeight;
    SkScalar fRadius;
    SkScalar fWidth, fDWidth;
    SkScalar fWidthScale;
    int fW, fH, fZoom;
    bool fAnimate;
    bool fDrawRibs;
    bool fDrawTangents;
    bool fDrawTDivs;
#ifdef SK_DEBUG
#define kStrokerErrorMin 0.001f
#define kStrokerErrorMax 5
#endif
#define kWidthMin 1
#define kWidthMax 100
public:
    QuadStrokerView( )
    {
        this->setBGColor( SK_ColorLTGRAY );

        fPts[0].set( 50, 200 );  // cubic
        fPts[1].set( 50, 100 );
        fPts[2].set( 150, 50 );
        fPts[3].set( 300, 50 );

        fPts[4].set( 350, 200 );  // conic
        fPts[5].set( 350, 100 );
        fPts[6].set( 450, 50 );

        fPts[7].set( 150, 300 );  // quad
        fPts[8].set( 150, 200 );
        fPts[9].set( 250, 150 );

        fPts[10].set( 250, 200 );  // arc
        fPts[11].set( 250, 300 );
        fPts[12].set( 150, 350 );

        fPts[13].set( 200, 200 ); // rrect
        fPts[14].set( 400, 400 );

        fPts[15].set( 250, 250 );  // oval
        fPts[16].set( 450, 450 );

        fText = "a";
        fTextSize = 12;
        fWidth = 50;
        fDWidth = 0.25f;
        fWeight = 1;
        fRadius = 150;

        fCubicButton.fLabel = 'C';
        fCubicButton.fEnabled = false;
        fConicButton.fLabel = 'K';
        fConicButton.fEnabled = false;
        fQuadButton.fLabel = 'Q';
        fQuadButton.fEnabled = false;
        fArcButton.fLabel = 'A';
        fArcButton.fEnabled = true;
        fRRectButton.fLabel = 'R';
        fRRectButton.fEnabled = false;
        fCircleButton.fLabel = 'O';
        fCircleButton.fEnabled = true;
        fCircleButton.fFill = true;
        fTextButton.fLabel = 'T';
        fTextButton.fEnabled = false;
        fAnimate = false;
        setAsNeeded( );
    }

protected:
    SkString name( ) override { return SkString( "QuadStroker" ); }

    bool onChar( SkUnichar uni ) override
    {
        if ( fTextButton.fEnabled )
        {
            switch ( uni )
            {
                case ' ':
                    fText = "";
                    break;
                case '-':
                    fTextSize = std::max( 1.0f, fTextSize - 1 );
                    break;
                case '+':
                case '=':
                    fTextSize += 1;
                    break;
                default:
                    fText.appendUnichar( uni );
            }
            return true;
        }
        return false;
    }

    void onSizeChange( ) override
    {
        fRadiusControl.setXYWH( this->width( ) - 200, 30, 30, 400 );
        fWeightControl.setXYWH( this->width( ) - 150, 30, 30, 400 );
        fErrorControl.setXYWH( this->width( ) - 100, 30, 30, 400 );
        fWidthControl.setXYWH( this->width( ) - 50, 30, 30, 400 );
        int buttonOffset = 450;
        fCubicButton.fBounds.setXYWH( this->width( ) - 50, SkIntToScalar( buttonOffset ), 30, 30 );
        buttonOffset += 50;
        fConicButton.fBounds.setXYWH( this->width( ) - 50, SkIntToScalar( buttonOffset ), 30, 30 );
        buttonOffset += 50;
        fQuadButton.fBounds.setXYWH( this->width( ) - 50, SkIntToScalar( buttonOffset ), 30, 30 );
        buttonOffset += 50;
        fArcButton.fBounds.setXYWH( this->width( ) - 50, SkIntToScalar( buttonOffset ), 30, 30 );
        buttonOffset += 50;
        fRRectButton.fBounds.setXYWH( this->width( ) - 50, SkIntToScalar( buttonOffset ), 30, 30 );
        buttonOffset += 50;
        fCircleButton.fBounds.setXYWH( this->width( ) - 50, SkIntToScalar( buttonOffset ), 30, 30 );
        buttonOffset += 50;
        fTextButton.fBounds.setXYWH( this->width( ) - 50, SkIntToScalar( buttonOffset ), 30, 30 );
        this->INHERITED::onSizeChange( );
    }

    void copyMinToMax( )
    {
        erase( fMaxSurface );
        SkCanvas* canvas = fMaxSurface->getCanvas( );
        canvas->save( );
        canvas->concat( fMatrix );
        fMinSurface->draw( canvas, 0, 0 );
        canvas->restore( );

        SkPaint paint;
        paint.setBlendMode( SkBlendMode::kClear );
        for ( int iy = 1; iy < fH; ++iy )
        {
            SkScalar y = SkIntToScalar( iy * fZoom );
            canvas->drawLine( 0, y - SK_ScalarHalf, 999, y - SK_ScalarHalf, paint );
        }
        for ( int ix = 1; ix < fW; ++ix )
        {
            SkScalar x = SkIntToScalar( ix * fZoom );
            canvas->drawLine( x - SK_ScalarHalf, 0, x - SK_ScalarHalf, 999, paint );
        }
    }

    void setWHZ( int width, int height, int zoom )
    {
        fZoom = zoom;
        fBounds.setIWH( width * zoom, height * zoom );
        fMatrix.setScale( SkIntToScalar( zoom ), SkIntToScalar( zoom ) );
        fInverse.setScale( SK_Scalar1 / zoom, SK_Scalar1 / zoom );
        fShader = ToolUtils::create_checkerboard_shader( 0xFFCCCCCC, 0xFFFFFFFF, zoom );

        SkImageInfo info = SkImageInfo::MakeN32Premul( width, height );
        fMinSurface = SkSurface::MakeRaster( info );
        info = info.makeWH( width * zoom, height * zoom );
        fMaxSurface = SkSurface::MakeRaster( info );
    }

    void draw_points( SkCanvas* canvas, const SkPath& path, SkColor color,
        bool show_lines )
    {
        SkPaint paint;
        paint.setColor( color );
        paint.setAlpha( 0x80 );
        paint.setAntiAlias( true );
        int n = path.countPoints( );
        SkAutoSTArray<32, SkPoint> pts( n );
        if ( show_lines && fDrawTangents )
        {
            SkTArray<int> contourCounts;
            getContourCounts( path, &contourCounts );
            SkPoint* ptPtr = pts.get( );
            for ( int i = 0; i < contourCounts.count( ); ++i )
            {
                int count = contourCounts[i];
                path.getPoints( ptPtr, count );
                canvas->drawPoints( SkCanvas::kPolygon_PointMode, count, ptPtr, paint );
                ptPtr += count;
            }
        }
        else
        {
            n = getOnCurvePoints( path, pts.get( ) );
        }
        paint.setStrokeWidth( 5 );
        canvas->drawPoints( SkCanvas::kPoints_PointMode, n, pts.get( ), paint );
    }

    void draw_ribs( SkCanvas* canvas, const SkPath& path, SkScalar width,
        SkColor color )
    {
        const SkScalar radius = width / 2;

        SkPathMeasure meas( path, false );
        SkScalar total = meas.getLength( );

        SkScalar delta = 8;
        SkPaint paint, labelP;
        paint.setColor( color );
        labelP.setColor( color & 0xff5f9f5f );
        SkFont font;
        SkPoint pos, tan;
        int index = 0;
        for ( SkScalar dist = 0; dist <= total; dist += delta )
        {
            if ( meas.getPosTan( dist, &pos, &tan ) )
            {
                tan.scale( radius );
                SkPointPriv::RotateCCW( &tan );
                canvas->drawLine( pos.x( ) + tan.x( ), pos.y( ) + tan.y( ),
                    pos.x( ) - tan.x( ), pos.y( ) - tan.y( ), paint );
                if ( 0 == index % 10 )
                {
                    SkString label;
                    label.appendS32( index );
                    SkRect dot = SkRect::MakeXYWH( pos.x( ) - 2, pos.y( ) - 2, 4, 4 );
                    canvas->drawRect( dot, labelP );
                    canvas->drawString( label,
                        pos.x( ) - tan.x( ) * 1.25f, pos.y( ) - tan.y( ) * 1.25f, font, labelP );
                }
            }
            ++index;
        }
    }

    void draw_t_divs( SkCanvas* canvas, const SkPath& path, SkScalar width, SkColor color )
    {
        const SkScalar radius = width / 2;
        SkPaint paint;
        paint.setColor( color );
        SkPathMeasure meas( path, false );
        SkScalar total = meas.getLength( );
        SkScalar delta = 8;
        int ribs = 0;
        for ( SkScalar dist = 0; dist <= total; dist += delta )
        {
            ++ribs;
        }
        const uint8_t* verbs = SkPathPriv::VerbData( path );
        if ( path.countVerbs( ) < 2 || SkPath::kMove_Verb != verbs[0] )
        {
            SkASSERT( 0 );
            return;
        }
        auto verb = static_cast<SkPath::Verb>( verbs[1] );
        SkASSERT( SkPath::kLine_Verb <= verb && verb <= SkPath::kCubic_Verb );
        const SkPoint* pts = SkPathPriv::PointData( path );
        SkPoint pos, tan;
        for ( int index = 0; index < ribs; ++index )
        {
            SkScalar t = (SkScalar)index / ribs;
            switch ( verb )
            {
                case SkPath::kLine_Verb:
                    tan = pts[1] - pts[0];
                    pos = pts[0];
                    pos.fX += tan.fX * t;
                    pos.fY += tan.fY * t;
                    break;
                case SkPath::kQuad_Verb:
                    pos = SkEvalQuadAt( pts, t );
                    tan = SkEvalQuadTangentAt( pts, t );
                    break;
                case SkPath::kConic_Verb:
                {
                    SkConic conic( pts, SkPathPriv::ConicWeightData( path )[0] );
                    pos = conic.evalAt( t );
                    tan = conic.evalTangentAt( t );
                } break;
                case SkPath::kCubic_Verb:
                    SkEvalCubicAt( pts, t, &pos, &tan, nullptr );
                    break;
                default:
                    SkASSERT( 0 );
                    return;
            }
            tan.setLength( radius );
            SkPointPriv::RotateCCW( &tan );
            canvas->drawLine( pos.x( ) + tan.x( ), pos.y( ) + tan.y( ),
                pos.x( ) - tan.x( ), pos.y( ) - tan.y( ), paint );
            if ( 0 == index % 10 )
            {
                SkString label;
                label.appendS32( index );
                canvas->drawString( label,
                    pos.x( ) + tan.x( ) * 1.25f, pos.y( ) + tan.y( ) * 1.25f, SkFont( ), paint );
            }
        }
    }

    void draw_stroke( SkCanvas* canvas, const SkPath& path, SkScalar width, SkScalar scale,
        bool drawText )
    {
        if ( path.isEmpty( ) )
        {
            return;
        }
        SkRect bounds = path.getBounds( );
        this->setWHZ( SkScalarCeilToInt( bounds.right( ) ), drawText
            ? SkScalarRoundToInt( scale * 3 / 2 ) : SkScalarRoundToInt( scale ),
            SkScalarRoundToInt( 950.0f / scale ) );
        erase( fMinSurface );
        SkPaint paint;
        paint.setColor( 0x1f1f0f0f );
        paint.setStyle( SkPaint::kStroke_Style );
        paint.setStrokeWidth( width * scale * scale );
        paint.setColor( 0x3f0f1f3f );
        if ( drawText )
        {
            fMinSurface->getCanvas( )->drawPath( path, paint );
            this->copyMinToMax( );
            fMaxSurface->draw( canvas, 0, 0 );
        }
        paint.setAntiAlias( true );
        paint.setStyle( SkPaint::kStroke_Style );
        paint.setStrokeWidth( 1 );

        paint.setColor( SKELETON_COLOR );
        SkPath scaled;
        SkMatrix matrix;
        matrix.reset( );
        matrix.setScale( 950 / scale, 950 / scale );
        if ( drawText )
        {
            path.transform( matrix, &scaled );
        }
        else
        {
            scaled = path;
        }
        canvas->drawPath( scaled, paint );
        draw_points( canvas, scaled, SKELETON_COLOR, true );

        if ( fDrawRibs )
        {
            draw_ribs( canvas, scaled, width, 0xFF00FF00 );
        }

        if ( fDrawTDivs )
        {
            draw_t_divs( canvas, scaled, width, 0xFF3F3F00 );
        }

        SkPath fill;

        SkPaint p;
        p.setStyle( SkPaint::kStroke_Style );
        if ( drawText )
        {
            p.setStrokeWidth( width * scale * scale );
        }
        else
        {
            p.setStrokeWidth( width );
        }
        p.getFillPath( path, &fill );
        SkPath scaledFill;
        if ( drawText )
        {
            fill.transform( matrix, &scaledFill );
        }
        else
        {
            scaledFill = fill;
        }
        paint.setColor( WIREFRAME_COLOR );
        canvas->drawPath( scaledFill, paint );
        draw_points( canvas, scaledFill, WIREFRAME_COLOR, false );
    }

    void draw_fill( SkCanvas* canvas, const SkRect& rect, SkScalar width )
    {
        if ( rect.isEmpty( ) )
        {
            return;
        }
        SkPaint paint;
        paint.setColor( 0x1f1f0f0f );
        paint.setStyle( SkPaint::kStroke_Style );
        paint.setStrokeWidth( width );
        SkPath path;
        SkScalar maxSide = std::max( rect.width( ), rect.height( ) ) / 2;
        SkPoint center = { rect.fLeft + maxSide, rect.fTop + maxSide };
        path.addCircle( center.fX, center.fY, maxSide );
        canvas->drawPath( path, paint );
        paint.setStyle( SkPaint::kFill_Style );
        path.reset( );
        path.addCircle( center.fX, center.fY, maxSide - width / 2 );
        paint.setColor( 0x3f0f1f3f );
        canvas->drawPath( path, paint );
        path.reset( );
        path.setFillType( SkPathFillType::kEvenOdd );
        path.addCircle( center.fX, center.fY, maxSide + width / 2 );
        SkRect outside = SkRect::MakeXYWH( center.fX - maxSide - width, center.fY - maxSide - width,
            ( maxSide + width ) * 2, ( maxSide + width ) * 2 );
        path.addRect( outside );
        canvas->drawPath( path, paint );
    }

    void draw_button( SkCanvas* canvas, const StrokeTypeButton& button )
    {
        SkPaint paint;
        paint.setAntiAlias( true );
        paint.setStyle( SkPaint::kStroke_Style );
        paint.setColor( button.fEnabled ? 0xFF3F0000 : 0x6F3F0000 );
        canvas->drawRect( button.fBounds, paint );
        paint.setColor( button.fEnabled ? 0xFF3F0000 : 0x6F3F0000 );
        paint.setStyle( SkPaint::kFill_Style );
        SkFont font;
        font.setSize( 25.0f );
        SkTextUtils::Draw( canvas, &button.fLabel, 1, SkTextEncoding::kUTF8,
            button.fBounds.centerX( ), button.fBounds.fBottom - 5,
            font, paint, SkTextUtils::kCenter_Align );
    }

    void draw_control( SkCanvas* canvas, const SkRect& bounds, SkScalar value,
        SkScalar min, SkScalar max, const char* name )
    {
        SkPaint paint;
        paint.setAntiAlias( true );
        paint.setStyle( SkPaint::kStroke_Style );
        canvas->drawRect( bounds, paint );
        SkScalar scale = max - min;
        SkScalar yPos = bounds.fTop + ( value - min ) * bounds.height( ) / scale;
        paint.setColor( 0xFFFF0000 );
        canvas->drawLine( bounds.fLeft - 5, yPos, bounds.fRight + 5, yPos, paint );
        SkString label;
        label.printf( "%0.3g", value );
        paint.setColor( 0xFF000000 );
        paint.setStyle( SkPaint::kFill_Style );
        SkFont font( nullptr, 11.0f );
        canvas->drawString( label, bounds.fLeft + 5, yPos - 5, font, paint );
        font.setSize( 13.0f );
        canvas->drawString( name, bounds.fLeft, bounds.bottom( ) + 11, font, paint );
    }

    void setForGeometry( )
    {
        fDrawRibs = true;
        fDrawTangents = true;
        fDrawTDivs = false;
        fWidthScale = 1;
    }

    void setForText( )
    {
        fDrawRibs = fDrawTangents = fDrawTDivs = false;
        fWidthScale = 0.002f;
    }

    void setForSingles( )
    {
        setForGeometry( );
        fDrawTDivs = true;
    }

    void setAsNeeded( )
    {
        if ( fConicButton.fEnabled || fCubicButton.fEnabled || fQuadButton.fEnabled )
        {
            setForSingles( );
        }
        else if ( fRRectButton.fEnabled || fCircleButton.fEnabled || fArcButton.fEnabled )
        {
            setForGeometry( );
        }
        else
        {
            setForText( );
        }
    }

    bool arcCenter( SkPoint* center )
    {
        SkPath path;
        path.moveTo( fPts[10] );
        path.arcTo( fPts[11], fPts[12], fRadius );
        SkPath::Iter iter( path, false );
        SkPoint pts[4];
        iter.next( pts );
        if ( SkPath::kLine_Verb == iter.next( pts ) )
        {
            iter.next( pts );
        }
        SkVector before = pts[0] - pts[1];
        SkVector after = pts[1] - pts[2];
        before.setLength( fRadius );
        after.setLength( fRadius );
        SkVector beforeCCW, afterCCW;
        SkPointPriv::RotateCCW( before, &beforeCCW );
        SkPointPriv::RotateCCW( after, &afterCCW );
        beforeCCW += pts[0];
        afterCCW += pts[2];
        *center = beforeCCW;
        if ( SkScalarNearlyEqual( beforeCCW.fX, afterCCW.fX )
            && SkScalarNearlyEqual( beforeCCW.fY, afterCCW.fY ) )
        {
            return true;
        }
        SkVector beforeCW, afterCW;
        SkPointPriv::RotateCW( before, &beforeCW );
        SkPointPriv::RotateCW( after, &afterCW );
        beforeCW += pts[0];
        afterCW += pts[2];
        *center = beforeCW;
        return SkScalarNearlyEqual( beforeCW.fX, afterCW.fX )
            && SkScalarNearlyEqual( beforeCCW.fY, afterCW.fY );
    }

    void onDrawContent( SkCanvas* canvas ) override
    {
        SkPath path;
        SkScalar width = fWidth;

        if ( fCubicButton.fEnabled )
        {
            path.moveTo( fPts[0] );
            path.cubicTo( fPts[1], fPts[2], fPts[3] );
            setForSingles( );
            draw_stroke( canvas, path, width, 950, false );
        }

        if ( fConicButton.fEnabled )
        {
            path.reset( );
            path.moveTo( fPts[4] );
            path.conicTo( fPts[5], fPts[6], fWeight );
            setForSingles( );
            draw_stroke( canvas, path, width, 950, false );
        }

        if ( fQuadButton.fEnabled )
        {
            path.reset( );
            path.moveTo( fPts[7] );
            path.quadTo( fPts[8], fPts[9] );
            setForSingles( );
            draw_stroke( canvas, path, width, 950, false );
        }

        if ( fArcButton.fEnabled )
        {
            path.reset( );
            path.moveTo( fPts[10] );
            path.arcTo( fPts[11], fPts[12], fRadius );
            setForGeometry( );
            draw_stroke( canvas, path, width, 950, false );
            SkPath pathPts;
            pathPts.moveTo( fPts[10] );
            pathPts.lineTo( fPts[11] );
            pathPts.lineTo( fPts[12] );
            draw_points( canvas, pathPts, SK_ColorDKGRAY, true );
        }

        if ( fRRectButton.fEnabled )
        {
            SkScalar rad = 32;
            SkRect r;
            r.setBounds( &fPts[13], 2 );
            path.reset( );
            SkRRect rr;
            rr.setRectXY( r, rad, rad );
            path.addRRect( rr );
            setForGeometry( );
            draw_stroke( canvas, path, width, 950, false );

            path.reset( );
            SkRRect rr2;
            rr.inset( width / 2, width / 2, &rr2 );
            path.addRRect( rr2, SkPathDirection::kCCW );
            rr.inset( -width / 2, -width / 2, &rr2 );
            path.addRRect( rr2, SkPathDirection::kCW );
            SkPaint paint;
            paint.setAntiAlias( true );
            paint.setColor( 0x40FF8844 );
            canvas->drawPath( path, paint );
        }

        if ( fCircleButton.fEnabled )
        {
            path.reset( );
            SkRect r;
            r.setBounds( &fPts[15], 2 );
            path.addOval( r );
            setForGeometry( );
            if ( fCircleButton.fFill )
            {
                if ( fArcButton.fEnabled )
                {
                    SkPoint center;
                    if ( arcCenter( &center ) )
                    {
                        r.setLTRB( center.fX - fRadius, center.fY - fRadius,
                            center.fX + fRadius, center.fY + fRadius );
                    }
                }
                draw_fill( canvas, r, width );
            }
            else
            {
                draw_stroke( canvas, path, width, 950, false );
            }
        }

        if ( fTextButton.fEnabled )
        {
            path.reset( );
            SkFont font;
            font.setSize( fTextSize );
            SkTextUtils::GetPath( fText.c_str( ), fText.size( ), SkTextEncoding::kUTF8,
                0, fTextSize, font, &path );
            setForText( );
            draw_stroke( canvas, path, width * fWidthScale / fTextSize, fTextSize, true );
        }

        if ( fAnimate )
        {
            fWidth += fDWidth;
            if ( fDWidth > 0 && fWidth > kWidthMax )
            {
                fDWidth = -fDWidth;
            }
            else if ( fDWidth < 0 && fWidth < kWidthMin )
            {
                fDWidth = -fDWidth;
            }
        }
        setAsNeeded( );
        if ( fConicButton.fEnabled )
        {
            draw_control( canvas, fWeightControl, fWeight, 0, 5, "weight" );
        }
        if ( fArcButton.fEnabled )
        {
            draw_control( canvas, fRadiusControl, fRadius, 0, 500, "radius" );
        }
#ifdef SK_DEBUG
        draw_control( canvas, fErrorControl, gDebugStrokerError, kStrokerErrorMin, kStrokerErrorMax,
            "error" );
#endif
        draw_control( canvas, fWidthControl, fWidth * fWidthScale, kWidthMin * fWidthScale,
            kWidthMax * fWidthScale, "width" );
        draw_button( canvas, fQuadButton );
        draw_button( canvas, fCubicButton );
        draw_button( canvas, fConicButton );
        draw_button( canvas, fArcButton );
        draw_button( canvas, fRRectButton );
        draw_button( canvas, fCircleButton );
        draw_button( canvas, fTextButton );
    }

    class MyClick : public Click
    {
    public:
        int fIndex;
        MyClick( int index ) : fIndex( index ) {}
    };

    Sample::Click* onFindClickHandler( SkScalar x, SkScalar y, skui::ModifierKey modi ) override
    {
        for ( size_t i = 0; i < SK_ARRAY_COUNT( fPts ); ++i )
        {
            if ( hittest( fPts[i], x, y ) )
            {
                return new MyClick( (int)i );
            }
        }
        const SkRect& rectPt = SkRect::MakeXYWH( x, y, 1, 1 );
        if ( fWeightControl.contains( rectPt ) )
        {
            return new MyClick( (int)SK_ARRAY_COUNT( fPts ) + 1 );
        }
        if ( fRadiusControl.contains( rectPt ) )
        {
            return new MyClick( (int)SK_ARRAY_COUNT( fPts ) + 2 );
        }
#ifdef SK_DEBUG
        if ( fErrorControl.contains( rectPt ) )
        {
            return new MyClick( (int)SK_ARRAY_COUNT( fPts ) + 3 );
        }
#endif
        if ( fWidthControl.contains( rectPt ) )
        {
            return new MyClick( (int)SK_ARRAY_COUNT( fPts ) + 4 );
        }
        if ( fCubicButton.fBounds.contains( rectPt ) )
        {
            fCubicButton.fEnabled ^= true;
            return new MyClick( (int)SK_ARRAY_COUNT( fPts ) + 5 );
        }
        if ( fConicButton.fBounds.contains( rectPt ) )
        {
            fConicButton.fEnabled ^= true;
            return new MyClick( (int)SK_ARRAY_COUNT( fPts ) + 6 );
        }
        if ( fQuadButton.fBounds.contains( rectPt ) )
        {
            fQuadButton.fEnabled ^= true;
            return new MyClick( (int)SK_ARRAY_COUNT( fPts ) + 7 );
        }
        if ( fArcButton.fBounds.contains( rectPt ) )
        {
            fArcButton.fEnabled ^= true;
            return new MyClick( (int)SK_ARRAY_COUNT( fPts ) + 8 );
        }
        if ( fRRectButton.fBounds.contains( rectPt ) )
        {
            fRRectButton.fEnabled ^= true;
            return new MyClick( (int)SK_ARRAY_COUNT( fPts ) + 9 );
        }
        if ( fCircleButton.fBounds.contains( rectPt ) )
        {
            bool wasEnabled = fCircleButton.fEnabled;
            fCircleButton.fEnabled = !fCircleButton.fFill;
            fCircleButton.fFill = wasEnabled && !fCircleButton.fFill;
            return new MyClick( (int)SK_ARRAY_COUNT( fPts ) + 10 );
        }
        if ( fTextButton.fBounds.contains( rectPt ) )
        {
            fTextButton.fEnabled ^= true;
            return new MyClick( (int)SK_ARRAY_COUNT( fPts ) + 11 );
        }
        return nullptr;
    }

    static SkScalar MapScreenYtoValue( SkScalar y, const SkRect& control, SkScalar min,
        SkScalar max )
    {
        return ( y - control.fTop ) / control.height( ) * ( max - min ) + min;
    }

    bool onClick( Click* click ) override
    {
        int index = ( (MyClick*)click )->fIndex;
        if ( index < (int)SK_ARRAY_COUNT( fPts ) )
        {
            fPts[index].offset( click->fCurr.fX - click->fPrev.fX,
                click->fCurr.fY - click->fPrev.fY );
        }
        else if ( index == (int)SK_ARRAY_COUNT( fPts ) + 1 )
        {
            fWeight = MapScreenYtoValue( click->fCurr.fY, fWeightControl, 0, 5 );
        }
        else if ( index == (int)SK_ARRAY_COUNT( fPts ) + 2 )
        {
            fRadius = MapScreenYtoValue( click->fCurr.fY, fRadiusControl, 0, 500 );
        }
#ifdef SK_DEBUG
        else if ( index == (int)SK_ARRAY_COUNT( fPts ) + 3 )
        {
            gDebugStrokerError = std::max( FLT_EPSILON, MapScreenYtoValue( click->fCurr.fY,
                fErrorControl, kStrokerErrorMin, kStrokerErrorMax ) );
            gDebugStrokerErrorSet = true;
        }
#endif
        else if ( index == (int)SK_ARRAY_COUNT( fPts ) + 4 )
        {
            fWidth = std::max( FLT_EPSILON, MapScreenYtoValue( click->fCurr.fY, fWidthControl,
                kWidthMin, kWidthMax ) );
            fAnimate = fWidth <= kWidthMin;
        }
        return true;
    }

private:
    using INHERITED = Sample;
};


int main()
{
    int result = SampleApplication<QuadStrokerView>::Run( );
    return result;
}

