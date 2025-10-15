package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class UInt16TimeseriesPropertyDefinitionObject extends TimeseriesPropertyDefinitionObject {

    private short _minValue = 0;
    private short _maxValue = 0;

    @Override
    public int getObjectType( ) {
        return Kind.UInt16TimeseriesPropertyDefinition;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new UInt16TimeseriesPropertyDefinitionObject( );
    }

    public short getMinValue( ) {
        return _minValue;
    }
    public void setMinValue( short value ) {
        if( !Comparer.equalsUInt16( _minValue, value ) ) {
            _minValue = value;
            onPropertyChanged( );
        }
    }

    public short getMaxValue( ) {
        return _maxValue;
    }
    public void setMaxValue( short value ) {
        if( !Comparer.equalsUInt16( _maxValue, value ) ) {
            _maxValue = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( UInt16TimeseriesPropertyDefinitionObject )target;
        targetObject._minValue = this._minValue;
        targetObject._maxValue = this._maxValue;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (UInt16TimeseriesPropertyDefinitionObject)obj;
        if( !Comparer.equalsUInt16( this._minValue, other._minValue ) ) {
            return false;
        }
        if( !Comparer.equalsUInt16( this._maxValue, other._maxValue ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeUInt16( _minValue );
        destination.writeUInt16( _maxValue );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _minValue = source.readUInt16( );
        _maxValue = source.readUInt16( );
    }

}
