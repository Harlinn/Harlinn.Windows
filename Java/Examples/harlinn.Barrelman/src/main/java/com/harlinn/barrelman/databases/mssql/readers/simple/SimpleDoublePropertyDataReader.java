package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleDoublePropertyDataReader extends SimplePropertyDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  dp.[Id], \r\n" +
            "  dp.[EntityType], \r\n" +
            "  dp.[RowVersion], \r\n" +
            "  dp.[Element], \r\n" +
            "  dp.[Definition], \r\n" +
            "  dp.[Value] \r\n" +
            "FROM [DoublePropertyView] dp \r\n";

    public final static String BaseViewName = "DoublePropertyView";
    public final static String ViewAliasName = "dp";

    public final static int VALUE_FIELD_ID = 6;

    public SimpleDoublePropertyDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final double getValue() throws SQLException {
        return getDouble( VALUE_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeDouble( getValue( ) );
    }

    @Override
    public DoublePropertyObject GetDataObject( ) throws SQLException {
        return new DoublePropertyObject( ObjectState.Stored, getId( ), getRowVersion( ), getElement( ), getDefinition( ), getValue( ) );
    }

}
