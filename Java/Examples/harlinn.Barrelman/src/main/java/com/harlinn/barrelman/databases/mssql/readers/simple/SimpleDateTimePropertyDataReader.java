package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleDateTimePropertyDataReader extends SimplePropertyDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  dtp.[Id], \r\n" +
            "  dtp.[EntityType], \r\n" +
            "  dtp.[RowVersion], \r\n" +
            "  dtp.[Element], \r\n" +
            "  dtp.[Definition], \r\n" +
            "  dtp.[Value] \r\n" +
            "FROM [DateTimePropertyView] dtp \r\n";

    public final static String BaseViewName = "DateTimePropertyView";
    public final static String ViewAliasName = "dtp";

    public final static int VALUE_FIELD_ID = 6;

    public SimpleDateTimePropertyDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final DateTime getValue() throws SQLException {
        return getDateTimeFromLong( VALUE_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeDateTime( getValue( ) );
    }

    @Override
    public DateTimePropertyObject getDataObject( ) throws SQLException {
        return new DateTimePropertyObject( ObjectState.Stored, getId( ), getRowVersion( ), getElement( ), getDefinition( ), getValue( ) );
    }

}
