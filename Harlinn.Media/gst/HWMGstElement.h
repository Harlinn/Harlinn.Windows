#pragma once
#ifndef HARLINN_MEDIA_GST_HWMGSTELEMENT_H_
#define HARLINN_MEDIA_GST_HWMGSTELEMENT_H_

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


#include "HWMGstConstants.h"
#include "HWMGstObject.h"
#include "HWMGstBus.h"
#include "HWMGstPad.h"
#include "HWMGstClock.h"

namespace Harlinn::Media::GStreamer
{
    namespace Internal
    {
        template<typename BaseT>
        class ElementImpl : public BaseT
        {
        public:
            using Base = BaseT;
            HWM_GOBJECT_IMPLEMENT_STANDARD_MEMBERS( ElementImpl, GstElement )

            GLib::RecMutex& StateLock( ) const
            {
                return reinterpret_cast< GLib::RecMutex& >( get( )->state_lock );
            }
            GLib::Cond& StateCond( ) const
            {
                return reinterpret_cast< GLib::Cond& >( get( )->state_cond );
            }

            GstState TargetState( ) const
            {
                return get( )->target_state;
            }
            GstState CurrentState( ) const
            {
                return get( )->current_state;
            }
            GstState NextState( ) const
            {
                return get( )->next_state;
            }
            GstState PendingState( ) const
            {
                return get( )->pending_state;
            }
            GstStateChangeReturn LastReturn( ) const
            {
                return get( )->last_return;
            }

            BasicBus Bus( GLib::ReferenceType referenceType = GLib::ReferenceType::None ) const
            {
                auto bus = get( )->bus;
                if ( bus )
                {
                    return BasicBus( bus, referenceType );
                }
                return {};
            }

            BasicClock Clock( GLib::ReferenceType referenceType = GLib::ReferenceType::None ) const
            {
                auto clock = get( )->clock;
                if ( clock )
                {
                    return BasicClock( clock, referenceType );
                }
                return {};
            }

            GstClockTimeDiff BaseTime( ) const
            {
                return get( )->base_time;
            }

            GstClockTime StartTime( ) const
            {
                return get( )->start_time;
            }
        };
    }

    using BasicElement = Internal::ElementImpl<BasicObject>;
    using Element = Internal::ElementImpl<Object>;


}

#endif
