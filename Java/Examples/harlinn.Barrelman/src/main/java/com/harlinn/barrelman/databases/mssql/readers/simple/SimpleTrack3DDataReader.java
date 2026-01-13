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

public class SimpleTrack3DDataReader extends SimpleTrackBaseDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  t3d.[Id], \r\n" +
            "  t3d.[EntityType], \r\n" +
            "  t3d.[RowVersion], \r\n" +
            "  t3d.[Tracker], \r\n" +
            "  t3d.[TrackNumber], \r\n" +
            "  t3d.[Timestamp] \r\n" +
            "FROM [Track3DView] t3d \r\n";

    public final static String BaseViewName = "Track3DView";
    public final static String ViewAliasName = "t3d";

    public SimpleTrack3DDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
    }

    @Override
    public Track3DObject getDataObject( ) throws SQLException {
        return new Track3DObject( ObjectState.Stored, getId( ), getRowVersion( ), getTracker( ), getTrackNumber( ), getTimestamp( ) );
    }

}
