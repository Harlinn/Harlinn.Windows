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

public class SimpleAisUtcAndDateResponseMessageDataReader extends SimpleAisMessageDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  auadrm.[Id], \r\n" +
            "  auadrm.[EntityType], \r\n" +
            "  auadrm.[RowVersion], \r\n" +
            "  auadrm.[AisDevice], \r\n" +
            "  auadrm.[ReceivedTimestamp], \r\n" +
            "  auadrm.[MessageSequenceNumber], \r\n" +
            "  auadrm.[Repeat], \r\n" +
            "  auadrm.[Mmsi], \r\n" +
            "  auadrm.[Datetime], \r\n" +
            "  auadrm.[PositionAccuracy], \r\n" +
            "  auadrm.[Longitude], \r\n" +
            "  auadrm.[Latitude], \r\n" +
            "  auadrm.[PositionFixType], \r\n" +
            "  auadrm.[Spare], \r\n" +
            "  auadrm.[Raim], \r\n" +
            "  auadrm.[RadioStatus] \r\n" +
            "FROM [AisUtcAndDateResponseMessageView] auadrm \r\n";

    public final static String BaseViewName = "AisUtcAndDateResponseMessageView";
    public final static String ViewAliasName = "auadrm";

    public final static int DATETIME_FIELD_ID = 9;
    public final static int POSITIONACCURACY_FIELD_ID = 10;
    public final static int LONGITUDE_FIELD_ID = 11;
    public final static int LATITUDE_FIELD_ID = 12;
    public final static int POSITIONFIXTYPE_FIELD_ID = 13;
    public final static int SPARE_FIELD_ID = 14;
    public final static int RAIM_FIELD_ID = 15;
    public final static int RADIOSTATUS_FIELD_ID = 16;

    public SimpleAisUtcAndDateResponseMessageDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final DateTime getDatetime() throws SQLException {
        return getDateTimeFromLong( DATETIME_FIELD_ID );
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

    public final int getPositionFixType() throws SQLException {
        return getInt32( POSITIONFIXTYPE_FIELD_ID );
    }

    public final int getSpare() throws SQLException {
        return getInt32( SPARE_FIELD_ID );
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
        destination.writeDateTime( getDatetime( ) );
        destination.writeInt32( getPositionAccuracy( ) );
        destination.writeDouble( getLongitude( ) );
        destination.writeDouble( getLatitude( ) );
        destination.writeInt32( getPositionFixType( ) );
        destination.writeInt32( getSpare( ) );
        destination.writeInt32( getRaim( ) );
        destination.writeInt32( getRadioStatus( ) );
    }

    @Override
    public AisUtcAndDateResponseMessageObject getDataObject( ) throws SQLException {
        return new AisUtcAndDateResponseMessageObject( ObjectState.Stored, getId( ), getRowVersion( ), getAisDevice( ), getReceivedTimestamp( ), getMessageSequenceNumber( ), getRepeat( ), getMmsi( ), getDatetime( ), getPositionAccuracy( ), getLongitude( ), getLatitude( ), getPositionFixType( ), getSpare( ), getRaim( ), getRadioStatus( ) );
    }

}
