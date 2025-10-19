package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleBinaryPropertyDataReader extends SimplePropertyDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  bp.[Id], \r\n" +
            "  bp.[EntityType], \r\n" +
            "  bp.[RowVersion], \r\n" +
            "  bp.[Element], \r\n" +
            "  bp.[Definition], \r\n" +
            "  bp.[Value] \r\n" +
            "FROM [BinaryPropertyView] bp \r\n";

    public final static String BaseViewName = "BinaryPropertyView";
    public final static String ViewAliasName = "bp";

    public final static int VALUE_FIELD_ID = 6;

    public SimpleBinaryPropertyDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final byte[] getValue() throws SQLException {
        return getBinary( VALUE_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeUInt8Array( getValue( ) );
    }

    @Override
    public BinaryPropertyObject getDataObject( ) throws SQLException {
        return new BinaryPropertyObject( ObjectState.Stored, getId( ), getRowVersion( ), getElement( ), getDefinition( ), getValue( ) );
    }

}
