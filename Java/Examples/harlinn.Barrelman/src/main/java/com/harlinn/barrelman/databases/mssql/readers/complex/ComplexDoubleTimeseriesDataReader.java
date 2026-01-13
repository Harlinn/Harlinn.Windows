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

public class ComplexDoubleTimeseriesDataReader extends ResultSetWrapper {

    public final static String BaseQuery = "SELECT \r\n" +
            "  dt.[Id], \r\n" +
            "  dt.[EntityType], \r\n" +
            "  dt.[RowVersion], \r\n" +
            "  dt.[Catalog], \r\n" +
            "  dt.[Name], \r\n" +
            "  dt.[MaxRetention], \r\n" +
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
            "  wswst.[WeatherStation] \r\n" +
            "FROM [DoubleTimeseriesView] dt \r\n" +
            "  LEFT JOIN [GNSSAltitudeTimeseries] gats ON(dt.[Id] = gats.[Id] ) \r\n" +
            "  LEFT JOIN [GNSSLatitudeTimeseries] glats ON(dt.[Id] = glats.[Id] ) \r\n" +
            "  LEFT JOIN [GNSSLongitudeTimeseries] glots ON(dt.[Id] = glots.[Id] ) \r\n" +
            "  LEFT JOIN [GyroCourseTimeseries] gct ON(dt.[Id] = gct.[Id] ) \r\n" +
            "  LEFT JOIN [GyroHeadingMagneticNorthTimeseries] ghmnt ON(dt.[Id] = ghmnt.[Id] ) \r\n" +
            "  LEFT JOIN [GyroHeadingTrueNorthTimeseries] ghtnt ON(dt.[Id] = ghtnt.[Id] ) \r\n" +
            "  LEFT JOIN [GyroPitchTimeseries] gpt ON(dt.[Id] = gpt.[Id] ) \r\n" +
            "  LEFT JOIN [GyroRateOfTurnTimeseries] grott ON(dt.[Id] = grott.[Id] ) \r\n" +
            "  LEFT JOIN [GyroRollTimeseries] grt ON(dt.[Id] = grt.[Id] ) \r\n" +
            "  LEFT JOIN [GyroSpeedTimeseries] gst ON(dt.[Id] = gst.[Id] ) \r\n" +
            "  LEFT JOIN [RadarLatitudeTimeseries] rlats ON(dt.[Id] = rlats.[Id] ) \r\n" +
            "  LEFT JOIN [RadarLongitudeTimeseries] rlots ON(dt.[Id] = rlots.[Id] ) \r\n" +
            "  LEFT JOIN [RadomeDewPointTimeseries] rdpt ON(dt.[Id] = rdpt.[Id] ) \r\n" +
            "  LEFT JOIN [RadomePressureTimeseries] rpt ON(dt.[Id] = rpt.[Id] ) \r\n" +
            "  LEFT JOIN [RadomeTemperatureTimeseries] rtets ON(dt.[Id] = rtets.[Id] ) \r\n" +
            "  LEFT JOIN [VesselDraughtTimeseries] vdt ON(dt.[Id] = vdt.[Id] ) \r\n" +
            "  LEFT JOIN [ViewLatitudeTimeseries] vlats ON(dt.[Id] = vlats.[Id] ) \r\n" +
            "  LEFT JOIN [ViewLongitudeTimeseries] vlots ON(dt.[Id] = vlots.[Id] ) \r\n" +
            "  LEFT JOIN [ViewZoomLevelTimeseries] vzlt ON(dt.[Id] = vzlt.[Id] ) \r\n" +
            "  LEFT JOIN [WeatherStationAbsoluteHumidityTimeseries] wsaht ON(dt.[Id] = wsaht.[Id] ) \r\n" +
            "  LEFT JOIN [WeatherStationAirTemperatureTimeseries] wsatt ON(dt.[Id] = wsatt.[Id] ) \r\n" +
            "  LEFT JOIN [WeatherStationBarometricPressureTimeseries] wsbpt ON(dt.[Id] = wsbpt.[Id] ) \r\n" +
            "  LEFT JOIN [WeatherStationDewPointTimeseries] wsdpt ON(dt.[Id] = wsdpt.[Id] ) \r\n" +
            "  LEFT JOIN [WeatherStationRelativeHumidityTimeseries] wsrht ON(dt.[Id] = wsrht.[Id] ) \r\n" +
            "  LEFT JOIN [WeatherStationWaterTemperatureTimeseries] wswtt ON(dt.[Id] = wswtt.[Id] ) \r\n" +
            "  LEFT JOIN [WeatherStationWindDirectionTimeseries] wswdt ON(dt.[Id] = wswdt.[Id] ) \r\n" +
            "  LEFT JOIN [WeatherStationWindSpeedTimeseries] wswst ON(dt.[Id] = wswst.[Id] ) \r\n";

