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

public class SimpleAisStandardClassBCsPositionReportMessageDataReader extends SimpleAisMessageDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  ascbprm.[Id], \r\n" +
            "  ascbprm.[EntityType], \r\n" +
            "  ascbprm.[RowVersion], \r\n" +
            "  ascbprm.[AisDevice], \r\n" +
            "  ascbprm.[ReceivedTimestamp], \r\n" +
            "  ascbprm.[MessageSequenceNumber], \r\n" +
            "  ascbprm.[Repeat], \r\n" +
            "  ascbprm.[Mmsi], \r\n" +
            "  ascbprm.[Reserved], \r\n" +
            "  ascbprm.[SpeedOverGround], \r\n" +
            "  ascbprm.[PositionAccuracy], \r\n" +
            "  ascbprm.[Longitude], \r\n" +
            "  ascbprm.[Latitude], \r\n" +
            "  ascbprm.[CourseOverGround], \r\n" +
            "  ascbprm.[TrueHeading], \r\n" +
            "  ascbprm.[Timestamp], \r\n" +
            "  ascbprm.[RegionalReserved], \r\n" +
            "  ascbprm.[IsCsUnit], \r\n" +
            "  ascbprm.[HasDisplay], \r\n" +
            "  ascbprm.[HasDscCapability], \r\n" +
            "  ascbprm.[Band], \r\n" +
            "  ascbprm.[CanAcceptMessage22], \r\n" +
            "  ascbprm.[Assigned], \r\n" +
            "  ascbprm.[Raim], \r\n" +
            "  ascbprm.[RadioStatus] \r\n" +
            "FROM [AisStandardClassBCsPositionReportMessageView] ascbprm \r\n";

    public final static String BaseViewName = "AisStandardClassBCsPositionReportMessageView";
    public final static String ViewAliasName = "ascbprm";

    public final static int RESERVED_FIELD_ID = 9;
    public final static int SPEEDOVERGROUND_FIELD_ID = 10;
    public final static int POSITIONACCURACY_FIELD_ID = 11;
    public final static int LONGITUDE_FIELD_ID = 12;
    public final static int LATITUDE_FIELD_ID = 13;
    public final static int COURSEOVERGROUND_FIELD_ID = 14;
    public final static int TRUEHEADING_FIELD_ID = 15;
    public final static int TIMESTAMP_FIELD_ID = 16;
    public final static int REGIONALRESERVED_FIELD_ID = 17;
    public final static int ISCSUNIT_FIELD_ID = 18;
    public final static int HASDISPLAY_FIELD_ID = 19;
    public final static int HASDSCCAPABILITY_FIELD_ID = 20;
    public final static int BAND_FIELD_ID = 21;
    public final static int CANACCEPTMESSAGE22_FIELD_ID = 22;
    public final static int ASSIGNED_FIELD_ID = 23;
    public final static int RAIM_FIELD_ID = 24;
    public final static int RADIOSTATUS_FIELD_ID = 25;

    public SimpleAisStandardClassBCsPositionReportMessageDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final int getReserved() throws SQLException {
        return getInt32( RESERVED_FIELD_ID );
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

    public final int getRegionalReserved() throws SQLException {
        return getInt32( REGIONALRESERVED_FIELD_ID );
    }

    public final boolean getIsCsUnit() throws SQLException {
        return getBoolean( ISCSUNIT_FIELD_ID );
    }

    public final boolean getHasDisplay() throws SQLException {
        return getBoolean( HASDISPLAY_FIELD_ID );
    }

    public final boolean getHasDscCapability() throws SQLException {
        return getBoolean( HASDSCCAPABILITY_FIELD_ID );
    }

    public final boolean getBand() throws SQLException {
        return getBoolean( BAND_FIELD_ID );
    }

    public final boolean getCanAcceptMessage22() throws SQLException {
        return getBoolean( CANACCEPTMESSAGE22_FIELD_ID );
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
        destination.writeInt32( getReserved( ) );
        destination.writeDouble( getSpeedOverGround( ) );
        destination.writeInt32( getPositionAccuracy( ) );
        destination.writeDouble( getLongitude( ) );
        destination.writeDouble( getLatitude( ) );
        destination.writeDouble( getCourseOverGround( ) );
        destination.writeNullableInt32( getTrueHeading( ) );
        destination.writeInt32( getTimestamp( ) );
        destination.writeInt32( getRegionalReserved( ) );
        destination.writeBoolean( getIsCsUnit( ) );
        destination.writeBoolean( getHasDisplay( ) );
        destination.writeBoolean( getHasDscCapability( ) );
        destination.writeBoolean( getBand( ) );
        destination.writeBoolean( getCanAcceptMessage22( ) );
        destination.writeBoolean( getAssigned( ) );
        destination.writeInt32( getRaim( ) );
        destination.writeInt32( getRadioStatus( ) );
    }

    @Override
    public AisStandardClassBCsPositionReportMessageObject getDataObject( ) throws SQLException {
        return new AisStandardClassBCsPositionReportMessageObject( ObjectState.Stored, getId( ), getRowVersion( ), getAisDevice( ), getReceivedTimestamp( ), getMessageSequenceNumber( ), getRepeat( ), getMmsi( ), getReserved( ), getSpeedOverGround( ), getPositionAccuracy( ), getLongitude( ), getLatitude( ), getCourseOverGround( ), getTrueHeading( ), getTimestamp( ), getRegionalReserved( ), getIsCsUnit( ), getHasDisplay( ), getHasDscCapability( ), getBand( ), getCanAcceptMessage22( ), getAssigned( ), getRaim( ), getRadioStatus( ) );
    }

}
