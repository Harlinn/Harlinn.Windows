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

public class SimpleCameraCommandAdjustPanTiltZoomDataReader extends SimpleCameraCommandDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  ccaptz.[Id], \r\n" +
            "  ccaptz.[EntityType], \r\n" +
            "  ccaptz.[RowVersion], \r\n" +
            "  ccaptz.[Camera], \r\n" +
            "  ccaptz.[Timestamp], \r\n" +
            "  ccaptz.[DeviceCommandSourceType], \r\n" +
            "  ccaptz.[DeviceCommandSourceId], \r\n" +
            "  ccaptz.[Reply], \r\n" +
            "  ccaptz.[X], \r\n" +
            "  ccaptz.[Y], \r\n" +
            "  ccaptz.[Z] \r\n" +
            "FROM [CameraCommandAdjustPanTiltZoomView] ccaptz \r\n";

    public final static String BaseViewName = "CameraCommandAdjustPanTiltZoomView";
    public final static String ViewAliasName = "ccaptz";

    public final static int X_FIELD_ID = 9;
    public final static int Y_FIELD_ID = 10;
    public final static int Z_FIELD_ID = 11;

    public SimpleCameraCommandAdjustPanTiltZoomDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Double getX() throws SQLException {
        return getNullableDouble( X_FIELD_ID );
    }

    public final Double getY() throws SQLException {
        return getNullableDouble( Y_FIELD_ID );
    }

    public final Double getZ() throws SQLException {
        return getNullableDouble( Z_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeNullableDouble( getX( ) );
        destination.writeNullableDouble( getY( ) );
        destination.writeNullableDouble( getZ( ) );
    }

    @Override
    public CameraCommandAdjustPanTiltZoomObject getDataObject( ) throws SQLException {
        return new CameraCommandAdjustPanTiltZoomObject( ObjectState.Stored, getId( ), getRowVersion( ), getCamera( ), getTimestamp( ), getDeviceCommandSourceType( ), getDeviceCommandSourceId( ), getReply( ), getX( ), getY( ), getZ( ) );
    }

}
