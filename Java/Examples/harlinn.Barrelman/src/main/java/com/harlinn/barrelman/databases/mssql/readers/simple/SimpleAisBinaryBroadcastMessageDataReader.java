package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleAisBinaryBroadcastMessageDataReader extends SimpleAisMessageDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  abbm.[Id], \r\n" +
            "  abbm.[EntityType], \r\n" +
            "  abbm.[RowVersion], \r\n" +
            "  abbm.[AisDevice], \r\n" +
            "  abbm.[ReceivedTimestamp], \r\n" +
            "  abbm.[MessageSequenceNumber], \r\n" +
            "  abbm.[Repeat], \r\n" +
            "  abbm.[Mmsi], \r\n" +
            "  abbm.[Spare], \r\n" +
            "  abbm.[DesignatedAreaCode], \r\n" +
            "  abbm.[FunctionalId], \r\n" +
            "  abbm.[Data] \r\n" +
            "FROM [AisBinaryBroadcastMessageView] abbm \r\n";

    public final static String BaseViewName = "AisBinaryBroadcastMessageView";
    public final static String ViewAliasName = "abbm";

    public final static int SPARE_FIELD_ID = 9;
    public final static int DESIGNATEDAREACODE_FIELD_ID = 10;
    public final static int FUNCTIONALID_FIELD_ID = 11;
    public final static int DATA_FIELD_ID = 12;

    public SimpleAisBinaryBroadcastMessageDataReader( ResultSet resultSet ) {
        super( resultSet );
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
        destination.writeInt32( getSpare( ) );
        destination.writeInt32( getDesignatedAreaCode( ) );
        destination.writeInt32( getFunctionalId( ) );
        destination.writeStringUtf8( getData( ) );
    }

}
