// EWGDI01Demo.cpp : Defines the entry point for the application.
//

#include "EWGDI01Demo.h"

#include "HWApplication.h"
#include "HWForm.h"
#include "HWMenu.h"
#include "HWStdctrls.h"
#include "HWEnvironment.h"
#include "HWFiledialog.h"
#include <iostream>

using namespace Harlinn::Windows;
using namespace Harlinn;

enum class DeviceContextExampleType
{
    DrawBitmap,
    DrawCaption,
    DrawCaptionFrameControlCloseButton,
    DrawCaptionFrameControlMinimizeButton,
    DrawCaptionFrameControlMaximizeButton,
    DrawCaptionFrameControlRestoreButton,
    DrawCaptionFrameControlHelpButton,
    DrawMenuBarFrameControlArrow,
    DrawMenuBarFrameControlCheck,
    DrawMenuBarFrameControlBullet,
    DrawMenuBarFrameControlArrowRight,
    DrawScrollBarFrameControlUp,
    DrawScrollBarFrameControlDown,
    DrawScrollBarFrameControlLeft,
    DrawScrollBarFrameControlRight,
    DrawScrollBarFrameControlComboBox,
    DrawScrollBarFrameControlSizeGrip,
    DrawScrollBarFrameControlSizeGripRight,
    DrawButtonFrameControlCheckBox,
    DrawButtonFrameControlRadioImage,
    DrawButtonFrameControlRadioMask,
    DrawButtonFrameControlRadioButton,
    DrawButtonFrameControlThreeState,
    DrawButtonFrameControlPushButton,
    DrawEdgeRaisedOuter,
    DrawEdgeSunkenOuter,
    DrawEdgeRaisedInner,
    DrawEdgeSunkenInner,
    DrawEdgeRaised,
    DrawEdgeSunken,
    DrawEdgeEtched,
    DrawEdgeBump,
    DrawFocusRect,
    DrawStateNormal,
    DrawStatePrefix,
    DrawStateDithered,
    DrawStateDisabled,
    DrawStateMono,
    DrawStateHidePrefix,
    DrawStatePrefixOnly,
    DrawStateRight,
    DrawDesktopWallPaper,
    DrawChord,
    DrawScreenWidthAndHeight
};

class DeviceContextExampleForm : public Form
{
    DeviceContextExampleType type;
    BitmapHandle bitMap;
public:
    typedef Form Base;
    DeviceContextExampleForm( );
protected:
    virtual void DoOnInitialize( );
    virtual void DoOnPaint( Message& message );

private:
    void InitializeMenuBar( );
    void OpenImageFile( );

