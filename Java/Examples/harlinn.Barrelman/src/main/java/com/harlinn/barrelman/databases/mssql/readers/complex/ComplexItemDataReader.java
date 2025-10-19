package com.harlinn.barrelman.databases.mssql.readers.complex;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class ComplexItemDataReader extends ResultSetWrapper {

    public final static String BaseQuery = "SELECT \r\n" +
            "  i.[Id], \r\n" +
            "  i.[EntityType], \r\n" +
            "  i.[RowVersion], \r\n" +
            "  bs.[Name], \r\n" +
            "  bs.[Type], \r\n" +
            "  d.[Host], \r\n" +
            "  d.[Name], \r\n" +
            "  d.[EnabledTimeseries], \r\n" +
            "  g.[LatitudeTimeseries], \r\n" +
            "  g.[LongitudeTimeseries], \r\n" +
            "  g.[AltitudeTimeseries], \r\n" +
            "  gd.[HeadingTrueNorthTimeseries], \r\n" +
            "  gd.[HeadingMagneticNorthTimeseries], \r\n" +
            "  gd.[PitchTimeseries], \r\n" +
            "  gd.[RateOfTurnTimeseries], \r\n" +
            "  gd.[RollTimeseries], \r\n" +
            "  gd.[CourseTimeseries], \r\n" +
            "  gd.[SpeedTimeseries], \r\n" +
            "  gd.[GNSSDevice], \r\n" +
            "  rdo.[Radar], \r\n" +
            "  rdo.[PressureTimeseries], \r\n" +
            "  rdo.[TemperatureTimeseries], \r\n" +
            "  rdo.[DewPointTimeseries], \r\n" +
            "  rdo.[StatusTimeseries], \r\n" +
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
            "  wsd.[BarometricPressureTimeseries], \r\n" +
            "  wsd.[AirTemperatureTimeseries], \r\n" +
            "  wsd.[WaterTemperatureTimeseries], \r\n" +
            "  wsd.[RelativeHumidityTimeseries], \r\n" +
            "  wsd.[AbsoluteHumidityTimeseries], \r\n" +
            "  wsd.[DewPointTimeseries], \r\n" +
            "  wsd.[WindDirectionTimeseries], \r\n" +
            "  wsd.[WindSpeedTimeseries], \r\n" +
            "  wsd.[Gyro], \r\n" +
            "  f.[Name], \r\n" +
            "  f.[Type], \r\n" +
            "  f.[Longitude], \r\n" +
            "  f.[Latitude], \r\n" +
            "  f.[Altitude], \r\n" +
            "  a.[Name], \r\n" +
            "  a.[Type], \r\n" +
            "  aatn.[Name], \r\n" +
            "  aatn.[MMSI], \r\n" +
            "  aatn.[NavigationalAidType], \r\n" +
            "  aatn.[Position], \r\n" +
            "  aatn.[IsVirtual], \r\n" +
            "  aatn.[ToBow], \r\n" +
            "  aatn.[ToStern], \r\n" +
            "  aatn.[ToPort], \r\n" +
            "  aatn.[ToStarboard], \r\n" +
            "  aatn.[OffPositionTimeseries], \r\n" +
            "  v.[Name], \r\n" +
            "  v.[Type], \r\n" +
            "  vsl.[Name], \r\n" +
            "  vsl.[Type], \r\n" +
            "  vsl.[ToBow], \r\n" +
            "  vsl.[ToStern], \r\n" +
            "  vsl.[ToPort], \r\n" +
            "  vsl.[ToStarboard], \r\n" +
            "  vsl.[DraughtTimeseries], \r\n" +
            "  vsl.[PersonsOnBoardTimeseries], \r\n" +
            "  d.[Description] \r\n" +
            "FROM [ItemView] i \r\n" +
            "  LEFT JOIN [BaseStation] bs ON(i.[Id] = bs.[Id] ) \r\n" +
            "  LEFT JOIN [Device] d ON(i.[Id] = d.[Id] ) \r\n" +
            "  LEFT JOIN [CameraDevice] cd ON(i.[Id] = cd.[Id] ) \r\n" +
            "  LEFT JOIN [GNSSDevice] g ON(i.[Id] = g.[Id] ) \r\n" +
            "  LEFT JOIN [GyroDevice] gd ON(i.[Id] = gd.[Id] ) \r\n" +
            "  LEFT JOIN [LineInputDevice] lid ON(i.[Id] = lid.[Id] ) \r\n" +
            "  LEFT JOIN [OilSpillDetectorDevice] osdd ON(i.[Id] = osdd.[Id] ) \r\n" +
            "  LEFT JOIN [RadioDevice] rdi ON(i.[Id] = rdi.[Id] ) \r\n" +
            "  LEFT JOIN [RadomeDevice] rdo ON(i.[Id] = rdo.[Id] ) \r\n" +
            "  LEFT JOIN [TrackerDevice] td ON(i.[Id] = td.[Id] ) \r\n" +
            "  LEFT JOIN [AisDevice] ad ON(i.[Id] = ad.[Id] ) \r\n" +
            "  LEFT JOIN [RadarDevice] rd ON(i.[Id] = rd.[Id] ) \r\n" +
            "  LEFT JOIN [WeatherStationDevice] wsd ON(i.[Id] = wsd.[Id] ) \r\n" +
            "  LEFT JOIN [Facility] f ON(i.[Id] = f.[Id] ) \r\n" +
            "  LEFT JOIN [TrackableItem] ti ON(i.[Id] = ti.[Id] ) \r\n" +
            "  LEFT JOIN [Aircraft] a ON(i.[Id] = a.[Id] ) \r\n" +
            "  LEFT JOIN [AisAidToNavigation] aatn ON(i.[Id] = aatn.[Id] ) \r\n" +
            "  LEFT JOIN [Vehicle] v ON(i.[Id] = v.[Id] ) \r\n" +
            "  LEFT JOIN [Vessel] vsl ON(i.[Id] = vsl.[Id] ) \r\n";

    public final static String BaseViewName = "ItemView";
    public final static String ViewAliasName = "i";

    public final static int I_ID_FIELD_ID = 1;
    public final static int I_KIND_FIELD_ID = 2;
    public final static int I_ROWVERSION_FIELD_ID = 3;
    public final static int BS_NAME_FIELD_ID = 4;
    public final static int BS_TYPE_FIELD_ID = 5;
    public final static int D_HOST_FIELD_ID = 6;
    public final static int D_NAME_FIELD_ID = 7;
    public final static int D_ENABLEDTIMESERIES_FIELD_ID = 8;
    public final static int G_LATITUDETIMESERIES_FIELD_ID = 9;
    public final static int G_LONGITUDETIMESERIES_FIELD_ID = 10;
    public final static int G_ALTITUDETIMESERIES_FIELD_ID = 11;
    public final static int GD_HEADINGTRUENORTHTIMESERIES_FIELD_ID = 12;
    public final static int GD_HEADINGMAGNETICNORTHTIMESERIES_FIELD_ID = 13;
    public final static int GD_PITCHTIMESERIES_FIELD_ID = 14;
    public final static int GD_RATEOFTURNTIMESERIES_FIELD_ID = 15;
    public final static int GD_ROLLTIMESERIES_FIELD_ID = 16;
    public final static int GD_COURSETIMESERIES_FIELD_ID = 17;
    public final static int GD_SPEEDTIMESERIES_FIELD_ID = 18;
    public final static int GD_GNSSDEVICE_FIELD_ID = 19;
    public final static int RDO_RADAR_FIELD_ID = 20;
    public final static int RDO_PRESSURETIMESERIES_FIELD_ID = 21;
    public final static int RDO_TEMPERATURETIMESERIES_FIELD_ID = 22;
    public final static int RDO_DEWPOINTTIMESERIES_FIELD_ID = 23;
    public final static int RDO_STATUSTIMESERIES_FIELD_ID = 24;
    public final static int RD_SAVESETTINGSTIMESERIES_FIELD_ID = 25;
    public final static int RD_POWERONTIMESERIES_FIELD_ID = 26;
    public final static int RD_TRACKINGONTIMESERIES_FIELD_ID = 27;
    public final static int RD_RADARPULSETIMESERIES_FIELD_ID = 28;
    public final static int RD_TUNINGTIMESERIES_FIELD_ID = 29;
    public final static int RD_BLANKSECTOR1TIMESERIES_FIELD_ID = 30;
    public final static int RD_SECTOR1STARTTIMESERIES_FIELD_ID = 31;
    public final static int RD_SECTOR1ENDTIMESERIES_FIELD_ID = 32;
    public final static int RD_BLANKSECTOR2TIMESERIES_FIELD_ID = 33;
    public final static int RD_SECTOR2STARTTIMESERIES_FIELD_ID = 34;
    public final static int RD_SECTOR2ENDTIMESERIES_FIELD_ID = 35;
    public final static int RD_ENABLEAUTOMATICFREQUENCYCONTROLTIMESERIES_FIELD_ID = 36;
    public final static int RD_AZIMUTHOFFSETTIMESERIES_FIELD_ID = 37;
    public final static int RD_ENABLESENSITIVITYTIMECONTROLTIMESERIES_FIELD_ID = 38;
    public final static int RD_AUTOMATICSENSITIVITYTIMECONTROLTIMESERIES_FIELD_ID = 39;
    public final static int RD_SENSITIVITYTIMECONTROLLEVELTIMESERIES_FIELD_ID = 40;
    public final static int RD_ENABLEFASTTIMECONSTANTTIMESERIES_FIELD_ID = 41;
    public final static int RD_FASTTIMECONSTANTLEVELTIMESERIES_FIELD_ID = 42;
    public final static int RD_FASTTIMECONSTANTMODETIMESERIES_FIELD_ID = 43;
    public final static int RD_LATITUDETIMESERIES_FIELD_ID = 44;
    public final static int RD_LONGITUDETIMESERIES_FIELD_ID = 45;
    public final static int RD_RADOME_FIELD_ID = 46;
    public final static int RD_GNSSDEVICE_FIELD_ID = 47;
    public final static int WSD_BAROMETRICPRESSURETIMESERIES_FIELD_ID = 48;
    public final static int WSD_AIRTEMPERATURETIMESERIES_FIELD_ID = 49;
    public final static int WSD_WATERTEMPERATURETIMESERIES_FIELD_ID = 50;
    public final static int WSD_RELATIVEHUMIDITYTIMESERIES_FIELD_ID = 51;
    public final static int WSD_ABSOLUTEHUMIDITYTIMESERIES_FIELD_ID = 52;
    public final static int WSD_DEWPOINTTIMESERIES_FIELD_ID = 53;
    public final static int WSD_WINDDIRECTIONTIMESERIES_FIELD_ID = 54;
    public final static int WSD_WINDSPEEDTIMESERIES_FIELD_ID = 55;
    public final static int WSD_GYRO_FIELD_ID = 56;
    public final static int F_NAME_FIELD_ID = 57;
    public final static int F_TYPE_FIELD_ID = 58;
    public final static int F_LONGITUDE_FIELD_ID = 59;
    public final static int F_LATITUDE_FIELD_ID = 60;
    public final static int F_ALTITUDE_FIELD_ID = 61;
    public final static int A_NAME_FIELD_ID = 62;
    public final static int A_TYPE_FIELD_ID = 63;
    public final static int AATN_NAME_FIELD_ID = 64;
    public final static int AATN_MMSI_FIELD_ID = 65;
    public final static int AATN_NAVIGATIONALAIDTYPE_FIELD_ID = 66;
    public final static int AATN_POSITION_FIELD_ID = 67;
    public final static int AATN_ISVIRTUAL_FIELD_ID = 68;
    public final static int AATN_TOBOW_FIELD_ID = 69;
    public final static int AATN_TOSTERN_FIELD_ID = 70;
    public final static int AATN_TOPORT_FIELD_ID = 71;
    public final static int AATN_TOSTARBOARD_FIELD_ID = 72;
    public final static int AATN_OFFPOSITIONTIMESERIES_FIELD_ID = 73;
    public final static int V_NAME_FIELD_ID = 74;
    public final static int V_TYPE_FIELD_ID = 75;
    public final static int VSL_NAME_FIELD_ID = 76;
    public final static int VSL_TYPE_FIELD_ID = 77;
    public final static int VSL_TOBOW_FIELD_ID = 78;
    public final static int VSL_TOSTERN_FIELD_ID = 79;
    public final static int VSL_TOPORT_FIELD_ID = 80;
    public final static int VSL_TOSTARBOARD_FIELD_ID = 81;
    public final static int VSL_DRAUGHTTIMESERIES_FIELD_ID = 82;
    public final static int VSL_PERSONSONBOARDTIMESERIES_FIELD_ID = 83;
    public final static int D_DESCRIPTION_FIELD_ID = 84;

    public ComplexItemDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public Guid getId( ) throws SQLException {
        return getGuid( I_ID_FIELD_ID );
    }

    public int getObjectType() throws SQLException {
        return getInt32( I_KIND_FIELD_ID );
    }

    public long getRowVersion( ) throws SQLException {
        return getInt64( I_ROWVERSION_FIELD_ID );
    }

    public String getBaseStationName( ) throws SQLException {
        return getString( BS_NAME_FIELD_ID );
    }

    public Guid getBaseStationType( ) throws SQLException {
        return getNullableGuid( BS_TYPE_FIELD_ID );
    }

    public Guid getDeviceHost( ) throws SQLException {
        return getGuid( D_HOST_FIELD_ID );
    }

    public String getDeviceName( ) throws SQLException {
        return getString( D_NAME_FIELD_ID );
    }

    public String getDeviceDescription( ) throws SQLException {
        return getString( D_DESCRIPTION_FIELD_ID );
    }

    public Guid getDeviceEnabledTimeseries( ) throws SQLException {
        return getNullableGuid( D_ENABLEDTIMESERIES_FIELD_ID );
    }

    public Guid getGNSSDeviceLatitudeTimeseries( ) throws SQLException {
        return getNullableGuid( G_LATITUDETIMESERIES_FIELD_ID );
    }

    public Guid getGNSSDeviceLongitudeTimeseries( ) throws SQLException {
        return getNullableGuid( G_LONGITUDETIMESERIES_FIELD_ID );
    }

    public Guid getGNSSDeviceAltitudeTimeseries( ) throws SQLException {
        return getNullableGuid( G_ALTITUDETIMESERIES_FIELD_ID );
    }

    public Guid getGyroDeviceHeadingTrueNorthTimeseries( ) throws SQLException {
        return getNullableGuid( GD_HEADINGTRUENORTHTIMESERIES_FIELD_ID );
    }

    public Guid getGyroDeviceHeadingMagneticNorthTimeseries( ) throws SQLException {
        return getNullableGuid( GD_HEADINGMAGNETICNORTHTIMESERIES_FIELD_ID );
    }

    public Guid getGyroDevicePitchTimeseries( ) throws SQLException {
        return getNullableGuid( GD_PITCHTIMESERIES_FIELD_ID );
    }

    public Guid getGyroDeviceRateOfTurnTimeseries( ) throws SQLException {
        return getNullableGuid( GD_RATEOFTURNTIMESERIES_FIELD_ID );
    }

    public Guid getGyroDeviceRollTimeseries( ) throws SQLException {
        return getNullableGuid( GD_ROLLTIMESERIES_FIELD_ID );
    }

    public Guid getGyroDeviceCourseTimeseries( ) throws SQLException {
        return getNullableGuid( GD_COURSETIMESERIES_FIELD_ID );
    }

    public Guid getGyroDeviceSpeedTimeseries( ) throws SQLException {
        return getNullableGuid( GD_SPEEDTIMESERIES_FIELD_ID );
    }

    public Guid getGyroDeviceGNSSDevice( ) throws SQLException {
        return getNullableGuid( GD_GNSSDEVICE_FIELD_ID );
    }

    public Guid getRadomeDeviceRadar( ) throws SQLException {
        return getNullableGuid( RDO_RADAR_FIELD_ID );
    }

    public Guid getRadomeDevicePressureTimeseries( ) throws SQLException {
        return getNullableGuid( RDO_PRESSURETIMESERIES_FIELD_ID );
    }

    public Guid getRadomeDeviceTemperatureTimeseries( ) throws SQLException {
        return getNullableGuid( RDO_TEMPERATURETIMESERIES_FIELD_ID );
    }

    public Guid getRadomeDeviceDewPointTimeseries( ) throws SQLException {
        return getNullableGuid( RDO_DEWPOINTTIMESERIES_FIELD_ID );
    }

    public Guid getRadomeDeviceStatusTimeseries( ) throws SQLException {
        return getNullableGuid( RDO_STATUSTIMESERIES_FIELD_ID );
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

    public Guid getWeatherStationDeviceBarometricPressureTimeseries( ) throws SQLException {
        return getNullableGuid( WSD_BAROMETRICPRESSURETIMESERIES_FIELD_ID );
    }

    public Guid getWeatherStationDeviceAirTemperatureTimeseries( ) throws SQLException {
        return getNullableGuid( WSD_AIRTEMPERATURETIMESERIES_FIELD_ID );
    }

    public Guid getWeatherStationDeviceWaterTemperatureTimeseries( ) throws SQLException {
        return getNullableGuid( WSD_WATERTEMPERATURETIMESERIES_FIELD_ID );
    }

    public Guid getWeatherStationDeviceRelativeHumidityTimeseries( ) throws SQLException {
        return getNullableGuid( WSD_RELATIVEHUMIDITYTIMESERIES_FIELD_ID );
    }

    public Guid getWeatherStationDeviceAbsoluteHumidityTimeseries( ) throws SQLException {
        return getNullableGuid( WSD_ABSOLUTEHUMIDITYTIMESERIES_FIELD_ID );
    }

    public Guid getWeatherStationDeviceDewPointTimeseries( ) throws SQLException {
        return getNullableGuid( WSD_DEWPOINTTIMESERIES_FIELD_ID );
    }

    public Guid getWeatherStationDeviceWindDirectionTimeseries( ) throws SQLException {
        return getNullableGuid( WSD_WINDDIRECTIONTIMESERIES_FIELD_ID );
    }

    public Guid getWeatherStationDeviceWindSpeedTimeseries( ) throws SQLException {
        return getNullableGuid( WSD_WINDSPEEDTIMESERIES_FIELD_ID );
    }

    public Guid getWeatherStationDeviceGyro( ) throws SQLException {
        return getNullableGuid( WSD_GYRO_FIELD_ID );
    }

    public String getFacilityName( ) throws SQLException {
        return getString( F_NAME_FIELD_ID );
    }

    public Guid getFacilityType( ) throws SQLException {
        return getNullableGuid( F_TYPE_FIELD_ID );
    }

    public double getFacilityLongitude( ) throws SQLException {
        return getDouble( F_LONGITUDE_FIELD_ID );
    }

    public double getFacilityLatitude( ) throws SQLException {
        return getDouble( F_LATITUDE_FIELD_ID );
    }

    public double getFacilityAltitude( ) throws SQLException {
        return getDouble( F_ALTITUDE_FIELD_ID );
    }

    public String getAircraftName( ) throws SQLException {
        return getString( A_NAME_FIELD_ID );
    }

    public Guid getAircraftType( ) throws SQLException {
        return getNullableGuid( A_TYPE_FIELD_ID );
    }

    public String getAisAidToNavigationName( ) throws SQLException {
        return getString( AATN_NAME_FIELD_ID );
    }

    public Guid getAisAidToNavigationMMSI( ) throws SQLException {
        return getNullableGuid( AATN_MMSI_FIELD_ID );
    }

    public int getAisAidToNavigationNavigationalAidType( ) throws SQLException {
        return getInt32( AATN_NAVIGATIONALAIDTYPE_FIELD_ID );
    }

    public Guid getAisAidToNavigationPosition( ) throws SQLException {
        return getNullableGuid( AATN_POSITION_FIELD_ID );
    }

    public boolean getAisAidToNavigationIsVirtual( ) throws SQLException {
        return getBoolean( AATN_ISVIRTUAL_FIELD_ID );
    }

    public int getAisAidToNavigationToBow( ) throws SQLException {
        return getInt32( AATN_TOBOW_FIELD_ID );
    }

    public int getAisAidToNavigationToStern( ) throws SQLException {
        return getInt32( AATN_TOSTERN_FIELD_ID );
    }

    public int getAisAidToNavigationToPort( ) throws SQLException {
        return getInt32( AATN_TOPORT_FIELD_ID );
    }

    public int getAisAidToNavigationToStarboard( ) throws SQLException {
        return getInt32( AATN_TOSTARBOARD_FIELD_ID );
    }

    public Guid getAisAidToNavigationOffPositionTimeseries( ) throws SQLException {
        return getNullableGuid( AATN_OFFPOSITIONTIMESERIES_FIELD_ID );
    }

    public String getVehicleName( ) throws SQLException {
        return getString( V_NAME_FIELD_ID );
    }

    public Guid getVehicleType( ) throws SQLException {
        return getNullableGuid( V_TYPE_FIELD_ID );
    }

    public String getVesselName( ) throws SQLException {
        return getString( VSL_NAME_FIELD_ID );
    }

    public Guid getVesselType( ) throws SQLException {
        return getNullableGuid( VSL_TYPE_FIELD_ID );
    }

    public int getVesselToBow( ) throws SQLException {
        return getInt32( VSL_TOBOW_FIELD_ID );
    }

    public int getVesselToStern( ) throws SQLException {
        return getInt32( VSL_TOSTERN_FIELD_ID );
    }

    public int getVesselToPort( ) throws SQLException {
        return getInt32( VSL_TOPORT_FIELD_ID );
    }

    public int getVesselToStarboard( ) throws SQLException {
        return getInt32( VSL_TOSTARBOARD_FIELD_ID );
    }

    public Guid getVesselDraughtTimeseries( ) throws SQLException {
        return getNullableGuid( VSL_DRAUGHTTIMESERIES_FIELD_ID );
    }

    public Guid getVesselPersonsOnBoardTimeseries( ) throws SQLException {
        return getNullableGuid( VSL_PERSONSONBOARDTIMESERIES_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination ) throws SQLException {
        var kind = getObjectType( );
        switch(kind) {
            case Kind.BaseStation: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeStringUtf8( getBaseStationName( ) );
                destination.writeNullableGuid( getBaseStationType( ) );
            }
            break;
            case Kind.CameraDevice: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeGuid( getDeviceHost( ) );
                destination.writeStringUtf8( getDeviceName( ) );
                destination.writeStringUtf8( getDeviceDescription( ) );
                destination.writeNullableGuid( getDeviceEnabledTimeseries( ) );
            }
            break;
            case Kind.GNSSDevice: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeGuid( getDeviceHost( ) );
                destination.writeStringUtf8( getDeviceName( ) );
                destination.writeStringUtf8( getDeviceDescription( ) );
                destination.writeNullableGuid( getDeviceEnabledTimeseries( ) );
                destination.writeNullableGuid( getGNSSDeviceLatitudeTimeseries( ) );
                destination.writeNullableGuid( getGNSSDeviceLongitudeTimeseries( ) );
                destination.writeNullableGuid( getGNSSDeviceAltitudeTimeseries( ) );
            }
            break;
            case Kind.GyroDevice: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeGuid( getDeviceHost( ) );
                destination.writeStringUtf8( getDeviceName( ) );
                destination.writeStringUtf8( getDeviceDescription( ) );
                destination.writeNullableGuid( getDeviceEnabledTimeseries( ) );
                destination.writeNullableGuid( getGyroDeviceHeadingTrueNorthTimeseries( ) );
                destination.writeNullableGuid( getGyroDeviceHeadingMagneticNorthTimeseries( ) );
                destination.writeNullableGuid( getGyroDevicePitchTimeseries( ) );
                destination.writeNullableGuid( getGyroDeviceRateOfTurnTimeseries( ) );
                destination.writeNullableGuid( getGyroDeviceRollTimeseries( ) );
                destination.writeNullableGuid( getGyroDeviceCourseTimeseries( ) );
                destination.writeNullableGuid( getGyroDeviceSpeedTimeseries( ) );
                destination.writeNullableGuid( getGyroDeviceGNSSDevice( ) );
            }
            break;
            case Kind.LineInputDevice: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeGuid( getDeviceHost( ) );
                destination.writeStringUtf8( getDeviceName( ) );
                destination.writeStringUtf8( getDeviceDescription( ) );
                destination.writeNullableGuid( getDeviceEnabledTimeseries( ) );
            }
            break;
            case Kind.OilSpillDetectorDevice: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeGuid( getDeviceHost( ) );
                destination.writeStringUtf8( getDeviceName( ) );
                destination.writeStringUtf8( getDeviceDescription( ) );
                destination.writeNullableGuid( getDeviceEnabledTimeseries( ) );
            }
            break;
            case Kind.RadioDevice: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeGuid( getDeviceHost( ) );
                destination.writeStringUtf8( getDeviceName( ) );
                destination.writeStringUtf8( getDeviceDescription( ) );
                destination.writeNullableGuid( getDeviceEnabledTimeseries( ) );
            }
            break;
            case Kind.RadomeDevice: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeGuid( getDeviceHost( ) );
                destination.writeStringUtf8( getDeviceName( ) );
                destination.writeStringUtf8( getDeviceDescription( ) );
                destination.writeNullableGuid( getDeviceEnabledTimeseries( ) );
                destination.writeNullableGuid( getRadomeDeviceRadar( ) );
                destination.writeNullableGuid( getRadomeDevicePressureTimeseries( ) );
                destination.writeNullableGuid( getRadomeDeviceTemperatureTimeseries( ) );
                destination.writeNullableGuid( getRadomeDeviceDewPointTimeseries( ) );
                destination.writeNullableGuid( getRadomeDeviceStatusTimeseries( ) );
            }
            break;
            case Kind.AisDevice: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeGuid( getDeviceHost( ) );
                destination.writeStringUtf8( getDeviceName( ) );
                destination.writeStringUtf8( getDeviceDescription( ) );
                destination.writeNullableGuid( getDeviceEnabledTimeseries( ) );
            }
            break;
            case Kind.RadarDevice: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeGuid( getDeviceHost( ) );
                destination.writeStringUtf8( getDeviceName( ) );
                destination.writeStringUtf8( getDeviceDescription( ) );
                destination.writeNullableGuid( getDeviceEnabledTimeseries( ) );
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
            case Kind.WeatherStationDevice: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeGuid( getDeviceHost( ) );
                destination.writeStringUtf8( getDeviceName( ) );
                destination.writeStringUtf8( getDeviceDescription( ) );
                destination.writeNullableGuid( getDeviceEnabledTimeseries( ) );
                destination.writeNullableGuid( getWeatherStationDeviceBarometricPressureTimeseries( ) );
                destination.writeNullableGuid( getWeatherStationDeviceAirTemperatureTimeseries( ) );
                destination.writeNullableGuid( getWeatherStationDeviceWaterTemperatureTimeseries( ) );
                destination.writeNullableGuid( getWeatherStationDeviceRelativeHumidityTimeseries( ) );
                destination.writeNullableGuid( getWeatherStationDeviceAbsoluteHumidityTimeseries( ) );
                destination.writeNullableGuid( getWeatherStationDeviceDewPointTimeseries( ) );
                destination.writeNullableGuid( getWeatherStationDeviceWindDirectionTimeseries( ) );
                destination.writeNullableGuid( getWeatherStationDeviceWindSpeedTimeseries( ) );
                destination.writeNullableGuid( getWeatherStationDeviceGyro( ) );
            }
            break;
            case Kind.Facility: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeStringUtf8( getFacilityName( ) );
                destination.writeNullableGuid( getFacilityType( ) );
                destination.writeDouble( getFacilityLongitude( ) );
                destination.writeDouble( getFacilityLatitude( ) );
                destination.writeDouble( getFacilityAltitude( ) );
            }
            break;
            case Kind.Aircraft: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeStringUtf8( getAircraftName( ) );
                destination.writeNullableGuid( getAircraftType( ) );
            }
            break;
            case Kind.AisAidToNavigation: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeStringUtf8( getAisAidToNavigationName( ) );
                destination.writeNullableGuid( getAisAidToNavigationMMSI( ) );
                destination.writeInt32( getAisAidToNavigationNavigationalAidType( ) );
                destination.writeNullableGuid( getAisAidToNavigationPosition( ) );
                destination.writeBoolean( getAisAidToNavigationIsVirtual( ) );
                destination.writeInt32( getAisAidToNavigationToBow( ) );
                destination.writeInt32( getAisAidToNavigationToStern( ) );
                destination.writeInt32( getAisAidToNavigationToPort( ) );
                destination.writeInt32( getAisAidToNavigationToStarboard( ) );
                destination.writeNullableGuid( getAisAidToNavigationOffPositionTimeseries( ) );
            }
            break;
            case Kind.Vehicle: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeStringUtf8( getVehicleName( ) );
                destination.writeNullableGuid( getVehicleType( ) );
            }
            break;
            case Kind.Vessel: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeStringUtf8( getVesselName( ) );
                destination.writeNullableGuid( getVesselType( ) );
                destination.writeInt32( getVesselToBow( ) );
                destination.writeInt32( getVesselToStern( ) );
                destination.writeInt32( getVesselToPort( ) );
                destination.writeInt32( getVesselToStarboard( ) );
                destination.writeNullableGuid( getVesselDraughtTimeseries( ) );
                destination.writeNullableGuid( getVesselPersonsOnBoardTimeseries( ) );
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

    public ItemObject getDataObject( ) throws SQLException {
        var kind = getObjectType( );
        switch(kind) {
            case Kind.BaseStation: {
                return new BaseStationObject( ObjectState.Stored, getId( ), getRowVersion( ), getBaseStationName( ), getBaseStationType( ) );
            }
            case Kind.CameraDevice: {
                return new CameraDeviceObject( ObjectState.Stored, getId( ), getRowVersion( ), getDeviceHost( ), getDeviceName( ), getDeviceDescription( ), getDeviceEnabledTimeseries( ) );
            }
            case Kind.GNSSDevice: {
                return new GNSSDeviceObject( ObjectState.Stored, getId( ), getRowVersion( ), getDeviceHost( ), getDeviceName( ), getDeviceDescription( ), getDeviceEnabledTimeseries( ), getGNSSDeviceLatitudeTimeseries( ), getGNSSDeviceLongitudeTimeseries( ), getGNSSDeviceAltitudeTimeseries( ) );
            }
            case Kind.GyroDevice: {
                return new GyroDeviceObject( ObjectState.Stored, getId( ), getRowVersion( ), getDeviceHost( ), getDeviceName( ), getDeviceDescription( ), getDeviceEnabledTimeseries( ), getGyroDeviceHeadingTrueNorthTimeseries( ), getGyroDeviceHeadingMagneticNorthTimeseries( ), getGyroDevicePitchTimeseries( ), getGyroDeviceRateOfTurnTimeseries( ), getGyroDeviceRollTimeseries( ), getGyroDeviceCourseTimeseries( ), getGyroDeviceSpeedTimeseries( ), getGyroDeviceGNSSDevice( ) );
            }
            case Kind.LineInputDevice: {
                return new LineInputDeviceObject( ObjectState.Stored, getId( ), getRowVersion( ), getDeviceHost( ), getDeviceName( ), getDeviceDescription( ), getDeviceEnabledTimeseries( ) );
            }
            case Kind.OilSpillDetectorDevice: {
                return new OilSpillDetectorDeviceObject( ObjectState.Stored, getId( ), getRowVersion( ), getDeviceHost( ), getDeviceName( ), getDeviceDescription( ), getDeviceEnabledTimeseries( ) );
            }
            case Kind.RadioDevice: {
                return new RadioDeviceObject( ObjectState.Stored, getId( ), getRowVersion( ), getDeviceHost( ), getDeviceName( ), getDeviceDescription( ), getDeviceEnabledTimeseries( ) );
            }
            case Kind.RadomeDevice: {
                return new RadomeDeviceObject( ObjectState.Stored, getId( ), getRowVersion( ), getDeviceHost( ), getDeviceName( ), getDeviceDescription( ), getDeviceEnabledTimeseries( ), getRadomeDeviceRadar( ), getRadomeDevicePressureTimeseries( ), getRadomeDeviceTemperatureTimeseries( ), getRadomeDeviceDewPointTimeseries( ), getRadomeDeviceStatusTimeseries( ) );
            }
            case Kind.AisDevice: {
                return new AisDeviceObject( ObjectState.Stored, getId( ), getRowVersion( ), getDeviceHost( ), getDeviceName( ), getDeviceDescription( ), getDeviceEnabledTimeseries( ) );
            }
            case Kind.RadarDevice: {
                return new RadarDeviceObject( ObjectState.Stored, getId( ), getRowVersion( ), getDeviceHost( ), getDeviceName( ), getDeviceDescription( ), getDeviceEnabledTimeseries( ), getRadarDeviceSaveSettingsTimeseries( ), getRadarDevicePowerOnTimeseries( ), getRadarDeviceTrackingOnTimeseries( ), getRadarDeviceRadarPulseTimeseries( ), getRadarDeviceTuningTimeseries( ), getRadarDeviceBlankSector1Timeseries( ), getRadarDeviceSector1StartTimeseries( ), getRadarDeviceSector1EndTimeseries( ), getRadarDeviceBlankSector2Timeseries( ), getRadarDeviceSector2StartTimeseries( ), getRadarDeviceSector2EndTimeseries( ), getRadarDeviceEnableAutomaticFrequencyControlTimeseries( ), getRadarDeviceAzimuthOffsetTimeseries( ), getRadarDeviceEnableSensitivityTimeControlTimeseries( ), getRadarDeviceAutomaticSensitivityTimeControlTimeseries( ), getRadarDeviceSensitivityTimeControlLevelTimeseries( ), getRadarDeviceEnableFastTimeConstantTimeseries( ), getRadarDeviceFastTimeConstantLevelTimeseries( ), getRadarDeviceFastTimeConstantModeTimeseries( ), getRadarDeviceLatitudeTimeseries( ), getRadarDeviceLongitudeTimeseries( ), getRadarDeviceRadome( ), getRadarDeviceGNSSDevice( ) );
            }
            case Kind.WeatherStationDevice: {
                return new WeatherStationDeviceObject( ObjectState.Stored, getId( ), getRowVersion( ), getDeviceHost( ), getDeviceName( ), getDeviceDescription( ), getDeviceEnabledTimeseries( ), getWeatherStationDeviceBarometricPressureTimeseries( ), getWeatherStationDeviceAirTemperatureTimeseries( ), getWeatherStationDeviceWaterTemperatureTimeseries( ), getWeatherStationDeviceRelativeHumidityTimeseries( ), getWeatherStationDeviceAbsoluteHumidityTimeseries( ), getWeatherStationDeviceDewPointTimeseries( ), getWeatherStationDeviceWindDirectionTimeseries( ), getWeatherStationDeviceWindSpeedTimeseries( ), getWeatherStationDeviceGyro( ) );
            }
            case Kind.Facility: {
                return new FacilityObject( ObjectState.Stored, getId( ), getRowVersion( ), getFacilityName( ), getFacilityType( ), getFacilityLongitude( ), getFacilityLatitude( ), getFacilityAltitude( ) );
            }
            case Kind.Aircraft: {
                return new AircraftObject( ObjectState.Stored, getId( ), getRowVersion( ), getAircraftName( ), getAircraftType( ) );
            }
            case Kind.AisAidToNavigation: {
                return new AisAidToNavigationObject( ObjectState.Stored, getId( ), getRowVersion( ), getAisAidToNavigationName( ), getAisAidToNavigationMMSI( ), getAisAidToNavigationNavigationalAidType( ), getAisAidToNavigationPosition( ), getAisAidToNavigationIsVirtual( ), getAisAidToNavigationToBow( ), getAisAidToNavigationToStern( ), getAisAidToNavigationToPort( ), getAisAidToNavigationToStarboard( ), getAisAidToNavigationOffPositionTimeseries( ) );
            }
            case Kind.Vehicle: {
                return new VehicleObject( ObjectState.Stored, getId( ), getRowVersion( ), getVehicleName( ), getVehicleType( ) );
            }
            case Kind.Vessel: {
                return new VesselObject( ObjectState.Stored, getId( ), getRowVersion( ), getVesselName( ), getVesselType( ), getVesselToBow( ), getVesselToStern( ), getVesselToPort( ), getVesselToStarboard( ), getVesselDraughtTimeseries( ), getVesselPersonsOnBoardTimeseries( ) );
            }
            default: {
                var exc = new SQLException( "Cannot create an object for kind=" + kind + "." );
                throw exc;
            }
        }
    }

}

