/*
    Copyright 2024-2026 Espen Harlinn
 
    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at
 
        http://www.apache.org/licenses/LICENSE-2.0
 
    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/
package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleStringTimeseriesPropertyDefinitionDataReader extends SimpleTimeseriesPropertyDefinitionDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  sttpd.[Id], \r\n" +
            "  sttpd.[EntityType], \r\n" +
            "  sttpd.[RowVersion], \r\n" +
            "  sttpd.[ElementType], \r\n" +
            "  sttpd.[Name], \r\n" +
            "  sttpd.[Description], \r\n" +
            "  sttpd.[Pattern] \r\n" +
            "FROM [StringTimeseriesPropertyDefinitionView] sttpd \r\n";

    public final static String BaseViewName = "StringTimeseriesPropertyDefinitionView";
    public final static String ViewAliasName = "sttpd";

    public final static int PATTERN_FIELD_ID = 7;

    public SimpleStringTimeseriesPropertyDefinitionDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final String getPattern() throws SQLException {
        return getString( PATTERN_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeStringUtf8( getPattern( ) );
    }

    @Override
    public StringTimeseriesPropertyDefinitionObject getDataObject( ) throws SQLException {
        return new StringTimeseriesPropertyDefinitionObject( ObjectState.Stored, getId( ), getRowVersion( ), getElementType( ), getName( ), getDescription( ), getPattern( ) );
    }

}
