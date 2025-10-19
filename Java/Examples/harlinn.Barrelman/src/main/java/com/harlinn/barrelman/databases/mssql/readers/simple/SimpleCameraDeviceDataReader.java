package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleCameraDeviceDataReader extends SimpleDeviceDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  cd.[Id], \r\n" +
            "  cd.[EntityType], \r\n" +
            "  cd.[RowVersion], \r\n" +
            "  cd.[Host], \r\n" +
            "  cd.[Name], \r\n" +
            "  cd.[Description], \r\n" +
            "  cd.[EnabledTimeseries] \r\n" +
            "FROM [CameraDeviceView] cd \r\n";

    public final static String BaseViewName = "CameraDeviceView";
    public final static String ViewAliasName = "cd";

    public SimpleCameraDeviceDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
    }

    @Override
    public CameraDeviceObject getDataObject( ) throws SQLException {
        return new CameraDeviceObject( ObjectState.Stored, getId( ), getRowVersion( ), getHost( ), getName( ), getDescription( ), getEnabledTimeseries( ) );
    }

}
