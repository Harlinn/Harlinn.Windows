package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleInt32PropertyDataReader extends SimplePropertyDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  i32p.[Id], \r\n" +
            "  i32p.[EntityType], \r\n" +
            "  i32p.[RowVersion], \r\n" +
            "  i32p.[Element], \r\n" +
            "  i32p.[Definition], \r\n" +
            "  i32p.[Value] \r\n" +
            "FROM [Int32PropertyView] i32p \r\n";

    public final static String BaseViewName = "Int32PropertyView";
    public final static String ViewAliasName = "i32p";

    public final static int VALUE_FIELD_ID = 6;

    public SimpleInt32PropertyDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final int getValue() throws SQLException {
        return getInt32( VALUE_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeInt32( getValue( ) );
    }

    @Override
    public Int32PropertyObject getDataObject( ) throws SQLException {
        return new Int32PropertyObject( ObjectState.Stored, getId( ), getRowVersion( ), getElement( ), getDefinition( ), getValue( ) );
    }

}
