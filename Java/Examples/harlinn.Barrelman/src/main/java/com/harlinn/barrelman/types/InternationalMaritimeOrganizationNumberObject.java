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

public class InternationalMaritimeOrganizationNumberObject extends IdentityObject {

    public final int KIND = Kind.InternationalMaritimeOrganizationNumber;

    private long _identifier = 0;

    public InternationalMaritimeOrganizationNumberObject( ) {
    }
    public InternationalMaritimeOrganizationNumberObject( byte objectState, Guid id, long rowVersion, long identifier ) {
        super( objectState, id, rowVersion );
        this._identifier = identifier;
    }

    @Override
    public int getObjectType( ) {
        return Kind.InternationalMaritimeOrganizationNumber;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new InternationalMaritimeOrganizationNumberObject( );
    }

    public long getIdentifier( ) {
        return _identifier;
    }
    public void setIdentifier( long value ) {
        if( !Comparer.equalsInt64( _identifier, value ) ) {
            _identifier = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( InternationalMaritimeOrganizationNumberObject )target;
        targetObject._identifier = this._identifier;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (InternationalMaritimeOrganizationNumberObject)obj;
        if( !Comparer.equalsInt64( this._identifier, other._identifier ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _identifier );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _identifier = source.readInt64( );
    }

}
