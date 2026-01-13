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

public class SimpleGNSSLongitudeTimeseriesDataReader extends SimpleDoubleTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  glots.[Id], \r\n" +
            "  glots.[EntityType], \r\n" +
            "  glots.[RowVersion], \r\n" +
            "  glots.[Catalog], \r\n" +
            "  glots.[Name], \r\n" +
            "  glots.[MaxRetention], \r\n" +
            "  glots.[GNSSDevice] \r\n" +
            "FROM [GNSSLongitudeTimeseriesView] glots \r\n";

    public final static String BaseViewName = "GNSSLongitudeTimeseriesView";
    public final static String ViewAliasName = "glots";

    public final static int GNSSDEVICE_FIELD_ID = 7;

    public SimpleGNSSLongitudeTimeseriesDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getGNSSDevice() throws SQLException {
        return getNullableGuid( GNSSDEVICE_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeNullableGuid( getGNSSDevice( ) );
    }

    @Override
    public GNSSLongitudeTimeseriesObject getDataObject( ) throws SQLException {
        return new GNSSLongitudeTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getGNSSDevice( ) );
    }

}
