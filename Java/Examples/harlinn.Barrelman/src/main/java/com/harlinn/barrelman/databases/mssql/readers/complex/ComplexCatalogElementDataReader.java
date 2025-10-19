package com.harlinn.barrelman.databases.mssql.readers.complex;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class ComplexCatalogElementDataReader extends ResultSetWrapper {

    public final static String BaseQuery = "SELECT \r\n" +
            "  ce.[Id], \r\n" +
            "  ce.[EntityType], \r\n" +
            "  ce.[RowVersion], \r\n" +
            "  ce.[Catalog], \r\n" +
            "  ce.[Name], \r\n" +
            "  e.[ElementType] \r\n" +
            "FROM [CatalogElementView] ce \r\n" +
            "  LEFT JOIN [Catalog] c ON(ce.[Id] = c.[Id] ) \r\n" +
            "  LEFT JOIN [Element] e ON(ce.[Id] = e.[Id] ) \r\n";

    public final static String BaseViewName = "CatalogElementView";
    public final static String ViewAliasName = "ce";

    public final static int CE_ID_FIELD_ID = 1;
    public final static int CE_KIND_FIELD_ID = 2;
    public final static int CE_ROWVERSION_FIELD_ID = 3;
    public final static int CE_CATALOG_FIELD_ID = 4;
    public final static int CE_NAME_FIELD_ID = 5;
    public final static int E_ELEMENTTYPE_FIELD_ID = 6;

    public ComplexCatalogElementDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public Guid getId( ) throws SQLException {
        return getGuid( CE_ID_FIELD_ID );
    }

    public int getObjectType() throws SQLException {
        return getInt32( CE_KIND_FIELD_ID );
    }

    public long getRowVersion( ) throws SQLException {
        return getInt64( CE_ROWVERSION_FIELD_ID );
    }

    public Guid getCatalog( ) throws SQLException {
        return getNullableGuid( CE_CATALOG_FIELD_ID );
    }

    public String getName( ) throws SQLException {
        return getString( CE_NAME_FIELD_ID );
    }

    public Guid getElementElementType( ) throws SQLException {
        return getNullableGuid( E_ELEMENTTYPE_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination ) throws SQLException {
        var kind = getObjectType( );
        switch(kind) {
            case Kind.Catalog: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
            }
            break;
            case Kind.Element: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeNullableGuid( getCatalog( ) );
                destination.writeStringUtf8( getName( ) );
                destination.writeNullableGuid( getElementElementType( ) );
            }
            break;
            default: {
                var exc = new SQLException( "Cannot perform serialization for kind=" + kind + "." );
                throw exc;
            }
        }
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

    public CatalogElementObject getDataObject( ) throws SQLException {
        var kind = getObjectType( );
        switch(kind) {
            case Kind.Catalog: {
                return new CatalogObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ) );
            }
            case Kind.Element: {
                return new ElementObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getElementElementType( ) );
            }
            default: {
                var exc = new SQLException( "Cannot create an object for kind=" + kind + "." );
                throw exc;
            }
        }
    }

}

