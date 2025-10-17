package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public abstract class SimpleTrackableItemDataReader extends SimpleItemDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  ti.[Id], \r\n" +
            "  ti.[EntityType], \r\n" +
            "  ti.[RowVersion] \r\n" +
            "FROM [TrackableItemView] ti \r\n";

    public final static String BaseViewName = "TrackableItemView";
    public final static String ViewAliasName = "ti";

    public SimpleTrackableItemDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
    }

}
