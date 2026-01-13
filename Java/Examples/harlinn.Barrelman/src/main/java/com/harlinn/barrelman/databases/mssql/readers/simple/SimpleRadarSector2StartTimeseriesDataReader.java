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

public class SimpleRadarSector2StartTimeseriesDataReader extends SimpleInt32TimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  rs2st.[Id], \r\n" +
            "  rs2st.[EntityType], \r\n" +
            "  rs2st.[RowVersion], \r\n" +
            "  rs2st.[Catalog], \r\n" +
            "  rs2st.[Name], \r\n" +
            "  rs2st.[MaxRetention], \r\n" +
            "  rs2st.[Radar] \r\n" +
            "FROM [RadarSector2StartTimeseriesView] rs2st \r\n";

    public final static String BaseViewName = "RadarSector2StartTimeseriesView";
    public final static String ViewAliasName = "rs2st";

    public final static int RADAR_FIELD_ID = 7;

    public SimpleRadarSector2StartTimeseriesDataReader( ResultSet resultSet ) {
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
    public RadarSector2StartTimeseriesObject getDataObject( ) throws SQLException {
        return new RadarSector2StartTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getRadar( ) );
    }

}
