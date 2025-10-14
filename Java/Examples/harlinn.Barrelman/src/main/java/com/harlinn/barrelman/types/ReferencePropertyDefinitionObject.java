package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class ReferencePropertyDefinitionObject extends PropertyDefinitionObject {

    private Guid _defaultValue;
    private Guid _referencedElementType;

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
