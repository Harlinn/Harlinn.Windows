package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleAidToNavigationReportMessageDataReader extends SimpleAisMessageDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  atnrm.[Id], \r\n" +
            "  atnrm.[EntityType], \r\n" +
            "  atnrm.[RowVersion], \r\n" +
            "  atnrm.[AisDevice], \r\n" +
            "  atnrm.[ReceivedTimestamp], \r\n" +
            "  atnrm.[MessageSequenceNumber], \r\n" +
            "  atnrm.[Repeat], \r\n" +
            "  atnrm.[Mmsi], \r\n" +
            "  atnrm.[NavigationalAidType], \r\n" +
            "  atnrm.[Name], \r\n" +
            "  atnrm.[PositionAccuracy], \r\n" +
            "  atnrm.[Longitude], \r\n" +
            "  atnrm.[Latitude], \r\n" +
            "  atnrm.[DimensionToBow], \r\n" +
            "  atnrm.[DimensionToStern], \r\n" +
            "  atnrm.[DimensionToPort], \r\n" +
            "  atnrm.[DimensionToStarboard], \r\n" +
            "  atnrm.[PositionFixType], \r\n" +
            "  atnrm.[Timestamp], \r\n" +
            "  atnrm.[OffPosition], \r\n" +
            "  atnrm.[RegionalReserved], \r\n" +
            "  atnrm.[Raim], \r\n" +
            "  atnrm.[VirtualAid], \r\n" +
            "  atnrm.[Assigned], \r\n" +
            "  atnrm.[Spare], \r\n" +
            "  atnrm.[NameExtension] \r\n" +
            "FROM [AidToNavigationReportMessageView] atnrm \r\n";

    public final static String BaseViewName = "AidToNavigationReportMessageView";
    public final static String ViewAliasName = "atnrm";

    public final static int NAVIGATIONALAIDTYPE_FIELD_ID = 9;
    public final static int NAME_FIELD_ID = 10;
    public final static int POSITIONACCURACY_FIELD_ID = 11;
    public final static int LONGITUDE_FIELD_ID = 12;
    public final static int LATITUDE_FIELD_ID = 13;
    public final static int DIMENSIONTOBOW_FIELD_ID = 14;
    public final static int DIMENSIONTOSTERN_FIELD_ID = 15;
    public final static int DIMENSIONTOPORT_FIELD_ID = 16;
    public final static int DIMENSIONTOSTARBOARD_FIELD_ID = 17;
    public final static int POSITIONFIXTYPE_FIELD_ID = 18;
    public final static int TIMESTAMP_FIELD_ID = 19;
    public final static int OFFPOSITION_FIELD_ID = 20;
    public final static int REGIONALRESERVED_FIELD_ID = 21;
    public final static int RAIM_FIELD_ID = 22;
    public final static int VIRTUALAID_FIELD_ID = 23;
    public final static int ASSIGNED_FIELD_ID = 24;
    public final static int SPARE_FIELD_ID = 25;
    public final static int NAMEEXTENSION_FIELD_ID = 26;

    public SimpleAidToNavigationReportMessageDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final int getNavigationalAidType() throws SQLException {
        return getInt32( NAVIGATIONALAIDTYPE_FIELD_ID );
    }

    public final String getName() throws SQLException {
        return getString( NAME_FIELD_ID );
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

    public final int getTimestamp() throws SQLException {
        return getInt32( TIMESTAMP_FIELD_ID );
    }

    public final boolean getOffPosition() throws SQLException {
        return getBoolean( OFFPOSITION_FIELD_ID );
    }

    public final int getRegionalReserved() throws SQLException {
        return getInt32( REGIONALRESERVED_FIELD_ID );
    }

    public final int getRaim() throws SQLException {
        return getInt32( RAIM_FIELD_ID );
    }

    public final boolean getVirtualAid() throws SQLException {
        return getBoolean( VIRTUALAID_FIELD_ID );
    }

    public final boolean getAssigned() throws SQLException {
        return getBoolean( ASSIGNED_FIELD_ID );
    }

    public final int getSpare() throws SQLException {
        return getInt32( SPARE_FIELD_ID );
    }

    public final String getNameExtension() throws SQLException {
        return getString( NAMEEXTENSION_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeInt32( getNavigationalAidType( ) );
        destination.writeStringUtf8( getName( ) );
        destination.writeInt32( getPositionAccuracy( ) );
        destination.writeDouble( getLongitude( ) );
        destination.writeDouble( getLatitude( ) );
        destination.writeInt32( getDimensionToBow( ) );
        destination.writeInt32( getDimensionToStern( ) );
        destination.writeInt32( getDimensionToPort( ) );
        destination.writeInt32( getDimensionToStarboard( ) );
        destination.writeInt32( getPositionFixType( ) );
        destination.writeInt32( getTimestamp( ) );
        destination.writeBoolean( getOffPosition( ) );
        destination.writeInt32( getRegionalReserved( ) );
        destination.writeInt32( getRaim( ) );
        destination.writeBoolean( getVirtualAid( ) );
        destination.writeBoolean( getAssigned( ) );
        destination.writeInt32( getSpare( ) );
        destination.writeStringUtf8( getNameExtension( ) );
    }

}
