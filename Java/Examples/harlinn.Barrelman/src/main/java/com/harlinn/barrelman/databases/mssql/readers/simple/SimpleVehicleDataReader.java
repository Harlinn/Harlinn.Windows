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

public class SimpleVehicleDataReader extends SimpleTrackableItemDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  v.[Id], \r\n" +
            "  v.[EntityType], \r\n" +
            "  v.[RowVersion], \r\n" +
            "  v.[Name], \r\n" +
            "  v.[Type] \r\n" +
            "FROM [VehicleView] v \r\n";

    public final static String BaseViewName = "VehicleView";
    public final static String ViewAliasName = "v";

    public final static int NAME_FIELD_ID = 4;
    public final static int TYPE_FIELD_ID = 5;

    public SimpleVehicleDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final String getName() throws SQLException {
        return getString( NAME_FIELD_ID );
    }

    public final Guid getTypeField() throws SQLException {
        return getNullableGuid( TYPE_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeStringUtf8( getName( ) );
        destination.writeNullableGuid( getTypeField( ) );
    }

    @Override
    public VehicleObject getDataObject( ) throws SQLException {
        return new VehicleObject( ObjectState.Stored, getId( ), getRowVersion( ), getName( ), getTypeField( ) );
    }

}
