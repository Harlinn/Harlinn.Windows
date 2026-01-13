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

public class SingleTimeseriesPropertyDefinitionObject extends TimeseriesPropertyDefinitionObject {

    public final int KIND = Kind.SingleTimeseriesPropertyDefinition;

    private float _minValue = 0.0f;
    private float _maxValue = 0.0f;

    public SingleTimeseriesPropertyDefinitionObject( ) {
    }
    public SingleTimeseriesPropertyDefinitionObject( byte objectState, Guid id, long rowVersion, Guid elementType, String name, String description, float minValue, float maxValue ) {
        super( objectState, id, rowVersion, elementType, name, description );
        this._minValue = minValue;
        this._maxValue = maxValue;
    }

    @Override
    public int getObjectType( ) {
        return Kind.SingleTimeseriesPropertyDefinition;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new SingleTimeseriesPropertyDefinitionObject( );
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
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( SingleTimeseriesPropertyDefinitionObject )target;
        targetObject._minValue = this._minValue;
        targetObject._maxValue = this._maxValue;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (SingleTimeseriesPropertyDefinitionObject)obj;
        if( !Comparer.equalsSingle( this._minValue, other._minValue ) ) {
            return false;
        }
        if( !Comparer.equalsSingle( this._maxValue, other._maxValue ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeSingle( _minValue );
        destination.writeSingle( _maxValue );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _minValue = source.readSingle( );
        _maxValue = source.readSingle( );
    }

}
