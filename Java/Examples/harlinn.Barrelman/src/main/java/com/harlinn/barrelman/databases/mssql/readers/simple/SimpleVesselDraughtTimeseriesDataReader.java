package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleVesselDraughtTimeseriesDataReader extends SimpleDoubleTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  vdt.[Id], \r\n" +
            "  vdt.[EntityType], \r\n" +
            "  vdt.[RowVersion], \r\n" +
            "  vdt.[Catalog], \r\n" +
            "  vdt.[Name], \r\n" +
            "  vdt.[MaxRetention], \r\n" +
            "  vdt.[Vessel] \r\n" +
            "FROM [VesselDraughtTimeseriesView] vdt \r\n";

    public final static String BaseViewName = "VesselDraughtTimeseriesView";
    public final static String ViewAliasName = "vdt";

    public final static int VESSEL_FIELD_ID = 7;

    public SimpleVesselDraughtTimeseriesDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getVessel() throws SQLException {
        return getNullableGuid( VESSEL_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeNullableGuid( getVessel( ) );
    }

}
