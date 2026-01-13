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

public class SimpleRadarCommandGetStatusDataReader extends SimpleRadarCommandDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  rcgs.[Id], \r\n" +
            "  rcgs.[EntityType], \r\n" +
            "  rcgs.[RowVersion], \r\n" +
            "  rcgs.[Radar], \r\n" +
            "  rcgs.[Timestamp], \r\n" +
            "  rcgs.[DeviceCommandSourceType], \r\n" +
            "  rcgs.[DeviceCommandSourceId], \r\n" +
            "  rcgs.[Reply] \r\n" +
            "FROM [RadarCommandGetStatusView] rcgs \r\n";

    public final static String BaseViewName = "RadarCommandGetStatusView";
    public final static String ViewAliasName = "rcgs";

    public SimpleRadarCommandGetStatusDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
    }

    @Override
    public RadarCommandGetStatusObject getDataObject( ) throws SQLException {
        return new RadarCommandGetStatusObject( ObjectState.Stored, getId( ), getRowVersion( ), getRadar( ), getTimestamp( ), getDeviceCommandSourceType( ), getDeviceCommandSourceId( ), getReply( ) );
    }

}