    void DrawBitmap( const DeviceContextHandle& dc, RECT& rect );
    void DrawCaption( const DeviceContextHandle& dc, RECT& rect );
    void DrawCaptionFrameControlCloseButton( const DeviceContextHandle& dc, RECT& rect );
    void DrawCaptionFrameControlMinimizeButton( const DeviceContextHandle& dc, RECT& rect );
    void DrawCaptionFrameControlMaximizeButton( const DeviceContextHandle& dc, RECT& rect );
    void DrawCaptionFrameControlRestoreButton( const DeviceContextHandle& dc, RECT& rect );
    void DrawCaptionFrameControlHelpButton( const DeviceContextHandle& dc, RECT& rect );
    void DrawMenuBarFrameControlArrow( const DeviceContextHandle& dc, RECT& rect );
    void DrawMenuBarFrameControlCheck( const DeviceContextHandle& dc, RECT& rect );
    void DrawMenuBarFrameControlBullet( const DeviceContextHandle& dc, RECT& rect );
    void DrawMenuBarFrameControlArrowRight( const DeviceContextHandle& dc, RECT& rect );
    void DrawScrollBarFrameControlUp( const DeviceContextHandle& dc, RECT& rect );
    void DrawScrollBarFrameControlDown( const DeviceContextHandle& dc, RECT& rect );
    void DrawScrollBarFrameControlLeft( const DeviceContextHandle& dc, RECT& rect );
    void DrawScrollBarFrameControlRight( const DeviceContextHandle& dc, RECT& rect );
    void DrawScrollBarFrameControlComboBox( const DeviceContextHandle& dc, RECT& rect );
    void DrawScrollBarFrameControlSizeGrip( const DeviceContextHandle& dc, RECT& rect );
    void DrawScrollBarFrameControlSizeGripRight( const DeviceContextHandle& dc, RECT& rect );
    void DrawButtonFrameControlCheckBox( const DeviceContextHandle& dc, RECT& rect );
    void DrawButtonFrameControlRadioImage( const DeviceContextHandle& dc, RECT& rect );
    void DrawButtonFrameControlRadioMask( const DeviceContextHandle& dc, RECT& rect );
    void DrawButtonFrameControlRadioButton( const DeviceContextHandle& dc, RECT& rect );
    void DrawButtonFrameControlThreeState( const DeviceContextHandle& dc, RECT& rect );
    void DrawButtonFrameControlPushButton( const DeviceContextHandle& dc, RECT& rect );
    void DrawEdgeRaisedOuter( const DeviceContextHandle& dc, RECT& rect );
    void DrawEdgeSunkenOuter( const DeviceContextHandle& dc, RECT& rect );
    void DrawEdgeRaisedInner( const DeviceContextHandle& dc, RECT& rect );
    void DrawEdgeSunkenInner( const DeviceContextHandle& dc, RECT& rect );
    void DrawEdgeRaised( const DeviceContextHandle& dc, RECT& rect );
    void DrawEdgeSunken( const DeviceContextHandle& dc, RECT& rect );
    void DrawEdgeEtched( const DeviceContextHandle& dc, RECT& rect );
    void DrawEdgeBump( const DeviceContextHandle& dc, RECT& rect );
    void DrawFocusRect( const DeviceContextHandle& dc, RECT& rect );
    void DrawStateNormal( const DeviceContextHandle& dc, RECT& rect );
    void DrawStatePrefix( const DeviceContextHandle& dc, RECT& rect );
    void DrawStateDithered( const DeviceContextHandle& dc, RECT& rect );
    void DrawStateDisabled( const DeviceContextHandle& dc, RECT& rect );
    void DrawStateMono( const DeviceContextHandle& dc, RECT& rect );
    void DrawStateHidePrefix( const DeviceContextHandle& dc, RECT& rect );
    void DrawStatePrefixOnly( const DeviceContextHandle& dc, RECT& rect );
    void DrawStateRight( const DeviceContextHandle& dc, RECT& rect );
    void DrawDesktopWallPaper( const DeviceContextHandle& dc, RECT& rect );
    void DrawChord( const DeviceContextHandle& dc, RECT& rect );
    void DrawScreenWidthAndHeight( const DeviceContextHandle& dc, RECT& rect );


};


DeviceContextExampleForm::DeviceContextExampleForm( )
    : Base( ), type( DeviceContextExampleType::DrawCaptionFrameControlCloseButton )
{
    SetText( L"DeviceContext example" );
}

void DeviceContextExampleForm::DoOnInitialize( )
{
    Base::DoOnInitialize( );

    InitializeMenuBar( );
}

