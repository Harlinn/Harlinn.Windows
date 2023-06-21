#include "pch.h"
#include <HOCIInternal.h>

namespace Harlinn::OCI
{
    RefCursorBind::~RefCursorBind( )
    {
        if ( !cursorStatement_ && boundStatementhandle_ )
        {
            auto& error = Error( );
            auto errorHandle = (OCIError*)error.Handle( );
            OCIStmtRelease( (OCIStmt*)boundStatementhandle_, errorHandle, nullptr, 0, OCI_DEFAULT );
        }
    }

    void RefCursorBind::Bind( UInt32 positon, UInt32 iters )
    {
        
        auto& environment = Environment( );
        auto environmentHandle = environment.Handle( );
        OCIStmt* tmp = nullptr;
        auto rc = OCIHandleAlloc( environmentHandle, (void**)( &tmp ), OCI_HTYPE_STMT, 0, NULL );
        if ( rc < OCI_SUCCESS )
        {
            ThrowOracleExceptionOnError( environmentHandle, rc );
        }
        boundStatementhandle_ = tmp;
        BindByPos( positon, OCI::OraType::RSET, &boundStatementhandle_, sizeof( boundStatementhandle_ ), &indicator_ );
    }
    void RefCursorBind::Bind( const WideString& name, UInt32 iters )
    {
        BindByName( name, OCI::OraType::RSET, &boundStatementhandle_, sizeof( boundStatementhandle_ ), &indicator_ );
    }

    const OCI::Statement& RefCursorBind::CursorStatement( )
    {
        if ( !cursorStatement_ && boundStatementhandle_ )
        {
            auto& statement = Statement( );
            if ( statement )
            {
                auto& serviceContext = statement.ServiceContext( );
                if ( serviceContext )
                {
                    cursorStatement_ = OCI::Statement( serviceContext, boundStatementhandle_, true );
                }
            }
        }
        return cursorStatement_;
    }
}