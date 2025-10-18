package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleCameraCommandSetAutoFocusDataReader extends SimpleCameraCommandDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  ccsaf.[Id], \r\n" +
            "  ccsaf.[EntityType], \r\n" +
            "  ccsaf.[RowVersion], \r\n" +
            "  ccsaf.[Camera], \r\n" +
            "  ccsaf.[Timestamp], \r\n" +
            "  ccsaf.[DeviceCommandSourceType], \r\n" +
            "  ccsaf.[DeviceCommandSourceId], \r\n" +
            "  ccsaf.[Reply], \r\n" +
            "  ccsaf.[Enabled] \r\n" +
            "FROM [CameraCommandSetAutoFocusView] ccsaf \r\n";

    public final static String BaseViewName = "CameraCommandSetAutoFocusView";
    public final static String ViewAliasName = "ccsaf";

    public final static int ENABLED_FIELD_ID = 9;

    public SimpleCameraCommandSetAutoFocusDataReader( ResultSet resultSet ) {
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
    public CameraCommandSetAutoFocusObject GetDataObject( ) throws SQLException {
        return new CameraCommandSetAutoFocusObject( ObjectState.Stored, getId( ), getRowVersion( ), getCamera( ), getTimestamp( ), getDeviceCommandSourceType( ), getDeviceCommandSourceId( ), getReply( ), getEnabled( ) );
    }

}
