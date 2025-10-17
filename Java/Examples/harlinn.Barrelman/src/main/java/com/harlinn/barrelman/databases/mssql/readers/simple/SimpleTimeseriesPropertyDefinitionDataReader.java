package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public abstract class SimpleTimeseriesPropertyDefinitionDataReader extends SimplePropertyDefinitionDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  tpd.[Id], \r\n" +
            "  tpd.[EntityType], \r\n" +
            "  tpd.[RowVersion], \r\n" +
            "  tpd.[ElementType], \r\n" +
            "  tpd.[Name], \r\n" +
            "  tpd.[Description] \r\n" +
            "FROM [TimeseriesPropertyDefinitionView] tpd \r\n";

    public final static String BaseViewName = "TimeseriesPropertyDefinitionView";
    public final static String ViewAliasName = "tpd";

    public SimpleTimeseriesPropertyDefinitionDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
    }

}
