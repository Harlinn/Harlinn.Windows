package com.harlinn.barrelman.databases.mssql.readers.complex;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class ComplexInt32TimeseriesDataReader extends ResultSetWrapper {

    public final static String BaseQuery = "SELECT \r\n" +
            "  i32t.[Id], \r\n" +
            "  i32t.[EntityType], \r\n" +
            "  i32t.[RowVersion], \r\n" +
            "  i32t.[Catalog], \r\n" +
            "  i32t.[Name], \r\n" +
            "  i32t.[MaxRetention], \r\n" +
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
            "  vpobt.[Vessel] \r\n" +
            "FROM [Int32TimeseriesView] i32t \r\n" +
            "  LEFT JOIN [RadarAzimuthOffsetTimeseries] raot ON(i32t.[Id] = raot.[Id] ) \r\n" +
            "  LEFT JOIN [RadarFastTimeConstantLevelTimeseries] rftclt ON(i32t.[Id] = rftclt.[Id] ) \r\n" +
            "  LEFT JOIN [RadarFastTimeConstantModeTimeseries] rftcmt ON(i32t.[Id] = rftcmt.[Id] ) \r\n" +
            "  LEFT JOIN [RadarPulseTimeseries] rapts ON(i32t.[Id] = rapts.[Id] ) \r\n" +
            "  LEFT JOIN [RadarSector1EndTimeseries] rs1et ON(i32t.[Id] = rs1et.[Id] ) \r\n" +
            "  LEFT JOIN [RadarSector1StartTimeseries] rs1st ON(i32t.[Id] = rs1st.[Id] ) \r\n" +
            "  LEFT JOIN [RadarSector2EndTimeseries] rs2et ON(i32t.[Id] = rs2et.[Id] ) \r\n" +
            "  LEFT JOIN [RadarSector2StartTimeseries] rs2st ON(i32t.[Id] = rs2st.[Id] ) \r\n" +
            "  LEFT JOIN [RadarSensitivityTimeControlLevelTimeseries] rstclt ON(i32t.[Id] = rstclt.[Id] ) \r\n" +
            "  LEFT JOIN [RadarTuningTimeseries] ratuts ON(i32t.[Id] = ratuts.[Id] ) \r\n" +
            "  LEFT JOIN [VesselPersonsOnBoardTimeseries] vpobt ON(i32t.[Id] = vpobt.[Id] ) \r\n";

    public final static String BaseViewName = "Int32TimeseriesView";
    public final static String ViewAliasName = "i32t";

    public final static int I32T_ID_FIELD_ID = 1;
    public final static int I32T_KIND_FIELD_ID = 2;
    public final static int I32T_ROWVERSION_FIELD_ID = 3;
    public final static int I32T_CATALOG_FIELD_ID = 4;
    public final static int I32T_NAME_FIELD_ID = 5;
    public final static int I32T_MAXRETENTION_FIELD_ID = 6;
    public final static int RAOT_RADAR_FIELD_ID = 7;
    public final static int RFTCLT_RADAR_FIELD_ID = 8;
    public final static int RFTCMT_RADAR_FIELD_ID = 9;
    public final static int RAPTS_RADAR_FIELD_ID = 10;
    public final static int RS1ET_RADAR_FIELD_ID = 11;
    public final static int RS1ST_RADAR_FIELD_ID = 12;
    public final static int RS2ET_RADAR_FIELD_ID = 13;
    public final static int RS2ST_RADAR_FIELD_ID = 14;
    public final static int RSTCLT_RADAR_FIELD_ID = 15;
    public final static int RATUTS_RADAR_FIELD_ID = 16;
    public final static int VPOBT_VESSEL_FIELD_ID = 17;

    public ComplexInt32TimeseriesDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public Guid getId( ) throws SQLException {
        return getGuid( I32T_ID_FIELD_ID );
    }

    public int getObjectType() throws SQLException {
        return getInt32( I32T_KIND_FIELD_ID );
    }

    public long getRowVersion( ) throws SQLException {
        return getInt64( I32T_ROWVERSION_FIELD_ID );
    }

    public Guid getCatalog( ) throws SQLException {
        return getNullableGuid( I32T_CATALOG_FIELD_ID );
    }

    public String getName( ) throws SQLException {
        return getString( I32T_NAME_FIELD_ID );
    }

    public TimeSpan getMaxRetention( ) throws SQLException {
        return getTimeSpan( I32T_MAXRETENTION_FIELD_ID );
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

}

