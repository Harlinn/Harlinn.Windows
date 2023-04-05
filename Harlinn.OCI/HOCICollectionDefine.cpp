#include "pch.h"
#include <HOCIInternal.h>

namespace Harlinn::OCI
{
    CollectionDefine::CollectionDefine( const OCI::Statement& statement, const OCI::Type& type )
        : Base( statement ), type_( &type )
    {
    }

    void CollectionDefine::Initialize( UInt32 positon )
    {
    }

    OCI::Collection* CollectionDefine::AsCollection( ) const
    {
        return nullptr;
    }
}