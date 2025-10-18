package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleRadarConfigurationDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  rc.[Id], \r\n" +
            "  rc.[RowVersion], \r\n" +
            "  rc.[Radar], \r\n" +
            "  rc.[Timestamp], \r\n" +
            "  rc.[RadarProtocolVersion], \r\n" +
            "  rc.[RadarIPAddress], \r\n" +
            "  rc.[RadarPort], \r\n" +
            "  rc.[RadarConfigurationPort], \r\n" +
            "  rc.[SkipMagicTimeout], \r\n" +
            "  rc.[ReadTimeout], \r\n" +
            "  rc.[SynchronizationInterval], \r\n" +
            "  rc.[TargetsRefreshRate], \r\n" +
            "  rc.[Range], \r\n" +
            "  rc.[SectorCount], \r\n" +
            "  rc.[SectorOffset], \r\n" +
            "  rc.[ImageColor], \r\n" +
            "  rc.[ImageSubstitutionColor], \r\n" +
            "  rc.[TransparentColor], \r\n" +
            "  rc.[ImageScaleFactorX], \r\n" +
            "  rc.[ImageOffsetX], \r\n" +
            "  rc.[ImageScaleFactorY], \r\n" +
            "  rc.[ImageOffsetY], \r\n" +
            "  rc.[RadarImageType], \r\n" +
            "  rc.[TrackColor], \r\n" +
            "  rc.[VectorColor], \r\n" +
            "  rc.[EnableNmea], \r\n" +
            "  rc.[NmeaReceiverIPAddress], \r\n" +
            "  rc.[NmeaReceiverPort], \r\n" +
            "  rc.[NmeaReceiverSourceId] \r\n" +
            "FROM [RadarConfigurationView] rc \r\n";

    public final static String BaseViewName = "RadarConfigurationView";
    public final static String ViewAliasName = "rc";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int RADAR_FIELD_ID = 3;
    public final static int TIMESTAMP_FIELD_ID = 4;
    public final static int RADARPROTOCOLVERSION_FIELD_ID = 5;
    public final static int RADARIPADDRESS_FIELD_ID = 6;
    public final static int RADARPORT_FIELD_ID = 7;
    public final static int RADARCONFIGURATIONPORT_FIELD_ID = 8;
    public final static int SKIPMAGICTIMEOUT_FIELD_ID = 9;
    public final static int READTIMEOUT_FIELD_ID = 10;
    public final static int SYNCHRONIZATIONINTERVAL_FIELD_ID = 11;
    public final static int TARGETSREFRESHRATE_FIELD_ID = 12;
    public final static int RANGE_FIELD_ID = 13;
    public final static int SECTORCOUNT_FIELD_ID = 14;
    public final static int SECTOROFFSET_FIELD_ID = 15;
    public final static int IMAGECOLOR_FIELD_ID = 16;
    public final static int IMAGESUBSTITUTIONCOLOR_FIELD_ID = 17;
    public final static int TRANSPARENTCOLOR_FIELD_ID = 18;
    public final static int IMAGESCALEFACTORX_FIELD_ID = 19;
    public final static int IMAGEOFFSETX_FIELD_ID = 20;
    public final static int IMAGESCALEFACTORY_FIELD_ID = 21;
    public final static int IMAGEOFFSETY_FIELD_ID = 22;
    public final static int RADARIMAGETYPE_FIELD_ID = 23;
    public final static int TRACKCOLOR_FIELD_ID = 24;
    public final static int VECTORCOLOR_FIELD_ID = 25;
    public final static int ENABLENMEA_FIELD_ID = 26;
    public final static int NMEARECEIVERIPADDRESS_FIELD_ID = 27;
    public final static int NMEARECEIVERPORT_FIELD_ID = 28;
    public final static int NMEARECEIVERSOURCEID_FIELD_ID = 29;

    public SimpleRadarConfigurationDataReader( ResultSet resultSet ) {
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

    public final int getRadarProtocolVersion() throws SQLException {
        return getInt32( RADARPROTOCOLVERSION_FIELD_ID );
    }

    public final String getRadarIPAddress() throws SQLException {
        return getString( RADARIPADDRESS_FIELD_ID );
    }

    public final int getRadarPort() throws SQLException {
        return getInt32( RADARPORT_FIELD_ID );
    }

    public final int getRadarConfigurationPort() throws SQLException {
        return getInt32( RADARCONFIGURATIONPORT_FIELD_ID );
    }

    public final TimeSpan getSkipMagicTimeout() throws SQLException {
        return getTimeSpan( SKIPMAGICTIMEOUT_FIELD_ID );
    }

    public final TimeSpan getReadTimeout() throws SQLException {
        return getTimeSpan( READTIMEOUT_FIELD_ID );
    }

    public final TimeSpan getSynchronizationInterval() throws SQLException {
        return getTimeSpan( SYNCHRONIZATIONINTERVAL_FIELD_ID );
    }

    public final int getTargetsRefreshRate() throws SQLException {
        return getInt32( TARGETSREFRESHRATE_FIELD_ID );
    }

    public final int getRange() throws SQLException {
        return getInt32( RANGE_FIELD_ID );
    }

    public final int getSectorCount() throws SQLException {
        return getInt32( SECTORCOUNT_FIELD_ID );
    }

    public final int getSectorOffset() throws SQLException {
        return getInt32( SECTOROFFSET_FIELD_ID );
    }

    public final int getImageColor() throws SQLException {
        return getUInt32( IMAGECOLOR_FIELD_ID );
    }

    public final Integer getImageSubstitutionColor() throws SQLException {
        return getNullableUInt32( IMAGESUBSTITUTIONCOLOR_FIELD_ID );
    }

    public final int getTransparentColor() throws SQLException {
        return getUInt32( TRANSPARENTCOLOR_FIELD_ID );
    }

    public final double getImageScaleFactorX() throws SQLException {
        return getDouble( IMAGESCALEFACTORX_FIELD_ID );
    }

    public final double getImageOffsetX() throws SQLException {
        return getDouble( IMAGEOFFSETX_FIELD_ID );
    }

    public final double getImageScaleFactorY() throws SQLException {
        return getDouble( IMAGESCALEFACTORY_FIELD_ID );
    }

    public final double getImageOffsetY() throws SQLException {
        return getDouble( IMAGEOFFSETY_FIELD_ID );
    }

    public final int getRadarImageType() throws SQLException {
        return getInt32( RADARIMAGETYPE_FIELD_ID );
    }

    public final int getTrackColor() throws SQLException {
        return getUInt32( TRACKCOLOR_FIELD_ID );
    }

    public final int getVectorColor() throws SQLException {
        return getUInt32( VECTORCOLOR_FIELD_ID );
    }

    public final boolean getEnableNmea() throws SQLException {
        return getBoolean( ENABLENMEA_FIELD_ID );
    }

    public final String getNmeaReceiverIPAddress() throws SQLException {
        return getString( NMEARECEIVERIPADDRESS_FIELD_ID );
    }

    public final int getNmeaReceiverPort() throws SQLException {
        return getInt32( NMEARECEIVERPORT_FIELD_ID );
    }

    public final String getNmeaReceiverSourceId() throws SQLException {
        return getString( NMEARECEIVERSOURCEID_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.RadarConfiguration );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getRadar( ) );
        destination.writeDateTime( getTimestamp( ) );
        destination.writeInt32( getRadarProtocolVersion( ) );
        destination.writeStringUtf8( getRadarIPAddress( ) );
        destination.writeInt32( getRadarPort( ) );
        destination.writeInt32( getRadarConfigurationPort( ) );
        destination.writeTimeSpan( getSkipMagicTimeout( ) );
        destination.writeTimeSpan( getReadTimeout( ) );
        destination.writeTimeSpan( getSynchronizationInterval( ) );
        destination.writeInt32( getTargetsRefreshRate( ) );
        destination.writeInt32( getRange( ) );
        destination.writeInt32( getSectorCount( ) );
        destination.writeInt32( getSectorOffset( ) );
        destination.writeUInt32( getImageColor( ) );
        destination.writeNullableUInt32( getImageSubstitutionColor( ) );
        destination.writeUInt32( getTransparentColor( ) );
        destination.writeDouble( getImageScaleFactorX( ) );
        destination.writeDouble( getImageOffsetX( ) );
        destination.writeDouble( getImageScaleFactorY( ) );
        destination.writeDouble( getImageOffsetY( ) );
        destination.writeInt32( getRadarImageType( ) );
        destination.writeUInt32( getTrackColor( ) );
        destination.writeUInt32( getVectorColor( ) );
        destination.writeBoolean( getEnableNmea( ) );
        destination.writeStringUtf8( getNmeaReceiverIPAddress( ) );
        destination.writeInt32( getNmeaReceiverPort( ) );
        destination.writeStringUtf8( getNmeaReceiverSourceId( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

    public RadarConfigurationObject GetDataObject( ) throws SQLException {
            return new RadarConfigurationObject( ObjectState.Stored, getId( ), getRowVersion( ), getRadar( ), getTimestamp( ), getRadarProtocolVersion( ), getRadarIPAddress( ), getRadarPort( ), getRadarConfigurationPort( ), getSkipMagicTimeout( ), getReadTimeout( ), getSynchronizationInterval( ), getTargetsRefreshRate( ), getRange( ), getSectorCount( ), getSectorOffset( ), getImageColor( ), getImageSubstitutionColor( ), getTransparentColor( ), getImageScaleFactorX( ), getImageOffsetX( ), getImageScaleFactorY( ), getImageOffsetY( ), getRadarImageType( ), getTrackColor( ), getVectorColor( ), getEnableNmea( ), getNmeaReceiverIPAddress( ), getNmeaReceiverPort( ), getNmeaReceiverSourceId( ) );
    }

}
