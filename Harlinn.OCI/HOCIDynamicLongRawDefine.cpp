#include "pch.h"
#include <HOCIInternal.h>

namespace Harlinn::OCI
{
    DynamicLongRawDefine::DynamicLongRawDefine( const OCI::Statement& statement, size_t size )
        : Base( statement, size )
    {
        //data_.resize( size );
    }

    DynamicLongRawDefine::~DynamicLongRawDefine( )
    {

    }

    void DynamicLongRawDefine::Initialize( UInt32 positon )
    {
        DefineByPos( positon, OCI::OraType::LBI, nullptr, static_cast<Int32>( Common::Core::MaxInt32 ), nullptr, nullptr, OCI_DYNAMIC_FETCH );
        RegisterCallback( );
    }

    Int32 DynamicLongRawDefine::HandleData( UInt32 iter, void** bufpp, UInt32** alenp, Byte* piecep, void** indp, UInt16** rcodep )
    {
        /*
        UInt32* addressOfLastBlockSize = nullptr;
        Byte* addressOfLastBlockData = nullptr;

        switch ( *piecep )
        {
            case OCI_ONE_PIECE: // 0
                //data_[iter] = std::make_unique<Blocks::Stream>( );
                break;
            case OCI_FIRST_PIECE: // 1
                //data_[iter] = std::make_unique<Blocks::Stream>( );
                break;
            case OCI_NEXT_PIECE: // 2
                break;
            case OCI_LAST_PIECE: // 3
                break;
        }


        Blocks::Stream* stream = ( Blocks::Stream* )data_[iter].get( );
        auto& blockManager = stream->Blocks( );
        auto block = blockManager.Append( );

        addressOfLastBlockData = block->data( );
        *addressOfLastBlockSize = static_cast<UInt32>( Blocks::Stream::BlockDataSize );

        *alenp = addressOfLastBlockSize;
        *bufpp = addressOfLastBlockData;
        
        */ 
        return OCI_CONTINUE;
    }

    //IO::StreamBase* DynamicLongRawDefine::AsStream( size_t index ) const
    //{
    //    return data_[index].get( );
    //}

}