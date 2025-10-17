package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleZoneExceptionsVesselLinkDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  zevl.[Id], \r\n" +
            "  zevl.[RowVersion], \r\n" +
            "  zevl.[ZoneExceptions], \r\n" +
            "  zevl.[Vessel] \r\n" +
            "FROM [ZoneExceptionsVesselLinkView] zevl \r\n";

    public final static String BaseViewName = "ZoneExceptionsVesselLinkView";
    public final static String ViewAliasName = "zevl";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int ZONEEXCEPTIONS_FIELD_ID = 3;
    public final static int VESSEL_FIELD_ID = 4;

    public SimpleZoneExceptionsVesselLinkDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final Guid getZoneExceptions() throws SQLException {
        return getGuid( ZONEEXCEPTIONS_FIELD_ID );
    }

    public final Guid getVessel() throws SQLException {
        return getGuid( VESSEL_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.ZoneExceptionsVesselLink );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getZoneExceptions( ) );
        destination.writeGuid( getVessel( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

}
