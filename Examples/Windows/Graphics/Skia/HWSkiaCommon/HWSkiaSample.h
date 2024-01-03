#pragma once
#ifndef HARLINN_HWSKIACOMMON_HWSKIASAMPLE_H_
#define HARLINN_HWSKIACOMMON_HWSKIASAMPLE_H_
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


#include <HWSkia.h>

#include <skia/tools/gpu/d3d/D3DTestUtils.h>
#include <skia/tools/skui/InputState.h>
#include <skia/tools/skui/Key.h>
#include <skia/tools/skui/ModifierKey.h>
#include <skia/tools/SkMetaData.h>
#include <src/core/SkUtils.h>
#include <skia/tools/Resources.h>

namespace Harlinn::Windows
{
    HCC_DEFINE_ENUM_FLAG_OPERATORS( skui::ModifierKey, int );

    namespace Skia
    {

        class Sample
        {
        public:
            // Click handling
            class Click
            {
            public:
                Click( ) {}
                Click( std::function<bool( Click* )> f ) : fFunc( f ), fHasFunc( true ) {}
                virtual ~Click( ) = default;

                SkPoint fOrig = { 0, 0 };
                SkPoint fPrev = { 0, 0 };
                SkPoint fCurr = { 0, 0 };
                skui::InputState  fState = skui::InputState::kDown;
                skui::ModifierKey fModifierKeys = skui::ModifierKey::kNone;
                SkMetaData  fMeta;

                std::function<bool( Click* )> fFunc;
                bool fHasFunc = false;
            };
        private:
            std::unique_ptr<Click> fClick;
            SkColor fBGColor;
            SkScalar fWidth, fHeight;
            bool fHaveCalledOnceBeforeDraw;
        public:
            Sample( )
                : fBGColor( SK_ColorWHITE )
                , fWidth( 0 ), fHeight( 0 )
                , fHaveCalledOnceBeforeDraw( false )
            {
            }

            virtual ~Sample( ) = default;

            Sample( const Sample& ) = delete;
            Sample& operator=( const Sample& ) = delete;

            SkScalar width( ) const { return fWidth; }
            SkScalar height( ) const { return fHeight; }
            void setSize( SkScalar width, SkScalar height )
            {
                width = std::max( 0.0f, width );
                height = std::max( 0.0f, height );

                if ( fWidth != width || fHeight != height )
                {
                    fWidth = width;
                    fHeight = height;
                    this->onSizeChange( );
                }
            }
            void setSize( const SkPoint& size ) { this->setSize( size.fX, size.fY ); }
            void setWidth( SkScalar width ) { this->setSize( width, fHeight ); }
            void setHeight( SkScalar height ) { this->setSize( fWidth, height ); }

            // Call this to have the view draw into the specified canvas. 
            virtual void draw( SkCanvas* canvas )
            {
                if ( fWidth && fHeight )
                {
                    SkRect    r;
                    r.setLTRB( 0, 0, fWidth, fHeight );
                    if ( canvas->quickReject( r ) )
                    {
                        return;
                    }

                    SkAutoCanvasRestore as( canvas, true );
                    int sc = canvas->save( );

                    if ( !fHaveCalledOnceBeforeDraw )
                    {
                        fHaveCalledOnceBeforeDraw = true;
                        this->onOnceBeforeDraw( );
                    }
                    this->onDrawBackground( canvas );

                    SkAutoCanvasRestore acr( canvas, true );
                    this->onDrawContent( canvas );
#if SK_SUPPORT_GPU
                    // Ensure the context doesn't combine GrDrawOps across draw loops.
                    if ( auto direct = GrAsDirectContext( canvas->recordingContext( ) ) )
                    {
                        direct->flushAndSubmit( );
                    }
#endif
                    canvas->restoreToCount( sc );
                }
            }

            virtual bool onChar( SkUnichar ) { return false; }

