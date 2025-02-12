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

#include "pch.h"
#include "yolo9.h"

#ifdef USE_COMPUTE_ENGINE
void D2DWindowSizeDependentResources::CreateWindowSizeDependentResources( )
{

}


void D2DResources::CreateDeviceDependentResources( )
{
    const auto& d2dDeviceContext = deviceResources_->D2DDeviceContext( );
    const auto& directWriteFactory = deviceResources_->DirectWriteFactory( );
    headingTextFormat_ = directWriteFactory.CreateTextFormat( L"Segoe UI Variable", 11 );
    headingBrush_ = d2dDeviceContext.CreateSolidColorBrush( D2D1_COLOR_F{ 0.f,0.f,0.f,1.f } );
    constexpr size_t colorCount = sizeof( YoloConstants::colors ) / sizeof( int );
    for ( size_t i = 0; i < colorCount; i++ )
    {
        auto col = YoloConstants::colors[ i ];
        frameBrushes_.emplace_back( d2dDeviceContext.CreateSolidColorBrush( D2D1_COLOR_F{ ( col >> 16 ) / 255.0f, ( ( col >> 8 ) & 0xff ) / 255.0f, ( col & 0xff ) / 255.0f, 1.0f } ) );
    }

}
void D2DResources::CreateWindowSizeDependentResources( )
{
    windowSizeDependentResources_ = std::make_unique<D2DWindowSizeDependentResources>( deviceResources_ );
    windowSizeDependentResources_->CreateWindowSizeDependentResources( );
}
#endif