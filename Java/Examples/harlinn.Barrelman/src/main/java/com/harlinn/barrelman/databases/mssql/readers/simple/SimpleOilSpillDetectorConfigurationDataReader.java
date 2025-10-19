package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleOilSpillDetectorConfigurationDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  osdc.[Id], \r\n" +
            "  osdc.[RowVersion], \r\n" +
            "  osdc.[OilSpillDetector], \r\n" +
            "  osdc.[Timestamp], \r\n" +
            "  osdc.[Range], \r\n" +
            "  osdc.[StartAngle], \r\n" +
            "  osdc.[EndAngle], \r\n" +
            "  osdc.[StartRange], \r\n" +
            "  osdc.[EndRange], \r\n" +
            "  osdc.[UpdateRate], \r\n" +
            "  osdc.[StatusSendTime], \r\n" +
            "  osdc.[DrawBorder], \r\n" +
            "  osdc.[Colors], \r\n" +
            "  osdc.[SendToServer], \r\n" +
            "  osdc.[Directory], \r\n" +
            "  osdc.[TransparentWater], \r\n" +
            "  osdc.[SavePictures], \r\n" +
            "  osdc.[SendAsTarget], \r\n" +
            "  osdc.[WriteLog], \r\n" +
            "  osdc.[TargetFilePrefix], \r\n" +
            "  osdc.[TargetMMSI], \r\n" +
            "  osdc.[Latitude], \r\n" +
            "  osdc.[Longitude], \r\n" +
            "  osdc.[TestSourceEnabled], \r\n" +
            "  osdc.[ProxyServer], \r\n" +
            "  osdc.[UseProxyServer] \r\n" +
            "FROM [OilSpillDetectorConfigurationView] osdc \r\n";

    public final static String BaseViewName = "OilSpillDetectorConfigurationView";
    public final static String ViewAliasName = "osdc";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int OILSPILLDETECTOR_FIELD_ID = 3;
    public final static int TIMESTAMP_FIELD_ID = 4;
    public final static int RANGE_FIELD_ID = 5;
    public final static int STARTANGLE_FIELD_ID = 6;
    public final static int ENDANGLE_FIELD_ID = 7;
    public final static int STARTRANGE_FIELD_ID = 8;
    public final static int ENDRANGE_FIELD_ID = 9;
    public final static int UPDATERATE_FIELD_ID = 10;
    public final static int STATUSSENDTIME_FIELD_ID = 11;
    public final static int DRAWBORDER_FIELD_ID = 12;
    public final static int COLORS_FIELD_ID = 13;
    public final static int SENDTOSERVER_FIELD_ID = 14;
    public final static int DIRECTORY_FIELD_ID = 15;
    public final static int TRANSPARENTWATER_FIELD_ID = 16;
    public final static int SAVEPICTURES_FIELD_ID = 17;
    public final static int SENDASTARGET_FIELD_ID = 18;
    public final static int WRITELOG_FIELD_ID = 19;
    public final static int TARGETFILEPREFIX_FIELD_ID = 20;
    public final static int TARGETMMSI_FIELD_ID = 21;
    public final static int LATITUDE_FIELD_ID = 22;
    public final static int LONGITUDE_FIELD_ID = 23;
    public final static int TESTSOURCEENABLED_FIELD_ID = 24;
    public final static int PROXYSERVER_FIELD_ID = 25;
    public final static int USEPROXYSERVER_FIELD_ID = 26;

    public SimpleOilSpillDetectorConfigurationDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final Guid getOilSpillDetector() throws SQLException {
        return getGuid( OILSPILLDETECTOR_FIELD_ID );
    }

    public final DateTime getTimestamp() throws SQLException {
        return getDateTimeFromLong( TIMESTAMP_FIELD_ID );
    }

    public final double getRange() throws SQLException {
        return getDouble( RANGE_FIELD_ID );
    }

    public final double getStartAngle() throws SQLException {
        return getDouble( STARTANGLE_FIELD_ID );
    }

    public final double getEndAngle() throws SQLException {
        return getDouble( ENDANGLE_FIELD_ID );
    }

    public final double getStartRange() throws SQLException {
        return getDouble( STARTRANGE_FIELD_ID );
    }

    public final double getEndRange() throws SQLException {
        return getDouble( ENDRANGE_FIELD_ID );
    }

    public final int getUpdateRate() throws SQLException {
        return getInt32( UPDATERATE_FIELD_ID );
    }

    public final TimeSpan getStatusSendTime() throws SQLException {
        return getTimeSpan( STATUSSENDTIME_FIELD_ID );
    }

    public final boolean getDrawBorder() throws SQLException {
        return getBoolean( DRAWBORDER_FIELD_ID );
    }

    public final byte[] getColors() throws SQLException {
        return getBinary( COLORS_FIELD_ID );
    }

    public final boolean getSendToServer() throws SQLException {
        return getBoolean( SENDTOSERVER_FIELD_ID );
    }

    public final String getDirectory() throws SQLException {
        return getString( DIRECTORY_FIELD_ID );
    }

    public final boolean getTransparentWater() throws SQLException {
        return getBoolean( TRANSPARENTWATER_FIELD_ID );
    }

    public final boolean getSavePictures() throws SQLException {
        return getBoolean( SAVEPICTURES_FIELD_ID );
    }

    public final boolean getSendAsTarget() throws SQLException {
        return getBoolean( SENDASTARGET_FIELD_ID );
    }

    public final boolean getWriteLog() throws SQLException {
        return getBoolean( WRITELOG_FIELD_ID );
    }

    public final String getTargetFilePrefix() throws SQLException {
        return getString( TARGETFILEPREFIX_FIELD_ID );
    }

    public final Guid getTargetMMSI() throws SQLException {
        return getNullableGuid( TARGETMMSI_FIELD_ID );
    }

    public final double getLatitude() throws SQLException {
        return getDouble( LATITUDE_FIELD_ID );
    }

    public final double getLongitude() throws SQLException {
        return getDouble( LONGITUDE_FIELD_ID );
    }

    public final boolean getTestSourceEnabled() throws SQLException {
        return getBoolean( TESTSOURCEENABLED_FIELD_ID );
    }

    public final String getProxyServer() throws SQLException {
        return getString( PROXYSERVER_FIELD_ID );
    }

    public final boolean getUseProxyServer() throws SQLException {
        return getBoolean( USEPROXYSERVER_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.OilSpillDetectorConfiguration );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getOilSpillDetector( ) );
        destination.writeDateTime( getTimestamp( ) );
        destination.writeDouble( getRange( ) );
        destination.writeDouble( getStartAngle( ) );
        destination.writeDouble( getEndAngle( ) );
        destination.writeDouble( getStartRange( ) );
        destination.writeDouble( getEndRange( ) );
        destination.writeInt32( getUpdateRate( ) );
        destination.writeTimeSpan( getStatusSendTime( ) );
        destination.writeBoolean( getDrawBorder( ) );
        destination.writeUInt8Array( getColors( ) );
        destination.writeBoolean( getSendToServer( ) );
        destination.writeStringUtf8( getDirectory( ) );
        destination.writeBoolean( getTransparentWater( ) );
        destination.writeBoolean( getSavePictures( ) );
        destination.writeBoolean( getSendAsTarget( ) );
        destination.writeBoolean( getWriteLog( ) );
        destination.writeStringUtf8( getTargetFilePrefix( ) );
        destination.writeNullableGuid( getTargetMMSI( ) );
        destination.writeDouble( getLatitude( ) );
        destination.writeDouble( getLongitude( ) );
        destination.writeBoolean( getTestSourceEnabled( ) );
        destination.writeStringUtf8( getProxyServer( ) );
        destination.writeBoolean( getUseProxyServer( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

    public OilSpillDetectorConfigurationObject getDataObject( ) throws SQLException {
            return new OilSpillDetectorConfigurationObject( ObjectState.Stored, getId( ), getRowVersion( ), getOilSpillDetector( ), getTimestamp( ), getRange( ), getStartAngle( ), getEndAngle( ), getStartRange( ), getEndRange( ), getUpdateRate( ), getStatusSendTime( ), getDrawBorder( ), getColors( ), getSendToServer( ), getDirectory( ), getTransparentWater( ), getSavePictures( ), getSendAsTarget( ), getWriteLog( ), getTargetFilePrefix( ), getTargetMMSI( ), getLatitude( ), getLongitude( ), getTestSourceEnabled( ), getProxyServer( ), getUseProxyServer( ) );
    }

}
