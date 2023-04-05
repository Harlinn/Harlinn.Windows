#include "pch.h"
#include <HOCIInternal.h>

namespace Harlinn::OCI
{

    void DefineBase::DefineByPos( UInt32 positon, OraType dataType, void* dataAddress, Int64 dataSize, Int16* indicators, UInt32* returnLengths, UInt16* returnCodes, UInt32 mode )
    {
        void* defineHandle = nullptr;
        auto& error = Error( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIDefineByPos2( (OCIStmt*)statement_->Handle( ), (OCIDefine**)&defineHandle, errorHandle, static_cast<UInt32>( positon ), 
            dataAddress, dataSize, static_cast<UInt16>( dataType ), 
            indicators, returnLengths, returnCodes, mode );
        if ( rc == OCI_ERROR )
        {
            error.CheckResult( rc );
        }
        InitializeHandle( defineHandle, true );
    }

    void DefineBase::SetLOBPrefetchSize( UInt32 lobPrefetchSize )
    {
        SetUInt32Attribute( Attribute::LOBPREFETCH_SIZE, lobPrefetchSize );
    }
    UInt32 DefineBase::LOBPrefetchSize( ) const
    {
        auto result = GetUInt32Attribute( Attribute::LOBPREFETCH_SIZE );
        return result;
    }

    void DefineBase::SetLOBPrefetchLength( bool value )
    {
        SetBooleanAttribute( Attribute::LOBPREFETCH_LENGTH, value );
    }
    bool DefineBase::LOBPrefetchLength( ) const
    {
        auto result = GetBooleanAttribute( Attribute::LOBPREFETCH_LENGTH );
        return result;
    }
}