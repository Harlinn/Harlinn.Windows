package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleNameDataReader extends SimpleIdentityDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  n.[Id], \r\n" +
            "  n.[EntityType], \r\n" +
            "  n.[RowVersion], \r\n" +
            "  n.[Text] \r\n" +
            "FROM [NameView] n \r\n";

    public final static String BaseViewName = "NameView";
    public final static String ViewAliasName = "n";

    public final static int TEXT_FIELD_ID = 4;

    public SimpleNameDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final String getText() throws SQLException {
        return getString( TEXT_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeStringUtf8( getText( ) );
    }

    @Override
    public NameObject GetDataObject( ) throws SQLException {
        return new NameObject( ObjectState.Stored, getId( ), getRowVersion( ), getText( ) );
    }

}
