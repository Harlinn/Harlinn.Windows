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

public class SimpleAisAidToNavigationDataReader extends SimpleTrackableItemDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  aatn.[Id], \r\n" +
            "  aatn.[EntityType], \r\n" +
            "  aatn.[RowVersion], \r\n" +
            "  aatn.[Name], \r\n" +
            "  aatn.[MMSI], \r\n" +
            "  aatn.[NavigationalAidType], \r\n" +
            "  aatn.[Position], \r\n" +
            "  aatn.[IsVirtual], \r\n" +
            "  aatn.[ToBow], \r\n" +
            "  aatn.[ToStern], \r\n" +
            "  aatn.[ToPort], \r\n" +
            "  aatn.[ToStarboard], \r\n" +
            "  aatn.[OffPositionTimeseries] \r\n" +
            "FROM [AisAidToNavigationView] aatn \r\n";

    public final static String BaseViewName = "AisAidToNavigationView";
    public final static String ViewAliasName = "aatn";

    public final static int NAME_FIELD_ID = 4;
    public final static int MMSI_FIELD_ID = 5;
    public final static int NAVIGATIONALAIDTYPE_FIELD_ID = 6;
    public final static int POSITION_FIELD_ID = 7;
    public final static int ISVIRTUAL_FIELD_ID = 8;
    public final static int TOBOW_FIELD_ID = 9;
    public final static int TOSTERN_FIELD_ID = 10;
    public final static int TOPORT_FIELD_ID = 11;
    public final static int TOSTARBOARD_FIELD_ID = 12;
    public final static int OFFPOSITIONTIMESERIES_FIELD_ID = 13;

    public SimpleAisAidToNavigationDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final String getName() throws SQLException {
        return getString( NAME_FIELD_ID );
    }

    public final Guid getMMSI() throws SQLException {
        return getNullableGuid( MMSI_FIELD_ID );
    }

    public final int getNavigationalAidType() throws SQLException {
        return getInt32( NAVIGATIONALAIDTYPE_FIELD_ID );
    }

    public final Guid getPosition() throws SQLException {
        return getNullableGuid( POSITION_FIELD_ID );
    }

    public final boolean getIsVirtual() throws SQLException {
        return getBoolean( ISVIRTUAL_FIELD_ID );
    }

    public final int getToBow() throws SQLException {
        return getInt32( TOBOW_FIELD_ID );
    }

    public final int getToStern() throws SQLException {
        return getInt32( TOSTERN_FIELD_ID );
    }

    public final int getToPort() throws SQLException {
        return getInt32( TOPORT_FIELD_ID );
    }

    public final int getToStarboard() throws SQLException {
        return getInt32( TOSTARBOARD_FIELD_ID );
    }

    public final Guid getOffPositionTimeseries() throws SQLException {
        return getNullableGuid( OFFPOSITIONTIMESERIES_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeStringUtf8( getName( ) );
        destination.writeNullableGuid( getMMSI( ) );
        destination.writeInt32( getNavigationalAidType( ) );
        destination.writeNullableGuid( getPosition( ) );
        destination.writeBoolean( getIsVirtual( ) );
        destination.writeInt32( getToBow( ) );
        destination.writeInt32( getToStern( ) );
        destination.writeInt32( getToPort( ) );
        destination.writeInt32( getToStarboard( ) );
        destination.writeNullableGuid( getOffPositionTimeseries( ) );
    }

    @Override
    public AisAidToNavigationObject getDataObject( ) throws SQLException {
        return new AisAidToNavigationObject( ObjectState.Stored, getId( ), getRowVersion( ), getName( ), getMMSI( ), getNavigationalAidType( ), getPosition( ), getIsVirtual( ), getToBow( ), getToStern( ), getToPort( ), getToStarboard( ), getOffPositionTimeseries( ) );
    }

}
