package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleLogHostDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  lh.[Id], \r\n" +
            "  lh.[RowVersion], \r\n" +
            "  lh.[ComputerName], \r\n" +
            "  lh.[Description] \r\n" +
            "FROM [LogHostView] lh \r\n";

    public final static String BaseViewName = "LogHostView";
    public final static String ViewAliasName = "lh";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int COMPUTERNAME_FIELD_ID = 3;
    public final static int DESCRIPTION_FIELD_ID = 4;

    public SimpleLogHostDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final String getComputerName() throws SQLException {
        return getString( COMPUTERNAME_FIELD_ID );
    }

    public final String getDescription() throws SQLException {
        return getString( DESCRIPTION_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.LogHost );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeStringUtf8( getComputerName( ) );
        destination.writeStringUtf8( getDescription( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

}
