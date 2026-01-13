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

public class BinaryPropertyDefinitionObject extends PropertyDefinitionObject {

    public final int KIND = Kind.BinaryPropertyDefinition;

    private byte[] _defaultValue = new byte[0];

    public BinaryPropertyDefinitionObject( ) {
    }
    public BinaryPropertyDefinitionObject( byte objectState, Guid id, long rowVersion, Guid elementType, String name, String description, byte[] defaultValue ) {
        super( objectState, id, rowVersion, elementType, name, description );
        this._defaultValue = defaultValue;
    }

    @Override
    public int getObjectType( ) {
        return Kind.BinaryPropertyDefinition;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new BinaryPropertyDefinitionObject( );
    }

    public byte[] getDefaultValue( ) {
        return _defaultValue;
    }
    public void setDefaultValue( byte[] value ) {
        if( !Comparer.equalsUInt8Array( _defaultValue, value ) ) {
            _defaultValue = value != null ? value.clone() : value;;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( BinaryPropertyDefinitionObject )target;
        targetObject._defaultValue = this._defaultValue != null ? this._defaultValue.clone() : this._defaultValue;;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (BinaryPropertyDefinitionObject)obj;
        if( !Comparer.equalsUInt8Array( this._defaultValue, other._defaultValue ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeUInt8Array( _defaultValue );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _defaultValue = source.readUInt8Array( );
    }

}
