#include <HWSkiaSample.h>
#include "skia/core/SkCanvas.h"
#include "skia/core/SkFont.h"
#include "skia/core/SkFontMetrics.h"
#include "skia/core/SkPath.h"

#include "skia/scenegraph/SkSceneGraph.h"

using namespace Harlinn::Windows::Skia;
using namespace Harlinn::Common::Core;


class RadarView : public Sample
{
public:
    using Base = Sample;
private:
    Reference<SceneGraph::Scene> scene_;
    Reference<SceneGraph::Group> rectGroup_;
    Reference<SceneGraph::Rectangle> rect1_;
    Reference<SceneGraph::Rectangle> rect2_;
    Reference<SceneGraph::Group> circleGroup_;
    Reference<SceneGraph::Circle> circle1_;
    Reference<SceneGraph::Circle> circle2_;
    Reference<SceneGraph::Image> image1_;
    Reference<SceneGraph::Radar> radar1_;
public:
    RadarView()
    { 
        scene_ = SceneGraph::Scene::Make( );
        rectGroup_ = scene_->AddGroup( 300, 300 );

        circleGroup_ = scene_->AddGroup( 600, 600 );

        auto redStrokeStyle = SceneGraph::ColorStyle::Make( SK_ColorRED );
        redStrokeStyle->SetAntiAlias( true );
        redStrokeStyle->SetPaintStyle( SkPaint::Style::kStroke_Style );
        redStrokeStyle->SetStrokeWidth( 4 );

        auto greenStrokeStyle = SceneGraph::ColorStyle::Make( SK_ColorGREEN );
        greenStrokeStyle->SetAntiAlias( true );
        greenStrokeStyle->SetPaintStyle( SkPaint::Style::kStroke_Style );
        greenStrokeStyle->SetStrokeWidth( 4 );

        auto blackStrokeStyle = SceneGraph::ColorStyle::Make( SK_ColorBLACK );
        blackStrokeStyle->SetAntiAlias( true );
        blackStrokeStyle->SetPaintStyle( SkPaint::Style::kStroke_Style );
        blackStrokeStyle->SetStrokeWidth( 4 );


        auto yellowFillStyle = SceneGraph::ColorStyle::Make( SK_ColorYELLOW );
        yellowFillStyle->SetAntiAlias( true );

        auto cyanFillStyle = SceneGraph::ColorStyle::Make( SK_ColorCYAN );
        cyanFillStyle->SetAntiAlias( true );


        rect1_ = rectGroup_->AddRectangle( SkRect::MakeXYWH( 150, 50, 400, 200 ), redStrokeStyle );
        rect2_ = rectGroup_->AddRectangle( SkRect::MakeXYWH( 250, 150, 200, 400 ), yellowFillStyle );

        circle1_ = circleGroup_->AddCircle( -200, -200, 250, greenStrokeStyle );
        circle1_ = circleGroup_->AddCircle( 200, -200, 250, cyanFillStyle );
        image1_ = circleGroup_->AddImage( 100, 300, "images/dog.jpg" );

        radar1_ = scene_->Add<SceneGraph::Radar>(500,500, blackStrokeStyle, 250.0f );


    }
    SkString name( ) override { return SkString( "Radar view" ); }

    void onDrawContent( SkCanvas* canvas ) override
    {
        scene_->Render( canvas );
    }


    virtual bool onChar( SkUnichar value ) 
    { 
        bool handled = true;

        switch ( value )
        {
            case '1':
            {
                rectGroup_->MoveTo( 100,100 );
                
            }
            break;
            case '2':
            {
                rectGroup_->MoveTo( 200, 200 );
            }
            break;
            case '3':
            {
                rectGroup_->MoveTo( 400, 400 );
            }
            break;
            case 'a':
            {
                rectGroup_->MoveBy( -10, 0 );
            }
            break;
            case 'd':
            {
                rectGroup_->MoveBy( 10, 0 );
            }
            break;
            case 'w':
            {
                rectGroup_->MoveBy( 0, -10 );
            }
            break;
            case 'x':
            {
                rectGroup_->MoveBy( 0, 10 );
            }
            break;

            default:
                handled = false;
        }

        return handled;
    }

    
    Click* onFindClickHandler( SkScalar x, SkScalar y, skui::ModifierKey modi ) override
    {
        auto node = scene_->NodeAt( { x, y } );
        if ( node )
        {
            Click* click = new Click( );
            click->fMeta.setPtr( "node", (void*)node );
            return click;
        }
        return nullptr;
    }

    bool onClick( Click* click ) override
    {
        SceneGraph::Node* node = nullptr;
        if ( click->fMeta.findPtr( "node", (void**)&node ) )
        {
            SkScalar dx = click->fCurr.fX - click->fPrev.fX;
            SkScalar dy = click->fCurr.fY - click->fPrev.fY;
            auto group = node->Group( );
            if ( group )
            {
                group->MoveBy( dx, dy );
            }
            else
            {
                node->MoveBy( dx, dy );
            }
            return true;
        }
        return false;
    }
    
};



int main( )
{
    int result = SampleApplication<RadarView>::Run( );
    return result;
}




