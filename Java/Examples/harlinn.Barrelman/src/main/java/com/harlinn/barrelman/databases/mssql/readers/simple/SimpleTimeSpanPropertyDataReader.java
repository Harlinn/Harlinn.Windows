package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleTimeSpanPropertyDataReader extends SimplePropertyDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  tsp.[Id], \r\n" +
            "  tsp.[EntityType], \r\n" +
            "  tsp.[RowVersion], \r\n" +
            "  tsp.[Element], \r\n" +
            "  tsp.[Definition], \r\n" +
            "  tsp.[Value] \r\n" +
            "FROM [TimeSpanPropertyView] tsp \r\n";

    public final static String BaseViewName = "TimeSpanPropertyView";
    public final static String ViewAliasName = "tsp";

    public final static int VALUE_FIELD_ID = 6;

    public SimpleTimeSpanPropertyDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final TimeSpan getValue() throws SQLException {
        return getTimeSpan( VALUE_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeTimeSpan( getValue( ) );
    }

}
