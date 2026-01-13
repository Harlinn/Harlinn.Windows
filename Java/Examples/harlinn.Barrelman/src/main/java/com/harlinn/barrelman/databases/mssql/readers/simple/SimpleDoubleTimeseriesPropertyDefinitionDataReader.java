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
    public DoubleTimeseriesPropertyDefinitionObject getDataObject( ) throws SQLException {
        return new DoubleTimeseriesPropertyDefinitionObject( ObjectState.Stored, getId( ), getRowVersion( ), getElementType( ), getName( ), getDescription( ), getMinValue( ), getMaxValue( ) );
    }

}
