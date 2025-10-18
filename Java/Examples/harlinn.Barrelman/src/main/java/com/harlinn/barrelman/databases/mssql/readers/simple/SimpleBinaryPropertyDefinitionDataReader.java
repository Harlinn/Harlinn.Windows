package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleBinaryPropertyDefinitionDataReader extends SimplePropertyDefinitionDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  bpd.[Id], \r\n" +
            "  bpd.[EntityType], \r\n" +
            "  bpd.[RowVersion], \r\n" +
            "  bpd.[ElementType], \r\n" +
            "  bpd.[Name], \r\n" +
            "  bpd.[Description], \r\n" +
            "  bpd.[DefaultValue] \r\n" +
            "FROM [BinaryPropertyDefinitionView] bpd \r\n";

    public final static String BaseViewName = "BinaryPropertyDefinitionView";
    public final static String ViewAliasName = "bpd";

    public final static int DEFAULTVALUE_FIELD_ID = 7;

    public SimpleBinaryPropertyDefinitionDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final byte[] getDefaultValue() throws SQLException {
        return getBinary( DEFAULTVALUE_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeUInt8Array( getDefaultValue( ) );
    }

    @Override
    public BinaryPropertyDefinitionObject GetDataObject( ) throws SQLException {
        return new BinaryPropertyDefinitionObject( ObjectState.Stored, getId( ), getRowVersion( ), getElementType( ), getName( ), getDescription( ), getDefaultValue( ) );
    }

}
