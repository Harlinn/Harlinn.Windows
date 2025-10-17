package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleViewLongitudeTimeseriesDataReader extends SimpleDoubleTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  vlots.[Id], \r\n" +
            "  vlots.[EntityType], \r\n" +
            "  vlots.[RowVersion], \r\n" +
            "  vlots.[Catalog], \r\n" +
            "  vlots.[Name], \r\n" +
            "  vlots.[MaxRetention], \r\n" +
            "  vlots.[View] \r\n" +
            "FROM [ViewLongitudeTimeseriesView] vlots \r\n";

    public final static String BaseViewName = "ViewLongitudeTimeseriesView";
    public final static String ViewAliasName = "vlots";

    public final static int VIEW_FIELD_ID = 7;

    public SimpleViewLongitudeTimeseriesDataReader( ResultSet resultSet ) {
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

}