void DeviceContextExampleForm::InitializeMenuBar( )
{
#define ADD_ITEM( choice, submenu, text ) \
    auto choice##_ = submenu->AddMenuItem(text, [&](MenuItem* sender){ type = DeviceContextExampleType::choice; InvalidateRect(); })

    auto menuBar = std::make_unique<MenuBar>( );

    auto fileSubMenu1 = menuBar->AddSubMenu( L"&File" );
    fileSubMenu1->AddMenuItem( L"Open", [&]( MenuItem* sender )
    {
        OpenImageFile( );
        type = DeviceContextExampleType::DrawBitmap;
        InvalidateRect( );
    } );



    auto subMenu1 = menuBar->AddSubMenu( L"Submenu1" );

    subMenu1->AddMenuItem( L"DrawCaption", [&]( MenuItem* sender ) { type = DeviceContextExampleType::DrawCaption; InvalidateRect( ); } );

    auto drawCaptionFrameControlSubMenu = subMenu1->AddSubMenu( L"DrawCaptionFrameControl" );



    drawCaptionFrameControlSubMenu->AddMenuItem( L"CloseButton", [&]( MenuItem* sender ) { type = DeviceContextExampleType::DrawCaptionFrameControlCloseButton; InvalidateRect( ); } );

    drawCaptionFrameControlSubMenu->AddMenuItem( L"MinimizeButton", [&]( MenuItem* sender ) { type = DeviceContextExampleType::DrawCaptionFrameControlMinimizeButton; InvalidateRect( ); } );

    drawCaptionFrameControlSubMenu->AddMenuItem( L"MaximizeButton", [&]( MenuItem* sender ) { type = DeviceContextExampleType::DrawCaptionFrameControlMaximizeButton; InvalidateRect( ); } );

    drawCaptionFrameControlSubMenu->AddMenuItem( L"RestoreButton", [&]( MenuItem* sender ) { type = DeviceContextExampleType::DrawCaptionFrameControlRestoreButton; InvalidateRect( ); } );

    drawCaptionFrameControlSubMenu->AddMenuItem( L"HelpButton", [&]( MenuItem* sender ) { type = DeviceContextExampleType::DrawCaptionFrameControlHelpButton; InvalidateRect( ); } );

    auto drawMenuBarFrameControlSubMenu = subMenu1->AddSubMenu( L"DrawMenuBarFrameControl" );


    drawMenuBarFrameControlSubMenu->AddMenuItem( L"Arrow", [&]( MenuItem* sender ) { type = DeviceContextExampleType::DrawMenuBarFrameControlArrow; InvalidateRect( ); } );

    drawMenuBarFrameControlSubMenu->AddMenuItem( L"Check", [&]( MenuItem* sender ) { type = DeviceContextExampleType::DrawMenuBarFrameControlCheck; InvalidateRect( ); } );

    drawMenuBarFrameControlSubMenu->AddMenuItem( L"Bullet", [&]( MenuItem* sender ) { type = DeviceContextExampleType::DrawMenuBarFrameControlBullet; InvalidateRect( ); } );

    drawMenuBarFrameControlSubMenu->AddMenuItem( L"ArrowRight", [&]( MenuItem* sender ) { type = DeviceContextExampleType::DrawMenuBarFrameControlArrowRight; InvalidateRect( ); } );


    auto drawScrollBarFrameControlSubMenu = subMenu1->AddSubMenu( L"DrawScrollBarFrameControl" );


    ADD_ITEM( DrawScrollBarFrameControlUp, drawScrollBarFrameControlSubMenu, L"Up" );
    ADD_ITEM( DrawScrollBarFrameControlDown, drawScrollBarFrameControlSubMenu, L"Down" );
    ADD_ITEM( DrawScrollBarFrameControlLeft, drawScrollBarFrameControlSubMenu, L"Left" );
    ADD_ITEM( DrawScrollBarFrameControlRight, drawScrollBarFrameControlSubMenu, L"Right" );
    ADD_ITEM( DrawScrollBarFrameControlComboBox, drawScrollBarFrameControlSubMenu, L"ComboBox" );
    ADD_ITEM( DrawScrollBarFrameControlSizeGrip, drawScrollBarFrameControlSubMenu, L"SizeGrip" );
    ADD_ITEM( DrawScrollBarFrameControlSizeGripRight, drawScrollBarFrameControlSubMenu, L"SizeGripRight" );

    auto drawButtonFrameControlSubMenu = subMenu1->AddSubMenu( L"DrawButtonFrameControl" );

    ADD_ITEM( DrawButtonFrameControlCheckBox, drawButtonFrameControlSubMenu, L"CheckBox" );
    ADD_ITEM( DrawButtonFrameControlRadioImage, drawButtonFrameControlSubMenu, L"RadioImage" );
    ADD_ITEM( DrawButtonFrameControlRadioMask, drawButtonFrameControlSubMenu, L"RadioMask" );
    ADD_ITEM( DrawButtonFrameControlRadioButton, drawButtonFrameControlSubMenu, L"RadioButton" );
    ADD_ITEM( DrawButtonFrameControlThreeState, drawButtonFrameControlSubMenu, L"ThreeState" );
    ADD_ITEM( DrawButtonFrameControlPushButton, drawButtonFrameControlSubMenu, L"PushButton" );

    auto drawEdgeSubMenu = subMenu1->AddSubMenu( L"DrawEdge" );

    ADD_ITEM( DrawEdgeRaisedOuter, drawEdgeSubMenu, L"Raised Outer" );
    ADD_ITEM( DrawEdgeSunkenOuter, drawEdgeSubMenu, L"Sunken Outer" );
    ADD_ITEM( DrawEdgeRaisedInner, drawEdgeSubMenu, L"Raised Inner" );
    ADD_ITEM( DrawEdgeSunkenInner, drawEdgeSubMenu, L"Sunken Inner" );
    ADD_ITEM( DrawEdgeRaised, drawEdgeSubMenu, L"Raised" );
    ADD_ITEM( DrawEdgeSunken, drawEdgeSubMenu, L"Sunken" );
    ADD_ITEM( DrawEdgeEtched, drawEdgeSubMenu, L"Etched" );
    ADD_ITEM( DrawEdgeBump, drawEdgeSubMenu, L"Bump" );

    ADD_ITEM( DrawFocusRect, subMenu1, L"DrawFocusRect" );

    auto drawStateSubMenu = subMenu1->AddSubMenu( L"DrawState" );

    ADD_ITEM( DrawStateNormal, drawStateSubMenu, L"Normal" );
    ADD_ITEM( DrawStatePrefix, drawStateSubMenu, L"Prefix" );
    ADD_ITEM( DrawStateDithered, drawStateSubMenu, L"Dithered" );
    ADD_ITEM( DrawStateDisabled, drawStateSubMenu, L"Disabled" );
    ADD_ITEM( DrawStateMono, drawStateSubMenu, L"Mono" );
    ADD_ITEM( DrawStateHidePrefix, drawStateSubMenu, L"HidePrefix" );
    ADD_ITEM( DrawStatePrefixOnly, drawStateSubMenu, L"PrefixOnly" );
    ADD_ITEM( DrawStateRight, drawStateSubMenu, L"Right" );
    ADD_ITEM( DrawScreenWidthAndHeight, drawStateSubMenu, L"Screen Width And Height" );

    ADD_ITEM( DrawDesktopWallPaper, subMenu1, L"DrawDesktopWallPaper" );

    SetMenu( std::move(menuBar) );
};


