package com.harlinn.barrelman.databases.mssql.readers.complex;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class ComplexBooleanTimeseriesDataReader extends ResultSetWrapper {

    public final static String BaseQuery = "SELECT \r\n" +
            "  bots.[Id], \r\n" +
            "  bots.[EntityType], \r\n" +
            "  bots.[RowVersion], \r\n" +
            "  bots.[Catalog], \r\n" +
            "  bots.[Name], \r\n" +
            "  bots.[MaxRetention], \r\n" +
            "  aatnopt.[AidToNavigation], \r\n" +
            "  det.[Device], \r\n" +
            "  mpset.[ProxySession], \r\n" +
            "  mset.[Service], \r\n" +
            "  rastct.[Radar], \r\n" +
            "  rbs1t.[Radar], \r\n" +
            "  rbs2t.[Radar], \r\n" +
            "  reafct.[Radar], \r\n" +
            "  reftct.[Radar], \r\n" +
            "  restct.[Radar], \r\n" +
            "  rpot.[Radar], \r\n" +
            "  rsst.[Radar], \r\n" +
            "  rtt.[Radar] \r\n" +
            "FROM [BooleanTimeseriesView] bots \r\n" +
            "  LEFT JOIN [AisAidToNavigationOffPositionTimeseries] aatnopt ON(bots.[Id] = aatnopt.[Id] ) \r\n" +
            "  LEFT JOIN [DeviceEnabledTimeseries] det ON(bots.[Id] = det.[Id] ) \r\n" +
            "  LEFT JOIN [MediaProxySessionEnabledTimeseries] mpset ON(bots.[Id] = mpset.[Id] ) \r\n" +
            "  LEFT JOIN [MediaServiceEnabledTimeseries] mset ON(bots.[Id] = mset.[Id] ) \r\n" +
            "  LEFT JOIN [RadarAutomaticSensitivityTimeControlTimeseries] rastct ON(bots.[Id] = rastct.[Id] ) \r\n" +
            "  LEFT JOIN [RadarBlankSector1Timeseries] rbs1t ON(bots.[Id] = rbs1t.[Id] ) \r\n" +
            "  LEFT JOIN [RadarBlankSector2Timeseries] rbs2t ON(bots.[Id] = rbs2t.[Id] ) \r\n" +
            "  LEFT JOIN [RadarEnableAutomaticFrequencyControlTimeseries] reafct ON(bots.[Id] = reafct.[Id] ) \r\n" +
            "  LEFT JOIN [RadarEnableFastTimeConstantTimeseries] reftct ON(bots.[Id] = reftct.[Id] ) \r\n" +
            "  LEFT JOIN [RadarEnableSensitivityTimeControlTimeseries] restct ON(bots.[Id] = restct.[Id] ) \r\n" +
            "  LEFT JOIN [RadarPowerOnTimeseries] rpot ON(bots.[Id] = rpot.[Id] ) \r\n" +
            "  LEFT JOIN [RadarSaveSettingsTimeseries] rsst ON(bots.[Id] = rsst.[Id] ) \r\n" +
            "  LEFT JOIN [RadarTrackingTimeseries] rtt ON(bots.[Id] = rtt.[Id] ) \r\n";

    public final static String BaseViewName = "BooleanTimeseriesView";
    public final static String ViewAliasName = "bots";

    public final static int BOTS_ID_FIELD_ID = 1;
    public final static int BOTS_KIND_FIELD_ID = 2;
    public final static int BOTS_ROWVERSION_FIELD_ID = 3;
    public final static int BOTS_CATALOG_FIELD_ID = 4;
    public final static int BOTS_NAME_FIELD_ID = 5;
    public final static int BOTS_MAXRETENTION_FIELD_ID = 6;
    public final static int AATNOPT_AIDTONAVIGATION_FIELD_ID = 7;
    public final static int DET_DEVICE_FIELD_ID = 8;
    public final static int MPSET_PROXYSESSION_FIELD_ID = 9;
    public final static int MSET_SERVICE_FIELD_ID = 10;
    public final static int RASTCT_RADAR_FIELD_ID = 11;
    public final static int RBS1T_RADAR_FIELD_ID = 12;
    public final static int RBS2T_RADAR_FIELD_ID = 13;
    public final static int REAFCT_RADAR_FIELD_ID = 14;
    public final static int REFTCT_RADAR_FIELD_ID = 15;
    public final static int RESTCT_RADAR_FIELD_ID = 16;
    public final static int RPOT_RADAR_FIELD_ID = 17;
    public final static int RSST_RADAR_FIELD_ID = 18;
    public final static int RTT_RADAR_FIELD_ID = 19;

    public ComplexBooleanTimeseriesDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public Guid getId( ) throws SQLException {
        return getGuid( BOTS_ID_FIELD_ID );
    }

    public int getObjectType() throws SQLException {
        return getInt32( BOTS_KIND_FIELD_ID );
    }

    public long getRowVersion( ) throws SQLException {
        return getInt64( BOTS_ROWVERSION_FIELD_ID );
    }

    public Guid getCatalog( ) throws SQLException {
        return getNullableGuid( BOTS_CATALOG_FIELD_ID );
    }

    public String getName( ) throws SQLException {
        return getString( BOTS_NAME_FIELD_ID );
    }

    public TimeSpan getMaxRetention( ) throws SQLException {
        return getTimeSpan( BOTS_MAXRETENTION_FIELD_ID );
    }

    public Guid getAisAidToNavigationOffPositionTimeseriesAidToNavigation( ) throws SQLException {
        return getNullableGuid( AATNOPT_AIDTONAVIGATION_FIELD_ID );
    }

    public Guid getDeviceEnabledTimeseriesDevice( ) throws SQLException {
        return getNullableGuid( DET_DEVICE_FIELD_ID );
    }

    public Guid getMediaProxySessionEnabledTimeseriesProxySession( ) throws SQLException {
        return getNullableGuid( MPSET_PROXYSESSION_FIELD_ID );
    }

    public Guid getMediaServiceEnabledTimeseriesService( ) throws SQLException {
        return getNullableGuid( MSET_SERVICE_FIELD_ID );
    }

    public Guid getRadarAutomaticSensitivityTimeControlTimeseriesRadar( ) throws SQLException {
        return getNullableGuid( RASTCT_RADAR_FIELD_ID );
    }

    public Guid getRadarBlankSector1TimeseriesRadar( ) throws SQLException {
        return getNullableGuid( RBS1T_RADAR_FIELD_ID );
    }

    public Guid getRadarBlankSector2TimeseriesRadar( ) throws SQLException {
        return getNullableGuid( RBS2T_RADAR_FIELD_ID );
    }

    public Guid getRadarEnableAutomaticFrequencyControlTimeseriesRadar( ) throws SQLException {
        return getNullableGuid( REAFCT_RADAR_FIELD_ID );
    }

    public Guid getRadarEnableFastTimeConstantTimeseriesRadar( ) throws SQLException {
        return getNullableGuid( REFTCT_RADAR_FIELD_ID );
    }

    public Guid getRadarEnableSensitivityTimeControlTimeseriesRadar( ) throws SQLException {
        return getNullableGuid( RESTCT_RADAR_FIELD_ID );
    }

    public Guid getRadarPowerOnTimeseriesRadar( ) throws SQLException {
        return getNullableGuid( RPOT_RADAR_FIELD_ID );
    }

    public Guid getRadarSaveSettingsTimeseriesRadar( ) throws SQLException {
        return getNullableGuid( RSST_RADAR_FIELD_ID );
    }

    public Guid getRadarTrackingTimeseriesRadar( ) throws SQLException {
        return getNullableGuid( RTT_RADAR_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination ) throws SQLException {
        var kind = getObjectType( );
        switch(kind) {
            case Kind.BooleanTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
            }
            break;
            case Kind.AisAidToNavigationOffPositionTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
                destination.writeNullableGuid( getAisAidToNavigationOffPositionTimeseriesAidToNavigation( ) );
            }
            break;
            case Kind.DeviceEnabledTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
                destination.writeNullableGuid( getDeviceEnabledTimeseriesDevice( ) );
            }
            break;
            case Kind.MediaProxySessionEnabledTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
                destination.writeNullableGuid( getMediaProxySessionEnabledTimeseriesProxySession( ) );
            }
            break;
            case Kind.MediaServiceEnabledTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
                destination.writeNullableGuid( getMediaServiceEnabledTimeseriesService( ) );
            }
            break;
            case Kind.RadarAutomaticSensitivityTimeControlTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
                destination.writeNullableGuid( getRadarAutomaticSensitivityTimeControlTimeseriesRadar( ) );
            }
            break;
            case Kind.RadarBlankSector1Timeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
                destination.writeNullableGuid( getRadarBlankSector1TimeseriesRadar( ) );
            }
            break;
            case Kind.RadarBlankSector2Timeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
                destination.writeNullableGuid( getRadarBlankSector2TimeseriesRadar( ) );
            }
            break;
            case Kind.RadarEnableAutomaticFrequencyControlTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
                destination.writeNullableGuid( getRadarEnableAutomaticFrequencyControlTimeseriesRadar( ) );
            }
            break;
            case Kind.RadarEnableFastTimeConstantTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
                destination.writeNullableGuid( getRadarEnableFastTimeConstantTimeseriesRadar( ) );
            }
            break;
            case Kind.RadarEnableSensitivityTimeControlTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
                destination.writeNullableGuid( getRadarEnableSensitivityTimeControlTimeseriesRadar( ) );
            }
            break;
            case Kind.RadarPowerOnTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
                destination.writeNullableGuid( getRadarPowerOnTimeseriesRadar( ) );
            }
            break;
            case Kind.RadarSaveSettingsTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
                destination.writeNullableGuid( getRadarSaveSettingsTimeseriesRadar( ) );
            }
            break;
            case Kind.RadarTrackingTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
                destination.writeNullableGuid( getRadarTrackingTimeseriesRadar( ) );
            }
            break;
            default: {
                var exc = new SQLException( "Cannot perform serialization for kind=" + kind + "." );
                throw exc;
            }
        }
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

    public BooleanTimeseriesObject getDataObject( ) throws SQLException {
        var kind = getObjectType( );
        switch(kind) {
            case Kind.BooleanTimeseries: {
                return new BooleanTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ) );
            }
            case Kind.AisAidToNavigationOffPositionTimeseries: {
                return new AisAidToNavigationOffPositionTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getAisAidToNavigationOffPositionTimeseriesAidToNavigation( ) );
            }
            case Kind.DeviceEnabledTimeseries: {
                return new DeviceEnabledTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getDeviceEnabledTimeseriesDevice( ) );
            }
            case Kind.MediaProxySessionEnabledTimeseries: {
                return new MediaProxySessionEnabledTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getMediaProxySessionEnabledTimeseriesProxySession( ) );
            }
            case Kind.MediaServiceEnabledTimeseries: {
                return new MediaServiceEnabledTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getMediaServiceEnabledTimeseriesService( ) );
            }
            case Kind.RadarAutomaticSensitivityTimeControlTimeseries: {
                return new RadarAutomaticSensitivityTimeControlTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getRadarAutomaticSensitivityTimeControlTimeseriesRadar( ) );
            }
            case Kind.RadarBlankSector1Timeseries: {
                return new RadarBlankSector1TimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getRadarBlankSector1TimeseriesRadar( ) );
            }
            case Kind.RadarBlankSector2Timeseries: {
                return new RadarBlankSector2TimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getRadarBlankSector2TimeseriesRadar( ) );
            }
            case Kind.RadarEnableAutomaticFrequencyControlTimeseries: {
                return new RadarEnableAutomaticFrequencyControlTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getRadarEnableAutomaticFrequencyControlTimeseriesRadar( ) );
            }
            case Kind.RadarEnableFastTimeConstantTimeseries: {
                return new RadarEnableFastTimeConstantTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getRadarEnableFastTimeConstantTimeseriesRadar( ) );
            }
            case Kind.RadarEnableSensitivityTimeControlTimeseries: {
                return new RadarEnableSensitivityTimeControlTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getRadarEnableSensitivityTimeControlTimeseriesRadar( ) );
            }
            case Kind.RadarPowerOnTimeseries: {
                return new RadarPowerOnTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getRadarPowerOnTimeseriesRadar( ) );
            }
            case Kind.RadarSaveSettingsTimeseries: {
                return new RadarSaveSettingsTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getRadarSaveSettingsTimeseriesRadar( ) );
            }
            case Kind.RadarTrackingTimeseries: {
                return new RadarTrackingTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getRadarTrackingTimeseriesRadar( ) );
            }
            default: {
                var exc = new SQLException( "Cannot create an object for kind=" + kind + "." );
                throw exc;
            }
        }
    }

}

