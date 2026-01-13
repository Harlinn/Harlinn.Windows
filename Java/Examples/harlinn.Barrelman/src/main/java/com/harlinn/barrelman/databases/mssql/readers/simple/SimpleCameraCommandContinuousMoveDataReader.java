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

public class SimpleCameraCommandContinuousMoveDataReader extends SimpleCameraCommandDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  cccm.[Id], \r\n" +
            "  cccm.[EntityType], \r\n" +
            "  cccm.[RowVersion], \r\n" +
            "  cccm.[Camera], \r\n" +
            "  cccm.[Timestamp], \r\n" +
            "  cccm.[DeviceCommandSourceType], \r\n" +
            "  cccm.[DeviceCommandSourceId], \r\n" +
            "  cccm.[Reply], \r\n" +
            "  cccm.[Normalized], \r\n" +
            "  cccm.[PanVelocity], \r\n" +
            "  cccm.[TiltVelocity], \r\n" +
            "  cccm.[ZoomVelocity], \r\n" +
            "  cccm.[Duration] \r\n" +
            "FROM [CameraCommandContinuousMoveView] cccm \r\n";

    public final static String BaseViewName = "CameraCommandContinuousMoveView";
    public final static String ViewAliasName = "cccm";

    public final static int NORMALIZED_FIELD_ID = 9;
    public final static int PANVELOCITY_FIELD_ID = 10;
    public final static int TILTVELOCITY_FIELD_ID = 11;
    public final static int ZOOMVELOCITY_FIELD_ID = 12;
    public final static int DURATION_FIELD_ID = 13;

    public SimpleCameraCommandContinuousMoveDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final boolean getNormalized() throws SQLException {
        return getBoolean( NORMALIZED_FIELD_ID );
    }

    public final Double getPanVelocity() throws SQLException {
        return getNullableDouble( PANVELOCITY_FIELD_ID );
    }

    public final Double getTiltVelocity() throws SQLException {
        return getNullableDouble( TILTVELOCITY_FIELD_ID );
    }

    public final Double getZoomVelocity() throws SQLException {
        return getNullableDouble( ZOOMVELOCITY_FIELD_ID );
    }

    public final TimeSpan getDuration() throws SQLException {
        return getNullableTimeSpan( DURATION_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeBoolean( getNormalized( ) );
        destination.writeNullableDouble( getPanVelocity( ) );
        destination.writeNullableDouble( getTiltVelocity( ) );
        destination.writeNullableDouble( getZoomVelocity( ) );
        destination.writeNullableTimeSpan( getDuration( ) );
    }

    @Override
    public CameraCommandContinuousMoveObject getDataObject( ) throws SQLException {
        return new CameraCommandContinuousMoveObject( ObjectState.Stored, getId( ), getRowVersion( ), getCamera( ), getTimestamp( ), getDeviceCommandSourceType( ), getDeviceCommandSourceId( ), getReply( ), getNormalized( ), getPanVelocity( ), getTiltVelocity( ), getZoomVelocity( ), getDuration( ) );
    }

}
