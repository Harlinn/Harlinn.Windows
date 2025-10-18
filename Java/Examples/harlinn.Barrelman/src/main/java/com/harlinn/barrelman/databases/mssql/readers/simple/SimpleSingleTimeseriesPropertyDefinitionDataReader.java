package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleSingleTimeseriesPropertyDefinitionDataReader extends SimpleTimeseriesPropertyDefinitionDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  sitpd.[Id], \r\n" +
            "  sitpd.[EntityType], \r\n" +
            "  sitpd.[RowVersion], \r\n" +
            "  sitpd.[ElementType], \r\n" +
            "  sitpd.[Name], \r\n" +
            "  sitpd.[Description], \r\n" +
            "  sitpd.[MinValue], \r\n" +
            "  sitpd.[MaxValue] \r\n" +
            "FROM [SingleTimeseriesPropertyDefinitionView] sitpd \r\n";

    public final static String BaseViewName = "SingleTimeseriesPropertyDefinitionView";
    public final static String ViewAliasName = "sitpd";

    public final static int MINVALUE_FIELD_ID = 7;
    public final static int MAXVALUE_FIELD_ID = 8;

    public SimpleSingleTimeseriesPropertyDefinitionDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final float getMinValue() throws SQLException {
        return getSingle( MINVALUE_FIELD_ID );
    }

    public final float getMaxValue() throws SQLException {
        return getSingle( MAXVALUE_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeSingle( getMinValue( ) );
        destination.writeSingle( getMaxValue( ) );
    }

    @Override
    public SingleTimeseriesPropertyDefinitionObject GetDataObject( ) throws SQLException {
        return new SingleTimeseriesPropertyDefinitionObject( ObjectState.Stored, getId( ), getRowVersion( ), getElementType( ), getName( ), getDescription( ), getMinValue( ), getMaxValue( ) );
    }

}
