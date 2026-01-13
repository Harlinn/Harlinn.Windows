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

public class SecurityPermissionObject extends AbstractDataObjectWithGuidKey {

    public final int KIND = Kind.SecurityPermission;

    private long _rowVersion = 0;
    private Guid _identifier;
    private DateTime _timestamp;
    private int _typeCode = 0;
    private boolean _canCreate = false;
    private boolean _canRead = false;
    private boolean _canUpdate = false;
    private boolean _canDelete = false;

    public SecurityPermissionObject( ) {
    }
    public SecurityPermissionObject( byte objectState, Guid id, long rowVersion, Guid identifier, DateTime timestamp, int typeCode, boolean canCreate, boolean canRead, boolean canUpdate, boolean canDelete ) {
        super( objectState, id );
        this._rowVersion = rowVersion;
        this._identifier = identifier;
        this._timestamp = timestamp;
        this._typeCode = typeCode;
        this._canCreate = canCreate;
        this._canRead = canRead;
        this._canUpdate = canUpdate;
        this._canDelete = canDelete;
    }

    @Override
    public int getObjectType( ) {
        return Kind.SecurityPermission;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new SecurityPermissionObject( );
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

    public Guid getIdentifier( ) {
        return _identifier;
    }
    public void setIdentifier( Guid value ) {
        if( !Comparer.equalsGuid( _identifier, value ) ) {
            _identifier = value;
            onPropertyChanged( );
        }
    }

    public DateTime getTimestamp( ) {
        return _timestamp;
    }
    public void setTimestamp( DateTime value ) {
        if( !Comparer.equalsDateTime( _timestamp, value ) ) {
            _timestamp = value;
            onPropertyChanged( );
        }
    }

    public int getTypeCode( ) {
        return _typeCode;
    }
    public void setTypeCode( int value ) {
        if( !Comparer.equalsInt32( _typeCode, value ) ) {
            _typeCode = value;
            onPropertyChanged( );
        }
    }

    public boolean getCanCreate( ) {
        return _canCreate;
    }
    public void setCanCreate( boolean value ) {
        if( !Comparer.equalsBoolean( _canCreate, value ) ) {
            _canCreate = value;
            onPropertyChanged( );
        }
    }

    public boolean getCanRead( ) {
        return _canRead;
    }
    public void setCanRead( boolean value ) {
        if( !Comparer.equalsBoolean( _canRead, value ) ) {
            _canRead = value;
            onPropertyChanged( );
        }
    }

    public boolean getCanUpdate( ) {
        return _canUpdate;
    }
    public void setCanUpdate( boolean value ) {
        if( !Comparer.equalsBoolean( _canUpdate, value ) ) {
            _canUpdate = value;
            onPropertyChanged( );
        }
    }

    public boolean getCanDelete( ) {
        return _canDelete;
    }
    public void setCanDelete( boolean value ) {
        if( !Comparer.equalsBoolean( _canDelete, value ) ) {
            _canDelete = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( SecurityPermissionObject )target;
        targetObject._rowVersion = this._rowVersion;
        targetObject._identifier = this._identifier;
        targetObject._timestamp = this._timestamp;
        targetObject._typeCode = this._typeCode;
        targetObject._canCreate = this._canCreate;
        targetObject._canRead = this._canRead;
        targetObject._canUpdate = this._canUpdate;
        targetObject._canDelete = this._canDelete;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (SecurityPermissionObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        if( !Comparer.equalsGuid( this._identifier, other._identifier ) ) {
            return false;
        }
        if( !Comparer.equalsDateTime( this._timestamp, other._timestamp ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._typeCode, other._typeCode ) ) {
            return false;
        }
        if( !Comparer.equalsBoolean( this._canCreate, other._canCreate ) ) {
            return false;
        }
        if( !Comparer.equalsBoolean( this._canRead, other._canRead ) ) {
            return false;
        }
        if( !Comparer.equalsBoolean( this._canUpdate, other._canUpdate ) ) {
            return false;
        }
        if( !Comparer.equalsBoolean( this._canDelete, other._canDelete ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _identifier );
        destination.writeDateTime( _timestamp );
        destination.writeInt32( _typeCode );
        destination.writeBoolean( _canCreate );
        destination.writeBoolean( _canRead );
        destination.writeBoolean( _canUpdate );
        destination.writeBoolean( _canDelete );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _identifier = source.readGuid( );
        _timestamp = source.readDateTime( );
        _typeCode = source.readInt32( );
        _canCreate = source.readBoolean( );
        _canRead = source.readBoolean( );
        _canUpdate = source.readBoolean( );
        _canDelete = source.readBoolean( );
    }

}
