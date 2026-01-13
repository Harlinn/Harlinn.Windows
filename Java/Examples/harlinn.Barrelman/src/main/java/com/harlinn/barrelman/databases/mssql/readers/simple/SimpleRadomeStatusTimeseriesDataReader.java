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

public class SimpleRadomeStatusTimeseriesDataReader extends SimpleUInt32TimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  rst.[Id], \r\n" +
            "  rst.[EntityType], \r\n" +
            "  rst.[RowVersion], \r\n" +
            "  rst.[Catalog], \r\n" +
            "  rst.[Name], \r\n" +
            "  rst.[MaxRetention], \r\n" +
            "  rst.[Radome] \r\n" +
            "FROM [RadomeStatusTimeseriesView] rst \r\n";

    public final static String BaseViewName = "RadomeStatusTimeseriesView";
    public final static String ViewAliasName = "rst";

    public final static int RADOME_FIELD_ID = 7;

    public SimpleRadomeStatusTimeseriesDataReader( ResultSet resultSet ) {
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
    public RadomeStatusTimeseriesObject getDataObject( ) throws SQLException {
        return new RadomeStatusTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getRadome( ) );
    }

}
