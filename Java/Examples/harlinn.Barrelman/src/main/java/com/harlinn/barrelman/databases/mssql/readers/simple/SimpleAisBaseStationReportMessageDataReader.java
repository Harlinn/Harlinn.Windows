package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleAisBaseStationReportMessageDataReader extends SimpleAisMessageDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  absrm.[Id], \r\n" +
            "  absrm.[EntityType], \r\n" +
            "  absrm.[RowVersion], \r\n" +
            "  absrm.[AisDevice], \r\n" +
            "  absrm.[ReceivedTimestamp], \r\n" +
            "  absrm.[MessageSequenceNumber], \r\n" +
            "  absrm.[Repeat], \r\n" +
            "  absrm.[Mmsi], \r\n" +
            "  absrm.[Timestamp], \r\n" +
            "  absrm.[PositionAccuracy], \r\n" +
            "  absrm.[Longitude], \r\n" +
            "  absrm.[Latitude], \r\n" +
            "  absrm.[PositionFixType], \r\n" +
            "  absrm.[Spare], \r\n" +
            "  absrm.[Raim], \r\n" +
            "  absrm.[RadioStatus] \r\n" +
            "FROM [AisBaseStationReportMessageView] absrm \r\n";

    public final static String BaseViewName = "AisBaseStationReportMessageView";
    public final static String ViewAliasName = "absrm";

    public final static int TIMESTAMP_FIELD_ID = 9;
    public final static int POSITIONACCURACY_FIELD_ID = 10;
    public final static int LONGITUDE_FIELD_ID = 11;
    public final static int LATITUDE_FIELD_ID = 12;
    public final static int POSITIONFIXTYPE_FIELD_ID = 13;
    public final static int SPARE_FIELD_ID = 14;
    public final static int RAIM_FIELD_ID = 15;
    public final static int RADIOSTATUS_FIELD_ID = 16;

    public SimpleAisBaseStationReportMessageDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final DateTime getTimestamp() throws SQLException {
        return getDateTimeFromLong( TIMESTAMP_FIELD_ID );
    }

    public final int getPositionAccuracy() throws SQLException {
        return getInt32( POSITIONACCURACY_FIELD_ID );
    }

    public final double getLongitude() throws SQLException {
        return getDouble( LONGITUDE_FIELD_ID );
    }

    public final double getLatitude() throws SQLException {
        return getDouble( LATITUDE_FIELD_ID );
    }

    public final int getPositionFixType() throws SQLException {
        return getInt32( POSITIONFIXTYPE_FIELD_ID );
    }

    public final int getSpare() throws SQLException {
        return getInt32( SPARE_FIELD_ID );
    }

    public final int getRaim() throws SQLException {
        return getInt32( RAIM_FIELD_ID );
    }

    public final int getRadioStatus() throws SQLException {
        return getInt32( RADIOSTATUS_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeDateTime( getTimestamp( ) );
        destination.writeInt32( getPositionAccuracy( ) );
        destination.writeDouble( getLongitude( ) );
        destination.writeDouble( getLatitude( ) );
        destination.writeInt32( getPositionFixType( ) );
        destination.writeInt32( getSpare( ) );
        destination.writeInt32( getRaim( ) );
        destination.writeInt32( getRadioStatus( ) );
    }

    @Override
    public AisBaseStationReportMessageObject GetDataObject( ) throws SQLException {
        return new AisBaseStationReportMessageObject( ObjectState.Stored, getId( ), getRowVersion( ), getAisDevice( ), getReceivedTimestamp( ), getMessageSequenceNumber( ), getRepeat( ), getMmsi( ), getTimestamp( ), getPositionAccuracy( ), getLongitude( ), getLatitude( ), getPositionFixType( ), getSpare( ), getRaim( ), getRadioStatus( ) );
    }

}
