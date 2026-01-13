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

public class SimpleViewLatitudeTimeseriesDataReader extends SimpleDoubleTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  vlats.[Id], \r\n" +
            "  vlats.[EntityType], \r\n" +
            "  vlats.[RowVersion], \r\n" +
            "  vlats.[Catalog], \r\n" +
            "  vlats.[Name], \r\n" +
            "  vlats.[MaxRetention], \r\n" +
            "  vlats.[View] \r\n" +
            "FROM [ViewLatitudeTimeseriesView] vlats \r\n";

    public final static String BaseViewName = "ViewLatitudeTimeseriesView";
    public final static String ViewAliasName = "vlats";

    public final static int VIEW_FIELD_ID = 7;

    public SimpleViewLatitudeTimeseriesDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getView() throws SQLException {
        return getNullableGuid( VIEW_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeNullableGuid( getView( ) );
    }

    @Override
    public ViewLatitudeTimeseriesObject getDataObject( ) throws SQLException {
        return new ViewLatitudeTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getView( ) );
    }

}
