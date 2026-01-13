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

public class ComplexTimeseriesDataReader extends ResultSetWrapper {

    public final static String BaseQuery = "SELECT \r\n" +
            "  t.[Id], \r\n" +
            "  t.[EntityType], \r\n" +
            "  t.[RowVersion], \r\n" +
            "  t.[Catalog], \r\n" +
            "  t.[Name], \r\n" +
            "  t.[MaxRetention], \r\n" +
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
            "  rtt.[Radar], \r\n" +
            "  gats.[GNSSDevice], \r\n" +
            "  glats.[GNSSDevice], \r\n" +
            "  glots.[GNSSDevice], \r\n" +
            "  gct.[GyroDevice], \r\n" +
            "  ghmnt.[GyroDevice], \r\n" +
            "  ghtnt.[GyroDevice], \r\n" +
            "  gpt.[GyroDevice], \r\n" +
            "  grott.[GyroDevice], \r\n" +
            "  grt.[GyroDevice], \r\n" +
            "  gst.[GyroDevice], \r\n" +
            "  rlats.[Radar], \r\n" +
            "  rlots.[Radar], \r\n" +
            "  rdpt.[Radome], \r\n" +
            "  rpt.[Radome], \r\n" +
            "  rtets.[Radome], \r\n" +
            "  vdt.[Vessel], \r\n" +
            "  vlats.[View], \r\n" +
            "  vlots.[View], \r\n" +
            "  vzlt.[View], \r\n" +
            "  wsaht.[WeatherStation], \r\n" +
            "  wsatt.[WeatherStation], \r\n" +
            "  wsbpt.[WeatherStation], \r\n" +
            "  wsdpt.[WeatherStation], \r\n" +
            "  wsrht.[WeatherStation], \r\n" +
            "  wswtt.[WeatherStation], \r\n" +
            "  wswdt.[WeatherStation], \r\n" +
            "  wswst.[WeatherStation], \r\n" +
            "  aatnpt.[AidToNavigation], \r\n" +
            "  raot.[Radar], \r\n" +
            "  rftclt.[Radar], \r\n" +
            "  rftcmt.[Radar], \r\n" +
            "  rapts.[Radar], \r\n" +
            "  rs1et.[Radar], \r\n" +
            "  rs1st.[Radar], \r\n" +
            "  rs2et.[Radar], \r\n" +
            "  rs2st.[Radar], \r\n" +
            "  rstclt.[Radar], \r\n" +
            "  ratuts.[Radar], \r\n" +
            "  vpobt.[Vessel], \r\n" +
            "  rst.[Radome] \r\n" +
            "FROM [TimeseriesView] t \r\n" +
            "  LEFT JOIN [BinaryTimeseries] bt ON(t.[Id] = bt.[Id] ) \r\n" +
            "  LEFT JOIN [BooleanTimeseries] bots ON(t.[Id] = bots.[Id] ) \r\n" +
            "  LEFT JOIN [AisAidToNavigationOffPositionTimeseries] aatnopt ON(t.[Id] = aatnopt.[Id] ) \r\n" +
            "  LEFT JOIN [DeviceEnabledTimeseries] det ON(t.[Id] = det.[Id] ) \r\n" +
            "  LEFT JOIN [MediaProxySessionEnabledTimeseries] mpset ON(t.[Id] = mpset.[Id] ) \r\n" +
            "  LEFT JOIN [MediaServiceEnabledTimeseries] mset ON(t.[Id] = mset.[Id] ) \r\n" +
            "  LEFT JOIN [RadarAutomaticSensitivityTimeControlTimeseries] rastct ON(t.[Id] = rastct.[Id] ) \r\n" +
            "  LEFT JOIN [RadarBlankSector1Timeseries] rbs1t ON(t.[Id] = rbs1t.[Id] ) \r\n" +
            "  LEFT JOIN [RadarBlankSector2Timeseries] rbs2t ON(t.[Id] = rbs2t.[Id] ) \r\n" +
            "  LEFT JOIN [RadarEnableAutomaticFrequencyControlTimeseries] reafct ON(t.[Id] = reafct.[Id] ) \r\n" +
            "  LEFT JOIN [RadarEnableFastTimeConstantTimeseries] reftct ON(t.[Id] = reftct.[Id] ) \r\n" +
            "  LEFT JOIN [RadarEnableSensitivityTimeControlTimeseries] restct ON(t.[Id] = restct.[Id] ) \r\n" +
            "  LEFT JOIN [RadarPowerOnTimeseries] rpot ON(t.[Id] = rpot.[Id] ) \r\n" +
            "  LEFT JOIN [RadarSaveSettingsTimeseries] rsst ON(t.[Id] = rsst.[Id] ) \r\n" +
            "  LEFT JOIN [RadarTrackingTimeseries] rtt ON(t.[Id] = rtt.[Id] ) \r\n" +
            "  LEFT JOIN [ByteTimeseries] byts ON(t.[Id] = byts.[Id] ) \r\n" +
            "  LEFT JOIN [DateTimeTimeseries] dtt ON(t.[Id] = dtt.[Id] ) \r\n" +
            "  LEFT JOIN [DoubleTimeseries] dt ON(t.[Id] = dt.[Id] ) \r\n" +
            "  LEFT JOIN [GNSSAltitudeTimeseries] gats ON(t.[Id] = gats.[Id] ) \r\n" +
            "  LEFT JOIN [GNSSLatitudeTimeseries] glats ON(t.[Id] = glats.[Id] ) \r\n" +
            "  LEFT JOIN [GNSSLongitudeTimeseries] glots ON(t.[Id] = glots.[Id] ) \r\n" +
            "  LEFT JOIN [GyroCourseTimeseries] gct ON(t.[Id] = gct.[Id] ) \r\n" +
            "  LEFT JOIN [GyroHeadingMagneticNorthTimeseries] ghmnt ON(t.[Id] = ghmnt.[Id] ) \r\n" +
            "  LEFT JOIN [GyroHeadingTrueNorthTimeseries] ghtnt ON(t.[Id] = ghtnt.[Id] ) \r\n" +
            "  LEFT JOIN [GyroPitchTimeseries] gpt ON(t.[Id] = gpt.[Id] ) \r\n" +
            "  LEFT JOIN [GyroRateOfTurnTimeseries] grott ON(t.[Id] = grott.[Id] ) \r\n" +
            "  LEFT JOIN [GyroRollTimeseries] grt ON(t.[Id] = grt.[Id] ) \r\n" +
            "  LEFT JOIN [GyroSpeedTimeseries] gst ON(t.[Id] = gst.[Id] ) \r\n" +
            "  LEFT JOIN [RadarLatitudeTimeseries] rlats ON(t.[Id] = rlats.[Id] ) \r\n" +
            "  LEFT JOIN [RadarLongitudeTimeseries] rlots ON(t.[Id] = rlots.[Id] ) \r\n" +
            "  LEFT JOIN [RadomeDewPointTimeseries] rdpt ON(t.[Id] = rdpt.[Id] ) \r\n" +
            "  LEFT JOIN [RadomePressureTimeseries] rpt ON(t.[Id] = rpt.[Id] ) \r\n" +
            "  LEFT JOIN [RadomeTemperatureTimeseries] rtets ON(t.[Id] = rtets.[Id] ) \r\n" +
            "  LEFT JOIN [VesselDraughtTimeseries] vdt ON(t.[Id] = vdt.[Id] ) \r\n" +
            "  LEFT JOIN [ViewLatitudeTimeseries] vlats ON(t.[Id] = vlats.[Id] ) \r\n" +
            "  LEFT JOIN [ViewLongitudeTimeseries] vlots ON(t.[Id] = vlots.[Id] ) \r\n" +
            "  LEFT JOIN [ViewZoomLevelTimeseries] vzlt ON(t.[Id] = vzlt.[Id] ) \r\n" +
            "  LEFT JOIN [WeatherStationAbsoluteHumidityTimeseries] wsaht ON(t.[Id] = wsaht.[Id] ) \r\n" +
            "  LEFT JOIN [WeatherStationAirTemperatureTimeseries] wsatt ON(t.[Id] = wsatt.[Id] ) \r\n" +
            "  LEFT JOIN [WeatherStationBarometricPressureTimeseries] wsbpt ON(t.[Id] = wsbpt.[Id] ) \r\n" +
            "  LEFT JOIN [WeatherStationDewPointTimeseries] wsdpt ON(t.[Id] = wsdpt.[Id] ) \r\n" +
            "  LEFT JOIN [WeatherStationRelativeHumidityTimeseries] wsrht ON(t.[Id] = wsrht.[Id] ) \r\n" +
            "  LEFT JOIN [WeatherStationWaterTemperatureTimeseries] wswtt ON(t.[Id] = wswtt.[Id] ) \r\n" +
            "  LEFT JOIN [WeatherStationWindDirectionTimeseries] wswdt ON(t.[Id] = wswdt.[Id] ) \r\n" +
            "  LEFT JOIN [WeatherStationWindSpeedTimeseries] wswst ON(t.[Id] = wswst.[Id] ) \r\n" +
            "  LEFT JOIN [GeoPosition2DTimeseries] gp2d ON(t.[Id] = gp2d.[Id] ) \r\n" +
            "  LEFT JOIN [AisAidToNavigationPositionTimeseries] aatnpt ON(t.[Id] = aatnpt.[Id] ) \r\n" +
            "  LEFT JOIN [GeoPosition3DTimeseries] gp3d ON(t.[Id] = gp3d.[Id] ) \r\n" +
            "  LEFT JOIN [GuidTimeseries] gt ON(t.[Id] = gt.[Id] ) \r\n" +
            "  LEFT JOIN [Int16Timeseries] i16t ON(t.[Id] = i16t.[Id] ) \r\n" +
            "  LEFT JOIN [Int32Timeseries] i32t ON(t.[Id] = i32t.[Id] ) \r\n" +
            "  LEFT JOIN [RadarAzimuthOffsetTimeseries] raot ON(t.[Id] = raot.[Id] ) \r\n" +
            "  LEFT JOIN [RadarFastTimeConstantLevelTimeseries] rftclt ON(t.[Id] = rftclt.[Id] ) \r\n" +
            "  LEFT JOIN [RadarFastTimeConstantModeTimeseries] rftcmt ON(t.[Id] = rftcmt.[Id] ) \r\n" +
            "  LEFT JOIN [RadarPulseTimeseries] rapts ON(t.[Id] = rapts.[Id] ) \r\n" +
            "  LEFT JOIN [RadarSector1EndTimeseries] rs1et ON(t.[Id] = rs1et.[Id] ) \r\n" +
            "  LEFT JOIN [RadarSector1StartTimeseries] rs1st ON(t.[Id] = rs1st.[Id] ) \r\n" +
            "  LEFT JOIN [RadarSector2EndTimeseries] rs2et ON(t.[Id] = rs2et.[Id] ) \r\n" +
            "  LEFT JOIN [RadarSector2StartTimeseries] rs2st ON(t.[Id] = rs2st.[Id] ) \r\n" +
            "  LEFT JOIN [RadarSensitivityTimeControlLevelTimeseries] rstclt ON(t.[Id] = rstclt.[Id] ) \r\n" +
            "  LEFT JOIN [RadarTuningTimeseries] ratuts ON(t.[Id] = ratuts.[Id] ) \r\n" +
            "  LEFT JOIN [VesselPersonsOnBoardTimeseries] vpobt ON(t.[Id] = vpobt.[Id] ) \r\n" +
            "  LEFT JOIN [Int64Timeseries] i64t ON(t.[Id] = i64t.[Id] ) \r\n" +
            "  LEFT JOIN [Position2DTimeseries] p2d ON(t.[Id] = p2d.[Id] ) \r\n" +
            "  LEFT JOIN [Position3DTimeseries] p3d ON(t.[Id] = p3d.[Id] ) \r\n" +
            "  LEFT JOIN [ReferenceTimeseries] rt ON(t.[Id] = rt.[Id] ) \r\n" +
            "  LEFT JOIN [SByteTimeseries] st ON(t.[Id] = st.[Id] ) \r\n" +
            "  LEFT JOIN [SingleTimeseries] sits ON(t.[Id] = sits.[Id] ) \r\n" +
            "  LEFT JOIN [StringTimeseries] stts ON(t.[Id] = stts.[Id] ) \r\n" +
            "  LEFT JOIN [TimeSpanTimeseries] tst ON(t.[Id] = tst.[Id] ) \r\n" +
            "  LEFT JOIN [UInt16Timeseries] u16t ON(t.[Id] = u16t.[Id] ) \r\n" +
            "  LEFT JOIN [UInt32Timeseries] u32t ON(t.[Id] = u32t.[Id] ) \r\n" +
            "  LEFT JOIN [RadomeStatusTimeseries] rst ON(t.[Id] = rst.[Id] ) \r\n" +
            "  LEFT JOIN [UInt64Timeseries] u64t ON(t.[Id] = u64t.[Id] ) \r\n";

