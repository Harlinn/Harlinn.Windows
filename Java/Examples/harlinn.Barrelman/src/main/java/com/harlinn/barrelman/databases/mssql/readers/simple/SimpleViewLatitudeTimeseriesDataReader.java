package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleViewLatitudeTimeseriesDataReader extends SimpleDoubleTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  vlats.[Id], \r\n" +
            "  vlats.[EntityType], \r\n" +
            "  vlats.[RowVersion], \r\n" +
            "  vlats.[Catalog], \r\n" +
            "  vlats.[Name], \r\n" +
            "  vlats.[MaxRetention], \r\n" +
            "  vlats.[View] \r\n" +
            "FROM [ViewLatitudeTimeseriesView] vlats \r\n";

    public final static String BaseViewName = "ViewLatitudeTimeseriesView";
    public final static String ViewAliasName = "vlats";

    public final static int VIEW_FIELD_ID = 7;

    public SimpleViewLatitudeTimeseriesDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getView() throws SQLException {
        return getNullableGuid( VIEW_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeNullableGuid( getView( ) );
    }

    @Override
    public ViewLatitudeTimeseriesObject GetDataObject( ) throws SQLException {
        return new ViewLatitudeTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getView( ) );
    }

}
