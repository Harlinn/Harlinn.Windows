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

public class SimpleAisStandardSarAircraftPositionReportMessageDataReader extends SimpleAisMessageDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  assaprm.[Id], \r\n" +
            "  assaprm.[EntityType], \r\n" +
            "  assaprm.[RowVersion], \r\n" +
            "  assaprm.[AisDevice], \r\n" +
            "  assaprm.[ReceivedTimestamp], \r\n" +
            "  assaprm.[MessageSequenceNumber], \r\n" +
            "  assaprm.[Repeat], \r\n" +
            "  assaprm.[Mmsi], \r\n" +
            "  assaprm.[Altitude], \r\n" +
            "  assaprm.[SpeedOverGround], \r\n" +
            "  assaprm.[PositionAccuracy], \r\n" +
            "  assaprm.[Longitude], \r\n" +
            "  assaprm.[Latitude], \r\n" +
            "  assaprm.[CourseOverGround], \r\n" +
            "  assaprm.[Timestamp], \r\n" +
            "  assaprm.[Reserved], \r\n" +
            "  assaprm.[DataTerminalReady], \r\n" +
            "  assaprm.[Spare], \r\n" +
            "  assaprm.[Assigned], \r\n" +
            "  assaprm.[Raim], \r\n" +
            "  assaprm.[RadioStatus] \r\n" +
            "FROM [AisStandardSarAircraftPositionReportMessageView] assaprm \r\n";

    public final static String BaseViewName = "AisStandardSarAircraftPositionReportMessageView";
    public final static String ViewAliasName = "assaprm";

    public final static int ALTITUDE_FIELD_ID = 9;
    public final static int SPEEDOVERGROUND_FIELD_ID = 10;
    public final static int POSITIONACCURACY_FIELD_ID = 11;
    public final static int LONGITUDE_FIELD_ID = 12;
    public final static int LATITUDE_FIELD_ID = 13;
    public final static int COURSEOVERGROUND_FIELD_ID = 14;
    public final static int TIMESTAMP_FIELD_ID = 15;
    public final static int RESERVED_FIELD_ID = 16;
    public final static int DATATERMINALREADY_FIELD_ID = 17;
    public final static int SPARE_FIELD_ID = 18;
    public final static int ASSIGNED_FIELD_ID = 19;
    public final static int RAIM_FIELD_ID = 20;
    public final static int RADIOSTATUS_FIELD_ID = 21;

    public SimpleAisStandardSarAircraftPositionReportMessageDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final int getAltitude() throws SQLException {
        return getInt32( ALTITUDE_FIELD_ID );
    }

    public final int getSpeedOverGround() throws SQLException {
        return getInt32( SPEEDOVERGROUND_FIELD_ID );
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

    public final int getTimestamp() throws SQLException {
        return getInt32( TIMESTAMP_FIELD_ID );
    }

    public final int getReserved() throws SQLException {
        return getInt32( RESERVED_FIELD_ID );
    }

    public final boolean getDataTerminalReady() throws SQLException {
        return getBoolean( DATATERMINALREADY_FIELD_ID );
    }

    public final int getSpare() throws SQLException {
        return getInt32( SPARE_FIELD_ID );
    }

    public final boolean getAssigned() throws SQLException {
        return getBoolean( ASSIGNED_FIELD_ID );
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
        destination.writeInt32( getAltitude( ) );
        destination.writeInt32( getSpeedOverGround( ) );
        destination.writeInt32( getPositionAccuracy( ) );
        destination.writeDouble( getLongitude( ) );
        destination.writeDouble( getLatitude( ) );
        destination.writeDouble( getCourseOverGround( ) );
        destination.writeInt32( getTimestamp( ) );
        destination.writeInt32( getReserved( ) );
        destination.writeBoolean( getDataTerminalReady( ) );
        destination.writeInt32( getSpare( ) );
        destination.writeBoolean( getAssigned( ) );
        destination.writeInt32( getRaim( ) );
        destination.writeInt32( getRadioStatus( ) );
    }

    @Override
    public AisStandardSarAircraftPositionReportMessageObject getDataObject( ) throws SQLException {
        return new AisStandardSarAircraftPositionReportMessageObject( ObjectState.Stored, getId( ), getRowVersion( ), getAisDevice( ), getReceivedTimestamp( ), getMessageSequenceNumber( ), getRepeat( ), getMmsi( ), getAltitude( ), getSpeedOverGround( ), getPositionAccuracy( ), getLongitude( ), getLatitude( ), getCourseOverGround( ), getTimestamp( ), getReserved( ), getDataTerminalReady( ), getSpare( ), getAssigned( ), getRaim( ), getRadioStatus( ) );
    }

}