void DeviceContextExampleForm::OpenImageFile( )
{
    auto fileOpenDialog = Harlinn::Windows::FileOpenDialog::Create( );
    if ( fileOpenDialog->Show( GetHandle( ) ) )
    {
        auto item = fileOpenDialog->GetResult( );
        auto fileName = item.GetDisplayName( SIGDN_FILESYSPATH );
        bitMap = BitmapHandle::LoadFromFile( fileName );
    }
}



void DeviceContextExampleForm::DoOnPaint( Message& message )
{
    Base::DoOnPaint( message );
    RECT rect = this->GetClientRect( );
    PaintDeviceContextHandle dc( *this );

    BrushHandle controlBrush( SysColor::Control );
    dc.DrawFilledRectangle( rect, controlBrush );

    InflateRect( &rect, -20, -20 );

    switch ( type )
    {
        case DeviceContextExampleType::DrawBitmap:
            DrawBitmap( dc, rect );
            break;
        case DeviceContextExampleType::DrawCaption:
            DrawCaption( dc, rect );
            break;
        case DeviceContextExampleType::DrawCaptionFrameControlCloseButton:
            DrawCaptionFrameControlCloseButton( dc, rect );
            break;
        case DeviceContextExampleType::DrawCaptionFrameControlMinimizeButton:
            DrawCaptionFrameControlMinimizeButton( dc, rect );
            break;
        case DeviceContextExampleType::DrawCaptionFrameControlMaximizeButton:
            DrawCaptionFrameControlMaximizeButton( dc, rect );
            break;
        case DeviceContextExampleType::DrawCaptionFrameControlRestoreButton:
            DrawCaptionFrameControlRestoreButton( dc, rect );
            break;
        case DeviceContextExampleType::DrawCaptionFrameControlHelpButton:
            DrawCaptionFrameControlHelpButton( dc, rect );
            break;
        case DeviceContextExampleType::DrawMenuBarFrameControlArrow:
            DrawMenuBarFrameControlArrow( dc, rect );
            break;
        case DeviceContextExampleType::DrawMenuBarFrameControlCheck:
            DrawMenuBarFrameControlCheck( dc, rect );
            break;
        case DeviceContextExampleType::DrawMenuBarFrameControlBullet:
            DrawMenuBarFrameControlBullet( dc, rect );
            break;
        case DeviceContextExampleType::DrawMenuBarFrameControlArrowRight:
            DrawMenuBarFrameControlArrowRight( dc, rect );
            break;
        case DeviceContextExampleType::DrawScrollBarFrameControlUp:
            DrawScrollBarFrameControlUp( dc, rect );
            break;
        case DeviceContextExampleType::DrawScrollBarFrameControlDown:
            DrawScrollBarFrameControlDown( dc, rect );
            break;
        case DeviceContextExampleType::DrawScrollBarFrameControlLeft:
            DrawScrollBarFrameControlLeft( dc, rect );
            break;
        case DeviceContextExampleType::DrawScrollBarFrameControlRight:
            DrawScrollBarFrameControlRight( dc, rect );
            break;
        case DeviceContextExampleType::DrawScrollBarFrameControlComboBox:
            DrawScrollBarFrameControlComboBox( dc, rect );
            break;
        case DeviceContextExampleType::DrawScrollBarFrameControlSizeGrip:
            DrawScrollBarFrameControlSizeGrip( dc, rect );
            break;
        case DeviceContextExampleType::DrawScrollBarFrameControlSizeGripRight:
            DrawScrollBarFrameControlSizeGripRight( dc, rect );
            break;
        case DeviceContextExampleType::DrawButtonFrameControlCheckBox:
            DrawButtonFrameControlCheckBox( dc, rect );
            break;
        case DeviceContextExampleType::DrawButtonFrameControlRadioImage:
            DrawButtonFrameControlRadioImage( dc, rect );
            break;
        case DeviceContextExampleType::DrawButtonFrameControlRadioMask:
            DrawButtonFrameControlRadioMask( dc, rect );
            break;
        case DeviceContextExampleType::DrawButtonFrameControlRadioButton:
            DrawButtonFrameControlRadioButton( dc, rect );
            break;
        case DeviceContextExampleType::DrawButtonFrameControlThreeState:
            DrawButtonFrameControlThreeState( dc, rect );
            break;
        case DeviceContextExampleType::DrawButtonFrameControlPushButton:
            DrawButtonFrameControlPushButton( dc, rect );
            break;
        case DeviceContextExampleType::DrawEdgeRaisedOuter:
            DrawEdgeRaisedOuter( dc, rect );
            break;
        case DeviceContextExampleType::DrawEdgeSunkenOuter:
            DrawEdgeSunkenOuter( dc, rect );
            break;
        case DeviceContextExampleType::DrawEdgeRaisedInner:
            DrawEdgeRaisedInner( dc, rect );
            break;
        case DeviceContextExampleType::DrawEdgeSunkenInner:
            DrawEdgeSunkenInner( dc, rect );
            break;
        case DeviceContextExampleType::DrawEdgeRaised:
            DrawEdgeRaised( dc, rect );
            break;
        case DeviceContextExampleType::DrawEdgeSunken:
            DrawEdgeSunken( dc, rect );
            break;
        case DeviceContextExampleType::DrawEdgeEtched:
            DrawEdgeEtched( dc, rect );
            break;
        case DeviceContextExampleType::DrawEdgeBump:
            DrawEdgeBump( dc, rect );
            break;
        case DeviceContextExampleType::DrawFocusRect:
            DrawFocusRect( dc, rect );
            break;
        case DeviceContextExampleType::DrawStateNormal:
            DrawStateNormal( dc, rect );
            break;
        case DeviceContextExampleType::DrawStatePrefix:
            DrawStatePrefix( dc, rect );
            break;
        case DeviceContextExampleType::DrawStateDithered:
            DrawStateDithered( dc, rect );
            break;
        case DeviceContextExampleType::DrawStateDisabled:
            DrawStateDisabled( dc, rect );
            break;
        case DeviceContextExampleType::DrawStateMono:
            DrawStateMono( dc, rect );
            break;
        case DeviceContextExampleType::DrawStateHidePrefix:
            DrawStateHidePrefix( dc, rect );
            break;
        case DeviceContextExampleType::DrawStatePrefixOnly:
            DrawStatePrefixOnly( dc, rect );
            break;
        case DeviceContextExampleType::DrawStateRight:
            DrawStateRight( dc, rect );
            break;
        case DeviceContextExampleType::DrawDesktopWallPaper:
            DrawDesktopWallPaper( dc, rect );
            break;
        case DeviceContextExampleType::DrawScreenWidthAndHeight:
            DrawScreenWidthAndHeight( dc, rect );
            break;


    }
}


