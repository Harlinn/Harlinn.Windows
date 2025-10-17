package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleTimeSpanTimeseriesPropertyDefinitionDataReader extends SimpleTimeseriesPropertyDefinitionDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  tstpd.[Id], \r\n" +
            "  tstpd.[EntityType], \r\n" +
            "  tstpd.[RowVersion], \r\n" +
            "  tstpd.[ElementType], \r\n" +
            "  tstpd.[Name], \r\n" +
            "  tstpd.[Description], \r\n" +
            "  tstpd.[MinValue], \r\n" +
            "  tstpd.[MaxValue] \r\n" +
            "FROM [TimeSpanTimeseriesPropertyDefinitionView] tstpd \r\n";

    public final static String BaseViewName = "TimeSpanTimeseriesPropertyDefinitionView";
    public final static String ViewAliasName = "tstpd";

    public final static int MINVALUE_FIELD_ID = 7;
    public final static int MAXVALUE_FIELD_ID = 8;

    public SimpleTimeSpanTimeseriesPropertyDefinitionDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final TimeSpan getMinValue() throws SQLException {
        return getTimeSpan( MINVALUE_FIELD_ID );
    }

    public final TimeSpan getMaxValue() throws SQLException {
        return getTimeSpan( MAXVALUE_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeTimeSpan( getMinValue( ) );
        destination.writeTimeSpan( getMaxValue( ) );
    }

}
