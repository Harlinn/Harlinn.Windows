#include "pch.h"
#include <HOCIInternal.h>

namespace Harlinn::OCI
{
    Statement::~Statement( )
    {
        auto handle = DetachHandle( );
        if ( handle )
        {
            auto& serviceContext = ServiceContext( );
            if ( serviceContext )
            {
                auto& environment = serviceContext.Environment( );
                auto error = environment.CreateError( );
                auto errorHandle = (OCIError*)error.Handle( );
                OCIStmtRelease( (OCIStmt*)handle, errorHandle, nullptr, 0, OCI_DEFAULT );
            }
        }
    }


    Int32 Statement::Execute( UInt32 iters, StatementExecuteMode executeMode, UInt32 rowoff )
    {
        auto& serviceContext = ServiceContext( );
        if ( serviceContext.IsValid( ) == false )
        {
            HCC_THROW( Data::OracleClient::OracleException, L"Missing service context" );
        }
        auto& environment = serviceContext.Environment( );
        if ( environment.IsValid( ) )
        {
            for ( auto& bind : binds_ )
            {
                bind->OnExecute( iters );
            }
            auto& error = serviceContext.Error( );
            auto serviceContextHandle = (OCISvcCtx*)serviceContext.Handle( );
            auto errorHandle = (OCIError*)error.Handle( );
            auto statementHandle = (OCIStmt*)Handle( );
            auto rc = OCIStmtExecute( serviceContextHandle, statementHandle, errorHandle, iters, rowoff, nullptr, nullptr, static_cast<UInt32>( executeMode ) );
            if ( rc < OCI::Result::Success )
            {   
                ThrowOracleExceptionOnError( errorHandle, rc, OCI::HandleType::Error );
            }
            return rc;
        }
        else
        {
            ThrowInvalidEnvironment( );
        }
    }



    Int32 Statement::Fetch( UInt32 numberOfRows, FetchOrientation fetchOrientation, long fetchOffset ) const
    {
        auto& error = Error( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIStmtFetch2( (OCIStmt*)Handle( ), errorHandle, numberOfRows, static_cast<UInt16>( fetchOrientation ), fetchOffset, OCI_DEFAULT );
        if ( rc < OCI::Result::Success )
        {
            error.CheckResult( rc );
        }
        return rc;
    }

    std::unique_ptr<OCI::ParameterDescriptor> Statement::Descriptor( UInt32 descriptorIndex ) const
    {
        auto& error = Error( );
        auto errorHandle = (OCIError*)error.Handle( );
        OCIParam* param = nullptr;
        auto rc = OCIParamGet( Handle( ), static_cast<UInt32>( HandleType( ) ), errorHandle, (void**)&param, static_cast<UInt32>( descriptorIndex ) );
        error.CheckResult( rc );
        auto& serviceContext = ServiceContext( );
        auto result = OCI::ParameterDescriptor::CreateParameter( serviceContext, param );
        return result;
    }

    void Statement::GetDescriptors( std::vector< std::unique_ptr<ParameterDescriptor> >& descriptors ) const
    {
        auto descriptorCount = DescriptorCount( );
        descriptors.clear( );
        descriptors.reserve( descriptorCount );
        for ( UInt32 i = 0; i < descriptorCount; i++ )
        {
            auto descriptor = Descriptor( i + 1 );
            descriptors.emplace_back( std::move( descriptor ) );
        }
    }

    std::unique_ptr <OCI::Define > Statement::Define( UInt32 descriptorIndex ) const
    {
        auto descriptor = Descriptor( descriptorIndex );
        const OCI::ColumnDescriptor& columnDescriptor = static_cast<const OCI::ColumnDescriptor&>( *descriptor );
        auto result = Define( descriptorIndex, columnDescriptor );
        return result;
    }
    std::unique_ptr<OCI::Define> Statement::Define( UInt32 descriptorIndex, const OCI::ColumnDescriptor& columnDescriptor ) const
    {
        return OCI::Define::CreateDefine( *this, columnDescriptor, descriptorIndex );
    }

    std::unique_ptr<OCI::ArrayDefine> Statement::Define( size_t defineSize, UInt32 descriptorIndex ) const
    {
        auto descriptor = Descriptor( descriptorIndex );
        const OCI::ColumnDescriptor& columnDescriptor = static_cast<const OCI::ColumnDescriptor&>( *descriptor );
        return Define( defineSize, descriptorIndex, columnDescriptor );
    }
    std::unique_ptr<OCI::ArrayDefine> Statement::Define( size_t defineSize, UInt32 descriptorIndex, const OCI::ColumnDescriptor& columnDescriptor ) const
    {
        return OCI::ArrayDefine::CreateDefine( *this, defineSize, columnDescriptor, descriptorIndex );
    }

}