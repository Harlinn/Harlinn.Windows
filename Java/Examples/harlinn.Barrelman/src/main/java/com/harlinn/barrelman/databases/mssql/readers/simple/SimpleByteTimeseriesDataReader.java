package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleByteTimeseriesDataReader extends SimpleTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  byts.[Id], \r\n" +
            "  byts.[EntityType], \r\n" +
            "  byts.[RowVersion], \r\n" +
            "  byts.[Catalog], \r\n" +
            "  byts.[Name], \r\n" +
            "  byts.[MaxRetention] \r\n" +
            "FROM [ByteTimeseriesView] byts \r\n";

    public final static String BaseViewName = "ByteTimeseriesView";
    public final static String ViewAliasName = "byts";

    public SimpleByteTimeseriesDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
    }

    @Override
    public ByteTimeseriesObject getDataObject( ) throws SQLException {
        return new ByteTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ) );
    }

}
