package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleCameraCommandSetWiperDataReader extends SimpleCameraCommandDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  cwi.[Id], \r\n" +
            "  cwi.[EntityType], \r\n" +
            "  cwi.[RowVersion], \r\n" +
            "  cwi.[Camera], \r\n" +
            "  cwi.[Timestamp], \r\n" +
            "  cwi.[DeviceCommandSourceType], \r\n" +
            "  cwi.[DeviceCommandSourceId], \r\n" +
            "  cwi.[Reply], \r\n" +
            "  cwi.[Enabled] \r\n" +
            "FROM [CameraCommandSetWiperView] cwi \r\n";

    public final static String BaseViewName = "CameraCommandSetWiperView";
    public final static String ViewAliasName = "cwi";

    public final static int ENABLED_FIELD_ID = 9;

    public SimpleCameraCommandSetWiperDataReader( ResultSet resultSet ) {
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
    public CameraCommandSetWiperObject getDataObject( ) throws SQLException {
        return new CameraCommandSetWiperObject( ObjectState.Stored, getId( ), getRowVersion( ), getCamera( ), getTimestamp( ), getDeviceCommandSourceType( ), getDeviceCommandSourceId( ), getReply( ), getEnabled( ) );
    }

}
