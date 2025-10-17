package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleLogProcessDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  lp.[Id], \r\n" +
            "  lp.[RowVersion], \r\n" +
            "  lp.[Application], \r\n" +
            "  lp.[Host], \r\n" +
            "  lp.[Started], \r\n" +
            "  lp.[Stopped], \r\n" +
            "  lp.[ProcessId], \r\n" +
            "  lp.[Path], \r\n" +
            "  lp.[Identity] \r\n" +
            "FROM [LogProcessView] lp \r\n";

    public final static String BaseViewName = "LogProcessView";
    public final static String ViewAliasName = "lp";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int APPLICATION_FIELD_ID = 3;
    public final static int HOST_FIELD_ID = 4;
    public final static int STARTED_FIELD_ID = 5;
    public final static int STOPPED_FIELD_ID = 6;
    public final static int PROCESSID_FIELD_ID = 7;
    public final static int PATH_FIELD_ID = 8;
    public final static int IDENTITY_FIELD_ID = 9;

    public SimpleLogProcessDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final Guid getApplication() throws SQLException {
        return getGuid( APPLICATION_FIELD_ID );
    }

    public final Guid getHost() throws SQLException {
        return getNullableGuid( HOST_FIELD_ID );
    }

    public final DateTime getStarted() throws SQLException {
        return getDateTimeFromLong( STARTED_FIELD_ID );
    }

    public final DateTime getStopped() throws SQLException {
        return getNullableDateTimeFromLong( STOPPED_FIELD_ID );
    }

    public final long getProcessId() throws SQLException {
        return getInt64( PROCESSID_FIELD_ID );
    }

    public final String getPath() throws SQLException {
        return getString( PATH_FIELD_ID );
    }

    public final String getIdentity() throws SQLException {
        return getString( IDENTITY_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.LogProcess );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getApplication( ) );
        destination.writeNullableGuid( getHost( ) );
        destination.writeDateTime( getStarted( ) );
        destination.writeNullableDateTime( getStopped( ) );
        destination.writeInt64( getProcessId( ) );
        destination.writeStringUtf8( getPath( ) );
        destination.writeStringUtf8( getIdentity( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

}
