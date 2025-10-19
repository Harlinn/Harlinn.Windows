package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleUInt16PropertyDataReader extends SimplePropertyDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  u16p.[Id], \r\n" +
            "  u16p.[EntityType], \r\n" +
            "  u16p.[RowVersion], \r\n" +
            "  u16p.[Element], \r\n" +
            "  u16p.[Definition], \r\n" +
            "  u16p.[Value] \r\n" +
            "FROM [UInt16PropertyView] u16p \r\n";

    public final static String BaseViewName = "UInt16PropertyView";
    public final static String ViewAliasName = "u16p";

    public final static int VALUE_FIELD_ID = 6;

    public SimpleUInt16PropertyDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final short getValue() throws SQLException {
        return getUInt16( VALUE_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeUInt16( getValue( ) );
    }

    @Override
    public UInt16PropertyObject getDataObject( ) throws SQLException {
        return new UInt16PropertyObject( ObjectState.Stored, getId( ), getRowVersion( ), getElement( ), getDefinition( ), getValue( ) );
    }

}
