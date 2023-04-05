#include "pch.h"
#include <HOCIInternal.h>

namespace Harlinn::OCI
{
    void DataReader::InitializeDefines( )
    {
        auto& serviceContext = statement_->ServiceContext( );
        auto& error = Base::Error( );
        auto serviceContextHandle = (OCISvcCtx*)serviceContext.Handle( );
        auto statementHandle = (OCIStmt*)statement_->Handle( );
        auto errorHandle = (OCIError*)error.Handle( );

        auto rc = OCIStmtExecute( serviceContextHandle, statementHandle, errorHandle, (ub4)1, (ub4)0, (const OCISnapshot*)0, (OCISnapshot*)0, OCI_DESCRIBE_ONLY );
        error.CheckResult( rc );

        auto descriptorCount = statement_->DescriptorCount( );

        defines_.reserve( descriptorCount );
        for ( UInt32 i = 0; i < descriptorCount; i++ )
        {
            auto define = statement_->Define( i + 1 );
            defines_.emplace_back( std::move( define ) );
        }
    }


}