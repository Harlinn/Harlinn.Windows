package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleViewZoomLevelTimeseriesDataReader extends SimpleDoubleTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  vzlt.[Id], \r\n" +
            "  vzlt.[EntityType], \r\n" +
            "  vzlt.[RowVersion], \r\n" +
            "  vzlt.[Catalog], \r\n" +
            "  vzlt.[Name], \r\n" +
            "  vzlt.[MaxRetention], \r\n" +
            "  vzlt.[View] \r\n" +
            "FROM [ViewZoomLevelTimeseriesView] vzlt \r\n";

    public final static String BaseViewName = "ViewZoomLevelTimeseriesView";
    public final static String ViewAliasName = "vzlt";

    public final static int VIEW_FIELD_ID = 7;

    public SimpleViewZoomLevelTimeseriesDataReader( ResultSet resultSet ) {
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
    public ViewZoomLevelTimeseriesObject getDataObject( ) throws SQLException {
        return new ViewZoomLevelTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getView( ) );
    }

}
