package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleInt64TimeseriesPropertyDefinitionDataReader extends SimpleTimeseriesPropertyDefinitionDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  i64tpd.[Id], \r\n" +
            "  i64tpd.[EntityType], \r\n" +
            "  i64tpd.[RowVersion], \r\n" +
            "  i64tpd.[ElementType], \r\n" +
            "  i64tpd.[Name], \r\n" +
            "  i64tpd.[Description], \r\n" +
            "  i64tpd.[MinValue], \r\n" +
            "  i64tpd.[MaxValue] \r\n" +
            "FROM [Int64TimeseriesPropertyDefinitionView] i64tpd \r\n";

    public final static String BaseViewName = "Int64TimeseriesPropertyDefinitionView";
    public final static String ViewAliasName = "i64tpd";

    public final static int MINVALUE_FIELD_ID = 7;
    public final static int MAXVALUE_FIELD_ID = 8;

    public SimpleInt64TimeseriesPropertyDefinitionDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final long getMinValue() throws SQLException {
        return getInt64( MINVALUE_FIELD_ID );
    }

    public final long getMaxValue() throws SQLException {
        return getInt64( MAXVALUE_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeInt64( getMinValue( ) );
        destination.writeInt64( getMaxValue( ) );
    }

    @Override
    public Int64TimeseriesPropertyDefinitionObject getDataObject( ) throws SQLException {
        return new Int64TimeseriesPropertyDefinitionObject( ObjectState.Stored, getId( ), getRowVersion( ), getElementType( ), getName( ), getDescription( ), getMinValue( ), getMaxValue( ) );
    }

}
