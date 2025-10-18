package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleInt16PropertyDataReader extends SimplePropertyDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  i16p.[Id], \r\n" +
            "  i16p.[EntityType], \r\n" +
            "  i16p.[RowVersion], \r\n" +
            "  i16p.[Element], \r\n" +
            "  i16p.[Definition], \r\n" +
            "  i16p.[Value] \r\n" +
            "FROM [Int16PropertyView] i16p \r\n";

    public final static String BaseViewName = "Int16PropertyView";
    public final static String ViewAliasName = "i16p";

    public final static int VALUE_FIELD_ID = 6;

    public SimpleInt16PropertyDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final short getValue() throws SQLException {
        return getInt16( VALUE_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeInt16( getValue( ) );
    }

    @Override
    public Int16PropertyObject GetDataObject( ) throws SQLException {
        return new Int16PropertyObject( ObjectState.Stored, getId( ), getRowVersion( ), getElement( ), getDefinition( ), getValue( ) );
    }

}
