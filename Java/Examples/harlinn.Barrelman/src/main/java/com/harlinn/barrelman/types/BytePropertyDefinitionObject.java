/*
    Copyright 2024-2026 Espen Harlinn
 
    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at
 
        http://www.apache.org/licenses/LICENSE-2.0
 
    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/
package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class BytePropertyDefinitionObject extends PropertyDefinitionObject {

    public final int KIND = Kind.BytePropertyDefinition;

    private byte _defaultValue = 0;
    private byte _minValue = 0;
    private byte _maxValue = 0;

    public BytePropertyDefinitionObject( ) {
    }
    public BytePropertyDefinitionObject( byte objectState, Guid id, long rowVersion, Guid elementType, String name, String description, byte defaultValue, byte minValue, byte maxValue ) {
        super( objectState, id, rowVersion, elementType, name, description );
        this._defaultValue = defaultValue;
        this._minValue = minValue;
        this._maxValue = maxValue;
    }

    @Override
    public int getObjectType( ) {
        return Kind.BytePropertyDefinition;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new BytePropertyDefinitionObject( );
    }

    public byte getDefaultValue( ) {
        return _defaultValue;
    }
    public void setDefaultValue( byte value ) {
        if( !Comparer.equalsUInt8( _defaultValue, value ) ) {
            _defaultValue = value;
            onPropertyChanged( );
        }
    }

    public byte getMinValue( ) {
        return _minValue;
    }
    public void setMinValue( byte value ) {
        if( !Comparer.equalsUInt8( _minValue, value ) ) {
            _minValue = value;
            onPropertyChanged( );
        }
    }

    public byte getMaxValue( ) {
        return _maxValue;
    }
    public void setMaxValue( byte value ) {
        if( !Comparer.equalsUInt8( _maxValue, value ) ) {
            _maxValue = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( BytePropertyDefinitionObject )target;
        targetObject._defaultValue = this._defaultValue;
        targetObject._minValue = this._minValue;
        targetObject._maxValue = this._maxValue;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (BytePropertyDefinitionObject)obj;
        if( !Comparer.equalsUInt8( this._defaultValue, other._defaultValue ) ) {
            return false;
        }
        if( !Comparer.equalsUInt8( this._minValue, other._minValue ) ) {
            return false;
        }
        if( !Comparer.equalsUInt8( this._maxValue, other._maxValue ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeUInt8( _defaultValue );
        destination.writeUInt8( _minValue );
        destination.writeUInt8( _maxValue );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _defaultValue = source.readUInt8( );
        _minValue = source.readUInt8( );
        _maxValue = source.readUInt8( );
    }

}
