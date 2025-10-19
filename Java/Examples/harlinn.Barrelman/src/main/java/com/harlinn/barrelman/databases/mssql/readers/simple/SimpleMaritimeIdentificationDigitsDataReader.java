package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleMaritimeIdentificationDigitsDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  mid.[Id], \r\n" +
            "  mid.[RowVersion], \r\n" +
            "  mid.[Code], \r\n" +
            "  mid.[Country] \r\n" +
            "FROM [MaritimeIdentificationDigitsView] mid \r\n";

    public final static String BaseViewName = "MaritimeIdentificationDigitsView";
    public final static String ViewAliasName = "mid";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int CODE_FIELD_ID = 3;
    public final static int COUNTRY_FIELD_ID = 4;

    public SimpleMaritimeIdentificationDigitsDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final int getCode() throws SQLException {
        return getInt32( CODE_FIELD_ID );
    }

    public final Guid getCountry() throws SQLException {
        return getGuid( COUNTRY_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.MaritimeIdentificationDigits );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeInt32( getCode( ) );
        destination.writeGuid( getCountry( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

    public MaritimeIdentificationDigitsObject getDataObject( ) throws SQLException {
            return new MaritimeIdentificationDigitsObject( ObjectState.Stored, getId( ), getRowVersion( ), getCode( ), getCountry( ) );
    }

}
