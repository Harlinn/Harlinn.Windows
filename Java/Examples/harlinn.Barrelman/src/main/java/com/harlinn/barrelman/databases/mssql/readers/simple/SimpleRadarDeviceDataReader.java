package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleRadarDeviceDataReader extends SimpleTrackerDeviceDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  rd.[Id], \r\n" +
            "  rd.[EntityType], \r\n" +
            "  rd.[RowVersion], \r\n" +
            "  rd.[Host], \r\n" +
            "  rd.[Name], \r\n" +
            "  rd.[Description], \r\n" +
            "  rd.[EnabledTimeseries], \r\n" +
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
            "  rd.[GNSSDevice] \r\n" +
            "FROM [RadarDeviceView] rd \r\n";

    public final static String BaseViewName = "RadarDeviceView";
    public final static String ViewAliasName = "rd";

    public final static int SAVESETTINGSTIMESERIES_FIELD_ID = 8;
    public final static int POWERONTIMESERIES_FIELD_ID = 9;
    public final static int TRACKINGONTIMESERIES_FIELD_ID = 10;
    public final static int RADARPULSETIMESERIES_FIELD_ID = 11;
    public final static int TUNINGTIMESERIES_FIELD_ID = 12;
    public final static int BLANKSECTOR1TIMESERIES_FIELD_ID = 13;
    public final static int SECTOR1STARTTIMESERIES_FIELD_ID = 14;
    public final static int SECTOR1ENDTIMESERIES_FIELD_ID = 15;
    public final static int BLANKSECTOR2TIMESERIES_FIELD_ID = 16;
    public final static int SECTOR2STARTTIMESERIES_FIELD_ID = 17;
    public final static int SECTOR2ENDTIMESERIES_FIELD_ID = 18;
    public final static int ENABLEAUTOMATICFREQUENCYCONTROLTIMESERIES_FIELD_ID = 19;
    public final static int AZIMUTHOFFSETTIMESERIES_FIELD_ID = 20;
    public final static int ENABLESENSITIVITYTIMECONTROLTIMESERIES_FIELD_ID = 21;
    public final static int AUTOMATICSENSITIVITYTIMECONTROLTIMESERIES_FIELD_ID = 22;
    public final static int SENSITIVITYTIMECONTROLLEVELTIMESERIES_FIELD_ID = 23;
    public final static int ENABLEFASTTIMECONSTANTTIMESERIES_FIELD_ID = 24;
    public final static int FASTTIMECONSTANTLEVELTIMESERIES_FIELD_ID = 25;
    public final static int FASTTIMECONSTANTMODETIMESERIES_FIELD_ID = 26;
    public final static int LATITUDETIMESERIES_FIELD_ID = 27;
    public final static int LONGITUDETIMESERIES_FIELD_ID = 28;
    public final static int RADOME_FIELD_ID = 29;
    public final static int GNSSDEVICE_FIELD_ID = 30;

    public SimpleRadarDeviceDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getSaveSettingsTimeseries() throws SQLException {
        return getNullableGuid( SAVESETTINGSTIMESERIES_FIELD_ID );
    }

    public final Guid getPowerOnTimeseries() throws SQLException {
        return getNullableGuid( POWERONTIMESERIES_FIELD_ID );
    }

    public final Guid getTrackingOnTimeseries() throws SQLException {
        return getNullableGuid( TRACKINGONTIMESERIES_FIELD_ID );
    }

    public final Guid getRadarPulseTimeseries() throws SQLException {
        return getNullableGuid( RADARPULSETIMESERIES_FIELD_ID );
    }

    public final Guid getTuningTimeseries() throws SQLException {
        return getNullableGuid( TUNINGTIMESERIES_FIELD_ID );
    }

    public final Guid getBlankSector1Timeseries() throws SQLException {
        return getNullableGuid( BLANKSECTOR1TIMESERIES_FIELD_ID );
    }

    public final Guid getSector1StartTimeseries() throws SQLException {
        return getNullableGuid( SECTOR1STARTTIMESERIES_FIELD_ID );
    }

    public final Guid getSector1EndTimeseries() throws SQLException {
        return getNullableGuid( SECTOR1ENDTIMESERIES_FIELD_ID );
    }

    public final Guid getBlankSector2Timeseries() throws SQLException {
        return getNullableGuid( BLANKSECTOR2TIMESERIES_FIELD_ID );
    }

    public final Guid getSector2StartTimeseries() throws SQLException {
        return getNullableGuid( SECTOR2STARTTIMESERIES_FIELD_ID );
    }

    public final Guid getSector2EndTimeseries() throws SQLException {
        return getNullableGuid( SECTOR2ENDTIMESERIES_FIELD_ID );
    }

    public final Guid getEnableAutomaticFrequencyControlTimeseries() throws SQLException {
        return getNullableGuid( ENABLEAUTOMATICFREQUENCYCONTROLTIMESERIES_FIELD_ID );
    }

    public final Guid getAzimuthOffsetTimeseries() throws SQLException {
        return getNullableGuid( AZIMUTHOFFSETTIMESERIES_FIELD_ID );
    }

    public final Guid getEnableSensitivityTimeControlTimeseries() throws SQLException {
        return getNullableGuid( ENABLESENSITIVITYTIMECONTROLTIMESERIES_FIELD_ID );
    }

    public final Guid getAutomaticSensitivityTimeControlTimeseries() throws SQLException {
        return getNullableGuid( AUTOMATICSENSITIVITYTIMECONTROLTIMESERIES_FIELD_ID );
    }

    public final Guid getSensitivityTimeControlLevelTimeseries() throws SQLException {
        return getNullableGuid( SENSITIVITYTIMECONTROLLEVELTIMESERIES_FIELD_ID );
    }

    public final Guid getEnableFastTimeConstantTimeseries() throws SQLException {
        return getNullableGuid( ENABLEFASTTIMECONSTANTTIMESERIES_FIELD_ID );
    }

    public final Guid getFastTimeConstantLevelTimeseries() throws SQLException {
        return getNullableGuid( FASTTIMECONSTANTLEVELTIMESERIES_FIELD_ID );
    }

    public final Guid getFastTimeConstantModeTimeseries() throws SQLException {
        return getNullableGuid( FASTTIMECONSTANTMODETIMESERIES_FIELD_ID );
    }

    public final Guid getLatitudeTimeseries() throws SQLException {
        return getNullableGuid( LATITUDETIMESERIES_FIELD_ID );
    }

    public final Guid getLongitudeTimeseries() throws SQLException {
        return getNullableGuid( LONGITUDETIMESERIES_FIELD_ID );
    }

    public final Guid getRadome() throws SQLException {
        return getNullableGuid( RADOME_FIELD_ID );
    }

    public final Guid getGNSSDevice() throws SQLException {
        return getNullableGuid( GNSSDEVICE_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeNullableGuid( getSaveSettingsTimeseries( ) );
        destination.writeNullableGuid( getPowerOnTimeseries( ) );
        destination.writeNullableGuid( getTrackingOnTimeseries( ) );
        destination.writeNullableGuid( getRadarPulseTimeseries( ) );
        destination.writeNullableGuid( getTuningTimeseries( ) );
        destination.writeNullableGuid( getBlankSector1Timeseries( ) );
        destination.writeNullableGuid( getSector1StartTimeseries( ) );
        destination.writeNullableGuid( getSector1EndTimeseries( ) );
        destination.writeNullableGuid( getBlankSector2Timeseries( ) );
        destination.writeNullableGuid( getSector2StartTimeseries( ) );
        destination.writeNullableGuid( getSector2EndTimeseries( ) );
        destination.writeNullableGuid( getEnableAutomaticFrequencyControlTimeseries( ) );
        destination.writeNullableGuid( getAzimuthOffsetTimeseries( ) );
        destination.writeNullableGuid( getEnableSensitivityTimeControlTimeseries( ) );
        destination.writeNullableGuid( getAutomaticSensitivityTimeControlTimeseries( ) );
        destination.writeNullableGuid( getSensitivityTimeControlLevelTimeseries( ) );
        destination.writeNullableGuid( getEnableFastTimeConstantTimeseries( ) );
        destination.writeNullableGuid( getFastTimeConstantLevelTimeseries( ) );
        destination.writeNullableGuid( getFastTimeConstantModeTimeseries( ) );
        destination.writeNullableGuid( getLatitudeTimeseries( ) );
        destination.writeNullableGuid( getLongitudeTimeseries( ) );
        destination.writeNullableGuid( getRadome( ) );
        destination.writeNullableGuid( getGNSSDevice( ) );
    }

    @Override
    public RadarDeviceObject GetDataObject( ) throws SQLException {
        return new RadarDeviceObject( ObjectState.Stored, getId( ), getRowVersion( ), getHost( ), getName( ), getDescription( ), getEnabledTimeseries( ), getSaveSettingsTimeseries( ), getPowerOnTimeseries( ), getTrackingOnTimeseries( ), getRadarPulseTimeseries( ), getTuningTimeseries( ), getBlankSector1Timeseries( ), getSector1StartTimeseries( ), getSector1EndTimeseries( ), getBlankSector2Timeseries( ), getSector2StartTimeseries( ), getSector2EndTimeseries( ), getEnableAutomaticFrequencyControlTimeseries( ), getAzimuthOffsetTimeseries( ), getEnableSensitivityTimeControlTimeseries( ), getAutomaticSensitivityTimeControlTimeseries( ), getSensitivityTimeControlLevelTimeseries( ), getEnableFastTimeConstantTimeseries( ), getFastTimeConstantLevelTimeseries( ), getFastTimeConstantModeTimeseries( ), getLatitudeTimeseries( ), getLongitudeTimeseries( ), getRadome( ), getGNSSDevice( ) );
    }

}
