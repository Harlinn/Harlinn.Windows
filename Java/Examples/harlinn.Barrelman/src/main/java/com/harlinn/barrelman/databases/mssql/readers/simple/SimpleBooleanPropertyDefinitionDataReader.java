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

public class SimpleBooleanPropertyDefinitionDataReader extends SimplePropertyDefinitionDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  bopd.[Id], \r\n" +
            "  bopd.[EntityType], \r\n" +
            "  bopd.[RowVersion], \r\n" +
            "  bopd.[ElementType], \r\n" +
            "  bopd.[Name], \r\n" +
            "  bopd.[Description], \r\n" +
            "  bopd.[DefaultValue] \r\n" +
            "FROM [BooleanPropertyDefinitionView] bopd \r\n";

    public final static String BaseViewName = "BooleanPropertyDefinitionView";
    public final static String ViewAliasName = "bopd";

    public final static int DEFAULTVALUE_FIELD_ID = 7;

    public SimpleBooleanPropertyDefinitionDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final boolean getDefaultValue() throws SQLException {
        return getBoolean( DEFAULTVALUE_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeBoolean( getDefaultValue( ) );
    }

    @Override
    public BooleanPropertyDefinitionObject getDataObject( ) throws SQLException {
        return new BooleanPropertyDefinitionObject( ObjectState.Stored, getId( ), getRowVersion( ), getElementType( ), getName( ), getDescription( ), getDefaultValue( ) );
    }

}
