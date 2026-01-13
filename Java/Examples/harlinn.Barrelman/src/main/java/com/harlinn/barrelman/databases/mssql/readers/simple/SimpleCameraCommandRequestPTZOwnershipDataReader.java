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

public class SimpleCameraCommandRequestPTZOwnershipDataReader extends SimpleCameraCommandDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  crqp.[Id], \r\n" +
            "  crqp.[EntityType], \r\n" +
            "  crqp.[RowVersion], \r\n" +
            "  crqp.[Camera], \r\n" +
            "  crqp.[Timestamp], \r\n" +
            "  crqp.[DeviceCommandSourceType], \r\n" +
            "  crqp.[DeviceCommandSourceId], \r\n" +
            "  crqp.[Reply] \r\n" +
            "FROM [CameraCommandRequestPTZOwnershipView] crqp \r\n";

    public final static String BaseViewName = "CameraCommandRequestPTZOwnershipView";
    public final static String ViewAliasName = "crqp";

    public SimpleCameraCommandRequestPTZOwnershipDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
    }

    @Override
    public CameraCommandRequestPTZOwnershipObject getDataObject( ) throws SQLException {
        return new CameraCommandRequestPTZOwnershipObject( ObjectState.Stored, getId( ), getRowVersion( ), getCamera( ), getTimestamp( ), getDeviceCommandSourceType( ), getDeviceCommandSourceId( ), getReply( ) );
    }

}
