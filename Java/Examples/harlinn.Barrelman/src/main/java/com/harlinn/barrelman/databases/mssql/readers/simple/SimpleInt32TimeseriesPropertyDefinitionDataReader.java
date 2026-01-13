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

public class SimpleInt32TimeseriesPropertyDefinitionDataReader extends SimpleTimeseriesPropertyDefinitionDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  i32tpd.[Id], \r\n" +
            "  i32tpd.[EntityType], \r\n" +
            "  i32tpd.[RowVersion], \r\n" +
            "  i32tpd.[ElementType], \r\n" +
            "  i32tpd.[Name], \r\n" +
            "  i32tpd.[Description], \r\n" +
            "  i32tpd.[MinValue], \r\n" +
            "  i32tpd.[MaxValue] \r\n" +
            "FROM [Int32TimeseriesPropertyDefinitionView] i32tpd \r\n";

    public final static String BaseViewName = "Int32TimeseriesPropertyDefinitionView";
    public final static String ViewAliasName = "i32tpd";

    public final static int MINVALUE_FIELD_ID = 7;
    public final static int MAXVALUE_FIELD_ID = 8;

    public SimpleInt32TimeseriesPropertyDefinitionDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final int getMinValue() throws SQLException {
        return getInt32( MINVALUE_FIELD_ID );
    }

    public final int getMaxValue() throws SQLException {
        return getInt32( MAXVALUE_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeInt32( getMinValue( ) );
        destination.writeInt32( getMaxValue( ) );
    }

    @Override
    public Int32TimeseriesPropertyDefinitionObject getDataObject( ) throws SQLException {
        return new Int32TimeseriesPropertyDefinitionObject( ObjectState.Stored, getId( ), getRowVersion( ), getElementType( ), getName( ), getDescription( ), getMinValue( ), getMaxValue( ) );
    }

}
