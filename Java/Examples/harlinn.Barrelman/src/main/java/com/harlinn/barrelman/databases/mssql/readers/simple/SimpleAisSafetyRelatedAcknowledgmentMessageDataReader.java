package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleAisSafetyRelatedAcknowledgmentMessageDataReader extends SimpleAisMessageDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  asram.[Id], \r\n" +
            "  asram.[EntityType], \r\n" +
            "  asram.[RowVersion], \r\n" +
            "  asram.[AisDevice], \r\n" +
            "  asram.[ReceivedTimestamp], \r\n" +
            "  asram.[MessageSequenceNumber], \r\n" +
            "  asram.[Repeat], \r\n" +
            "  asram.[Mmsi], \r\n" +
            "  asram.[Spare], \r\n" +
            "  asram.[SequenceNumber1], \r\n" +
            "  asram.[Mmsi1], \r\n" +
            "  asram.[SequenceNumber2], \r\n" +
            "  asram.[Mmsi2], \r\n" +
            "  asram.[SequenceNumber3], \r\n" +
            "  asram.[Mmsi3], \r\n" +
            "  asram.[SequenceNumber4], \r\n" +
            "  asram.[Mmsi4] \r\n" +
            "FROM [AisSafetyRelatedAcknowledgmentMessageView] asram \r\n";

    public final static String BaseViewName = "AisSafetyRelatedAcknowledgmentMessageView";
    public final static String ViewAliasName = "asram";

    public final static int SPARE_FIELD_ID = 9;
    public final static int SEQUENCENUMBER1_FIELD_ID = 10;
    public final static int MMSI1_FIELD_ID = 11;
    public final static int SEQUENCENUMBER2_FIELD_ID = 12;
    public final static int MMSI2_FIELD_ID = 13;
    public final static int SEQUENCENUMBER3_FIELD_ID = 14;
    public final static int MMSI3_FIELD_ID = 15;
    public final static int SEQUENCENUMBER4_FIELD_ID = 16;
    public final static int MMSI4_FIELD_ID = 17;

    public SimpleAisSafetyRelatedAcknowledgmentMessageDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final int getSpare() throws SQLException {
        return getInt32( SPARE_FIELD_ID );
    }

    public final int getSequenceNumber1() throws SQLException {
        return getInt32( SEQUENCENUMBER1_FIELD_ID );
    }

    public final Guid getMmsi1() throws SQLException {
        return getNullableGuid( MMSI1_FIELD_ID );
    }

    public final Integer getSequenceNumber2() throws SQLException {
        return getNullableInt32( SEQUENCENUMBER2_FIELD_ID );
    }

    public final Guid getMmsi2() throws SQLException {
        return getNullableGuid( MMSI2_FIELD_ID );
    }

    public final Integer getSequenceNumber3() throws SQLException {
        return getNullableInt32( SEQUENCENUMBER3_FIELD_ID );
    }

    public final Guid getMmsi3() throws SQLException {
        return getNullableGuid( MMSI3_FIELD_ID );
    }

    public final Integer getSequenceNumber4() throws SQLException {
        return getNullableInt32( SEQUENCENUMBER4_FIELD_ID );
    }

    public final Guid getMmsi4() throws SQLException {
        return getNullableGuid( MMSI4_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeInt32( getSpare( ) );
        destination.writeInt32( getSequenceNumber1( ) );
        destination.writeNullableGuid( getMmsi1( ) );
        destination.writeNullableInt32( getSequenceNumber2( ) );
        destination.writeNullableGuid( getMmsi2( ) );
        destination.writeNullableInt32( getSequenceNumber3( ) );
        destination.writeNullableGuid( getMmsi3( ) );
        destination.writeNullableInt32( getSequenceNumber4( ) );
        destination.writeNullableGuid( getMmsi4( ) );
    }

}
