package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleAisInterrogationMessageDataReader extends SimpleAisMessageDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  aim.[Id], \r\n" +
            "  aim.[EntityType], \r\n" +
            "  aim.[RowVersion], \r\n" +
            "  aim.[AisDevice], \r\n" +
            "  aim.[ReceivedTimestamp], \r\n" +
            "  aim.[MessageSequenceNumber], \r\n" +
            "  aim.[Repeat], \r\n" +
            "  aim.[Mmsi], \r\n" +
            "  aim.[InterrogatedMmsi], \r\n" +
            "  aim.[FirstMessageType], \r\n" +
            "  aim.[FirstSlotOffset], \r\n" +
            "  aim.[SecondMessageType], \r\n" +
            "  aim.[SecondSlotOffset], \r\n" +
            "  aim.[SecondStationInterrogationMmsi], \r\n" +
            "  aim.[SecondStationFirstMessageType], \r\n" +
            "  aim.[SecondStationFirstSlotOffset] \r\n" +
            "FROM [AisInterrogationMessageView] aim \r\n";

    public final static String BaseViewName = "AisInterrogationMessageView";
    public final static String ViewAliasName = "aim";

    public final static int INTERROGATEDMMSI_FIELD_ID = 9;
    public final static int FIRSTMESSAGETYPE_FIELD_ID = 10;
    public final static int FIRSTSLOTOFFSET_FIELD_ID = 11;
    public final static int SECONDMESSAGETYPE_FIELD_ID = 12;
    public final static int SECONDSLOTOFFSET_FIELD_ID = 13;
    public final static int SECONDSTATIONINTERROGATIONMMSI_FIELD_ID = 14;
    public final static int SECONDSTATIONFIRSTMESSAGETYPE_FIELD_ID = 15;
    public final static int SECONDSTATIONFIRSTSLOTOFFSET_FIELD_ID = 16;

    public SimpleAisInterrogationMessageDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getInterrogatedMmsi() throws SQLException {
        return getNullableGuid( INTERROGATEDMMSI_FIELD_ID );
    }

    public final int getFirstMessageType() throws SQLException {
        return getInt32( FIRSTMESSAGETYPE_FIELD_ID );
    }

    public final int getFirstSlotOffset() throws SQLException {
        return getInt32( FIRSTSLOTOFFSET_FIELD_ID );
    }

    public final Integer getSecondMessageType() throws SQLException {
        return getNullableInt32( SECONDMESSAGETYPE_FIELD_ID );
    }

    public final Integer getSecondSlotOffset() throws SQLException {
        return getNullableInt32( SECONDSLOTOFFSET_FIELD_ID );
    }

    public final Guid getSecondStationInterrogationMmsi() throws SQLException {
        return getNullableGuid( SECONDSTATIONINTERROGATIONMMSI_FIELD_ID );
    }

    public final Integer getSecondStationFirstMessageType() throws SQLException {
        return getNullableInt32( SECONDSTATIONFIRSTMESSAGETYPE_FIELD_ID );
    }

    public final Integer getSecondStationFirstSlotOffset() throws SQLException {
        return getNullableInt32( SECONDSTATIONFIRSTSLOTOFFSET_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeNullableGuid( getInterrogatedMmsi( ) );
        destination.writeInt32( getFirstMessageType( ) );
        destination.writeInt32( getFirstSlotOffset( ) );
        destination.writeNullableInt32( getSecondMessageType( ) );
        destination.writeNullableInt32( getSecondSlotOffset( ) );
        destination.writeNullableGuid( getSecondStationInterrogationMmsi( ) );
        destination.writeNullableInt32( getSecondStationFirstMessageType( ) );
        destination.writeNullableInt32( getSecondStationFirstSlotOffset( ) );
    }

    @Override
    public AisInterrogationMessageObject GetDataObject( ) throws SQLException {
        return new AisInterrogationMessageObject( ObjectState.Stored, getId( ), getRowVersion( ), getAisDevice( ), getReceivedTimestamp( ), getMessageSequenceNumber( ), getRepeat( ), getMmsi( ), getInterrogatedMmsi( ), getFirstMessageType( ), getFirstSlotOffset( ), getSecondMessageType( ), getSecondSlotOffset( ), getSecondStationInterrogationMmsi( ), getSecondStationFirstMessageType( ), getSecondStationFirstSlotOffset( ) );
    }

}
