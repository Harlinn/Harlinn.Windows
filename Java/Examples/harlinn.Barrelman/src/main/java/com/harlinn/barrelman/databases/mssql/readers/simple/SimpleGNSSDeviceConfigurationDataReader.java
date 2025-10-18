package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleGNSSDeviceConfigurationDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  gc.[Id], \r\n" +
            "  gc.[RowVersion], \r\n" +
            "  gc.[GNSSDevice], \r\n" +
            "  gc.[Timestamp], \r\n" +
            "  gc.[DefaultLatitude], \r\n" +
            "  gc.[DefaultLongitude], \r\n" +
            "  gc.[DefaultAltitude], \r\n" +
            "  gc.[LatitudeOffset], \r\n" +
            "  gc.[LongitudeOffset], \r\n" +
            "  gc.[AltitudeOffset] \r\n" +
            "FROM [GNSSDeviceConfigurationView] gc \r\n";

    public final static String BaseViewName = "GNSSDeviceConfigurationView";
    public final static String ViewAliasName = "gc";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int GNSSDEVICE_FIELD_ID = 3;
    public final static int TIMESTAMP_FIELD_ID = 4;
    public final static int DEFAULTLATITUDE_FIELD_ID = 5;
    public final static int DEFAULTLONGITUDE_FIELD_ID = 6;
    public final static int DEFAULTALTITUDE_FIELD_ID = 7;
    public final static int LATITUDEOFFSET_FIELD_ID = 8;
    public final static int LONGITUDEOFFSET_FIELD_ID = 9;
    public final static int ALTITUDEOFFSET_FIELD_ID = 10;

    public SimpleGNSSDeviceConfigurationDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final Guid getGNSSDevice() throws SQLException {
        return getGuid( GNSSDEVICE_FIELD_ID );
    }

    public final DateTime getTimestamp() throws SQLException {
        return getDateTimeFromLong( TIMESTAMP_FIELD_ID );
    }

    public final double getDefaultLatitude() throws SQLException {
        return getDouble( DEFAULTLATITUDE_FIELD_ID );
    }

    public final double getDefaultLongitude() throws SQLException {
        return getDouble( DEFAULTLONGITUDE_FIELD_ID );
    }

    public final double getDefaultAltitude() throws SQLException {
        return getDouble( DEFAULTALTITUDE_FIELD_ID );
    }

    public final double getLatitudeOffset() throws SQLException {
        return getDouble( LATITUDEOFFSET_FIELD_ID );
    }

    public final double getLongitudeOffset() throws SQLException {
        return getDouble( LONGITUDEOFFSET_FIELD_ID );
    }

    public final double getAltitudeOffset() throws SQLException {
        return getDouble( ALTITUDEOFFSET_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.GNSSDeviceConfiguration );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getGNSSDevice( ) );
        destination.writeDateTime( getTimestamp( ) );
        destination.writeDouble( getDefaultLatitude( ) );
        destination.writeDouble( getDefaultLongitude( ) );
        destination.writeDouble( getDefaultAltitude( ) );
        destination.writeDouble( getLatitudeOffset( ) );
        destination.writeDouble( getLongitudeOffset( ) );
        destination.writeDouble( getAltitudeOffset( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

    public GNSSDeviceConfigurationObject GetDataObject( ) throws SQLException {
            return new GNSSDeviceConfigurationObject( ObjectState.Stored, getId( ), getRowVersion( ), getGNSSDevice( ), getTimestamp( ), getDefaultLatitude( ), getDefaultLongitude( ), getDefaultAltitude( ), getLatitudeOffset( ), getLongitudeOffset( ), getAltitudeOffset( ) );
    }

}
