package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class ElementObject extends CatalogElementObject {

    private Guid _elementType;

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
