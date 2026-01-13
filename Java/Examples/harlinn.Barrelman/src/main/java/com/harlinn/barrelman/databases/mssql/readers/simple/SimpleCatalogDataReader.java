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

public class SimpleCatalogDataReader extends SimpleCatalogElementDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  c.[Id], \r\n" +
            "  c.[EntityType], \r\n" +
            "  c.[RowVersion], \r\n" +
            "  c.[Catalog], \r\n" +
            "  c.[Name] \r\n" +
            "FROM [CatalogView] c \r\n";

    public final static String BaseViewName = "CatalogView";
    public final static String ViewAliasName = "c";

    public SimpleCatalogDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
    }

    @Override
    public CatalogObject getDataObject( ) throws SQLException {
        return new CatalogObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ) );
    }

}
