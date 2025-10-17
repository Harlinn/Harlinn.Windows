package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleRadioDeviceDataReader extends SimpleDeviceDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  rdi.[Id], \r\n" +
            "  rdi.[EntityType], \r\n" +
            "  rdi.[RowVersion], \r\n" +
            "  rdi.[Host], \r\n" +
            "  rdi.[Name], \r\n" +
            "  rdi.[Description], \r\n" +
            "  rdi.[EnabledTimeseries] \r\n" +
            "FROM [RadioDeviceView] rdi \r\n";

    public final static String BaseViewName = "RadioDeviceView";
    public final static String ViewAliasName = "rdi";

    public SimpleRadioDeviceDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
    }

}
