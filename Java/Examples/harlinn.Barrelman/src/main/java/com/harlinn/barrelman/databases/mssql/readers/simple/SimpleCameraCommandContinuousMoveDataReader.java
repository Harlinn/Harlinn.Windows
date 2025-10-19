package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleCameraCommandContinuousMoveDataReader extends SimpleCameraCommandDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  cccm.[Id], \r\n" +
            "  cccm.[EntityType], \r\n" +
            "  cccm.[RowVersion], \r\n" +
            "  cccm.[Camera], \r\n" +
            "  cccm.[Timestamp], \r\n" +
            "  cccm.[DeviceCommandSourceType], \r\n" +
            "  cccm.[DeviceCommandSourceId], \r\n" +
            "  cccm.[Reply], \r\n" +
            "  cccm.[Normalized], \r\n" +
            "  cccm.[PanVelocity], \r\n" +
            "  cccm.[TiltVelocity], \r\n" +
            "  cccm.[ZoomVelocity], \r\n" +
            "  cccm.[Duration] \r\n" +
            "FROM [CameraCommandContinuousMoveView] cccm \r\n";

    public final static String BaseViewName = "CameraCommandContinuousMoveView";
    public final static String ViewAliasName = "cccm";

    public final static int NORMALIZED_FIELD_ID = 9;
    public final static int PANVELOCITY_FIELD_ID = 10;
    public final static int TILTVELOCITY_FIELD_ID = 11;
    public final static int ZOOMVELOCITY_FIELD_ID = 12;
    public final static int DURATION_FIELD_ID = 13;

    public SimpleCameraCommandContinuousMoveDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final boolean getNormalized() throws SQLException {
        return getBoolean( NORMALIZED_FIELD_ID );
    }

    public final Double getPanVelocity() throws SQLException {
        return getNullableDouble( PANVELOCITY_FIELD_ID );
    }

    public final Double getTiltVelocity() throws SQLException {
        return getNullableDouble( TILTVELOCITY_FIELD_ID );
    }

    public final Double getZoomVelocity() throws SQLException {
        return getNullableDouble( ZOOMVELOCITY_FIELD_ID );
    }

    public final TimeSpan getDuration() throws SQLException {
        return getNullableTimeSpan( DURATION_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeBoolean( getNormalized( ) );
        destination.writeNullableDouble( getPanVelocity( ) );
        destination.writeNullableDouble( getTiltVelocity( ) );
        destination.writeNullableDouble( getZoomVelocity( ) );
        destination.writeNullableTimeSpan( getDuration( ) );
    }

    @Override
    public CameraCommandContinuousMoveObject getDataObject( ) throws SQLException {
        return new CameraCommandContinuousMoveObject( ObjectState.Stored, getId( ), getRowVersion( ), getCamera( ), getTimestamp( ), getDeviceCommandSourceType( ), getDeviceCommandSourceId( ), getReply( ), getNormalized( ), getPanVelocity( ), getTiltVelocity( ), getZoomVelocity( ), getDuration( ) );
    }

}
