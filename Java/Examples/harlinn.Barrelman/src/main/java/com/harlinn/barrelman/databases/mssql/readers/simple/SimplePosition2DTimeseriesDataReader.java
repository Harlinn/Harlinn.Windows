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

public class SimplePosition2DTimeseriesDataReader extends SimpleTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  p2d.[Id], \r\n" +
            "  p2d.[EntityType], \r\n" +
            "  p2d.[RowVersion], \r\n" +
            "  p2d.[Catalog], \r\n" +
            "  p2d.[Name], \r\n" +
            "  p2d.[MaxRetention] \r\n" +
            "FROM [Position2DTimeseriesView] p2d \r\n";

    public final static String BaseViewName = "Position2DTimeseriesView";
    public final static String ViewAliasName = "p2d";

    public SimplePosition2DTimeseriesDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
    }

    @Override
    public Position2DTimeseriesObject getDataObject( ) throws SQLException {
        return new Position2DTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ) );
    }

}
