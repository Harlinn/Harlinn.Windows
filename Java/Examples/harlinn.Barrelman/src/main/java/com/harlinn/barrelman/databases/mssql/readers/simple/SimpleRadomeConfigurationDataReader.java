package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleRadomeConfigurationDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  rc.[Id], \r\n" +
            "  rc.[RowVersion], \r\n" +
            "  rc.[Radome], \r\n" +
            "  rc.[Timestamp], \r\n" +
            "  rc.[Interval], \r\n" +
            "  rc.[LowPressureLimit], \r\n" +
            "  rc.[HighPressureLimit], \r\n" +
            "  rc.[LowTemperatureLimit], \r\n" +
            "  rc.[HighTemperatureLimit] \r\n" +
            "FROM [RadomeConfigurationView] rc \r\n";

    public final static String BaseViewName = "RadomeConfigurationView";
    public final static String ViewAliasName = "rc";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int RADOME_FIELD_ID = 3;
    public final static int TIMESTAMP_FIELD_ID = 4;
    public final static int INTERVAL_FIELD_ID = 5;
    public final static int LOWPRESSURELIMIT_FIELD_ID = 6;
    public final static int HIGHPRESSURELIMIT_FIELD_ID = 7;
    public final static int LOWTEMPERATURELIMIT_FIELD_ID = 8;
    public final static int HIGHTEMPERATURELIMIT_FIELD_ID = 9;

    public SimpleRadomeConfigurationDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final Guid getRadome() throws SQLException {
        return getGuid( RADOME_FIELD_ID );
    }

    public final DateTime getTimestamp() throws SQLException {
        return getDateTimeFromLong( TIMESTAMP_FIELD_ID );
    }

    public final TimeSpan getInterval() throws SQLException {
        return getTimeSpan( INTERVAL_FIELD_ID );
    }

    public final double getLowPressureLimit() throws SQLException {
        return getDouble( LOWPRESSURELIMIT_FIELD_ID );
    }

    public final double getHighPressureLimit() throws SQLException {
        return getDouble( HIGHPRESSURELIMIT_FIELD_ID );
    }

    public final double getLowTemperatureLimit() throws SQLException {
        return getDouble( LOWTEMPERATURELIMIT_FIELD_ID );
    }

    public final double getHighTemperatureLimit() throws SQLException {
        return getDouble( HIGHTEMPERATURELIMIT_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.RadomeConfiguration );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getRadome( ) );
        destination.writeDateTime( getTimestamp( ) );
        destination.writeTimeSpan( getInterval( ) );
        destination.writeDouble( getLowPressureLimit( ) );
        destination.writeDouble( getHighPressureLimit( ) );
        destination.writeDouble( getLowTemperatureLimit( ) );
        destination.writeDouble( getHighTemperatureLimit( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

    public RadomeConfigurationObject GetDataObject( ) throws SQLException {
            return new RadomeConfigurationObject( ObjectState.Stored, getId( ), getRowVersion( ), getRadome( ), getTimestamp( ), getInterval( ), getLowPressureLimit( ), getHighPressureLimit( ), getLowTemperatureLimit( ), getHighTemperatureLimit( ) );
    }

}
