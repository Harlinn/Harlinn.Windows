package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleAisPositionReportForLongRangeApplicationsMessageDataReader extends SimpleAisMessageDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  aprflram.[Id], \r\n" +
            "  aprflram.[EntityType], \r\n" +
            "  aprflram.[RowVersion], \r\n" +
            "  aprflram.[AisDevice], \r\n" +
            "  aprflram.[ReceivedTimestamp], \r\n" +
            "  aprflram.[MessageSequenceNumber], \r\n" +
            "  aprflram.[Repeat], \r\n" +
            "  aprflram.[Mmsi], \r\n" +
            "  aprflram.[PositionAccuracy], \r\n" +
            "  aprflram.[Raim], \r\n" +
            "  aprflram.[NavigationStatus], \r\n" +
            "  aprflram.[Longitude], \r\n" +
            "  aprflram.[Latitude], \r\n" +
            "  aprflram.[SpeedOverGround], \r\n" +
            "  aprflram.[CourseOverGround], \r\n" +
            "  aprflram.[GnssPositionStatus], \r\n" +
            "  aprflram.[Spare] \r\n" +
            "FROM [AisPositionReportForLongRangeApplicationsMessageView] aprflram \r\n";

    public final static String BaseViewName = "AisPositionReportForLongRangeApplicationsMessageView";
    public final static String ViewAliasName = "aprflram";

    public final static int POSITIONACCURACY_FIELD_ID = 9;
    public final static int RAIM_FIELD_ID = 10;
    public final static int NAVIGATIONSTATUS_FIELD_ID = 11;
    public final static int LONGITUDE_FIELD_ID = 12;
    public final static int LATITUDE_FIELD_ID = 13;
    public final static int SPEEDOVERGROUND_FIELD_ID = 14;
    public final static int COURSEOVERGROUND_FIELD_ID = 15;
    public final static int GNSSPOSITIONSTATUS_FIELD_ID = 16;
    public final static int SPARE_FIELD_ID = 17;

    public SimpleAisPositionReportForLongRangeApplicationsMessageDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final int getPositionAccuracy() throws SQLException {
        return getInt32( POSITIONACCURACY_FIELD_ID );
    }

    public final int getRaim() throws SQLException {
        return getInt32( RAIM_FIELD_ID );
    }

    public final int getNavigationStatus() throws SQLException {
        return getInt32( NAVIGATIONSTATUS_FIELD_ID );
    }

    public final double getLongitude() throws SQLException {
        return getDouble( LONGITUDE_FIELD_ID );
    }

    public final double getLatitude() throws SQLException {
        return getDouble( LATITUDE_FIELD_ID );
    }

    public final double getSpeedOverGround() throws SQLException {
        return getDouble( SPEEDOVERGROUND_FIELD_ID );
    }

    public final double getCourseOverGround() throws SQLException {
        return getDouble( COURSEOVERGROUND_FIELD_ID );
    }

    public final int getGnssPositionStatus() throws SQLException {
        return getInt32( GNSSPOSITIONSTATUS_FIELD_ID );
    }

    public final int getSpare() throws SQLException {
        return getInt32( SPARE_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeInt32( getPositionAccuracy( ) );
        destination.writeInt32( getRaim( ) );
        destination.writeInt32( getNavigationStatus( ) );
        destination.writeDouble( getLongitude( ) );
        destination.writeDouble( getLatitude( ) );
        destination.writeDouble( getSpeedOverGround( ) );
        destination.writeDouble( getCourseOverGround( ) );
        destination.writeInt32( getGnssPositionStatus( ) );
        destination.writeInt32( getSpare( ) );
    }

    @Override
    public AisPositionReportForLongRangeApplicationsMessageObject GetDataObject( ) throws SQLException {
        return new AisPositionReportForLongRangeApplicationsMessageObject( ObjectState.Stored, getId( ), getRowVersion( ), getAisDevice( ), getReceivedTimestamp( ), getMessageSequenceNumber( ), getRepeat( ), getMmsi( ), getPositionAccuracy( ), getRaim( ), getNavigationStatus( ), getLongitude( ), getLatitude( ), getSpeedOverGround( ), getCourseOverGround( ), getGnssPositionStatus( ), getSpare( ) );
    }

}
