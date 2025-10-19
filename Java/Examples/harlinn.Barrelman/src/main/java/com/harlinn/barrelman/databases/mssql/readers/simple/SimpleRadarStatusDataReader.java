package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleRadarStatusDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  rs.[Id], \r\n" +
            "  rs.[RowVersion], \r\n" +
            "  rs.[Radar], \r\n" +
            "  rs.[Timestamp], \r\n" +
            "  rs.[AzimuthCount], \r\n" +
            "  rs.[TriggerCount], \r\n" +
            "  rs.[RotationTime], \r\n" +
            "  rs.[Pulse], \r\n" +
            "  rs.[Tx], \r\n" +
            "  rs.[Tracking] \r\n" +
            "FROM [RadarStatusView] rs \r\n";

    public final static String BaseViewName = "RadarStatusView";
    public final static String ViewAliasName = "rs";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int RADAR_FIELD_ID = 3;
    public final static int TIMESTAMP_FIELD_ID = 4;
    public final static int AZIMUTHCOUNT_FIELD_ID = 5;
    public final static int TRIGGERCOUNT_FIELD_ID = 6;
    public final static int ROTATIONTIME_FIELD_ID = 7;
    public final static int PULSE_FIELD_ID = 8;
    public final static int TX_FIELD_ID = 9;
    public final static int TRACKING_FIELD_ID = 10;

    public SimpleRadarStatusDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final Guid getRadar() throws SQLException {
        return getGuid( RADAR_FIELD_ID );
    }

    public final DateTime getTimestamp() throws SQLException {
        return getDateTimeFromLong( TIMESTAMP_FIELD_ID );
    }

    public final int getAzimuthCount() throws SQLException {
        return getInt32( AZIMUTHCOUNT_FIELD_ID );
    }

    public final int getTriggerCount() throws SQLException {
        return getInt32( TRIGGERCOUNT_FIELD_ID );
    }

    public final TimeSpan getRotationTime() throws SQLException {
        return getTimeSpan( ROTATIONTIME_FIELD_ID );
    }

    public final int getPulse() throws SQLException {
        return getInt32( PULSE_FIELD_ID );
    }

    public final boolean getTx() throws SQLException {
        return getBoolean( TX_FIELD_ID );
    }

    public final boolean getTracking() throws SQLException {
        return getBoolean( TRACKING_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.RadarStatus );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getRadar( ) );
        destination.writeDateTime( getTimestamp( ) );
        destination.writeInt32( getAzimuthCount( ) );
        destination.writeInt32( getTriggerCount( ) );
        destination.writeTimeSpan( getRotationTime( ) );
        destination.writeInt32( getPulse( ) );
        destination.writeBoolean( getTx( ) );
        destination.writeBoolean( getTracking( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

    public RadarStatusObject getDataObject( ) throws SQLException {
            return new RadarStatusObject( ObjectState.Stored, getId( ), getRowVersion( ), getRadar( ), getTimestamp( ), getAzimuthCount( ), getTriggerCount( ), getRotationTime( ), getPulse( ), getTx( ), getTracking( ) );
    }

}