void DeviceContextExampleForm::DrawBitmap( const DeviceContextHandle& dc, RECT& rect )
{
    if ( bitMap )
    {
        POINT pt = { rect.left,rect.top };
        SIZE sz = { rect.right - rect.left, rect.bottom - rect.top };
        dc.DrawBitmap( bitMap, pt, sz );
    }
}

void DeviceContextExampleForm::DrawCaption( const DeviceContextHandle& dc, RECT& rect )
{
    int height = Windows::Environment::SystemMetrics::CaptionHeight( );
    rect.top = rect.top + ( ( ( rect.bottom - rect.top ) / 2 ) - ( height / 2 ) );
    rect.bottom = rect.top + height;
    dc.DrawCaption( *this, rect, DrawCaptionOptions::Active | DrawCaptionOptions::Text | DrawCaptionOptions::Icon | DrawCaptionOptions::Gradient | DrawCaptionOptions::Buttons );
}

void DeviceContextExampleForm::DrawCaptionFrameControlCloseButton( const DeviceContextHandle& dc, RECT& rect )
{
    dc.DrawCaptionFrameControl( DrawFrameControlCaptionPart::CloseButton, rect, DrawFrameControlOptions::None );
}

void DeviceContextExampleForm::DrawCaptionFrameControlMinimizeButton( const DeviceContextHandle& dc, RECT& rect )
{
    dc.DrawCaptionFrameControl( DrawFrameControlCaptionPart::MinimizeButton, rect, DrawFrameControlOptions::None );
}

