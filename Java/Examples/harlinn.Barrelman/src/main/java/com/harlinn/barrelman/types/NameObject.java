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

public class NameObject extends IdentityObject {

    public final int KIND = Kind.Name;

    private String _text = "";

    public NameObject( ) {
    }
    public NameObject( byte objectState, Guid id, long rowVersion, String text ) {
        super( objectState, id, rowVersion );
        this._text = text;
    }

    @Override
    public int getObjectType( ) {
        return Kind.Name;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new NameObject( );
    }

    public String getText( ) {
        return _text;
    }
    public void setText( String value ) {
        if( !Comparer.equalsString( _text, value ) ) {
            _text = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( NameObject )target;
        targetObject._text = this._text;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (NameObject)obj;
        if( !Comparer.equalsString( this._text, other._text ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeStringUtf8( _text );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _text = source.readString( );
    }

}
