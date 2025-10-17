package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleLogHostConfigurationDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  lhc.[Id], \r\n" +
            "  lhc.[RowVersion], \r\n" +
            "  lhc.[Host], \r\n" +
            "  lhc.[Timestamp], \r\n" +
            "  lhc.[Finest], \r\n" +
            "  lhc.[Finer], \r\n" +
            "  lhc.[Fine], \r\n" +
            "  lhc.[Info], \r\n" +
            "  lhc.[Notice], \r\n" +
            "  lhc.[Warn], \r\n" +
            "  lhc.[Error], \r\n" +
            "  lhc.[Severe], \r\n" +
            "  lhc.[Critical], \r\n" +
            "  lhc.[Alert], \r\n" +
            "  lhc.[Fatal], \r\n" +
            "  lhc.[Emergency] \r\n" +
            "FROM [LogHostConfigurationView] lhc \r\n";

    public final static String BaseViewName = "LogHostConfigurationView";
    public final static String ViewAliasName = "lhc";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int HOST_FIELD_ID = 3;
    public final static int TIMESTAMP_FIELD_ID = 4;
    public final static int FINEST_FIELD_ID = 5;
    public final static int FINER_FIELD_ID = 6;
    public final static int FINE_FIELD_ID = 7;
    public final static int INFO_FIELD_ID = 8;
    public final static int NOTICE_FIELD_ID = 9;
    public final static int WARN_FIELD_ID = 10;
    public final static int ERROR_FIELD_ID = 11;
    public final static int SEVERE_FIELD_ID = 12;
    public final static int CRITICAL_FIELD_ID = 13;
    public final static int ALERT_FIELD_ID = 14;
    public final static int FATAL_FIELD_ID = 15;
    public final static int EMERGENCY_FIELD_ID = 16;

    public SimpleLogHostConfigurationDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final Guid getHost() throws SQLException {
        return getGuid( HOST_FIELD_ID );
    }

    public final DateTime getTimestamp() throws SQLException {
        return getDateTimeFromLong( TIMESTAMP_FIELD_ID );
    }

    public final boolean getFinest() throws SQLException {
        return getBoolean( FINEST_FIELD_ID );
    }

    public final boolean getFiner() throws SQLException {
        return getBoolean( FINER_FIELD_ID );
    }

    public final boolean getFine() throws SQLException {
        return getBoolean( FINE_FIELD_ID );
    }

    public final boolean getInfo() throws SQLException {
        return getBoolean( INFO_FIELD_ID );
    }

    public final boolean getNotice() throws SQLException {
        return getBoolean( NOTICE_FIELD_ID );
    }

    public final boolean getWarn() throws SQLException {
        return getBoolean( WARN_FIELD_ID );
    }

    public final boolean getError() throws SQLException {
        return getBoolean( ERROR_FIELD_ID );
    }

    public final boolean getSevere() throws SQLException {
        return getBoolean( SEVERE_FIELD_ID );
    }

    public final boolean getCritical() throws SQLException {
        return getBoolean( CRITICAL_FIELD_ID );
    }

    public final boolean getAlert() throws SQLException {
        return getBoolean( ALERT_FIELD_ID );
    }

    public final boolean getFatal() throws SQLException {
        return getBoolean( FATAL_FIELD_ID );
    }

    public final boolean getEmergency() throws SQLException {
        return getBoolean( EMERGENCY_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.LogHostConfiguration );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getHost( ) );
        destination.writeDateTime( getTimestamp( ) );
        destination.writeBoolean( getFinest( ) );
        destination.writeBoolean( getFiner( ) );
        destination.writeBoolean( getFine( ) );
        destination.writeBoolean( getInfo( ) );
        destination.writeBoolean( getNotice( ) );
        destination.writeBoolean( getWarn( ) );
        destination.writeBoolean( getError( ) );
        destination.writeBoolean( getSevere( ) );
        destination.writeBoolean( getCritical( ) );
        destination.writeBoolean( getAlert( ) );
        destination.writeBoolean( getFatal( ) );
        destination.writeBoolean( getEmergency( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

}
