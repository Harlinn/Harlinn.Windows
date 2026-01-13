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


#include <HWSkiaSample.h>
#include "skia/core/SkCanvas.h"
#include "skia/core/SkFont.h"
#include "skia/core/SkFontMetrics.h"
#include "skia/core/SkPath.h"

#include "skia/sg/SkSGDraw.h"
#include "skia/sg/SkSGGroup.h"
#include "skia/sg/SkSGPaint.h"
#include "skia/sg/SkSGRect.h"
#include "skia/sg/SkSGScene.h"

using namespace Harlinn::Windows::Skia;

struct PerNodeInfo
{
    // key
    sksg::Draw* fDraw;

    // value(s)
    sksg::GeometryNode* fGeo;
    sksg::PaintNode* fPaint;
};

class SampleSG : public Sample
{
    SkTDArray<PerNodeInfo> fSideCar;
    sk_sp<sksg::Group> fGroup;
    std::unique_ptr<sksg::Scene> fScene;

    PerNodeInfo* findInfo( sksg::Draw* key )
    {
        for ( int i = 0; i < fSideCar.count( ); ++i )
        {
            if ( fSideCar[i].fDraw == key )
            {
                return &fSideCar[i];
            }
        }
        return nullptr;
    }

    void appendNode( sk_sp<sksg::Draw> d, sk_sp<sksg::GeometryNode> g, sk_sp<sksg::PaintNode> p )
    {
        fGroup->addChild( d );
        auto sc = fSideCar.append( );
        sc->fDraw = d.get( );
        sc->fGeo = g.get( );
        sc->fPaint = p.get( );
    }

public:
    SampleSG( )
    {
        fGroup = sksg::Group::Make( );

        fScene = sksg::Scene::Make( fGroup );

        auto r = sksg::Rect::Make( { 20, 20, 400, 300 } );
        auto p = sksg::Color::Make( SK_ColorRED );
        auto d = sksg::Draw::Make( r, p );
        this->appendNode( d, r, p );

        r = sksg::Rect::Make( { 60, 70, 300, 400 } );
        p = sksg::Color::Make( SK_ColorBLUE );
        d = sksg::Draw::Make( r, p );
        this->appendNode( d, r, p );
    }

protected:
    SkString name( ) override { return SkString( "SceneGraph" ); }

    void onDrawContent( SkCanvas* canvas ) override
    {
        fScene->render( canvas );
    }

    Click* onFindClickHandler( SkScalar x, SkScalar y, skui::ModifierKey modi ) override
    {
        if ( auto node = fScene->nodeAt( { x, y } ) )
        {
            Click* click = new Click( );
            click->fMeta.setPtr( "node", (void*)node );
            return click;
        }
        return nullptr;
    }

    bool onClick( Click* click ) override
    {
        sksg::Draw* node = nullptr;
        if ( click->fMeta.findPtr( "node", (void**)&node ) )
        {
            if ( auto info = this->findInfo( node ) )
            {
                auto geo = info->fGeo;
                sksg::Rect* r = (sksg::Rect*)geo;
                SkScalar dx = click->fCurr.fX - click->fPrev.fX;
                SkScalar dy = click->fCurr.fY - click->fPrev.fY;
                r->setL( r->getL( ) + dx );
                r->setR( r->getR( ) + dx );
                r->setT( r->getT( ) + dy );
                r->setB( r->getB( ) + dy );
            }
            return true;
        }
        return false;
    }

private:

    using INHERITED = Sample;
};


int main()
{
    int result = SampleApplication<SampleSG>::Run( );
    return result;
}

