package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleUInt64TimeseriesPropertyDefinitionDataReader extends SimpleTimeseriesPropertyDefinitionDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  u64tpd.[Id], \r\n" +
            "  u64tpd.[EntityType], \r\n" +
            "  u64tpd.[RowVersion], \r\n" +
            "  u64tpd.[ElementType], \r\n" +
            "  u64tpd.[Name], \r\n" +
            "  u64tpd.[Description], \r\n" +
            "  u64tpd.[MinValue], \r\n" +
            "  u64tpd.[MaxValue] \r\n" +
            "FROM [UInt64TimeseriesPropertyDefinitionView] u64tpd \r\n";

    public final static String BaseViewName = "UInt64TimeseriesPropertyDefinitionView";
    public final static String ViewAliasName = "u64tpd";

    public final static int MINVALUE_FIELD_ID = 7;
    public final static int MAXVALUE_FIELD_ID = 8;

    public SimpleUInt64TimeseriesPropertyDefinitionDataReader( ResultSet resultSet ) {
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
    public UInt64TimeseriesPropertyDefinitionObject GetDataObject( ) throws SQLException {
        return new UInt64TimeseriesPropertyDefinitionObject( ObjectState.Stored, getId( ), getRowVersion( ), getElementType( ), getName( ), getDescription( ), getMinValue( ), getMaxValue( ) );
    }

}
