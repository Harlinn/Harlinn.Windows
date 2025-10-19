package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleBaseStationTypeDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  bst.[Id], \r\n" +
            "  bst.[RowVersion], \r\n" +
            "  bst.[Name] \r\n" +
            "FROM [BaseStationTypeView] bst \r\n";

    public final static String BaseViewName = "BaseStationTypeView";
    public final static String ViewAliasName = "bst";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int NAME_FIELD_ID = 3;

    public SimpleBaseStationTypeDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final String getName() throws SQLException {
        return getString( NAME_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.BaseStationType );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeStringUtf8( getName( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

    public BaseStationTypeObject getDataObject( ) throws SQLException {
            return new BaseStationTypeObject( ObjectState.Stored, getId( ), getRowVersion( ), getName( ) );
    }

}
