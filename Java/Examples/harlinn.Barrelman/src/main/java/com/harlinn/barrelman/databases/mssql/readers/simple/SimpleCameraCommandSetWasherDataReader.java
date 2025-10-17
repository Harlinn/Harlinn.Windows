package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleCameraCommandSetWasherDataReader extends SimpleCameraCommandDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  cwa.[Id], \r\n" +
            "  cwa.[EntityType], \r\n" +
            "  cwa.[RowVersion], \r\n" +
            "  cwa.[Camera], \r\n" +
            "  cwa.[Timestamp], \r\n" +
            "  cwa.[DeviceCommandSourceType], \r\n" +
            "  cwa.[DeviceCommandSourceId], \r\n" +
            "  cwa.[Reply], \r\n" +
            "  cwa.[Enabled] \r\n" +
            "FROM [CameraCommandSetWasherView] cwa \r\n";

    public final static String BaseViewName = "CameraCommandSetWasherView";
    public final static String ViewAliasName = "cwa";

    public final static int ENABLED_FIELD_ID = 9;

    public SimpleCameraCommandSetWasherDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final boolean getEnabled() throws SQLException {
        return getBoolean( ENABLED_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeBoolean( getEnabled( ) );
    }

}
