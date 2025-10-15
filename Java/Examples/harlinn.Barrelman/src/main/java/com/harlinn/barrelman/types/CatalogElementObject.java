package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public abstract class CatalogElementObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _catalog;
    private String _name = "";


    public long getRowVersion( ) {
        return _rowVersion;
    }
    public void setRowVersion( long value ) {
        if( !Comparer.equalsInt64( _rowVersion, value ) ) {
            _rowVersion = value;
            onPropertyChanged( );
        }
    }

    public Guid getCatalog( ) {
        return _catalog;
    }
    public void setCatalog( Guid value ) {
        if( !Comparer.equalsNullableGuid( _catalog, value ) ) {
            _catalog = value;
            onPropertyChanged( );
        }
    }

    public String getName( ) {
        return _name;
    }
    public void setName( String value ) {
        if( !Comparer.equalsString( _name, value ) ) {
            _name = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( CatalogElementObject )target;
        targetObject._rowVersion = this._rowVersion;
        targetObject._catalog = this._catalog;
        targetObject._name = this._name;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (CatalogElementObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        if( !Comparer.equalsNullableGuid( this._catalog, other._catalog ) ) {
            return false;
        }
        if( !Comparer.equalsString( this._name, other._name ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeNullableGuid( _catalog );
        destination.writeStringUtf8( _name );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _catalog = source.readNullableGuid( );
        _name = source.readString( );
    }

}