            bool mouse( SkPoint point, skui::InputState clickState, skui::ModifierKey modifierKeys )
            {
                auto dispatch = [this]( Click* c )
                {
                    return c->fHasFunc ? c->fFunc( c ) : this->onClick( c );
                };

                switch ( clickState )
                {
                    case skui::InputState::kDown:
                        fClick = nullptr;
                        fClick.reset( this->onFindClickHandler( point.x( ), point.y( ), modifierKeys ) );
                        if ( !fClick )
                        {
                            return false;
                        }
                        fClick->fPrev = fClick->fCurr = fClick->fOrig = point;
                        fClick->fState = skui::InputState::kDown;
                        fClick->fModifierKeys = modifierKeys;
                        dispatch( fClick.get( ) );
                        return true;
                    case skui::InputState::kMove:
                        if ( fClick )
                        {
                            fClick->fPrev = fClick->fCurr;
                            fClick->fCurr = point;
                            fClick->fState = skui::InputState::kMove;
                            fClick->fModifierKeys = modifierKeys;
                            return dispatch( fClick.get( ) );
                        }
                        return false;
                    case skui::InputState::kUp:
                        if ( fClick )
                        {
                            fClick->fPrev = fClick->fCurr;
                            fClick->fCurr = point;
                            fClick->fState = skui::InputState::kUp;
                            fClick->fModifierKeys = modifierKeys;
                            bool result = dispatch( fClick.get( ) );
                            fClick = nullptr;
                            return result;
                        }
                        return false;
                    default:
                        // Ignore other cases
                        SkASSERT( false );
                        break;
                }
                SkASSERT( false );
                return false;
            }

            void setBGColor( SkColor color ) { fBGColor = color; }
            bool animate( double nanos ) { return this->onAnimate( nanos ); }

            virtual SkString name( ) = 0;

        protected:
            // Override to be notified of size changes. Overriders must call the super class. 
            virtual void onSizeChange( )
            {
            }

            // Override this if you might handle the click 
            virtual Click* onFindClickHandler( SkScalar x, SkScalar y, skui::ModifierKey modi )
            {
                return nullptr;
            }

            // Override to track clicks. Return true as long as you want to track the pen/mouse. 
            virtual bool onClick( Click* )
            {
                return false;
            }

            virtual void onDrawBackground( SkCanvas* canvas )
            {
                canvas->drawColor( fBGColor );
            }
            virtual void onDrawContent( SkCanvas* ) = 0;
            virtual bool onAnimate( double /*nanos*/ )
            {
                return false;
            }
            virtual void onOnceBeforeDraw( )
            {
            }


        };



        class SampleControlBase : public SkiaControl
        {
        public:
            using Base = SkiaControl;
        private:
            std::unique_ptr<Sample> sample_;
            Timer timer_;
            DateTime started_;
        public:
            virtual void DoOnTimer( Timer* timer )
            {

                if ( sample_ )
                {
                    double now = static_cast<double>( (DateTime::Now( ).Ticks( ) - started_.Ticks( ) ) * 100 );
                    if ( sample_->animate( now ) )
                    {
                        InvalidateRect( );
                    }
                }
            }

            SampleControlBase( )
                : Base( ), started_( DateTime::Now( ) )
            {
                timer_.OnTick.connect( [this]( Timer* timer )
                {
                    this->DoOnTimer( timer );
                } );
            }

            void StartTimer( )
            {
                timer_.SetEnabled( );
            }
            void SetTimerInterval( const TimeSpan& interval )
            {
                timer_.SetInterval( interval );
            }



        protected:
            template<typename T>
            void CreateSample( )
            {
                sample_ = std::make_unique<T>( );
            }

            virtual void DoOnHandleCreated( ) override
            {
                Base::DoOnHandleCreated( );
                SetTimerInterval( TimeSpan::FromMilliseconds( 33 ) );
                StartTimer( );
            }

