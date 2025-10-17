package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleCameraCommandAdjustPanTiltZoomDataReader extends SimpleCameraCommandDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  ccaptz.[Id], \r\n" +
            "  ccaptz.[EntityType], \r\n" +
            "  ccaptz.[RowVersion], \r\n" +
            "  ccaptz.[Camera], \r\n" +
            "  ccaptz.[Timestamp], \r\n" +
            "  ccaptz.[DeviceCommandSourceType], \r\n" +
            "  ccaptz.[DeviceCommandSourceId], \r\n" +
            "  ccaptz.[Reply], \r\n" +
            "  ccaptz.[X], \r\n" +
            "  ccaptz.[Y], \r\n" +
            "  ccaptz.[Z] \r\n" +
            "FROM [CameraCommandAdjustPanTiltZoomView] ccaptz \r\n";

    public final static String BaseViewName = "CameraCommandAdjustPanTiltZoomView";
    public final static String ViewAliasName = "ccaptz";

    public final static int X_FIELD_ID = 9;
    public final static int Y_FIELD_ID = 10;
    public final static int Z_FIELD_ID = 11;

    public SimpleCameraCommandAdjustPanTiltZoomDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Double getX() throws SQLException {
        return getNullableDouble( X_FIELD_ID );
    }

    public final Double getY() throws SQLException {
        return getNullableDouble( Y_FIELD_ID );
    }

    public final Double getZ() throws SQLException {
        return getNullableDouble( Z_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeNullableDouble( getX( ) );
        destination.writeNullableDouble( getY( ) );
        destination.writeNullableDouble( getZ( ) );
    }

}
