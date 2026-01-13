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

public class SimpleAisBinaryAcknowledgeMessageDataReader extends SimpleAisMessageDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  abac.[Id], \r\n" +
            "  abac.[EntityType], \r\n" +
            "  abac.[RowVersion], \r\n" +
            "  abac.[AisDevice], \r\n" +
            "  abac.[ReceivedTimestamp], \r\n" +
            "  abac.[MessageSequenceNumber], \r\n" +
            "  abac.[Repeat], \r\n" +
            "  abac.[Mmsi], \r\n" +
            "  abac.[Spare], \r\n" +
            "  abac.[SequenceNumber1], \r\n" +
            "  abac.[Mmsi1], \r\n" +
            "  abac.[SequenceNumber2], \r\n" +
            "  abac.[Mmsi2], \r\n" +
            "  abac.[SequenceNumber3], \r\n" +
            "  abac.[Mmsi3], \r\n" +
            "  abac.[SequenceNumber4], \r\n" +
            "  abac.[Mmsi4] \r\n" +
            "FROM [AisBinaryAcknowledgeMessageView] abac \r\n";

    public final static String BaseViewName = "AisBinaryAcknowledgeMessageView";
    public final static String ViewAliasName = "abac";

    public final static int SPARE_FIELD_ID = 9;
    public final static int SEQUENCENUMBER1_FIELD_ID = 10;
    public final static int MMSI1_FIELD_ID = 11;
    public final static int SEQUENCENUMBER2_FIELD_ID = 12;
    public final static int MMSI2_FIELD_ID = 13;
    public final static int SEQUENCENUMBER3_FIELD_ID = 14;
    public final static int MMSI3_FIELD_ID = 15;
    public final static int SEQUENCENUMBER4_FIELD_ID = 16;
    public final static int MMSI4_FIELD_ID = 17;

    public SimpleAisBinaryAcknowledgeMessageDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final int getSpare() throws SQLException {
        return getInt32( SPARE_FIELD_ID );
    }

    public final int getSequenceNumber1() throws SQLException {
        return getInt32( SEQUENCENUMBER1_FIELD_ID );
    }

    public final Guid getMmsi1() throws SQLException {
        return getNullableGuid( MMSI1_FIELD_ID );
    }

    public final Integer getSequenceNumber2() throws SQLException {
        return getNullableInt32( SEQUENCENUMBER2_FIELD_ID );
    }

    public final Guid getMmsi2() throws SQLException {
        return getNullableGuid( MMSI2_FIELD_ID );
    }

    public final Integer getSequenceNumber3() throws SQLException {
        return getNullableInt32( SEQUENCENUMBER3_FIELD_ID );
    }

    public final Guid getMmsi3() throws SQLException {
        return getNullableGuid( MMSI3_FIELD_ID );
    }

    public final Integer getSequenceNumber4() throws SQLException {
        return getNullableInt32( SEQUENCENUMBER4_FIELD_ID );
    }

    public final Guid getMmsi4() throws SQLException {
        return getNullableGuid( MMSI4_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeInt32( getSpare( ) );
        destination.writeInt32( getSequenceNumber1( ) );
        destination.writeNullableGuid( getMmsi1( ) );
        destination.writeNullableInt32( getSequenceNumber2( ) );
        destination.writeNullableGuid( getMmsi2( ) );
        destination.writeNullableInt32( getSequenceNumber3( ) );
        destination.writeNullableGuid( getMmsi3( ) );
        destination.writeNullableInt32( getSequenceNumber4( ) );
        destination.writeNullableGuid( getMmsi4( ) );
    }

    @Override
    public AisBinaryAcknowledgeMessageObject getDataObject( ) throws SQLException {
        return new AisBinaryAcknowledgeMessageObject( ObjectState.Stored, getId( ), getRowVersion( ), getAisDevice( ), getReceivedTimestamp( ), getMessageSequenceNumber( ), getRepeat( ), getMmsi( ), getSpare( ), getSequenceNumber1( ), getMmsi1( ), getSequenceNumber2( ), getMmsi2( ), getSequenceNumber3( ), getMmsi3( ), getSequenceNumber4( ), getMmsi4( ) );
    }

}
