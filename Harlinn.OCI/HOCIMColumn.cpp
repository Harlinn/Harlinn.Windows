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