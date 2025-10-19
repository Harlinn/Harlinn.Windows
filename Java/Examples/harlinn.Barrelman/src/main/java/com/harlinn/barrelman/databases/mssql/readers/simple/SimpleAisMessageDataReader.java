package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public abstract class SimpleAisMessageDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  am.[Id], \r\n" +
            "  am.[EntityType], \r\n" +
            "  am.[RowVersion], \r\n" +
            "  am.[AisDevice], \r\n" +
            "  am.[ReceivedTimestamp], \r\n" +
            "  am.[MessageSequenceNumber], \r\n" +
            "  am.[Repeat], \r\n" +
            "  am.[Mmsi] \r\n" +
            "FROM [AisMessageView] am \r\n";

    public final static String BaseViewName = "AisMessageView";
    public final static String ViewAliasName = "am";

    public final static int ID_FIELD_ID = 1;
    public final static int ENTITYTYPE_FIELD_ID = 2;
    public final static int ROWVERSION_FIELD_ID = 3;
    public final static int AISDEVICE_FIELD_ID = 4;
    public final static int RECEIVEDTIMESTAMP_FIELD_ID = 5;
    public final static int MESSAGESEQUENCENUMBER_FIELD_ID = 6;
    public final static int REPEAT_FIELD_ID = 7;
    public final static int MMSI_FIELD_ID = 8;

    public SimpleAisMessageDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final int getObjectType() throws SQLException {
        return getInt32( ENTITYTYPE_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final Guid getAisDevice() throws SQLException {
        return getGuid( AISDEVICE_FIELD_ID );
    }

    public final DateTime getReceivedTimestamp() throws SQLException {
        return getDateTimeFromLong( RECEIVEDTIMESTAMP_FIELD_ID );
    }

    public final long getMessageSequenceNumber() throws SQLException {
        return getInt64( MESSAGESEQUENCENUMBER_FIELD_ID );
    }

    public final int getRepeat() throws SQLException {
        return getInt32( REPEAT_FIELD_ID );
    }

    public final Guid getMmsi() throws SQLException {
        return getNullableGuid( MMSI_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.AisMessage );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getAisDevice( ) );
        destination.writeDateTime( getReceivedTimestamp( ) );
        destination.writeInt64( getMessageSequenceNumber( ) );
        destination.writeInt32( getRepeat( ) );
        destination.writeNullableGuid( getMmsi( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

    public abstract AisMessageObject getDataObject( ) throws SQLException;

}
