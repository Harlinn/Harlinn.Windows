package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleStringTimeseriesDataReader extends SimpleTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  stts.[Id], \r\n" +
            "  stts.[EntityType], \r\n" +
            "  stts.[RowVersion], \r\n" +
            "  stts.[Catalog], \r\n" +
            "  stts.[Name], \r\n" +
            "  stts.[MaxRetention] \r\n" +
            "FROM [StringTimeseriesView] stts \r\n";

    public final static String BaseViewName = "StringTimeseriesView";
    public final static String ViewAliasName = "stts";

    public SimpleStringTimeseriesDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
    }

    @Override
    public StringTimeseriesObject getDataObject( ) throws SQLException {
        return new StringTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ) );
    }

}