            virtual void DoOnRender( SkCanvas* canvas )
            {
                Base::DoOnRender( canvas );
                sample_->draw( canvas );
            }

            static skui::Key get_key( WPARAM vk )
            {
                static const struct
                {
                    WPARAM      fVK;
                    skui::Key fKey;
                } gPair[] = {
                    { VK_BACK,    skui::Key::kBack     },
                    { VK_CLEAR,   skui::Key::kBack     },
                    { VK_RETURN,  skui::Key::kOK       },
                    { VK_UP,      skui::Key::kUp       },
                    { VK_DOWN,    skui::Key::kDown     },
                    { VK_LEFT,    skui::Key::kLeft     },
                    { VK_RIGHT,   skui::Key::kRight    },
                    { VK_TAB,     skui::Key::kTab      },
                    { VK_PRIOR,   skui::Key::kPageUp   },
                    { VK_NEXT,    skui::Key::kPageDown },
                    { VK_HOME,    skui::Key::kHome     },
                    { VK_END,     skui::Key::kEnd      },
                    { VK_DELETE,  skui::Key::kDelete   },
                    { VK_ESCAPE,  skui::Key::kEscape   },
                    { VK_SHIFT,   skui::Key::kShift    },
                    { VK_CONTROL, skui::Key::kCtrl     },
                    { VK_MENU,    skui::Key::kOption   },
                    { 'A',        skui::Key::kA        },
                    { 'C',        skui::Key::kC        },
                    { 'V',        skui::Key::kV        },
                    { 'X',        skui::Key::kX        },
                    { 'Y',        skui::Key::kY        },
                    { 'Z',        skui::Key::kZ        },
                };
                for ( size_t i = 0; i < SK_ARRAY_COUNT( gPair ); i++ )
                {
                    if ( gPair[i].fVK == vk )
                    {
                        return gPair[i].fKey;
                    }
                }
                return skui::Key::kNONE;
            }

            static skui::ModifierKey get_modifiers( UINT message, WPARAM wParam, LPARAM lParam )
            {
                skui::ModifierKey modifiers = skui::ModifierKey::kNone;

                switch ( message )
                {
                    case WM_UNICHAR:
                    case WM_CHAR:
                        if ( 0 == ( lParam & ( 1 << 30 ) ) )
                        {
                            modifiers |= skui::ModifierKey::kFirstPress;
                        }
                        if ( lParam & ( 1 << 29 ) )
                        {
                            modifiers |= skui::ModifierKey::kOption;
                        }
                        break;

                    case WM_KEYDOWN:
                    case WM_SYSKEYDOWN:
                        if ( 0 == ( lParam & ( 1 << 30 ) ) )
                        {
                            modifiers |= skui::ModifierKey::kFirstPress;
                        }
                        if ( lParam & ( 1 << 29 ) )
                        {
                            modifiers |= skui::ModifierKey::kOption;
                        }
                        break;

                    case WM_KEYUP:
                    case WM_SYSKEYUP:
                        if ( lParam & ( 1 << 29 ) )
                        {
                            modifiers |= skui::ModifierKey::kOption;
                        }
                        break;

                    case WM_LBUTTONDOWN:
                    case WM_LBUTTONUP:
                    case WM_MOUSEMOVE:
                    case WM_MOUSEWHEEL:
                        if ( wParam & MK_CONTROL )
                        {
                            modifiers |= skui::ModifierKey::kControl;
                        }
                        if ( wParam & MK_SHIFT )
                        {
                            modifiers |= skui::ModifierKey::kShift;
                        }
                        break;
                }

                return modifiers;
            }


