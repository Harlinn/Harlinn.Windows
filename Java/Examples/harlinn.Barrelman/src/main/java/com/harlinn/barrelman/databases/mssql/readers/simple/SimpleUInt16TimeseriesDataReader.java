package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleUInt16TimeseriesDataReader extends SimpleTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  u16t.[Id], \r\n" +
            "  u16t.[EntityType], \r\n" +
            "  u16t.[RowVersion], \r\n" +
            "  u16t.[Catalog], \r\n" +
            "  u16t.[Name], \r\n" +
            "  u16t.[MaxRetention] \r\n" +
            "FROM [UInt16TimeseriesView] u16t \r\n";

    public final static String BaseViewName = "UInt16TimeseriesView";
    public final static String ViewAliasName = "u16t";

    public SimpleUInt16TimeseriesDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
    }

    @Override
    public UInt16TimeseriesObject GetDataObject( ) throws SQLException {
        return new UInt16TimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ) );
    }

}
