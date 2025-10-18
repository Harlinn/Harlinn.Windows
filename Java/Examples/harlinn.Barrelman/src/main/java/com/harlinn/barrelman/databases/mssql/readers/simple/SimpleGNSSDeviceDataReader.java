package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleGNSSDeviceDataReader extends SimpleDeviceDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  g.[Id], \r\n" +
            "  g.[EntityType], \r\n" +
            "  g.[RowVersion], \r\n" +
            "  g.[Host], \r\n" +
            "  g.[Name], \r\n" +
            "  g.[Description], \r\n" +
            "  g.[EnabledTimeseries], \r\n" +
            "  g.[LatitudeTimeseries], \r\n" +
            "  g.[LongitudeTimeseries], \r\n" +
            "  g.[AltitudeTimeseries] \r\n" +
            "FROM [GNSSDeviceView] g \r\n";

    public final static String BaseViewName = "GNSSDeviceView";
    public final static String ViewAliasName = "g";

    public final static int LATITUDETIMESERIES_FIELD_ID = 8;
    public final static int LONGITUDETIMESERIES_FIELD_ID = 9;
    public final static int ALTITUDETIMESERIES_FIELD_ID = 10;

    public SimpleGNSSDeviceDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getLatitudeTimeseries() throws SQLException {
        return getNullableGuid( LATITUDETIMESERIES_FIELD_ID );
    }

    public final Guid getLongitudeTimeseries() throws SQLException {
        return getNullableGuid( LONGITUDETIMESERIES_FIELD_ID );
    }

    public final Guid getAltitudeTimeseries() throws SQLException {
        return getNullableGuid( ALTITUDETIMESERIES_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeNullableGuid( getLatitudeTimeseries( ) );
        destination.writeNullableGuid( getLongitudeTimeseries( ) );
        destination.writeNullableGuid( getAltitudeTimeseries( ) );
    }

    @Override
    public GNSSDeviceObject GetDataObject( ) throws SQLException {
        return new GNSSDeviceObject( ObjectState.Stored, getId( ), getRowVersion( ), getHost( ), getName( ), getDescription( ), getEnabledTimeseries( ), getLatitudeTimeseries( ), getLongitudeTimeseries( ), getAltitudeTimeseries( ) );
    }

}
