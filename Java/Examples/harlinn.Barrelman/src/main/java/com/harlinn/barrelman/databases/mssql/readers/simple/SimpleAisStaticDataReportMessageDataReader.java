package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleAisStaticDataReportMessageDataReader extends SimpleAisMessageDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  asdrm.[Id], \r\n" +
            "  asdrm.[EntityType], \r\n" +
            "  asdrm.[RowVersion], \r\n" +
            "  asdrm.[AisDevice], \r\n" +
            "  asdrm.[ReceivedTimestamp], \r\n" +
            "  asdrm.[MessageSequenceNumber], \r\n" +
            "  asdrm.[Repeat], \r\n" +
            "  asdrm.[Mmsi], \r\n" +
            "  asdrm.[PartNumber] \r\n" +
            "FROM [AisStaticDataReportMessageView] asdrm \r\n";

    public final static String BaseViewName = "AisStaticDataReportMessageView";
    public final static String ViewAliasName = "asdrm";

    public final static int PARTNUMBER_FIELD_ID = 9;

    public SimpleAisStaticDataReportMessageDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final int getPartNumber() throws SQLException {
        return getInt32( PARTNUMBER_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeInt32( getPartNumber( ) );
    }

    @Override
    public AisStaticDataReportMessageObject GetDataObject( ) throws SQLException {
        return new AisStaticDataReportMessageObject( ObjectState.Stored, getId( ), getRowVersion( ), getAisDevice( ), getReceivedTimestamp( ), getMessageSequenceNumber( ), getRepeat( ), getMmsi( ), getPartNumber( ) );
    }

}
