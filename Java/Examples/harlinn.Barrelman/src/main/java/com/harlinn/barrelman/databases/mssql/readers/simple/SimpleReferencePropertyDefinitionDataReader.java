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

public class SimpleReferencePropertyDefinitionDataReader extends SimplePropertyDefinitionDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  rpd.[Id], \r\n" +
            "  rpd.[EntityType], \r\n" +
            "  rpd.[RowVersion], \r\n" +
            "  rpd.[ElementType], \r\n" +
            "  rpd.[Name], \r\n" +
            "  rpd.[Description], \r\n" +
            "  rpd.[DefaultValue], \r\n" +
            "  rpd.[ReferencedElementType] \r\n" +
            "FROM [ReferencePropertyDefinitionView] rpd \r\n";

    public final static String BaseViewName = "ReferencePropertyDefinitionView";
    public final static String ViewAliasName = "rpd";

    public final static int DEFAULTVALUE_FIELD_ID = 7;
    public final static int REFERENCEDELEMENTTYPE_FIELD_ID = 8;

    public SimpleReferencePropertyDefinitionDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getDefaultValue() throws SQLException {
        return getNullableGuid( DEFAULTVALUE_FIELD_ID );
    }

    public final Guid getReferencedElementType() throws SQLException {
        return getNullableGuid( REFERENCEDELEMENTTYPE_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeNullableGuid( getDefaultValue( ) );
        destination.writeNullableGuid( getReferencedElementType( ) );
    }

    @Override
    public ReferencePropertyDefinitionObject getDataObject( ) throws SQLException {
        return new ReferencePropertyDefinitionObject( ObjectState.Stored, getId( ), getRowVersion( ), getElementType( ), getName( ), getDescription( ), getDefaultValue( ), getReferencedElementType( ) );
    }

}
