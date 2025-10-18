package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleRadomeTemperatureTimeseriesDataReader extends SimpleDoubleTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  rtets.[Id], \r\n" +
            "  rtets.[EntityType], \r\n" +
            "  rtets.[RowVersion], \r\n" +
            "  rtets.[Catalog], \r\n" +
            "  rtets.[Name], \r\n" +
            "  rtets.[MaxRetention], \r\n" +
            "  rtets.[Radome] \r\n" +
            "FROM [RadomeTemperatureTimeseriesView] rtets \r\n";

    public final static String BaseViewName = "RadomeTemperatureTimeseriesView";
    public final static String ViewAliasName = "rtets";

    public final static int RADOME_FIELD_ID = 7;

    public SimpleRadomeTemperatureTimeseriesDataReader( ResultSet resultSet ) {
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
    public RadomeTemperatureTimeseriesObject GetDataObject( ) throws SQLException {
        return new RadomeTemperatureTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getRadome( ) );
    }

}
