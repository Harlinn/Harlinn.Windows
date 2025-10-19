package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleReferenceTimeseriesDataReader extends SimpleTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  rt.[Id], \r\n" +
            "  rt.[EntityType], \r\n" +
            "  rt.[RowVersion], \r\n" +
            "  rt.[Catalog], \r\n" +
            "  rt.[Name], \r\n" +
            "  rt.[MaxRetention] \r\n" +
            "FROM [ReferenceTimeseriesView] rt \r\n";

    public final static String BaseViewName = "ReferenceTimeseriesView";
    public final static String ViewAliasName = "rt";

    public SimpleReferenceTimeseriesDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
    }

    @Override
    public ReferenceTimeseriesObject getDataObject( ) throws SQLException {
        return new ReferenceTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ) );
    }

}
