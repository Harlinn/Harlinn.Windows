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

public class UInt16TimeseriesPropertyDefinitionObject extends TimeseriesPropertyDefinitionObject {

    public final int KIND = Kind.UInt16TimeseriesPropertyDefinition;

    private short _minValue = 0;
    private short _maxValue = 0;

    public UInt16TimeseriesPropertyDefinitionObject( ) {
    }
    public UInt16TimeseriesPropertyDefinitionObject( byte objectState, Guid id, long rowVersion, Guid elementType, String name, String description, short minValue, short maxValue ) {
        super( objectState, id, rowVersion, elementType, name, description );
        this._minValue = minValue;
        this._maxValue = maxValue;
    }

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
