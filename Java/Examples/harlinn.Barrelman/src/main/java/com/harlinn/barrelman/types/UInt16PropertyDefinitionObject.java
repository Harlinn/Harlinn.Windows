package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class UInt16PropertyDefinitionObject extends PropertyDefinitionObject {

    private short _defaultValue = 0;
    private short _minValue = 0;
    private short _maxValue = 0;

    @Override
    public int getObjectType( ) {
        return Kind.UInt16PropertyDefinition;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new UInt16PropertyDefinitionObject( );
    }

    public short getDefaultValue( ) {
        return _defaultValue;
    }
    public void setDefaultValue( short value ) {
        if( !Comparer.equalsUInt16( _defaultValue, value ) ) {
            _defaultValue = value;
            onPropertyChanged( );
        }
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
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeUInt16( _defaultValue );
        destination.writeUInt16( _minValue );
        destination.writeUInt16( _maxValue );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _defaultValue = source.readUInt16( );
        _minValue = source.readUInt16( );
        _maxValue = source.readUInt16( );
    }

}
