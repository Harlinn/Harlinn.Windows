package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleBooleanTimeseriesPropertyDefinitionDataReader extends SimpleTimeseriesPropertyDefinitionDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  botpd.[Id], \r\n" +
            "  botpd.[EntityType], \r\n" +
            "  botpd.[RowVersion], \r\n" +
            "  botpd.[ElementType], \r\n" +
            "  botpd.[Name], \r\n" +
            "  botpd.[Description] \r\n" +
            "FROM [BooleanTimeseriesPropertyDefinitionView] botpd \r\n";

    public final static String BaseViewName = "BooleanTimeseriesPropertyDefinitionView";
    public final static String ViewAliasName = "botpd";

    public SimpleBooleanTimeseriesPropertyDefinitionDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
    }

    @Override
    public BooleanTimeseriesPropertyDefinitionObject getDataObject( ) throws SQLException {
        return new BooleanTimeseriesPropertyDefinitionObject( ObjectState.Stored, getId( ), getRowVersion( ), getElementType( ), getName( ), getDescription( ) );
    }

}
