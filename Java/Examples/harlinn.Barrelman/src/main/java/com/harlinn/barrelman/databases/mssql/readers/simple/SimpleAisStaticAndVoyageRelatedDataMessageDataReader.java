package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleAisStaticAndVoyageRelatedDataMessageDataReader extends SimpleAisMessageDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  asavrdm.[Id], \r\n" +
            "  asavrdm.[EntityType], \r\n" +
            "  asavrdm.[RowVersion], \r\n" +
            "  asavrdm.[AisDevice], \r\n" +
            "  asavrdm.[ReceivedTimestamp], \r\n" +
            "  asavrdm.[MessageSequenceNumber], \r\n" +
            "  asavrdm.[Repeat], \r\n" +
            "  asavrdm.[Mmsi], \r\n" +
            "  asavrdm.[AisVersion], \r\n" +
            "  asavrdm.[ImoNumber], \r\n" +
            "  asavrdm.[Callsign], \r\n" +
            "  asavrdm.[ShipName], \r\n" +
            "  asavrdm.[ShipType], \r\n" +
            "  asavrdm.[DimensionToBow], \r\n" +
            "  asavrdm.[DimensionToStern], \r\n" +
            "  asavrdm.[DimensionToPort], \r\n" +
            "  asavrdm.[DimensionToStarboard], \r\n" +
            "  asavrdm.[PositionFixType], \r\n" +
            "  asavrdm.[EstimatedTimeOfArrival], \r\n" +
            "  asavrdm.[Draught], \r\n" +
            "  asavrdm.[Destination], \r\n" +
            "  asavrdm.[DataTerminalReady], \r\n" +
            "  asavrdm.[Spare] \r\n" +
            "FROM [AisStaticAndVoyageRelatedDataMessageView] asavrdm \r\n";

    public final static String BaseViewName = "AisStaticAndVoyageRelatedDataMessageView";
    public final static String ViewAliasName = "asavrdm";

    public final static int AISVERSION_FIELD_ID = 9;
    public final static int IMONUMBER_FIELD_ID = 10;
    public final static int CALLSIGN_FIELD_ID = 11;
    public final static int SHIPNAME_FIELD_ID = 12;
    public final static int SHIPTYPE_FIELD_ID = 13;
    public final static int DIMENSIONTOBOW_FIELD_ID = 14;
    public final static int DIMENSIONTOSTERN_FIELD_ID = 15;
    public final static int DIMENSIONTOPORT_FIELD_ID = 16;
    public final static int DIMENSIONTOSTARBOARD_FIELD_ID = 17;
    public final static int POSITIONFIXTYPE_FIELD_ID = 18;
    public final static int ESTIMATEDTIMEOFARRIVAL_FIELD_ID = 19;
    public final static int DRAUGHT_FIELD_ID = 20;
    public final static int DESTINATION_FIELD_ID = 21;
    public final static int DATATERMINALREADY_FIELD_ID = 22;
    public final static int SPARE_FIELD_ID = 23;

    public SimpleAisStaticAndVoyageRelatedDataMessageDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final int getAisVersion() throws SQLException {
        return getInt32( AISVERSION_FIELD_ID );
    }

    public final Guid getImoNumber() throws SQLException {
        return getNullableGuid( IMONUMBER_FIELD_ID );
    }

    public final Guid getCallsign() throws SQLException {
        return getNullableGuid( CALLSIGN_FIELD_ID );
    }

    public final Guid getShipName() throws SQLException {
        return getNullableGuid( SHIPNAME_FIELD_ID );
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

    public final DateTime getEstimatedTimeOfArrival() throws SQLException {
        return getNullableDateTimeFromLong( ESTIMATEDTIMEOFARRIVAL_FIELD_ID );
    }

    public final double getDraught() throws SQLException {
        return getDouble( DRAUGHT_FIELD_ID );
    }

    public final String getDestination() throws SQLException {
        return getString( DESTINATION_FIELD_ID );
    }

    public final boolean getDataTerminalReady() throws SQLException {
        return getBoolean( DATATERMINALREADY_FIELD_ID );
    }

    public final int getSpare() throws SQLException {
        return getInt32( SPARE_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeInt32( getAisVersion( ) );
        destination.writeNullableGuid( getImoNumber( ) );
        destination.writeNullableGuid( getCallsign( ) );
        destination.writeNullableGuid( getShipName( ) );
        destination.writeInt32( getShipType( ) );
        destination.writeInt32( getDimensionToBow( ) );
        destination.writeInt32( getDimensionToStern( ) );
        destination.writeInt32( getDimensionToPort( ) );
        destination.writeInt32( getDimensionToStarboard( ) );
        destination.writeInt32( getPositionFixType( ) );
        destination.writeNullableDateTime( getEstimatedTimeOfArrival( ) );
        destination.writeDouble( getDraught( ) );
        destination.writeStringUtf8( getDestination( ) );
        destination.writeBoolean( getDataTerminalReady( ) );
        destination.writeInt32( getSpare( ) );
    }

    @Override
    public AisStaticAndVoyageRelatedDataMessageObject getDataObject( ) throws SQLException {
        return new AisStaticAndVoyageRelatedDataMessageObject( ObjectState.Stored, getId( ), getRowVersion( ), getAisDevice( ), getReceivedTimestamp( ), getMessageSequenceNumber( ), getRepeat( ), getMmsi( ), getAisVersion( ), getImoNumber( ), getCallsign( ), getShipName( ), getShipType( ), getDimensionToBow( ), getDimensionToStern( ), getDimensionToPort( ), getDimensionToStarboard( ), getPositionFixType( ), getEstimatedTimeOfArrival( ), getDraught( ), getDestination( ), getDataTerminalReady( ), getSpare( ) );
    }

}
