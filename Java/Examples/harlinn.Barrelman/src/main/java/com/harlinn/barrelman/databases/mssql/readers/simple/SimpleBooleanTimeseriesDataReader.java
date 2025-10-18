package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleBooleanTimeseriesDataReader extends SimpleTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  bots.[Id], \r\n" +
            "  bots.[EntityType], \r\n" +
            "  bots.[RowVersion], \r\n" +
            "  bots.[Catalog], \r\n" +
            "  bots.[Name], \r\n" +
            "  bots.[MaxRetention] \r\n" +
            "FROM [BooleanTimeseriesView] bots \r\n";

    public final static String BaseViewName = "BooleanTimeseriesView";
    public final static String ViewAliasName = "bots";

    public SimpleBooleanTimeseriesDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
    }

    @Override
    public BooleanTimeseriesObject GetDataObject( ) throws SQLException {
        return new BooleanTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ) );
    }

}
