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

public class SimpleAisPositionReportClassAResponseToInterrogationMessageDataReader extends SimpleAisPositionReportClassAMessageBaseDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  aprcatim.[Id], \r\n" +
            "  aprcatim.[EntityType], \r\n" +
            "  aprcatim.[RowVersion], \r\n" +
            "  aprcatim.[AisDevice], \r\n" +
            "  aprcatim.[ReceivedTimestamp], \r\n" +
            "  aprcatim.[MessageSequenceNumber], \r\n" +
            "  aprcatim.[Repeat], \r\n" +
            "  aprcatim.[Mmsi], \r\n" +
            "  aprcatim.[NavigationStatus], \r\n" +
            "  aprcatim.[RateOfTurn], \r\n" +
            "  aprcatim.[SpeedOverGround], \r\n" +
            "  aprcatim.[PositionAccuracy], \r\n" +
            "  aprcatim.[Longitude], \r\n" +
            "  aprcatim.[Latitude], \r\n" +
            "  aprcatim.[CourseOverGround], \r\n" +
            "  aprcatim.[TrueHeading], \r\n" +
            "  aprcatim.[Timestamp], \r\n" +
            "  aprcatim.[ManeuverIndicator], \r\n" +
            "  aprcatim.[Spare], \r\n" +
            "  aprcatim.[Raim], \r\n" +
            "  aprcatim.[RadioStatus] \r\n" +
            "FROM [AisPositionReportClassAResponseToInterrogationMessageView] aprcatim \r\n";

    public final static String BaseViewName = "AisPositionReportClassAResponseToInterrogationMessageView";
    public final static String ViewAliasName = "aprcatim";

    public SimpleAisPositionReportClassAResponseToInterrogationMessageDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
    }

    @Override
    public AisPositionReportClassAResponseToInterrogationMessageObject getDataObject( ) throws SQLException {
        return new AisPositionReportClassAResponseToInterrogationMessageObject( ObjectState.Stored, getId( ), getRowVersion( ), getAisDevice( ), getReceivedTimestamp( ), getMessageSequenceNumber( ), getRepeat( ), getMmsi( ), getNavigationStatus( ), getRateOfTurn( ), getSpeedOverGround( ), getPositionAccuracy( ), getLongitude( ), getLatitude( ), getCourseOverGround( ), getTrueHeading( ), getTimestamp( ), getManeuverIndicator( ), getSpare( ), getRaim( ), getRadioStatus( ) );
    }

}
