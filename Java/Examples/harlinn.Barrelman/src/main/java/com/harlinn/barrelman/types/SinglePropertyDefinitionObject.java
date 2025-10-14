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
        if( !Comparer.equalsSingle( _defaultValue, value ) ) {
            _defaultValue = value;
            onPropertyChanged( );
        }
    }

    public float getMinValue( ) {
        return _minValue;
    }
    public void setMinValue( float value ) {
        if( !Comparer.equalsSingle( _minValue, value ) ) {
            _minValue = value;
            onPropertyChanged( );
        }
    }

    public float getMaxValue( ) {
        return _maxValue;
    }
    public void setMaxValue( float value ) {
        if( !Comparer.equalsSingle( _maxValue, value ) ) {
            _maxValue = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeSingle( _defaultValue );
        destination.writeSingle( _minValue );
        destination.writeSingle( _maxValue );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _defaultValue = source.readSingle( );
        _minValue = source.readSingle( );
        _maxValue = source.readSingle( );
    }

}
