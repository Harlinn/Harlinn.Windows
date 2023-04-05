#include "pch.h"
#include <HOCIInternal.h>

namespace Harlinn::OCI
{
    Int32 ErrorHandle::CheckResult( void* errorHandle, OCI::HandleType handleType, Int32 rc ) const
    {
        return ThrowOracleExceptionOnError( Handle( ), rc, OCI::HandleType::Error );
    }

    Int32 ErrorHandle::CheckResult( Int32 rc ) const
    {
        return CheckResult( Handle( ), OCI::HandleType::Error, rc );
    }

    UInt32 ErrorHandle::DMLRowOffset( ) const
    {
        auto result = GetUInt32Attribute( Attribute::DML_ROW_OFFSET );
        return result;
    }
}