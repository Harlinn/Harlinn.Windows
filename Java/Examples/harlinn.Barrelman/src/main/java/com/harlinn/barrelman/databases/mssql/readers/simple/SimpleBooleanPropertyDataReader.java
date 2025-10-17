package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleBooleanPropertyDataReader extends SimplePropertyDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  bop.[Id], \r\n" +
            "  bop.[EntityType], \r\n" +
            "  bop.[RowVersion], \r\n" +
            "  bop.[Element], \r\n" +
            "  bop.[Definition], \r\n" +
            "  bop.[Value] \r\n" +
            "FROM [BooleanPropertyView] bop \r\n";

    public final static String BaseViewName = "BooleanPropertyView";
    public final static String ViewAliasName = "bop";

    public final static int VALUE_FIELD_ID = 6;

    public SimpleBooleanPropertyDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final boolean getValue() throws SQLException {
        return getBoolean( VALUE_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeBoolean( getValue( ) );
    }

}
