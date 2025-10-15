package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class Int32TimeseriesPropertyDefinitionObject extends TimeseriesPropertyDefinitionObject {

    private int _minValue = 0;
    private int _maxValue = 0;

    @Override
    public int getObjectType( ) {
        return Kind.Int32TimeseriesPropertyDefinition;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new Int32TimeseriesPropertyDefinitionObject( );
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
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( Int32TimeseriesPropertyDefinitionObject )target;
        targetObject._minValue = this._minValue;
        targetObject._maxValue = this._maxValue;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (Int32TimeseriesPropertyDefinitionObject)obj;
        if( !Comparer.equalsInt32( this._minValue, other._minValue ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._maxValue, other._maxValue ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt32( _minValue );
        destination.writeInt32( _maxValue );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _minValue = source.readInt32( );
        _maxValue = source.readInt32( );
    }

}
