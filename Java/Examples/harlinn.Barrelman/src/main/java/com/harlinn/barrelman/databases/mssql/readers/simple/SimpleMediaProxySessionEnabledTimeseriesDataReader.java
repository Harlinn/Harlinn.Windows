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

public class SimpleMediaProxySessionEnabledTimeseriesDataReader extends SimpleBooleanTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  mpset.[Id], \r\n" +
            "  mpset.[EntityType], \r\n" +
            "  mpset.[RowVersion], \r\n" +
            "  mpset.[Catalog], \r\n" +
            "  mpset.[Name], \r\n" +
            "  mpset.[MaxRetention], \r\n" +
            "  mpset.[ProxySession] \r\n" +
            "FROM [MediaProxySessionEnabledTimeseriesView] mpset \r\n";

    public final static String BaseViewName = "MediaProxySessionEnabledTimeseriesView";
    public final static String ViewAliasName = "mpset";

    public final static int PROXYSESSION_FIELD_ID = 7;

    public SimpleMediaProxySessionEnabledTimeseriesDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getProxySession() throws SQLException {
        return getNullableGuid( PROXYSESSION_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeNullableGuid( getProxySession( ) );
    }

    @Override
    public MediaProxySessionEnabledTimeseriesObject getDataObject( ) throws SQLException {
        return new MediaProxySessionEnabledTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getProxySession( ) );
    }

}
