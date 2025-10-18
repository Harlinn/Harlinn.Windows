package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleCameraCommandRelativeMoveDataReader extends SimpleCameraCommandDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  ccrm.[Id], \r\n" +
            "  ccrm.[EntityType], \r\n" +
            "  ccrm.[RowVersion], \r\n" +
            "  ccrm.[Camera], \r\n" +
            "  ccrm.[Timestamp], \r\n" +
            "  ccrm.[DeviceCommandSourceType], \r\n" +
            "  ccrm.[DeviceCommandSourceId], \r\n" +
            "  ccrm.[Reply], \r\n" +
            "  ccrm.[Normalized], \r\n" +
            "  ccrm.[PanAngle], \r\n" +
            "  ccrm.[TiltAngle], \r\n" +
            "  ccrm.[FocalLength], \r\n" +
            "  ccrm.[PanSpeed], \r\n" +
            "  ccrm.[TiltSpeed], \r\n" +
            "  ccrm.[ZoomSpeed] \r\n" +
            "FROM [CameraCommandRelativeMoveView] ccrm \r\n";

    public final static String BaseViewName = "CameraCommandRelativeMoveView";
    public final static String ViewAliasName = "ccrm";

    public final static int NORMALIZED_FIELD_ID = 9;
    public final static int PANANGLE_FIELD_ID = 10;
    public final static int TILTANGLE_FIELD_ID = 11;
    public final static int FOCALLENGTH_FIELD_ID = 12;
    public final static int PANSPEED_FIELD_ID = 13;
    public final static int TILTSPEED_FIELD_ID = 14;
    public final static int ZOOMSPEED_FIELD_ID = 15;

    public SimpleCameraCommandRelativeMoveDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final boolean getNormalized() throws SQLException {
        return getBoolean( NORMALIZED_FIELD_ID );
    }

    public final Double getPanAngle() throws SQLException {
        return getNullableDouble( PANANGLE_FIELD_ID );
    }

    public final Double getTiltAngle() throws SQLException {
        return getNullableDouble( TILTANGLE_FIELD_ID );
    }

    public final Double getFocalLength() throws SQLException {
        return getNullableDouble( FOCALLENGTH_FIELD_ID );
    }

    public final Double getPanSpeed() throws SQLException {
        return getNullableDouble( PANSPEED_FIELD_ID );
    }

    public final Double getTiltSpeed() throws SQLException {
        return getNullableDouble( TILTSPEED_FIELD_ID );
    }

    public final Double getZoomSpeed() throws SQLException {
        return getNullableDouble( ZOOMSPEED_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeBoolean( getNormalized( ) );
        destination.writeNullableDouble( getPanAngle( ) );
        destination.writeNullableDouble( getTiltAngle( ) );
        destination.writeNullableDouble( getFocalLength( ) );
        destination.writeNullableDouble( getPanSpeed( ) );
        destination.writeNullableDouble( getTiltSpeed( ) );
        destination.writeNullableDouble( getZoomSpeed( ) );
    }

    @Override
    public CameraCommandRelativeMoveObject GetDataObject( ) throws SQLException {
        return new CameraCommandRelativeMoveObject( ObjectState.Stored, getId( ), getRowVersion( ), getCamera( ), getTimestamp( ), getDeviceCommandSourceType( ), getDeviceCommandSourceId( ), getReply( ), getNormalized( ), getPanAngle( ), getTiltAngle( ), getFocalLength( ), getPanSpeed( ), getTiltSpeed( ), getZoomSpeed( ) );
    }

}
