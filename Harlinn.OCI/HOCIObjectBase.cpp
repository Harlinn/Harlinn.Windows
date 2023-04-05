#include "pch.h"
#include <HOCIInternal.h>

namespace Harlinn::OCI
{
    ObjectBase::~ObjectBase( )
    {
        auto& serviceContext = ServiceContext( );
        if ( serviceContext.IsValid( ) && object_ && objectReleaseMethod_ != ObjectReleaseMethod::None )
        {
            auto& error = Error( );
            auto& environment = serviceContext.Environment( );
            auto environmentHandle = (OCIEnv*)environment.Handle( );
            auto errorHandle = (OCIError*)error.Handle( );

            if ( ( objectReleaseMethod_ & ObjectReleaseMethod::ObjectFree ) != ObjectReleaseMethod::ObjectFree )
            {
                OCIObjectUnpin( environmentHandle, errorHandle, object_ );
            }
            else
            {
                OCIObjectFree( environmentHandle, errorHandle, object_, static_cast<UInt16>( objectReleaseMethod_ & ObjectReleaseMethod::ObjectFreeMask ) );
            }
        }
    }
}