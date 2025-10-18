package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class ReferencePropertyDefinitionObject extends PropertyDefinitionObject {

    public final int KIND = Kind.ReferencePropertyDefinition;

    private Guid _defaultValue;
    private Guid _referencedElementType;

    public ReferencePropertyDefinitionObject( ) {
    }
    public ReferencePropertyDefinitionObject( byte objectState, Guid id, long rowVersion, Guid elementType, String name, String description, Guid defaultValue, Guid referencedElementType ) {
        super( objectState, id, rowVersion, elementType, name, description );
        this._defaultValue = defaultValue;
        this._referencedElementType = referencedElementType;
    }

    @Override
    public int getObjectType( ) {
        return Kind.ReferencePropertyDefinition;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new ReferencePropertyDefinitionObject( );
    }

    public Guid getDefaultValue( ) {
        return _defaultValue;
    }
    public void setDefaultValue( Guid value ) {
        if( !Comparer.equalsNullableGuid( _defaultValue, value ) ) {
            _defaultValue = value;
            onPropertyChanged( );
        }
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
        var targetObject = ( ReferencePropertyDefinitionObject )target;
        targetObject._defaultValue = this._defaultValue;
        targetObject._referencedElementType = this._referencedElementType;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (ReferencePropertyDefinitionObject)obj;
        if( !Comparer.equalsNullableGuid( this._defaultValue, other._defaultValue ) ) {
            return false;
        }
        if( !Comparer.equalsNullableGuid( this._referencedElementType, other._referencedElementType ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeNullableGuid( _defaultValue );
        destination.writeNullableGuid( _referencedElementType );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _defaultValue = source.readNullableGuid( );
        _referencedElementType = source.readNullableGuid( );
    }

}
