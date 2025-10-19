package com.harlinn.barrelman.databases.mssql.readers.complex;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class ComplexTimeseriesCatalogElementDataReader extends ResultSetWrapper {

    public final static String BaseQuery = "SELECT \r\n" +
            "  tce.[Id], \r\n" +
            "  tce.[EntityType], \r\n" +
            "  tce.[RowVersion], \r\n" +
            "  tce.[Catalog], \r\n" +
            "  tce.[Name], \r\n" +
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
            "FROM [TimeseriesCatalogElementView] tce \r\n" +
            "  LEFT JOIN [Timeseries] t ON(tce.[Id] = t.[Id] ) \r\n" +
            "  LEFT JOIN [BinaryTimeseries] bt ON(tce.[Id] = bt.[Id] ) \r\n" +
            "  LEFT JOIN [BooleanTimeseries] bots ON(tce.[Id] = bots.[Id] ) \r\n" +
            "  LEFT JOIN [AisAidToNavigationOffPositionTimeseries] aatnopt ON(tce.[Id] = aatnopt.[Id] ) \r\n" +
            "  LEFT JOIN [DeviceEnabledTimeseries] det ON(tce.[Id] = det.[Id] ) \r\n" +
            "  LEFT JOIN [MediaProxySessionEnabledTimeseries] mpset ON(tce.[Id] = mpset.[Id] ) \r\n" +
            "  LEFT JOIN [MediaServiceEnabledTimeseries] mset ON(tce.[Id] = mset.[Id] ) \r\n" +
            "  LEFT JOIN [RadarAutomaticSensitivityTimeControlTimeseries] rastct ON(tce.[Id] = rastct.[Id] ) \r\n" +
            "  LEFT JOIN [RadarBlankSector1Timeseries] rbs1t ON(tce.[Id] = rbs1t.[Id] ) \r\n" +
            "  LEFT JOIN [RadarBlankSector2Timeseries] rbs2t ON(tce.[Id] = rbs2t.[Id] ) \r\n" +
            "  LEFT JOIN [RadarEnableAutomaticFrequencyControlTimeseries] reafct ON(tce.[Id] = reafct.[Id] ) \r\n" +
            "  LEFT JOIN [RadarEnableFastTimeConstantTimeseries] reftct ON(tce.[Id] = reftct.[Id] ) \r\n" +
            "  LEFT JOIN [RadarEnableSensitivityTimeControlTimeseries] restct ON(tce.[Id] = restct.[Id] ) \r\n" +
            "  LEFT JOIN [RadarPowerOnTimeseries] rpot ON(tce.[Id] = rpot.[Id] ) \r\n" +
            "  LEFT JOIN [RadarSaveSettingsTimeseries] rsst ON(tce.[Id] = rsst.[Id] ) \r\n" +
            "  LEFT JOIN [RadarTrackingTimeseries] rtt ON(tce.[Id] = rtt.[Id] ) \r\n" +
            "  LEFT JOIN [ByteTimeseries] byts ON(tce.[Id] = byts.[Id] ) \r\n" +
            "  LEFT JOIN [DateTimeTimeseries] dtt ON(tce.[Id] = dtt.[Id] ) \r\n" +
            "  LEFT JOIN [DoubleTimeseries] dt ON(tce.[Id] = dt.[Id] ) \r\n" +
            "  LEFT JOIN [GNSSAltitudeTimeseries] gats ON(tce.[Id] = gats.[Id] ) \r\n" +
            "  LEFT JOIN [GNSSLatitudeTimeseries] glats ON(tce.[Id] = glats.[Id] ) \r\n" +
            "  LEFT JOIN [GNSSLongitudeTimeseries] glots ON(tce.[Id] = glots.[Id] ) \r\n" +
            "  LEFT JOIN [GyroCourseTimeseries] gct ON(tce.[Id] = gct.[Id] ) \r\n" +
            "  LEFT JOIN [GyroHeadingMagneticNorthTimeseries] ghmnt ON(tce.[Id] = ghmnt.[Id] ) \r\n" +
            "  LEFT JOIN [GyroHeadingTrueNorthTimeseries] ghtnt ON(tce.[Id] = ghtnt.[Id] ) \r\n" +
            "  LEFT JOIN [GyroPitchTimeseries] gpt ON(tce.[Id] = gpt.[Id] ) \r\n" +
            "  LEFT JOIN [GyroRateOfTurnTimeseries] grott ON(tce.[Id] = grott.[Id] ) \r\n" +
            "  LEFT JOIN [GyroRollTimeseries] grt ON(tce.[Id] = grt.[Id] ) \r\n" +
            "  LEFT JOIN [GyroSpeedTimeseries] gst ON(tce.[Id] = gst.[Id] ) \r\n" +
            "  LEFT JOIN [RadarLatitudeTimeseries] rlats ON(tce.[Id] = rlats.[Id] ) \r\n" +
            "  LEFT JOIN [RadarLongitudeTimeseries] rlots ON(tce.[Id] = rlots.[Id] ) \r\n" +
            "  LEFT JOIN [RadomeDewPointTimeseries] rdpt ON(tce.[Id] = rdpt.[Id] ) \r\n" +
            "  LEFT JOIN [RadomePressureTimeseries] rpt ON(tce.[Id] = rpt.[Id] ) \r\n" +
            "  LEFT JOIN [RadomeTemperatureTimeseries] rtets ON(tce.[Id] = rtets.[Id] ) \r\n" +
            "  LEFT JOIN [VesselDraughtTimeseries] vdt ON(tce.[Id] = vdt.[Id] ) \r\n" +
            "  LEFT JOIN [ViewLatitudeTimeseries] vlats ON(tce.[Id] = vlats.[Id] ) \r\n" +
            "  LEFT JOIN [ViewLongitudeTimeseries] vlots ON(tce.[Id] = vlots.[Id] ) \r\n" +
            "  LEFT JOIN [ViewZoomLevelTimeseries] vzlt ON(tce.[Id] = vzlt.[Id] ) \r\n" +
            "  LEFT JOIN [WeatherStationAbsoluteHumidityTimeseries] wsaht ON(tce.[Id] = wsaht.[Id] ) \r\n" +
            "  LEFT JOIN [WeatherStationAirTemperatureTimeseries] wsatt ON(tce.[Id] = wsatt.[Id] ) \r\n" +
            "  LEFT JOIN [WeatherStationBarometricPressureTimeseries] wsbpt ON(tce.[Id] = wsbpt.[Id] ) \r\n" +
            "  LEFT JOIN [WeatherStationDewPointTimeseries] wsdpt ON(tce.[Id] = wsdpt.[Id] ) \r\n" +
            "  LEFT JOIN [WeatherStationRelativeHumidityTimeseries] wsrht ON(tce.[Id] = wsrht.[Id] ) \r\n" +
            "  LEFT JOIN [WeatherStationWaterTemperatureTimeseries] wswtt ON(tce.[Id] = wswtt.[Id] ) \r\n" +
            "  LEFT JOIN [WeatherStationWindDirectionTimeseries] wswdt ON(tce.[Id] = wswdt.[Id] ) \r\n" +
            "  LEFT JOIN [WeatherStationWindSpeedTimeseries] wswst ON(tce.[Id] = wswst.[Id] ) \r\n" +
            "  LEFT JOIN [GeoPosition2DTimeseries] gp2d ON(tce.[Id] = gp2d.[Id] ) \r\n" +
            "  LEFT JOIN [AisAidToNavigationPositionTimeseries] aatnpt ON(tce.[Id] = aatnpt.[Id] ) \r\n" +
            "  LEFT JOIN [GeoPosition3DTimeseries] gp3d ON(tce.[Id] = gp3d.[Id] ) \r\n" +
            "  LEFT JOIN [GuidTimeseries] gt ON(tce.[Id] = gt.[Id] ) \r\n" +
            "  LEFT JOIN [Int16Timeseries] i16t ON(tce.[Id] = i16t.[Id] ) \r\n" +
            "  LEFT JOIN [Int32Timeseries] i32t ON(tce.[Id] = i32t.[Id] ) \r\n" +
            "  LEFT JOIN [RadarAzimuthOffsetTimeseries] raot ON(tce.[Id] = raot.[Id] ) \r\n" +
            "  LEFT JOIN [RadarFastTimeConstantLevelTimeseries] rftclt ON(tce.[Id] = rftclt.[Id] ) \r\n" +
            "  LEFT JOIN [RadarFastTimeConstantModeTimeseries] rftcmt ON(tce.[Id] = rftcmt.[Id] ) \r\n" +
            "  LEFT JOIN [RadarPulseTimeseries] rapts ON(tce.[Id] = rapts.[Id] ) \r\n" +
            "  LEFT JOIN [RadarSector1EndTimeseries] rs1et ON(tce.[Id] = rs1et.[Id] ) \r\n" +
            "  LEFT JOIN [RadarSector1StartTimeseries] rs1st ON(tce.[Id] = rs1st.[Id] ) \r\n" +
            "  LEFT JOIN [RadarSector2EndTimeseries] rs2et ON(tce.[Id] = rs2et.[Id] ) \r\n" +
            "  LEFT JOIN [RadarSector2StartTimeseries] rs2st ON(tce.[Id] = rs2st.[Id] ) \r\n" +
            "  LEFT JOIN [RadarSensitivityTimeControlLevelTimeseries] rstclt ON(tce.[Id] = rstclt.[Id] ) \r\n" +
            "  LEFT JOIN [RadarTuningTimeseries] ratuts ON(tce.[Id] = ratuts.[Id] ) \r\n" +
            "  LEFT JOIN [VesselPersonsOnBoardTimeseries] vpobt ON(tce.[Id] = vpobt.[Id] ) \r\n" +
            "  LEFT JOIN [Int64Timeseries] i64t ON(tce.[Id] = i64t.[Id] ) \r\n" +
            "  LEFT JOIN [Position2DTimeseries] p2d ON(tce.[Id] = p2d.[Id] ) \r\n" +
            "  LEFT JOIN [Position3DTimeseries] p3d ON(tce.[Id] = p3d.[Id] ) \r\n" +
            "  LEFT JOIN [ReferenceTimeseries] rt ON(tce.[Id] = rt.[Id] ) \r\n" +
            "  LEFT JOIN [SByteTimeseries] st ON(tce.[Id] = st.[Id] ) \r\n" +
            "  LEFT JOIN [SingleTimeseries] sits ON(tce.[Id] = sits.[Id] ) \r\n" +
            "  LEFT JOIN [StringTimeseries] stts ON(tce.[Id] = stts.[Id] ) \r\n" +
            "  LEFT JOIN [TimeSpanTimeseries] tst ON(tce.[Id] = tst.[Id] ) \r\n" +
            "  LEFT JOIN [UInt16Timeseries] u16t ON(tce.[Id] = u16t.[Id] ) \r\n" +
            "  LEFT JOIN [UInt32Timeseries] u32t ON(tce.[Id] = u32t.[Id] ) \r\n" +
            "  LEFT JOIN [RadomeStatusTimeseries] rst ON(tce.[Id] = rst.[Id] ) \r\n" +
            "  LEFT JOIN [UInt64Timeseries] u64t ON(tce.[Id] = u64t.[Id] ) \r\n" +
            "  LEFT JOIN [TimeseriesCatalog] tc ON(tce.[Id] = tc.[Id] ) \r\n";

    public final static String BaseViewName = "TimeseriesCatalogElementView";
    public final static String ViewAliasName = "tce";

    public final static int TCE_ID_FIELD_ID = 1;
    public final static int TCE_KIND_FIELD_ID = 2;
    public final static int TCE_ROWVERSION_FIELD_ID = 3;
    public final static int TCE_CATALOG_FIELD_ID = 4;
    public final static int TCE_NAME_FIELD_ID = 5;
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

    public ComplexTimeseriesCatalogElementDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public Guid getId( ) throws SQLException {
        return getGuid( TCE_ID_FIELD_ID );
    }

    public int getObjectType() throws SQLException {
        return getInt32( TCE_KIND_FIELD_ID );
    }

    public long getRowVersion( ) throws SQLException {
        return getInt64( TCE_ROWVERSION_FIELD_ID );
    }

    public Guid getCatalog( ) throws SQLException {
        return getNullableGuid( TCE_CATALOG_FIELD_ID );
    }

    public String getName( ) throws SQLException {
        return getString( TCE_NAME_FIELD_ID );
    }

    public TimeSpan getTimeseriesMaxRetention( ) throws SQLException {
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
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
            }
            break;
            case Kind.BooleanTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
            }
            break;
            case Kind.AisAidToNavigationOffPositionTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
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
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
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
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
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
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
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
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
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
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
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
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
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
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
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
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
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
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
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
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
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
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
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
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
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
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
            }
            break;
            case Kind.DateTimeTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
            }
            break;
            case Kind.DoubleTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
            }
            break;
            case Kind.GNSSAltitudeTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
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
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
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
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
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
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
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
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
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
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
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
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
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
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
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
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
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
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
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
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
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
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
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
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
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
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
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
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
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
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
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
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
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
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
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
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
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
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
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
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
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
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
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
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
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
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
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
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
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
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
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
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
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
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
            }
            break;
            case Kind.AisAidToNavigationPositionTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
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
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
            }
            break;
            case Kind.GuidTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
            }
            break;
            case Kind.Int16Timeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
            }
            break;
            case Kind.Int32Timeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
            }
            break;
            case Kind.RadarAzimuthOffsetTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
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
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
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
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
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
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
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
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
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
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
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
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
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
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
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
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
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
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
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
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
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
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
            }
            break;
            case Kind.Position2DTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
            }
            break;
            case Kind.Position3DTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
            }
            break;
            case Kind.ReferenceTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
            }
            break;
            case Kind.SByteTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
            }
            break;
            case Kind.SingleTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
            }
            break;
            case Kind.StringTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
            }
            break;
            case Kind.TimeSpanTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
            }
            break;
            case Kind.UInt16Timeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
            }
            break;
            case Kind.UInt32Timeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
            }
            break;
            case Kind.RadomeStatusTimeseries: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
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
                destination.writeTimeSpan( getTimeseriesMaxRetention( ) );
            }
            break;
            case Kind.TimeseriesCatalog: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
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

    public TimeseriesCatalogElementObject getDataObject( ) throws SQLException {
        var kind = getObjectType( );
        switch(kind) {
            case Kind.BinaryTimeseries: {
                return new BinaryTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ) );
            }
            case Kind.BooleanTimeseries: {
                return new BooleanTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ) );
            }
            case Kind.AisAidToNavigationOffPositionTimeseries: {
                return new AisAidToNavigationOffPositionTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ), getAisAidToNavigationOffPositionTimeseriesAidToNavigation( ) );
            }
            case Kind.DeviceEnabledTimeseries: {
                return new DeviceEnabledTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ), getDeviceEnabledTimeseriesDevice( ) );
            }
            case Kind.MediaProxySessionEnabledTimeseries: {
                return new MediaProxySessionEnabledTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ), getMediaProxySessionEnabledTimeseriesProxySession( ) );
            }
            case Kind.MediaServiceEnabledTimeseries: {
                return new MediaServiceEnabledTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ), getMediaServiceEnabledTimeseriesService( ) );
            }
            case Kind.RadarAutomaticSensitivityTimeControlTimeseries: {
                return new RadarAutomaticSensitivityTimeControlTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ), getRadarAutomaticSensitivityTimeControlTimeseriesRadar( ) );
            }
            case Kind.RadarBlankSector1Timeseries: {
                return new RadarBlankSector1TimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ), getRadarBlankSector1TimeseriesRadar( ) );
            }
            case Kind.RadarBlankSector2Timeseries: {
                return new RadarBlankSector2TimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ), getRadarBlankSector2TimeseriesRadar( ) );
            }
            case Kind.RadarEnableAutomaticFrequencyControlTimeseries: {
                return new RadarEnableAutomaticFrequencyControlTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ), getRadarEnableAutomaticFrequencyControlTimeseriesRadar( ) );
            }
            case Kind.RadarEnableFastTimeConstantTimeseries: {
                return new RadarEnableFastTimeConstantTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ), getRadarEnableFastTimeConstantTimeseriesRadar( ) );
            }
            case Kind.RadarEnableSensitivityTimeControlTimeseries: {
                return new RadarEnableSensitivityTimeControlTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ), getRadarEnableSensitivityTimeControlTimeseriesRadar( ) );
            }
            case Kind.RadarPowerOnTimeseries: {
                return new RadarPowerOnTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ), getRadarPowerOnTimeseriesRadar( ) );
            }
            case Kind.RadarSaveSettingsTimeseries: {
                return new RadarSaveSettingsTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ), getRadarSaveSettingsTimeseriesRadar( ) );
            }
            case Kind.RadarTrackingTimeseries: {
                return new RadarTrackingTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ), getRadarTrackingTimeseriesRadar( ) );
            }
            case Kind.ByteTimeseries: {
                return new ByteTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ) );
            }
            case Kind.DateTimeTimeseries: {
                return new DateTimeTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ) );
            }
            case Kind.DoubleTimeseries: {
                return new DoubleTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ) );
            }
            case Kind.GNSSAltitudeTimeseries: {
                return new GNSSAltitudeTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ), getGNSSAltitudeTimeseriesGNSSDevice( ) );
            }
            case Kind.GNSSLatitudeTimeseries: {
                return new GNSSLatitudeTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ), getGNSSLatitudeTimeseriesGNSSDevice( ) );
            }
            case Kind.GNSSLongitudeTimeseries: {
                return new GNSSLongitudeTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ), getGNSSLongitudeTimeseriesGNSSDevice( ) );
            }
            case Kind.GyroCourseTimeseries: {
                return new GyroCourseTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ), getGyroCourseTimeseriesGyroDevice( ) );
            }
            case Kind.GyroHeadingMagneticNorthTimeseries: {
                return new GyroHeadingMagneticNorthTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ), getGyroHeadingMagneticNorthTimeseriesGyroDevice( ) );
            }
            case Kind.GyroHeadingTrueNorthTimeseries: {
                return new GyroHeadingTrueNorthTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ), getGyroHeadingTrueNorthTimeseriesGyroDevice( ) );
            }
            case Kind.GyroPitchTimeseries: {
                return new GyroPitchTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ), getGyroPitchTimeseriesGyroDevice( ) );
            }
            case Kind.GyroRateOfTurnTimeseries: {
                return new GyroRateOfTurnTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ), getGyroRateOfTurnTimeseriesGyroDevice( ) );
            }
            case Kind.GyroRollTimeseries: {
                return new GyroRollTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ), getGyroRollTimeseriesGyroDevice( ) );
            }
            case Kind.GyroSpeedTimeseries: {
                return new GyroSpeedTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ), getGyroSpeedTimeseriesGyroDevice( ) );
            }
            case Kind.RadarLatitudeTimeseries: {
                return new RadarLatitudeTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ), getRadarLatitudeTimeseriesRadar( ) );
            }
            case Kind.RadarLongitudeTimeseries: {
                return new RadarLongitudeTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ), getRadarLongitudeTimeseriesRadar( ) );
            }
            case Kind.RadomeDewPointTimeseries: {
                return new RadomeDewPointTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ), getRadomeDewPointTimeseriesRadome( ) );
            }
            case Kind.RadomePressureTimeseries: {
                return new RadomePressureTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ), getRadomePressureTimeseriesRadome( ) );
            }
            case Kind.RadomeTemperatureTimeseries: {
                return new RadomeTemperatureTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ), getRadomeTemperatureTimeseriesRadome( ) );
            }
            case Kind.VesselDraughtTimeseries: {
                return new VesselDraughtTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ), getVesselDraughtTimeseriesVessel( ) );
            }
            case Kind.ViewLatitudeTimeseries: {
                return new ViewLatitudeTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ), getViewLatitudeTimeseriesView( ) );
            }
            case Kind.ViewLongitudeTimeseries: {
                return new ViewLongitudeTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ), getViewLongitudeTimeseriesView( ) );
            }
            case Kind.ViewZoomLevelTimeseries: {
                return new ViewZoomLevelTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ), getViewZoomLevelTimeseriesView( ) );
            }
            case Kind.WeatherStationAbsoluteHumidityTimeseries: {
                return new WeatherStationAbsoluteHumidityTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ), getWeatherStationAbsoluteHumidityTimeseriesWeatherStation( ) );
            }
            case Kind.WeatherStationAirTemperatureTimeseries: {
                return new WeatherStationAirTemperatureTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ), getWeatherStationAirTemperatureTimeseriesWeatherStation( ) );
            }
            case Kind.WeatherStationBarometricPressureTimeseries: {
                return new WeatherStationBarometricPressureTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ), getWeatherStationBarometricPressureTimeseriesWeatherStation( ) );
            }
            case Kind.WeatherStationDewPointTimeseries: {
                return new WeatherStationDewPointTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ), getWeatherStationDewPointTimeseriesWeatherStation( ) );
            }
            case Kind.WeatherStationRelativeHumidityTimeseries: {
                return new WeatherStationRelativeHumidityTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ), getWeatherStationRelativeHumidityTimeseriesWeatherStation( ) );
            }
            case Kind.WeatherStationWaterTemperatureTimeseries: {
                return new WeatherStationWaterTemperatureTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ), getWeatherStationWaterTemperatureTimeseriesWeatherStation( ) );
            }
            case Kind.WeatherStationWindDirectionTimeseries: {
                return new WeatherStationWindDirectionTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ), getWeatherStationWindDirectionTimeseriesWeatherStation( ) );
            }
            case Kind.WeatherStationWindSpeedTimeseries: {
                return new WeatherStationWindSpeedTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ), getWeatherStationWindSpeedTimeseriesWeatherStation( ) );
            }
            case Kind.GeoPosition2DTimeseries: {
                return new GeoPosition2DTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ) );
            }
            case Kind.AisAidToNavigationPositionTimeseries: {
                return new AisAidToNavigationPositionTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ), getAisAidToNavigationPositionTimeseriesAidToNavigation( ) );
            }
            case Kind.GeoPosition3DTimeseries: {
                return new GeoPosition3DTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ) );
            }
            case Kind.GuidTimeseries: {
                return new GuidTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ) );
            }
            case Kind.Int16Timeseries: {
                return new Int16TimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ) );
            }
            case Kind.Int32Timeseries: {
                return new Int32TimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ) );
            }
            case Kind.RadarAzimuthOffsetTimeseries: {
                return new RadarAzimuthOffsetTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ), getRadarAzimuthOffsetTimeseriesRadar( ) );
            }
            case Kind.RadarFastTimeConstantLevelTimeseries: {
                return new RadarFastTimeConstantLevelTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ), getRadarFastTimeConstantLevelTimeseriesRadar( ) );
            }
            case Kind.RadarFastTimeConstantModeTimeseries: {
                return new RadarFastTimeConstantModeTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ), getRadarFastTimeConstantModeTimeseriesRadar( ) );
            }
            case Kind.RadarPulseTimeseries: {
                return new RadarPulseTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ), getRadarPulseTimeseriesRadar( ) );
            }
            case Kind.RadarSector1EndTimeseries: {
                return new RadarSector1EndTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ), getRadarSector1EndTimeseriesRadar( ) );
            }
            case Kind.RadarSector1StartTimeseries: {
                return new RadarSector1StartTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ), getRadarSector1StartTimeseriesRadar( ) );
            }
            case Kind.RadarSector2EndTimeseries: {
                return new RadarSector2EndTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ), getRadarSector2EndTimeseriesRadar( ) );
            }
            case Kind.RadarSector2StartTimeseries: {
                return new RadarSector2StartTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ), getRadarSector2StartTimeseriesRadar( ) );
            }
            case Kind.RadarSensitivityTimeControlLevelTimeseries: {
                return new RadarSensitivityTimeControlLevelTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ), getRadarSensitivityTimeControlLevelTimeseriesRadar( ) );
            }
            case Kind.RadarTuningTimeseries: {
                return new RadarTuningTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ), getRadarTuningTimeseriesRadar( ) );
            }
            case Kind.VesselPersonsOnBoardTimeseries: {
                return new VesselPersonsOnBoardTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ), getVesselPersonsOnBoardTimeseriesVessel( ) );
            }
            case Kind.Int64Timeseries: {
                return new Int64TimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ) );
            }
            case Kind.Position2DTimeseries: {
                return new Position2DTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ) );
            }
            case Kind.Position3DTimeseries: {
                return new Position3DTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ) );
            }
            case Kind.ReferenceTimeseries: {
                return new ReferenceTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ) );
            }
            case Kind.SByteTimeseries: {
                return new SByteTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ) );
            }
            case Kind.SingleTimeseries: {
                return new SingleTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ) );
            }
            case Kind.StringTimeseries: {
                return new StringTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ) );
            }
            case Kind.TimeSpanTimeseries: {
                return new TimeSpanTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ) );
            }
            case Kind.UInt16Timeseries: {
                return new UInt16TimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ) );
            }
            case Kind.UInt32Timeseries: {
                return new UInt32TimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ) );
            }
            case Kind.RadomeStatusTimeseries: {
                return new RadomeStatusTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ), getRadomeStatusTimeseriesRadome( ) );
            }
            case Kind.UInt64Timeseries: {
                return new UInt64TimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getTimeseriesMaxRetention( ) );
            }
            case Kind.TimeseriesCatalog: {
                return new TimeseriesCatalogObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ) );
            }
            default: {
                var exc = new SQLException( "Cannot create an object for kind=" + kind + "." );
                throw exc;
            }
        }
    }

}

