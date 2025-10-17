package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleCameraCommandReleasePTZOwnershipDataReader extends SimpleCameraCommandDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  crlp.[Id], \r\n" +
            "  crlp.[EntityType], \r\n" +
            "  crlp.[RowVersion], \r\n" +
            "  crlp.[Camera], \r\n" +
            "  crlp.[Timestamp], \r\n" +
            "  crlp.[DeviceCommandSourceType], \r\n" +
            "  crlp.[DeviceCommandSourceId], \r\n" +
            "  crlp.[Reply] \r\n" +
            "FROM [CameraCommandReleasePTZOwnershipView] crlp \r\n";

    public final static String BaseViewName = "CameraCommandReleasePTZOwnershipView";
    public final static String ViewAliasName = "crlp";

    public SimpleCameraCommandReleasePTZOwnershipDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
    }

}
