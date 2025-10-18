package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleAisExtendedClassBCsPositionReportMessageDataReader extends SimpleAisMessageDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  aecbprm.[Id], \r\n" +
            "  aecbprm.[EntityType], \r\n" +
            "  aecbprm.[RowVersion], \r\n" +
            "  aecbprm.[AisDevice], \r\n" +
            "  aecbprm.[ReceivedTimestamp], \r\n" +
            "  aecbprm.[MessageSequenceNumber], \r\n" +
            "  aecbprm.[Repeat], \r\n" +
            "  aecbprm.[Mmsi], \r\n" +
            "  aecbprm.[Reserved], \r\n" +
            "  aecbprm.[SpeedOverGround], \r\n" +
            "  aecbprm.[PositionAccuracy], \r\n" +
            "  aecbprm.[Longitude], \r\n" +
            "  aecbprm.[Latitude], \r\n" +
            "  aecbprm.[CourseOverGround], \r\n" +
            "  aecbprm.[TrueHeading], \r\n" +
            "  aecbprm.[Timestamp], \r\n" +
            "  aecbprm.[RegionalReserved], \r\n" +
            "  aecbprm.[Name], \r\n" +
            "  aecbprm.[ShipType], \r\n" +
            "  aecbprm.[DimensionToBow], \r\n" +
            "  aecbprm.[DimensionToStern], \r\n" +
            "  aecbprm.[DimensionToPort], \r\n" +
            "  aecbprm.[DimensionToStarboard], \r\n" +
            "  aecbprm.[PositionFixType], \r\n" +
            "  aecbprm.[Raim], \r\n" +
            "  aecbprm.[DataTerminalReady], \r\n" +
            "  aecbprm.[Assigned], \r\n" +
            "  aecbprm.[Spare] \r\n" +
            "FROM [AisExtendedClassBCsPositionReportMessageView] aecbprm \r\n";

    public final static String BaseViewName = "AisExtendedClassBCsPositionReportMessageView";
    public final static String ViewAliasName = "aecbprm";

    public final static int RESERVED_FIELD_ID = 9;
    public final static int SPEEDOVERGROUND_FIELD_ID = 10;
    public final static int POSITIONACCURACY_FIELD_ID = 11;
    public final static int LONGITUDE_FIELD_ID = 12;
    public final static int LATITUDE_FIELD_ID = 13;
    public final static int COURSEOVERGROUND_FIELD_ID = 14;
    public final static int TRUEHEADING_FIELD_ID = 15;
    public final static int TIMESTAMP_FIELD_ID = 16;
    public final static int REGIONALRESERVED_FIELD_ID = 17;
    public final static int NAME_FIELD_ID = 18;
    public final static int SHIPTYPE_FIELD_ID = 19;
    public final static int DIMENSIONTOBOW_FIELD_ID = 20;
    public final static int DIMENSIONTOSTERN_FIELD_ID = 21;
    public final static int DIMENSIONTOPORT_FIELD_ID = 22;
    public final static int DIMENSIONTOSTARBOARD_FIELD_ID = 23;
    public final static int POSITIONFIXTYPE_FIELD_ID = 24;
    public final static int RAIM_FIELD_ID = 25;
    public final static int DATATERMINALREADY_FIELD_ID = 26;
    public final static int ASSIGNED_FIELD_ID = 27;
    public final static int SPARE_FIELD_ID = 28;

    public SimpleAisExtendedClassBCsPositionReportMessageDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final int getReserved() throws SQLException {
        return getInt32( RESERVED_FIELD_ID );
    }

    public final double getSpeedOverGround() throws SQLException {
        return getDouble( SPEEDOVERGROUND_FIELD_ID );
    }

    public final int getPositionAccuracy() throws SQLException {
        return getInt32( POSITIONACCURACY_FIELD_ID );
    }

    public final double getLongitude() throws SQLException {
        return getDouble( LONGITUDE_FIELD_ID );
    }

    public final double getLatitude() throws SQLException {
        return getDouble( LATITUDE_FIELD_ID );
    }

    public final double getCourseOverGround() throws SQLException {
        return getDouble( COURSEOVERGROUND_FIELD_ID );
    }

    public final Integer getTrueHeading() throws SQLException {
        return getNullableInt32( TRUEHEADING_FIELD_ID );
    }

    public final int getTimestamp() throws SQLException {
        return getInt32( TIMESTAMP_FIELD_ID );
    }

    public final int getRegionalReserved() throws SQLException {
        return getInt32( REGIONALRESERVED_FIELD_ID );
    }

    public final Guid getName() throws SQLException {
        return getNullableGuid( NAME_FIELD_ID );
    }

    public final int getShipType() throws SQLException {
        return getInt32( SHIPTYPE_FIELD_ID );
    }

    public final int getDimensionToBow() throws SQLException {
        return getInt32( DIMENSIONTOBOW_FIELD_ID );
    }

    public final int getDimensionToStern() throws SQLException {
        return getInt32( DIMENSIONTOSTERN_FIELD_ID );
    }

    public final int getDimensionToPort() throws SQLException {
        return getInt32( DIMENSIONTOPORT_FIELD_ID );
    }

    public final int getDimensionToStarboard() throws SQLException {
        return getInt32( DIMENSIONTOSTARBOARD_FIELD_ID );
    }

    public final int getPositionFixType() throws SQLException {
        return getInt32( POSITIONFIXTYPE_FIELD_ID );
    }

    public final int getRaim() throws SQLException {
        return getInt32( RAIM_FIELD_ID );
    }

    public final boolean getDataTerminalReady() throws SQLException {
        return getBoolean( DATATERMINALREADY_FIELD_ID );
    }

    public final boolean getAssigned() throws SQLException {
        return getBoolean( ASSIGNED_FIELD_ID );
    }

    public final int getSpare() throws SQLException {
        return getInt32( SPARE_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeInt32( getReserved( ) );
        destination.writeDouble( getSpeedOverGround( ) );
        destination.writeInt32( getPositionAccuracy( ) );
        destination.writeDouble( getLongitude( ) );
        destination.writeDouble( getLatitude( ) );
        destination.writeDouble( getCourseOverGround( ) );
        destination.writeNullableInt32( getTrueHeading( ) );
        destination.writeInt32( getTimestamp( ) );
        destination.writeInt32( getRegionalReserved( ) );
        destination.writeNullableGuid( getName( ) );
        destination.writeInt32( getShipType( ) );
        destination.writeInt32( getDimensionToBow( ) );
        destination.writeInt32( getDimensionToStern( ) );
        destination.writeInt32( getDimensionToPort( ) );
        destination.writeInt32( getDimensionToStarboard( ) );
        destination.writeInt32( getPositionFixType( ) );
        destination.writeInt32( getRaim( ) );
        destination.writeBoolean( getDataTerminalReady( ) );
        destination.writeBoolean( getAssigned( ) );
        destination.writeInt32( getSpare( ) );
    }

    @Override
    public AisExtendedClassBCsPositionReportMessageObject GetDataObject( ) throws SQLException {
        return new AisExtendedClassBCsPositionReportMessageObject( ObjectState.Stored, getId( ), getRowVersion( ), getAisDevice( ), getReceivedTimestamp( ), getMessageSequenceNumber( ), getRepeat( ), getMmsi( ), getReserved( ), getSpeedOverGround( ), getPositionAccuracy( ), getLongitude( ), getLatitude( ), getCourseOverGround( ), getTrueHeading( ), getTimestamp( ), getRegionalReserved( ), getName( ), getShipType( ), getDimensionToBow( ), getDimensionToStern( ), getDimensionToPort( ), getDimensionToStarboard( ), getPositionFixType( ), getRaim( ), getDataTerminalReady( ), getAssigned( ), getSpare( ) );
    }

}
