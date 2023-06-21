#include "pch.h"
#include <HOCIInternal.h>

namespace Harlinn::OCI
{
    BinaryDynamicBind::~BinaryDynamicBind( )
    {
    }

    void BinaryDynamicBind::Bind( UInt32 positon, UInt32 iters )
    {
        BindByPos( positon, ExternalType, ( Common::Core::MaxInt32 - 1 ) );

    }

    void BinaryDynamicBind::Bind( const WideString& name, UInt32 iters )
    {
        BindByName( name, ExternalType, 0 );
    }

    Int32 BinaryDynamicBind::HandleInData( UInt32 iter, UInt32 index, void** bufpp, UInt32* alenpp, Byte* piecep, void** indpp )
    {
        auto& info = data_[iter];
        if ( info.bufferSize_ > blockSize_ )
        {
            auto remaining = info.bufferSize_ - info.position_;
            *bufpp = (void*)&info.buffer_[info.position_];
            auto count = blockSize_;
            if ( remaining <= blockSize_ )
            {
                count = remaining;
                *piecep = OCI_LAST_PIECE;
            }
            else if ( info.position_ == 0 )
            {
                *piecep = OCI_FIRST_PIECE;
            }
            else
            {
                *piecep = OCI_NEXT_PIECE;
            }

            *alenpp = static_cast<UInt32>( count );
            info.position_ += count;
        }
        else
        {
            *bufpp = (void*)info.buffer_;
            *alenpp = static_cast<UInt32>( info.bufferSize_ );
            *piecep = OCI_ONE_PIECE;
        }
        *indpp = (dvoid*)0;
        return OCI_CONTINUE;
    }
}