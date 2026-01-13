/*
    Copyright 2024-2026 Espen Harlinn
 
    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at
 
        http://www.apache.org/licenses/LICENSE-2.0
 
    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/
package com.harlinn.barrelman.databases.mssql.readers.complex;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class ComplexDeviceDataReader extends ResultSetWrapper {

    public final static String BaseQuery = "SELECT \r\n" +
            "  d.[Id], \r\n" +
            "  d.[EntityType], \r\n" +
            "  d.[RowVersion], \r\n" +
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
            "  d.[Description] \r\n" +
            "FROM [DeviceView] d \r\n" +
            "  LEFT JOIN [CameraDevice] cd ON(d.[Id] = cd.[Id] ) \r\n" +
            "  LEFT JOIN [GNSSDevice] g ON(d.[Id] = g.[Id] ) \r\n" +
            "  LEFT JOIN [GyroDevice] gd ON(d.[Id] = gd.[Id] ) \r\n" +
            "  LEFT JOIN [LineInputDevice] lid ON(d.[Id] = lid.[Id] ) \r\n" +
            "  LEFT JOIN [OilSpillDetectorDevice] osdd ON(d.[Id] = osdd.[Id] ) \r\n" +
            "  LEFT JOIN [RadioDevice] rdi ON(d.[Id] = rdi.[Id] ) \r\n" +
            "  LEFT JOIN [RadomeDevice] rdo ON(d.[Id] = rdo.[Id] ) \r\n" +
            "  LEFT JOIN [TrackerDevice] td ON(d.[Id] = td.[Id] ) \r\n" +
            "  LEFT JOIN [AisDevice] ad ON(d.[Id] = ad.[Id] ) \r\n" +
            "  LEFT JOIN [RadarDevice] rd ON(d.[Id] = rd.[Id] ) \r\n" +
            "  LEFT JOIN [WeatherStationDevice] wsd ON(d.[Id] = wsd.[Id] ) \r\n";

    public final static String BaseViewName = "DeviceView";
    public final static String ViewAliasName = "d";

    public final static int D_ID_FIELD_ID = 1;
    public final static int D_KIND_FIELD_ID = 2;
    public final static int D_ROWVERSION_FIELD_ID = 3;
    public final static int D_HOST_FIELD_ID = 4;
    public final static int D_NAME_FIELD_ID = 5;
    public final static int D_ENABLEDTIMESERIES_FIELD_ID = 6;
    public final static int G_LATITUDETIMESERIES_FIELD_ID = 7;
    public final static int G_LONGITUDETIMESERIES_FIELD_ID = 8;
    public final static int G_ALTITUDETIMESERIES_FIELD_ID = 9;
    public final static int GD_HEADINGTRUENORTHTIMESERIES_FIELD_ID = 10;
    public final static int GD_HEADINGMAGNETICNORTHTIMESERIES_FIELD_ID = 11;
    public final static int GD_PITCHTIMESERIES_FIELD_ID = 12;
    public final static int GD_RATEOFTURNTIMESERIES_FIELD_ID = 13;
    public final static int GD_ROLLTIMESERIES_FIELD_ID = 14;
    public final static int GD_COURSETIMESERIES_FIELD_ID = 15;
    public final static int GD_SPEEDTIMESERIES_FIELD_ID = 16;
    public final static int GD_GNSSDEVICE_FIELD_ID = 17;
    public final static int RDO_RADAR_FIELD_ID = 18;
    public final static int RDO_PRESSURETIMESERIES_FIELD_ID = 19;
    public final static int RDO_TEMPERATURETIMESERIES_FIELD_ID = 20;
    public final static int RDO_DEWPOINTTIMESERIES_FIELD_ID = 21;
    public final static int RDO_STATUSTIMESERIES_FIELD_ID = 22;
    public final static int RD_SAVESETTINGSTIMESERIES_FIELD_ID = 23;
    public final static int RD_POWERONTIMESERIES_FIELD_ID = 24;
    public final static int RD_TRACKINGONTIMESERIES_FIELD_ID = 25;
    public final static int RD_RADARPULSETIMESERIES_FIELD_ID = 26;
    public final static int RD_TUNINGTIMESERIES_FIELD_ID = 27;
    public final static int RD_BLANKSECTOR1TIMESERIES_FIELD_ID = 28;
    public final static int RD_SECTOR1STARTTIMESERIES_FIELD_ID = 29;
    public final static int RD_SECTOR1ENDTIMESERIES_FIELD_ID = 30;
    public final static int RD_BLANKSECTOR2TIMESERIES_FIELD_ID = 31;
    public final static int RD_SECTOR2STARTTIMESERIES_FIELD_ID = 32;
    public final static int RD_SECTOR2ENDTIMESERIES_FIELD_ID = 33;
    public final static int RD_ENABLEAUTOMATICFREQUENCYCONTROLTIMESERIES_FIELD_ID = 34;
    public final static int RD_AZIMUTHOFFSETTIMESERIES_FIELD_ID = 35;
    public final static int RD_ENABLESENSITIVITYTIMECONTROLTIMESERIES_FIELD_ID = 36;
    public final static int RD_AUTOMATICSENSITIVITYTIMECONTROLTIMESERIES_FIELD_ID = 37;
    public final static int RD_SENSITIVITYTIMECONTROLLEVELTIMESERIES_FIELD_ID = 38;
    public final static int RD_ENABLEFASTTIMECONSTANTTIMESERIES_FIELD_ID = 39;
    public final static int RD_FASTTIMECONSTANTLEVELTIMESERIES_FIELD_ID = 40;
    public final static int RD_FASTTIMECONSTANTMODETIMESERIES_FIELD_ID = 41;
    public final static int RD_LATITUDETIMESERIES_FIELD_ID = 42;
    public final static int RD_LONGITUDETIMESERIES_FIELD_ID = 43;
    public final static int RD_RADOME_FIELD_ID = 44;
    public final static int RD_GNSSDEVICE_FIELD_ID = 45;
    public final static int WSD_BAROMETRICPRESSURETIMESERIES_FIELD_ID = 46;
    public final static int WSD_AIRTEMPERATURETIMESERIES_FIELD_ID = 47;
    public final static int WSD_WATERTEMPERATURETIMESERIES_FIELD_ID = 48;
    public final static int WSD_RELATIVEHUMIDITYTIMESERIES_FIELD_ID = 49;
    public final static int WSD_ABSOLUTEHUMIDITYTIMESERIES_FIELD_ID = 50;
    public final static int WSD_DEWPOINTTIMESERIES_FIELD_ID = 51;
    public final static int WSD_WINDDIRECTIONTIMESERIES_FIELD_ID = 52;
    public final static int WSD_WINDSPEEDTIMESERIES_FIELD_ID = 53;
    public final static int WSD_GYRO_FIELD_ID = 54;
    public final static int D_DESCRIPTION_FIELD_ID = 55;

    public ComplexDeviceDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public Guid getId( ) throws SQLException {
        return getGuid( D_ID_FIELD_ID );
    }

    public int getObjectType() throws SQLException {
        return getInt32( D_KIND_FIELD_ID );
    }

    public long getRowVersion( ) throws SQLException {
        return getInt64( D_ROWVERSION_FIELD_ID );
    }

    public Guid getHost( ) throws SQLException {
        return getGuid( D_HOST_FIELD_ID );
    }

    public String getName( ) throws SQLException {
        return getString( D_NAME_FIELD_ID );
    }

    public String getDescription( ) throws SQLException {
        return getString( D_DESCRIPTION_FIELD_ID );
    }

    public Guid getEnabledTimeseries( ) throws SQLException {
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

    public void writeTo(BinaryWriter destination ) throws SQLException {
        var kind = getObjectType( );
        switch(kind) {
            case Kind.CameraDevice: {
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
            case Kind.GNSSDevice: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeGuid( getHost( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeStringUtf8( getDescription( ) );
                destination.writeNullableGuid( getEnabledTimeseries( ) );
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
                destination.writeGuid( getHost( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeStringUtf8( getDescription( ) );
                destination.writeNullableGuid( getEnabledTimeseries( ) );
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
                destination.writeGuid( getHost( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeStringUtf8( getDescription( ) );
                destination.writeNullableGuid( getEnabledTimeseries( ) );
            }
            break;
            case Kind.OilSpillDetectorDevice: {
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
            case Kind.RadioDevice: {
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
            case Kind.RadomeDevice: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeGuid( getHost( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeStringUtf8( getDescription( ) );
                destination.writeNullableGuid( getEnabledTimeseries( ) );
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
            case Kind.WeatherStationDevice: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeGuid( getHost( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeStringUtf8( getDescription( ) );
                destination.writeNullableGuid( getEnabledTimeseries( ) );
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

    public DeviceObject getDataObject( ) throws SQLException {
        var kind = getObjectType( );
        switch(kind) {
            case Kind.CameraDevice: {
                return new CameraDeviceObject( ObjectState.Stored, getId( ), getRowVersion( ), getHost( ), getName( ), getDescription( ), getEnabledTimeseries( ) );
            }
            case Kind.GNSSDevice: {
                return new GNSSDeviceObject( ObjectState.Stored, getId( ), getRowVersion( ), getHost( ), getName( ), getDescription( ), getEnabledTimeseries( ), getGNSSDeviceLatitudeTimeseries( ), getGNSSDeviceLongitudeTimeseries( ), getGNSSDeviceAltitudeTimeseries( ) );
            }
            case Kind.GyroDevice: {
                return new GyroDeviceObject( ObjectState.Stored, getId( ), getRowVersion( ), getHost( ), getName( ), getDescription( ), getEnabledTimeseries( ), getGyroDeviceHeadingTrueNorthTimeseries( ), getGyroDeviceHeadingMagneticNorthTimeseries( ), getGyroDevicePitchTimeseries( ), getGyroDeviceRateOfTurnTimeseries( ), getGyroDeviceRollTimeseries( ), getGyroDeviceCourseTimeseries( ), getGyroDeviceSpeedTimeseries( ), getGyroDeviceGNSSDevice( ) );
            }
            case Kind.LineInputDevice: {
                return new LineInputDeviceObject( ObjectState.Stored, getId( ), getRowVersion( ), getHost( ), getName( ), getDescription( ), getEnabledTimeseries( ) );
            }
            case Kind.OilSpillDetectorDevice: {
                return new OilSpillDetectorDeviceObject( ObjectState.Stored, getId( ), getRowVersion( ), getHost( ), getName( ), getDescription( ), getEnabledTimeseries( ) );
            }
            case Kind.RadioDevice: {
                return new RadioDeviceObject( ObjectState.Stored, getId( ), getRowVersion( ), getHost( ), getName( ), getDescription( ), getEnabledTimeseries( ) );
            }
            case Kind.RadomeDevice: {
                return new RadomeDeviceObject( ObjectState.Stored, getId( ), getRowVersion( ), getHost( ), getName( ), getDescription( ), getEnabledTimeseries( ), getRadomeDeviceRadar( ), getRadomeDevicePressureTimeseries( ), getRadomeDeviceTemperatureTimeseries( ), getRadomeDeviceDewPointTimeseries( ), getRadomeDeviceStatusTimeseries( ) );
            }
            case Kind.AisDevice: {
                return new AisDeviceObject( ObjectState.Stored, getId( ), getRowVersion( ), getHost( ), getName( ), getDescription( ), getEnabledTimeseries( ) );
            }
            case Kind.RadarDevice: {
                return new RadarDeviceObject( ObjectState.Stored, getId( ), getRowVersion( ), getHost( ), getName( ), getDescription( ), getEnabledTimeseries( ), getRadarDeviceSaveSettingsTimeseries( ), getRadarDevicePowerOnTimeseries( ), getRadarDeviceTrackingOnTimeseries( ), getRadarDeviceRadarPulseTimeseries( ), getRadarDeviceTuningTimeseries( ), getRadarDeviceBlankSector1Timeseries( ), getRadarDeviceSector1StartTimeseries( ), getRadarDeviceSector1EndTimeseries( ), getRadarDeviceBlankSector2Timeseries( ), getRadarDeviceSector2StartTimeseries( ), getRadarDeviceSector2EndTimeseries( ), getRadarDeviceEnableAutomaticFrequencyControlTimeseries( ), getRadarDeviceAzimuthOffsetTimeseries( ), getRadarDeviceEnableSensitivityTimeControlTimeseries( ), getRadarDeviceAutomaticSensitivityTimeControlTimeseries( ), getRadarDeviceSensitivityTimeControlLevelTimeseries( ), getRadarDeviceEnableFastTimeConstantTimeseries( ), getRadarDeviceFastTimeConstantLevelTimeseries( ), getRadarDeviceFastTimeConstantModeTimeseries( ), getRadarDeviceLatitudeTimeseries( ), getRadarDeviceLongitudeTimeseries( ), getRadarDeviceRadome( ), getRadarDeviceGNSSDevice( ) );
            }
            case Kind.WeatherStationDevice: {
                return new WeatherStationDeviceObject( ObjectState.Stored, getId( ), getRowVersion( ), getHost( ), getName( ), getDescription( ), getEnabledTimeseries( ), getWeatherStationDeviceBarometricPressureTimeseries( ), getWeatherStationDeviceAirTemperatureTimeseries( ), getWeatherStationDeviceWaterTemperatureTimeseries( ), getWeatherStationDeviceRelativeHumidityTimeseries( ), getWeatherStationDeviceAbsoluteHumidityTimeseries( ), getWeatherStationDeviceDewPointTimeseries( ), getWeatherStationDeviceWindDirectionTimeseries( ), getWeatherStationDeviceWindSpeedTimeseries( ), getWeatherStationDeviceGyro( ) );
            }
            default: {
                var exc = new SQLException( "Cannot create an object for kind=" + kind + "." );
                throw exc;
            }
        }
    }

}

