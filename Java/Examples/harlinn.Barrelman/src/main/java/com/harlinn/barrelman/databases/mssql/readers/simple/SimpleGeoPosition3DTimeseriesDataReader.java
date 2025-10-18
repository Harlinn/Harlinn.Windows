package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleGeoPosition3DTimeseriesDataReader extends SimpleTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  gp3d.[Id], \r\n" +
            "  gp3d.[EntityType], \r\n" +
            "  gp3d.[RowVersion], \r\n" +
            "  gp3d.[Catalog], \r\n" +
            "  gp3d.[Name], \r\n" +
            "  gp3d.[MaxRetention] \r\n" +
            "FROM [GeoPosition3DTimeseriesView] gp3d \r\n";

    public final static String BaseViewName = "GeoPosition3DTimeseriesView";
    public final static String ViewAliasName = "gp3d";

    public SimpleGeoPosition3DTimeseriesDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
    }

    @Override
    public GeoPosition3DTimeseriesObject GetDataObject( ) throws SQLException {
        return new GeoPosition3DTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ) );
    }

}
