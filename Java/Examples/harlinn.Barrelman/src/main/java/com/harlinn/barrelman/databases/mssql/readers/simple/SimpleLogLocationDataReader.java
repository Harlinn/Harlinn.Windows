package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleLogLocationDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  ll.[Id], \r\n" +
            "  ll.[RowVersion], \r\n" +
            "  ll.[FileName], \r\n" +
            "  ll.[LineNumber], \r\n" +
            "  ll.[Namespace], \r\n" +
            "  ll.[ClassName], \r\n" +
            "  ll.[MethodName] \r\n" +
            "FROM [LogLocationView] ll \r\n";

    public final static String BaseViewName = "LogLocationView";
    public final static String ViewAliasName = "ll";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int FILENAME_FIELD_ID = 3;
    public final static int LINENUMBER_FIELD_ID = 4;
    public final static int NAMESPACE_FIELD_ID = 5;
    public final static int CLASSNAME_FIELD_ID = 6;
    public final static int METHODNAME_FIELD_ID = 7;

    public SimpleLogLocationDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final String getFileName() throws SQLException {
        return getString( FILENAME_FIELD_ID );
    }

    public final int getLineNumber() throws SQLException {
        return getInt32( LINENUMBER_FIELD_ID );
    }

    public final String getNamespace() throws SQLException {
        return getString( NAMESPACE_FIELD_ID );
    }

    public final String getClassName() throws SQLException {
        return getString( CLASSNAME_FIELD_ID );
    }

    public final String getMethodName() throws SQLException {
        return getString( METHODNAME_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.LogLocation );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeStringUtf8( getFileName( ) );
        destination.writeInt32( getLineNumber( ) );
        destination.writeStringUtf8( getNamespace( ) );
        destination.writeStringUtf8( getClassName( ) );
        destination.writeStringUtf8( getMethodName( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

}
