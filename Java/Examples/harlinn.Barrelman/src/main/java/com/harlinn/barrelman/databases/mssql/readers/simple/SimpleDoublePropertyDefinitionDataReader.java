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

public class SimpleDoublePropertyDefinitionDataReader extends SimplePropertyDefinitionDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  dpd.[Id], \r\n" +
            "  dpd.[EntityType], \r\n" +
            "  dpd.[RowVersion], \r\n" +
            "  dpd.[ElementType], \r\n" +
            "  dpd.[Name], \r\n" +
            "  dpd.[Description], \r\n" +
            "  dpd.[DefaultValue], \r\n" +
            "  dpd.[MinValue], \r\n" +
            "  dpd.[MaxValue] \r\n" +
            "FROM [DoublePropertyDefinitionView] dpd \r\n";

    public final static String BaseViewName = "DoublePropertyDefinitionView";
    public final static String ViewAliasName = "dpd";

    public final static int DEFAULTVALUE_FIELD_ID = 7;
    public final static int MINVALUE_FIELD_ID = 8;
    public final static int MAXVALUE_FIELD_ID = 9;

    public SimpleDoublePropertyDefinitionDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final double getDefaultValue() throws SQLException {
        return getDouble( DEFAULTVALUE_FIELD_ID );
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
        destination.writeDouble( getDefaultValue( ) );
        destination.writeDouble( getMinValue( ) );
        destination.writeDouble( getMaxValue( ) );
    }

    @Override
    public DoublePropertyDefinitionObject getDataObject( ) throws SQLException {
        return new DoublePropertyDefinitionObject( ObjectState.Stored, getId( ), getRowVersion( ), getElementType( ), getName( ), getDescription( ), getDefaultValue( ), getMinValue( ), getMaxValue( ) );
    }

}
