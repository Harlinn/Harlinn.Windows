package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleAisPositionReportClassAAssignedScheduleMessageDataReader extends SimpleAisPositionReportClassAMessageBaseDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  aprcasm.[Id], \r\n" +
            "  aprcasm.[EntityType], \r\n" +
            "  aprcasm.[RowVersion], \r\n" +
            "  aprcasm.[AisDevice], \r\n" +
            "  aprcasm.[ReceivedTimestamp], \r\n" +
            "  aprcasm.[MessageSequenceNumber], \r\n" +
            "  aprcasm.[Repeat], \r\n" +
            "  aprcasm.[Mmsi], \r\n" +
            "  aprcasm.[NavigationStatus], \r\n" +
            "  aprcasm.[RateOfTurn], \r\n" +
            "  aprcasm.[SpeedOverGround], \r\n" +
            "  aprcasm.[PositionAccuracy], \r\n" +
            "  aprcasm.[Longitude], \r\n" +
            "  aprcasm.[Latitude], \r\n" +
            "  aprcasm.[CourseOverGround], \r\n" +
            "  aprcasm.[TrueHeading], \r\n" +
            "  aprcasm.[Timestamp], \r\n" +
            "  aprcasm.[ManeuverIndicator], \r\n" +
            "  aprcasm.[Spare], \r\n" +
            "  aprcasm.[Raim], \r\n" +
            "  aprcasm.[RadioStatus] \r\n" +
            "FROM [AisPositionReportClassAAssignedScheduleMessageView] aprcasm \r\n";

    public final static String BaseViewName = "AisPositionReportClassAAssignedScheduleMessageView";
    public final static String ViewAliasName = "aprcasm";

    public SimpleAisPositionReportClassAAssignedScheduleMessageDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
    }

}
