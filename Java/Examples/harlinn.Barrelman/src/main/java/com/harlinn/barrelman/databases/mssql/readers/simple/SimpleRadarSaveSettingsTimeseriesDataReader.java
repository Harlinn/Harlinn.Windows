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

public class SimpleRadarSaveSettingsTimeseriesDataReader extends SimpleBooleanTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  rsst.[Id], \r\n" +
            "  rsst.[EntityType], \r\n" +
            "  rsst.[RowVersion], \r\n" +
            "  rsst.[Catalog], \r\n" +
            "  rsst.[Name], \r\n" +
            "  rsst.[MaxRetention], \r\n" +
            "  rsst.[Radar] \r\n" +
            "FROM [RadarSaveSettingsTimeseriesView] rsst \r\n";

    public final static String BaseViewName = "RadarSaveSettingsTimeseriesView";
    public final static String ViewAliasName = "rsst";

    public final static int RADAR_FIELD_ID = 7;

    public SimpleRadarSaveSettingsTimeseriesDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getRadar() throws SQLException {
        return getNullableGuid( RADAR_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeNullableGuid( getRadar( ) );
    }

    @Override
    public RadarSaveSettingsTimeseriesObject getDataObject( ) throws SQLException {
        return new RadarSaveSettingsTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getRadar( ) );
    }

}
