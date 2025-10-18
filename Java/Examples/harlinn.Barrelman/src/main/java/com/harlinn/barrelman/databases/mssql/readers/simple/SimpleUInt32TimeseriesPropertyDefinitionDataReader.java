package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleUInt32TimeseriesPropertyDefinitionDataReader extends SimpleTimeseriesPropertyDefinitionDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  u32tpd.[Id], \r\n" +
            "  u32tpd.[EntityType], \r\n" +
            "  u32tpd.[RowVersion], \r\n" +
            "  u32tpd.[ElementType], \r\n" +
            "  u32tpd.[Name], \r\n" +
            "  u32tpd.[Description], \r\n" +
            "  u32tpd.[MinValue], \r\n" +
            "  u32tpd.[MaxValue] \r\n" +
            "FROM [UInt32TimeseriesPropertyDefinitionView] u32tpd \r\n";

    public final static String BaseViewName = "UInt32TimeseriesPropertyDefinitionView";
    public final static String ViewAliasName = "u32tpd";

    public final static int MINVALUE_FIELD_ID = 7;
    public final static int MAXVALUE_FIELD_ID = 8;

    public SimpleUInt32TimeseriesPropertyDefinitionDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final int getMinValue() throws SQLException {
        return getUInt32( MINVALUE_FIELD_ID );
    }

    public final int getMaxValue() throws SQLException {
        return getUInt32( MAXVALUE_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeUInt32( getMinValue( ) );
        destination.writeUInt32( getMaxValue( ) );
    }

    @Override
    public UInt32TimeseriesPropertyDefinitionObject GetDataObject( ) throws SQLException {
        return new UInt32TimeseriesPropertyDefinitionObject( ObjectState.Stored, getId( ), getRowVersion( ), getElementType( ), getName( ), getDescription( ), getMinValue( ), getMaxValue( ) );
    }

}
