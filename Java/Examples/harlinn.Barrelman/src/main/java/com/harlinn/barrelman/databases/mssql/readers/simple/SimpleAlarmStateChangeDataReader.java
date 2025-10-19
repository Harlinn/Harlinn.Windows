package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleAlarmStateChangeDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  asc.[Id], \r\n" +
            "  asc.[RowVersion], \r\n" +
            "  asc.[Alarm], \r\n" +
            "  asc.[Timestamp], \r\n" +
            "  asc.[State] \r\n" +
            "FROM [AlarmStateChangeView] asc \r\n";

    public final static String BaseViewName = "AlarmStateChangeView";
    public final static String ViewAliasName = "asc";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int ALARM_FIELD_ID = 3;
    public final static int TIMESTAMP_FIELD_ID = 4;
    public final static int STATE_FIELD_ID = 5;

    public SimpleAlarmStateChangeDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final Guid getAlarm() throws SQLException {
        return getGuid( ALARM_FIELD_ID );
    }

    public final DateTime getTimestamp() throws SQLException {
        return getDateTimeFromLong( TIMESTAMP_FIELD_ID );
    }

    public final int getState() throws SQLException {
        return getInt32( STATE_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.AlarmStateChange );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getAlarm( ) );
        destination.writeDateTime( getTimestamp( ) );
        destination.writeInt32( getState( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

    public AlarmStateChangeObject getDataObject( ) throws SQLException {
            return new AlarmStateChangeObject( ObjectState.Stored, getId( ), getRowVersion( ), getAlarm( ), getTimestamp( ), getState( ) );
    }

}
