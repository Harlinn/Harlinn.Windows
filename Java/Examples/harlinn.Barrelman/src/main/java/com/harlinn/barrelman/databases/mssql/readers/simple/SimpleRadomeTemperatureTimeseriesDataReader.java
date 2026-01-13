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

public class SimpleRadomeTemperatureTimeseriesDataReader extends SimpleDoubleTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  rtets.[Id], \r\n" +
            "  rtets.[EntityType], \r\n" +
            "  rtets.[RowVersion], \r\n" +
            "  rtets.[Catalog], \r\n" +
            "  rtets.[Name], \r\n" +
            "  rtets.[MaxRetention], \r\n" +
            "  rtets.[Radome] \r\n" +
            "FROM [RadomeTemperatureTimeseriesView] rtets \r\n";

    public final static String BaseViewName = "RadomeTemperatureTimeseriesView";
    public final static String ViewAliasName = "rtets";

    public final static int RADOME_FIELD_ID = 7;

    public SimpleRadomeTemperatureTimeseriesDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getRadome() throws SQLException {
        return getNullableGuid( RADOME_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeNullableGuid( getRadome( ) );
    }

    @Override
    public RadomeTemperatureTimeseriesObject getDataObject( ) throws SQLException {
        return new RadomeTemperatureTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getRadome( ) );
    }

}
