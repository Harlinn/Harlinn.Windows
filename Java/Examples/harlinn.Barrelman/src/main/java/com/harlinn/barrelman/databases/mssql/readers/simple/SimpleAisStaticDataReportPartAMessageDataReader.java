package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleAisStaticDataReportPartAMessageDataReader extends SimpleAisStaticDataReportMessageDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  asdrpa.[Id], \r\n" +
            "  asdrpa.[EntityType], \r\n" +
            "  asdrpa.[RowVersion], \r\n" +
            "  asdrpa.[AisDevice], \r\n" +
            "  asdrpa.[ReceivedTimestamp], \r\n" +
            "  asdrpa.[MessageSequenceNumber], \r\n" +
            "  asdrpa.[Repeat], \r\n" +
            "  asdrpa.[Mmsi], \r\n" +
            "  asdrpa.[PartNumber], \r\n" +
            "  asdrpa.[ShipName], \r\n" +
            "  asdrpa.[Spare] \r\n" +
            "FROM [AisStaticDataReportPartAMessageView] asdrpa \r\n";

    public final static String BaseViewName = "AisStaticDataReportPartAMessageView";
    public final static String ViewAliasName = "asdrpa";

    public final static int SHIPNAME_FIELD_ID = 10;
    public final static int SPARE_FIELD_ID = 11;

    public SimpleAisStaticDataReportPartAMessageDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getShipName() throws SQLException {
        return getNullableGuid( SHIPNAME_FIELD_ID );
    }

    public final int getSpare() throws SQLException {
        return getInt32( SPARE_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeNullableGuid( getShipName( ) );
        destination.writeInt32( getSpare( ) );
    }

    @Override
    public AisStaticDataReportPartAMessageObject GetDataObject( ) throws SQLException {
        return new AisStaticDataReportPartAMessageObject( ObjectState.Stored, getId( ), getRowVersion( ), getAisDevice( ), getReceivedTimestamp( ), getMessageSequenceNumber( ), getRepeat( ), getMmsi( ), getPartNumber( ), getShipName( ), getSpare( ) );
    }

}
