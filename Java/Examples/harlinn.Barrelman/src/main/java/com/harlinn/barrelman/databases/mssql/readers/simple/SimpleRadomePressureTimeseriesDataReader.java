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

public class SimpleRadomePressureTimeseriesDataReader extends SimpleDoubleTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  rpt.[Id], \r\n" +
            "  rpt.[EntityType], \r\n" +
            "  rpt.[RowVersion], \r\n" +
            "  rpt.[Catalog], \r\n" +
            "  rpt.[Name], \r\n" +
            "  rpt.[MaxRetention], \r\n" +
            "  rpt.[Radome] \r\n" +
            "FROM [RadomePressureTimeseriesView] rpt \r\n";

    public final static String BaseViewName = "RadomePressureTimeseriesView";
    public final static String ViewAliasName = "rpt";

    public final static int RADOME_FIELD_ID = 7;

    public SimpleRadomePressureTimeseriesDataReader( ResultSet resultSet ) {
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
    public RadomePressureTimeseriesObject getDataObject( ) throws SQLException {
        return new RadomePressureTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getRadome( ) );
    }

}
