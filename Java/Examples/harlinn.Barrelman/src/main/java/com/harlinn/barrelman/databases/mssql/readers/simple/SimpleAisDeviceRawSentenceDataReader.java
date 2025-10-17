package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleAisDeviceRawSentenceDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  adrs.[Id], \r\n" +
            "  adrs.[RowVersion], \r\n" +
            "  adrs.[AisDevice], \r\n" +
            "  adrs.[Timestamp], \r\n" +
            "  adrs.[Sentence] \r\n" +
            "FROM [AisDeviceRawSentenceView] adrs \r\n";

    public final static String BaseViewName = "AisDeviceRawSentenceView";
    public final static String ViewAliasName = "adrs";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int AISDEVICE_FIELD_ID = 3;
    public final static int TIMESTAMP_FIELD_ID = 4;
    public final static int SENTENCE_FIELD_ID = 5;

    public SimpleAisDeviceRawSentenceDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final Guid getAisDevice() throws SQLException {
        return getGuid( AISDEVICE_FIELD_ID );
    }

    public final DateTime getTimestamp() throws SQLException {
        return getDateTimeFromLong( TIMESTAMP_FIELD_ID );
    }

    public final String getSentence() throws SQLException {
        return getString( SENTENCE_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.AisDeviceRawSentence );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getAisDevice( ) );
        destination.writeDateTime( getTimestamp( ) );
        destination.writeStringUtf8( getSentence( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

}