            virtual void HandleMessage( Message& message ) override
            {
                bool eventHandled = false;

                switch ( message.message )
                {
                    case WM_SIZE:
                        sample_->setSize( static_cast<SkScalar>( LOWORD( message.lParam ) ), static_cast<SkScalar>( HIWORD( message.lParam ) ) );
                        break;

                    case WM_UNICHAR:
                        eventHandled = sample_->onChar( (SkUnichar)message.wParam );
                        break;

                    case WM_CHAR:
                    {
                        eventHandled = sample_->onChar( static_cast<SkUnichar>( message.wParam ) );
                    }
                    break;

                    case WM_LBUTTONDOWN:
                    case WM_LBUTTONUP:
                    {
                        int xPos = GET_X_LPARAM( message.lParam );
                        int yPos = GET_Y_LPARAM( message.lParam );

                        skui::InputState istate = ( ( message.wParam & MK_LBUTTON ) != 0 ) ? skui::InputState::kDown
                            : skui::InputState::kUp;

                        eventHandled = sample_->mouse( SkPoint::Make( static_cast<SkScalar>(xPos), static_cast<SkScalar>( yPos ) ), istate, get_modifiers( message.message, message.wParam, message.lParam ) );
                    } break;

                    case WM_MOUSEMOVE:
                    {
                        int xPos = GET_X_LPARAM( message.lParam );
                        int yPos = GET_Y_LPARAM( message.lParam );
                        eventHandled = sample_->mouse( SkPoint::Make( static_cast<SkScalar>( xPos ), static_cast<SkScalar>( yPos ) ), skui::InputState::kMove, get_modifiers( message.message, message.wParam, message.lParam ) );
                    } break;


                }
                if ( !eventHandled )
                {
                    Base::HandleMessage( message );
                }
                else
                {
                    InvalidateRect( );
                    message.handled = eventHandled;
                }
            }



        };

        template<typename T>
        requires std::is_base_of_v<Sample, T>
            class SampleControl : public SampleControlBase
        {
        public:
            using Base = SampleControlBase;
            using SampleType = T;
        protected:
            virtual void DoOnInitialize( ) override
            {
                CreateSample<SampleType>( );
                Base::DoOnInitialize( );
            }



        };



        class SampleFormBase : public Form
        {
        public:
            using Base = Form;
        private:
            std::unique_ptr<SampleControlBase> control_;
        protected:
            template<typename T>
            void CreateControl( )
            {
                control_ = make_control<T>( this );
            }
        public:
            SampleFormBase( )
                : Base( )
            {
            }
        protected:
            void DoOnSize( Message& message ) override
            {
                if ( control_ )
                {
                    Harlinn::Windows::Rectangle clientRect = GetClientRect( );
                    control_->MoveWindow( 0, 0, clientRect.Width( ), clientRect.Height( ) );
                }
            }
            void DoOnSetFocus( Message& message ) override
            {
                Base::DoOnSetFocus( message );
                control_->SetFocus( );
            }
        };

        template<typename T>
        requires std::is_base_of_v<Sample, T>
            class SampleForm : public SampleFormBase
        {
        public:
            using Base = SampleFormBase;
            using Control = SampleControl<T>;
        protected:
            virtual void DoOnInitialize( ) override
            {
                Base::DoOnInitialize( );
                CreateControl<Control>( );
            }
        };



        class SampleApplicationBase : public Harlinn::Windows::Application
        {
        public:
            using Base = Harlinn::Windows::Application;
        };

        template<typename T>
        requires std::is_base_of_v<Sample, T>
            class SampleApplication : public SampleApplicationBase
        {
        public:
            using Base = SampleApplicationBase;
            using FormType = SampleForm<T>;

            static int Run( )
            {
                try
                {
                    SetThreadDpiAwarenessContext( DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2 );

                    Harlinn::Windows::Application application;
                    application.Start( );

                    SkGraphics::Init( );

                    auto hccHome = Harlinn::Common::Core::Environment::EnvironmentVariable( "HCC_HOME" );
                    auto resourcesDirectory = hccHome + "\\resources";
                    SetResourcePath( resourcesDirectory.c_str( ) );

                    FormType form;
                    form.Initialize( );

                    auto result = application.Run( form );

                    application.Stop( );

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


        };
    }
}

#endif
