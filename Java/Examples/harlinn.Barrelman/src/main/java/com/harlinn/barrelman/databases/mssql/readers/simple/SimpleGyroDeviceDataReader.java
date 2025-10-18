package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleGyroDeviceDataReader extends SimpleDeviceDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  gd.[Id], \r\n" +
            "  gd.[EntityType], \r\n" +
            "  gd.[RowVersion], \r\n" +
            "  gd.[Host], \r\n" +
            "  gd.[Name], \r\n" +
            "  gd.[Description], \r\n" +
            "  gd.[EnabledTimeseries], \r\n" +
            "  gd.[HeadingTrueNorthTimeseries], \r\n" +
            "  gd.[HeadingMagneticNorthTimeseries], \r\n" +
            "  gd.[PitchTimeseries], \r\n" +
            "  gd.[RateOfTurnTimeseries], \r\n" +
            "  gd.[RollTimeseries], \r\n" +
            "  gd.[CourseTimeseries], \r\n" +
            "  gd.[SpeedTimeseries], \r\n" +
            "  gd.[GNSSDevice] \r\n" +
            "FROM [GyroDeviceView] gd \r\n";

    public final static String BaseViewName = "GyroDeviceView";
    public final static String ViewAliasName = "gd";

    public final static int HEADINGTRUENORTHTIMESERIES_FIELD_ID = 8;
    public final static int HEADINGMAGNETICNORTHTIMESERIES_FIELD_ID = 9;
    public final static int PITCHTIMESERIES_FIELD_ID = 10;
    public final static int RATEOFTURNTIMESERIES_FIELD_ID = 11;
    public final static int ROLLTIMESERIES_FIELD_ID = 12;
    public final static int COURSETIMESERIES_FIELD_ID = 13;
    public final static int SPEEDTIMESERIES_FIELD_ID = 14;
    public final static int GNSSDEVICE_FIELD_ID = 15;

    public SimpleGyroDeviceDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getHeadingTrueNorthTimeseries() throws SQLException {
        return getNullableGuid( HEADINGTRUENORTHTIMESERIES_FIELD_ID );
    }

    public final Guid getHeadingMagneticNorthTimeseries() throws SQLException {
        return getNullableGuid( HEADINGMAGNETICNORTHTIMESERIES_FIELD_ID );
    }

    public final Guid getPitchTimeseries() throws SQLException {
        return getNullableGuid( PITCHTIMESERIES_FIELD_ID );
    }

    public final Guid getRateOfTurnTimeseries() throws SQLException {
        return getNullableGuid( RATEOFTURNTIMESERIES_FIELD_ID );
    }

    public final Guid getRollTimeseries() throws SQLException {
        return getNullableGuid( ROLLTIMESERIES_FIELD_ID );
    }

    public final Guid getCourseTimeseries() throws SQLException {
        return getNullableGuid( COURSETIMESERIES_FIELD_ID );
    }

    public final Guid getSpeedTimeseries() throws SQLException {
        return getNullableGuid( SPEEDTIMESERIES_FIELD_ID );
    }

    public final Guid getGNSSDevice() throws SQLException {
        return getNullableGuid( GNSSDEVICE_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeNullableGuid( getHeadingTrueNorthTimeseries( ) );
        destination.writeNullableGuid( getHeadingMagneticNorthTimeseries( ) );
        destination.writeNullableGuid( getPitchTimeseries( ) );
        destination.writeNullableGuid( getRateOfTurnTimeseries( ) );
        destination.writeNullableGuid( getRollTimeseries( ) );
        destination.writeNullableGuid( getCourseTimeseries( ) );
        destination.writeNullableGuid( getSpeedTimeseries( ) );
        destination.writeNullableGuid( getGNSSDevice( ) );
    }

    @Override
    public GyroDeviceObject GetDataObject( ) throws SQLException {
        return new GyroDeviceObject( ObjectState.Stored, getId( ), getRowVersion( ), getHost( ), getName( ), getDescription( ), getEnabledTimeseries( ), getHeadingTrueNorthTimeseries( ), getHeadingMagneticNorthTimeseries( ), getPitchTimeseries( ), getRateOfTurnTimeseries( ), getRollTimeseries( ), getCourseTimeseries( ), getSpeedTimeseries( ), getGNSSDevice( ) );
    }

}
