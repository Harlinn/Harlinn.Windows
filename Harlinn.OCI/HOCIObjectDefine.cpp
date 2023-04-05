#include "pch.h"
#include <HOCIInternal.h>

namespace Harlinn::OCI
{
    ObjectDefine::ObjectDefine( const OCI::Statement& statement, const OCI::Type& type )
        : Base( statement ), type_( &type )
    {
    }

    void ObjectDefine::Initialize( UInt32 positon )
    {
        //DefineByPos( positon, OCI::OraType::NTY, data_.data( ), sizeof( void* ) );
    }


    OCI::Object* ObjectDefine::AsObject( ) const
    {
        return nullptr;
    }
}