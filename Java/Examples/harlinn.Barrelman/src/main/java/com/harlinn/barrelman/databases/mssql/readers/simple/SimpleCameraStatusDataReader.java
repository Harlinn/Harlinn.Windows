package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleCameraStatusDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  cs.[Id], \r\n" +
            "  cs.[RowVersion], \r\n" +
            "  cs.[Camera], \r\n" +
            "  cs.[Track], \r\n" +
            "  cs.[Timestamp], \r\n" +
            "  cs.[PositionPanTiltMode], \r\n" +
            "  cs.[PanAngle], \r\n" +
            "  cs.[TiltAngle], \r\n" +
            "  cs.[PositionFocalLengthMode], \r\n" +
            "  cs.[FocalLength], \r\n" +
            "  cs.[PanTiltMoveStatus], \r\n" +
            "  cs.[ZoomMoveStatus], \r\n" +
            "  cs.[VelocityPanTiltMode], \r\n" +
            "  cs.[PanVelocity], \r\n" +
            "  cs.[TiltVelocity], \r\n" +
            "  cs.[VelocityFocalLengthMode], \r\n" +
            "  cs.[ZoomVelocity], \r\n" +
            "  cs.[ActiveFeatures], \r\n" +
            "  cs.[Error] \r\n" +
            "FROM [CameraStatusView] cs \r\n";

    public final static String BaseViewName = "CameraStatusView";
    public final static String ViewAliasName = "cs";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int CAMERA_FIELD_ID = 3;
    public final static int TRACK_FIELD_ID = 4;
    public final static int TIMESTAMP_FIELD_ID = 5;
    public final static int POSITIONPANTILTMODE_FIELD_ID = 6;
    public final static int PANANGLE_FIELD_ID = 7;
    public final static int TILTANGLE_FIELD_ID = 8;
    public final static int POSITIONFOCALLENGTHMODE_FIELD_ID = 9;
    public final static int FOCALLENGTH_FIELD_ID = 10;
    public final static int PANTILTMOVESTATUS_FIELD_ID = 11;
    public final static int ZOOMMOVESTATUS_FIELD_ID = 12;
    public final static int VELOCITYPANTILTMODE_FIELD_ID = 13;
    public final static int PANVELOCITY_FIELD_ID = 14;
    public final static int TILTVELOCITY_FIELD_ID = 15;
    public final static int VELOCITYFOCALLENGTHMODE_FIELD_ID = 16;
    public final static int ZOOMVELOCITY_FIELD_ID = 17;
    public final static int ACTIVEFEATURES_FIELD_ID = 18;
    public final static int ERROR_FIELD_ID = 19;

    public SimpleCameraStatusDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final Guid getCamera() throws SQLException {
        return getGuid( CAMERA_FIELD_ID );
    }

    public final Guid getTrack() throws SQLException {
        return getNullableGuid( TRACK_FIELD_ID );
    }

    public final DateTime getTimestamp() throws SQLException {
        return getDateTimeFromLong( TIMESTAMP_FIELD_ID );
    }

    public final int getPositionPanTiltMode() throws SQLException {
        return getInt32( POSITIONPANTILTMODE_FIELD_ID );
    }

    public final double getPanAngle() throws SQLException {
        return getDouble( PANANGLE_FIELD_ID );
    }

    public final double getTiltAngle() throws SQLException {
        return getDouble( TILTANGLE_FIELD_ID );
    }

    public final int getPositionFocalLengthMode() throws SQLException {
        return getInt32( POSITIONFOCALLENGTHMODE_FIELD_ID );
    }

    public final double getFocalLength() throws SQLException {
        return getDouble( FOCALLENGTH_FIELD_ID );
    }

    public final int getPanTiltMoveStatus() throws SQLException {
        return getInt32( PANTILTMOVESTATUS_FIELD_ID );
    }

    public final int getZoomMoveStatus() throws SQLException {
        return getInt32( ZOOMMOVESTATUS_FIELD_ID );
    }

    public final int getVelocityPanTiltMode() throws SQLException {
        return getInt32( VELOCITYPANTILTMODE_FIELD_ID );
    }

    public final Double getPanVelocity() throws SQLException {
        return getNullableDouble( PANVELOCITY_FIELD_ID );
    }

    public final Double getTiltVelocity() throws SQLException {
        return getNullableDouble( TILTVELOCITY_FIELD_ID );
    }

    public final int getVelocityFocalLengthMode() throws SQLException {
        return getInt32( VELOCITYFOCALLENGTHMODE_FIELD_ID );
    }

    public final Double getZoomVelocity() throws SQLException {
        return getNullableDouble( ZOOMVELOCITY_FIELD_ID );
    }

    public final int getActiveFeatures() throws SQLException {
        return getInt32( ACTIVEFEATURES_FIELD_ID );
    }

    public final String getError() throws SQLException {
        return getString( ERROR_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.CameraStatus );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getCamera( ) );
        destination.writeNullableGuid( getTrack( ) );
        destination.writeDateTime( getTimestamp( ) );
        destination.writeInt32( getPositionPanTiltMode( ) );
        destination.writeDouble( getPanAngle( ) );
        destination.writeDouble( getTiltAngle( ) );
        destination.writeInt32( getPositionFocalLengthMode( ) );
        destination.writeDouble( getFocalLength( ) );
        destination.writeInt32( getPanTiltMoveStatus( ) );
        destination.writeInt32( getZoomMoveStatus( ) );
        destination.writeInt32( getVelocityPanTiltMode( ) );
        destination.writeNullableDouble( getPanVelocity( ) );
        destination.writeNullableDouble( getTiltVelocity( ) );
        destination.writeInt32( getVelocityFocalLengthMode( ) );
        destination.writeNullableDouble( getZoomVelocity( ) );
        destination.writeInt32( getActiveFeatures( ) );
        destination.writeStringUtf8( getError( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

}
