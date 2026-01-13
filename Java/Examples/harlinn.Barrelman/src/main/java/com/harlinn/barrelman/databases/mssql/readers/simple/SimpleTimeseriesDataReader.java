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

public abstract class SimpleTimeseriesDataReader extends SimpleTimeseriesCatalogElementDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  t.[Id], \r\n" +
            "  t.[EntityType], \r\n" +
            "  t.[RowVersion], \r\n" +
            "  t.[Catalog], \r\n" +
            "  t.[Name], \r\n" +
            "  t.[MaxRetention] \r\n" +
            "FROM [TimeseriesView] t \r\n";

    public final static String BaseViewName = "TimeseriesView";
    public final static String ViewAliasName = "t";

    public final static int MAXRETENTION_FIELD_ID = 6;

    public SimpleTimeseriesDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final TimeSpan getMaxRetention() throws SQLException {
        return getTimeSpan( MAXRETENTION_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeTimeSpan( getMaxRetention( ) );
    }

}
