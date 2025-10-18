package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleAisUtcAndDateInquiryMessageDataReader extends SimpleAisMessageDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  auadim.[Id], \r\n" +
            "  auadim.[EntityType], \r\n" +
            "  auadim.[RowVersion], \r\n" +
            "  auadim.[AisDevice], \r\n" +
            "  auadim.[ReceivedTimestamp], \r\n" +
            "  auadim.[MessageSequenceNumber], \r\n" +
            "  auadim.[Repeat], \r\n" +
            "  auadim.[Mmsi], \r\n" +
            "  auadim.[Spare1], \r\n" +
            "  auadim.[DestinationMmsi], \r\n" +
            "  auadim.[Spare2] \r\n" +
            "FROM [AisUtcAndDateInquiryMessageView] auadim \r\n";

    public final static String BaseViewName = "AisUtcAndDateInquiryMessageView";
    public final static String ViewAliasName = "auadim";

    public final static int SPARE1_FIELD_ID = 9;
    public final static int DESTINATIONMMSI_FIELD_ID = 10;
    public final static int SPARE2_FIELD_ID = 11;

    public SimpleAisUtcAndDateInquiryMessageDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final int getSpare1() throws SQLException {
        return getInt32( SPARE1_FIELD_ID );
    }

    public final Guid getDestinationMmsi() throws SQLException {
        return getNullableGuid( DESTINATIONMMSI_FIELD_ID );
    }

    public final int getSpare2() throws SQLException {
        return getInt32( SPARE2_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeInt32( getSpare1( ) );
        destination.writeNullableGuid( getDestinationMmsi( ) );
        destination.writeInt32( getSpare2( ) );
    }

    @Override
    public AisUtcAndDateInquiryMessageObject GetDataObject( ) throws SQLException {
        return new AisUtcAndDateInquiryMessageObject( ObjectState.Stored, getId( ), getRowVersion( ), getAisDevice( ), getReceivedTimestamp( ), getMessageSequenceNumber( ), getRepeat( ), getMmsi( ), getSpare1( ), getDestinationMmsi( ), getSpare2( ) );
    }

}
