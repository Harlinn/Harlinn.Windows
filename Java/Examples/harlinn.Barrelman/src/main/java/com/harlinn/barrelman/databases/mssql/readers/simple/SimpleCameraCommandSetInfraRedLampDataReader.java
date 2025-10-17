package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleCameraCommandSetInfraRedLampDataReader extends SimpleCameraCommandDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  ccsirl.[Id], \r\n" +
            "  ccsirl.[EntityType], \r\n" +
            "  ccsirl.[RowVersion], \r\n" +
            "  ccsirl.[Camera], \r\n" +
            "  ccsirl.[Timestamp], \r\n" +
            "  ccsirl.[DeviceCommandSourceType], \r\n" +
            "  ccsirl.[DeviceCommandSourceId], \r\n" +
            "  ccsirl.[Reply], \r\n" +
            "  ccsirl.[Enabled] \r\n" +
            "FROM [CameraCommandSetInfraRedLampView] ccsirl \r\n";

    public final static String BaseViewName = "CameraCommandSetInfraRedLampView";
    public final static String ViewAliasName = "ccsirl";

    public final static int ENABLED_FIELD_ID = 9;

    public SimpleCameraCommandSetInfraRedLampDataReader( ResultSet resultSet ) {
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
