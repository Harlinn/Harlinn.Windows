package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleSinglePropertyDataReader extends SimplePropertyDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  sip.[Id], \r\n" +
            "  sip.[EntityType], \r\n" +
            "  sip.[RowVersion], \r\n" +
            "  sip.[Element], \r\n" +
            "  sip.[Definition], \r\n" +
            "  sip.[Value] \r\n" +
            "FROM [SinglePropertyView] sip \r\n";

    public final static String BaseViewName = "SinglePropertyView";
    public final static String ViewAliasName = "sip";

    public final static int VALUE_FIELD_ID = 6;

    public SimpleSinglePropertyDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final float getValue() throws SQLException {
        return getSingle( VALUE_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeSingle( getValue( ) );
    }

    @Override
    public SinglePropertyObject getDataObject( ) throws SQLException {
        return new SinglePropertyObject( ObjectState.Stored, getId( ), getRowVersion( ), getElement( ), getDefinition( ), getValue( ) );
    }

}
