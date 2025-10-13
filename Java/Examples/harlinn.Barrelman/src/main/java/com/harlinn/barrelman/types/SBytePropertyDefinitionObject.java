package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SBytePropertyDefinitionObject extends PropertyDefinitionObject {

    private byte _defaultValue = 0;
    private byte _minValue = 0;
    private byte _maxValue = 0;

    @Override
    public int getObjectType( ) {
        return Kind.SBytePropertyDefinition;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new SBytePropertyDefinitionObject( );
    }

    public byte getDefaultValue( ) {
        return _defaultValue;
    }
    public void setDefaultValue( byte value ) {
        if( _defaultValue != value ) {
            this._defaultValue = value;
            onPropertyChanged( );
        }
    }

    public byte getMinValue( ) {
        return _minValue;
    }
    public void setMinValue( byte value ) {
        if( _minValue != value ) {
            this._minValue = value;
            onPropertyChanged( );
        }
    }

    public byte getMaxValue( ) {
        return _maxValue;
    }
    public void setMaxValue( byte value ) {
        if( _maxValue != value ) {
            this._maxValue = value;
            onPropertyChanged( );
        }
    }


}
