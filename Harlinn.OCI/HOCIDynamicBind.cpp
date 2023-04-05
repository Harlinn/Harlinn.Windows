#include "pch.h"
#include <HOCIInternal.h>

namespace Harlinn::OCI
{
    Int32 DynamicBind::HandleInDataCallback( void* ctxp, OCIBind* bindp, UInt32 iter, UInt32 index, void** bufpp, UInt32* alenpp, Byte* piecep, void** indpp )
    {
        DynamicBind* context = (DynamicBind*)ctxp;
        if ( context )
        {
            auto result = context->HandleInData( iter, index, bufpp, alenpp, piecep, indpp );
            return result;
        }
        else
        {
            *bufpp = nullptr;
            *alenpp = 0;
            *indpp = nullptr;
            *piecep = OCI_ONE_PIECE;
            return OCI_CONTINUE;
        }

    }
    Int32 DynamicBind::HandleOutDataCallback( void* ctxp, OCIBind* bindp, UInt32 iter, UInt32 index, void** bufpp, UInt32** alenp, Byte* piecep, void** indpp, UInt16** rcodepp )
    {
        DynamicBind* context = (DynamicBind*)ctxp;
        if ( context )
        {
            auto result = context->HandleOutData( iter, index, bufpp, alenp, piecep, indpp, rcodepp );
            return result;
        }
        else
        {
            *bufpp = nullptr;
            *alenp = 0;
            *indpp = nullptr;
            *rcodepp = nullptr;
            *piecep = OCI_ONE_PIECE;
            return OCI_CONTINUE;
        }
        return OCI_CONTINUE;
    }

    Int32 DynamicBind::HandleInData( UInt32 iter, UInt32 index, void** bufpp, UInt32* alenpp, Byte* piecep, void** indpp )
    {
        *bufpp = nullptr;
        *alenpp = 0;
        *indpp = nullptr;
        *piecep = OCI_ONE_PIECE;
        return OCI_CONTINUE;
    }

    Int32 DynamicBind::HandleOutData( UInt32 iter, UInt32 index, void** bufpp, UInt32** alenp, Byte* piecep, void** indpp, UInt16** rcodepp )
    {
        *bufpp = nullptr;
        *alenp = 0;
        *indpp = nullptr;
        *rcodepp = nullptr;
        *piecep = OCI_ONE_PIECE;
        return OCI_CONTINUE;
    }

    void DynamicBind::RegisterCallbacks( )
    {
        auto& error = Error( );
        auto errorHandle = (OCIError*)error.Handle( );
        DynamicBind* ctx = this;
        auto rc = OCIBindDynamic( (OCIBind*)Handle( ), errorHandle, ctx, HandleInDataCallback, ctx, HandleOutDataCallback );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }

    void DynamicBind::BindByPos( UInt32 positon, OraType dataType, Int32 dataSize )
    {
        Base::BindByPos( positon, dataType, nullptr, dataSize, nullptr, nullptr, nullptr, 0, nullptr, OCI_DATA_AT_EXEC );
        RegisterCallbacks( );
    }

    void DynamicBind::BindByName( const std::wstring& name, OraType dataType, Int32 dataSize )
    {
        Base::BindByName( name, dataType, nullptr, dataSize, nullptr, nullptr, nullptr, 0, nullptr, OCI_DATA_AT_EXEC );
        RegisterCallbacks( );
    }

}