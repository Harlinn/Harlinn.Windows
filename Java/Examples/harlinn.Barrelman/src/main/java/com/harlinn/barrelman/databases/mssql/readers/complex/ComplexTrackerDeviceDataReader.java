package com.harlinn.barrelman.databases.mssql.readers.complex;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class ComplexTrackerDeviceDataReader extends ResultSetWrapper {

    public final static String BaseQuery = "SELECT \r\n" +
            "  td.[Id], \r\n" +
            "  td.[EntityType], \r\n" +
            "  td.[RowVersion], \r\n" +
            "  td.[Host], \r\n" +
            "  td.[Name], \r\n" +
            "  td.[EnabledTimeseries], \r\n" +
            "  rd.[SaveSettingsTimeseries], \r\n" +
            "  rd.[PowerOnTimeseries], \r\n" +
            "  rd.[TrackingOnTimeseries], \r\n" +
            "  rd.[RadarPulseTimeseries], \r\n" +
            "  rd.[TuningTimeseries], \r\n" +
            "  rd.[BlankSector1Timeseries], \r\n" +
            "  rd.[Sector1StartTimeseries], \r\n" +
            "  rd.[Sector1EndTimeseries], \r\n" +
            "  rd.[BlankSector2Timeseries], \r\n" +
            "  rd.[Sector2StartTimeseries], \r\n" +
            "  rd.[Sector2EndTimeseries], \r\n" +
            "  rd.[EnableAutomaticFrequencyControlTimeseries], \r\n" +
            "  rd.[AzimuthOffsetTimeseries], \r\n" +
            "  rd.[EnableSensitivityTimeControlTimeseries], \r\n" +
            "  rd.[AutomaticSensitivityTimeControlTimeseries], \r\n" +
            "  rd.[SensitivityTimeControlLevelTimeseries], \r\n" +
            "  rd.[EnableFastTimeConstantTimeseries], \r\n" +
            "  rd.[FastTimeConstantLevelTimeseries], \r\n" +
            "  rd.[FastTimeConstantModeTimeseries], \r\n" +
            "  rd.[LatitudeTimeseries], \r\n" +
            "  rd.[LongitudeTimeseries], \r\n" +
            "  rd.[Radome], \r\n" +
            "  rd.[GNSSDevice], \r\n" +
            "  td.[Description] \r\n" +
            "FROM [TrackerDeviceView] td \r\n" +
            "  LEFT JOIN [AisDevice] ad ON(td.[Id] = ad.[Id] ) \r\n" +
            "  LEFT JOIN [RadarDevice] rd ON(td.[Id] = rd.[Id] ) \r\n";

    public final static String BaseViewName = "TrackerDeviceView";
    public final static String ViewAliasName = "td";

    public final static int TD_ID_FIELD_ID = 1;
    public final static int TD_KIND_FIELD_ID = 2;
    public final static int TD_ROWVERSION_FIELD_ID = 3;
    public final static int TD_HOST_FIELD_ID = 4;
    public final static int TD_NAME_FIELD_ID = 5;
    public final static int TD_ENABLEDTIMESERIES_FIELD_ID = 6;
    public final static int RD_SAVESETTINGSTIMESERIES_FIELD_ID = 7;
    public final static int RD_POWERONTIMESERIES_FIELD_ID = 8;
    public final static int RD_TRACKINGONTIMESERIES_FIELD_ID = 9;
    public final static int RD_RADARPULSETIMESERIES_FIELD_ID = 10;
    public final static int RD_TUNINGTIMESERIES_FIELD_ID = 11;
    public final static int RD_BLANKSECTOR1TIMESERIES_FIELD_ID = 12;
    public final static int RD_SECTOR1STARTTIMESERIES_FIELD_ID = 13;
    public final static int RD_SECTOR1ENDTIMESERIES_FIELD_ID = 14;
    public final static int RD_BLANKSECTOR2TIMESERIES_FIELD_ID = 15;
    public final static int RD_SECTOR2STARTTIMESERIES_FIELD_ID = 16;
    public final static int RD_SECTOR2ENDTIMESERIES_FIELD_ID = 17;
    public final static int RD_ENABLEAUTOMATICFREQUENCYCONTROLTIMESERIES_FIELD_ID = 18;
    public final static int RD_AZIMUTHOFFSETTIMESERIES_FIELD_ID = 19;
    public final static int RD_ENABLESENSITIVITYTIMECONTROLTIMESERIES_FIELD_ID = 20;
    public final static int RD_AUTOMATICSENSITIVITYTIMECONTROLTIMESERIES_FIELD_ID = 21;
    public final static int RD_SENSITIVITYTIMECONTROLLEVELTIMESERIES_FIELD_ID = 22;
    public final static int RD_ENABLEFASTTIMECONSTANTTIMESERIES_FIELD_ID = 23;
    public final static int RD_FASTTIMECONSTANTLEVELTIMESERIES_FIELD_ID = 24;
    public final static int RD_FASTTIMECONSTANTMODETIMESERIES_FIELD_ID = 25;
    public final static int RD_LATITUDETIMESERIES_FIELD_ID = 26;
    public final static int RD_LONGITUDETIMESERIES_FIELD_ID = 27;
    public final static int RD_RADOME_FIELD_ID = 28;
    public final static int RD_GNSSDEVICE_FIELD_ID = 29;
    public final static int TD_DESCRIPTION_FIELD_ID = 30;

    public ComplexTrackerDeviceDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public Guid getId( ) throws SQLException {
        return getGuid( TD_ID_FIELD_ID );
    }

    public int getObjectType() throws SQLException {
        return getInt32( TD_KIND_FIELD_ID );
    }

    public long getRowVersion( ) throws SQLException {
        return getInt64( TD_ROWVERSION_FIELD_ID );
    }

    public Guid getHost( ) throws SQLException {
        return getGuid( TD_HOST_FIELD_ID );
    }

    public String getName( ) throws SQLException {
        return getString( TD_NAME_FIELD_ID );
    }

    public String getDescription( ) throws SQLException {
        return getString( TD_DESCRIPTION_FIELD_ID );
    }

    public Guid getEnabledTimeseries( ) throws SQLException {
        return getNullableGuid( TD_ENABLEDTIMESERIES_FIELD_ID );
    }

    public Guid getRadarDeviceSaveSettingsTimeseries( ) throws SQLException {
        return getNullableGuid( RD_SAVESETTINGSTIMESERIES_FIELD_ID );
    }

    public Guid getRadarDevicePowerOnTimeseries( ) throws SQLException {
        return getNullableGuid( RD_POWERONTIMESERIES_FIELD_ID );
    }

    public Guid getRadarDeviceTrackingOnTimeseries( ) throws SQLException {
        return getNullableGuid( RD_TRACKINGONTIMESERIES_FIELD_ID );
    }

    public Guid getRadarDeviceRadarPulseTimeseries( ) throws SQLException {
        return getNullableGuid( RD_RADARPULSETIMESERIES_FIELD_ID );
    }

    public Guid getRadarDeviceTuningTimeseries( ) throws SQLException {
        return getNullableGuid( RD_TUNINGTIMESERIES_FIELD_ID );
    }

    public Guid getRadarDeviceBlankSector1Timeseries( ) throws SQLException {
        return getNullableGuid( RD_BLANKSECTOR1TIMESERIES_FIELD_ID );
    }

    public Guid getRadarDeviceSector1StartTimeseries( ) throws SQLException {
        return getNullableGuid( RD_SECTOR1STARTTIMESERIES_FIELD_ID );
    }

    public Guid getRadarDeviceSector1EndTimeseries( ) throws SQLException {
        return getNullableGuid( RD_SECTOR1ENDTIMESERIES_FIELD_ID );
    }

    public Guid getRadarDeviceBlankSector2Timeseries( ) throws SQLException {
        return getNullableGuid( RD_BLANKSECTOR2TIMESERIES_FIELD_ID );
    }

    public Guid getRadarDeviceSector2StartTimeseries( ) throws SQLException {
        return getNullableGuid( RD_SECTOR2STARTTIMESERIES_FIELD_ID );
    }

    public Guid getRadarDeviceSector2EndTimeseries( ) throws SQLException {
        return getNullableGuid( RD_SECTOR2ENDTIMESERIES_FIELD_ID );
    }

    public Guid getRadarDeviceEnableAutomaticFrequencyControlTimeseries( ) throws SQLException {
        return getNullableGuid( RD_ENABLEAUTOMATICFREQUENCYCONTROLTIMESERIES_FIELD_ID );
    }

    public Guid getRadarDeviceAzimuthOffsetTimeseries( ) throws SQLException {
        return getNullableGuid( RD_AZIMUTHOFFSETTIMESERIES_FIELD_ID );
    }

    public Guid getRadarDeviceEnableSensitivityTimeControlTimeseries( ) throws SQLException {
        return getNullableGuid( RD_ENABLESENSITIVITYTIMECONTROLTIMESERIES_FIELD_ID );
    }

    public Guid getRadarDeviceAutomaticSensitivityTimeControlTimeseries( ) throws SQLException {
        return getNullableGuid( RD_AUTOMATICSENSITIVITYTIMECONTROLTIMESERIES_FIELD_ID );
    }

    public Guid getRadarDeviceSensitivityTimeControlLevelTimeseries( ) throws SQLException {
        return getNullableGuid( RD_SENSITIVITYTIMECONTROLLEVELTIMESERIES_FIELD_ID );
    }

    public Guid getRadarDeviceEnableFastTimeConstantTimeseries( ) throws SQLException {
        return getNullableGuid( RD_ENABLEFASTTIMECONSTANTTIMESERIES_FIELD_ID );
    }

    public Guid getRadarDeviceFastTimeConstantLevelTimeseries( ) throws SQLException {
        return getNullableGuid( RD_FASTTIMECONSTANTLEVELTIMESERIES_FIELD_ID );
    }

    public Guid getRadarDeviceFastTimeConstantModeTimeseries( ) throws SQLException {
        return getNullableGuid( RD_FASTTIMECONSTANTMODETIMESERIES_FIELD_ID );
    }

    public Guid getRadarDeviceLatitudeTimeseries( ) throws SQLException {
        return getNullableGuid( RD_LATITUDETIMESERIES_FIELD_ID );
    }

    public Guid getRadarDeviceLongitudeTimeseries( ) throws SQLException {
        return getNullableGuid( RD_LONGITUDETIMESERIES_FIELD_ID );
    }

    public Guid getRadarDeviceRadome( ) throws SQLException {
        return getNullableGuid( RD_RADOME_FIELD_ID );
    }

    public Guid getRadarDeviceGNSSDevice( ) throws SQLException {
        return getNullableGuid( RD_GNSSDEVICE_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination ) throws SQLException {
        var kind = getObjectType( );
        switch(kind) {
            case Kind.AisDevice: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeGuid( getHost( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeStringUtf8( getDescription( ) );
                destination.writeNullableGuid( getEnabledTimeseries( ) );
            }
            break;
            case Kind.RadarDevice: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeGuid( getHost( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeStringUtf8( getDescription( ) );
                destination.writeNullableGuid( getEnabledTimeseries( ) );
                destination.writeNullableGuid( getRadarDeviceSaveSettingsTimeseries( ) );
                destination.writeNullableGuid( getRadarDevicePowerOnTimeseries( ) );
                destination.writeNullableGuid( getRadarDeviceTrackingOnTimeseries( ) );
                destination.writeNullableGuid( getRadarDeviceRadarPulseTimeseries( ) );
                destination.writeNullableGuid( getRadarDeviceTuningTimeseries( ) );
                destination.writeNullableGuid( getRadarDeviceBlankSector1Timeseries( ) );
                destination.writeNullableGuid( getRadarDeviceSector1StartTimeseries( ) );
                destination.writeNullableGuid( getRadarDeviceSector1EndTimeseries( ) );
                destination.writeNullableGuid( getRadarDeviceBlankSector2Timeseries( ) );
                destination.writeNullableGuid( getRadarDeviceSector2StartTimeseries( ) );
                destination.writeNullableGuid( getRadarDeviceSector2EndTimeseries( ) );
                destination.writeNullableGuid( getRadarDeviceEnableAutomaticFrequencyControlTimeseries( ) );
                destination.writeNullableGuid( getRadarDeviceAzimuthOffsetTimeseries( ) );
                destination.writeNullableGuid( getRadarDeviceEnableSensitivityTimeControlTimeseries( ) );
                destination.writeNullableGuid( getRadarDeviceAutomaticSensitivityTimeControlTimeseries( ) );
                destination.writeNullableGuid( getRadarDeviceSensitivityTimeControlLevelTimeseries( ) );
                destination.writeNullableGuid( getRadarDeviceEnableFastTimeConstantTimeseries( ) );
                destination.writeNullableGuid( getRadarDeviceFastTimeConstantLevelTimeseries( ) );
                destination.writeNullableGuid( getRadarDeviceFastTimeConstantModeTimeseries( ) );
                destination.writeNullableGuid( getRadarDeviceLatitudeTimeseries( ) );
                destination.writeNullableGuid( getRadarDeviceLongitudeTimeseries( ) );
                destination.writeNullableGuid( getRadarDeviceRadome( ) );
                destination.writeNullableGuid( getRadarDeviceGNSSDevice( ) );
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

    public TrackerDeviceObject getDataObject( ) throws SQLException {
        var kind = getObjectType( );
        switch(kind) {
            case Kind.AisDevice: {
                return new AisDeviceObject( ObjectState.Stored, getId( ), getRowVersion( ), getHost( ), getName( ), getDescription( ), getEnabledTimeseries( ) );
            }
            case Kind.RadarDevice: {
                return new RadarDeviceObject( ObjectState.Stored, getId( ), getRowVersion( ), getHost( ), getName( ), getDescription( ), getEnabledTimeseries( ), getRadarDeviceSaveSettingsTimeseries( ), getRadarDevicePowerOnTimeseries( ), getRadarDeviceTrackingOnTimeseries( ), getRadarDeviceRadarPulseTimeseries( ), getRadarDeviceTuningTimeseries( ), getRadarDeviceBlankSector1Timeseries( ), getRadarDeviceSector1StartTimeseries( ), getRadarDeviceSector1EndTimeseries( ), getRadarDeviceBlankSector2Timeseries( ), getRadarDeviceSector2StartTimeseries( ), getRadarDeviceSector2EndTimeseries( ), getRadarDeviceEnableAutomaticFrequencyControlTimeseries( ), getRadarDeviceAzimuthOffsetTimeseries( ), getRadarDeviceEnableSensitivityTimeControlTimeseries( ), getRadarDeviceAutomaticSensitivityTimeControlTimeseries( ), getRadarDeviceSensitivityTimeControlLevelTimeseries( ), getRadarDeviceEnableFastTimeConstantTimeseries( ), getRadarDeviceFastTimeConstantLevelTimeseries( ), getRadarDeviceFastTimeConstantModeTimeseries( ), getRadarDeviceLatitudeTimeseries( ), getRadarDeviceLongitudeTimeseries( ), getRadarDeviceRadome( ), getRadarDeviceGNSSDevice( ) );
            }
            default: {
                var exc = new SQLException( "Cannot create an object for kind=" + kind + "." );
                throw exc;
            }
        }
    }

}

