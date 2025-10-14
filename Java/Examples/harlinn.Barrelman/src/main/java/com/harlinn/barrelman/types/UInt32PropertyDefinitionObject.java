package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class UInt32PropertyDefinitionObject extends PropertyDefinitionObject {

    private int _defaultValue = 0;
    private int _minValue = 0;
    private int _maxValue = 0;

    @Override
    public int getObjectType( ) {
        return Kind.UInt32PropertyDefinition;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new UInt32PropertyDefinitionObject( );
    }

    public int getDefaultValue( ) {
        return _defaultValue;
    }
    public void setDefaultValue( int value ) {
        if( !Comparer.equalsUInt32( _defaultValue, value ) ) {
            _defaultValue = value;
            onPropertyChanged( );
        }
    }

    public int getMinValue( ) {
        return _minValue;
    }
    public void setMinValue( int value ) {
        if( !Comparer.equalsUInt32( _minValue, value ) ) {
            _minValue = value;
            onPropertyChanged( );
        }
    }

    public int getMaxValue( ) {
        return _maxValue;
    }
    public void setMaxValue( int value ) {
        if( !Comparer.equalsUInt32( _maxValue, value ) ) {
            _maxValue = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeUInt32( _defaultValue );
        destination.writeUInt32( _minValue );
        destination.writeUInt32( _maxValue );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _defaultValue = source.readUInt32( );
        _minValue = source.readUInt32( );
        _maxValue = source.readUInt32( );
    }

}
