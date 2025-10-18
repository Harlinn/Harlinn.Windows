package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleDoubleTimeseriesDataReader extends SimpleTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  dt.[Id], \r\n" +
            "  dt.[EntityType], \r\n" +
            "  dt.[RowVersion], \r\n" +
            "  dt.[Catalog], \r\n" +
            "  dt.[Name], \r\n" +
            "  dt.[MaxRetention] \r\n" +
            "FROM [DoubleTimeseriesView] dt \r\n";

    public final static String BaseViewName = "DoubleTimeseriesView";
    public final static String ViewAliasName = "dt";

    public SimpleDoubleTimeseriesDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
    }

    @Override
    public DoubleTimeseriesObject GetDataObject( ) throws SQLException {
        return new DoubleTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ) );
    }

}
