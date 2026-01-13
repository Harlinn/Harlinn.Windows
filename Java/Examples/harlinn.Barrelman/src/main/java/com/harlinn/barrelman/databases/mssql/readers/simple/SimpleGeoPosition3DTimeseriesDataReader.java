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

public class SimpleGeoPosition3DTimeseriesDataReader extends SimpleTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  gp3d.[Id], \r\n" +
            "  gp3d.[EntityType], \r\n" +
            "  gp3d.[RowVersion], \r\n" +
            "  gp3d.[Catalog], \r\n" +
            "  gp3d.[Name], \r\n" +
            "  gp3d.[MaxRetention] \r\n" +
            "FROM [GeoPosition3DTimeseriesView] gp3d \r\n";

    public final static String BaseViewName = "GeoPosition3DTimeseriesView";
    public final static String ViewAliasName = "gp3d";

    public SimpleGeoPosition3DTimeseriesDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
    }

    @Override
    public GeoPosition3DTimeseriesObject getDataObject( ) throws SQLException {
        return new GeoPosition3DTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ) );
    }

}
