package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleByteTimeseriesPropertyDefinitionDataReader extends SimpleTimeseriesPropertyDefinitionDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  bytpd.[Id], \r\n" +
            "  bytpd.[EntityType], \r\n" +
            "  bytpd.[RowVersion], \r\n" +
            "  bytpd.[ElementType], \r\n" +
            "  bytpd.[Name], \r\n" +
            "  bytpd.[Description], \r\n" +
            "  bytpd.[MinValue], \r\n" +
            "  bytpd.[MaxValue] \r\n" +
            "FROM [ByteTimeseriesPropertyDefinitionView] bytpd \r\n";

    public final static String BaseViewName = "ByteTimeseriesPropertyDefinitionView";
    public final static String ViewAliasName = "bytpd";

    public final static int MINVALUE_FIELD_ID = 7;
    public final static int MAXVALUE_FIELD_ID = 8;

    public SimpleByteTimeseriesPropertyDefinitionDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final byte getMinValue() throws SQLException {
        return getUInt8( MINVALUE_FIELD_ID );
    }

    public final byte getMaxValue() throws SQLException {
        return getUInt8( MAXVALUE_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeUInt8( getMinValue( ) );
        destination.writeUInt8( getMaxValue( ) );
    }

    @Override
    public ByteTimeseriesPropertyDefinitionObject GetDataObject( ) throws SQLException {
        return new ByteTimeseriesPropertyDefinitionObject( ObjectState.Stored, getId( ), getRowVersion( ), getElementType( ), getName( ), getDescription( ), getMinValue( ), getMaxValue( ) );
    }

}
