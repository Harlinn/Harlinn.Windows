package com.harlinn.barrelman.databases.mssql.readers.complex;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class ComplexRadarCommandReplyDataReader extends ResultSetWrapper {

    public final static String BaseQuery = "SELECT \r\n" +
            "  rcr.[Id], \r\n" +
            "  rcr.[EntityType], \r\n" +
            "  rcr.[RowVersion], \r\n" +
            "  rcr.[Radar], \r\n" +
            "  rcr.[Timestamp], \r\n" +
            "  rcr.[Command], \r\n" +
            "  rcr.[Status], \r\n" +
            "  rcrgs.[AzimuthCount], \r\n" +
            "  rcrgs.[TriggerCount], \r\n" +
            "  rcrgs.[RotationCount], \r\n" +
            "  rcrgs.[Pulse], \r\n" +
            "  rcrgs.[Tx], \r\n" +
            "  rcr.[Message] \r\n" +
            "FROM [RadarCommandReplyView] rcr \r\n" +
            "  LEFT JOIN [RadarCommandReplyGetStatus] rcrgs ON(rcr.[Id] = rcrgs.[Id] ) \r\n";

    public final static String BaseViewName = "RadarCommandReplyView";
    public final static String ViewAliasName = "rcr";

    public final static int RCR_ID_FIELD_ID = 1;
    public final static int RCR_KIND_FIELD_ID = 2;
    public final static int RCR_ROWVERSION_FIELD_ID = 3;
    public final static int RCR_RADAR_FIELD_ID = 4;
    public final static int RCR_TIMESTAMP_FIELD_ID = 5;
    public final static int RCR_COMMAND_FIELD_ID = 6;
    public final static int RCR_STATUS_FIELD_ID = 7;
    public final static int RCRGS_AZIMUTHCOUNT_FIELD_ID = 8;
    public final static int RCRGS_TRIGGERCOUNT_FIELD_ID = 9;
    public final static int RCRGS_ROTATIONCOUNT_FIELD_ID = 10;
    public final static int RCRGS_PULSE_FIELD_ID = 11;
    public final static int RCRGS_TX_FIELD_ID = 12;
    public final static int RCR_MESSAGE_FIELD_ID = 13;

    public ComplexRadarCommandReplyDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public Guid getId( ) throws SQLException {
        return getGuid( RCR_ID_FIELD_ID );
    }

    public int getObjectType() throws SQLException {
        return getInt32( RCR_KIND_FIELD_ID );
    }

    public long getRowVersion( ) throws SQLException {
        return getInt64( RCR_ROWVERSION_FIELD_ID );
    }

    public Guid getRadar( ) throws SQLException {
        return getGuid( RCR_RADAR_FIELD_ID );
    }

    public DateTime getTimestamp( ) throws SQLException {
        return getDateTimeFromLong( RCR_TIMESTAMP_FIELD_ID );
    }

    public Guid getCommand( ) throws SQLException {
        return getNullableGuid( RCR_COMMAND_FIELD_ID );
    }

    public int getStatus( ) throws SQLException {
        return getInt32( RCR_STATUS_FIELD_ID );
    }

    public String getMessage( ) throws SQLException {
        return getString( RCR_MESSAGE_FIELD_ID );
    }

    public int getRadarCommandReplyGetStatusAzimuthCount( ) throws SQLException {
        return getInt32( RCRGS_AZIMUTHCOUNT_FIELD_ID );
    }

    public int getRadarCommandReplyGetStatusTriggerCount( ) throws SQLException {
        return getInt32( RCRGS_TRIGGERCOUNT_FIELD_ID );
    }

    public TimeSpan getRadarCommandReplyGetStatusRotationCount( ) throws SQLException {
        return getTimeSpan( RCRGS_ROTATIONCOUNT_FIELD_ID );
    }

    public int getRadarCommandReplyGetStatusPulse( ) throws SQLException {
        return getInt32( RCRGS_PULSE_FIELD_ID );
    }

    public boolean getRadarCommandReplyGetStatusTx( ) throws SQLException {
        return getBoolean( RCRGS_TX_FIELD_ID );
    }

}

