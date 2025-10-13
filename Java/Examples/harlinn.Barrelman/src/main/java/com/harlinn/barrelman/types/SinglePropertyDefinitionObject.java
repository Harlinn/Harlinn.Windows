package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SinglePropertyDefinitionObject extends PropertyDefinitionObject {

    private float _defaultValue = 0.0f;
    private float _minValue = 0.0f;
    private float _maxValue = 0.0f;

    @Override
    public int getObjectType( ) {
        return Kind.SinglePropertyDefinition;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new SinglePropertyDefinitionObject( );
    }

    public float getDefaultValue( ) {
        return _defaultValue;
    }
    public void setDefaultValue( float value ) {
        if( _defaultValue != value ) {
            this._defaultValue = value;
            onPropertyChanged( );
        }
    }

    public float getMinValue( ) {
        return _minValue;
    }
    public void setMinValue( float value ) {
        if( _minValue != value ) {
            this._minValue = value;
            onPropertyChanged( );
        }
    }

    public float getMaxValue( ) {
        return _maxValue;
    }
    public void setMaxValue( float value ) {
        if( _maxValue != value ) {
            this._maxValue = value;
            onPropertyChanged( );
        }
    }


}
