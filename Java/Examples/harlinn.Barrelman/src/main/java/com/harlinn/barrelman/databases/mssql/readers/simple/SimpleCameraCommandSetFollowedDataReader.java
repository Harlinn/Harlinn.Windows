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

public class SimpleCameraCommandSetFollowedDataReader extends SimpleCameraCommandDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  ccsf.[Id], \r\n" +
            "  ccsf.[EntityType], \r\n" +
            "  ccsf.[RowVersion], \r\n" +
            "  ccsf.[Camera], \r\n" +
            "  ccsf.[Timestamp], \r\n" +
            "  ccsf.[DeviceCommandSourceType], \r\n" +
            "  ccsf.[DeviceCommandSourceId], \r\n" +
            "  ccsf.[Reply], \r\n" +
            "  ccsf.[TrackId], \r\n" +
            "  ccsf.[Reason] \r\n" +
            "FROM [CameraCommandSetFollowedView] ccsf \r\n";

    public final static String BaseViewName = "CameraCommandSetFollowedView";
    public final static String ViewAliasName = "ccsf";

    public final static int TRACKID_FIELD_ID = 9;
    public final static int REASON_FIELD_ID = 10;

    public SimpleCameraCommandSetFollowedDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getTrackId() throws SQLException {
        return getGuid( TRACKID_FIELD_ID );
    }

    public final int getReason() throws SQLException {
        return getInt32( REASON_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeGuid( getTrackId( ) );
        destination.writeInt32( getReason( ) );
    }

    @Override
    public CameraCommandSetFollowedObject getDataObject( ) throws SQLException {
        return new CameraCommandSetFollowedObject( ObjectState.Stored, getId( ), getRowVersion( ), getCamera( ), getTimestamp( ), getDeviceCommandSourceType( ), getDeviceCommandSourceId( ), getReply( ), getTrackId( ), getReason( ) );
    }

}