    public final static String BaseViewName = "DoubleTimeseriesView";
    public final static String ViewAliasName = "dt";

    public final static int DT_ID_FIELD_ID = 1;
    public final static int DT_KIND_FIELD_ID = 2;
    public final static int DT_ROWVERSION_FIELD_ID = 3;
    public final static int DT_CATALOG_FIELD_ID = 4;
    public final static int DT_NAME_FIELD_ID = 5;
    public final static int DT_MAXRETENTION_FIELD_ID = 6;
    public final static int GATS_GNSSDEVICE_FIELD_ID = 7;
    public final static int GLATS_GNSSDEVICE_FIELD_ID = 8;
    public final static int GLOTS_GNSSDEVICE_FIELD_ID = 9;
    public final static int GCT_GYRODEVICE_FIELD_ID = 10;
    public final static int GHMNT_GYRODEVICE_FIELD_ID = 11;
    public final static int GHTNT_GYRODEVICE_FIELD_ID = 12;
    public final static int GPT_GYRODEVICE_FIELD_ID = 13;
    public final static int GROTT_GYRODEVICE_FIELD_ID = 14;
    public final static int GRT_GYRODEVICE_FIELD_ID = 15;
    public final static int GST_GYRODEVICE_FIELD_ID = 16;
    public final static int RLATS_RADAR_FIELD_ID = 17;
    public final static int RLOTS_RADAR_FIELD_ID = 18;
    public final static int RDPT_RADOME_FIELD_ID = 19;
    public final static int RPT_RADOME_FIELD_ID = 20;
    public final static int RTETS_RADOME_FIELD_ID = 21;
    public final static int VDT_VESSEL_FIELD_ID = 22;
    public final static int VLATS_VIEW_FIELD_ID = 23;
    public final static int VLOTS_VIEW_FIELD_ID = 24;
    public final static int VZLT_VIEW_FIELD_ID = 25;
    public final static int WSAHT_WEATHERSTATION_FIELD_ID = 26;
    public final static int WSATT_WEATHERSTATION_FIELD_ID = 27;
    public final static int WSBPT_WEATHERSTATION_FIELD_ID = 28;
    public final static int WSDPT_WEATHERSTATION_FIELD_ID = 29;
    public final static int WSRHT_WEATHERSTATION_FIELD_ID = 30;
    public final static int WSWTT_WEATHERSTATION_FIELD_ID = 31;
    public final static int WSWDT_WEATHERSTATION_FIELD_ID = 32;
    public final static int WSWST_WEATHERSTATION_FIELD_ID = 33;

    public ComplexDoubleTimeseriesDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public Guid getId( ) throws SQLException {
        return getGuid( DT_ID_FIELD_ID );
    }

    public int getObjectType() throws SQLException {
        return getInt32( DT_KIND_FIELD_ID );
    }

    public long getRowVersion( ) throws SQLException {
        return getInt64( DT_ROWVERSION_FIELD_ID );
    }

    public Guid getCatalog( ) throws SQLException {
        return getNullableGuid( DT_CATALOG_FIELD_ID );
    }

    public String getName( ) throws SQLException {
        return getString( DT_NAME_FIELD_ID );
    }

    public TimeSpan getMaxRetention( ) throws SQLException {
        return getTimeSpan( DT_MAXRETENTION_FIELD_ID );
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

    public void writeTo(BinaryWriter destination ) throws SQLException {
        var kind = getObjectType( );
        switch(kind) {
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

    public DoubleTimeseriesObject getDataObject( ) throws SQLException {
        var kind = getObjectType( );
        switch(kind) {
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
            default: {
                var exc = new SQLException( "Cannot create an object for kind=" + kind + "." );
                throw exc;
            }
        }
    }

}

