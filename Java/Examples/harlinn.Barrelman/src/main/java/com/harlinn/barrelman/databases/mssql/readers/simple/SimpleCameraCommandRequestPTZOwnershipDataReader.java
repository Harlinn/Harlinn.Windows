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

}
