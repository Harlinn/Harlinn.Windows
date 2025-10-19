package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleInt16TimeseriesDataReader extends SimpleTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  i16t.[Id], \r\n" +
            "  i16t.[EntityType], \r\n" +
            "  i16t.[RowVersion], \r\n" +
            "  i16t.[Catalog], \r\n" +
            "  i16t.[Name], \r\n" +
            "  i16t.[MaxRetention] \r\n" +
            "FROM [Int16TimeseriesView] i16t \r\n";

    public final static String BaseViewName = "Int16TimeseriesView";
    public final static String ViewAliasName = "i16t";

    public SimpleInt16TimeseriesDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
    }

    @Override
    public Int16TimeseriesObject getDataObject( ) throws SQLException {
        return new Int16TimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ) );
    }

}
