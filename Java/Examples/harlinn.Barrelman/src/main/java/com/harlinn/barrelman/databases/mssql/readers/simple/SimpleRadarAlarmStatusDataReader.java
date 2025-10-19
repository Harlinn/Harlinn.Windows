package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleRadarAlarmStatusDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  ras.[Id], \r\n" +
            "  ras.[RowVersion], \r\n" +
            "  ras.[Radar], \r\n" +
            "  ras.[Timestamp], \r\n" +
            "  ras.[Type] \r\n" +
            "FROM [RadarAlarmStatusView] ras \r\n";

    public final static String BaseViewName = "RadarAlarmStatusView";
    public final static String ViewAliasName = "ras";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int RADAR_FIELD_ID = 3;
    public final static int TIMESTAMP_FIELD_ID = 4;
    public final static int TYPE_FIELD_ID = 5;

    public SimpleRadarAlarmStatusDataReader( ResultSet resultSet ) {
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

    public final int getTypeField() throws SQLException {
        return getInt32( TYPE_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.RadarAlarmStatus );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getRadar( ) );
        destination.writeDateTime( getTimestamp( ) );
        destination.writeInt32( getTypeField( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

    public RadarAlarmStatusObject getDataObject( ) throws SQLException {
            return new RadarAlarmStatusObject( ObjectState.Stored, getId( ), getRowVersion( ), getRadar( ), getTimestamp( ), getTypeField( ) );
    }

}
