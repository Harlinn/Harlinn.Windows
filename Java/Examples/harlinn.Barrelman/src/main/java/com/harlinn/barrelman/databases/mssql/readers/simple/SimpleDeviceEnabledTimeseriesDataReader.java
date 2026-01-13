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

public class SimpleDeviceEnabledTimeseriesDataReader extends SimpleBooleanTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  det.[Id], \r\n" +
            "  det.[EntityType], \r\n" +
            "  det.[RowVersion], \r\n" +
            "  det.[Catalog], \r\n" +
            "  det.[Name], \r\n" +
            "  det.[MaxRetention], \r\n" +
            "  det.[Device] \r\n" +
            "FROM [DeviceEnabledTimeseriesView] det \r\n";

    public final static String BaseViewName = "DeviceEnabledTimeseriesView";
    public final static String ViewAliasName = "det";

    public final static int DEVICE_FIELD_ID = 7;

    public SimpleDeviceEnabledTimeseriesDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getDevice() throws SQLException {
        return getNullableGuid( DEVICE_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeNullableGuid( getDevice( ) );
    }

    @Override
    public DeviceEnabledTimeseriesObject getDataObject( ) throws SQLException {
        return new DeviceEnabledTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getDevice( ) );
    }

}
