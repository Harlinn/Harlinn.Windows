package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class BinaryPropertyDefinitionObject extends PropertyDefinitionObject {

    private byte[] _defaultValue = new byte[0];

    @Override
    public int getObjectType( ) {
        return Kind.BinaryPropertyDefinition;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new BinaryPropertyDefinitionObject( );
    }

    public byte[] getDefaultValue( ) {
        return _defaultValue;
    }
    public void setDefaultValue( byte[] value ) {
        if( !Comparer.equalsUInt8Array( _defaultValue, value ) ) {
            _defaultValue = value != null ? value.clone() : value;;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeUInt8Array( _defaultValue );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _defaultValue = source.readUInt8Array( );
    }

}
