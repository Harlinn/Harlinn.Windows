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

    @Override
    public AisPositionReportClassAAssignedScheduleMessageObject getDataObject( ) throws SQLException {
        return new AisPositionReportClassAAssignedScheduleMessageObject( ObjectState.Stored, getId( ), getRowVersion( ), getAisDevice( ), getReceivedTimestamp( ), getMessageSequenceNumber( ), getRepeat( ), getMmsi( ), getNavigationStatus( ), getRateOfTurn( ), getSpeedOverGround( ), getPositionAccuracy( ), getLongitude( ), getLatitude( ), getCourseOverGround( ), getTrueHeading( ), getTimestamp( ), getManeuverIndicator( ), getSpare( ), getRaim( ), getRadioStatus( ) );
    }

}
