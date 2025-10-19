package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleRadomePressureTimeseriesDataReader extends SimpleDoubleTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  rpt.[Id], \r\n" +
            "  rpt.[EntityType], \r\n" +
            "  rpt.[RowVersion], \r\n" +
            "  rpt.[Catalog], \r\n" +
            "  rpt.[Name], \r\n" +
            "  rpt.[MaxRetention], \r\n" +
            "  rpt.[Radome] \r\n" +
            "FROM [RadomePressureTimeseriesView] rpt \r\n";

    public final static String BaseViewName = "RadomePressureTimeseriesView";
    public final static String ViewAliasName = "rpt";

    public final static int RADOME_FIELD_ID = 7;

    public SimpleRadomePressureTimeseriesDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getRadome() throws SQLException {
        return getNullableGuid( RADOME_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeNullableGuid( getRadome( ) );
    }

    @Override
    public RadomePressureTimeseriesObject getDataObject( ) throws SQLException {
        return new RadomePressureTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getRadome( ) );
    }

}
