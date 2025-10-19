package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleRadarCommandReplyGetStatusDataReader extends SimpleRadarCommandReplyDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  rcrgs.[Id], \r\n" +
            "  rcrgs.[EntityType], \r\n" +
            "  rcrgs.[RowVersion], \r\n" +
            "  rcrgs.[Radar], \r\n" +
            "  rcrgs.[Timestamp], \r\n" +
            "  rcrgs.[Command], \r\n" +
            "  rcrgs.[Status], \r\n" +
            "  rcrgs.[Message], \r\n" +
            "  rcrgs.[AzimuthCount], \r\n" +
            "  rcrgs.[TriggerCount], \r\n" +
            "  rcrgs.[RotationCount], \r\n" +
            "  rcrgs.[Pulse], \r\n" +
            "  rcrgs.[Tx] \r\n" +
            "FROM [RadarCommandReplyGetStatusView] rcrgs \r\n";

    public final static String BaseViewName = "RadarCommandReplyGetStatusView";
    public final static String ViewAliasName = "rcrgs";

    public final static int AZIMUTHCOUNT_FIELD_ID = 9;
    public final static int TRIGGERCOUNT_FIELD_ID = 10;
    public final static int ROTATIONCOUNT_FIELD_ID = 11;
    public final static int PULSE_FIELD_ID = 12;
    public final static int TX_FIELD_ID = 13;

    public SimpleRadarCommandReplyGetStatusDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final int getAzimuthCount() throws SQLException {
        return getInt32( AZIMUTHCOUNT_FIELD_ID );
    }

    public final int getTriggerCount() throws SQLException {
        return getInt32( TRIGGERCOUNT_FIELD_ID );
    }

    public final TimeSpan getRotationCount() throws SQLException {
        return getTimeSpan( ROTATIONCOUNT_FIELD_ID );
    }

    public final int getPulse() throws SQLException {
        return getInt32( PULSE_FIELD_ID );
    }

    public final boolean getTx() throws SQLException {
        return getBoolean( TX_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeInt32( getAzimuthCount( ) );
        destination.writeInt32( getTriggerCount( ) );
        destination.writeTimeSpan( getRotationCount( ) );
        destination.writeInt32( getPulse( ) );
        destination.writeBoolean( getTx( ) );
    }

    @Override
    public RadarCommandReplyGetStatusObject getDataObject( ) throws SQLException {
        return new RadarCommandReplyGetStatusObject( ObjectState.Stored, getId( ), getRowVersion( ), getRadar( ), getTimestamp( ), getCommand( ), getStatus( ), getMessage( ), getAzimuthCount( ), getTriggerCount( ), getRotationCount( ), getPulse( ), getTx( ) );
    }

}
