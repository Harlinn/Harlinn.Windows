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

public class SimpleInt64TimeseriesPropertyDataReader extends SimpleTimeseriesPropertyDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  i64tp.[Id], \r\n" +
            "  i64tp.[EntityType], \r\n" +
            "  i64tp.[RowVersion], \r\n" +
            "  i64tp.[Element], \r\n" +
            "  i64tp.[Definition], \r\n" +
            "  i64tp.[Timeseries] \r\n" +
            "FROM [Int64TimeseriesPropertyView] i64tp \r\n";

    public final static String BaseViewName = "Int64TimeseriesPropertyView";
    public final static String ViewAliasName = "i64tp";

    public final static int TIMESERIES_FIELD_ID = 6;

    public SimpleInt64TimeseriesPropertyDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getTimeseries() throws SQLException {
        return getNullableGuid( TIMESERIES_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeNullableGuid( getTimeseries( ) );
    }

    @Override
    public Int64TimeseriesPropertyObject getDataObject( ) throws SQLException {
        return new Int64TimeseriesPropertyObject( ObjectState.Stored, getId( ), getRowVersion( ), getElement( ), getDefinition( ), getTimeseries( ) );
    }

}
