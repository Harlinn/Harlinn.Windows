#include "pch.h"
#include "HCCEse.h"

namespace Harlinn::Common::Core::Ese
{
    namespace
    {
        __declspec(thread) wchar_t messagebuffer[4096] = { 0, };

        WideString GetEseError( JET_ERR rc )
        {
            wchar_t* buffer = messagebuffer;
            JetGetSystemParameterW( JET_instanceNil, JET_sesidNil, JET_paramErrorToString, ( JET_API_PTR* )&rc, buffer, 4096 );
            auto result = Format( L"ESENT error %d: %s\n", rc, buffer );
            return result;
        }
    }

    Exception::Exception(JET_ERR rc)
        : Base( GetEseError( rc ) )
    {

    }

    Exception::Exception( Result rc )
        : Base( GetEseError( static_cast<JET_ERR>( rc ) ) )
    {

    }

    WideString Exception::GetErrorMessage( JET_ERR rc )
    {
        return GetEseError( rc );
    }

    WideString Exception::GetErrorMessage( Result rc )
    {
        return GetEseError( static_cast<JET_ERR>( rc ) );
    }
    
    HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS(Exception)
    

}
