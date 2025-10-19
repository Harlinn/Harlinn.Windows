package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleCameraCommandSetBlackAndWhiteDataReader extends SimpleCameraCommandDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  ccsbaw.[Id], \r\n" +
            "  ccsbaw.[EntityType], \r\n" +
            "  ccsbaw.[RowVersion], \r\n" +
            "  ccsbaw.[Camera], \r\n" +
            "  ccsbaw.[Timestamp], \r\n" +
            "  ccsbaw.[DeviceCommandSourceType], \r\n" +
            "  ccsbaw.[DeviceCommandSourceId], \r\n" +
            "  ccsbaw.[Reply], \r\n" +
            "  ccsbaw.[Enabled] \r\n" +
            "FROM [CameraCommandSetBlackAndWhiteView] ccsbaw \r\n";

    public final static String BaseViewName = "CameraCommandSetBlackAndWhiteView";
    public final static String ViewAliasName = "ccsbaw";

    public final static int ENABLED_FIELD_ID = 9;

    public SimpleCameraCommandSetBlackAndWhiteDataReader( ResultSet resultSet ) {
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

    @Override
    public CameraCommandSetBlackAndWhiteObject getDataObject( ) throws SQLException {
        return new CameraCommandSetBlackAndWhiteObject( ObjectState.Stored, getId( ), getRowVersion( ), getCamera( ), getTimestamp( ), getDeviceCommandSourceType( ), getDeviceCommandSourceId( ), getReply( ), getEnabled( ) );
    }

}
