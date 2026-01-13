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

public abstract class NamespaceElementObject extends AbstractDataObjectWithGuidKey {

    public final int KIND = Kind.NamespaceElement;

    private long _rowVersion = 0;
    private Guid _namespace;
    private String _name = "";
    private String _description = "";

    public NamespaceElementObject( ) {
    }
    public NamespaceElementObject( byte objectState, Guid id, long rowVersion, Guid namespace, String name, String description ) {
        super( objectState, id );
        this._rowVersion = rowVersion;
        this._namespace = namespace;
        this._name = name;
        this._description = description;
    }


    public long getRowVersion( ) {
        return _rowVersion;
    }
    public void setRowVersion( long value ) {
        if( !Comparer.equalsInt64( _rowVersion, value ) ) {
            _rowVersion = value;
            onPropertyChanged( );
        }
    }

    public Guid getNamespace( ) {
        return _namespace;
    }
    public void setNamespace( Guid value ) {
        if( !Comparer.equalsGuid( _namespace, value ) ) {
            _namespace = value;
            onPropertyChanged( );
        }
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

    public String getDescription( ) {
        return _description;
    }
    public void setDescription( String value ) {
        if( !Comparer.equalsString( _description, value ) ) {
            _description = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( NamespaceElementObject )target;
        targetObject._rowVersion = this._rowVersion;
        targetObject._namespace = this._namespace;
        targetObject._name = this._name;
        targetObject._description = this._description;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (NamespaceElementObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        if( !Comparer.equalsGuid( this._namespace, other._namespace ) ) {
            return false;
        }
        if( !Comparer.equalsString( this._name, other._name ) ) {
            return false;
        }
        if( !Comparer.equalsString( this._description, other._description ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _namespace );
        destination.writeStringUtf8( _name );
        destination.writeStringUtf8( _description );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _namespace = source.readGuid( );
        _name = source.readString( );
        _description = source.readString( );
    }

}
