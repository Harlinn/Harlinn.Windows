package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleCameraCommandStopDataReader extends SimpleCameraCommandDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  ccs.[Id], \r\n" +
            "  ccs.[EntityType], \r\n" +
            "  ccs.[RowVersion], \r\n" +
            "  ccs.[Camera], \r\n" +
            "  ccs.[Timestamp], \r\n" +
            "  ccs.[DeviceCommandSourceType], \r\n" +
            "  ccs.[DeviceCommandSourceId], \r\n" +
            "  ccs.[Reply], \r\n" +
            "  ccs.[PanTilt], \r\n" +
            "  ccs.[Zoom] \r\n" +
            "FROM [CameraCommandStopView] ccs \r\n";

    public final static String BaseViewName = "CameraCommandStopView";
    public final static String ViewAliasName = "ccs";

    public final static int PANTILT_FIELD_ID = 9;
    public final static int ZOOM_FIELD_ID = 10;

    public SimpleCameraCommandStopDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final boolean getPanTilt() throws SQLException {
        return getBoolean( PANTILT_FIELD_ID );
    }

    public final boolean getZoom() throws SQLException {
        return getBoolean( ZOOM_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeBoolean( getPanTilt( ) );
        destination.writeBoolean( getZoom( ) );
    }

}
