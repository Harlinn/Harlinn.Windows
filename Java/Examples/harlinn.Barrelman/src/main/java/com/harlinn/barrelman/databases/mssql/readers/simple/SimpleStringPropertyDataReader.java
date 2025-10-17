package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleStringPropertyDataReader extends SimplePropertyDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  stp.[Id], \r\n" +
            "  stp.[EntityType], \r\n" +
            "  stp.[RowVersion], \r\n" +
            "  stp.[Element], \r\n" +
            "  stp.[Definition], \r\n" +
            "  stp.[Value] \r\n" +
            "FROM [StringPropertyView] stp \r\n";

    public final static String BaseViewName = "StringPropertyView";
    public final static String ViewAliasName = "stp";

    public final static int VALUE_FIELD_ID = 6;

    public SimpleStringPropertyDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final String getValue() throws SQLException {
        return getString( VALUE_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeStringUtf8( getValue( ) );
    }

}
