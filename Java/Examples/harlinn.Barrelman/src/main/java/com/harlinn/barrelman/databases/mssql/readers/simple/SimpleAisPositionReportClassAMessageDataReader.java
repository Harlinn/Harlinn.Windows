package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleAisPositionReportClassAMessageDataReader extends SimpleAisPositionReportClassAMessageBaseDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  aprca.[Id], \r\n" +
            "  aprca.[EntityType], \r\n" +
            "  aprca.[RowVersion], \r\n" +
            "  aprca.[AisDevice], \r\n" +
            "  aprca.[ReceivedTimestamp], \r\n" +
            "  aprca.[MessageSequenceNumber], \r\n" +
            "  aprca.[Repeat], \r\n" +
            "  aprca.[Mmsi], \r\n" +
            "  aprca.[NavigationStatus], \r\n" +
            "  aprca.[RateOfTurn], \r\n" +
            "  aprca.[SpeedOverGround], \r\n" +
            "  aprca.[PositionAccuracy], \r\n" +
            "  aprca.[Longitude], \r\n" +
            "  aprca.[Latitude], \r\n" +
            "  aprca.[CourseOverGround], \r\n" +
            "  aprca.[TrueHeading], \r\n" +
            "  aprca.[Timestamp], \r\n" +
            "  aprca.[ManeuverIndicator], \r\n" +
            "  aprca.[Spare], \r\n" +
            "  aprca.[Raim], \r\n" +
            "  aprca.[RadioStatus] \r\n" +
            "FROM [AisPositionReportClassAMessageView] aprca \r\n";

    public final static String BaseViewName = "AisPositionReportClassAMessageView";
    public final static String ViewAliasName = "aprca";

    public SimpleAisPositionReportClassAMessageDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
    }

    @Override
    public AisPositionReportClassAMessageObject getDataObject( ) throws SQLException {
        return new AisPositionReportClassAMessageObject( ObjectState.Stored, getId( ), getRowVersion( ), getAisDevice( ), getReceivedTimestamp( ), getMessageSequenceNumber( ), getRepeat( ), getMmsi( ), getNavigationStatus( ), getRateOfTurn( ), getSpeedOverGround( ), getPositionAccuracy( ), getLongitude( ), getLatitude( ), getCourseOverGround( ), getTrueHeading( ), getTimestamp( ), getManeuverIndicator( ), getSpare( ), getRaim( ), getRadioStatus( ) );
    }

}
