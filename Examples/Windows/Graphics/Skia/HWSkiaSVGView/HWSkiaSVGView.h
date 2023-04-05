#pragma once
#ifndef HARLINN_HWSKIASVGVIEW_H_
#define HARLINN_HWSKIASVGVIEW_H_

#include <HWForm.h>
#include <HWSkia.h>
#include <HCCIO.h>

#include "skia/core/SkMatrix.h"
#include "skia/core/SkStream.h"
#include "skia/core/SkSurface.h"
#include "skia/resources/SkResources.h"
#include "skia/svg/SkSVGNode.h"
#include "skia/svg/SkSVGDOM.h"

using namespace Harlinn::Common::Core;
using namespace Harlinn::Windows;

class SkiaSVGView : public SkiaControl
{
public:
    using Base = Harlinn::Windows::SkiaControl;
private:
    sk_sp<SkSVGDOM> svg_dom_;
public:
    SkiaSVGView( )
        : Base( )
    {
    }

    void LoadFromFile( const std::wstring& wideFilename )
    {
        auto filename = ToAnsiString( wideFilename );
        auto direcory = IO::Path::GetParentDirectory( filename );
        auto resourceProvider = skresources::DataURIResourceProviderProxy::Make( skresources::FileResourceProvider::Make( SkString( direcory ), true ), true );
        SkFILEStream in( filename.c_str( ) );
        svg_dom_ = SkSVGDOM::Builder( )
            .setFontManager( SkFontMgr::RefDefault( ) )
            .setResourceProvider( std::move( resourceProvider ) )
            .make( in );
    }
protected:
    void DoOnRender( SkCanvas* canvas ) override
    {
        Base::DoOnRender( canvas );
        canvas->clear( SK_ColorWHITE );
        if ( svg_dom_ )
        {
            svg_dom_->render( canvas );
        }
    }
};




#endif
