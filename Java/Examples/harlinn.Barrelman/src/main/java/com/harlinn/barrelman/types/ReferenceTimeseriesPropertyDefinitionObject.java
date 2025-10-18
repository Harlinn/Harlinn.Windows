package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class ReferenceTimeseriesPropertyDefinitionObject extends TimeseriesPropertyDefinitionObject {

    public final int KIND = Kind.ReferenceTimeseriesPropertyDefinition;

    private Guid _referencedElementType;

    public ReferenceTimeseriesPropertyDefinitionObject( ) {
    }
    public ReferenceTimeseriesPropertyDefinitionObject( byte objectState, Guid id, long rowVersion, Guid elementType, String name, String description, Guid referencedElementType ) {
        super( objectState, id, rowVersion, elementType, name, description );
        this._referencedElementType = referencedElementType;
    }

    @Override
    public int getObjectType( ) {
        return Kind.ReferenceTimeseriesPropertyDefinition;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new ReferenceTimeseriesPropertyDefinitionObject( );
    }

    public Guid getReferencedElementType( ) {
        return _referencedElementType;
    }
    public void setReferencedElementType( Guid value ) {
        if( !Comparer.equalsNullableGuid( _referencedElementType, value ) ) {
            _referencedElementType = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( ReferenceTimeseriesPropertyDefinitionObject )target;
        targetObject._referencedElementType = this._referencedElementType;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (ReferenceTimeseriesPropertyDefinitionObject)obj;
        if( !Comparer.equalsNullableGuid( this._referencedElementType, other._referencedElementType ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeNullableGuid( _referencedElementType );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _referencedElementType = source.readNullableGuid( );
    }

}
