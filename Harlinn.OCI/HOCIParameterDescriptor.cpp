#include "pch.h"
#include <HOCIInternal.h>

namespace Harlinn::OCI
{
    std::unique_ptr<OCI::ParameterDescriptor> ParameterDescriptor::CreateParameter( const OCI::ServiceContext& serviceContext, OCIParam* handle, bool ownsHandle )
    {
        std::unique_ptr<OCI::ParameterDescriptor> result;
        auto parameterType = OCI::ParameterType::Unknown;
        auto& error = serviceContext.Error( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIAttrGet( handle, static_cast<UInt32>( OCI::HandleType::Parameter ), (dvoid*)&parameterType, nullptr, static_cast<UInt32>( Attribute::PTYPE ), errorHandle );
        error.CheckResult( rc );
        switch ( parameterType )
        {
            case OCI::ParameterType::Table:
                result = std::make_unique<TableDescriptor>( serviceContext, handle, ownsHandle );
                break;

            case OCI::ParameterType::View:
                result = std::make_unique<ViewDescriptor>( serviceContext, handle, ownsHandle );
                break;

            case OCI::ParameterType::Procedure:
                result = std::make_unique<ProcedureDescriptor>( serviceContext, handle, ownsHandle );
                break;

            case OCI::ParameterType::Function:
                result = std::make_unique<FunctionDescriptor>( serviceContext, handle, ownsHandle );
                break;

            case OCI::ParameterType::Package:
                result = std::make_unique<PackageDescriptor>( serviceContext, handle, ownsHandle );
                break;

            case OCI::ParameterType::Type:
                result = std::make_unique<TypeDescriptor>( serviceContext, handle, ownsHandle );
                break;

            case OCI::ParameterType::Synonym:
                result = std::make_unique<SynonymDescriptor>( serviceContext, handle, ownsHandle );
                break;

            case OCI::ParameterType::Sequence:
                result = std::make_unique<SequenceDescriptor>( serviceContext, handle, ownsHandle );
                break;

            case OCI::ParameterType::Column:
                result = std::make_unique<ColumnDescriptor>( serviceContext, handle, ownsHandle );
                break;

            case OCI::ParameterType::Argument:
                result = std::make_unique<ArgumentDescriptor>( serviceContext, handle, ownsHandle );
                break;

            case OCI::ParameterType::List:
                result = std::make_unique<ListDescriptor>( serviceContext, handle, ownsHandle );
                break;

            case OCI::ParameterType::TypeAttribute:
                result = std::make_unique<TypeAttributeDescriptor>( serviceContext, handle, ownsHandle );
                break;

            case OCI::ParameterType::Collection:
                result = std::make_unique<CollectionDescriptor>( serviceContext, handle, ownsHandle );
                break;

            case OCI::ParameterType::Method:
                result = std::make_unique<MethodDescriptor>( serviceContext, handle, ownsHandle );
                break;

            case OCI::ParameterType::MethodArgument:
                result = std::make_unique<MethodArgumentDescriptor>( serviceContext, handle, ownsHandle );
                break;

            case OCI::ParameterType::MethodResult:
                result = std::make_unique<MethodResultDescriptor>( serviceContext, handle, ownsHandle );
                break;

            case OCI::ParameterType::Schema:
                result = std::make_unique<SchemaDescriptor>( serviceContext, handle, ownsHandle );
                break;

            case OCI::ParameterType::Database:
                result = std::make_unique<DatabaseDescriptor>( serviceContext, handle, ownsHandle );
                break;

            case OCI::ParameterType::Rule:
                result = std::make_unique<RuleDescriptor>( serviceContext, handle, ownsHandle );
                break;

            case OCI::ParameterType::RuleSet:
                result = std::make_unique<RuleSetDescriptor>( serviceContext, handle, ownsHandle );
                break;

            case OCI::ParameterType::EvaluationContext:
                result = std::make_unique<EvaluationContextDescriptor>( serviceContext, handle, ownsHandle );
                break;

            case OCI::ParameterType::TableAlias:
                result = std::make_unique<TableAliasDescriptor>( serviceContext, handle, ownsHandle );
                break;

            case OCI::ParameterType::VariableType:
                result = std::make_unique<VariableTypeDescriptor>( serviceContext, handle, ownsHandle );
                break;

            case OCI::ParameterType::NameValuePair:
                result = std::make_unique<NameValuePairDescriptor>( serviceContext, handle, ownsHandle );
                break;

            default:
                result = std::make_unique<OCI::ParameterDescriptor>( serviceContext, handle, ownsHandle );
        }
        return result;
    }

    std::unique_ptr<ParameterDescriptor> ParameterDescriptor::GetChildDescriptor( size_t index ) const
    {
        auto& error = Error( );
        auto errorHandle = (OCIError*)error.Handle( );
        OCIParam* parameterDescriptorHandle = nullptr;
        
        auto rc = OCIParamGet( (void*)Handle( ), OCI_DTYPE_PARAM, errorHandle, (void**)&parameterDescriptorHandle, (UInt32)index );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
        auto& serviceContext = ServiceContext( );
        auto result = CreateParameter( serviceContext, parameterDescriptorHandle );
        return result;
    }

    std::unique_ptr<ParameterDescriptor> ParameterDescriptor::GetChildDescriptor( void* listHandle, size_t index ) const
    {
        auto& error = Error( );
        auto errorHandle = (OCIError*)error.Handle( );
        OCIParam* parameterDescriptorHandle = nullptr;
        auto rc = OCIParamGet( (void*)listHandle, OCI_DTYPE_PARAM, errorHandle, (void**)&parameterDescriptorHandle, (UInt32)index );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
        auto& serviceContext = ServiceContext( );
        auto result = CreateParameter( serviceContext, parameterDescriptorHandle );
        return result;
    }
}
