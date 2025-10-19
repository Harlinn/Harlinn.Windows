package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleGuidPropertyDataReader extends SimplePropertyDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  gp.[Id], \r\n" +
            "  gp.[EntityType], \r\n" +
            "  gp.[RowVersion], \r\n" +
            "  gp.[Element], \r\n" +
            "  gp.[Definition], \r\n" +
            "  gp.[Value] \r\n" +
            "FROM [GuidPropertyView] gp \r\n";

    public final static String BaseViewName = "GuidPropertyView";
    public final static String ViewAliasName = "gp";

    public final static int VALUE_FIELD_ID = 6;

    public SimpleGuidPropertyDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getValue() throws SQLException {
        return getGuid( VALUE_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeGuid( getValue( ) );
    }

    @Override
    public GuidPropertyObject getDataObject( ) throws SQLException {
        return new GuidPropertyObject( ObjectState.Stored, getId( ), getRowVersion( ), getElement( ), getDefinition( ), getValue( ) );
    }

}
