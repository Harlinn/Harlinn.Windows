package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleLogThreadDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  lt.[Id], \r\n" +
            "  lt.[RowVersion], \r\n" +
            "  lt.[Process], \r\n" +
            "  lt.[Started], \r\n" +
            "  lt.[Stopped], \r\n" +
            "  lt.[ThreadId], \r\n" +
            "  lt.[Name] \r\n" +
            "FROM [LogThreadView] lt \r\n";

    public final static String BaseViewName = "LogThreadView";
    public final static String ViewAliasName = "lt";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int PROCESS_FIELD_ID = 3;
    public final static int STARTED_FIELD_ID = 4;
    public final static int STOPPED_FIELD_ID = 5;
    public final static int THREADID_FIELD_ID = 6;
    public final static int NAME_FIELD_ID = 7;

    public SimpleLogThreadDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final Guid getProcess() throws SQLException {
        return getGuid( PROCESS_FIELD_ID );
    }

    public final DateTime getStarted() throws SQLException {
        return getDateTimeFromLong( STARTED_FIELD_ID );
    }

    public final DateTime getStopped() throws SQLException {
        return getNullableDateTimeFromLong( STOPPED_FIELD_ID );
    }

    public final long getThreadId() throws SQLException {
        return getInt64( THREADID_FIELD_ID );
    }

    public final String getName() throws SQLException {
        return getString( NAME_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.LogThread );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getProcess( ) );
        destination.writeDateTime( getStarted( ) );
        destination.writeNullableDateTime( getStopped( ) );
        destination.writeInt64( getThreadId( ) );
        destination.writeStringUtf8( getName( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

    public LogThreadObject getDataObject( ) throws SQLException {
            return new LogThreadObject( ObjectState.Stored, getId( ), getRowVersion( ), getProcess( ), getStarted( ), getStopped( ), getThreadId( ), getName( ) );
    }

}
