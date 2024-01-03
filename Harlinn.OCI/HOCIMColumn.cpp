/*
   Copyright 2024 Espen Harlinn

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
    Column::Column( const OCI::ServiceContext* serviceContext, const TableOrView* owner, const OCI::ColumnDescriptor* descriptor )
        : Base( serviceContext, owner, descriptor->Name() ),
          usesCharacterLength_( descriptor->UsesCharacterLength() ),
          characterLength_( descriptor->CharacterLength( ) ),
          length_( descriptor->Length( ) ),
          properties_( descriptor->Properties( ) ),
          isInvisible_( descriptor->IsInvisible( ) ),
          dataType_( descriptor->DataType( ) ),
          precision_( descriptor->Precision( false ) ),
          scale_( descriptor->Scale( ) ),
          nullable_( descriptor->Nullable( ) ),
          typeName_( descriptor->TypeName( ) ),
          schemaName_( descriptor->SchemaName( ) ),
          characterSetForm_( descriptor->CharacterSetForm( ) )
    {
    }
}