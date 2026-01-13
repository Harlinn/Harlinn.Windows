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

public class SimpleUInt32TimeseriesPropertyDefinitionDataReader extends SimpleTimeseriesPropertyDefinitionDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  u32tpd.[Id], \r\n" +
            "  u32tpd.[EntityType], \r\n" +
            "  u32tpd.[RowVersion], \r\n" +
            "  u32tpd.[ElementType], \r\n" +
            "  u32tpd.[Name], \r\n" +
            "  u32tpd.[Description], \r\n" +
            "  u32tpd.[MinValue], \r\n" +
            "  u32tpd.[MaxValue] \r\n" +
            "FROM [UInt32TimeseriesPropertyDefinitionView] u32tpd \r\n";

    public final static String BaseViewName = "UInt32TimeseriesPropertyDefinitionView";
    public final static String ViewAliasName = "u32tpd";

    public final static int MINVALUE_FIELD_ID = 7;
    public final static int MAXVALUE_FIELD_ID = 8;

    public SimpleUInt32TimeseriesPropertyDefinitionDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final int getMinValue() throws SQLException {
        return getUInt32( MINVALUE_FIELD_ID );
    }

    public final int getMaxValue() throws SQLException {
        return getUInt32( MAXVALUE_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeUInt32( getMinValue( ) );
        destination.writeUInt32( getMaxValue( ) );
    }

    @Override
    public UInt32TimeseriesPropertyDefinitionObject getDataObject( ) throws SQLException {
        return new UInt32TimeseriesPropertyDefinitionObject( ObjectState.Stored, getId( ), getRowVersion( ), getElementType( ), getName( ), getDescription( ), getMinValue( ), getMaxValue( ) );
    }

}
