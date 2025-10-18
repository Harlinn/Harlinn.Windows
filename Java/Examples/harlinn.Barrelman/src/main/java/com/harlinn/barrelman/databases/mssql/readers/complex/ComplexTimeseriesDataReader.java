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

}

