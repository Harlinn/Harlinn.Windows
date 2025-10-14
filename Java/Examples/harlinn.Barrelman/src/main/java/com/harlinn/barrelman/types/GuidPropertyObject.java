package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class GuidPropertyObject extends PropertyObject {

    private Guid _value;

    @Override
    public int getObjectType( ) {
        return Kind.GuidProperty;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new GuidPropertyObject( );
    }

    public Guid getValue( ) {
        return _value;
    }
    public void setValue( Guid value ) {
        if( !Comparer.equalsGuid( _value, value ) ) {
            _value = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeGuid( _value );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _value = source.readGuid( );
    }

}