void DeviceContextExampleForm::DrawCaptionFrameControlMaximizeButton( const DeviceContextHandle& dc, RECT& rect )
{
    dc.DrawCaptionFrameControl( DrawFrameControlCaptionPart::MaximizeButton, rect, DrawFrameControlOptions::None );
}

void DeviceContextExampleForm::DrawCaptionFrameControlRestoreButton( const DeviceContextHandle& dc, RECT& rect )
{
    dc.DrawCaptionFrameControl( DrawFrameControlCaptionPart::RestoreButton, rect, DrawFrameControlOptions::None );
}

void DeviceContextExampleForm::DrawCaptionFrameControlHelpButton( const DeviceContextHandle& dc, RECT& rect )
{
    dc.DrawCaptionFrameControl( DrawFrameControlCaptionPart::HelpButton, rect, DrawFrameControlOptions::None );
}

void DeviceContextExampleForm::DrawMenuBarFrameControlArrow( const DeviceContextHandle& dc, RECT& rect )
{
    dc.DrawMenuBarFrameControl( DrawFrameControlMenuBarPart::Arrow, rect, DrawFrameControlOptions::None );
}
void DeviceContextExampleForm::DrawMenuBarFrameControlCheck( const DeviceContextHandle& dc, RECT& rect )
{
    dc.DrawMenuBarFrameControl( DrawFrameControlMenuBarPart::Check, rect, DrawFrameControlOptions::None );
}
void DeviceContextExampleForm::DrawMenuBarFrameControlBullet( const DeviceContextHandle& dc, RECT& rect )
{
    dc.DrawMenuBarFrameControl( DrawFrameControlMenuBarPart::Bullet, rect, DrawFrameControlOptions::None );
}
void DeviceContextExampleForm::DrawMenuBarFrameControlArrowRight( const DeviceContextHandle& dc, RECT& rect )
{
    dc.DrawMenuBarFrameControl( DrawFrameControlMenuBarPart::ArrowRight, rect, DrawFrameControlOptions::None );
}


void DeviceContextExampleForm::DrawScrollBarFrameControlUp( const DeviceContextHandle& dc, RECT& rect )
{
    dc.DrawScrollBarFrameControl( DrawFrameControlScrollBarPart::Up, rect, DrawFrameControlOptions::None );
}

void DeviceContextExampleForm::DrawScrollBarFrameControlDown( const DeviceContextHandle& dc, RECT& rect )
{
    dc.DrawScrollBarFrameControl( DrawFrameControlScrollBarPart::Down, rect, DrawFrameControlOptions::None );
}

void DeviceContextExampleForm::DrawScrollBarFrameControlLeft( const DeviceContextHandle& dc, RECT& rect )
{
    dc.DrawScrollBarFrameControl( DrawFrameControlScrollBarPart::Left, rect, DrawFrameControlOptions::None );
}

void DeviceContextExampleForm::DrawScrollBarFrameControlRight( const DeviceContextHandle& dc, RECT& rect )
{
    dc.DrawScrollBarFrameControl( DrawFrameControlScrollBarPart::Right, rect, DrawFrameControlOptions::None );
}

void DeviceContextExampleForm::DrawScrollBarFrameControlComboBox( const DeviceContextHandle& dc, RECT& rect )
{
    dc.DrawScrollBarFrameControl( DrawFrameControlScrollBarPart::ComboBox, rect, DrawFrameControlOptions::None );
}

void DeviceContextExampleForm::DrawScrollBarFrameControlSizeGrip( const DeviceContextHandle& dc, RECT& rect )
{
    dc.DrawScrollBarFrameControl( DrawFrameControlScrollBarPart::SizeGrip, rect, DrawFrameControlOptions::None );
}

void DeviceContextExampleForm::DrawScrollBarFrameControlSizeGripRight( const DeviceContextHandle& dc, RECT& rect )
{
    dc.DrawScrollBarFrameControl( DrawFrameControlScrollBarPart::SizeGripRight, rect, DrawFrameControlOptions::None );
}

void DeviceContextExampleForm::DrawButtonFrameControlCheckBox( const DeviceContextHandle& dc, RECT& rect )
{
    dc.DrawButtonFrameControl( DrawFrameControlButtonOptions::CheckBox, rect, DrawFrameControlOptions::None );
}

