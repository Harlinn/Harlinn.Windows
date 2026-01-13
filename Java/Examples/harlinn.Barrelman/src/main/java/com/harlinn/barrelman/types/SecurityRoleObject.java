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

public class SecurityRoleObject extends SecurityIdentifierObject {

    public final int KIND = Kind.SecurityRole;

    private String _name = "";

    public SecurityRoleObject( ) {
    }
    public SecurityRoleObject( byte objectState, Guid id, long rowVersion, Guid domain, String identity, String description, String name ) {
        super( objectState, id, rowVersion, domain, identity, description );
        this._name = name;
    }

    @Override
    public int getObjectType( ) {
        return Kind.SecurityRole;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new SecurityRoleObject( );
    }

    public String getName( ) {
        return _name;
    }
    public void setName( String value ) {
        if( !Comparer.equalsString( _name, value ) ) {
            _name = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( SecurityRoleObject )target;
        targetObject._name = this._name;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (SecurityRoleObject)obj;
        if( !Comparer.equalsString( this._name, other._name ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeStringUtf8( _name );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _name = source.readString( );
    }

}