    public final static String BaseViewName = "TimeseriesView";
    public final static String ViewAliasName = "t";

    public final static int T_ID_FIELD_ID = 1;
    public final static int T_KIND_FIELD_ID = 2;
    public final static int T_ROWVERSION_FIELD_ID = 3;
    public final static int T_CATALOG_FIELD_ID = 4;
    public final static int T_NAME_FIELD_ID = 5;
    public final static int T_MAXRETENTION_FIELD_ID = 6;
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
    public final static int GATS_GNSSDEVICE_FIELD_ID = 20;
    public final static int GLATS_GNSSDEVICE_FIELD_ID = 21;
    public final static int GLOTS_GNSSDEVICE_FIELD_ID = 22;
    public final static int GCT_GYRODEVICE_FIELD_ID = 23;
    public final static int GHMNT_GYRODEVICE_FIELD_ID = 24;
    public final static int GHTNT_GYRODEVICE_FIELD_ID = 25;
    public final static int GPT_GYRODEVICE_FIELD_ID = 26;
    public final static int GROTT_GYRODEVICE_FIELD_ID = 27;
    public final static int GRT_GYRODEVICE_FIELD_ID = 28;
    public final static int GST_GYRODEVICE_FIELD_ID = 29;
    public final static int RLATS_RADAR_FIELD_ID = 30;
    public final static int RLOTS_RADAR_FIELD_ID = 31;
    public final static int RDPT_RADOME_FIELD_ID = 32;
    public final static int RPT_RADOME_FIELD_ID = 33;
    public final static int RTETS_RADOME_FIELD_ID = 34;
    public final static int VDT_VESSEL_FIELD_ID = 35;
    public final static int VLATS_VIEW_FIELD_ID = 36;
    public final static int VLOTS_VIEW_FIELD_ID = 37;
    public final static int VZLT_VIEW_FIELD_ID = 38;
    public final static int WSAHT_WEATHERSTATION_FIELD_ID = 39;
    public final static int WSATT_WEATHERSTATION_FIELD_ID = 40;
    public final static int WSBPT_WEATHERSTATION_FIELD_ID = 41;
    public final static int WSDPT_WEATHERSTATION_FIELD_ID = 42;
    public final static int WSRHT_WEATHERSTATION_FIELD_ID = 43;
    public final static int WSWTT_WEATHERSTATION_FIELD_ID = 44;
    public final static int WSWDT_WEATHERSTATION_FIELD_ID = 45;
    public final static int WSWST_WEATHERSTATION_FIELD_ID = 46;
    public final static int AATNPT_AIDTONAVIGATION_FIELD_ID = 47;
    public final static int RAOT_RADAR_FIELD_ID = 48;
    public final static int RFTCLT_RADAR_FIELD_ID = 49;
    public final static int RFTCMT_RADAR_FIELD_ID = 50;
    public final static int RAPTS_RADAR_FIELD_ID = 51;
    public final static int RS1ET_RADAR_FIELD_ID = 52;
    public final static int RS1ST_RADAR_FIELD_ID = 53;
    public final static int RS2ET_RADAR_FIELD_ID = 54;
    public final static int RS2ST_RADAR_FIELD_ID = 55;
    public final static int RSTCLT_RADAR_FIELD_ID = 56;
    public final static int RATUTS_RADAR_FIELD_ID = 57;
    public final static int VPOBT_VESSEL_FIELD_ID = 58;
    public final static int RST_RADOME_FIELD_ID = 59;

