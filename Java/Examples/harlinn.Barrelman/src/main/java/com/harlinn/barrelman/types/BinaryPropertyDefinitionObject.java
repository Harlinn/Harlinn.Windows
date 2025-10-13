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
        if( _defaultValue != value ) {
            this._defaultValue = value;
            onPropertyChanged( );
        }
    }


}
