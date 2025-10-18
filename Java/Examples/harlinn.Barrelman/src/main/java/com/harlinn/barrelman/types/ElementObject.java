package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class ElementObject extends CatalogElementObject {

    public final int KIND = Kind.Element;

    private Guid _elementType;

    public ElementObject( ) {
    }
    public ElementObject( byte objectState, Guid id, long rowVersion, Guid catalog, String name, Guid elementType ) {
        super( objectState, id, rowVersion, catalog, name );
        this._elementType = elementType;
    }

    @Override
    public int getObjectType( ) {
        return Kind.Element;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new ElementObject( );
    }

    public Guid getElementType( ) {
        return _elementType;
    }
    public void setElementType( Guid value ) {
        if( !Comparer.equalsNullableGuid( _elementType, value ) ) {
            _elementType = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( ElementObject )target;
        targetObject._elementType = this._elementType;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (ElementObject)obj;
        if( !Comparer.equalsNullableGuid( this._elementType, other._elementType ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeNullableGuid( _elementType );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _elementType = source.readNullableGuid( );
    }

}