    public ComplexTimeseriesDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public Guid getId( ) throws SQLException {
        return getGuid( T_ID_FIELD_ID );
    }

    public int getObjectType() throws SQLException {
        return getInt32( T_KIND_FIELD_ID );
    }

    public long getRowVersion( ) throws SQLException {
        return getInt64( T_ROWVERSION_FIELD_ID );
    }

    public Guid getCatalog( ) throws SQLException {
        return getNullableGuid( T_CATALOG_FIELD_ID );
    }

    public String getName( ) throws SQLException {
        return getString( T_NAME_FIELD_ID );
    }

    public TimeSpan getMaxRetention( ) throws SQLException {
        return getTimeSpan( T_MAXRETENTION_FIELD_ID );
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

    public Guid getGNSSAltitudeTimeseriesGNSSDevice( ) throws SQLException {
        return getNullableGuid( GATS_GNSSDEVICE_FIELD_ID );
    }

    public Guid getGNSSLatitudeTimeseriesGNSSDevice( ) throws SQLException {
        return getNullableGuid( GLATS_GNSSDEVICE_FIELD_ID );
    }

    public Guid getGNSSLongitudeTimeseriesGNSSDevice( ) throws SQLException {
        return getNullableGuid( GLOTS_GNSSDEVICE_FIELD_ID );
    }

    public Guid getGyroCourseTimeseriesGyroDevice( ) throws SQLException {
        return getNullableGuid( GCT_GYRODEVICE_FIELD_ID );
    }

    public Guid getGyroHeadingMagneticNorthTimeseriesGyroDevice( ) throws SQLException {
        return getNullableGuid( GHMNT_GYRODEVICE_FIELD_ID );
    }

    public Guid getGyroHeadingTrueNorthTimeseriesGyroDevice( ) throws SQLException {
        return getNullableGuid( GHTNT_GYRODEVICE_FIELD_ID );
    }

    public Guid getGyroPitchTimeseriesGyroDevice( ) throws SQLException {
        return getNullableGuid( GPT_GYRODEVICE_FIELD_ID );
    }

    public Guid getGyroRateOfTurnTimeseriesGyroDevice( ) throws SQLException {
        return getNullableGuid( GROTT_GYRODEVICE_FIELD_ID );
    }

    public Guid getGyroRollTimeseriesGyroDevice( ) throws SQLException {
        return getNullableGuid( GRT_GYRODEVICE_FIELD_ID );
    }

    public Guid getGyroSpeedTimeseriesGyroDevice( ) throws SQLException {
        return getNullableGuid( GST_GYRODEVICE_FIELD_ID );
    }

    public Guid getRadarLatitudeTimeseriesRadar( ) throws SQLException {
        return getNullableGuid( RLATS_RADAR_FIELD_ID );
    }

    public Guid getRadarLongitudeTimeseriesRadar( ) throws SQLException {
        return getNullableGuid( RLOTS_RADAR_FIELD_ID );
    }

    public Guid getRadomeDewPointTimeseriesRadome( ) throws SQLException {
        return getNullableGuid( RDPT_RADOME_FIELD_ID );
    }

    public Guid getRadomePressureTimeseriesRadome( ) throws SQLException {
        return getNullableGuid( RPT_RADOME_FIELD_ID );
    }

    public Guid getRadomeTemperatureTimeseriesRadome( ) throws SQLException {
        return getNullableGuid( RTETS_RADOME_FIELD_ID );
    }

    public Guid getVesselDraughtTimeseriesVessel( ) throws SQLException {
        return getNullableGuid( VDT_VESSEL_FIELD_ID );
    }

    public Guid getViewLatitudeTimeseriesView( ) throws SQLException {
        return getNullableGuid( VLATS_VIEW_FIELD_ID );
    }

    public Guid getViewLongitudeTimeseriesView( ) throws SQLException {
        return getNullableGuid( VLOTS_VIEW_FIELD_ID );
    }

    public Guid getViewZoomLevelTimeseriesView( ) throws SQLException {
        return getNullableGuid( VZLT_VIEW_FIELD_ID );
    }

    public Guid getWeatherStationAbsoluteHumidityTimeseriesWeatherStation( ) throws SQLException {
        return getNullableGuid( WSAHT_WEATHERSTATION_FIELD_ID );
    }

    public Guid getWeatherStationAirTemperatureTimeseriesWeatherStation( ) throws SQLException {
        return getNullableGuid( WSATT_WEATHERSTATION_FIELD_ID );
    }

    public Guid getWeatherStationBarometricPressureTimeseriesWeatherStation( ) throws SQLException {
        return getNullableGuid( WSBPT_WEATHERSTATION_FIELD_ID );
    }

    public Guid getWeatherStationDewPointTimeseriesWeatherStation( ) throws SQLException {
        return getNullableGuid( WSDPT_WEATHERSTATION_FIELD_ID );
    }

    public Guid getWeatherStationRelativeHumidityTimeseriesWeatherStation( ) throws SQLException {
        return getNullableGuid( WSRHT_WEATHERSTATION_FIELD_ID );
    }

    public Guid getWeatherStationWaterTemperatureTimeseriesWeatherStation( ) throws SQLException {
        return getNullableGuid( WSWTT_WEATHERSTATION_FIELD_ID );
    }

    public Guid getWeatherStationWindDirectionTimeseriesWeatherStation( ) throws SQLException {
        return getNullableGuid( WSWDT_WEATHERSTATION_FIELD_ID );
    }

    public Guid getWeatherStationWindSpeedTimeseriesWeatherStation( ) throws SQLException {
        return getNullableGuid( WSWST_WEATHERSTATION_FIELD_ID );
    }

    public Guid getAisAidToNavigationPositionTimeseriesAidToNavigation( ) throws SQLException {
        return getNullableGuid( AATNPT_AIDTONAVIGATION_FIELD_ID );
    }

    public Guid getRadarAzimuthOffsetTimeseriesRadar( ) throws SQLException {
        return getNullableGuid( RAOT_RADAR_FIELD_ID );
    }

    public Guid getRadarFastTimeConstantLevelTimeseriesRadar( ) throws SQLException {
        return getNullableGuid( RFTCLT_RADAR_FIELD_ID );
    }

    public Guid getRadarFastTimeConstantModeTimeseriesRadar( ) throws SQLException {
        return getNullableGuid( RFTCMT_RADAR_FIELD_ID );
    }

    public Guid getRadarPulseTimeseriesRadar( ) throws SQLException {
        return getNullableGuid( RAPTS_RADAR_FIELD_ID );
    }

    public Guid getRadarSector1EndTimeseriesRadar( ) throws SQLException {
        return getNullableGuid( RS1ET_RADAR_FIELD_ID );
    }

    public Guid getRadarSector1StartTimeseriesRadar( ) throws SQLException {
        return getNullableGuid( RS1ST_RADAR_FIELD_ID );
    }

    public Guid getRadarSector2EndTimeseriesRadar( ) throws SQLException {
        return getNullableGuid( RS2ET_RADAR_FIELD_ID );
    }

    public Guid getRadarSector2StartTimeseriesRadar( ) throws SQLException {
        return getNullableGuid( RS2ST_RADAR_FIELD_ID );
    }

    public Guid getRadarSensitivityTimeControlLevelTimeseriesRadar( ) throws SQLException {
        return getNullableGuid( RSTCLT_RADAR_FIELD_ID );
    }

    public Guid getRadarTuningTimeseriesRadar( ) throws SQLException {
        return getNullableGuid( RATUTS_RADAR_FIELD_ID );
    }

    public Guid getVesselPersonsOnBoardTimeseriesVessel( ) throws SQLException {
        return getNullableGuid( VPOBT_VESSEL_FIELD_ID );
    }

    public Guid getRadomeStatusTimeseriesRadome( ) throws SQLException {
        return getNullableGuid( RST_RADOME_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination ) throws SQLException {
        var kind = getObjectType( );
        switch(kind) {
            case Kind.BinaryTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
            }
            break;
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
            case Kind.ByteTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
            }
            break;
            case Kind.DateTimeTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
            }
            break;
            case Kind.DoubleTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
            }
            break;
            case Kind.GNSSAltitudeTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
                destination.writeNullableGuid( getGNSSAltitudeTimeseriesGNSSDevice( ) );
            }
            break;
            case Kind.GNSSLatitudeTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
                destination.writeNullableGuid( getGNSSLatitudeTimeseriesGNSSDevice( ) );
            }
            break;
            case Kind.GNSSLongitudeTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
                destination.writeNullableGuid( getGNSSLongitudeTimeseriesGNSSDevice( ) );
            }
            break;
            case Kind.GyroCourseTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
                destination.writeNullableGuid( getGyroCourseTimeseriesGyroDevice( ) );
            }
            break;
            case Kind.GyroHeadingMagneticNorthTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
                destination.writeNullableGuid( getGyroHeadingMagneticNorthTimeseriesGyroDevice( ) );
            }
            break;
            case Kind.GyroHeadingTrueNorthTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
                destination.writeNullableGuid( getGyroHeadingTrueNorthTimeseriesGyroDevice( ) );
            }
            break;
            case Kind.GyroPitchTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
                destination.writeNullableGuid( getGyroPitchTimeseriesGyroDevice( ) );
            }
            break;
            case Kind.GyroRateOfTurnTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
                destination.writeNullableGuid( getGyroRateOfTurnTimeseriesGyroDevice( ) );
            }
            break;
            case Kind.GyroRollTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
                destination.writeNullableGuid( getGyroRollTimeseriesGyroDevice( ) );
            }
            break;
            case Kind.GyroSpeedTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
                destination.writeNullableGuid( getGyroSpeedTimeseriesGyroDevice( ) );
            }
            break;
            case Kind.RadarLatitudeTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
                destination.writeNullableGuid( getRadarLatitudeTimeseriesRadar( ) );
            }
            break;
            case Kind.RadarLongitudeTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
                destination.writeNullableGuid( getRadarLongitudeTimeseriesRadar( ) );
            }
            break;
            case Kind.RadomeDewPointTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
                destination.writeNullableGuid( getRadomeDewPointTimeseriesRadome( ) );
            }
            break;
            case Kind.RadomePressureTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
                destination.writeNullableGuid( getRadomePressureTimeseriesRadome( ) );
            }
            break;
            case Kind.RadomeTemperatureTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
                destination.writeNullableGuid( getRadomeTemperatureTimeseriesRadome( ) );
            }
            break;
            case Kind.VesselDraughtTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
                destination.writeNullableGuid( getVesselDraughtTimeseriesVessel( ) );
            }
            break;
            case Kind.ViewLatitudeTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
                destination.writeNullableGuid( getViewLatitudeTimeseriesView( ) );
            }
            break;
            case Kind.ViewLongitudeTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
                destination.writeNullableGuid( getViewLongitudeTimeseriesView( ) );
            }
            break;
            case Kind.ViewZoomLevelTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
                destination.writeNullableGuid( getViewZoomLevelTimeseriesView( ) );
            }
            break;
            case Kind.WeatherStationAbsoluteHumidityTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
                destination.writeNullableGuid( getWeatherStationAbsoluteHumidityTimeseriesWeatherStation( ) );
            }
            break;
            case Kind.WeatherStationAirTemperatureTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
                destination.writeNullableGuid( getWeatherStationAirTemperatureTimeseriesWeatherStation( ) );
            }
            break;
            case Kind.WeatherStationBarometricPressureTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
                destination.writeNullableGuid( getWeatherStationBarometricPressureTimeseriesWeatherStation( ) );
            }
            break;
            case Kind.WeatherStationDewPointTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
                destination.writeNullableGuid( getWeatherStationDewPointTimeseriesWeatherStation( ) );
            }
            break;
            case Kind.WeatherStationRelativeHumidityTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
                destination.writeNullableGuid( getWeatherStationRelativeHumidityTimeseriesWeatherStation( ) );
            }
            break;
            case Kind.WeatherStationWaterTemperatureTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
                destination.writeNullableGuid( getWeatherStationWaterTemperatureTimeseriesWeatherStation( ) );
            }
            break;
            case Kind.WeatherStationWindDirectionTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
                destination.writeNullableGuid( getWeatherStationWindDirectionTimeseriesWeatherStation( ) );
            }
            break;
            case Kind.WeatherStationWindSpeedTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
                destination.writeNullableGuid( getWeatherStationWindSpeedTimeseriesWeatherStation( ) );
            }
            break;
            case Kind.GeoPosition2DTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
            }
            break;
            case Kind.AisAidToNavigationPositionTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
                destination.writeNullableGuid( getAisAidToNavigationPositionTimeseriesAidToNavigation( ) );
            }
            break;
            case Kind.GeoPosition3DTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
            }
            break;
            case Kind.GuidTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
            }
            break;
            case Kind.Int16Timeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
            }
            break;
            case Kind.Int32Timeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
            }
            break;
            case Kind.RadarAzimuthOffsetTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
                destination.writeNullableGuid( getRadarAzimuthOffsetTimeseriesRadar( ) );
            }
            break;
            case Kind.RadarFastTimeConstantLevelTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
                destination.writeNullableGuid( getRadarFastTimeConstantLevelTimeseriesRadar( ) );
            }
            break;
            case Kind.RadarFastTimeConstantModeTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
                destination.writeNullableGuid( getRadarFastTimeConstantModeTimeseriesRadar( ) );
            }
            break;
            case Kind.RadarPulseTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
                destination.writeNullableGuid( getRadarPulseTimeseriesRadar( ) );
            }
            break;
            case Kind.RadarSector1EndTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
                destination.writeNullableGuid( getRadarSector1EndTimeseriesRadar( ) );
            }
            break;
            case Kind.RadarSector1StartTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
                destination.writeNullableGuid( getRadarSector1StartTimeseriesRadar( ) );
            }
            break;
            case Kind.RadarSector2EndTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
                destination.writeNullableGuid( getRadarSector2EndTimeseriesRadar( ) );
            }
            break;
            case Kind.RadarSector2StartTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
                destination.writeNullableGuid( getRadarSector2StartTimeseriesRadar( ) );
            }
            break;
            case Kind.RadarSensitivityTimeControlLevelTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
                destination.writeNullableGuid( getRadarSensitivityTimeControlLevelTimeseriesRadar( ) );
            }
            break;
            case Kind.RadarTuningTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
                destination.writeNullableGuid( getRadarTuningTimeseriesRadar( ) );
            }
            break;
            case Kind.VesselPersonsOnBoardTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
                destination.writeNullableGuid( getVesselPersonsOnBoardTimeseriesVessel( ) );
            }
            break;
            case Kind.Int64Timeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
            }
            break;
            case Kind.Position2DTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
            }
            break;
            case Kind.Position3DTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
            }
            break;
            case Kind.ReferenceTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
            }
            break;
            case Kind.SByteTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
            }
            break;
            case Kind.SingleTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
            }
            break;
            case Kind.StringTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
            }
            break;
            case Kind.TimeSpanTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
            }
            break;
            case Kind.UInt16Timeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
            }
            break;
            case Kind.UInt32Timeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
            }
            break;
            case Kind.RadomeStatusTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
                destination.writeNullableGuid( getRadomeStatusTimeseriesRadome( ) );
            }
            break;
            case Kind.UInt64Timeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getMaxRetention( ) );
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

    public TimeseriesObject getDataObject( ) throws SQLException {
        var kind = getObjectType( );
        switch(kind) {
            case Kind.BinaryTimeseries: {
                return new BinaryTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ) );
            }
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
            case Kind.ByteTimeseries: {
                return new ByteTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ) );
            }
            case Kind.DateTimeTimeseries: {
                return new DateTimeTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ) );
            }
            case Kind.DoubleTimeseries: {
                return new DoubleTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ) );
            }
            case Kind.GNSSAltitudeTimeseries: {
                return new GNSSAltitudeTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getGNSSAltitudeTimeseriesGNSSDevice( ) );
            }
            case Kind.GNSSLatitudeTimeseries: {
                return new GNSSLatitudeTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getGNSSLatitudeTimeseriesGNSSDevice( ) );
            }
            case Kind.GNSSLongitudeTimeseries: {
                return new GNSSLongitudeTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getGNSSLongitudeTimeseriesGNSSDevice( ) );
            }
            case Kind.GyroCourseTimeseries: {
                return new GyroCourseTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getGyroCourseTimeseriesGyroDevice( ) );
            }
            case Kind.GyroHeadingMagneticNorthTimeseries: {
                return new GyroHeadingMagneticNorthTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getGyroHeadingMagneticNorthTimeseriesGyroDevice( ) );
            }
            case Kind.GyroHeadingTrueNorthTimeseries: {
                return new GyroHeadingTrueNorthTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getGyroHeadingTrueNorthTimeseriesGyroDevice( ) );
            }
            case Kind.GyroPitchTimeseries: {
                return new GyroPitchTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getGyroPitchTimeseriesGyroDevice( ) );
            }
            case Kind.GyroRateOfTurnTimeseries: {
                return new GyroRateOfTurnTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getGyroRateOfTurnTimeseriesGyroDevice( ) );
            }
            case Kind.GyroRollTimeseries: {
                return new GyroRollTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getGyroRollTimeseriesGyroDevice( ) );
            }
            case Kind.GyroSpeedTimeseries: {
                return new GyroSpeedTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getGyroSpeedTimeseriesGyroDevice( ) );
            }
            case Kind.RadarLatitudeTimeseries: {
                return new RadarLatitudeTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getRadarLatitudeTimeseriesRadar( ) );
            }
            case Kind.RadarLongitudeTimeseries: {
                return new RadarLongitudeTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getRadarLongitudeTimeseriesRadar( ) );
            }
            case Kind.RadomeDewPointTimeseries: {
                return new RadomeDewPointTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getRadomeDewPointTimeseriesRadome( ) );
            }
            case Kind.RadomePressureTimeseries: {
                return new RadomePressureTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getRadomePressureTimeseriesRadome( ) );
            }
            case Kind.RadomeTemperatureTimeseries: {
                return new RadomeTemperatureTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getRadomeTemperatureTimeseriesRadome( ) );
            }
            case Kind.VesselDraughtTimeseries: {
                return new VesselDraughtTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getVesselDraughtTimeseriesVessel( ) );
            }
            case Kind.ViewLatitudeTimeseries: {
                return new ViewLatitudeTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getViewLatitudeTimeseriesView( ) );
            }
            case Kind.ViewLongitudeTimeseries: {
                return new ViewLongitudeTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getViewLongitudeTimeseriesView( ) );
            }
            case Kind.ViewZoomLevelTimeseries: {
                return new ViewZoomLevelTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getViewZoomLevelTimeseriesView( ) );
            }
            case Kind.WeatherStationAbsoluteHumidityTimeseries: {
                return new WeatherStationAbsoluteHumidityTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getWeatherStationAbsoluteHumidityTimeseriesWeatherStation( ) );
            }
            case Kind.WeatherStationAirTemperatureTimeseries: {
                return new WeatherStationAirTemperatureTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getWeatherStationAirTemperatureTimeseriesWeatherStation( ) );
            }
            case Kind.WeatherStationBarometricPressureTimeseries: {
                return new WeatherStationBarometricPressureTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getWeatherStationBarometricPressureTimeseriesWeatherStation( ) );
            }
            case Kind.WeatherStationDewPointTimeseries: {
                return new WeatherStationDewPointTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getWeatherStationDewPointTimeseriesWeatherStation( ) );
            }
            case Kind.WeatherStationRelativeHumidityTimeseries: {
                return new WeatherStationRelativeHumidityTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getWeatherStationRelativeHumidityTimeseriesWeatherStation( ) );
            }
            case Kind.WeatherStationWaterTemperatureTimeseries: {
                return new WeatherStationWaterTemperatureTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getWeatherStationWaterTemperatureTimeseriesWeatherStation( ) );
            }
            case Kind.WeatherStationWindDirectionTimeseries: {
                return new WeatherStationWindDirectionTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getWeatherStationWindDirectionTimeseriesWeatherStation( ) );
            }
            case Kind.WeatherStationWindSpeedTimeseries: {
                return new WeatherStationWindSpeedTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getWeatherStationWindSpeedTimeseriesWeatherStation( ) );
            }
            case Kind.GeoPosition2DTimeseries: {
                return new GeoPosition2DTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ) );
            }
            case Kind.AisAidToNavigationPositionTimeseries: {
                return new AisAidToNavigationPositionTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getAisAidToNavigationPositionTimeseriesAidToNavigation( ) );
            }
            case Kind.GeoPosition3DTimeseries: {
                return new GeoPosition3DTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ) );
            }
            case Kind.GuidTimeseries: {
                return new GuidTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ) );
            }
            case Kind.Int16Timeseries: {
                return new Int16TimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ) );
            }
            case Kind.Int32Timeseries: {
                return new Int32TimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ) );
            }
            case Kind.RadarAzimuthOffsetTimeseries: {
                return new RadarAzimuthOffsetTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getRadarAzimuthOffsetTimeseriesRadar( ) );
            }
            case Kind.RadarFastTimeConstantLevelTimeseries: {
                return new RadarFastTimeConstantLevelTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getRadarFastTimeConstantLevelTimeseriesRadar( ) );
            }
            case Kind.RadarFastTimeConstantModeTimeseries: {
                return new RadarFastTimeConstantModeTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getRadarFastTimeConstantModeTimeseriesRadar( ) );
            }
            case Kind.RadarPulseTimeseries: {
                return new RadarPulseTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getRadarPulseTimeseriesRadar( ) );
            }
            case Kind.RadarSector1EndTimeseries: {
                return new RadarSector1EndTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getRadarSector1EndTimeseriesRadar( ) );
            }
            case Kind.RadarSector1StartTimeseries: {
                return new RadarSector1StartTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getRadarSector1StartTimeseriesRadar( ) );
            }
            case Kind.RadarSector2EndTimeseries: {
                return new RadarSector2EndTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getRadarSector2EndTimeseriesRadar( ) );
            }
            case Kind.RadarSector2StartTimeseries: {
                return new RadarSector2StartTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getRadarSector2StartTimeseriesRadar( ) );
            }
            case Kind.RadarSensitivityTimeControlLevelTimeseries: {
                return new RadarSensitivityTimeControlLevelTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getRadarSensitivityTimeControlLevelTimeseriesRadar( ) );
            }
            case Kind.RadarTuningTimeseries: {
                return new RadarTuningTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getRadarTuningTimeseriesRadar( ) );
            }
            case Kind.VesselPersonsOnBoardTimeseries: {
                return new VesselPersonsOnBoardTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getVesselPersonsOnBoardTimeseriesVessel( ) );
            }
            case Kind.Int64Timeseries: {
                return new Int64TimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ) );
            }
            case Kind.Position2DTimeseries: {
                return new Position2DTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ) );
            }
            case Kind.Position3DTimeseries: {
                return new Position3DTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ) );
            }
            case Kind.ReferenceTimeseries: {
                return new ReferenceTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ) );
            }
            case Kind.SByteTimeseries: {
                return new SByteTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ) );
            }
            case Kind.SingleTimeseries: {
                return new SingleTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ) );
            }
            case Kind.StringTimeseries: {
                return new StringTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ) );
            }
            case Kind.TimeSpanTimeseries: {
                return new TimeSpanTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ) );
            }
            case Kind.UInt16Timeseries: {
                return new UInt16TimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ) );
            }
            case Kind.UInt32Timeseries: {
                return new UInt32TimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ) );
            }
            case Kind.RadomeStatusTimeseries: {
                return new RadomeStatusTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getRadomeStatusTimeseriesRadome( ) );
            }
            case Kind.UInt64Timeseries: {
                return new UInt64TimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ) );
            }
            default: {
                var exc = new SQLException( "Cannot create an object for kind=" + kind + "." );
                throw exc;
            }
        }
    }

}

