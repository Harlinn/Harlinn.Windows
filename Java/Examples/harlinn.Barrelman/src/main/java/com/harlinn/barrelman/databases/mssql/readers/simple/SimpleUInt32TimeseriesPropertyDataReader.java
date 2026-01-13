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

public class SimpleUInt32TimeseriesPropertyDataReader extends SimpleTimeseriesPropertyDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  u32tp.[Id], \r\n" +
            "  u32tp.[EntityType], \r\n" +
            "  u32tp.[RowVersion], \r\n" +
            "  u32tp.[Element], \r\n" +
            "  u32tp.[Definition], \r\n" +
            "  u32tp.[Timeseries] \r\n" +
            "FROM [UInt32TimeseriesPropertyView] u32tp \r\n";

    public final static String BaseViewName = "UInt32TimeseriesPropertyView";
    public final static String ViewAliasName = "u32tp";

    public final static int TIMESERIES_FIELD_ID = 6;

    public SimpleUInt32TimeseriesPropertyDataReader( ResultSet resultSet ) {
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
    public UInt32TimeseriesPropertyObject getDataObject( ) throws SQLException {
        return new UInt32TimeseriesPropertyObject( ObjectState.Stored, getId( ), getRowVersion( ), getElement( ), getDefinition( ), getTimeseries( ) );
    }

}
