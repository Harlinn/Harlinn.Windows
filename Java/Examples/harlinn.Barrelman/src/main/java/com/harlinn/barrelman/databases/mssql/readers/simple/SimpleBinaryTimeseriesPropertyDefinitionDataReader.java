package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleBinaryTimeseriesPropertyDefinitionDataReader extends SimpleTimeseriesPropertyDefinitionDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  btpd.[Id], \r\n" +
            "  btpd.[EntityType], \r\n" +
            "  btpd.[RowVersion], \r\n" +
            "  btpd.[ElementType], \r\n" +
            "  btpd.[Name], \r\n" +
            "  btpd.[Description] \r\n" +
            "FROM [BinaryTimeseriesPropertyDefinitionView] btpd \r\n";

    public final static String BaseViewName = "BinaryTimeseriesPropertyDefinitionView";
    public final static String ViewAliasName = "btpd";

    public SimpleBinaryTimeseriesPropertyDefinitionDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
    }

}
