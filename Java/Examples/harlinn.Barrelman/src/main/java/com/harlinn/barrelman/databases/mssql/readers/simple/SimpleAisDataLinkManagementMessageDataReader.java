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

public class SimpleAisDataLinkManagementMessageDataReader extends SimpleAisMessageDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  adlmm.[Id], \r\n" +
            "  adlmm.[EntityType], \r\n" +
            "  adlmm.[RowVersion], \r\n" +
            "  adlmm.[AisDevice], \r\n" +
            "  adlmm.[ReceivedTimestamp], \r\n" +
            "  adlmm.[MessageSequenceNumber], \r\n" +
            "  adlmm.[Repeat], \r\n" +
            "  adlmm.[Mmsi], \r\n" +
            "  adlmm.[Spare], \r\n" +
            "  adlmm.[Offset1], \r\n" +
            "  adlmm.[ReservedSlots1], \r\n" +
            "  adlmm.[Timeout1], \r\n" +
            "  adlmm.[Increment1], \r\n" +
            "  adlmm.[Offset2], \r\n" +
            "  adlmm.[ReservedSlots2], \r\n" +
            "  adlmm.[Timeout2], \r\n" +
            "  adlmm.[Increment2], \r\n" +
            "  adlmm.[Offset3], \r\n" +
            "  adlmm.[ReservedSlots3], \r\n" +
            "  adlmm.[Timeout3], \r\n" +
            "  adlmm.[Increment3], \r\n" +
            "  adlmm.[Offset4], \r\n" +
            "  adlmm.[ReservedSlots4], \r\n" +
            "  adlmm.[Timeout4], \r\n" +
            "  adlmm.[Increment4] \r\n" +
            "FROM [AisDataLinkManagementMessageView] adlmm \r\n";

    public final static String BaseViewName = "AisDataLinkManagementMessageView";
    public final static String ViewAliasName = "adlmm";

    public final static int SPARE_FIELD_ID = 9;
    public final static int OFFSET1_FIELD_ID = 10;
    public final static int RESERVEDSLOTS1_FIELD_ID = 11;
    public final static int TIMEOUT1_FIELD_ID = 12;
    public final static int INCREMENT1_FIELD_ID = 13;
    public final static int OFFSET2_FIELD_ID = 14;
    public final static int RESERVEDSLOTS2_FIELD_ID = 15;
    public final static int TIMEOUT2_FIELD_ID = 16;
    public final static int INCREMENT2_FIELD_ID = 17;
    public final static int OFFSET3_FIELD_ID = 18;
    public final static int RESERVEDSLOTS3_FIELD_ID = 19;
    public final static int TIMEOUT3_FIELD_ID = 20;
    public final static int INCREMENT3_FIELD_ID = 21;
    public final static int OFFSET4_FIELD_ID = 22;
    public final static int RESERVEDSLOTS4_FIELD_ID = 23;
    public final static int TIMEOUT4_FIELD_ID = 24;
    public final static int INCREMENT4_FIELD_ID = 25;

    public SimpleAisDataLinkManagementMessageDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final int getSpare() throws SQLException {
        return getInt32( SPARE_FIELD_ID );
    }

    public final int getOffset1() throws SQLException {
        return getInt32( OFFSET1_FIELD_ID );
    }

    public final int getReservedSlots1() throws SQLException {
        return getInt32( RESERVEDSLOTS1_FIELD_ID );
    }

    public final int getTimeout1() throws SQLException {
        return getInt32( TIMEOUT1_FIELD_ID );
    }

    public final int getIncrement1() throws SQLException {
        return getInt32( INCREMENT1_FIELD_ID );
    }

    public final Integer getOffset2() throws SQLException {
        return getNullableInt32( OFFSET2_FIELD_ID );
    }

    public final Integer getReservedSlots2() throws SQLException {
        return getNullableInt32( RESERVEDSLOTS2_FIELD_ID );
    }

    public final Integer getTimeout2() throws SQLException {
        return getNullableInt32( TIMEOUT2_FIELD_ID );
    }

    public final Integer getIncrement2() throws SQLException {
        return getNullableInt32( INCREMENT2_FIELD_ID );
    }

    public final Integer getOffset3() throws SQLException {
        return getNullableInt32( OFFSET3_FIELD_ID );
    }

    public final Integer getReservedSlots3() throws SQLException {
        return getNullableInt32( RESERVEDSLOTS3_FIELD_ID );
    }

    public final Integer getTimeout3() throws SQLException {
        return getNullableInt32( TIMEOUT3_FIELD_ID );
    }

    public final Integer getIncrement3() throws SQLException {
        return getNullableInt32( INCREMENT3_FIELD_ID );
    }

    public final Integer getOffset4() throws SQLException {
        return getNullableInt32( OFFSET4_FIELD_ID );
    }

    public final Integer getReservedSlots4() throws SQLException {
        return getNullableInt32( RESERVEDSLOTS4_FIELD_ID );
    }

    public final Integer getTimeout4() throws SQLException {
        return getNullableInt32( TIMEOUT4_FIELD_ID );
    }

    public final Integer getIncrement4() throws SQLException {
        return getNullableInt32( INCREMENT4_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeInt32( getSpare( ) );
        destination.writeInt32( getOffset1( ) );
        destination.writeInt32( getReservedSlots1( ) );
        destination.writeInt32( getTimeout1( ) );
        destination.writeInt32( getIncrement1( ) );
        destination.writeNullableInt32( getOffset2( ) );
        destination.writeNullableInt32( getReservedSlots2( ) );
        destination.writeNullableInt32( getTimeout2( ) );
        destination.writeNullableInt32( getIncrement2( ) );
        destination.writeNullableInt32( getOffset3( ) );
        destination.writeNullableInt32( getReservedSlots3( ) );
        destination.writeNullableInt32( getTimeout3( ) );
        destination.writeNullableInt32( getIncrement3( ) );
        destination.writeNullableInt32( getOffset4( ) );
        destination.writeNullableInt32( getReservedSlots4( ) );
        destination.writeNullableInt32( getTimeout4( ) );
        destination.writeNullableInt32( getIncrement4( ) );
    }

    @Override
    public AisDataLinkManagementMessageObject getDataObject( ) throws SQLException {
        return new AisDataLinkManagementMessageObject( ObjectState.Stored, getId( ), getRowVersion( ), getAisDevice( ), getReceivedTimestamp( ), getMessageSequenceNumber( ), getRepeat( ), getMmsi( ), getSpare( ), getOffset1( ), getReservedSlots1( ), getTimeout1( ), getIncrement1( ), getOffset2( ), getReservedSlots2( ), getTimeout2( ), getIncrement2( ), getOffset3( ), getReservedSlots3( ), getTimeout3( ), getIncrement3( ), getOffset4( ), getReservedSlots4( ), getTimeout4( ), getIncrement4( ) );
    }

}
