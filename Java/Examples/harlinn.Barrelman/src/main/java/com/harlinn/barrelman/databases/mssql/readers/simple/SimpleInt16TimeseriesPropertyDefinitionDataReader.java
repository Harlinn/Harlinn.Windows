package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleInt16TimeseriesPropertyDefinitionDataReader extends SimpleTimeseriesPropertyDefinitionDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  i16tpd.[Id], \r\n" +
            "  i16tpd.[EntityType], \r\n" +
            "  i16tpd.[RowVersion], \r\n" +
            "  i16tpd.[ElementType], \r\n" +
            "  i16tpd.[Name], \r\n" +
            "  i16tpd.[Description], \r\n" +
            "  i16tpd.[MinValue], \r\n" +
            "  i16tpd.[MaxValue] \r\n" +
            "FROM [Int16TimeseriesPropertyDefinitionView] i16tpd \r\n";

    public final static String BaseViewName = "Int16TimeseriesPropertyDefinitionView";
    public final static String ViewAliasName = "i16tpd";

    public final static int MINVALUE_FIELD_ID = 7;
    public final static int MAXVALUE_FIELD_ID = 8;

    public SimpleInt16TimeseriesPropertyDefinitionDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final short getMinValue() throws SQLException {
        return getInt16( MINVALUE_FIELD_ID );
    }

    public final short getMaxValue() throws SQLException {
        return getInt16( MAXVALUE_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeInt16( getMinValue( ) );
        destination.writeInt16( getMaxValue( ) );
    }

    @Override
    public Int16TimeseriesPropertyDefinitionObject getDataObject( ) throws SQLException {
        return new Int16TimeseriesPropertyDefinitionObject( ObjectState.Stored, getId( ), getRowVersion( ), getElementType( ), getName( ), getDescription( ), getMinValue( ), getMaxValue( ) );
    }

}