void DeviceContextExampleForm::DrawButtonFrameControlRadioImage( const DeviceContextHandle& dc, RECT& rect )
{
    dc.DrawButtonFrameControl( DrawFrameControlButtonOptions::RadioImage, rect, DrawFrameControlOptions::None );
}

void DeviceContextExampleForm::DrawButtonFrameControlRadioMask( const DeviceContextHandle& dc, RECT& rect )
{
    dc.DrawButtonFrameControl( DrawFrameControlButtonOptions::RadioMask, rect, DrawFrameControlOptions::None );
}

void DeviceContextExampleForm::DrawButtonFrameControlRadioButton( const DeviceContextHandle& dc, RECT& rect )
{
    dc.DrawButtonFrameControl( DrawFrameControlButtonOptions::RadioButton, rect, DrawFrameControlOptions::None );
}

void DeviceContextExampleForm::DrawButtonFrameControlThreeState( const DeviceContextHandle& dc, RECT& rect )
{
    dc.DrawButtonFrameControl( DrawFrameControlButtonOptions::ThreeState, rect, DrawFrameControlOptions::None );
}

void DeviceContextExampleForm::DrawButtonFrameControlPushButton( const DeviceContextHandle& dc, RECT& rect )
{
    dc.DrawButtonFrameControl( DrawFrameControlButtonOptions::PushButton, rect, DrawFrameControlOptions::None );
}

void DeviceContextExampleForm::DrawEdgeRaisedOuter( const DeviceContextHandle& dc, RECT& rect )
{
    dc.DrawEdge( rect, BorderStyle::RaisedOuter, BorderFlags::Rectangle );
}

void DeviceContextExampleForm::DrawEdgeSunkenOuter( const DeviceContextHandle& dc, RECT& rect )
{
    dc.DrawEdge( rect, BorderStyle::SunkenOuter, BorderFlags::Rectangle );
}

void DeviceContextExampleForm::DrawEdgeRaisedInner( const DeviceContextHandle& dc, RECT& rect )
{
    dc.DrawEdge( rect, BorderStyle::RaisedInner, BorderFlags::Rectangle );
}

void DeviceContextExampleForm::DrawEdgeSunkenInner( const DeviceContextHandle& dc, RECT& rect )
{
    dc.DrawEdge( rect, BorderStyle::SunkenInner, BorderFlags::Rectangle );
}

void DeviceContextExampleForm::DrawEdgeRaised( const DeviceContextHandle& dc, RECT& rect )
{
    dc.DrawEdge( rect, BorderStyle::Raised, BorderFlags::Rectangle );
}

void DeviceContextExampleForm::DrawEdgeSunken( const DeviceContextHandle& dc, RECT& rect )
{
    dc.DrawEdge( rect, BorderStyle::Sunken, BorderFlags::Rectangle );
}

void DeviceContextExampleForm::DrawEdgeEtched( const DeviceContextHandle& dc, RECT& rect )
{
    dc.DrawEdge( rect, BorderStyle::Etched, BorderFlags::Rectangle );
}

void DeviceContextExampleForm::DrawEdgeBump( const DeviceContextHandle& dc, RECT& rect )
{
    dc.DrawEdge( rect, BorderStyle::Bump, BorderFlags::Rectangle );
}

void DeviceContextExampleForm::DrawFocusRect( const DeviceContextHandle& dc, RECT& rect )
{
    dc.DrawFocusRect( rect );
}

void DeviceContextExampleForm::DrawStateNormal( const DeviceContextHandle& dc, RECT& rect )
{
    auto height = Windows::Environment::SystemMetrics::CaptionHeight( );
    rect.top = rect.top + ( ( ( rect.bottom - rect.top ) / 2 ) - ( height / 2 ) );

    std::wstring s( L"DrawState Normal" );
    dc.DrawStateW( s, rect.left, rect.top, DrawStateFlags::Normal );
}

void DeviceContextExampleForm::DrawStatePrefix( const DeviceContextHandle& dc, RECT& rect )
{
    auto height = Windows::Environment::SystemMetrics::CaptionHeight( );
    rect.top = rect.top + ( ( ( rect.bottom - rect.top ) / 2 ) - ( height / 2 ) );

    std::wstring s( L"DrawState &Prefix" );
    dc.DrawStateW( s, rect.left, rect.top, DrawStateFlags::Prefix );
}

void DeviceContextExampleForm::DrawStateDithered( const DeviceContextHandle& dc, RECT& rect )
{
    auto height = Windows::Environment::SystemMetrics::CaptionHeight( );
    rect.top = rect.top + ( ( ( rect.bottom - rect.top ) / 2 ) - ( height / 2 ) );

    std::wstring s( L"DrawState Dithered" );
    dc.DrawStateW( s, rect.left, rect.top, DrawStateFlags::Dithered );
}

