package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleSingleTimeseriesDataReader extends SimpleTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  sits.[Id], \r\n" +
            "  sits.[EntityType], \r\n" +
            "  sits.[RowVersion], \r\n" +
            "  sits.[Catalog], \r\n" +
            "  sits.[Name], \r\n" +
            "  sits.[MaxRetention] \r\n" +
            "FROM [SingleTimeseriesView] sits \r\n";

    public final static String BaseViewName = "SingleTimeseriesView";
    public final static String ViewAliasName = "sits";

    public SimpleSingleTimeseriesDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
    }

    @Override
    public SingleTimeseriesObject getDataObject( ) throws SQLException {
        return new SingleTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ) );
    }

}
