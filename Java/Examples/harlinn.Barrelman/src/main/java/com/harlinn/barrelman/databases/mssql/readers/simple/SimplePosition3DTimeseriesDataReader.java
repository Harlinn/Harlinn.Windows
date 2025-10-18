package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimplePosition3DTimeseriesDataReader extends SimpleTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  p3d.[Id], \r\n" +
            "  p3d.[EntityType], \r\n" +
            "  p3d.[RowVersion], \r\n" +
            "  p3d.[Catalog], \r\n" +
            "  p3d.[Name], \r\n" +
            "  p3d.[MaxRetention] \r\n" +
            "FROM [Position3DTimeseriesView] p3d \r\n";

    public final static String BaseViewName = "Position3DTimeseriesView";
    public final static String ViewAliasName = "p3d";

    public SimplePosition3DTimeseriesDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
    }

    @Override
    public Position3DTimeseriesObject GetDataObject( ) throws SQLException {
        return new Position3DTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ) );
    }

}