void DeviceContextExampleForm::DrawStateDisabled( const DeviceContextHandle& dc, RECT& rect )
{
    auto height = Windows::Environment::SystemMetrics::CaptionHeight( );
    rect.top = rect.top + ( ( ( rect.bottom - rect.top ) / 2 ) - ( height / 2 ) );

    std::wstring s( L"DrawState Disabled" );
    dc.DrawStateW( s, rect.left, rect.top, DrawStateFlags::Disabled );
}

void DeviceContextExampleForm::DrawStateMono( const DeviceContextHandle& dc, RECT& rect )
{
    auto height = Windows::Environment::SystemMetrics::CaptionHeight( );
    rect.top = rect.top + ( ( ( rect.bottom - rect.top ) / 2 ) - ( height / 2 ) );

    std::wstring s( L"DrawState Mono" );
    BrushHandle brush( RGB( 0xFF, 0, 0 ) );
    dc.DrawStateW( brush, s, rect.left, rect.top, DrawStateFlags::Mono );
}

void DeviceContextExampleForm::DrawStateHidePrefix( const DeviceContextHandle& dc, RECT& rect )
{
    auto height = Windows::Environment::SystemMetrics::CaptionHeight( );
    rect.top = rect.top + ( ( ( rect.bottom - rect.top ) / 2 ) - ( height / 2 ) );

    std::wstring s( L"DrawState &Prefix" );
    dc.DrawStateW( s, rect.left, rect.top, DrawStateFlags::HidePrefix );
}

void DeviceContextExampleForm::DrawStatePrefixOnly( const DeviceContextHandle& dc, RECT& rect )
{
    auto height = Windows::Environment::SystemMetrics::CaptionHeight( );
    rect.top = rect.top + ( ( ( rect.bottom - rect.top ) / 2 ) - ( height / 2 ) );

    std::wstring s( L"DrawState &Prefix" );
    dc.DrawStateW( s, rect.left, rect.top, DrawStateFlags::PrefixOnly );
}

void DeviceContextExampleForm::DrawStateRight( const DeviceContextHandle& dc, RECT& rect )
{
    auto height = Windows::Environment::SystemMetrics::CaptionHeight( );
    rect.top = rect.top + ( ( ( rect.bottom - rect.top ) / 2 ) - ( height / 2 ) );

    std::wstring s( L"DrawState Right" );
    dc.DrawStateW( s, rect.left, rect.top, rect.right - rect.left, height, DrawStateFlags::Right );
}

void DeviceContextExampleForm::DrawDesktopWallPaper( const DeviceContextHandle& dc, RECT& rect )
{
    dc.DrawDesktopWallPaper( );
}


void DeviceContextExampleForm::DrawChord( const DeviceContextHandle& dc, RECT& rect )
{
    POINT start = { rect.left };
    POINT end;
    dc.DrawChord( rect, start, end );
}

void DeviceContextExampleForm::DrawScreenWidthAndHeight( const DeviceContextHandle& dc, RECT& rect )
{
    auto height = Windows::Environment::SystemMetrics::CaptionHeight( );
    rect.top = rect.top + ( ( ( rect.bottom - rect.top ) / 2 ) - ( height / 2 ) );

    auto screenHeight = Windows::Environment::SystemMetrics::ScreenHeight( );
    auto screenWidth = Windows::Environment::SystemMetrics::ScreenWidth( );

    MapMode mapMode = dc.MapMode( );
    dc.SetMapMode( MapMode::LoMetric );

    POINT pt = { (LONG)screenWidth,(LONG)screenHeight };
    ::DPtoLP( dc.Value( ), &pt, 1 );

    dc.SetMapMode( mapMode );

    auto s = Format( L"Width {}, Height {}", pt.x, pt.y );

    dc.DrawStateW( s, rect.left, rect.top, DrawStateFlags::Normal );
}



int APIENTRY _tWinMain( _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPTSTR    lpCmdLine,
    _In_ int       nCmdShow )
{
    UNREFERENCED_PARAMETER( hPrevInstance );
    UNREFERENCED_PARAMETER( lpCmdLine );
    try
    {
        auto application = std::make_shared<Harlinn::Windows::Application>( );
        application->Start( );

        auto result = application->Run<DeviceContextExampleForm>( );

        application->Stop( );

        return result;

    }
    catch ( std::exception& exc )
    {
        std::cout << exc.what( ) << std::endl;
    }
    catch ( ... )
    {

    }
    return 0;
}