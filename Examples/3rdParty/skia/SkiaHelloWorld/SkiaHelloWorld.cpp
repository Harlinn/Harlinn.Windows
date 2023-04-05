
/*
* Copyright 2017 Google Inc.
*
* Use of this source code is governed by a BSD-style license that can be
* found in the LICENSE file.
*/
#include <Windows.h>
#include "SkiaHelloWorld.h"

#include "skia/core/SkCanvas.h"
#include "skia/core/SkFont.h"
#include "skia/core/SkGraphics.h"
#include "skia/core/SkSurface.h"
#include "skia/effects/SkGradientShader.h"

using namespace sk_app;

HelloWorld::HelloWorld( int argc, char** argv, void* platformData )
    : fBackendType( Window::kDirect3D_BackendType /*kDirect3D_BackendType*/ )//fBackendType( Window::kNativeGL_BackendType )
    , fRotationAngle( 0 )
{
    SkGraphics::Init( );

    fWindow = Window::CreateNativeWindow( platformData );
    fWindow->setRequestedDisplayParams( DisplayParams( ) );

    // register callbacks
    fWindow->pushLayer( this );

    fWindow->attach( fBackendType );
}

HelloWorld::~HelloWorld( )
{
    fWindow->detach( );
    delete fWindow;
}

void HelloWorld::updateTitle( )
{
    if ( !fWindow || fWindow->sampleCount( ) <= 1 )
    {
        return;
    }

    SkString title( "Hello World " );
    switch ( fBackendType )
    {
        case Window::kRaster_BackendType:
            title.append( "Raster" );
            break;

        case Window::kNativeGL_BackendType:
            title.append( "OpenGL" );
            break;
        
        case Window::kVulkan_BackendType:
            title.append( "Vulkan" );
            break;
        
        case Window::kDirect3D_BackendType:
            title.append( "Direct3D" );
            break;
    }
    
    fWindow->setTitle( title.c_str( ) );
}

void HelloWorld::onBackendCreated( )
{
    this->updateTitle( );
    fWindow->show( );
    fWindow->inval( );
}

void HelloWorld::onPaint( SkSurface* surface )
{
    auto canvas = surface->getCanvas( );

    // Clear background
    canvas->clear( SK_ColorWHITE );

    SkPaint paint;
    paint.setColor( SK_ColorRED );

    // Draw a rectangle with red paint
    SkRect rect = SkRect::MakeXYWH( 10, 10, 128, 128 );
    canvas->drawRect( rect, paint );

    // Set up a linear gradient and draw a circle
    {
        SkPoint linearPoints[] = { { 0, 0 }, { 300, 300 } };
        SkColor linearColors[] = { SK_ColorGREEN, SK_ColorBLACK };
        paint.setShader( SkGradientShader::MakeLinear( linearPoints, linearColors, nullptr, 2,
            SkTileMode::kMirror ) );
        paint.setAntiAlias( true );

        canvas->drawCircle( 200, 200, 64, paint );

        // Detach shader
        paint.setShader( nullptr );
    }

    // Draw a message with a nice black paint
    SkFont font;
    font.setSubpixel( true );
    font.setSize( 20 );
    paint.setColor( SK_ColorBLACK );

    canvas->save( );
    static const char message[] = "Hello World";

    // Translate and rotate
    canvas->translate( 300, 300 );
    fRotationAngle += 0.2f;
    if ( fRotationAngle > 360 )
    {
        fRotationAngle -= 360;
    }
    canvas->rotate( fRotationAngle );

    // Draw the text
    canvas->drawSimpleText( message, strlen( message ), SkTextEncoding::kUTF8, 0, 0, font, paint );

    canvas->restore( );
}

void HelloWorld::onIdle( )
{
    // Just re-paint continously
    fWindow->inval( );
}

bool HelloWorld::onChar( SkUnichar c, skui::ModifierKey modifiers )
{
    if ( ' ' == c )
    {
        if ( fBackendType == Window::kRaster_BackendType )
        {
            fBackendType = Window::kNativeGL_BackendType;
        }
        else if ( fBackendType == Window::kNativeGL_BackendType )
        {
            fBackendType = Window::kVulkan_BackendType;
        }
        else if ( fBackendType == Window::kVulkan_BackendType )
        {
            fBackendType = Window::kDirect3D_BackendType;
        }
        else
        {
            fBackendType = Window::kRaster_BackendType;
        }

        fWindow->detach( );
        fWindow->attach( fBackendType );
        updateTitle( );
    }
    return true;
}


int main( int argc, char** argv )
{
    HelloWorldApplicationFactory applicationFactory;
    auto result = Application::Run( applicationFactory, argc, argv );
    return result;
}
