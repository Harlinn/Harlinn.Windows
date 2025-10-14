package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class Int32PropertyDefinitionObject extends PropertyDefinitionObject {

    private int _defaultValue = 0;
    private int _minValue = 0;
    private int _maxValue = 0;

    @Override
    public int getObjectType( ) {
        return Kind.Int32PropertyDefinition;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new Int32PropertyDefinitionObject( );
    }

    public int getDefaultValue( ) {
        return _defaultValue;
    }
    public void setDefaultValue( int value ) {
        if( !Comparer.equalsInt32( _defaultValue, value ) ) {
            _defaultValue = value;
            onPropertyChanged( );
        }
    }

    public int getMinValue( ) {
        return _minValue;
    }
    public void setMinValue( int value ) {
        if( !Comparer.equalsInt32( _minValue, value ) ) {
            _minValue = value;
            onPropertyChanged( );
        }
    }

    public int getMaxValue( ) {
        return _maxValue;
    }
    public void setMaxValue( int value ) {
        if( !Comparer.equalsInt32( _maxValue, value ) ) {
            _maxValue = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt32( _defaultValue );
        destination.writeInt32( _minValue );
        destination.writeInt32( _maxValue );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _defaultValue = source.readInt32( );
        _minValue = source.readInt32( );
        _maxValue = source.readInt32( );
    }

}
