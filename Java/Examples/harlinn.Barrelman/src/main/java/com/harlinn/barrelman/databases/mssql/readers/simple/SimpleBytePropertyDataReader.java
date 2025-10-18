package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleBytePropertyDataReader extends SimplePropertyDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  byp.[Id], \r\n" +
            "  byp.[EntityType], \r\n" +
            "  byp.[RowVersion], \r\n" +
            "  byp.[Element], \r\n" +
            "  byp.[Definition], \r\n" +
            "  byp.[Value] \r\n" +
            "FROM [BytePropertyView] byp \r\n";

    public final static String BaseViewName = "BytePropertyView";
    public final static String ViewAliasName = "byp";

    public final static int VALUE_FIELD_ID = 6;

    public SimpleBytePropertyDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final byte getValue() throws SQLException {
        return getUInt8( VALUE_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeUInt8( getValue( ) );
    }

    @Override
    public BytePropertyObject GetDataObject( ) throws SQLException {
        return new BytePropertyObject( ObjectState.Stored, getId( ), getRowVersion( ), getElement( ), getDefinition( ), getValue( ) );
    }

}
