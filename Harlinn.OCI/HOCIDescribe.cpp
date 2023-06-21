#include "pch.h"
#include <HOCIInternal.h>

namespace Harlinn::OCI
{

    void Describe::DescribeAny( const WideString& objectName, OCI::ParameterType parameterType ) const
    {
        auto& serviceContext = ServiceContext( );
        auto& error = Error( );
        auto serviceContextHandle = (OCISvcCtx*)serviceContext.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );

        OraText* ociObjectName = (OraText*)objectName.data( );
        UInt32 objectNameLength = static_cast<UInt32>( objectName.length( ) );
        auto rc = OCIDescribeAny( serviceContextHandle, errorHandle, ociObjectName, objectNameLength, OCI_OTYPE_NAME, OCI_DEFAULT, static_cast<Byte>( parameterType ), (OCIDescribe*)Handle( ) );
        error.CheckResult( rc );
    }
    void Describe::DescribeAny( const OCI::Type& type ) const
    {
        DescribeAny( (OCIType*)type.Handle( ) );
    }

    void Describe::DescribeAny( OCIType* type ) const
    {
        auto& serviceContext = ServiceContext( );
        auto& error = Error( );
        auto serviceContextHandle = (OCISvcCtx*)serviceContext.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIDescribeAny( serviceContextHandle, errorHandle, type, 0, OCI_OTYPE_PTR, OCI_DEFAULT, OCI_PTYPE_TYPE, (OCIDescribe*)Handle( ) );
        error.CheckResult( rc );
    }

    void Describe::DescribeAny( const OCI::Ref& typeRef ) const
    {
        DescribeAny( (OCIRef*)typeRef.Handle( ) );
    }

    void Describe::DescribeAny( OCIRef* typeRef ) const
    {
        auto& serviceContext = ServiceContext( );
        auto& error = Error( );
        auto serviceContextHandle = (OCISvcCtx*)serviceContext.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIDescribeAny( serviceContextHandle, errorHandle, typeRef, 0, OCI_OTYPE_REF, OCI_DEFAULT, OCI_PTYPE_TYPE, (OCIDescribe*)Handle( ) );
        error.CheckResult( rc );
    }

    std::unique_ptr<ParameterDescriptor> Describe::_Descriptor( ) const
    {
        OCIParam* parameterDescriptorHandle = (OCIParam*)GetPointerAttribute( Attribute::PARAM );
        auto& serviceContext = ServiceContext( );
        auto result = ParameterDescriptor::CreateParameter( serviceContext, parameterDescriptorHandle );
        return result;
    }
}