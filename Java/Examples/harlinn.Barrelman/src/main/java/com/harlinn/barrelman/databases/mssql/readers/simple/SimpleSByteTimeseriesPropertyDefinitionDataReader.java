package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleSByteTimeseriesPropertyDefinitionDataReader extends SimpleTimeseriesPropertyDefinitionDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  sbtpd.[Id], \r\n" +
            "  sbtpd.[EntityType], \r\n" +
            "  sbtpd.[RowVersion], \r\n" +
            "  sbtpd.[ElementType], \r\n" +
            "  sbtpd.[Name], \r\n" +
            "  sbtpd.[Description], \r\n" +
            "  sbtpd.[MinValue], \r\n" +
            "  sbtpd.[MaxValue] \r\n" +
            "FROM [SByteTimeseriesPropertyDefinitionView] sbtpd \r\n";

    public final static String BaseViewName = "SByteTimeseriesPropertyDefinitionView";
    public final static String ViewAliasName = "sbtpd";

    public final static int MINVALUE_FIELD_ID = 7;
    public final static int MAXVALUE_FIELD_ID = 8;

    public SimpleSByteTimeseriesPropertyDefinitionDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final byte getMinValue() throws SQLException {
        return getInt8( MINVALUE_FIELD_ID );
    }

    public final byte getMaxValue() throws SQLException {
        return getInt8( MAXVALUE_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeInt8( getMinValue( ) );
        destination.writeInt8( getMaxValue( ) );
    }

    @Override
    public SByteTimeseriesPropertyDefinitionObject getDataObject( ) throws SQLException {
        return new SByteTimeseriesPropertyDefinitionObject( ObjectState.Stored, getId( ), getRowVersion( ), getElementType( ), getName( ), getDescription( ), getMinValue( ), getMaxValue( ) );
    }

}
