package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleGuidTimeseriesDataReader extends SimpleTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  gt.[Id], \r\n" +
            "  gt.[EntityType], \r\n" +
            "  gt.[RowVersion], \r\n" +
            "  gt.[Catalog], \r\n" +
            "  gt.[Name], \r\n" +
            "  gt.[MaxRetention] \r\n" +
            "FROM [GuidTimeseriesView] gt \r\n";

    public final static String BaseViewName = "GuidTimeseriesView";
    public final static String ViewAliasName = "gt";

    public SimpleGuidTimeseriesDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
    }

    @Override
    public GuidTimeseriesObject getDataObject( ) throws SQLException {
        return new GuidTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ) );
    }

}
