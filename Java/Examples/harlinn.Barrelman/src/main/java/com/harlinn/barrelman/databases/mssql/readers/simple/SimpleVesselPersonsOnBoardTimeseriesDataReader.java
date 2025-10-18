package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleVesselPersonsOnBoardTimeseriesDataReader extends SimpleInt32TimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  vpobt.[Id], \r\n" +
            "  vpobt.[EntityType], \r\n" +
            "  vpobt.[RowVersion], \r\n" +
            "  vpobt.[Catalog], \r\n" +
            "  vpobt.[Name], \r\n" +
            "  vpobt.[MaxRetention], \r\n" +
            "  vpobt.[Vessel] \r\n" +
            "FROM [VesselPersonsOnBoardTimeseriesView] vpobt \r\n";

    public final static String BaseViewName = "VesselPersonsOnBoardTimeseriesView";
    public final static String ViewAliasName = "vpobt";

    public final static int VESSEL_FIELD_ID = 7;

    public SimpleVesselPersonsOnBoardTimeseriesDataReader( ResultSet resultSet ) {
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

    @Override
    public VesselPersonsOnBoardTimeseriesObject GetDataObject( ) throws SQLException {
        return new VesselPersonsOnBoardTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getVessel( ) );
    }

}
