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
    public ReferenceTimeseriesPropertyDefinitionObject GetDataObject( ) throws SQLException {
        return new ReferenceTimeseriesPropertyDefinitionObject( ObjectState.Stored, getId( ), getRowVersion( ), getElementType( ), getName( ), getDescription( ), getReferencedElementType( ) );
    }

}
