package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleAisBinaryAddressedMessageDataReader extends SimpleAisMessageDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  abam.[Id], \r\n" +
            "  abam.[EntityType], \r\n" +
            "  abam.[RowVersion], \r\n" +
            "  abam.[AisDevice], \r\n" +
            "  abam.[ReceivedTimestamp], \r\n" +
            "  abam.[MessageSequenceNumber], \r\n" +
            "  abam.[Repeat], \r\n" +
            "  abam.[Mmsi], \r\n" +
            "  abam.[SequenceNumber], \r\n" +
            "  abam.[DestinationMmsi], \r\n" +
            "  abam.[RetransmitFlag], \r\n" +
            "  abam.[Spare], \r\n" +
            "  abam.[DesignatedAreaCode], \r\n" +
            "  abam.[FunctionalId], \r\n" +
            "  abam.[Data] \r\n" +
            "FROM [AisBinaryAddressedMessageView] abam \r\n";

    public final static String BaseViewName = "AisBinaryAddressedMessageView";
    public final static String ViewAliasName = "abam";

    public final static int SEQUENCENUMBER_FIELD_ID = 9;
    public final static int DESTINATIONMMSI_FIELD_ID = 10;
    public final static int RETRANSMITFLAG_FIELD_ID = 11;
    public final static int SPARE_FIELD_ID = 12;
    public final static int DESIGNATEDAREACODE_FIELD_ID = 13;
    public final static int FUNCTIONALID_FIELD_ID = 14;
    public final static int DATA_FIELD_ID = 15;

    public SimpleAisBinaryAddressedMessageDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final int getSequenceNumber() throws SQLException {
        return getInt32( SEQUENCENUMBER_FIELD_ID );
    }

    public final Guid getDestinationMmsi() throws SQLException {
        return getNullableGuid( DESTINATIONMMSI_FIELD_ID );
    }

    public final boolean getRetransmitFlag() throws SQLException {
        return getBoolean( RETRANSMITFLAG_FIELD_ID );
    }

    public final int getSpare() throws SQLException {
        return getInt32( SPARE_FIELD_ID );
    }

    public final int getDesignatedAreaCode() throws SQLException {
        return getInt32( DESIGNATEDAREACODE_FIELD_ID );
    }

    public final int getFunctionalId() throws SQLException {
        return getInt32( FUNCTIONALID_FIELD_ID );
    }

    public final String getData() throws SQLException {
        return getString( DATA_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeInt32( getSequenceNumber( ) );
        destination.writeNullableGuid( getDestinationMmsi( ) );
        destination.writeBoolean( getRetransmitFlag( ) );
        destination.writeInt32( getSpare( ) );
        destination.writeInt32( getDesignatedAreaCode( ) );
        destination.writeInt32( getFunctionalId( ) );
        destination.writeStringUtf8( getData( ) );
    }

}
