package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleReferencePropertyDataReader extends SimplePropertyDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  rp.[Id], \r\n" +
            "  rp.[EntityType], \r\n" +
            "  rp.[RowVersion], \r\n" +
            "  rp.[Element], \r\n" +
            "  rp.[Definition], \r\n" +
            "  rp.[Value] \r\n" +
            "FROM [ReferencePropertyView] rp \r\n";

    public final static String BaseViewName = "ReferencePropertyView";
    public final static String ViewAliasName = "rp";

    public final static int VALUE_FIELD_ID = 6;

    public SimpleReferencePropertyDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getValue() throws SQLException {
        return getNullableGuid( VALUE_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeNullableGuid( getValue( ) );
    }

    @Override
    public ReferencePropertyObject GetDataObject( ) throws SQLException {
        return new ReferencePropertyObject( ObjectState.Stored, getId( ), getRowVersion( ), getElement( ), getDefinition( ), getValue( ) );
    }

}
