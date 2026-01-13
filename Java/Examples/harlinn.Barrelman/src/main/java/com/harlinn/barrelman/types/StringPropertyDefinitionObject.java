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

public class StringPropertyDefinitionObject extends PropertyDefinitionObject {

    public final int KIND = Kind.StringPropertyDefinition;

    private String _defaultValue = "";
    private String _pattern = "";

    public StringPropertyDefinitionObject( ) {
    }
    public StringPropertyDefinitionObject( byte objectState, Guid id, long rowVersion, Guid elementType, String name, String description, String defaultValue, String pattern ) {
        super( objectState, id, rowVersion, elementType, name, description );
        this._defaultValue = defaultValue;
        this._pattern = pattern;
    }

    @Override
    public int getObjectType( ) {
        return Kind.StringPropertyDefinition;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new StringPropertyDefinitionObject( );
    }

    public String getDefaultValue( ) {
        return _defaultValue;
    }
    public void setDefaultValue( String value ) {
        if( !Comparer.equalsString( _defaultValue, value ) ) {
            _defaultValue = value;
            onPropertyChanged( );
        }
    }

    public String getPattern( ) {
        return _pattern;
    }
    public void setPattern( String value ) {
        if( !Comparer.equalsString( _pattern, value ) ) {
            _pattern = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( StringPropertyDefinitionObject )target;
        targetObject._defaultValue = this._defaultValue;
        targetObject._pattern = this._pattern;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (StringPropertyDefinitionObject)obj;
        if( !Comparer.equalsString( this._defaultValue, other._defaultValue ) ) {
            return false;
        }
        if( !Comparer.equalsString( this._pattern, other._pattern ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeStringUtf8( _defaultValue );
        destination.writeStringUtf8( _pattern );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _defaultValue = source.readString( );
        _pattern = source.readString( );
    }

}
