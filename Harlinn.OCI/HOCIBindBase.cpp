#include "pch.h"
#include <HOCIInternal.h>

namespace Harlinn::OCI
{
    void BindBase::BindByPos( UInt32 positon, OraType dataType, void* dataAddress, Int64 dataSize, Int16* indicators, UInt32* actualLengths, UInt16* returnCodes, UInt32 plsqlMaxArrayLength, UInt32* plsqlArrayLength, UInt32 mode )
    {
        void* bindHandle = nullptr;
        auto& statement = Statement( );
        auto& error = statement.Error( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIBindByPos2( (OCIStmt*)statement.Handle( ), (OCIBind**)&bindHandle, errorHandle, static_cast<UInt32>( positon ),
            dataAddress, dataSize, static_cast<UInt16>( dataType ), indicators, actualLengths, returnCodes, plsqlMaxArrayLength, plsqlArrayLength, mode );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
        InitializeHandle( bindHandle, true );
    }
    void BindBase::BindByName( const WideString& name, OraType dataType, void* dataAddress, Int64 dataSize, Int16* indicators, UInt32* actualLengths, UInt16* returnCodes, UInt32 plsqlMaxArrayLength, UInt32* plsqlArrayLength, UInt32 mode )
    {
        void* bindHandle = nullptr;
        auto& statement = Statement( );
        auto& error = statement.Error( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIBindByName2( (OCIStmt*)statement.Handle( ), (OCIBind**)&bindHandle, errorHandle, (OraText*)name.c_str( ), static_cast<sb4>( name.length( ) * sizeof( wchar_t ) ),
            dataAddress, dataSize, static_cast<UInt16>( dataType ), indicators, actualLengths, returnCodes, plsqlMaxArrayLength, plsqlArrayLength, mode );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
        InitializeHandle( bindHandle, true );
    }
    void BindBase::Bind( UInt32 positon, UInt32 iters )
    {
        HCC_THROW( NotImplementedException );
    }

    void BindBase::Bind( const WideString& name, UInt32 iters )
    {
        HCC_THROW( NotImplementedException );
    }



}