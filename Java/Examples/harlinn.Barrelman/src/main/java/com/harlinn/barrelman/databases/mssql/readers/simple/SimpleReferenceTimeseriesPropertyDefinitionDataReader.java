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

public class SimpleReferenceTimeseriesPropertyDefinitionDataReader extends SimpleTimeseriesPropertyDefinitionDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  rtpd.[Id], \r\n" +
            "  rtpd.[EntityType], \r\n" +
            "  rtpd.[RowVersion], \r\n" +
            "  rtpd.[ElementType], \r\n" +
            "  rtpd.[Name], \r\n" +
            "  rtpd.[Description], \r\n" +
            "  rtpd.[ReferencedElementType] \r\n" +
            "FROM [ReferenceTimeseriesPropertyDefinitionView] rtpd \r\n";

    public final static String BaseViewName = "ReferenceTimeseriesPropertyDefinitionView";
    public final static String ViewAliasName = "rtpd";

    public final static int REFERENCEDELEMENTTYPE_FIELD_ID = 7;

    public SimpleReferenceTimeseriesPropertyDefinitionDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getReferencedElementType() throws SQLException {
        return getNullableGuid( REFERENCEDELEMENTTYPE_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeNullableGuid( getReferencedElementType( ) );
    }

    @Override
    public ReferenceTimeseriesPropertyDefinitionObject getDataObject( ) throws SQLException {
        return new ReferenceTimeseriesPropertyDefinitionObject( ObjectState.Stored, getId( ), getRowVersion( ), getElementType( ), getName( ), getDescription( ), getReferencedElementType( ) );
    }

}
