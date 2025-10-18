package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleDoubleTimeseriesPropertyDefinitionDataReader extends SimpleTimeseriesPropertyDefinitionDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  dotpd.[Id], \r\n" +
            "  dotpd.[EntityType], \r\n" +
            "  dotpd.[RowVersion], \r\n" +
            "  dotpd.[ElementType], \r\n" +
            "  dotpd.[Name], \r\n" +
            "  dotpd.[Description], \r\n" +
            "  dotpd.[MinValue], \r\n" +
            "  dotpd.[MaxValue] \r\n" +
            "FROM [DoubleTimeseriesPropertyDefinitionView] dotpd \r\n";

    public final static String BaseViewName = "DoubleTimeseriesPropertyDefinitionView";
    public final static String ViewAliasName = "dotpd";

    public final static int MINVALUE_FIELD_ID = 7;
    public final static int MAXVALUE_FIELD_ID = 8;

    public SimpleDoubleTimeseriesPropertyDefinitionDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final double getMinValue() throws SQLException {
        return getDouble( MINVALUE_FIELD_ID );
    }

    public final double getMaxValue() throws SQLException {
        return getDouble( MAXVALUE_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeDouble( getMinValue( ) );
        destination.writeDouble( getMaxValue( ) );
    }

    @Override
    public DoubleTimeseriesPropertyDefinitionObject GetDataObject( ) throws SQLException {
        return new DoubleTimeseriesPropertyDefinitionObject( ObjectState.Stored, getId( ), getRowVersion( ), getElementType( ), getName( ), getDescription( ), getMinValue( ), getMaxValue( ) );
    }

}
