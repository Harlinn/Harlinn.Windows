package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleAisAddressedSafetyRelatedMessageDataReader extends SimpleAisMessageDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  aasrm.[Id], \r\n" +
            "  aasrm.[EntityType], \r\n" +
            "  aasrm.[RowVersion], \r\n" +
            "  aasrm.[AisDevice], \r\n" +
            "  aasrm.[ReceivedTimestamp], \r\n" +
            "  aasrm.[MessageSequenceNumber], \r\n" +
            "  aasrm.[Repeat], \r\n" +
            "  aasrm.[Mmsi], \r\n" +
            "  aasrm.[SequenceNumber], \r\n" +
            "  aasrm.[DestinationMmsi], \r\n" +
            "  aasrm.[RetransmitFlag], \r\n" +
            "  aasrm.[Spare], \r\n" +
            "  aasrm.[Text] \r\n" +
            "FROM [AisAddressedSafetyRelatedMessageView] aasrm \r\n";

    public final static String BaseViewName = "AisAddressedSafetyRelatedMessageView";
    public final static String ViewAliasName = "aasrm";

    public final static int SEQUENCENUMBER_FIELD_ID = 9;
    public final static int DESTINATIONMMSI_FIELD_ID = 10;
    public final static int RETRANSMITFLAG_FIELD_ID = 11;
    public final static int SPARE_FIELD_ID = 12;
    public final static int TEXT_FIELD_ID = 13;

    public SimpleAisAddressedSafetyRelatedMessageDataReader( ResultSet resultSet ) {
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

    public final String getText() throws SQLException {
        return getString( TEXT_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeInt32( getSequenceNumber( ) );
        destination.writeNullableGuid( getDestinationMmsi( ) );
        destination.writeBoolean( getRetransmitFlag( ) );
        destination.writeInt32( getSpare( ) );
        destination.writeStringUtf8( getText( ) );
    }

    @Override
    public AisAddressedSafetyRelatedMessageObject getDataObject( ) throws SQLException {
        return new AisAddressedSafetyRelatedMessageObject( ObjectState.Stored, getId( ), getRowVersion( ), getAisDevice( ), getReceivedTimestamp( ), getMessageSequenceNumber( ), getRepeat( ), getMmsi( ), getSequenceNumber( ), getDestinationMmsi( ), getRetransmitFlag( ), getSpare( ), getText( ) );
    }

}
