package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleGuidTimeseriesPropertyDefinitionDataReader extends SimpleTimeseriesPropertyDefinitionDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  gtpd.[Id], \r\n" +
            "  gtpd.[EntityType], \r\n" +
            "  gtpd.[RowVersion], \r\n" +
            "  gtpd.[ElementType], \r\n" +
            "  gtpd.[Name], \r\n" +
            "  gtpd.[Description] \r\n" +
            "FROM [GuidTimeseriesPropertyDefinitionView] gtpd \r\n";

    public final static String BaseViewName = "GuidTimeseriesPropertyDefinitionView";
    public final static String ViewAliasName = "gtpd";

    public SimpleGuidTimeseriesPropertyDefinitionDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
    }

}
