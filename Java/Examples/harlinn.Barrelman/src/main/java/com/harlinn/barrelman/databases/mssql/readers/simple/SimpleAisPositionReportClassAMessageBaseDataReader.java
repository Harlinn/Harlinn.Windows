package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public abstract class SimpleAisPositionReportClassAMessageBaseDataReader extends SimpleAisMessageDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  aprcab.[Id], \r\n" +
            "  aprcab.[EntityType], \r\n" +
            "  aprcab.[RowVersion], \r\n" +
            "  aprcab.[AisDevice], \r\n" +
            "  aprcab.[ReceivedTimestamp], \r\n" +
            "  aprcab.[MessageSequenceNumber], \r\n" +
            "  aprcab.[Repeat], \r\n" +
            "  aprcab.[Mmsi], \r\n" +
            "  aprcab.[NavigationStatus], \r\n" +
            "  aprcab.[RateOfTurn], \r\n" +
            "  aprcab.[SpeedOverGround], \r\n" +
            "  aprcab.[PositionAccuracy], \r\n" +
            "  aprcab.[Longitude], \r\n" +
            "  aprcab.[Latitude], \r\n" +
            "  aprcab.[CourseOverGround], \r\n" +
            "  aprcab.[TrueHeading], \r\n" +
            "  aprcab.[Timestamp], \r\n" +
            "  aprcab.[ManeuverIndicator], \r\n" +
            "  aprcab.[Spare], \r\n" +
            "  aprcab.[Raim], \r\n" +
            "  aprcab.[RadioStatus] \r\n" +
            "FROM [AisPositionReportClassAMessageBaseView] aprcab \r\n";

    public final static String BaseViewName = "AisPositionReportClassAMessageBaseView";
    public final static String ViewAliasName = "aprcab";

    public final static int NAVIGATIONSTATUS_FIELD_ID = 9;
    public final static int RATEOFTURN_FIELD_ID = 10;
    public final static int SPEEDOVERGROUND_FIELD_ID = 11;
    public final static int POSITIONACCURACY_FIELD_ID = 12;
    public final static int LONGITUDE_FIELD_ID = 13;
    public final static int LATITUDE_FIELD_ID = 14;
    public final static int COURSEOVERGROUND_FIELD_ID = 15;
    public final static int TRUEHEADING_FIELD_ID = 16;
    public final static int TIMESTAMP_FIELD_ID = 17;
    public final static int MANEUVERINDICATOR_FIELD_ID = 18;
    public final static int SPARE_FIELD_ID = 19;
    public final static int RAIM_FIELD_ID = 20;
    public final static int RADIOSTATUS_FIELD_ID = 21;

    public SimpleAisPositionReportClassAMessageBaseDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final int getNavigationStatus() throws SQLException {
        return getInt32( NAVIGATIONSTATUS_FIELD_ID );
    }

    public final Integer getRateOfTurn() throws SQLException {
        return getNullableInt32( RATEOFTURN_FIELD_ID );
    }

    public final double getSpeedOverGround() throws SQLException {
        return getDouble( SPEEDOVERGROUND_FIELD_ID );
    }

    public final int getPositionAccuracy() throws SQLException {
        return getInt32( POSITIONACCURACY_FIELD_ID );
    }

    public final double getLongitude() throws SQLException {
        return getDouble( LONGITUDE_FIELD_ID );
    }

    public final double getLatitude() throws SQLException {
        return getDouble( LATITUDE_FIELD_ID );
    }

    public final double getCourseOverGround() throws SQLException {
        return getDouble( COURSEOVERGROUND_FIELD_ID );
    }

    public final Integer getTrueHeading() throws SQLException {
        return getNullableInt32( TRUEHEADING_FIELD_ID );
    }

    public final int getTimestamp() throws SQLException {
        return getInt32( TIMESTAMP_FIELD_ID );
    }

    public final int getManeuverIndicator() throws SQLException {
        return getInt32( MANEUVERINDICATOR_FIELD_ID );
    }

    public final int getSpare() throws SQLException {
        return getInt32( SPARE_FIELD_ID );
    }

    public final int getRaim() throws SQLException {
        return getInt32( RAIM_FIELD_ID );
    }

    public final int getRadioStatus() throws SQLException {
        return getInt32( RADIOSTATUS_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeInt32( getNavigationStatus( ) );
        destination.writeNullableInt32( getRateOfTurn( ) );
        destination.writeDouble( getSpeedOverGround( ) );
        destination.writeInt32( getPositionAccuracy( ) );
        destination.writeDouble( getLongitude( ) );
        destination.writeDouble( getLatitude( ) );
        destination.writeDouble( getCourseOverGround( ) );
        destination.writeNullableInt32( getTrueHeading( ) );
        destination.writeInt32( getTimestamp( ) );
        destination.writeInt32( getManeuverIndicator( ) );
        destination.writeInt32( getSpare( ) );
        destination.writeInt32( getRaim( ) );
        destination.writeInt32( getRadioStatus( ) );
    }

}
