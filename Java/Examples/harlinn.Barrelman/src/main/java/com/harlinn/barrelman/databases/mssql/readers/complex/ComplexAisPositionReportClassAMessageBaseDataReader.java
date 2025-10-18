package com.harlinn.barrelman.databases.mssql.readers.complex;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class ComplexAisPositionReportClassAMessageBaseDataReader extends ResultSetWrapper {

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
            "FROM [AisPositionReportClassAMessageBaseView] aprcab \r\n" +
            "  LEFT JOIN [AisPositionReportClassAAssignedScheduleMessage] aprcasm ON(aprcab.[Id] = aprcasm.[Id] ) \r\n" +
            "  LEFT JOIN [AisPositionReportClassAMessage] aprca ON(aprcab.[Id] = aprca.[Id] ) \r\n" +
            "  LEFT JOIN [AisPositionReportClassAResponseToInterrogationMessage] aprcatim ON(aprcab.[Id] = aprcatim.[Id] ) \r\n";

    public final static String BaseViewName = "AisPositionReportClassAMessageBaseView";
    public final static String ViewAliasName = "aprcab";

    public final static int APRCAB_ID_FIELD_ID = 1;
    public final static int APRCAB_KIND_FIELD_ID = 2;
    public final static int APRCAB_ROWVERSION_FIELD_ID = 3;
    public final static int APRCAB_AISDEVICE_FIELD_ID = 4;
    public final static int APRCAB_RECEIVEDTIMESTAMP_FIELD_ID = 5;
    public final static int APRCAB_MESSAGESEQUENCENUMBER_FIELD_ID = 6;
    public final static int APRCAB_REPEAT_FIELD_ID = 7;
    public final static int APRCAB_MMSI_FIELD_ID = 8;
    public final static int APRCAB_NAVIGATIONSTATUS_FIELD_ID = 9;
    public final static int APRCAB_RATEOFTURN_FIELD_ID = 10;
    public final static int APRCAB_SPEEDOVERGROUND_FIELD_ID = 11;
    public final static int APRCAB_POSITIONACCURACY_FIELD_ID = 12;
    public final static int APRCAB_LONGITUDE_FIELD_ID = 13;
    public final static int APRCAB_LATITUDE_FIELD_ID = 14;
    public final static int APRCAB_COURSEOVERGROUND_FIELD_ID = 15;
    public final static int APRCAB_TRUEHEADING_FIELD_ID = 16;
    public final static int APRCAB_TIMESTAMP_FIELD_ID = 17;
    public final static int APRCAB_MANEUVERINDICATOR_FIELD_ID = 18;
    public final static int APRCAB_SPARE_FIELD_ID = 19;
    public final static int APRCAB_RAIM_FIELD_ID = 20;
    public final static int APRCAB_RADIOSTATUS_FIELD_ID = 21;

    public ComplexAisPositionReportClassAMessageBaseDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public Guid getId( ) throws SQLException {
        return getGuid( APRCAB_ID_FIELD_ID );
    }

    public int getObjectType() throws SQLException {
        return getInt32( APRCAB_KIND_FIELD_ID );
    }

    public long getRowVersion( ) throws SQLException {
        return getInt64( APRCAB_ROWVERSION_FIELD_ID );
    }

    public Guid getAisDevice( ) throws SQLException {
        return getGuid( APRCAB_AISDEVICE_FIELD_ID );
    }

    public DateTime getReceivedTimestamp( ) throws SQLException {
        return getDateTimeFromLong( APRCAB_RECEIVEDTIMESTAMP_FIELD_ID );
    }

    public long getMessageSequenceNumber( ) throws SQLException {
        return getInt64( APRCAB_MESSAGESEQUENCENUMBER_FIELD_ID );
    }

    public int getRepeat( ) throws SQLException {
        return getInt32( APRCAB_REPEAT_FIELD_ID );
    }

    public Guid getMmsi( ) throws SQLException {
        return getNullableGuid( APRCAB_MMSI_FIELD_ID );
    }

    public int getNavigationStatus( ) throws SQLException {
        return getInt32( APRCAB_NAVIGATIONSTATUS_FIELD_ID );
    }

    public Integer getRateOfTurn( ) throws SQLException {
        return getNullableInt32( APRCAB_RATEOFTURN_FIELD_ID );
    }

    public double getSpeedOverGround( ) throws SQLException {
        return getDouble( APRCAB_SPEEDOVERGROUND_FIELD_ID );
    }

    public int getPositionAccuracy( ) throws SQLException {
        return getInt32( APRCAB_POSITIONACCURACY_FIELD_ID );
    }

    public double getLongitude( ) throws SQLException {
        return getDouble( APRCAB_LONGITUDE_FIELD_ID );
    }

    public double getLatitude( ) throws SQLException {
        return getDouble( APRCAB_LATITUDE_FIELD_ID );
    }

    public double getCourseOverGround( ) throws SQLException {
        return getDouble( APRCAB_COURSEOVERGROUND_FIELD_ID );
    }

    public Integer getTrueHeading( ) throws SQLException {
        return getNullableInt32( APRCAB_TRUEHEADING_FIELD_ID );
    }

    public int getTimestamp( ) throws SQLException {
        return getInt32( APRCAB_TIMESTAMP_FIELD_ID );
    }

    public int getManeuverIndicator( ) throws SQLException {
        return getInt32( APRCAB_MANEUVERINDICATOR_FIELD_ID );
    }

    public int getSpare( ) throws SQLException {
        return getInt32( APRCAB_SPARE_FIELD_ID );
    }

    public int getRaim( ) throws SQLException {
        return getInt32( APRCAB_RAIM_FIELD_ID );
    }

    public int getRadioStatus( ) throws SQLException {
        return getInt32( APRCAB_RADIOSTATUS_FIELD_ID );
    }

}

