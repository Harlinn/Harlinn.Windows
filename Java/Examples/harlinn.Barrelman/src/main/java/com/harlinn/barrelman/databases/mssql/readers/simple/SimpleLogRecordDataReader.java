package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleLogRecordDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  lr.[Id], \r\n" +
            "  lr.[RowVersion], \r\n" +
            "  lr.[Thread], \r\n" +
            "  lr.[SequenceNumber], \r\n" +
            "  lr.[Level], \r\n" +
            "  lr.[Timestamp], \r\n" +
            "  lr.[Depth], \r\n" +
            "  lr.[Location], \r\n" +
            "  lr.[Message], \r\n" +
            "  lr.[ExceptionString], \r\n" +
            "  lr.[PropertiesData] \r\n" +
            "FROM [LogRecordView] lr \r\n";

    public final static String BaseViewName = "LogRecordView";
    public final static String ViewAliasName = "lr";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int THREAD_FIELD_ID = 3;
    public final static int SEQUENCENUMBER_FIELD_ID = 4;
    public final static int LEVEL_FIELD_ID = 5;
    public final static int TIMESTAMP_FIELD_ID = 6;
    public final static int DEPTH_FIELD_ID = 7;
    public final static int LOCATION_FIELD_ID = 8;
    public final static int MESSAGE_FIELD_ID = 9;
    public final static int EXCEPTIONSTRING_FIELD_ID = 10;
    public final static int PROPERTIESDATA_FIELD_ID = 11;

    public SimpleLogRecordDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final Guid getThread() throws SQLException {
        return getGuid( THREAD_FIELD_ID );
    }

    public final long getSequenceNumber() throws SQLException {
        return getInt64( SEQUENCENUMBER_FIELD_ID );
    }

    public final int getLevel() throws SQLException {
        return getInt32( LEVEL_FIELD_ID );
    }

    public final DateTime getTimestamp() throws SQLException {
        return getDateTimeFromLong( TIMESTAMP_FIELD_ID );
    }

    public final int getDepth() throws SQLException {
        return getInt32( DEPTH_FIELD_ID );
    }

    public final Guid getLocation() throws SQLException {
        return getGuid( LOCATION_FIELD_ID );
    }

    public final String getMessage() throws SQLException {
        return getString( MESSAGE_FIELD_ID );
    }

    public final String getExceptionString() throws SQLException {
        return getString( EXCEPTIONSTRING_FIELD_ID );
    }

    public final byte[] getPropertiesData() throws SQLException {
        return getBinary( PROPERTIESDATA_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.LogRecord );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getThread( ) );
        destination.writeInt64( getSequenceNumber( ) );
        destination.writeInt32( getLevel( ) );
        destination.writeDateTime( getTimestamp( ) );
        destination.writeInt32( getDepth( ) );
        destination.writeGuid( getLocation( ) );
        destination.writeStringUtf8( getMessage( ) );
        destination.writeStringUtf8( getExceptionString( ) );
        destination.writeUInt8Array( getPropertiesData( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

    public LogRecordObject GetDataObject( ) throws SQLException {
            return new LogRecordObject( ObjectState.Stored, getId( ), getRowVersion( ), getThread( ), getSequenceNumber( ), getLevel( ), getTimestamp( ), getDepth( ), getLocation( ), getMessage( ), getExceptionString( ), getPropertiesData( ) );
    }

}
