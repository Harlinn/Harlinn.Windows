package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleAisStaticDataReportPartBMessageDataReader extends SimpleAisStaticDataReportMessageDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  asdrpb.[Id], \r\n" +
            "  asdrpb.[EntityType], \r\n" +
            "  asdrpb.[RowVersion], \r\n" +
            "  asdrpb.[AisDevice], \r\n" +
            "  asdrpb.[ReceivedTimestamp], \r\n" +
            "  asdrpb.[MessageSequenceNumber], \r\n" +
            "  asdrpb.[Repeat], \r\n" +
            "  asdrpb.[Mmsi], \r\n" +
            "  asdrpb.[PartNumber], \r\n" +
            "  asdrpb.[ShipType], \r\n" +
            "  asdrpb.[VendorId], \r\n" +
            "  asdrpb.[UnitModelCode], \r\n" +
            "  asdrpb.[SerialNumber], \r\n" +
            "  asdrpb.[Callsign], \r\n" +
            "  asdrpb.[DimensionToBow], \r\n" +
            "  asdrpb.[DimensionToStern], \r\n" +
            "  asdrpb.[DimensionToPort], \r\n" +
            "  asdrpb.[DimensionToStarboard], \r\n" +
            "  asdrpb.[MothershipMmsi], \r\n" +
            "  asdrpb.[PositionFixType], \r\n" +
            "  asdrpb.[Spare] \r\n" +
            "FROM [AisStaticDataReportPartBMessageView] asdrpb \r\n";

    public final static String BaseViewName = "AisStaticDataReportPartBMessageView";
    public final static String ViewAliasName = "asdrpb";

    public final static int SHIPTYPE_FIELD_ID = 10;
    public final static int VENDORID_FIELD_ID = 11;
    public final static int UNITMODELCODE_FIELD_ID = 12;
    public final static int SERIALNUMBER_FIELD_ID = 13;
    public final static int CALLSIGN_FIELD_ID = 14;
    public final static int DIMENSIONTOBOW_FIELD_ID = 15;
    public final static int DIMENSIONTOSTERN_FIELD_ID = 16;
    public final static int DIMENSIONTOPORT_FIELD_ID = 17;
    public final static int DIMENSIONTOSTARBOARD_FIELD_ID = 18;
    public final static int MOTHERSHIPMMSI_FIELD_ID = 19;
    public final static int POSITIONFIXTYPE_FIELD_ID = 20;
    public final static int SPARE_FIELD_ID = 21;

    public SimpleAisStaticDataReportPartBMessageDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final int getShipType() throws SQLException {
        return getInt32( SHIPTYPE_FIELD_ID );
    }

    public final String getVendorId() throws SQLException {
        return getString( VENDORID_FIELD_ID );
    }

    public final int getUnitModelCode() throws SQLException {
        return getInt32( UNITMODELCODE_FIELD_ID );
    }

    public final int getSerialNumber() throws SQLException {
        return getInt32( SERIALNUMBER_FIELD_ID );
    }

    public final Guid getCallsign() throws SQLException {
        return getNullableGuid( CALLSIGN_FIELD_ID );
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

    public final Guid getMothershipMmsi() throws SQLException {
        return getNullableGuid( MOTHERSHIPMMSI_FIELD_ID );
    }

    public final int getPositionFixType() throws SQLException {
        return getInt32( POSITIONFIXTYPE_FIELD_ID );
    }

    public final int getSpare() throws SQLException {
        return getInt32( SPARE_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeInt32( getShipType( ) );
        destination.writeStringUtf8( getVendorId( ) );
        destination.writeInt32( getUnitModelCode( ) );
        destination.writeInt32( getSerialNumber( ) );
        destination.writeNullableGuid( getCallsign( ) );
        destination.writeInt32( getDimensionToBow( ) );
        destination.writeInt32( getDimensionToStern( ) );
        destination.writeInt32( getDimensionToPort( ) );
        destination.writeInt32( getDimensionToStarboard( ) );
        destination.writeNullableGuid( getMothershipMmsi( ) );
        destination.writeInt32( getPositionFixType( ) );
        destination.writeInt32( getSpare( ) );
    }

    @Override
    public AisStaticDataReportPartBMessageObject GetDataObject( ) throws SQLException {
        return new AisStaticDataReportPartBMessageObject( ObjectState.Stored, getId( ), getRowVersion( ), getAisDevice( ), getReceivedTimestamp( ), getMessageSequenceNumber( ), getRepeat( ), getMmsi( ), getPartNumber( ), getShipType( ), getVendorId( ), getUnitModelCode( ), getSerialNumber( ), getCallsign( ), getDimensionToBow( ), getDimensionToStern( ), getDimensionToPort( ), getDimensionToStarboard( ), getMothershipMmsi( ), getPositionFixType( ), getSpare( ) );
    }

}
