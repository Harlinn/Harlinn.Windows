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

    void LoadFromFile( const WideString& wideFilename )
    {
        auto filename = ToAnsiString( wideFilename );
        auto direcory = IO::Path::GetParentDirectory( filename );
        auto resourceProvider = skresources::DataURIResourceProviderProxy::Make( skresources::FileResourceProvider::Make( SkString( direcory.c_str(), direcory.size() ), true ), true );
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
