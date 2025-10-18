package com.harlinn.barrelman.databases.mssql.readers.complex;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class ComplexAisStaticDataReportMessageDataReader extends ResultSetWrapper {

    public final static String BaseQuery = "SELECT \r\n" +
            "  asdrm.[Id], \r\n" +
            "  asdrm.[EntityType], \r\n" +
            "  asdrm.[RowVersion], \r\n" +
            "  asdrm.[AisDevice], \r\n" +
            "  asdrm.[ReceivedTimestamp], \r\n" +
            "  asdrm.[MessageSequenceNumber], \r\n" +
            "  asdrm.[Repeat], \r\n" +
            "  asdrm.[Mmsi], \r\n" +
            "  asdrm.[PartNumber], \r\n" +
            "  asdrpa.[ShipName], \r\n" +
            "  asdrpa.[Spare], \r\n" +
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
            "FROM [AisStaticDataReportMessageView] asdrm \r\n" +
            "  LEFT JOIN [AisStaticDataReportPartAMessage] asdrpa ON(asdrm.[Id] = asdrpa.[Id] ) \r\n" +
            "  LEFT JOIN [AisStaticDataReportPartBMessage] asdrpb ON(asdrm.[Id] = asdrpb.[Id] ) \r\n";

    public final static String BaseViewName = "AisStaticDataReportMessageView";
    public final static String ViewAliasName = "asdrm";

    public final static int ASDRM_ID_FIELD_ID = 1;
    public final static int ASDRM_KIND_FIELD_ID = 2;
    public final static int ASDRM_ROWVERSION_FIELD_ID = 3;
    public final static int ASDRM_AISDEVICE_FIELD_ID = 4;
    public final static int ASDRM_RECEIVEDTIMESTAMP_FIELD_ID = 5;
    public final static int ASDRM_MESSAGESEQUENCENUMBER_FIELD_ID = 6;
    public final static int ASDRM_REPEAT_FIELD_ID = 7;
    public final static int ASDRM_MMSI_FIELD_ID = 8;
    public final static int ASDRM_PARTNUMBER_FIELD_ID = 9;
    public final static int ASDRPA_SHIPNAME_FIELD_ID = 10;
    public final static int ASDRPA_SPARE_FIELD_ID = 11;
    public final static int ASDRPB_SHIPTYPE_FIELD_ID = 12;
    public final static int ASDRPB_VENDORID_FIELD_ID = 13;
    public final static int ASDRPB_UNITMODELCODE_FIELD_ID = 14;
    public final static int ASDRPB_SERIALNUMBER_FIELD_ID = 15;
    public final static int ASDRPB_CALLSIGN_FIELD_ID = 16;
    public final static int ASDRPB_DIMENSIONTOBOW_FIELD_ID = 17;
    public final static int ASDRPB_DIMENSIONTOSTERN_FIELD_ID = 18;
    public final static int ASDRPB_DIMENSIONTOPORT_FIELD_ID = 19;
    public final static int ASDRPB_DIMENSIONTOSTARBOARD_FIELD_ID = 20;
    public final static int ASDRPB_MOTHERSHIPMMSI_FIELD_ID = 21;
    public final static int ASDRPB_POSITIONFIXTYPE_FIELD_ID = 22;
    public final static int ASDRPB_SPARE_FIELD_ID = 23;

    public ComplexAisStaticDataReportMessageDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public Guid getId( ) throws SQLException {
        return getGuid( ASDRM_ID_FIELD_ID );
    }

    public int getObjectType() throws SQLException {
        return getInt32( ASDRM_KIND_FIELD_ID );
    }

    public long getRowVersion( ) throws SQLException {
        return getInt64( ASDRM_ROWVERSION_FIELD_ID );
    }

    public Guid getAisDevice( ) throws SQLException {
        return getGuid( ASDRM_AISDEVICE_FIELD_ID );
    }

    public DateTime getReceivedTimestamp( ) throws SQLException {
        return getDateTimeFromLong( ASDRM_RECEIVEDTIMESTAMP_FIELD_ID );
    }

    public long getMessageSequenceNumber( ) throws SQLException {
        return getInt64( ASDRM_MESSAGESEQUENCENUMBER_FIELD_ID );
    }

    public int getRepeat( ) throws SQLException {
        return getInt32( ASDRM_REPEAT_FIELD_ID );
    }

    public Guid getMmsi( ) throws SQLException {
        return getNullableGuid( ASDRM_MMSI_FIELD_ID );
    }

    public int getPartNumber( ) throws SQLException {
        return getInt32( ASDRM_PARTNUMBER_FIELD_ID );
    }

    public Guid getAisStaticDataReportPartAMessageShipName( ) throws SQLException {
        return getNullableGuid( ASDRPA_SHIPNAME_FIELD_ID );
    }

    public int getAisStaticDataReportPartAMessageSpare( ) throws SQLException {
        return getInt32( ASDRPA_SPARE_FIELD_ID );
    }

    public int getAisStaticDataReportPartBMessageShipType( ) throws SQLException {
        return getInt32( ASDRPB_SHIPTYPE_FIELD_ID );
    }

    public String getAisStaticDataReportPartBMessageVendorId( ) throws SQLException {
        return getString( ASDRPB_VENDORID_FIELD_ID );
    }

    public int getAisStaticDataReportPartBMessageUnitModelCode( ) throws SQLException {
        return getInt32( ASDRPB_UNITMODELCODE_FIELD_ID );
    }

    public int getAisStaticDataReportPartBMessageSerialNumber( ) throws SQLException {
        return getInt32( ASDRPB_SERIALNUMBER_FIELD_ID );
    }

    public Guid getAisStaticDataReportPartBMessageCallsign( ) throws SQLException {
        return getNullableGuid( ASDRPB_CALLSIGN_FIELD_ID );
    }

    public int getAisStaticDataReportPartBMessageDimensionToBow( ) throws SQLException {
        return getInt32( ASDRPB_DIMENSIONTOBOW_FIELD_ID );
    }

    public int getAisStaticDataReportPartBMessageDimensionToStern( ) throws SQLException {
        return getInt32( ASDRPB_DIMENSIONTOSTERN_FIELD_ID );
    }

    public int getAisStaticDataReportPartBMessageDimensionToPort( ) throws SQLException {
        return getInt32( ASDRPB_DIMENSIONTOPORT_FIELD_ID );
    }

    public int getAisStaticDataReportPartBMessageDimensionToStarboard( ) throws SQLException {
        return getInt32( ASDRPB_DIMENSIONTOSTARBOARD_FIELD_ID );
    }

    public Guid getAisStaticDataReportPartBMessageMothershipMmsi( ) throws SQLException {
        return getNullableGuid( ASDRPB_MOTHERSHIPMMSI_FIELD_ID );
    }

    public int getAisStaticDataReportPartBMessagePositionFixType( ) throws SQLException {
        return getInt32( ASDRPB_POSITIONFIXTYPE_FIELD_ID );
    }

    public int getAisStaticDataReportPartBMessageSpare( ) throws SQLException {
        return getInt32( ASDRPB_SPARE_FIELD_ID );
    }

}

