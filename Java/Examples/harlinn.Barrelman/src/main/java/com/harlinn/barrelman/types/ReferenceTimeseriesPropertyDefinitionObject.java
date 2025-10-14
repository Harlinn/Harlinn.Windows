package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class ReferenceTimeseriesPropertyDefinitionObject extends TimeseriesPropertyDefinitionObject {

    private Guid _referencedElementType;

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
