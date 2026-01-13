/*
   Copyright 2024-2026 Espen Harlinn

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

#include "pch.h"
#include <HOCIInternal.h>

namespace Harlinn::OCI::Metadata
{
    Schema::Schema( const OCI::ServiceContext* serviceContext, const Database* owner, const OCI::SchemaDescriptor* descriptor )
        : Base( serviceContext, owner, descriptor->Schema() )
    { }



    Schema::~Schema( ) = default;

    Schema::SchemaObjectContainer Schema::Objects( ) const
    {
        SchemaObjectContainer result;

        auto* serviceContext = ServiceContext( );
        auto describe = serviceContext->Describe( Name( ), OCI::ParameterType::Schema );
        auto schemaDescriptor = describe.Descriptor<SchemaDescriptor>( );
        auto objectDescriptors = schemaDescriptor->Objects( );
        for ( auto& objectDescriptor : objectDescriptors )
        {
            auto parameterType = objectDescriptor->ParameterType( );
            switch ( parameterType )
            {
                case ParameterType::Unknown:
                {
                    auto schemaObject = std::make_unique<SchemaObject>( serviceContext, this, objectDescriptor.get( ) );
                    result.emplace( schemaObject->Name( ), std::move( schemaObject ) );
                }
                break;
                case ParameterType::Table:
                {
                    auto schemaObject = std::make_unique<Table>( serviceContext, this, static_cast<OCI::TableDescriptor*>( objectDescriptor.get( ) ) );
                    result.emplace( schemaObject->Name( ), std::move( schemaObject ) );
                }
                break;
                case ParameterType::View:
                {
                    auto schemaObject = std::make_unique<View>( serviceContext, this, static_cast<OCI::ViewDescriptor*>( objectDescriptor.get( ) ) );
                    result.emplace( schemaObject->Name( ), std::move( schemaObject ) );
                }
                break;
                case ParameterType::Procedure:
                {
                    auto schemaObject = std::make_unique<Procedure>( serviceContext, this, static_cast<OCI::ProcedureDescriptor*>( objectDescriptor.get( ) ) );
                    result.emplace( schemaObject->Name( ), std::move( schemaObject ) );
                }
                break;
                case ParameterType::Function:
                {
                    auto schemaObject = std::make_unique<Function>( serviceContext, this, static_cast<OCI::FunctionDescriptor*>( objectDescriptor.get( ) ) );
                    result.emplace( schemaObject->Name( ), std::move( schemaObject ) );
                }
                break;
                case ParameterType::Package:
                {
                    auto schemaObject = std::make_unique<Package>( serviceContext, this, static_cast<OCI::PackageDescriptor*>( objectDescriptor.get( ) ) );
                    result.emplace( schemaObject->Name( ), std::move( schemaObject ) );
                }
                break;
                case ParameterType::Type:
                {
                    auto schemaObject = std::make_unique<Type>( serviceContext, this, static_cast<OCI::TypeDescriptor*>( objectDescriptor.get( ) ) );
                    result.emplace( schemaObject->Name( ), std::move( schemaObject ) );
                }
                break;
                case ParameterType::Synonym:
                {
                    auto schemaObject = std::make_unique<Synonym>( serviceContext, this, static_cast<OCI::SynonymDescriptor*>( objectDescriptor.get( ) ) );
                    result.emplace( schemaObject->Name( ), std::move( schemaObject ) );
                }
                break;
                case ParameterType::Sequence:
                {
                    auto schemaObject = std::make_unique<Sequence>( serviceContext, this, static_cast<OCI::SequenceDescriptor*>( objectDescriptor.get( ) ) );
                    result.emplace( schemaObject->Name( ), std::move( schemaObject ) );
                }
                break;
                default:
                {
#ifdef _DEBUG
                    auto& schema = Name( );
                    auto name = objectDescriptor->Name( );
                    wprintf( L"Unsupported schema object type:%d, Schema:%s, Name:%s\n", static_cast<int>(parameterType), schema.c_str(), name.c_str() );
#endif
                }
                break;
            }
        }

        return result;
    }


}