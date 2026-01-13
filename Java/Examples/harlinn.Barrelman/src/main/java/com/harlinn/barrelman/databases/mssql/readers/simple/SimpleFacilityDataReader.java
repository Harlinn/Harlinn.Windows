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

public class SimpleFacilityDataReader extends SimpleItemDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  f.[Id], \r\n" +
            "  f.[EntityType], \r\n" +
            "  f.[RowVersion], \r\n" +
            "  f.[Name], \r\n" +
            "  f.[Type], \r\n" +
            "  f.[Longitude], \r\n" +
            "  f.[Latitude], \r\n" +
            "  f.[Altitude] \r\n" +
            "FROM [FacilityView] f \r\n";

    public final static String BaseViewName = "FacilityView";
    public final static String ViewAliasName = "f";

    public final static int NAME_FIELD_ID = 4;
    public final static int TYPE_FIELD_ID = 5;
    public final static int LONGITUDE_FIELD_ID = 6;
    public final static int LATITUDE_FIELD_ID = 7;
    public final static int ALTITUDE_FIELD_ID = 8;

    public SimpleFacilityDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final String getName() throws SQLException {
        return getString( NAME_FIELD_ID );
    }

    public final Guid getTypeField() throws SQLException {
        return getNullableGuid( TYPE_FIELD_ID );
    }

    public final double getLongitude() throws SQLException {
        return getDouble( LONGITUDE_FIELD_ID );
    }

    public final double getLatitude() throws SQLException {
        return getDouble( LATITUDE_FIELD_ID );
    }

    public final double getAltitude() throws SQLException {
        return getDouble( ALTITUDE_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeStringUtf8( getName( ) );
        destination.writeNullableGuid( getTypeField( ) );
        destination.writeDouble( getLongitude( ) );
        destination.writeDouble( getLatitude( ) );
        destination.writeDouble( getAltitude( ) );
    }

    @Override
    public FacilityObject getDataObject( ) throws SQLException {
        return new FacilityObject( ObjectState.Stored, getId( ), getRowVersion( ), getName( ), getTypeField( ), getLongitude( ), getLatitude( ), getAltitude( ) );
    }

}
